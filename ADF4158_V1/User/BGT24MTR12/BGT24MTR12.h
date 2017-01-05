#ifndef __BGT24MTR12_H
#define __BGT24MTR12_H



#include "stm32f10x.h"



/************************** SPI BGT24MTR12 连接引脚定义********************************/
#define      macSPIx                                     SPI1
#define      macSPI_APBxClock_FUN                        RCC_APB2PeriphClockCmd
#define      macSPI_CLK                                  RCC_APB2Periph_SPI1

#define      macSPI_CS_APBxClock_FUN                     RCC_APB2PeriphClockCmd
#define      macSPI_CS_CLK                               RCC_APB2Periph_GPIOC    
#define      macSPI_CS_PORT                              GPIOB
#define      macSPI_CS_PIN                               GPIO_Pin_8

#define      macSPI_SCK_APBxClock_FUN                    RCC_APB2PeriphClockCmd
#define      macSPI_SCK_CLK                              RCC_APB2Periph_GPIOA   
#define      macSPI_SCK_PORT                             GPIOA   
#define      macSPI_SCK_PIN                              GPIO_Pin_5

#define      macSPI_MISO_APBxClock_FUN                   RCC_APB2PeriphClockCmd
#define      macSPI_MISO_CLK                             RCC_APB2Periph_GPIOA    
#define      macSPI_MISO_PORT                            GPIOA 
#define      macSPI_MISO_PIN                             GPIO_Pin_6

#define      macSPI_MOSI_APBxClock_FUN                   RCC_APB2PeriphClockCmd
#define      macSPI_MOSI_CLK                             RCC_APB2Periph_GPIOA    
#define      macSPI_MOSI_PORT                            GPIOA 
#define      macSPI_MOSI_PIN                             GPIO_Pin_7



/************************** SPI Flash 函数宏定义********************************/
#define      macSPI_BGT24MTR12_CS_ENABLE()                       GPIO_ResetBits( macSPI_CS_PORT, macSPI_CS_PIN )
#define      macSPI_BGT24MTR12_CS_DISABLE()                      GPIO_SetBits( macSPI_CS_PORT, macSPI_CS_PIN )



void SPI_BGT24MTR12_Init(void);
u16 SPI_BGT24MTR12_Write(u16 count);
u16 SPI_BGT24MTR12_SendByte(u16 byte);

#endif /* __BGT24MTR12_H */

