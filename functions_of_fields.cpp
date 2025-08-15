#include "common_structure.h"
#include "snake_apple.h"


void resetField(){
    GameInfo_t* info= updateCurrentState();
    for (int i=0; i<height1; i++){
        for (int j=0; j<width1; j++){
            if (info->field[i][j]!=3){ info->field[i][j]=0;}   
        }      
    }
}


void fillField( Snake& snake, const Apple& app){ //гдя яблоки и змея 
    GameInfo_t* info =updateCurrentState();
    auto occupied=getOccupiedCells(snake);   
    for (long long code : occupied) {
    int x = static_cast<int>(code >> 32);
    int y = static_cast<int>(code & 0xFFFFFFFF);
      info->field[x][y]=1;   
    }
    info->field[app.getX()][app.getY()]=3;
}
void resetDynamicField(int a) {
  GameInfo_t* info =  updateCurrentState();
  if (a == 0) {  //
    info->field = (int **) calloc(sizeof(int*) , (size_t) height1);
    for (int i = 0; i < height1; i++) {
      info->field[i] = (int*) calloc(sizeof(int) , (size_t) width1);
    }
  } else if (a == 1) {
    for (int i = 0; i < height1; i++) {
      free(info->field[i]);
    }
    free(info->field);
  }
}
void initialization(){
  Snake& snake = getSnake();
  Apple& app = getApple();
  State* st=whichState();
  GameInfo_t* info= updateCurrentState();
  resetDynamicField(0);
  app.relocate(snake);
  fillField(snake, app);
  info->score=snake.get_length_of_snake();
  info->speed = 0;
  print_field();
  st=new State(State_move);
}
///int delay = 1000 - info->speed;


void userInput(UserAction_t action, bool hold){
  State* st=whichState();

    if (action==Pause){
      *st=(State_pause);
       printWelcome(st);
    }
    else if(action==Terminate){     
      *st=(State_terminate);
      resetDynamicField(1);
      printWelcome(st);
       
    }
    else if( action==Start){
      *st=(State_start);
      initialization();
      printWelcome(st);
     
      
      
    }
    else if (action==Up || action==Down || action==Left || action==Right)
    {
      *st=(State_move);
      processSnakeMove(action);
      print_field();
      refresh();
      
    }
    // else if(action==ERR){
    //   Snake &my = getSnake();
    //   int previousDirection = getDirectionBetweenVectors(my.body[0], my.body[1]);
    //   if (previousDirection==0){action=Up;}
    //   else if(previousDirection==1){action=Down;}
    //   else if(previousDirection==2){action=Left;}
    //   else if(previousDirection==3){action=Right;}
    //   processSnakeMove(action);
      
     
    // }
}  
