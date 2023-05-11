#include "ChessBoard.h"
#include <stdlib.h>
#include <string.h>
static int _count=0;
static int _linkedCount=0;
static int _row=0;
static int _column=0;
static char _filler='-';
static char** pBoard=NULL;
void initalChessBoard(int row,int column,int linkedCount,char filler){
    _row=row;
    _column=column;
    _filler=filler;
    _linkedCount=linkedCount;
    pBoard=malloc(sizeof(int*)*_row);
    char* temp=malloc(sizeof(int)*_row*_column);
    memset(temp,_filler,sizeof(int)*_row*_column);
    for(int i=0;i<_row;i++){
        pBoard[i]=temp+i*_column;
    }
}
void showChessBoard(){
    for(int i=0;i<_column;i++){
        printf("%c%-3d",' ',i+1);
        if(i==_column-1){
            printf("\n");
        }
    }
    for(int i=0;i<_column;i++){
        printf("*---");
        if(i==_column-1){
            printf("*\n");
        }
    }
    for(int i=0;i<_row;i++){
        for(int j=0;j<_column;j++){
            printf("| %c ",pBoard[i][j]);
        }
        printf("| %d\n",i+1);
        for(int j=0;j<_column;j++){
            printf("*---");
            if(j==_column-1){
                printf("*\n");
            }
        }
    }
}
char getChequer(int pos){
    return pBoard[pos/_column][pos%_column];
}
void addChequer(int pos,char chequer){
    pBoard[pos/_column][pos%_column]=chequer;
    ++_count;
}
bool isInvalid(int pos){
    if(pos<0||pos>=_row*_column)
        return true;
    return pBoard[pos/_column][pos%_column]!=_filler;
}
int isWin(int pos){
    int row=pos/_column;
    int column=pos%_column;
    int count=1;
    int flag=1;
    int rflag=1;
    char chequer=pBoard[row][column];
    //horizon
    for(int i=1;i<_linkedCount;++i){
        if(flag&&column+i<_column){
            if(chequer==pBoard[row][column+i]){
                ++count;
            }else{
                count=count-(i-1);
                flag=0;
            }
        }
        if(rflag&&column-i>=0){
            if(chequer==pBoard[row][column-i]){
                ++count;
            }else{
                count=count-(i-1);
                rflag=0;
            }
        }
        if(count>=_linkedCount||flag==0&&rflag==0){
            break;
        }
    }
    if(count>=_linkedCount){
        return 1;
    count=1;
    flag=1;
    rflag=1;
    //vertical
    for(int i=1;i<_linkedCount;++i){
        if(flag&&row+i<_row){
            if(chequer==pBoard[row+i][column]){
                ++count;
            }else{
                count=count-(i-1);
                flag=0;
            }
        }
        if(rflag&&row-i>=0){
            if(chequer==pBoard[row-i][column]){
                ++count;
            }else{
                count=count-(i-1);
                rflag=0;
            }
        }
        if(count>=_linkedCount||flag==0&&rflag==0){
            break;
        }
    }
    if(count>=_linkedCount){
        return 1;
    count=1;
    flag=1;
    rflag=1;
    //
    for(int i=1;i<_linkedCount;++i){
        if(flag&&row+i<_row&&column+i<_column){
            if(chequer==pBoard[row+i][column+i]){
                ++count;
            }else{
                count=count-(i-1);
                flag=0;
            }
        }
        if(rflag&&row-i>=0&&column-i>=0){
            if(chequer==pBoard[row-i][column-i]){
                ++count;
            }else{
                count=count-(i-1);
                rflag=0;
            }
        }
        if(count>=_linkedCount||flag==0&&rflag==0){
            break;
        }
    }
    if(count>=_linkedCount){
        return 1;
    count=1;
    flag=1;
    rflag=1;
    //
    for(int i=1;i<_linkedCount;++i){
        if(flag&&row-i>=0&&column+i<_column){
            if(chequer==pBoard[row-i][column+i]){
                ++count;
            }else{
                count=count-(i-1);
                flag=0;
            }
        }
        if(rflag&&row+i<_row&&column-i>=0){
            if(chequer==pBoard[row+i][column-i]){
                ++count;
            }else{
                count=count-(i-1);
                rflag=0;
            }
        }
        if(count>=_linkedCount||flag==0&&rflag==0){
            break;
        }
    }
    if(count>=_linkedCount){
        return 1;
    }else if(_count>_row*_column-1){
        return 0;
    }
    return -1;
}
void freeChessBoard(){
    if(pBoard!=NULL){
        for(int i=0;i<_row;i++){
            free(pBoard[i]);
        }
    }
    free(pBoard);
    pBoard=NULL;
}