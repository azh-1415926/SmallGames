#ifndef _GAMECONTROL_H_
#define _GAMECONTROL_H_
#include <stdio.h>
#if _WIN32
#include <conio.h>
#include <windows.h>
#elif __linux__
#include <unistd.h>
#endif
#define MOVE_FRONT 0
#define MOVE_LEFT 1
#define MOVE_BEHIND 2
#define MOVE_RIGHT 3
void moveAction();
int getUserControl();
#endif /* _GAMECONTROL_H_ */
