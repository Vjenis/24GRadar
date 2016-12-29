/**
  ******************************************************************************
  * @file    bsp_exti.c
  * @author  jianhan
  * @version V1.0
  * @date    2016-xx-xx
  * @brief   I/O���ж�Ӧ��bsp
  ******************************************************************************
  */
  
#include "bsp_exti.h"

 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void NVIC1_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* �����ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = macEXTI1_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

static void NVIC2_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* �����ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = macEXTI2_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @brief  ���� PA0 Ϊ���жϿڣ��������ж����ȼ�
  * @param  ��
  * @retval ��
  */
void EXTI1_Pxy_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/* config the extiline clock and AFIO clock */
	RCC_APB2PeriphClockCmd(macEXTI1_GPIO_CLK,ENABLE);
												
	/* config the NVIC */
	NVIC1_Configuration();

	/* EXTI line gpio config*/	
  GPIO_InitStructure.GPIO_Pin = macEXTI1_GPIO_PIN;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 // ��������
  GPIO_Init(macEXTI1_GPIO_PORT, &GPIO_InitStructure);

	/* EXTI line mode config */
  GPIO_EXTILineConfig(macEXTI1_SOURCE_PORT, macEXTI1_SOURCE_PIN); 
  EXTI_InitStructure.EXTI_Line = macEXTI1_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�������ж�
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}

/**
  * @brief  ���� C13 Ϊ���жϿڣ��������ж����ȼ�
  * @param  ��
  * @retval ��
  */
void EXTI2_Pxy_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/* config the extiline clock and AFIO clock */
	RCC_APB2PeriphClockCmd(macEXTI2_GPIO_CLK,ENABLE);
												
	/* config the NVIC */
	NVIC2_Configuration();

	/* EXTI line gpio config*/	
  GPIO_InitStructure.GPIO_Pin = macEXTI2_GPIO_PIN;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 // ��������
  GPIO_Init(macEXTI2_GPIO_PORT, &GPIO_InitStructure);

	/* EXTI line mode config */
  GPIO_EXTILineConfig(macEXTI2_SOURCE_PORT, macEXTI2_SOURCE_PIN); 
  EXTI_InitStructure.EXTI_Line = macEXTI2_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�������ж�
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}
/*********************************************END OF FILE**********************/
