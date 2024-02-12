#include "BoardAction.h"
#include "GameControl.h"
#include <stdlib.h>
int printMenu(char* tips,char* options[],unsigned int n){
    printf("**************\n");
    printf("**FiveInARow**\n");
    printf("**************\n");
    printf("              \n");
    for(int i=0;i<n;i++)
        printf(" [ %d ]-- %s --  \n",i+1,options[i]);
    printf("              \n");
    printf("%s",tips);
    int option=-1;
    if(scanf("%d",&option)!=1)
        scanf("%*s");
    return option;
}
static void clearScreen(){
    #if _WIN32
    system("cls");
    #elif __linux__
    system("clear");
    #endif
}
int main(){
    char* menuOption[]={"Play Game!","Exit!"};
    int option=printMenu("Please enter:",menuOption,2);
    int pos=-1;
    char chequer='-';
    char filler='-';
    const char* boardTitle="Game Initalize!";
    while(option==-1)
        option=printMenu("error,please enter again:",menuOption,2);
    switch (option)
    {
    case 1:
        initalizeChessBoard(filler);
        initalizeGame('O','X',getChequer);
        printf("  %s\n",boardTitle);
        showChessBoard();
        boardTitle="Game Running!";
        while(1){
            do{
                printf("Pleas enter:");
                pos=playChess();
            }while(isInvalid(pos));
            chequer=getCurrChequer();
            switchToNextPlayer();
            addChequer(pos,chequer);
            clearScreen();
            printf("  %s\n",boardTitle);
            showChessBoard();
            printf("lastChequer is set on (%d,%d).\n",pos%15+1,pos/15+1);
            switch(isWin(pos)){
                case -1:
                    break;
                case 1:
                    boardTitle="Game Over!";
                    clearScreen();
                    printf("  %s\n",boardTitle);
                    showChessBoard();
                    printf("%s\n",getWinner(chequer));
                    return 0;
                case 0:
                    boardTitle="Game Over!";
                    clearScreen();
                    printf("  %s\n",boardTitle);
                    showChessBoard();
                    printf("%s\n",getWinner(filler));
                    return 0;
            }
        }
        break;
    case 2:
        printf("Exit!\n");
        break;
    default:
        printf("Fatal error!\n");
        exit(1);
        break;
    }
    return 0;
}