#include "GameMap.h"
int main(){
    setBoard('=','^','+');
    initalizeGameMap(6,8,' ');
    showGameMap();
    //getAPoint();
    //getPointByIndex(int pos);
    //addPoint(int pos,char point);
    //delPoint(int pos);
    freeGameMap();
    return 0;
}