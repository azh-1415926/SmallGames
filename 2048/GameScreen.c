#include "GameScreen.h"
static int board[4][4]={0};
static int maxNumber=0;
static int totalScore=0;
static int zeroCount=16;
static void updateScore(int number){
    if(number>maxNumber){
        maxNumber=number;
    }
    totalScore+=number;
    zeroCount++;
}
void showGameScreen(){
    printf("*----*----*----*----*\n");
    printf("|%4d|%4d|%4d|%4d|\n",board[0][0],board[0][1],board[0][2],board[0][3]);
    printf("*----*----*----*----*\n");
    printf("|%4d|%4d|%4d|%4d|\n",board[1][0],board[1][1],board[1][2],board[1][3]);
    printf("*----*----*----*----*\n");
    printf("|%4d|%4d|%4d|%4d|\n",board[2][0],board[2][1],board[2][2],board[2][3]);
    printf("*----*----*----*----*\n");
    printf("|%4d|%4d|%4d|%4d|\n",board[3][0],board[3][1],board[3][2],board[3][3]);
    printf("*----*----*----*----*\n");
}
void addPoint(int pos,int number){
    board[pos/4][pos%4]=number;
    maxNumber=maxNumber<number?number:maxNumber;
    zeroCount--;
}
int getScore(){
    return totalScore;
}
int getZero(){
    return zeroCount;
}
void moveFront(){
    for(int i=0;i<4;i++){
        for(int j=1;j<4;j++){
            for(int k=1;k<4&&j-k>=0;){
                if(board[j][i]!=0&&board[j][i]==board[j-k][i]){
                    updateScore(board[j][i]);
                    board[j-k][i]=0;
                    board[j][i]*=2;
                    k++;
                }else if(board[j-k][i]==0){
                    k++;
                }else{
                    break;
                }
            }
        }
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(board[j][i]==0){
                for(int k=j+1;k<4;k++){
                    if(board[k][i]!=0){
                        board[j][i]=board[k][i];
                        board[k][i]=0;
                        break;
                    }
                }
            }
        }
    }
}
void moveLeft(){
    for(int i=0;i<4;i++){
        //curr columns
        for(int j=1;j<4;j++){
            // i row j column
            //compare to the front of k columns
            for(int k=1;k<4&&j-k>=0;){
                if(board[i][j]!=0&&board[i][j]==board[i][j-k]){
                    updateScore(board[j][i]);
                    board[i][j-k]=0;
                    board[i][j]*=2;
                    k++;
                }else if(board[i][j-k]==0){
                    k++;
                }else{
                    break;
                }
            }
        }
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(board[i][j]==0){
                for(int k=j+1;k<4;k++){
                    if(board[i][k]!=0){
                        board[i][j]=board[i][k];
                        board[i][k]=0;
                        break;
                    }
                }
            }
        }
    }
}
void moveRight(){
    for(int i=0;i<4;i++){
        for(int j=3;j>=0;j--){
            for(int k=1;k<4&&j+k<4;){
                if(board[i][j]!=0&&board[i][j]==board[i][j+k]){
                    updateScore(board[j][i]);
                    board[i][j+k]=0;
                    board[i][j]*=2;
                    k++;
                }else if(board[i][j+k]==0){
                    k++;
                }else{
                    break;
                }
            }
        }
    }
    for(int i=0;i<4;i++){
        for(int j=3;j>=0;j--){
            if(board[i][j]==0){
                for(int k=j-1;k>=0;k--){
                    if(board[i][k]!=0){
                        board[i][j]=board[i][k];
                        board[i][k]=0;
                        break;
                    }
                }
            }
        }
    }
}
void moveBehind(){
    for(int i=0;i<4;i++){
        for(int j=3;j>=0;j--){
            for(int k=1;k<4&&j+k<4;){
                if(board[j][i]!=0&&board[j][i]==board[j+k][i]){
                    updateScore(board[j][i]);
                    board[j+k][i]=0;
                    board[j][i]*=2;
                    k++;
                }else if(board[j+k][i]==0){
                    k++;
                }else{
                    break;
                }
            }
        }
    }
    for(int i=0;i<4;i++){
        for(int j=3;j>=0;j--){
            if(board[j][i]==0){
                for(int k=j-1;k>=0;k--){
                    if(board[k][i]!=0){
                        board[j][i]=board[k][i];
                        board[k][i]=0;
                        break;
                    }
                }
            }
        }
    }
}
bool isInvaild(int pos){
    if(pos<0||pos>15)
        return true;
    return board[pos/4][pos%4]!=0;
}
bool isFull(){
    return zeroCount==0;
}
int isWin(){
    if(maxNumber==2048){
        return 1;
    }else if(zeroCount==0){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(i+1<4&&board[i][j]==board[i+1][j]){
                    return 0;
                }
                if(j+1<4&&board[i][j]==board[i][j+1]){
                    return 0;
                }
            }
        }
    }else{
        return 0;
    }
    return -1;
}