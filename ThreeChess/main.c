#include "BoardAction.h"
#include "GameControl.h"
#include <stdlib.h>
int printMenu(char* tips,char* options[],unsigned int n){
    printf("**************\n");
    printf("**ThreeChess**\n");
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
        initalizeGame('O','X');
        printf("  %s\n",boardTitle);
        printChessBoard();
        boardTitle="Game Running!";
        while(1){
            do{
                printf("Pleas enter:");
                pos=playChess();
            }while(isInvaild(pos));
            chequer=getCurrChequer();
            switchToNextPlayer();
            addChequer(pos,chequer);
            system("cls");
            printf("  %s\n",boardTitle);
            printChessBoard();
            printf("lastChequer is set on postion %d.\n",pos+1);
            switch(isWin(pos)){
                case -1:
                    break;
                case 1:
                    boardTitle="Game Over!";
                    system("cls");
                    printf("  %s\n",boardTitle);
                    printChessBoard();
                    printf("%s\n",getWinner(chequer));
                    return 0;
                case 0:
                    boardTitle="Game Over!";
                    system("cls");
                    printf("  %s\n",boardTitle);
                    printChessBoard();
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