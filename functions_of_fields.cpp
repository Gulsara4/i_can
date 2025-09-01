// #include "common_structure.h"
// #include "snake_apple.h"
#include "snake.h"

void resetField() {
  GameInfo_t* info = updateCurrentState();
  for (int i = 0; i < height1; i++) {
    for (int j = 0; j < width1; j++) {
      if (info->field[i][j] != 3) {
        info->field[i][j] = 0;
      }
    }
  }
}

void fillField(Snake& snake, const Apple& app) {  //гдя яблоки и змея
  GameInfo_t* info = updateCurrentState();
  auto occupied = getOccupiedCells(snake);
  for (long long code : occupied) {
    int x = static_cast<int>(code >> 32);
    int y = static_cast<int>(code & 0xFFFFFFFF);
    info->field[x][y] = 1;
  }
  info->field[app.getX()][app.getY()] = 3;
}
void resetDynamicField(int a) {
  GameInfo_t* info = updateCurrentState();
  if (a == 0) {  //
    info->field = (int**)calloc(sizeof(int*), (size_t)height1);
    for (int i = 0; i < height1; i++) {
      info->field[i] = (int*)calloc(sizeof(int), (size_t)width1);
    }
  } else if (a == 1) {
    for (int i = 0; i < height1; i++) {
      free(info->field[i]);
    }
    free(info->field);
  }
}

void userInput(UserAction_t action) {
  State* st = whichState();

  if (action == Pause && *st==State_move) {
    *st = (State_pause);
    nodelay(stdscr, false);
  } else if (action == Terminate) {
    nodelay(stdscr, false);
    *st = (State_terminate);
    resetDynamicField(1);
    

  } else if (action == Start) {
    nodelay(stdscr, false);
    *st = (State_start);
    initialization();
    
    *st = (State_move);

  } else if (action == Up || action == Down || action == Left ||
             action == Right) {
    *st = (State_move);
    processSnakeMove(action);
    nodelay(stdscr, true);

  } else if (action == ERR && *st == State_move) {
    Snake& my = getSnake();
    int previousDirection = getDirectionBetweenVectors(my.body[0], my.body[1]);
    if (previousDirection == 0) {
      action = Up;
    } else if (previousDirection == 1) {
      action = Down;
    } else if (previousDirection == 2) {
      action = Left;
    } else if (previousDirection == 3) {
      action = Right;
    }
    processSnakeMove(action);
    nodelay(stdscr, true);
  }
}
