#include <iostream>
#include "common_structure.h"
#include "snake_apple.h"

int main(){
#ifdef RUN1   
    userInput(Start, false);
    YYY();
#endif
#ifdef RUN2
    initscr();                 // Инициализация ncurses
    cbreak();
    noecho();
    nodelay(stdscr, FALSE);
    keypad(stdscr, TRUE);
    
     State* st=whichState();
     *st=State_start;
     
    while(1){
      

        
        int ch = getch();
        // printw("%d\n", ch);
        // refresh();
        if (ch != ERR) {
            userInput((UserAction_t)ch, false);
        }
        
        
        
        
    }
    
    refresh();                 // Отображение строки на реальном экране
    getch();                   // Ожидание пользовательского ввода
    endwin(); 
#endif  
    return 0;
}