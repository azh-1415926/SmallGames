#ifndef _GAME_CONTROL_H_
#define _GAME_CONTROL_H_
#include<stdio.h>
#include <stdbool.h>
void initalizeGame(char firstChequer,char secondChequer);
void setJudgeFunc(bool(*judge)(int));
int playChess();
char getCurrChequer();
void switchToNextPlayer();
const char* getWinner(char chequer);
#endif /* _GAME_CONTROL_H_ */
