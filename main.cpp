#include <iostream>

#include "common_structure.h"
#include "snake_apple.h"

int main() {
    initscr();  
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  WINDOW* win1 = newwin(height1 + 2, width1 + 2, 0, 0); 
  WINDOW*  win2  = newwin(5, 14, 0, width1 + 2);    
  
  State* st = whichState();
  *st = State_start;
  GameInfo_t* info = updateCurrentState();
  
  
    print_field(st, win1, win2);
    timeout(1000);
  getch();
  endwin();

  delwin(win1);
  delwin(win2);

  return 0;
}