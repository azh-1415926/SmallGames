#include "GameControl.h"
#include<stdlib.h>
#include<time.h>
static char currChequer='-';
static char playerChequer='-';
static char computerChequer='-';
static char (*getChequerByPos)(int);
static int playerOption=-1;
static int getOption(char* title,char* options[],unsigned int n){
    int i=0;
    int option=-1;
    printf("%s\n",title);
    for(;i<n-1;++i){
        printf("[%d] %s or ",i+1,options[i]); 
    }
    printf("[%d] %s\n",i+1,options[i]);
    while(scanf("%d",&option)!=1){
        printf("enter[ 1-%d ]:",n);
        scanf("%*s");
    }
    if(option<0||option>=n){
        printf("error option,system will give a automatic selection!\n");
        option=-1;
    }
    return option;
}
static int getPlayerOption(){
    int row=-1;
    int column=-1;
    int option=-1;
    if(scanf("%d %d",&row,&column)!=2){
        scanf("%*s");
        option=-1;
    }else{
        option=(column-1)*15+row-1;
        if(getChequerByPos(option)=='-'){
            playerOption=option;
        }
    }
    return option;
}
static int getComputerOption(){
    return rand()%(15*15);
    int pos=-1;
    int count=1;
    int extend=0;
    int flag=1;
    int rflag=1;
    char chequer='\0';
    //getChequerByPos(playerOption)
    for(int i=1;i<5;i++){
        chequer=getChequerByPos(playerOption+i);
        if(flag&&chequer!='\0'){
            if(chequer==playerChequer){
                count++;
            }else{
                pos=playerOption+i;
                if(chequer=='-'){
                    for(int j=i+1;j<5;j++){
                        if(getChequerByPos(playerOption+i+1)==playerChequer)
                            extend++;
                    }
                }else{
                    flag=0;
                    pos=-1;
                }
            }
        }
        if(pos!=-1&&count+extend>=4){
            return pos;
        }
        chequer=getChequerByPos(playerOption-1);
        if(flag&&chequer!='\0'){
            if(chequer==playerChequer){
                count++;
            }else{
                rflag=0;
            }
        }
    }
}
void initalizeGame(char firstChequer,char secondChequer,char (*get)(int)){
    char chequer_1[2]={0};
    chequer_1[0]=firstChequer;
    char chequer_2[2]={0};
    chequer_2[0]=secondChequer;
    char* chequers[]={chequer_1,chequer_2};
    char* players[]={"player","computer"};
    int choose=0;
    choose=getOption("Chequer Option",chequers,2);
    playerChequer=(choose==1?firstChequer:secondChequer);
    computerChequer=(choose==1?secondChequer:firstChequer);
    choose=getOption("Player Option",players,2);
    currChequer=(choose==1?playerChequer:computerChequer);
    getChequerByPos=get;
    srand((unsigned)time(NULL));
}
int playChess(){
    if(currChequer==computerChequer)
        return getComputerOption();
    if(currChequer==playerChequer)
        return getPlayerOption();
    return -1;
}
char getCurrChequer(){
    return currChequer;
}
void switchToNextPlayer(){
    currChequer=(currChequer==playerChequer)?(computerChequer):(playerChequer);
}
const char* getWinner(char chequer){
    if(chequer==playerChequer)
        return "Player Wins!";
    if(chequer==computerChequer)
        return "Computer Wins!";
    return "No one Wins!";
}