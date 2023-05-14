#include "GameMap.h"
#include <stdlib.h>
#include <time.h>
static time_t startTime=0;
static void clearScreen(){
    #if _WIN32
    system("cls");
    #elif __linux__
    system("clear");
    #endif
}
static void showTime(){
    time_t endTime=time(NULL);
    time_t costTime=endTime-startTime;
    printf("Time %ld%ld:%ld%ld  ",costTime/(60*10),costTime/60%10,(costTime%60-costTime%10)/10,costTime%10);
}
int main(){
    printf("**************\n");
    printf("**Tetris**\n");
    printf("**************\n");
    printf("              \n");
    printf(" [ 1 ]-- Play --  \n");
    printf(" [ 2 ]-- Exit --  \n");
    int option=-1;
    if(scanf("%d",&option)!=1)
        scanf("%*s");
    if(option==1)
    {
        char _filler=' ';
        char ch='-';
        int _rows=20;
        int _columns=10;
        setBoard('*','-','|');
        initalizeGameMap(_rows,_columns,_filler);
        //initalizeGame(_rows,_columns);
        startTime=time(NULL);
        //while(1){
            clearScreen();
            showTime();
            printf("Score %d\n",0);
            showGameMap();
            //currAction=getUserControl();
        //}
        freeGameMap();
        printf("Game Over!,the score is %d\n",0);
    }else if(option==2){
        printf("Exit!\n");
    }else{
        printf("Fatal error!\n");
    }
    return 0;
}