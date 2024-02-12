#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_
#include <stdio.h>
#include <stdbool.h>
void initalizeGameMap(int rows,int columns,char filler);
void freeGameMap();
void setBoard(char vertex,char top,char left);
void showGameMap();
int getAPoint();
int getPointByIndex(int pos);
void addPoint(int pos,char point);
void delPoint(int pos);
#endif /* _GAMEMAP_H_ */