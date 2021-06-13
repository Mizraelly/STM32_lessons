#include "stm32f4xx.h"

//constants
#define ZERO 63
#define ONE	6
#define TWO	91
#define THREE 79
#define FOUR 102
#define FIVE 109
#define SIX 125
#define SEVEN 7
#define EIGHT 127
#define NINE 111

int ButtonPress (const int but, int *but_flag);
int ButtonReleased (const int but, int *but_flag);
void delay (long sec);
void fixNumber(int *num);
void switchNum(int num);
void debugLed(long sec);
