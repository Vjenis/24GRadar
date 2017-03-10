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



extern uint8_t Key1Down_Count;
uint8_t Buffer[] = "00000001";
extern  uint32_t ADF4158Registers[8];
uint16_t ADF4158Read_1[8];
uint16_t ADF4158Read_2[8];
uint16_t ADF4158Read_3[8];
unsigned long int test;

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
//	uint8_t j=0;
	
	
	/* 配置串口1为：115200 8-N-1 */
//	USARTx_Config();
	
	LED_GPIO_Config();
	LED1_ON;
	LED2_ON;
	
	LCD_Init ();         					//LCD 初始化
	ILI9341_GramScan ( 1 );
	ILI9341_Clear ( 0, 0, 240, 320, macBACKGROUND);
	
	SPI_BGT24MTR12_Init();    		//初始化BGT24MTR12
	
	ADF4158_GPIO_Config();
//	for(i=7;i>0;i--)
//	{
//		if(i==5)
//		{
//			WriteToADF4158(ADF4158Registers,i);
//			ADF4158Registers[5]=0x00800005;
//			WriteToADF4158(ADF4158Registers,i);
//		}
//		else if(i==6)
//		{
//			WriteToADF4158(ADF4158Registers,i);
//			ADF4158Registers[6]=0x00800006;
//			WriteToADF4158(ADF4158Registers,i);
//		}
//		else
//			WriteToADF4158(ADF4158Registers,i);
//	}
//		//test4 adf4158	
//	ADF4158Registers[0]=0xf84b0000;
//	ADF4158Registers[1]=0x00000001;
//	ADF4158Registers[2]=0x00008f2a;		
//	ADF4158Registers[3]=0x00000443;
//	ADF4158Registers[4]=0x00480104;
//	ADF4158Registers[5]=0x00000005;
//	ADF4158Registers[6]=0x00000006;
//	ADF4158Registers[7]=0x00000007;
	
//	ADF4158Registers[7]=0x00000007;
//	ADF4158Registers[6]=0x00000006;
//	ADF4158Registers[5]=0x04000005;
//	ADF4158Registers[4]=0x00580104;
//	ADF4158Registers[3]=0x00000043;
//	ADF4158Registers[2]=0x0000800A;	
//	ADF4158Registers[1]=0x00000001;
//	ADF4158Registers[0]=0x784B0000;
//	for(i=7;i>0;i--)
		//WriteToADF4158(ADF4158Registers,i);
	
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
		
//			Usart_SendStr_length( macUSARTx, ADF4158Read_1, 16 );
//			printf("\r\n 读出的数据为：%s \r\n", ADF4158Read_1);
		for(i=7;i>0;i--)
		{
			WriteToADF4158(ADF4158Registers,i);
			WriteToADF4158(ADF4158Registers,0);
		}
		ADF4158Registers[5]=0x00800005;
		ADF4158Registers[6]=0x00800006;
		WriteToADF4158(ADF4158Registers,6);
		WriteToADF4158(ADF4158Registers,0);
		WriteToADF4158(ADF4158Registers,5);
		WriteToADF4158(ADF4158Registers,0);
//		if(j!=1)
//		{
//			WriteToADF4158(ADF4158Registers,0);
//			j++;
//		}
//			else
//				WriteToADF4158(ADF4158Registers,4);
			
//			test=ReadToADF4158_16bit();
//			i++;
//			if(i>7)
//				i=0;
//			WriteToADF4158(ADF4158Registers,4);
			
	}
}
/*********************************************END OF FILE**********************/
