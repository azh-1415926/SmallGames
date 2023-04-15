#include <stdio.h>
#include <stdlib.h>
#include "GameScreen.h"
static void clearScreen(){
    #if _WIN32
    system("cls");
    #elif __linux__
    system("clear");
    #endif
}
int main(){
    printf("**************\n");
    printf("**2048**\n");
    printf("**************\n");
    printf("              \n");
    printf(" [ 1 ]-- Play --  \n");
    printf(" [ 2 ]-- Exit --  \n");
    int option=-1;
    if(scanf("%d",&option)!=1)
        scanf("%*s");
    switch (option)
    {
        case 1:
            showGameScreen();
            addRandomPoint();
            showGameScreen();
            moveLeft();
            showGameScreen();
        case 2:
            break;
        default:
            break;
    }
    return 0;
}