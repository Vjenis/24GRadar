#ifndef __EXTI_H
#define	__EXTI_H


#include "stm32f10x.h"


/*外部中断EXIT相关宏定义*/
#define             macEXTI1_GPIO_CLK                        (RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO)     
#define             macEXTI1_GPIO_PORT                       GPIOA   
#define             macEXTI1_GPIO_PIN                        GPIO_Pin_0
#define             macEXTI1_SOURCE_PORT                     GPIO_PortSourceGPIOA
#define             macEXTI1_SOURCE_PIN                      GPIO_PinSource0
#define             macEXTI1_LINE                            EXTI_Line0
#define             macEXTI1_IRQ                             EXTI0_IRQn
#define             macEXTI1_INT_FUNCTION                    EXTI0_IRQHandler

#define             macEXTI2_GPIO_CLK                        (RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO)     
#define             macEXTI2_GPIO_PORT                       GPIOC   
#define             macEXTI2_GPIO_PIN                        GPIO_Pin_13
#define             macEXTI2_SOURCE_PORT                     GPIO_PortSourceGPIOC
#define             macEXTI2_SOURCE_PIN                      GPIO_PinSource13
#define             macEXTI2_LINE                            EXTI_Line13
#define             macEXTI2_IRQ                             EXTI15_10_IRQn
#define             macEXTI2_INT_FUNCTION                    EXTI15_10_IRQHandler

void EXTI1_Pxy_Config(void);
void EXTI2_Pxy_Config(void);

#endif /* __EXTI_H */
