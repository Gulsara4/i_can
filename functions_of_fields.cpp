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

void fillField(Snake& snake, const Apple& app) {  // гдя яблоки и змея
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
    info->field = (int**)calloc((size_t)height1, sizeof(int*));
    for (int i = 0; i < height1; i++) {
      info->field[i] = (int*)calloc((size_t)width1, sizeof(int));
    }
  } else if (a == 1) {
    for (int i = 0; i < height1; i++) {
      free(info->field[i]);
    }
    free(info->field);
  }
}
bool isValid(UserAction_t a) {
  if (a == Up || a == Down || a == Left || a == Right || a == Pause ||
      a == Terminate || a == Start) {
    return true;
  } else {
    return false;
  }
}

void userInput(UserAction_t action) {
  State* st = whichState();
  if (action == Pause && *st == State_move) {
    *st = (State_pause);
  } else if (action == Terminate) {
    *st = (State_terminate);
    resetDynamicField(1);
  } else if (action == Start && *st == State_start) {
    initialization();
    *st = (State_move);
  } else if (action == Up || action == Down || action == Left ||
             action == Right) {
    *st = (State_move);
    processSnakeMove(action);
  } else if ((action == ERR && *st == State_move) ||
             (isValid(action) == false)) {
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
  }
#ifdef NOT_TEST
  if ((action == Pause && *st == State_move) || (action == Terminate) ||
      (action == Start)) {
    nodelay(stdscr, false);
  } else if ((action == Up || action == Down || action == Left ||
              action == Right) ||
             (action == ERR && *st == State_move)) {
    nodelay(stdscr, true);
  }
#endif
}
