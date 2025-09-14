#include <curses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#define DX 12
#define DY 12

// keys
#define SPACEBAR 32

// make linked list
// OR count lines in file and then load it to char**
  struct MyStr
  {
    char **line;
    size_t len;
    ssize_t nread;
  };

  int fLinesCounter(FILE *fp)
{ 
  int result = 0;
  char endline = '\n';
  char c;
  while((c = fgetc(fp)) != EOF)
  {
    if(c == endline)
    {
      result++;
    }
  }
  rewind(fp);
  return result;
}

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
  
  // count lines
  int linesInFILE = fLinesCounter(fp);
  //int linesInFILE = 1;

  WINDOW *frame, *win;
  int c = 0;

  initscr();
  noecho();
  cbreak();
  printw("Window: filename: %s Lines in file: %d", argv[1], linesInFILE);
  refresh();
  
  frame = newwin(LINES - 2*DY, COLS - 2*DX, DY, DX);
  box(frame, 0, 0);
  mvwaddstr(frame, 0, (int)((COLS - 2*DX - 5)/2), argv[1]);
  wrefresh(frame);

  win = newwin(LINES - 2*DY - 2, COLS - 2 *DX-2, DY + 1 , DX + 1 );
  keypad(win, TRUE);
  scrollok(win, TRUE);

  int lineCounter = 1;
  while((c = wgetch(win)) != 27)
  {
  if(c == SPACEBAR)
  {
    if(getline(&curLine, &lineLen, fp) != -1)
      {
        wprintw(win, "%d : %s", lineCounter,curLine);
        lineCounter++;
      }
  }
  }
  delwin(win);
  delwin(frame);
  endwin();
  return 0;
}
