#include <Chessboard/ChessBoard.h>
#include <Chessboard/GameControl.h>
#include <Chessboard/ComputerPlayer.h>

int main(){
    initalChessBoard(8,8,4,'-');
    for(int i=0;i<64;i++){
        addChequer(i,'O');
        if(isWin(i)!=-1){
           break;
        }
    }
    showChessBoard();
    freeChessBoard();
    return 0;
}