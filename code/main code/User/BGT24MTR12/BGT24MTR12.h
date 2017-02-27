#ifndef __BGT24MTR12_H
#define __BGT24MTR12_H



#include "stm32f10x.h"



/************************** SPI BGT24MTR12 连接引脚定义********************************/
#define      macSPI1                                     	SPI1
#define      macSPI1_APBxClock_FUN                        RCC_APB2PeriphClockCmd
#define      macSPI1_CLK                                  RCC_APB2Periph_SPI1

#define      macSPI1_CS_APBxClock_FUN                     RCC_APB2PeriphClockCmd
#define      macSPI1_CS_CLK                               RCC_APB2Periph_GPIOB    
#define      macSPI1_CS_PORT                              GPIOB
#define      macSPI1_CS_PIN                               GPIO_Pin_8

#define      macSPI1_SCK_APBxClock_FUN                    RCC_APB2PeriphClockCmd
#define      macSPI1_SCK_CLK                              RCC_APB2Periph_GPIOA   
#define      macSPI1_SCK_PORT                             GPIOA   
#define      macSPI1_SCK_PIN                              GPIO_Pin_5

#define      macSPI1_MISO_APBxClock_FUN                   RCC_APB2PeriphClockCmd
#define      macSPI1_MISO_CLK                             RCC_APB2Periph_GPIOA    
#define      macSPI1_MISO_PORT                            GPIOA 
#define      macSPI1_MISO_PIN                             GPIO_Pin_6

#define      macSPI1_MOSI_APBxClock_FUN                   RCC_APB2PeriphClockCmd
#define      macSPI1_MOSI_CLK                             RCC_APB2Periph_GPIOA    
#define      macSPI1_MOSI_PORT                            GPIOA 
#define      macSPI1_MOSI_PIN                             GPIO_Pin_7



/************************** SPI Flash 函数宏定义********************************/
#define      macSPI_BGT24MTR12_CS_ENABLE()                       GPIO_ResetBits( macSPI1_CS_PORT, macSPI1_CS_PIN )
#define      macSPI_BGT24MTR12_CS_DISABLE()                      GPIO_SetBits( macSPI1_CS_PORT, macSPI1_CS_PIN )



void SPI_BGT24MTR12_Init(void);
void SPI_BGT24MTR12_Write(u16 count);
u16 SPI_BGT24MTR12_SendByte(u16 byte);
//void SPI_BGT_ByteWrite(u8* pBuffer, u16 ByteWrite);
//void SPI_BGT_ByteWrite(u16 ByteWrite);
u8 SPI_BGT2_SendByte(u8 byte);

#endif /* __BGT24MTR12_H */

