#include "ComputerPlayer.h"
static bool(*_judgeInvalid)(int)=NULL;
void setJudgeFunc(bool(*judge)(int)){
    _judgeInvalid=judge;
}

int getOptionFromAI(){
    int option=-1;
    // if(playerOption!=-1){
    //     int row=playerOption/3;
    //     int column=playerOption%3;
    //     for(int i=1;i<3;++i){
    //         if(!_judgeInvalid((row+i)%3*3+column)){
    //             option=(row+i+1)%3*3+column;
    //             if(i==2){
    //                 option=(row+i+2)%3*3+column;
    //             }
    //             break;
    //         }
    //         if(!_judgeInvalid(row*3+(column+i)%3)){
    //             option=row*3+(column+i+1)%3;
    //             if(i==2){
    //                 option=row*3+(column+i+2)%3;
    //             }
    //             break;
    //         }
    //     }
    //     for(int i=1;i<3&&(row==column);++i){
    //         if(!_judgeInvalid((row+i)%3*3+(column+i)%3)){
    //             option=(row+i+1)%3*3+(column+i+1)%3;
    //             if(i==2){
    //                 option=(row+i+2)%3*3+(column+i+2)%3;
    //             }
    //             break;
    //         }
    //     }
    //     for(int i=1;i<3&&((row+column)==2);++i){
    //         if(!_judgeInvalid((row+i)%3*3+(column+2*i)%3)){
    //             option=(row+i+1)%3*3+(column+2*(i+1))%3;
    //             if(i==2){
    //                 option=(row+i+2)%3*3+(column+2*(i+2))%3;
    //             }
    //             break;
    //         }
    //     }
    //     playerOption=-1;
    // }else if(playerOption==-1&&!_judgeInvalid(4)){
    //     option=4;
    // }else if(playerOption==-1&&_judgeInvalid(4)){
    //     option=(rand()%2)?(4+(rand()%2+1)*2):(4-(rand()%2+1)*2);
    //     if(_judgeInvalid(0)&&_judgeInvalid(2)&&_judgeInvalid(6)&&_judgeInvalid(8)){
    //         option=rand()%9;
    //     }
    // }
    return option;
}