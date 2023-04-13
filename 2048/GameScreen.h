#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_
#include <stdio.h>
#include <stdbool.h>
void showGameScreen();
void addPoint(int pos,int data);
bool isInvaild(int pos);
int isWin(int pos);
#endif /* _GAME_MAP_H_ */
