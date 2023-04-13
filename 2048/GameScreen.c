#include "GameScreen.h"
static int board[16]={0};
void showGameScreen(){
    printf("*----*----*----*----*\n");
    printf("|%4d|%4d|%4d|%4d|\n",board[0],board[1],board[2],board[3]);
    printf("*----*----*----*----*\n");
    printf("|%4d|%4d|%4d|%4d|\n",board[4],board[5],board[6],board[7]);
    printf("*----*----*----*----*\n");
    printf("|%4d|%4d|%4d|%4d|\n",board[8],board[9],board[10],board[11]);
    printf("*----*----*----*----*\n");
    printf("|%4d|%4d|%4d|%4d|\n",board[12],board[13],board[14],board[15]);
    printf("*----*----*----*----*\n");
}
void addPoint(int pos,int data){
    board[pos]=data;
}
bool isInvaild(int pos){
    if(pos<0||pos>15)
        return true;
    return board[pos]!=0;
}
int isWin(int pos){
    return board[pos]==2048;
}