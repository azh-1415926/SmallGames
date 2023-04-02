#include "GameControl.h"
#include "BoardAction.h"
#include<stdlib.h>
#include<time.h>
char FirstPlayer='-';
char PlayerChequer='-';
char ComputerChequer='-';
int printMenu(char* tips){
    char option;
    system("cls");
    printf("**************\n");
    printf("**ThreeChess**\n");
    printf("**************\n");
    printf("              \n");
    printf(" [1]--Play--  \n");
    printf(" [2]--Exit--  \n");
    printf("              \n");
    printf("%s",tips);
    scanf("%c",&option);
    fflush(stdin);
    if(option<'1'||option>'2')
        printMenu("Please enter incorrect option:");
    return option-48;
}
void menuControl(unsigned int option){
    if(option==2)
        exit(1);
    playerInitalize();
    chessboardInitalize('-');
    startGame();
}
int getOption(char* title,char* options[],unsigned int n,char* tips){
    int i=0;
    char option;
    system("cls");
    printf("%s\n",title);
    for(;i<n-1;++i){
        printf("[%d] %s or",i+1,options[i]); 
    }
    printf("[%d] %s\n",i+1,options[i]);
    printf("%s",tips);
    fflush(stdin);
    scanf("%c",&option);
    fflush(stdin);
    if(option<'1'||option>(n+48))
        getOption(title,options,n,"Please enter incorrect option.\n");
    return option-48;
}

void playerInitalize(){
    char *chequers[]={"O","X"};
    char *players[]={"player","computer"};
    int choose=0;
    choose=getOption("Chequer Option",chequers,2,"[1-2]:");
    PlayerChequer=(choose==1?'O':'X');
    ComputerChequer=(choose==1?'X':'O');
    choose=getOption("Player Option",players,2,"[1-2]:");
    FirstPlayer=(choose==1?'P':'C');
}
void startGame(){
    if(FirstPlayer=='P')
        player(PlayerChequer);
    while(1){
        computer(ComputerChequer);
        player(PlayerChequer);
    }
}
void gameSettle(char chequer){
    if(chequer==PlayerChequer)
        printChessBoard("Game Over","Player Wins!\n");
    else if(chequer==ComputerChequer)
        printChessBoard("Game Over","Computer Wins!\n");
    else
        printChessBoard("Game Over","No One Wins!\n");
    system("pause");
    exit(1);
}
void player(char chequer){
    char num;
    printChessBoard("Game Running","Please push your chequer.\nUsing number 1-9:");
    fflush(stdin);
    scanf("%c",&num);
    while(judgeInvailed(num-49)){
        printChessBoard("Game Running","The position is valied.\n");
        printf("Please choose again:\n");
        fflush(stdin);
        scanf("%c",&num);
    }
    printChessBoard("Game Running","Player push the chequer.\n");
    printf("Player push to postion %d\n",num-48);
    addChequer(chequer,num-49);
    chequerJudge(num-49,gameSettle);
}
void computer(char chequer){
    srand((unsigned)time(NULL));
    int num=rand()%9+1;
    while(judgeInvailed(num))
        num=rand()%9+1;
    printChessBoard("Game Running","Computer push the chequer.\n");
    printf("Computer push to postion %d\n",num+1);
    addChequer(chequer,num);
    chequerJudge(num,gameSettle);
}