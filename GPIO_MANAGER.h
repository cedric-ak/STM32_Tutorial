#ifndef _GPIO_MANAGER
#define _GPIO_MANAGER
#include "_definition.h"

#define OUTPUT_GP_PUSH_PULL   ((uint32_t) 0x00)
#define OUTPUT_GP_OPEN_DRAIN  ((uint32_t) 0x01)
#define OUTPUT_ALT_PUSH_PULL  ((uint32_t) 0x02)
#define OUTPUT_ALT_OPEN_DRAIN ((uint32_t) 0x03)

#define INPUT_PULL_UP    ((uint32_t) 0x02)
#define INPUT_ANAL       ((uint32_t) 0x00)
#define INPUT_FLOATING   ((uint32_t) 0x01)

#define OUTPUT_50_MZ     ((uint32_t) 0x03)
#define OUTPUT_10_MZ     ((uint32_t) 0x01)
#define OUTPUT_2_MZ      ((uint32_t) 0x02)

#define CLK_EN_GPIOA RCC->APB2ENR |=(1<<2)
#define CLK_EN_GPIOB RCC->APB2ENR |=(1<<3)
#define CLK_EN_GPIOC RCC->APB2ENR |=(1<<4)


typedef union {
	
	struct{
		uint32_t PC15 		:4;
		uint32_t PC14 		:4;
		uint32_t PC13 		:4;
	};
	
} portc_t;

portc_t PORTCbits;

typedef union {
	
	struct{
		uint32_t PA12 	:4;
		uint32_t PA11 	:4;
		uint32_t PA10		:4;
		uint32_t PA9 		:4;
		uint32_t PA8 		:4;
		uint32_t PA7 		:4;
		uint32_t PA6 		:4;
		uint32_t PA5 		:4;
		uint32_t PA4 		:4;
		uint32_t PA3 		:4;
		uint32_t PA2 		:4;
		uint32_t PA1 		:4;
		uint32_t PA0 		:4;
		
	};
	
} porta_t;

porta_t PORTAbits;


typedef union {
	
	struct{
		
		uint32_t PB15 	:4;
		uint32_t PB14 	:4;
		uint32_t PB13 	:4;
		uint32_t PB12		:4;
		uint32_t PB9 		:4;
		uint32_t PB8 		:4;
		uint32_t PB7 		:4;
		uint32_t PB6 		:4;
		uint32_t PB5 		:4;
		uint32_t PB4 		:4;
		uint32_t PB3 		:4;
		uint32_t PB2 		:4;
		uint32_t PB1 		:4;
		uint32_t PB0 		:4;
		
	};
	
} portb_t;

portb_t PORTBbits;


#endif

