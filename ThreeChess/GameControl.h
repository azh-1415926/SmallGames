#ifndef _GAME_CONTROL_H_
#define _GAME_CONTROL_H_
#include<stdio.h>
int printMenu(char* tips);
void menuControl(unsigned int option);
int getOption(char* title,char* options[],unsigned int n,char* tips);
void playerInitalize();
void startGame();
void gameSettle(char chequer);
void player(char chequer);
void computer(char chequer);
#endif