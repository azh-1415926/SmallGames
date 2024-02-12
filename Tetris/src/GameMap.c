#include "GameMap.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
static int _rows=10;
static int _columns=10;
static char _filler=' ';
static char _vertex='*';
static char _topBorder='-';
static char _leftBorder='|';
static char* pMap=NULL;
static bool isInvaild(int pos){
    if(pos<0||pos>=_rows*_columns)
        return true;
    if(pMap[pos]==_vertex||pMap[pos]==_topBorder||pMap[pos]==_leftBorder)
        return true;
    return false;
}
void initalizeGameMap(int rows,int columns,char filler){
    _rows=rows+2;
    _columns=columns+2;
    _filler=filler;
    pMap=(char*)malloc(sizeof(char)*_rows*_columns);
    printf("%d,%d,%d\n",_rows,_columns,sizeof(char)*_rows*_columns);
    memset(pMap,_filler,sizeof(char)*_rows*_columns);
    pMap[0]=_vertex;
    pMap[_columns-1]=_vertex;
    pMap[(_rows-1)*_columns]=_vertex;
    pMap[_rows*_columns-1]=_vertex;
    for(int i=1;i<_columns-1;i++){
        pMap[i]=_topBorder;
        pMap[(_rows-1)*_columns+i]=_topBorder;
    }
    for(int i=1;i<_rows-1;i++){
        pMap[i*_columns]=_leftBorder;
        pMap[(i+1)*_columns-1]=_leftBorder;
    }
    srand(time(NULL));
}
void freeGameMap(){
    if(pMap==NULL)
        return;
    free(pMap);
}
void setBoard(char vertex,char top,char left){
    _vertex=vertex;
    _topBorder=top;
    _leftBorder=left;
}

void showGameMap(){
    for(int i=0;i<_rows;i++){
        for(int j=0;j<_columns;j++)
            printf("%c",pMap[i*_columns+j]);
        printf("\n");
    }
}
int getAPoint(){
    int pos=-1;
    while(isInvaild(pos)||pMap[pos]!=_filler)
        pos=rand()%(_rows*_columns);
    return pos;
}
int getPointByIndex(int pos){
    return pMap[pos];
}
void addPoint(int pos,char point){
    pMap[pos]=point;
}
void delPoint(int pos){
    pMap[pos]=_filler;
}