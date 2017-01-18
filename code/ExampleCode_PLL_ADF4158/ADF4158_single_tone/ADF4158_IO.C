/***************************************************************************

 Author        : CAST 

 Date          : March 10th, 2011

 File          : ADF4158_IO.c

 Hardware      : ADuC7026 and ADF4158
	
***************************************************************************/
#include <ADuC7026.h>
#include "ADuC7026Driver.h"
#include "ADF4158_IO.h"

unsigned long int ADF4158Registers[8];

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

//---------------------------------
//void WriteToADF4158(unsigned long int *buff , char Adress)
//---------------------------------

void WriteToADF4158(unsigned long int *buff , char Adress)
{
    unsigned	char      i;
	unsigned	long int  temp ;
	
	SET_DATA_OUT();	
	delay(1);
	CLR_CLK();
	CLR_LE();
    temp =*(buff+Adress);
	for(i=0; i<32; i++)
	{
			if(temp & 0x80000000)
			{
				SET_DATA();	  //Send one to SDO pin
			}
			else
			{
				CLR_DATA();	  //Send zero to SDO pin
			}
			delay(1);
			SET_CLK();
			temp <<= 1;	//Rotate data
			CLR_CLK();		
	}
	delay(1);
	SET_LE();
	delay(1);
	CLR_LE();
}
