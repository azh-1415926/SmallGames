#ifndef _GAME_CONTROL_H_
#define _GAME_CONTROL_H_
#include <stdio.h>
#include <stdbool.h>
#if _WIN32
//#include <windows.h>
#include <conio.h>
#include <windows.h>
#elif __linux__
#include <unistd.h>
#endif
#define MOVE_FRONT 0
#define MOVE_LEFT 1
#define MOVE_BEHIND 2
#define MOVE_RIGHT 3
void initalizeGame(int rows,int columns);
bool moveIsInvaild(int flag);
int movePoint(int pos,int flag);
int getUserControl();
#endif /* _GAME_CONTROL_H_ */
