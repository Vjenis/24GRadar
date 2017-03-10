/**
  ******************************************************************************
  * @file    bsp_i2c_adf4158.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2016-xx-xx
  * @brief   i2c adf4158Ó¦ÓÃº¯Êýbsp
  ******************************************************************************
  */ 

#include "bsp_adf4158.h"
#include "bsp_SysTick.h"

uint32_t ADF4158Registers[8];


void config (void)
{
	ADF4158Registers[0]=0;
	ADF4158Registers[1]=0;
	ADF4158Registers[2]=0;
	ADF4158Registers[3]=0;
	ADF4158Registers[4]=0;
	ADF4158Registers[5]=0;
	ADF4158Registers[6]=0;
	ADF4158Registers[7]=0;


/*---------------------------------------------------------------------------
Reference frequency: 10.000MHz;
   Output frequency: 5800.000MHz;
---------------------------------------------------------------------------*/
/*	ADF4158Registers[FRAC_INT_REGISTER_R0]=(FRAC_INT_REGISTER_R0|BIT_12_INTEGER_VALUE|BIT_12_MSB_FRACTIONAL_VALUE);
	ADF4158Registers[FRAC_REGISTER_R1]=(FRAC_REGISTER_R1|BIT_13_LSB_FRACTIONAL_VALUE);
	ADF4158Registers[R_DIVIDER_REGISTER_R2]=(R_DIVIDER_REGISTER_R2|BIT_5_R_COUNTER|BIT_12_MOD_DIVIDER|PRESCALER);
	ADF4158Registers[FUNCTION_REGISTER_R3]=(FUNCTION_REGISTER_R3|PD_POLARITY);
	ADF4158Registers[TEST_REGISTER_R4]=(TEST_REGISTER_R4|BIT_12_CLOCK_DIVIDER_VALUE);
	ADF4158Registers[DEVIATION_REGISTER_R5]=(DEVIATION_REGISTER_R5|BIT_4_DEV_OFFSET_WORD|BIT_16_DEVIATION_WORD);
	ADF4158Registers[STEP_REGISTER_R6]=(STEP_REGISTER_R6|Bit_20_Step_Word);
	ADF4158Registers[DELAY_REGISTER_R7]=(DELAY_REGISTER_R7);
*/


/*---------------------------------------------------------------------------
Reference frequency: 10.000MHz;
   Output frequency: 5800MHz-5815MHz;
---------------------------------------------------------------------------*/
	ADF4158Registers[FRAC_INT_REGISTER_R0]=(FRAC_INT_REGISTER_R0|BIT_12_INTEGER_VALUE|BIT_12_MSB_FRACTIONAL_VALUE|RAMP_ON);
	ADF4158Registers[FRAC_REGISTER_R1]=(FRAC_REGISTER_R1|BIT_13_LSB_FRACTIONAL_VALUE);
	ADF4158Registers[R_DIVIDER_REGISTER_R2]=(R_DIVIDER_REGISTER_R2|BIT_5_R_COUNTER|BIT_12_MOD_DIVIDER|PRESCALER);
	ADF4158Registers[FUNCTION_REGISTER_R3]=(FUNCTION_REGISTER_R3|PD_POLARITY|CONTINUOUS_SAWTOOTH);
	ADF4158Registers[TEST_REGISTER_R4]=(TEST_REGISTER_R4|BIT_12_CLOCK_DIVIDER_VALUE|RAMP_DIVIDER);
	ADF4158Registers[DEVIATION_REGISTER_R5]=(DEVIATION_REGISTER_R5|BIT_4_DEV_OFFSET_WORD|BIT_16_DEVIATION_WORD);
	ADF4158Registers[STEP_REGISTER_R6]=(STEP_REGISTER_R6|Bit_20_Step_Word);
	ADF4158Registers[DELAY_REGISTER_R7]=(DELAY_REGISTER_R7);
}

void delay (int length)
{
	while (length >0)
    	length--;
}


void ADF4158_GPIO_Config()
{

	GPIO_InitTypeDef  GPIO_InitStructure;
	
  /*!< Configure ADF4158 pin: LE */
	macADF4158_LE_APBxClock_FUN ( macADF4158_LE_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macADF4158_LE_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(macADF4158_LE_PORT, &GPIO_InitStructure);
	
	/*!< Configure ADF4158 pins: CLK */
	macADF4158_CLK_APBxClock_FUN ( macADF4158_CLK_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macADF4158_CLK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(macADF4158_LE_PORT, &GPIO_InitStructure);
	
	/*!< Configure ADF4158 pins: DATA */
	macADF4158_DATA_APBxClock_FUN ( macADF4158_DATA_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macADF4158_DATA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(macADF4158_DATA_PORT, &GPIO_InitStructure);
	
  /*!< Configure ADF4158 pins: TXDATA */
	macADF4158_TXDATA_APBxClock_FUN ( macADF4158_TXDATA_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macADF4158_TXDATA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(macADF4158_TXDATA_PORT, &GPIO_InitStructure);

  /*!< Configure ADF4158 pins: MUXOUT */
	macADF4158_MUXOUT_APBxClock_FUN ( macADF4158_MUXOUT_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macADF4158_MUXOUT_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(macADF4158_MUXOUT_PORT, &GPIO_InitStructure);
 
// 	config();
	ADF4158Registers[7]=0x00000007;
	ADF4158Registers[6]=0x00000006;
	ADF4158Registers[5]=0x00000005;
	ADF4158Registers[4]=0x00180104;
	ADF4158Registers[3]=0x00000043;
	ADF4158Registers[2]=0x0000800A;	
	ADF4158Registers[1]=0x00000001;
	ADF4158Registers[0]=0x004b0000;

//	ADF4158Registers[0]=0xf84b0000;
//	ADF4158Registers[1]=0x00000001;
//	ADF4158Registers[2]=0x00008f2a;		
//	ADF4158Registers[3]=0x00000443;
//	ADF4158Registers[4]=0x00480104;
//	ADF4158Registers[5]=0x00000005;
//	ADF4158Registers[6]=0x00000006;
//	ADF4158Registers[7]=0x00000007;
}

//---------------------------------
//void WriteToADF4158(unsigned long int *buff , char Adress)
//---------------------------------

void WriteToADF4158(u32* pBuffer , u16 Adress)//u8 WriteAddr
{
  unsigned	char      i;
	unsigned	long int  temp ;
	
	//DATA(1);//DATAOUT(1);	
	//delay(2);
	LE(1);
	CLK(0);
	LE(0);
    temp =*(pBuffer+Adress);
	for(i=0; i<31; i++)
	{
			if(temp & 0x80000000)
			{
				DATA(1);	  //Send one to SDO pin
			}
			else
			{
				DATA(0);	  //Send zero to SDO pin
			}
			delay(2);
			CLK(1);
			temp <<= 1;	//Rotate data
			delay(1);
			CLK(0);		
	}
	if(temp & 0x80000000)
			{
				DATA(1);	  //Send one to SDO pin
			}
			else
			{
				DATA(0);	  //Send zero to SDO pin
			}
	CLK(1);
	delay(1);
	LE(1);
	delay(2);
	CLK(0);
//	LE(0);
}

unsigned long int ReadToADF4158_16bit(void)
{
	unsigned	char      i;
	unsigned	long int  temp=0 ;
	
	TXDATA(0);//DATAOUT(1);	
	CLK(0);
	LE(1);
	delay(2);
	TXDATA(1);
	temp=temp|MUXOUT();
	temp<<=1;
	delay(2);
	CLK(1);
	TXDATA(0);
	delay(2);
	
//    temp =*(pBuffer+Adress);
	for(i=1; i<37; i++)
	{
		CLK(0);
		temp=temp|MUXOUT();
		temp<<=1;
			//delay(2);
			CLK(1);
//			temp <<= 1;	//Rotate data
			delay(2);	
	}
	CLK(0);
	//delay(2);	
//	LE(1);
//	delay(1);
	LE(0);
	return temp;
}

/*********************************************END OF FILE**********************/

