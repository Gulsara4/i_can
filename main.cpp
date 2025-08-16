#include <iostream>
#include "common_structure.h"
#include "snake_apple.h"

int main(){
#ifdef RUN1   
    userInput(Start, false);
    YYY();
#endif

    initscr();                 // Инициализация ncurses
    cbreak();
    noecho();
    nodelay(stdscr, FALSE);
    keypad(stdscr, TRUE);   
     State* st=whichState();
    *st=State_start;
    GameInfo_t* info=updateCurrentState();    
   
    while(1){
        if ( *st==State_start){
            printw("GOOOO %d", *st);
            print_field(st);
            
            nodelay(stdscr, FALSE);
            int ch = getch(); // ждём
            while (ch!=ERR){
                userInput((UserAction_t)ch, false);
                ch = getch();
            }
            refresh();
            
            continue;
            
        }
        else if (*st==State_pause ){
            //printw("PAUSE %d", *st);
            print_field(st);
            refresh();
            nodelay(stdscr, FALSE);
            int ch = getch(); // ждём
            userInput((UserAction_t)ch, false);
            continue;
            
        }
        else if ( *st==State_terminate ){
            nodelay(stdscr, FALSE);
            
            print_field(st);
            break;
        }
        else if (*st==State_move){
             nodelay(stdscr, TRUE);

        }
       
        timeout(1000);

        int ch = getch();       
        userInput((UserAction_t)ch, false);
        print_field(st);
        refresh();
        
    }
  
        
        

    refresh();                 // Отображение строки на реальном экране
    getch();                   // Ожидание пользовательского ввода
    endwin(); 

    return 0;
}