#pragma once
#include <stdio.h>

typedef unsigned long 		uint32;
typedef unsigned long long 	uint64;

//REG ENABLE CLOCK
#define RCC_AHB1_ENABLE_REG	(uint32*)  	0x40023830

//REG ENABLE IN/OUT
#define GPIOA_MODE_REG		(uint32*)  	0x40020000
#define GPIOB_MODE_REG		(uint32*)	0x40020400

#define RCC_AHB1_GPIOA_CLOCK	0 //номер біту для ініц.тактування порта A
#define RCC_AHB1_GPIOB_CLOCK	1 //номер біту для ініц.тактування порта B


//reg output and input
#define GPIOA_IN_DATA_REG 	(uint32*)	0x40020010  //input register A

#define GPIOB_OUT_DATA_REG	(uint32*)	0x40020414	//output register B

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


//functions
#define GPIOx_SET_MODE_OUTPUT(port, pin) \
        do { \
		*GPIO##port##_MODE_REG |= (1 << (pin * 2)); \
		*GPIO##port##_MODE_REG &= ~(1 << (pin * 2 + 1)); \
        } while(0)
		
#define GPIOx_SET_MODE_INPUT(port1, pin1) \
        do { \
		*GPIO##port1##_MODE_REG &= ~(1 << (pin1 * 2)); \
		*GPIO##port1##_MODE_REG &= ~(1 << (pin1 * 2 + 1)); \
        } while(0)


int ButtonPress (const int but, int *but_flag);
int ButtonReleased (const int but, int *but_flag);
void delay (long sec);
void fixNumber(int *num);
void switchNum(int num);
void debugLed(long sec);