#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_
#include <stdio.h>
#include <stdbool.h>
void initalizeGameScreen(int rows,int columns,char filler);
void freeGameScreen();
void setBoard(char vertex,char top,char left);
void showGameScreen();
bool isInvaild(int pos);
int getAPoint();
int getPointByIndex(int pos);
int addPoint(int pos,char point);
void delPoint(int pos);
#endif