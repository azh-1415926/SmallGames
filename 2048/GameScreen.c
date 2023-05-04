#include "GameScreen.h"
static int board[4][4]={0};
static int maxNumber=0;
static int zeroCount=16;
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
// static void moveHorizon(){
//     for(int i=0;i<4;i++){
//         //curr columns
//         for(int j=1;j<4;j++){
//             // i row j column
//             //compare to the front of k columns
//             for(int k=1;k<4&&j-k>=0;){
//                 if(board[i][j-k]!=0&&board[i][j]==board[i][j-k]){
//                     board[i][j-k]*=2;
//                     board[i][j]=0;
//                     maxNumber=maxNumber<board[i][j-k]?board[i][j-k]:maxNumber;
//                     j=j-k-1;
//                     break;
//                 }else if(board[i][j-k]==0){
//                     k++;
//                 }else{
//                     break;
//                 }
//             }
//         }
//     }
// }
// static void moveVertical(){
//     for(int i=0;i<4;i++){
//         for(int j=1;j<4;j++){
//             for(int k=1;k<4&&j-k>=0;){
//                 if(board[j-k][i]!=0&&board[j][i]==board[j-k][i]){
//                     board[j-k][i]*=2;
//                     board[j][i]=0;
//                     maxNumber=maxNumber<board[j-k][i]?board[j-k][i]:maxNumber;
//                     j=j-k-1;
//                     break;
//                 }else if(board[j-k][i]==0){
//                     k++;
//                 }else{
//                     break;
//                 }
//             }
//         }
//     }
// }
void moveFront(){
    for(int i=0;i<4;i++){
        for(int j=1;j<4;j++){
            for(int k=1;k<4&&j-k>=0;){
                if(board[j-k][i]!=0&&board[j][i]==board[j-k][i]){
                    board[j-k][i]=0;
                    board[j][i]*=2;
                    maxNumber=maxNumber<board[j-k][i]?board[j-k][i]:maxNumber;
                    k++;
                    //break;
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
    int zero=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(board[i][j]==0){
                zero+=4-i;
                break;
            }
        }
    }
    zeroCount=zero;
}
void moveLeft(){
    for(int i=0;i<4;i++){
        //curr columns
        for(int j=1;j<4;j++){
            // i row j column
            //compare to the front of k columns
            for(int k=1;k<4&&j-k>=0;){
                if(board[i][j-k]!=0&&board[i][j]==board[i][j-k]){
                    board[i][j-k]=0;
                    board[i][j]*=2;
                    maxNumber=maxNumber<board[i][j-k]?board[i][j-k]:maxNumber;
                    k++;
                    //break;
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
    int zero=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(board[i][j]==0){
                zero+=4-j;
                break;
            }
        }
    }
    zeroCount=zero;
}
void moveRight(){
    for(int i=0;i<4;i++){
        for(int j=3;j>=0;j--){
            for(int k=1;k<4&&j+k<4;){
                if(board[i][j+k]!=0&&board[i][j]==board[i][j+k]){
                    board[i][j+k]=0;
                    board[i][j]*=2;
                    maxNumber=maxNumber<board[i][j+k]?board[i][j+k]:maxNumber;
                    k++;
                    //break;
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
    int zero=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(board[i][j]==0){
                zero+=j;
                break;
            }
        }
    }
    zeroCount=zero;
}
void moveBehind(){
    for(int i=0;i<4;i++){
        for(int j=3;j>=0;j--){
            for(int k=1;k<4&&j+k<4;){
                if(board[j+k][i]!=0&&board[j][i]==board[j+k][i]){
                    board[j+k][i]=0;
                    board[j][i]*=2;
                    maxNumber=maxNumber<board[j+k][i]?board[j+k][i]:maxNumber;
                    k++;
                    //break;
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
    int zero=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(board[i][j]==0){
                zero+=i;
                break;
            }
        }
    }
    zeroCount=zero;
}
bool isInvaild(int pos){
    if(pos<0||pos>15)
        return true;
    return board[pos/4][pos%4]!=0;
}
bool isFull(){
    return zeroCount==0;
}
bool isWin(){
    return maxNumber==2048;
}