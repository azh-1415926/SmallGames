#ifndef _CHESSBOARD_H_
#define _CHESSBOARD_H_
#include <stdio.h>
#include <stdbool.h>
void initalChessBoard(int row,int column,int linkedCount,char filler);
void showChessBoard();
char getChequer(int pos);
void addChequer(int pos,char chequer);
bool isInvalid(int pos);
int isWin(int pos);
void freeChessBoard();
#endif /* _CHESSBOARD_H_ */