#include "stm32f10x.h"
#include "HAL_GPIO.h"


int main()
{
	// Enablbe APB2 clock by left shift by four//
	RCC->APB2ENR |= 0x1U<<4;
	//Configure pin portc  //
	GPIOC->CRH |= (~(0x1U<<21) | 0x1U<<20);	//Output mode, max speed 10 MHz.
	GPIOC->CRH &= (~(0x3U<<22)); 
	while(1)
	{
		//set bit 13
		GPIOC->BSRR = (0x1U<<13);
		delay((uint32_t)128);
		GPIOC->BSRR = (0x1U<<(13+16));
		delay((uint32_t)128);
	}
}
int main()
{
	GPIO_TYPE gpio;
	gpio.port = PORTC;
	//gpio.Init = GPIOC;
	//gpio.Alternate = OUTPUT_MODE_CONF_AF_PP;
	//gpio.conf = OUTPUT_MODE_CONF_PP;
	gpio.mode = OUTPUT_MODE;
	gpio.mode_type = OUTPUT_MODE_CONF_PP;
	gpio.speed = OUTPUT_MODE_10MHZ;
	gpio.pin = 13;
	
	gpioInit(gpio);
  //configure_gpio_intereupt(PORTA,0,RISING_EDGE);
	//enable_irqnum(0,EXTI0_IRQn);
	//gpio_conf_sw_intereput(0);
	
  while(1)
	{
		gpio_toggle(PORTC,13);
		for(int i=0; i<1000;i++);
		//gpio_write(PORTC,13,HIGH);
		delay(100);
	}
	return 0;
}

/*void EXTI0_IRQHandler(void)
{
	gpio_clear_intereupt(0);
	gpio_write(PORTC,13,HIGH);
}*/
