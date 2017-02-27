/**
  ******************************************************************************
  * @file    bsp_i2c_adf4158.c
  * @author  STMicroelectronics
  * @version V1.0
  * @date    2016-xx-xx
  * @brief   i2c adf4158应用函数bsp
  ******************************************************************************
  */ 

#include "bsp_adf4158.h"

#define WIP_Flag                  0x01  /* Write In Progress (WIP) flag */

#define Dummy_Byte                0xFF

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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(macADF4158_LE_PORT, &GPIO_InitStructure);
	
	/*!< Configure ADF4158 pins: DATA */
	macADF4158_DATA_APBxClock_FUN ( macADF4158_DATA_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macADF4158_DATA_PIN;
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
//	ADF4158Registers[6]=0x00800006;
	ADF4158Registers[5]=0x00000005;
//	ADF4158Registers[5]=0x00800005;
	ADF4158Registers[4]=0x00180104;
	ADF4158Registers[3]=0x00000043;
	ADF4158Registers[2]=0x0000800A;	
	ADF4158Registers[1]=0x00000001;
	ADF4158Registers[0]=0x004B0000;

}


/**
  * @brief  I2C 外设adf4158初始化
  * @param  无
  * @retval 无
  */
void ADF4158_Init(void)
{
	
	SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	  
  /* Enable SPI1 and GPIO clocks */
  /*!< SPI_FLASH_SPI_CS_GPIO, SPI_FLASH_SPI_MOSI_GPIO, 
       SPI_FLASH_SPI_MISO_GPIO, SPI_FLASH_SPI_DETECT_GPIO 
       and SPI_FLASH_SPI_SCK_GPIO Periph clock enable */
  /*!< SPI_FLASH_SPI Periph clock enable */
	macSPI2_APBxClock_FUN ( macSPI2_CLK, ENABLE );
 
  /*!< Configure SPI_FLASH_SPI_CS_PIN pin: SPI_FLASH Card CS pin */
	macSPI2_CS_APBxClock_FUN ( macSPI2_CS_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macSPI2_CS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(macSPI2_CS_PORT, &GPIO_InitStructure);
	
  /*!< Configure SPI_FLASH_SPI pins: SCK */
	macSPI2_SCK_APBxClock_FUN ( macSPI2_SCK_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macSPI2_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(macSPI2_SCK_PORT, &GPIO_InitStructure);

  /*!< Configure SPI_FLASH_SPI pins: MOSI */
	macSPI2_MOSI_APBxClock_FUN ( macSPI2_MOSI_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macSPI2_MOSI_PIN;
  GPIO_Init(macSPI2_MOSI_PORT, &GPIO_InitStructure);
	
	/*!< Configure SPI_FLASH_SPI pins: MISO */
	macSPI2_MISO_APBxClock_FUN ( macSPI2_MISO_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macSPI2_MISO_PIN;
  GPIO_Init(macSPI2_MISO_PORT, &GPIO_InitStructure);

  /*!< Configure ADF4158 pins: TXDATA */
	macADF4158_TXDATA_APBxClock_FUN ( macADF4158_TXDATA_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macADF4158_TXDATA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(macADF4158_TXDATA_PORT, &GPIO_InitStructure);
  /* Deselect the FLASH: Chip Select high */
  macSPI_ADF4158_CS_DISABLE();

  /* SPI1 configuration */
  // W25X16: data input on the DIO pin is sampled on the rising edge of the CLK. 
  // Data on the DO and DIO pins are clocked out on the falling edge of CLK.
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(macSPI2 , &SPI_InitStructure);

  /* Enable SPI1  */
  SPI_Cmd(macSPI2 , ENABLE);

//	ADF4158Registers[0]=0x81220000;
//	ADF4158Registers[1]=0x00000001;
//	ADF4158Registers[2]=0x00408fa2;		
//	ADF4158Registers[3]=0x00000443;
//	ADF4158Registers[4]=0x00180084;
//	ADF4158Registers[5]=0x00481ebd;
//	ADF4158Registers[6]=0x00000326;
//	ADF4158Registers[7]=0x00000007;
	
//	ADF4158Registers[9]=0x00000007;
//	ADF4158Registers[8]=0x00000006;
//	ADF4158Registers[7]=0x00800006;
//	ADF4158Registers[6]=0x00000005;
//	ADF4158Registers[5]=0x00800005;
//	ADF4158Registers[4]=0x00180104;
//	ADF4158Registers[3]=0x00000043;
//	ADF4158Registers[2]=0x0000800A;	
//	ADF4158Registers[1]=0x00000001;
//	ADF4158Registers[0]=0x004B0000;
	
	ADF4158Registers[7]=0x00000007;
	ADF4158Registers[6]=0x00000006;
//	ADF4158Registers[6]=0x00800006;
	ADF4158Registers[5]=0x00000005;
//	ADF4158Registers[5]=0x00800005;
	ADF4158Registers[4]=0x00180104;
	ADF4158Registers[3]=0x00000043;
	ADF4158Registers[2]=0x0000800A;	
	ADF4158Registers[1]=0x00000001;
	ADF4158Registers[0]=0x004B0000;
	
//	ADF4158Registers[0]=0;
//	ADF4158Registers[1]=0;
//	ADF4158Registers[2]=0;	
//	ADF4158Registers[3]=0;
//	ADF4158Registers[4]=0;
//	ADF4158Registers[5]=0;
//	ADF4158Registers[6]=0;
//	ADF4158Registers[7]=0;
	
//	config();
}

u16 SPI_ADF4158_ReadByte(void)
{
    /* Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(macSPI2 , SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(macSPI2 );
}

void SPI_ADF4158_SendByte(u16 byte)
{
  /* Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(macSPI2 , SPI_I2S_FLAG_TXE) == RESET);

  /* Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(macSPI2 , byte);

  /* Wait to receive a byte */
//  while (SPI_I2S_GetFlagStatus(macSPI2 , SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
//  return SPI_I2S_ReceiveData(macSPI2 );
}

/*******************************************************************************
* Function Name  : SPI_adf4158_ByteWrite
* Description    : Writes more than one byte to the FLASH with a single WRITE
*                  cycle(Page WRITE sequence). The number of byte can't exceed
*                  the FLASH page size.
* Input          : - pBuffer : pointer to the buffer  containing the data to be
*                    written to the FLASH.
*                  - NumByteToWrite : number of bytes to write to the FLASH,
*                    must be equal or less than "SPI_FLASH_PageSize" value.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_adf4158_ByteWrite(u32* pBuffer, u16 count)
//void SPI_adf4158_ByteWrite(u8* pBuffer, u32 ByteWrite)
//void SPI_ADF4158_ByteWrite(u32 ByteWrite)
{
//	u8 FLASH_Status = 0;
	unsigned	long int  temp ;

  /* Select the FLASH: Chip Select low */
  macSPI_ADF4158_CS_ENABLE();
	
//	/* Send WriteAddr high nibble address byte to write to */
//  SPI_ADF4158_SendByte((ByteWrite & 0xFFFF0000) >> 16);  
//	/* Send WriteAddr high nibble address byte to write to */
//  SPI_ADF4158_SendByte(ByteWrite & 0xFFFF) ;
	
//	/* Send WriteAddr high nibble address byte to write to */
//  SPI_ADF4158_SendByte((ByteWrite & 0xFF000000) >> 24);  
//	/* Send WriteAddr high nibble address byte to write to */
//  SPI_ADF4158_SendByte((ByteWrite & 0xFF0000) >> 16);
//  /* Send WriteAddr medium nibble address byte to write to */
//  SPI_ADF4158_SendByte((ByteWrite & 0xFF00) >> 8);
//  /* Send WriteAddr low nibble address byte to write to */
//  SPI_ADF4158_SendByte(ByteWrite & 0xFF);

	temp =*(pBuffer+count);
	/* Send WriteAddr high nibble address byte to write to */
  SPI_ADF4158_SendByte((temp & 0xFFFF0000) >> 16);  
	/* Send WriteAddr high nibble address byte to write to */
  SPI_ADF4158_SendByte(temp & 0xFFFF) ;
	
  /* while there is data to be written on the FLASH */
//  while (ByteWrite--)
//  {
//    /* Send the current byte */
//    SPI_ADF4158_SendByte(*pBuffer);
//    /* Point on the next byte to be written */
//    pBuffer++;
//  }

//  /* Wait the end of ADF4158 writing */
//  do
//  {
//    /* Send a dummy byte to generate the clock needed by the FLASH
//    and put the value of the status register in FLASH_Status variable */
//    FLASH_Status = SPI_ADF4158_SendByte(Dummy_Byte);	 
//  }
//  while ((FLASH_Status & WIP_Flag) == SET); /* Write in progress */
	
  /* Deselect the FLASH: Chip Select high */
  macSPI_ADF4158_CS_DISABLE();
	
}

//void SPI_adf4158_ByteRead(u32* pBuffer, u16 count)
void SPI_adf4158_ByteRead16bit(u16* pBuffer, u16 count)
{
//	unsigned	long int  temp ;
	
//	/* Select the FLASH: Chip Select low */
//  macSPI_ADF4158_CS_ENABLE();
	
	/* Deselect the FLASH: Chip Select high */
  macSPI_ADF4158_CS_DISABLE();	
	
	TXDATA(1);
	delay(1);
	TXDATA(0);
		
	*(pBuffer+count) =SPI_ADF4158_ReadByte();
	
//	temp =*(pBuffer+count);
	
//	temp =*(pBuffer+count);
		
	/* Send WriteAddr high nibble address byte to write to */
//  SPI_ADF4158_SendByte((temp & 0xFFFF0000) >> 16);  
	/* Send WriteAddr high nibble address byte to write to */
//  SPI_ADF4158_SendByte(temp & 0xFFFF) ;
	
//	/* Deselect the FLASH: Chip Select high */
//  macSPI_ADF4158_CS_DISABLE();
	
}


//---------------------------------
//void WriteToADF4158(unsigned long int *buff , char Adress)
//---------------------------------

void WriteToADF4158(u32* pBuffer , u16 Adress)//u8 WriteAddr
{
  unsigned	char      i;
	unsigned	long int  temp ;
	
	DATA(1);//DATAOUT(1);	
	delay(1);
	CLK(0);
	LE(0);
    temp =*(pBuffer+Adress);
	for(i=0; i<32; i++)
	{
			if(temp & 0x80000000)
			{
				DATA(1);	  //Send one to SDO pin
			}
			else
			{
				DATA(0);	  //Send zero to SDO pin
			}
			delay(1);
			CLK(1);
			temp <<= 1;	//Rotate data
			CLK(0);		
	}
	delay(1);
	LE(1);
	delay(1);
	LE(0);
}

void ReadToADF4158_16bit(u16* pBuffer , u16 Adress)
{
	unsigned	char      i;
	unsigned	long int  temp ;
	
	TXDATA(1);//DATAOUT(1);	
	delay(1);
	CLK(0);
	LE(1);

    temp =*(pBuffer+Adress);
	for(i=0; i<16; i++)
	{
			if(temp & 0x8000)
			{
				DATA(1);	  //Send one to SDO pin
			}
			else
			{
				DATA(0);	  //Send zero to SDO pin
			}
			delay(1);
			CLK(1);
			temp <<= 1;	//Rotate data
			CLK(0);		
	}
//	delay(1);
//	LE(1);
//	delay(1);
//	LE(0);
}

void ReadToADF4158_21bit(u32* pBuffer , u16 Adress)
{
	unsigned	char      i;
	unsigned	long int  temp ;
	
//	TXDATA(1);//DATAOUT(1);	
//	delay(1);
//	CLK(0);
//	LE(1);

    temp =*(pBuffer+Adress);
	for(i=0; i<25; i++)
	{
			if(temp & 0x8000000)
			{
				DATA(1);	  //Send one to SDO pin
			}
			else
			{
				DATA(0);	  //Send zero to SDO pin
			}
			delay(1);
			CLK(1);
			temp <<= 1;	//Rotate data
			CLK(0);		
	}
//	delay(1);
//	LE(1);
	delay(1);
	LE(0);
}
/*********************************************END OF FILE**********************/

