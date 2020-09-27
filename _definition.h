#ifndef _DEFINITION
#define _DEFINITION

#include <stm32f10x.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void delay(uint32_t timeMs);
void Blink(int timeDelay);
void Init(void);
bool btnPressed(void);
void externalInterrupt_int(void);
void uart_int(void);
void uart_Write_Text(char* txData);
void uart_Write(char txData);
void *itoa(uint64_t iData);
void *ftoa(float fData);

bool uartInt_status;
bool exti_status;

typedef enum{
	ledBlink,
	buttonControl,
	adc,
	i2c,
	spi,
	uart,
	pwm,
	timer,
	interrupt,
	exterInt,
	rtc,
	dma,
	bootLoader
}app_t;

typedef struct{
	app_t state;
}application;

application tutorial;

#endif

