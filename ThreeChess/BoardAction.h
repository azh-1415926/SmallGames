#ifndef _BOARD_ACTION_H_
#define _BOARD_ACTION_H_
#include<stdio.h>
void chessboardInitalize(char filler);
void printChessBoard(char* title,char* tips);
void addChequer(char chequer,int pos);
int judgeInvailed(int pos);
void chequerJudge(int pos,void(*handle)(char));
#endif