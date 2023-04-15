#include "GameControl.h"
void moveAction(){
    
}
int getUserControl(){
    char ch=0;
    int action;
    #if _WIN32
    if(!kbhit()){
        Sleep(1000);
    }
    if(kbhit()){
        ch=getch();
    }
    #elif __linux__

    #endif
    switch (ch)
    {
    case 56:
    case 119:
        /* front */
        action=MOVE_FRONT;
        break;
    case 52:
    case 97:
        /* left */
        action=MOVE_LEFT;
        break;
    case 50:
    case 115:
        /* behind */
        action=MOVE_BEHIND;
        break;    
    case 54:
    case 100:
        /* right */
        action=MOVE_RIGHT;
        break;
    default:
        action=-1;
        break;
    }
    return action;
}