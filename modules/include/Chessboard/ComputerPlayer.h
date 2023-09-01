#ifndef _COMPUTERPLAYER_H_
#define _COMPUTERPLAYER_H_

#include <stdbool.h>

void initalComputer();
void setJudgeFunc(bool(*judge)(int));
int getOptionFromAI();

#endif /* _COMPUTERPLAYER_H_ */