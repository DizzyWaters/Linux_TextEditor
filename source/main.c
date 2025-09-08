#include <curses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#define DX 8
#define DY 8


  struct MyStr
  {
    char *line;
    size_t len;
    ssize_t nread;
  };

int main(int argc, char *argv[])
{

  if(argc < 2)
  {
    printf("Nothing to work with\n");
    exit(-1);
  }
  if(argc < 2)
  {
    printf("Too many arguments\n");
    exit(-1);
  }

  FILE *fp = NULL;
  fp = fopen(argv[1], "r");
  if(fp == NULL){
    printf("can't open file");
    exit(-1);
  }
  char* curLine;
  size_t lineLen;
  



  WINDOW *frame, *win;
  int c = 0;

  initscr();
  noecho();
  cbreak();
  printw("Window:");
  refresh();
  
  frame = newwin(LINES - 2*DY, COLS - 2*DX, DY, DX);
  box(frame, 0, 0);
  mvwaddstr(frame, 0, (int)((COLS - 2*DX - 5)/2), argv[1]);
  wrefresh(frame);

  win = newwin(LINES - 2*DY - 2, COLS - 2 *DX-2, DY + 1 , DX + 1 );
  keypad(win, TRUE);
  scrollok(win, TRUE);

  while(getline(&curLine, &lineLen, fp) != -1)
  {
    wprintw(win, "%s", curLine);
  }

  if((c = wgetch(win)) == 27)
  {
  delwin(win);
  delwin(frame);
  }
  endwin();
  return 0;
}
