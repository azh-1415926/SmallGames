#include "BoardAction.h"
#include <string.h>
static int chequerCount=0;
static char board[9]={0};
static char chequerFiller='-';
void initalizeChessBoard(char filler){
    memset(board,filler,sizeof(board));
}
void showChessBoard(){
    printf("*---*---*---*\n");
    printf("| %c | %c | %c |\n",board[0],board[1],board[2]);
    printf("*---*---*---*\n");
    printf("| %c | %c | %c |\n",board[3],board[4],board[5]);
    printf("*---*---*---*\n");
    printf("| %c | %c | %c |\n",board[6],board[7],board[8]);
    printf("*---*---*---*\n");
}
char getChequer(int pos){
    if(pos<0||pos>8)
        return '\0';
    return board[pos];
}
void addChequer(int pos,char chequer){
    board[pos]=chequer;
    ++chequerCount;
}
bool isInvalid(int pos){
    if(pos<0||pos>8)
        return true;
    return board[pos]!=chequerFiller;
}
int isWin(int pos){
    int row=pos/3;
    int column=pos%3;
    int count=1;
    char chequer=board[pos];
    for(int i=1;i<3;++i){
        if(chequer==board[(row+i)%3*3+column])
            ++count;
    }
    if(count==3)
        return 1;
    count=1;
    for(int i=1;i<3;++i){
        if(chequer==board[row*3+(column+i)%3])
            ++count;
    }
    if(count==3)
        return 1;
    count=1;
    for(int i=1;i<3&&(row==column);++i){
        if(chequer==board[(row+i)%3*3+(column+i)%3])
            ++count;
    }
    if(count==3)
        return 1;
    count=1;
    for(int i=1;i<3&&((row+column)==2);++i){
        if(chequer==board[(row+i)%3*3+(column+2*i)%3])
            ++count;
    }
    if(count==3)
        return 1;
    if(chequerCount>8)
        return 0;
    return -1;
}