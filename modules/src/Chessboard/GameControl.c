#include <ChessBoard/GameControl.h>
#include<stdlib.h>

static char currChequer='-';
static char playerChequer='-';
static char computerChequer='-';
static int playerOption=-1;
static int(*computerPlayer)(int)=NULL;

static int getOption(char* title,char* options[],unsigned int n)
{
    int i=0;
    int option=-1;
    printf("%s\n",title);
    for(;i<n-1;++i)
        printf("[%d] %s or ",i+1,options[i]); 
    printf("[%d] %s\n",i+1,options[i]);
    while(scanf("%d",&option)!=1)
    {
        printf("enter[ 1-%d ]:",n);
        scanf("%*s");
    }
    if(option<1||option>n)
    {
        printf("error option,system will give a automatic selection!\n");
        option=-1;
    }
    return option-1;
}

static int getPlayerOption()
{
    int option=-1;
    if(scanf("%d",&option)!=1)
        scanf("%*s");
    if(option!=-1)
        playerOption=option-1;
    return option-1;
}

static int getComputerOption()
{
    int option=-1;
    if(computerPlayer!=NULL)
        option=computerPlayer(playerOption);
    return option;
}

void initalizeGame(char firstChequer,char secondChequer)
{
    char chequer_1[2]={0};
    chequer_1[0]=firstChequer;
    char chequer_2[2]={0};
    chequer_2[0]=secondChequer;
    char* chequers[]={chequer_1,chequer_2};
    char* players[]={"player","computer"};
    int choose=0;
    choose=getOption("Chequer Option",chequers,2);
    playerChequer=(choose==0?firstChequer:secondChequer);
    computerChequer=(choose==0?secondChequer:firstChequer);
    choose=getOption("Player Option",players,2);
    currChequer=(choose==0?playerChequer:computerChequer);
}

void setComputerPlayer(int(*computer)(int))
{
    computerPlayer=computer;
}

int playChess()
{
    if(currChequer==computerChequer)
        return getComputerOption();
    if(currChequer==playerChequer)
        return getPlayerOption();
    return -1;
}

char getCurrChequer()
{
    return currChequer;
}

void switchToNextPlayer()
{
    currChequer=(currChequer==playerChequer)?(computerChequer):(playerChequer);
}

const char* getWinner(char chequer)
{
    if(chequer==playerChequer)
        return "Player Wins!";
    if(chequer==computerChequer)
        return "Computer Wins!";
    return "No one Wins!";
}