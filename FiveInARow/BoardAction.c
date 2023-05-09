#include "BoardAction.h"
#include <string.h>
static int chequerCount=0;
static char board[15][15]={0};
static char chequerFiller='-';
void initalizeChessBoard(char filler){
    memset(board,filler,sizeof(board));
}
void showChessBoard(){
    printf("  1   2   3   4   5   6   7   8   9   10  11  12  13  14  15\n");
    printf("*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*\n");
    for(int i=0;i<15;i++){
        for(int j=0;j<15;j++){
            printf("| %c ",board[i][j]);
        }
        printf("| %d\n*---*---*---*---*---*---*---*---*---*---*---*---*---*---*---*\n",i+1);
    }
}
// char getChequer(int pos){
//     // if(pos<0||pos>8)
//     //     return '\0';
//     // return board[pos];
// }
void addChequer(int pos,char chequer){
    board[pos/15][pos%15]=chequer;
    ++chequerCount;
}
bool isInvaild(int pos){
    if(pos<0||pos>=225)
        return true;
    return board[pos/15][pos%15]!=chequerFiller;
}
int isWin(int pos){
    int row=pos/15;
    int column=pos%15;
    int count=1;
    int maxcount=1;
    int flag=1;
    int rflag=1;
    char chequer=board[row][column];
    //horizon
    for(int i=1;i<5;++i){
        if(flag&&column+i<15){
            if(chequer==board[row][column+i]){
                ++count;
            }else{
                count=count-(i-1);
                flag=0;
            }
        }
        if(rflag&&column-i>=0){
            if(chequer==board[row][column-i]){
                ++count;
            }else{
                count=count-(i-1);
                rflag=0;
            }
        }
        if(count>=5||flag==0&&rflag==0){
            break;
        }
    }
    if(count>maxcount){
        maxcount=count;
        return 1;
    }
    count=1;
    flag=1;
    rflag=1;
    //vertical
        for(int i=1;i<5;++i){
        if(flag&&row+i<15){
            if(chequer==board[row+i][column]){
                ++count;
            }else{
                count=count-(i-1);
                flag=0;
            }
        }
        if(rflag&&row-i>=0){
            if(chequer==board[row-i][column]){
                ++count;
            }else{
                count=count-(i-1);
                rflag=0;
            }
        }
        if(count>=5||flag==0&&rflag==0){
            break;
        }
    }
    if(count>maxcount){
        maxcount=count;
        return 1;
    }
    count=1;
    flag=1;
    rflag=1;
    //
    for(int i=1;i<5;++i){
        if(flag&&row+i<15&&column+i<15){
            if(chequer==board[row+i][column+i]){
                ++count;
            }else{
                count=count-(i-1);
                flag=0;
            }
        }
        if(rflag&&row-i>=0&&column-i>=0){
            if(chequer==board[row-i][column-i]){
                ++count;
            }else{
                count=count-(i-1);
                rflag=0;
            }
        }
        if(count>=5||flag==0&&rflag==0){
            break;
        }
    }
    if(count>maxcount){
        maxcount=count;
        return 1;
    }
    count=1;
    flag=1;
    rflag=1;
    //
    for(int i=1;i<5;++i){
        if(flag&&row-i>=0&&column+i<15){
            if(chequer==board[row-i][column+i]){
                ++count;
            }else{
                count=count-(i-1);
                flag=0;
            }
        }
        if(rflag&&row+i<15&&column-i>=0){
            if(chequer==board[row+i][column-i]){
                ++count;
            }else{
                count=count-(i-1);
                rflag=0;
            }
        }
        if(count>=5||flag==0&&rflag==0){
            break;
        }
    }
    if(count>maxcount){
        maxcount=count;
        return 1;
    }
//     maxcount=(maxcount<count)?(count):(maxcount);
//     if(maxcount==3)
//         return 1;
//     if(chequerCount>8)
//         return 0;
    return -1;
}