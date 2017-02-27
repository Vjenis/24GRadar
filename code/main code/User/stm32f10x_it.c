/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "bsp_led.h"
#include "bsp_exti.h"
#include "bsp_lcd.h"
#include <stdio.h>
#include "stm_flash.h"
#include "string.h"
#include "BGT24MTR12.h"
#include "bsp_adf4158.h"

//#define FLASH_SAVE_ADDR  0X08070000		              //设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)
//uint8_t TEMP_Buffer[]="";  												//要写入到STM32 FLASH的字符串数组
uint8_t Key1Down_Count = '8';
//#define SIZE sizeof(TEMP_Buffer)		                //数组长度

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

// EXTI Line --> PE4
void macXPT2046_EXTI_INT_FUNCTION ( void )
{ 
  if ( EXTI_GetITStatus ( macXPT2046_EXTI_LINE ) != RESET )
  {	
    ucXPT2046_TouchFlag = 1;
		
    EXTI_ClearITPendingBit ( macXPT2046_EXTI_LINE );
		
  }
	
}

void macEXTI1_INT_FUNCTION (void)
{
	//uint8_t datatemp [ SIZE ];
	
	if(EXTI_GetITStatus(macEXTI1_LINE) != RESET) //确保是否产生了EXTI Line中断
	{
		// LED1 取反
		LED1_TOGGLE;
		
		if(Key1Down_Count >= '7')
		{
			Key1Down_Count = '0' ;
		}
		else
			Key1Down_Count++;

		ILI9341_Display_Num ( 180, 10, Key1Down_Count, macBACKGROUND, macRED );
		
		EXTI_ClearITPendingBit(macEXTI1_LINE);     //清除中断标志位
	}  
	
}

void macEXTI2_INT_FUNCTION (void)
{
	//uint8_t datatemp [ SIZE ];
	
	if(EXTI_GetITStatus(macEXTI2_LINE) != RESET) //确保是否产生了EXTI Line中断
	{
		// LED2 取反
		LED2_TOGGLE;
		
		EXTI_ClearITPendingBit(macEXTI2_LINE);     //清除中断标志位
	}  
	
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
