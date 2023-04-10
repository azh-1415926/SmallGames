#include "GameScreen.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
static int _rows=10;
static int _columns=10;
static char _filler=' ';
static char _vertex='*';
static char _topBorder='-';
static char _leftBorder='|';
static char* pScreen=NULL;
void initalizeGameScreen(int rows,int columns,char filler){
    _rows=rows+2;
    _columns=columns+2;
    _filler=filler;
    pScreen=(char*)malloc(sizeof(char)*_rows*_columns);
    printf("%d,%d,%d\n",_rows,_columns,sizeof(char)*_rows*_columns);
    memset(pScreen,_filler,sizeof(char)*_rows*_columns);
    pScreen[0]=_vertex;
    pScreen[_columns-1]=_vertex;
    pScreen[(_rows-1)*_columns]=_vertex;
    pScreen[_rows*_columns-1]=_vertex;
    for(int i=1;i<_columns-1;i++){
        pScreen[i]=_topBorder;
        pScreen[(_rows-1)*_columns+i]=_topBorder;
    }
    for(int i=1;i<_rows-1;i++){
        pScreen[i*_columns]=_leftBorder;
        pScreen[(i+1)*_columns-1]=_leftBorder;
    }
    srand(time(NULL));
}
void freeGameScreen(){
    if(pScreen==NULL)
        return;
    free(pScreen);
}
void setBoard(char vertex,char top,char left){
    _vertex=vertex;
    _topBorder=top;
    _leftBorder=left;
}

void showGameScreen(){
    for(int i=0;i<_rows;i++){
        for(int j=0;j<_columns;j++)
            printf("%c",pScreen[i*_columns+j]);
        printf("\n");
    }
}
bool isInvaild(int pos){
    if(pos<0||pos>=_rows*_columns)
        return true;
    if(pScreen[pos]==_vertex||pScreen[pos]==_topBorder||pScreen[pos]==_leftBorder)
        return true;
    return false;
}
int getAPoint(){
    int pos=-1;
    while(isInvaild(pos)||pScreen[pos]!=_filler)
        pos=rand()%(_rows*_columns);
    return pos;
}
int getPointByIndex(int pos){
    return pScreen[pos];
}
int addPoint(int pos,char point){
    char temp=pScreen[pos];
    pScreen[pos]=point;
    if(temp==_filler)
        return 0;
    return -1;
}
void delPoint(int pos){
    pScreen[pos]=_filler;
}