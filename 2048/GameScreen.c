#include "GameScreen.h"
static int board[4][4]={0};
void showGameScreen(){
    printf("*----*----*----*----*\n");
    printf("|%4d|%4d|%4d|%4d|\n",board[0][0],board[0][1],board[0][2],board[0][3]);
    printf("*----*----*----*----*\n");
    printf("|%4d|%4d|%4d|%4d|\n",board[1][0],board[0][1],board[1][2],board[1][3]);
    printf("*----*----*----*----*\n");
    printf("|%4d|%4d|%4d|%4d|\n",board[2][0],board[2][1],board[2][2],board[2][3]);
    printf("*----*----*----*----*\n");
    printf("|%4d|%4d|%4d|%4d|\n",board[3][0],board[3][1],board[3][2],board[3][3]);
    printf("*----*----*----*----*\n");
}
void addRandomPoint(){
    board[0][0]=2;
    board[1][0]=1;
    board[2][0]=1;
    board[3][0]=0;
    board[0][1]=2;
    board[1][1]=2;
    board[2][1]=1;
    board[3][1]=1;
    board[0][2]=2;
    board[1][2]=2;
    board[2][2]=1;
    board[3][2]=2;
    // board[0][0]=2;
    // board[0][1]=1;
    // board[0][2]=1;
    // board[0][3]=0;
    // board[1][0]=1;
    // board[1][1]=1;
    // board[1][2]=1;
    // board[1][3]=2;
    // board[2][0]=2;
    // board[2][1]=1;
    // board[2][2]=1;
    // board[2][3]=2;
}
static void moveHorizon(){
    for(int i=0;i<4;i++){
        //curr columns
        for(int j=1;j<4;j++){
            // i row j column
            //compare to the front of k columns
            for(int k=1;k<4&&j-k>=0;){
                if(board[i][j-k]!=0&&board[i][j]==board[i][j-k]){
                    board[i][j-k]*=2;
                    board[i][j]=0;
                    j=j-k-1;
                    break;
                }else if(board[i][j-k]==0){
                    k++;
                }else{
                    break;
                }
            }
        }
    }
}
static void moveVertical(){
    for(int i=0;i<4;i++){
        for(int j=1;j<4;j++){
            for(int k=1;k<4&&j-k>=0;){
                if(board[j-k][i]!=0&&board[j][i]==board[j-k][i]){
                    board[j-k][i]*=2;
                    board[j][i]=0;
                    j=j-k-1;
                    break;
                }else if(board[j-k][i]==0){
                    k++;
                }else{
                    break;
                }
            }
        }
    }
}
void moveFront(){
    moveVertical();
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
    moveHorizon();
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
    moveHorizon();
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
    moveVertical();
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
    return board[pos]!=0;
}
int isWin(int pos){
    return board[pos]==2048;
}