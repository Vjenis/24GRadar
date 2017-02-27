/**
  ******************************************************************************
  * @file    main.c
  * @author  jianhan
  * @version V1.0
  * @date    2016-xx-xx
  * @brief   24GRadar
  ******************************************************************************
  */ 

#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_exti.h" 
#include "bsp_lcd.h"
#include <stdio.h>
#include "BGT24MTR12.h"
#include "bsp_adf4158.h"
#include "bsp_lcd.h"
#include "bsp_usart1.h"
//#include "bsp_clkconfig.h"

extern uint8_t Key1Down_Count;
uint8_t Buffer[] = "00000001";
extern  uint32_t ADF4158Registers[8];
uint16_t ADF4158Read_1[8];
uint16_t ADF4158Read_2[8];
uint16_t ADF4158Read_3[8];

#define CLI()      __set_PRIMASK(1)		/* 关闭总中断 */  
#define SEI() __set_PRIMASK(0)				/* 开放总中断 */ 

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */ 
int main(void)
{	
	uint8_t i;
	
//	HSE_SetSysClock(RCC_PLLMul_9);
	
	/* 配置串口1为：115200 8-N-1 */
//	USARTx_Config();
	
	LED_GPIO_Config();
	LED1_ON;
	LED2_ON;
	
	LCD_Init ();         					//LCD 初始化
	ILI9341_GramScan ( 1 );
	ILI9341_Clear ( 0, 0, 240, 320, macBACKGROUND);
	
	SPI_BGT24MTR12_Init();    		//初始化BGT24MTR12
	
	ADF4158_Init();
//	ADF4158_GPIO_Config();
	
	CLI();
	SEI();	
	/* exti line config */
	EXTI1_Pxy_Config(); 
	EXTI2_Pxy_Config();
	
	ILI9341_DispString_EN ( 0, 10, "K1:  BGT Power Select", macBACKGROUND, macRED );
//	ILI9341_DispString_EN ( 0, 30, "K2:  ADF4158 Select", macBACKGROUND, macRED );
	
	/* wait interrupt */
	while(1)                            
	{
		SPI_BGT24MTR12_Write(Key1Down_Count);
		
		//test bgt
//		SPI_BGT_ByteWrite(Buffer,4);
//		SPI_BGT_ByteWrite(0x0007);
		
		//test1 adf4158
//		for(i=0;i<7;i++)
//		{
//			WriteToADF4158(ADF4158Registers,i);
//			ReadToADF4158_16bit(ADF4158Read_16bit,i);
//			ReadToADF4158_21bit(ADF4158Read_21bit,i);
//		}
		
		//test2 adf4158
//			SPI_adf4158_ByteWrite(Buffer, 8);
//		SPI_ADF4158_ByteWrite(0x00000001);

		//test3 adf4158
//		SPI_ADF4158_ByteWrite(0x00000007);
//		SPI_ADF4158_ByteWrite(0x00000006);
//		SPI_ADF4158_ByteWrite(0x00000005);
//		SPI_ADF4158_ByteWrite(0x00180104);
//		SPI_ADF4158_ByteWrite(0x00000043);
//		SPI_ADF4158_ByteWrite(0x0000800A);
//		SPI_ADF4158_ByteWrite(0x00000001);
//		SPI_ADF4158_ByteWrite(0x00320000);
		
		//test4 adf4158
		for(i=0;i<8;i++)
		{
			SPI_adf4158_ByteWrite(ADF4158Registers, i);
			SPI_adf4158_ByteRead16bit(ADF4158Read_1, i);
//			Usart_SendStr_length( macUSARTx, ADF4158Read_1, 16 );
//			printf("\r\n 读出的数据为：%s \r\n", ADF4158Read_1);
//			SPI_adf4158_ByteRead16bit(ADF4158Read_2, i);
//			SPI_adf4158_ByteRead16bit(ADF4158Read_3, i);
		}

	}
}
/*********************************************END OF FILE**********************/
