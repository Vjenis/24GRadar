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
//#include "bsp_clkconfig.h"

extern uint8_t Key1Down_Count;
uint8_t Buffer[] = "1105";

#define CLI()      __set_PRIMASK(1)		/* 关闭总中断 */  
#define SEI() __set_PRIMASK(0)				/* 开放总中断 */ 

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */ 
int main(void)
{	
//	uint8_t i;
	
//	HSE_SetSysClock(RCC_PLLMul_9);
	
	LED_GPIO_Config();
	LED1_ON;
	LED2_ON;
	
	LCD_Init ();         					//LCD 初始化
	ILI9341_GramScan ( 1 );
	ILI9341_Clear ( 0, 0, 240, 320, macBACKGROUND);
	
	SPI_BGT24MTR12_Init();    		//初始化BGT24MTR12
	
	ADF4158_Init();
	
	CLI();
	SEI();	
	/* exti line config */
	EXTI1_Pxy_Config(); 
//	EXTI2_Pxy_Config();
	
	ILI9341_DispString_EN ( 0, 10, "BGT Power Select", macBACKGROUND, macRED );
	
//	for(i=7;i>0;i--)
//		WriteToADF4158(ADF4158Registers,i);
	
	/* wait interrupt */
	while(1)                            
	{
		SPI_BGT24MTR12_Write(Key1Down_Count);
//		SPI_BGT_ByteWrite(Buffer,4);
//		SPI_BGT_ByteWrite(0x0007);
//		switch(Key2Down_Count)
//		{
//			case '0':WriteToADF4158(ADF4158Registers,0);break;
//			case '1':WriteToADF4158(ADF4158Registers,1);break;
//			case '2':WriteToADF4158(ADF4158Registers,2);break;
//			case '3':WriteToADF4158(ADF4158Registers,3);break;
//			case '4':WriteToADF4158(ADF4158Registers,4);break;
//			case '5':WriteToADF4158(ADF4158Registers,5);break;
//			case '6':WriteToADF4158(ADF4158Registers,6);break;
//			case '7':WriteToADF4158(ADF4158Registers,7);break;
//			default:WriteToADF4158(ADF4158Registers,0);break;
//		}		

	}
}
/*********************************************END OF FILE**********************/
