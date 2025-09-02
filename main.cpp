#include <iostream>

#include "snake.h"
int main() {
  

  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, false);
  start_color();
    init_pair(1, COLOR_RED, COLOR_RED);
  init_pair(2, COLOR_YELLOW, COLOR_YELLOW);
  WINDOW* win1 = newwin(height1 + 2, 2* width1 + 2, 0, 0);
  WINDOW* win2 = newwin(5, 14, 0, 2* width1 + 3);

  State* st = whichState();
  *st = State_start;
  GameInfo_t* info = updateCurrentState();
  print_field(st, win1, win2);
  int ch = getch();
  while (1) {
    userInput((UserAction_t)ch);
    if (*st == State_move) {
      timeout(info->speed);
    }

    print_field(st, win1, win2);

    ch = getch();
  }
  getch();
  refresh();

  delwin(win1);
  delwin(win2);
  endwin();
  return 0;
}