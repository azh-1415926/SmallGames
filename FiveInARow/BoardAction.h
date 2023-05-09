#ifndef _BOARD_ACTION_H_
#define _BOARD_ACTION_H_
#include <stdio.h>
#include <stdbool.h>
void initalizeChessBoard(char filler);
void showChessBoard();
// char getChequer(int pos);
void addChequer(int pos,char chequer);
bool isInvalid(int pos);
int isWin(int pos);
#endif