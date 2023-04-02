#include "BoardAction.h"
#include<string.h>
int ChequerCount=0;
char chessboard[9];
void chessboardInitalize(char filler){
    memset(chessboard,filler,sizeof(chessboard));
    printChessBoard("Game Start","Initalize Chessboard.\n");
}
void printChessBoard(char* title,char* tips){
    system("cls");
    printf("  %s\n",title);
    printf("*---*---*---*\n");
    printf("| %c | %c | %c |\n",chessboard[0],chessboard[1],chessboard[2]);
    printf("*---*---*---*\n");
    printf("| %c | %c | %c |\n",chessboard[3],chessboard[4],chessboard[5]);
    printf("*---*---*---*\n");
    printf("| %c | %c | %c |\n",chessboard[6],chessboard[7],chessboard[8]);
    printf("*---*---*---*\n  %s",tips);
}
int judgeInvailed(int pos){
    if(pos<0||pos>8)
        return 1;
    if(chessboard[pos]=='O'||chessboard[pos]=='X')
        return 1;
    return 0;
}
void chequerJudge(int pos,void(*handle)(char)){
    int row=pos/3;
    int column=pos%3;
    int count=1;
    int maxcount=1;
    char chequer=chessboard[pos];
    for(int i=1;i<3;++i){
        if(chessboard[pos]==chessboard[(row+i)%3*3+column])
            ++count;
    }
    maxcount=(maxcount<count)?(count):(maxcount);
    count=1;
    for(int i=1;i<3;++i){
        if(chessboard[pos]==chessboard[row*3+(column+i)%3])
            ++count;
    }
    maxcount=(maxcount<count)?(count):(maxcount);
    count=1;
    for(int i=1;i<3&&(row==column);++i){
        if(chessboard[pos]==chessboard[(row+i)%3*3+(column+i)%3])
            ++count;
    }
    maxcount=(maxcount<count)?(count):(maxcount);
    count=1;
    for(int i=1;i<3&&((row+column)==2);++i){
        if(chessboard[pos]==chessboard[(row+i)%3*3+(column+2*i)%3])
            ++count;
    }
    maxcount=(maxcount<count)?(count):(maxcount);
    count=1;
    if(maxcount==3){
        handle(chequer);
    }
    if(ChequerCount>8){
        handle('-');
    }
}
void addChequer(char chequer,int pos){
    chessboard[pos]=chequer;
    ++ChequerCount;
}
