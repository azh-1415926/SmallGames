#include "GameControl.h"
static int _rows=10;
static int _columns=10;
static int lastAction=MOVE_FRONT;
void initalizeGame(int rows,int columns){
    _rows=rows+2;
    _columns=columns+2;
}
bool moveIsInvaild(int flag){
    bool status=true;
    switch (flag)
    {
    case MOVE_FRONT:
        if(lastAction!=MOVE_BEHIND){
            status=false;
        }
        break;
    case MOVE_LEFT:
        if(lastAction!=MOVE_RIGHT){
            status=false;
        }
        break;
    case MOVE_RIGHT:
        if(lastAction!=MOVE_LEFT){
            status=false;
        }
        break;
    case MOVE_BEHIND:
        if(lastAction!=MOVE_FRONT){
            status=false;
        }
        break;
    default:
        break;
    }
    return status;
}
int movePoint(int pos,int flag){
    switch (flag)
    {
    case MOVE_FRONT:
        pos=pos<2*_columns?-1:pos-_columns;
        break;
    case MOVE_LEFT:
        pos=(pos-1)%_columns==0?-1:pos-1;
        break;
    case MOVE_BEHIND:
        pos=pos>(_rows-2)*_columns-1?-1:pos+_columns;
        break;
    case MOVE_RIGHT:
        pos=(pos+2)%_columns==0?-1:pos+1;
        break;
    default:
        break;
    }
    lastAction=flag;
    return pos;
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