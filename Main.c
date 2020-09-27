#include "GPIO_MANAGER.h"
#define EXTERNAL_INTER

int t_Delay = 0;
uint32_t data[100];
uint64_t x;
float y;
char X[10];
void EXTI15_10_IRQHandler(){
	if(EXTI->PR &(EXTI_PR_PR10)){         //if interrupt occure on pin 10
		delay(10);
		if(EXTI->PR &(EXTI_PR_PR10)){	
		EXTI->PR |=EXTI_PR_PR10;            //clear interrupt flag
		t_Delay +=200;
		}
		
	}
}

int main(){
	
//	Init();
	tutorial.state =  uart;
	
	while(true){

		switch(tutorial.state){
			case ledBlink:
				Blink(500);
				break;
			
			case buttonControl:
				
				if(btnPressed()){
					tutorial.state = exterInt;          //blink led if button pressed (move led blink state) 
				}else{
					GPIOC->BSRR |= GPIO_BSRR_BS13;      //if button not pressed led off
				}
				
				break;
			
			case adc:
				break;
			
			case i2c:
				break;
			
			case spi:
				break;
			
			case uart:
				if(!uartInt_status){
					uart_int();
				}
				y+=10.3;
				uart_Write_Text("Value of X is:");
//				uart_Write_Text(itoa(x));
				uart_Write_Text(ftoa(y));
				uart_Write_Text("\r");
			  delay(250);
				break;
			
			case pwm:
				break;
			
			case interrupt:
	      if(!exti_status){
					externalInterrupt_int();
				}
				break;
			
			case exterInt:
				Blink(t_Delay);
				break;
			
			case rtc:
				break;
			
		}

	}
}

void delay(uint32_t timeMs){
	for(volatile int cnt = 0; cnt <=5000 * timeMs; cnt++);
}

void Blink(int timeDelay){
	
	GPIOC->BSRR |= GPIO_BSRR_BS13;
	delay(timeDelay);
	GPIOC->BSRR |= GPIO_BSRR_BR13;
	delay(timeDelay);

}

bool btnPressed(void){
	if(GPIOA ->IDR &(GPIO_IDR_IDR9)){  //check if button is pressed
	 return true;
	}
	return false;
}
	

void Init(void){  
	/*Port initialize*/
	RCC ->APB2ENR |= RCC_APB2ENR_IOPAEN;  //enable port A clock
	RCC ->APB2ENR |= RCC_APB2ENR_IOPCEN;  //enable port C clock
	  
	GPIOC ->CRH |= GPIO_CRH_MODE13;       //Output mode, max speed 50 MHz. PC13       Led
	GPIOC->CRH  &=~ GPIO_CRH_CNF13;       //general purpose output push pull
	
	GPIOA ->CRH &=~ GPIO_CRH_MODE9;       //input mode    A9 
	GPIOA ->CRH &=~ GPIO_CRH_CNF9_0;      //Floating input (reset state)
	GPIOA ->CRH |=  GPIO_CRH_CNF9_1; 

}

void externalInterrupt_int(void){
//	GPIOA ->CRH &=~ GPIO_CRH_MODE10;       //input mode    A8 
//  GPIOA ->CRH &=~ GPIO_CRH_CNF10_1;      //Floating input (reset state)
//	GPIOA ->CRH |=  GPIO_CRH_CNF10_0; 
	
	/*Enable AFIO clock*/
//	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; 
	/*Config AFIO Register for PA9 external interrupt*/
//	AFIO->EXTICR[3] =  AFIO_EXTICR3_EXTI10_PA;
	/*Config EXTIx register*/
	EXTI->IMR |=  EXTI_IMR_MR10;            //external Interrupt on pin A10
	EXTI->RTSR|=  EXTI_RTSR_TR10;           //Interrupt rising edge
	NVIC_EnableIRQ(EXTI15_10_IRQn);         //enable interrupt vector
	NVIC_SetPriority(EXTI15_10_IRQn,0);     //set priority
	exti_status = true;
}

void uart_int(void){

  RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPBEN |RCC_APB2ENR_AFIOEN; //enable UART clock and GPIOB clock, Alternate Function I/O clock enabled  									   
  AFIO->MAPR |= AFIO_MAPR_USART1_REMAP;	                     										 //map UART1 pin to TX/PB6, RX/PB7 
	GPIOB->CRL |= GPIO_CRL_MODE6 | GPIO_CRL_CNF6_1;                                //Output mode, max speed 50 MHz. PB6 Tx line
	GPIOB->CRL  &=~ GPIO_CRL_CNF6_0;                                               //general purpose output push pull
  USART1->BRR = 0x1D4C;  								                                         //baud rate 9600
	USART1->CR1 |= USART_CR1_TE |USART_CR1_RE |USART_CR1_SBK |USART_CR1_UE;        //Transmitter enable, Receiver enable, Send break, enable USART 1
	uartInt_status = true;
}

uint8_t uart_Read(void){
	while(!(USART1->SR & USART_SR_RXNE));  //wait for data recieve
	return USART1->DR;
}

void uart_Write(char txData){ 
  USART1->DR = txData;
	while(!(USART1->SR & USART_SR_TC));    //wait for transmittion to complete
}

void uart_Write_Text(char* txData){ 
   for(int i = 0; txData[i] != '\0'; i++){
		uart_Write(txData[i]);
	}
}	
 
void *itoa(uint64_t iData){ //convert integer to character
  char buf[10]; 
	sprintf(buf, "%.3d", iData);
  return buf;		
}

void *ftoa(float fData){   //convert float to character
	char buf[10]; 
	sprintf(buf, "%.3lf", fData);
  return buf;
}




