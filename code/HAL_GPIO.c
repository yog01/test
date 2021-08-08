#include "HAL_GPIO.h"
#include <stdint.h>

//define how much shift to get to pin position
uint32_t pinpos[16] =
{
	0x00, //0 pin
	0x04,
	0x08,
	0x0C,
	0x10,
	0x14,
	0x18,
	0x1C,//7pin
	0x00, //8 pin
	0x04,
	0x08,
	0x0C,
	0x10,
	0x14,
	0x18,
	0x1C//15 pin
};

static void conf_pin(GPIO_TypeDef *GPIOx, uint32_t pinNum, uint32_t mode_type)
{
	if(pinNum<8)//configure lower 8 pin
	{
		switch(mode_type)
		{
			case INPUT_MODE_CONF_AN | OUTPUT_MODE_CONF_PP :
				GPIOx->CRL &= ~(0x01<<CONF_BIT1_POS | 0x01<<CONF_BIT2_POS );
			break;
			case INPUT_MODE_CONF_FI | OUTPUT_MODE_CONF_OD :
				GPIOx->CRL |= (INPUT_MODE_CONF_FI<<CONF_BIT1_POS);
				GPIOx->CRL &= ~(OUTPUT_MODE_CONF_OD<<CONF_BIT2_POS);
			break;
			case INPUT_MODE_CONF_PU_PD | OUTPUT_MODE_CONF_AF_PP :
				GPIOx->CRL |= (INPUT_MODE_CONF_PU_PD<<CONF_BIT1_POS);
			break;
			case OUTPUT_MODE_CONF_AF_OD	:
				GPIOx->CRL |= (OUTPUT_MODE_CONF_AF_OD<<CONF_BIT1_POS);
			break;
			default:
				break;
		}
		
	}
	else//configure higer pin
	{
		switch(mode_type)
		{
			case INPUT_MODE_CONF_AN | OUTPUT_MODE_CONF_PP :
				GPIOx->CRH &= ~(0x01<<CONF_BIT1_POS | 0x01<<CONF_BIT2_POS );
			break;
			case INPUT_MODE_CONF_FI | OUTPUT_MODE_CONF_OD :
				GPIOx->CRH |= (INPUT_MODE_CONF_FI<<CONF_BIT1_POS);
				GPIOx->CRH &= ~(OUTPUT_MODE_CONF_OD<<CONF_BIT2_POS);
			break;
			case INPUT_MODE_CONF_PU_PD | OUTPUT_MODE_CONF_AF_PP :
				GPIOx->CRH |= (INPUT_MODE_CONF_PU_PD<<CONF_BIT1_POS);
			break;
			case OUTPUT_MODE_CONF_AF_OD	:
				GPIOx->CRH |= (OUTPUT_MODE_CONF_AF_OD<<CONF_BIT1_POS);
			break;
			default:
				break;
		}
		
	}
	
}


static void conf_pin_speed(GPIO_TypeDef *GPIOx, uint32_t pinNum, uint32_t pinSpeed, uint32_t mode)
{
	if(pinNum<8)
	{//lower pin mode and speed
		/*switch(mode)
		{
			case INPUT_MODE:
				GPIOx->CRL &= ~(0x3U<<pinpos[pinNum]);
			break;
			case OUTPUT_MODE_10MHZ:
				GPIOx->CRL |= (OUTPUT_MODE_10MHZ<<pinpos[pinNum]);
			break;
			case OUTPUT_MODE_2MHZ:
				GPIOx->CRL &= ~(0x01U<<pinpos[pinNum]);
				GPIOx->CRL |= (0x01U<<MODE_BIT2_POS);
			break;
			case OUTPUT_MODE_50MHZ:
				GPIOx->CRL |= (OUTPUT_MODE_50MHZ<<pinpos[pinNum]);
			break;
			default:
				break;
		}*/
		if(mode == INPUT_MODE)//input mode
		{
			GPIOx->CRL &=~(0x3U<<pinpos[pinNum]);
		}
		else
		{
			GPIOx->CRL |= pinSpeed<<pinpos[pinNum];
		}
	}
	else//higher pin mode and speed
	{
		/*switch(mode)
		{
			case INPUT_MODE :
				GPIOx->CRH &= ~(0x3U<<pinpos[pinNum]);
			break;
			case OUTPUT_MODE_10MHZ:
				GPIOx->CRH |= (OUTPUT_MODE_10MHZ<<pinpos[pinNum]);
			break;
			case OUTPUT_MODE_2MHZ :
				GPIOx->CRH &= ~(0x01U<<pinpos[pinNum]);
				GPIOx->CRH |= (0x01U<<MODE_BIT2_POS);
			break;
			case OUTPUT_MODE_50MHZ:
				GPIOx->CRH |= (OUTPUT_MODE_50MHZ<<pinpos[pinNum]);
			break;
			default:
				break;
		}*/
		if(mode == INPUT_MODE)//input mode
		{
			GPIOx->CRH &=~(0x3U<<pinpos[pinNum]);
		}
		else
		{
			GPIOx->CRH |= pinSpeed<<pinpos[pinNum];
		}
	}
}



void gpio_write(GPIO_TypeDef *GPIOx, uint32_t pinNum, uint8_t state)
{
	if(state == HIGH)
	{
		GPIOx->BSRR = 0x1U<<pinNum; //ATOMIC REGISTER
	}
	else
	{
		GPIOx->BSRR = 0x1U<<(pinNum+16);
	}
}


/*void APB2_clkInit()
{
	RCC->APB2ENR |= RCC_APB2_PORTC_CLK_EN;
}*/
void gpioInit(GPIO_TYPE gpio)
{
	
	if(gpio.port == PORTA)
	{
		RCC_APB2_PORTA_CLK_EN;
	}else if(gpio.port == PORTB)
	{
		RCC_APB2_PORTB_CLK_EN;
	}else if(gpio.port == PORTC)
	{
		RCC_APB2_PORTC_CLK_EN;
	}
	else
	{
		RCC_APB2_AF_CLK_EN;
	}
		
	conf_pin(gpio.port,gpio.pin,gpio.mode_type);
	conf_pin_speed(gpio.port,gpio.pin,gpio.speed,gpio.mode);
	
}

void gpio_toggle(GPIO_TypeDef *GPIOx, uint32_t pinNum)
{
	GPIOx->ODR ^=(0x1U<<pinNum);
}
void delay(uint32_t delay)
{
	uint8_t i=0;
	for(i=0;i<delay;i++);
}
//////my Interupt configuration 
/*void configure_gpio_intereupt(GPIO_TypeDef *GPIOx, uint32_t pinNum, edge_type edges)
{
	//enable alternate function
	RCC->APB2ENR |= RCC_APB2_AF_CLK_EN;
		if(GPIOx == PORTA)
		{
				switch(pinNum)
				{
					case 0:
					case 1:
					case 2:
					case 3:
						EXT_CONF_REG_PA0_3;
					break;
					
					case 4:
					case 5:
					case 6:
					case 7:
						EXT_CONF_REG_PA4_7;
					break;
					
					case 8:
					case 9:
					case 10:
					case 11:
						EXT_CONF_REG_PA8_11;
					break;
					
					case 12:
					case 13:
					case 14:
					case 15:
						EXT_CONF_REG_PA12_15;
					break;
					default:
						break;
				}
		}
		else if (GPIOx == PORTB)
		{
				switch(pinNum)
				{
					case 0:
					case 1:
					case 2:
					case 3:
						EXT_CONF_REG_PB0_3;
					break;
					
					case 4:
					case 5:
					case 6:
					case 7:
						EXT_CONF_REG_PB4_7;
					break;
					
					case 8:
					case 9:
					case 10:
					case 11:
						EXT_CONF_REG_PB8_11;
					break;
					
					case 12:
					case 13:
					case 14:
					case 15:
						EXT_CONF_REG_PB12_15;
					break;
					default:
						break;
				}
				
		}else if(GPIOx == PORTC)
		{
			switch(pinNum)
				{
					case 0:
					case 1:
					case 2:
					case 3:
						EXT_CONF_REG_PC0_3;
					break;
					
					case 4:
					case 5:
					case 6:
					case 7:
						EXT_CONF_REG_PC4_7;
					break;
					
					case 8:
					case 9:
					case 10:
					case 11:
						EXT_CONF_REG_PC8_11;
					break;
					
					case 12:
					case 13:
					case 14:
					case 15:
						EXT_CONF_REG_PC12_15;
					break;
					default:
						break;
				}
		}
		else
		{
			//not a port
		}
		EXT_INT_PIN_EN; // enable and selecting interupt for pin
		if(edges == RISING_EDGE)
		{
			RISE_TIG_PIN_EN; // Intererupt for rising 
		}
		else if(edges == FALLING_EDGE)
		{
			FALL_TIG_PIN_EN;
		}
		else
		{
			EXTI->RTSR |= ((uint32_t)0x1<<pinNum);
			EXTI->FTSR |= ((uint32_t)0x1<<pinNum); // Intererupt for rising or falling edege
		}
}
/////// Interupt*/

void configure_gpio_intereupt(GPIO_TypeDef *GPIOx, uint32_t pinNum, edge_type edges)
{
	
	if(GPIOx == PORTA)
	{
		switch(pinNum)
		{
			case 0:
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PA;
			break;
			case 1:
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PA;
			break;
			case 2:
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PA;
			break;
			case 3:
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PA;
			break;
			case 4:
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PA;
			break;
			case 5:
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PA;
			break;
			case 6:
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PA;
			break;
			case 7:
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PA;
			break;
			case 8:
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PA;
			break;
			case 9:
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PA;
			break;
			case 10:
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PA;
			break;
			case 11:
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PA;
			break;
			case 12:
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PA;
			break;
			case 13:
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PA;
			break;
			case 14:
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PA;
			break;
			case 15:
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PA;
			break;
			default:
				break;
		}
	}else if(GPIOx == PORTB)
	{
		switch(pinNum)
		{
			case 0:
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PB;
			break;
			case 1:
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PB;
			break;
			case 2:
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PB;
			break;
			case 3:
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PB;
			break;
			case 4:
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PB;
			break;
			case 5:
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PB;
			break;
			case 6:
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PB;
			break;
			case 7:
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PB;
			break;
			case 8:
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PB;
			break;
			case 9:
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PB;
			break;
			case 10:
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PB;
			break;
			case 11:
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PB;
			break;
			case 12:
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PB;
			break;
			case 13:
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PB;
			break;
			case 14:
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PB;
			break;
			case 15:
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PB;
			break;
			default:
				break;
		}
	}else if(GPIOx == PORTC)
	{
		switch(pinNum)
		{
			case 0:
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI0_PC;
			break;
			case 1:
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI1_PC;
			break;
			case 2:
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI2_PC;
			break;
			case 3:
				AFIO->EXTICR[0] = AFIO_EXTICR1_EXTI3_PC;
			break;
			case 4:
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI4_PC;
			break;
			case 5:
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI5_PC;
			break;
			case 6:
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI6_PC;
			break;
			case 7:
				AFIO->EXTICR[1] = AFIO_EXTICR2_EXTI7_PC;
			break;
			case 8:
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI8_PC;
			break;
			case 9:
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI9_PC;
			break;
			case 10:
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI10_PC;
			break;
			case 11:
				AFIO->EXTICR[2] = AFIO_EXTICR3_EXTI11_PC;
			break;
			case 12:
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI12_PC;
			break;
			case 13:
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI13_PC;
			break;
			case 14:
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI14_PC;
			break;
			case 15:
				AFIO->EXTICR[3] = AFIO_EXTICR4_EXTI15_PC;
			break;
			default:
				break;
		}
	}
	else
	{
	}
	if(edges == RISING_EDGE)
		{
			RISE_TIG_PIN_EN; // Intererupt for rising 
		}
		else if(edges == FALLING_EDGE)
		{
			FALL_TIG_PIN_EN;
		}
		else
		{
			EXTI->RTSR |= ((uint32_t)0x1<<pinNum);
			EXTI->FTSR |= ((uint32_t)0x1<<pinNum); // Intererupt for rising or falling edege
		}
}
//Enable the NVIC no mapped to EXTI
void enable_irqnum(uint32_t pinNum, IRQn_Type IRQn)
{
	//Enable intereput on maskm register 
	EXT_INT_PIN_EN;
	//Enable the NVIC register
	NVIC_EnableIRQ(IRQn);
}
void gpio_clear_intereupt(uint32_t pinNum)
{
	EXT_INT_PEND_REG;
}
//Enable sw interupt 
void gpio_conf_sw_intereput(uint32_t pinNum)
{
	EXT_INT_SW_HAN_REG;
}
