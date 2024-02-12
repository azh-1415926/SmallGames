#include "GameControl.h"
#include<stdlib.h>
#include<time.h>
static char currChequer='-';
static char playerChequer='-';
static char computerChequer='-';
static int playerOptions[9]={0};
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
    if(option<1||option>n){
        printf("error option,system will give a automatic selection!\n");
        option=-1;
    }
    return option;
}
static int getPlayerOption(){
    int option=-1;
    if(scanf("%d",&option)!=1)
        scanf("%*s");
    if(option!=-1&&playerOptions[option-1]==0){
        playerOptions[option-1]=1;
        playerOption=option-1;
    }
    return option-1;
}
static int getComputerOption(){
    int option=-1;
    if(playerOption!=-1){
        int row=playerOption/3;
        int column=playerOption%3;
        for(int i=1;i<3;++i){
            if(playerOptions[(row+i)%3*3+column]==1){
                option=(row+i+1)%3*3+column;
                if(i==2){
                    option=(row+i+2)%3*3+column;
                }
                break;
            }
            if(playerOptions[row*3+(column+i)%3]==1){
                option=row*3+(column+i+1)%3;
                if(i==2){
                    option=row*3+(column+i+2)%3;
                }
                break;
            }
        }
        for(int i=1;i<3&&(row==column);++i){
            if(playerOptions[(row+i)%3*3+(column+i)%3]==1){
                option=(row+i+1)%3*3+(column+i+1)%3;
                if(i==2){
                    option=(row+i+2)%3*3+(column+i+2)%3;
                }
                break;
            }
        }
        for(int i=1;i<3&&((row+column)==2);++i){
            if(playerOptions[(row+i)%3*3+(column+2*i)%3]==1){
                option=(row+i+1)%3*3+(column+2*(i+1))%3;
                if(i==2){
                    option=(row+i+2)%3*3+(column+2*(i+2))%3;
                }
                break;
            }
        }
        playerOption=-1;
    }else if(playerOption==-1&&playerOptions[4]==0){
        option=4;
    }else if(playerOption==-1&&playerOptions[4]!=0){
        option=(rand()%2)?(4+(rand()%2+1)*2):(4-(rand()%2+1)*2);
        if(playerOptions[0]!=0&&playerOptions[2]!=0&&playerOptions[6]!=0&&playerOptions[8]!=0){
            playerOption=-2;
        }
    }
    if(playerOption==-2){
        option=rand()%9;
    }else if(playerOptions[option]==0){
        playerOptions[option]=-1;
    }
    return option;
}
void initalizeGame(char firstChequer,char secondChequer){
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