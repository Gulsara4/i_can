
#ifndef COMMON_STRUCTURES
#define COMMON_STRUCTURES
#include <ncurses/ncurses.h>
#include <string>
#include <cstring>
#define height1 20
#define width1 10

typedef enum {
  Start = 'g',
  Pause = 'p',
  Terminate = 'q',
  Left = 'a', //KEY_LEFT,
  Right ='d',// KEY_RIGHT,
  Up = 'w', //KEY_UP,
  Down = 's',// KEY_DOWN,
  Action
} UserAction_t;

typedef struct {
  int** field;
  int** next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;
typedef enum {
  State_zero,
  State_start,
  State_move,
  State_pause,
  State_terminate,

} State;

void userInput(UserAction_t action, bool hold);

GameInfo_t* updateCurrentState();
State* whichState();
void initialization();
#endif