#ifndef HAL_GPIO
#define HAL_GPIO

#include"stm32f10x.h"

#define HIGH 1
#define LOW  0

#define PORTA GPIOA
#define PORTB GPIOB
#define PORTC GPIOC

//pin mode
#define INPUT_MODE ((uint32_t)0x00) //Input mode reset state
#define OUTPUT_MODE ((uint32_t)0x01) //Output mode, max speed 10 MHz.

//output pin configuration
#define OUTPUT_MODE_CONF_PP ((uint32_t)0x00) //General purpose output push-pull
#define OUTPUT_MODE_CONF_OD ((uint32_t)0x01) //General purpose output Open-drain
#define OUTPUT_MODE_CONF_AF_PP ((uint32_t)0x10) //Alternate function output Push-pull
#define OUTPUT_MODE_CONF_AF_OD ((uint32_t)0x11) //Alternate function output Open-drain

//input pin conf
#define INPUT_MODE_CONF_AN ((uint32_t)0x00) // Analog mode
#define INPUT_MODE_CONF_FI ((uint32_t) 0x01) //Floating input (reset state)
#define INPUT_MODE_CONF_PU_PD ((uint32_t)0x10) //Input with pull-up / pull-down

//Speed/Slew rate for output
#define OUTPUT_MODE_10MHZ ((uint32_t)0x01) //Output mode, max speed 10 MHz.
#define OUTPUT_MODE_2MHZ ((uint32_t)0x10) //Output mode, max speed 2 MHz.
#define OUTPUT_MODE_50MHZ ((uint32_t)0x11)// Output mode, max speed 50 MHz.

//Clock enable
#define RCC_APB2_PORTC_CLK_EN (RCC->APB2ENR |= (uint32_t)0x01<<4) //IO port C clock enabled 
#define RCC_APB2_PORTB_CLK_EN (RCC->APB2ENR |= (uint32_t)0x01<<3) //IO port B clock enabled 
#define RCC_APB2_PORTA_CLK_EN (RCC->APB2ENR |= (uint32_t)0x01<<2) //IO port A clock enabled 
#define RCC_APB2_AF_CLK_EN 		(RCC->APB2ENR |= (uint32_t)0x01<<0) //Alternate Function IO clock enabled 

//For postion for conf
#define CONF_BIT1_POS (pinpos[pinNum]+2)//CONF_BIT1_POS(pinnum)
#define CONF_BIT2_POS (pinpos[pinNum]+3)//CONF_BIT2_POS(pinnum)



//For Set and disable bit
//#define BIT_SET   ((uint32_t)0x01<<pinNum) //BIT_SET(pinNum)   ((uint32_t)0x01<<pinNum)
//#define BIT_RESET ((uint32_t)0x01<<(pinNum+16)) //BIT_RESET(pinNum) ((uint32_t)0x01<<(pinNum+16))

////////////////////my External configure Interupt register
#define EXT_CONF_REG_PA0_3 (AFIO->EXTICR[0] &=~(0xFU<<4*pinNum)) 
#define EXT_CONF_REG_PB0_3 (AFIO->EXTICR[0] |= (0x1U<<4*pinNum)) 
#define EXT_CONF_REG_PC0_3 (AFIO->EXTICR[0] |= (0x2U<<4*pinNum)) 


#define EXT_CONF_REG_PA4_7 (AFIO->EXTICR[1] &=~(0xFU<<4*pinNum)) 
#define EXT_CONF_REG_PB4_7 (AFIO->EXTICR[1] |= (0x1U<<4*pinNum)) 
#define EXT_CONF_REG_PC4_7 (AFIO->EXTICR[1] |= (0x2U<<4*pinNum)) 


#define EXT_CONF_REG_PA8_11 (AFIO->EXTICR[2] &=~(0xFU<<4*pinNum)) 
#define EXT_CONF_REG_PB8_11 (AFIO->EXTICR[2] |= (0x1U<<4*pinNum)) 
#define EXT_CONF_REG_PC8_11 (AFIO->EXTICR[2] |= (0x2U<<4*pinNum)) 

#define EXT_CONF_REG_PA12_15 (AFIO->EXTICR[3] &=~(0xFU<<4*pinNum)) 
#define EXT_CONF_REG_PB12_15 (AFIO->EXTICR[3] |= (0x1U<<4*pinNum)) 
#define EXT_CONF_REG_PC12_15 (AFIO->EXTICR[3] |= (0x2U<<4*pinNum)) 


//Intereut mask register for pin
#define EXT_INT_PIN_EN (EXTI->IMR |= ((uint32_t)0x1<<pinNum))
//Rising tigger selection register
#define RISE_TIG_PIN_EN (EXTI->RTSR |= ((uint32_t)0x1<<pinNum))
//Falling edge selection regidter 
#define FALL_TIG_PIN_EN (EXTI->FTSR |= ((uint32_t)0x1<<pinNum))

//External Software interupt event register
#define EXT_INT_SW_HAN_REG (EXTI->SWIER |=((uint32_t)0x1<<pinNum))
//External Interupt pending register
#define EXT_INT_PEND_REG (EXTI->PR |=((uint32_t)0x1<<pinNum))
/////////////////////////////




typedef struct{
	//GPIO_TypeDef *Init;
	
	GPIO_TypeDef *port;
	uint32_t pin;
	uint32_t mode;
	uint32_t mode_type;
	uint32_t conf;
	uint32_t speed;
	uint32_t Alternate;
	
}GPIO_TYPE;

typedef enum{
	RISING_EDGE,
	FALLING_EDGE,
	RISING_FALLING_EDGE
}edge_type;

typedef enum{
	PORT_A,
	PORT_B,
	PORT_C
}port_type;

/////// GPIO Configuration pin
static void conf_pin(GPIO_TypeDef *GPIOx, uint32_t pinNum, uint32_t mode_type);
static void conf_pin_speed(GPIO_TypeDef *GPIOx, uint32_t pinNum, uint32_t pinSpeed, uint32_t mode);
////// GPIO USER PIN CONFIGURATION
void gpio_write(GPIO_TypeDef *GPIOx, uint32_t pinNum, uint8_t state);
void gpio_toggle(GPIO_TypeDef *GPIOx, uint32_t pinNum);
//////Delat
void delay(uint32_t delay);
//clock enable and configure
void gpioInit(GPIO_TYPE gpio);
/////gpio Interupt configure
void configure_gpio_intereupt(GPIO_TypeDef *GPIOx, uint32_t pinNum, edge_type edges);
void enable_irqnum(uint32_t pinNum, IRQn_Type IRQn);
void gpio_clear_intereupt(uint32_t pinNum);
void gpio_conf_sw_intereput(uint32_t pinNum);
//IRQ Handler prototype
void EXTI0_IRQHandler(void);
#endif

