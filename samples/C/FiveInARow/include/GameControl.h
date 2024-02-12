#ifndef _GAME_CONTROL_H_
#define _GAME_CONTROL_H_
#include<stdio.h>
void initalizeGame(char firstChequer,char secondChequer,char (*get)(int));
int playChess();
char getCurrChequer();
void switchToNextPlayer();
const char* getWinner(char chequer);
#endif