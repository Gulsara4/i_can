#include "snake_apple.h"


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



extern GameInfo_t currentGameState;
extern State currentMachineState; 


void processSnakeMove(UserAction_t t);
bool isColliding(const Cell& newHead, Snake& my);
bool checkAppleCollision(Snake& snake, Apple& apple, const Cell& newHead);
inline long long encodeCell(int x, int y);
std::unordered_set<long long> getOccupiedCells(Snake& my);
int getDirectionBetweenVectors(Cell one, Cell two);

void initialization();
int play_w_file(const char* opt, int score);


void fillField(Snake& snake, const Apple& app);
void print_field(State* st, WINDOW* win1, WINDOW* win2);
void resetField();
void resetDynamicField(int a);
