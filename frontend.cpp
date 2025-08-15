#include "common_structure.h"
#include "snake_apple.h"

#ifdef RUN1
void print_field(){
    GameInfo_t* info =updateCurrentState();
    for (int i=0; i<height1; i++){
      
         std::cout<< i<<" ";
         if (i<10){ std::cout<<" ";}
        for (int j=0; j<width1; j++){
            if (info->field[i][j]==1){              
            std::cout<<"1";}
            else if (info->field[i][j]==3){
            std::cout<<"3";}
            else{    std::cout<<" ";}
        }
         std::cout<<"\n";
    }
}

#endif
#ifdef RUN2
void print_field(){
  GameInfo_t* info =updateCurrentState();
   WINDOW *win1 = newwin(height1+2, width1+2, 0, 0);
    box(win1, 0, 0);
    for (int i=0; i<height1; i++){
        for (int j=0; j<width1; j++){
            if (info->field[i][j]==1){              
            mvwprintw(win1, i + 1, j + 1, "1");}
            else if (info->field[i][j]==3){
            mvwprintw(win1, i + 1, j + 1, "3");}
            else{    
              mvwprintw(win1, i + 1, j + 1, " ");}
        }
         std::cout<<"\n";
    }
    wrefresh(win1);
    WINDOW *win2 = newwin(5, 14, 0 , width1+2);
    box(win2, 0, 0);
    std::string msg = "Score";
    int y = 1;
    int x = 2;
    mvwprintw(win2, y, x, "%s %d", msg.c_str(), info->score);
    mvwprintw(win2, 3, x, "%s %d", "Level", info->level);
    wrefresh(win2);
    delwin(win1);
    delwin(win2);         
}
void printWelcome(State* st){
  
  WINDOW *win1 = newwin(height1+2, width1+2, 0, 0);
  box(win1, 0, 0);
  if (*st==State_terminate){
     mvwprintw(win1, 1, 1, "Game over");
  }
  else if (*st==State_start){
    mvwprintw(win1, 1, 1, "Game Snake");
    mvwprintw(win1, 2, 1, "Press o to start ");}
  
  else if (*st==State_pause){
     mvwprintw(win1, 1, 1, "Pause");
  }
  wrefresh(win1);
  delwin(win1);
}
#endif