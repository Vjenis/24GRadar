 /**
  ******************************************************************************
  * @file    BGT24MTR12.c
  * @author  
  * @version 
  * @date    2016-12-08
  * @brief   BGT24MTR12µ×²ãÓ¦ÓÃº¯Êýbsp 
  ******************************************************************************
  */
  
#include "BGT24MTR12.h"
#include "bsp_adf4158.h"

/* Private define ------------------------------------------------------------*/
#define Output_Power_Reducion_0		      0x0000  			//0dB
#define Output_Power_Reducion_1		      0x0001 				//0.4dB
#define Output_Power_Reducion_2		      0x0002 				//0.8dB
#define Output_Power_Reducion_3		      0x0003 				//1.4dB
#define Output_Power_Reducion_4			    0x0004 				//2.5dB
#define Output_Power_Reducion_5		      0x0005 				//4dB
#define Output_Power_Reducion_6		      0x0006 				//6dB
#define Output_Power_Reducion_7		      0x0007 				//9dB

#define WIP_Flag                  0x0001  /* Write In Progress (WIP) flag */
#define NoneOutput                0x1001  /* Write In Progress (WIP) flag */

#define Dummy_Byte                0xFF

uint8_t ReadValue;

//extern uint8_t Key1Down_Count;

/*******************************************************************************
* Function Name  : SPI_BGT24MTR12_Init
* Description    : Initializes the peripherals used by the SPI FLASH driver.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_BGT24MTR12_Init(void)
{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	
  
  /* Enable SPI1 and GPIO clocks */
  /*!< SPI_FLASH_SPI_CS_GPIO, SPI_FLASH_SPI_MOSI_GPIO, 
       SPI_FLASH_SPI_MISO_GPIO, SPI_FLASH_SPI_DETECT_GPIO 
       and SPI_FLASH_SPI_SCK_GPIO Periph clock enable */
  /*!< SPI_FLASH_SPI Periph clock enable */
	macSPI_APBxClock_FUN ( macSPI_CLK, ENABLE );
 
  /*!< Configure SPI_FLASH_SPI_CS_PIN pin: SPI_FLASH Card CS pin */
	macSPI_CS_APBxClock_FUN ( macSPI_CS_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macSPI_CS_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(macSPI_CS_PORT, &GPIO_InitStructure);
	
  /*!< Configure SPI_FLASH_SPI pins: SCK */
	macSPI_SCK_APBxClock_FUN ( macSPI_SCK_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macSPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(macSPI_SCK_PORT, &GPIO_InitStructure);

  /*!< Configure SPI_FLASH_SPI pins: MOSI */
	macSPI_MOSI_APBxClock_FUN ( macSPI_MOSI_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macSPI_MOSI_PIN;
  GPIO_Init(macSPI_MOSI_PORT, &GPIO_InitStructure);
	
	/*!< Configure SPI_FLASH_SPI pins: MISO */
	macSPI_MISO_APBxClock_FUN ( macSPI_MISO_CLK, ENABLE );
  GPIO_InitStructure.GPIO_Pin = macSPI_MISO_PIN;
  GPIO_Init(macSPI_MISO_PORT, &GPIO_InitStructure);

  /* Deselect the FLASH: Chip Select high */
  macSPI_BGT24MTR12_CS_DISABLE();

  /* SPI1 configuration */
  // W25X16: data input on the DIO pin is sampled on the rising edge of the CLK. 
  // Data on the DO and DIO pins are clocked out on the falling edge of CLK.
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(macSPIx , &SPI_InitStructure);

  /* Enable SPI1  */
  SPI_Cmd(macSPIx , ENABLE);
	
}

u8 SPI_BGT_SendByte(u8 byte)
{
  /* Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(macSPIx , SPI_I2S_FLAG_TXE) == RESET);

  /* Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(macSPIx , byte);

  /* Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(macSPIx , SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(macSPIx );
}

/*******************************************************************************
* Function Name  : SPI_BGT24MTR12_Write
* Description    : Write BGT24MTR12 Register.
* Input          : None
* Output         : None
* Return         : 
*******************************************************************************/
void SPI_BGT24MTR12_Write(u16 count)
{
//  u16 Temp = 0;

  /* Select the FLASH: Chip Select low */
  macSPI_BGT24MTR12_CS_ENABLE();

	switch(count)
	{
		 /* Send data */
		case '0' : SPI_BGT24MTR12_SendByte(Output_Power_Reducion_0);break;
		case '1' : SPI_BGT24MTR12_SendByte(Output_Power_Reducion_1);break;
		case '2' : SPI_BGT24MTR12_SendByte(Output_Power_Reducion_2);break;
		case '3' : SPI_BGT24MTR12_SendByte(Output_Power_Reducion_3);break;
		case '4' : SPI_BGT24MTR12_SendByte(Output_Power_Reducion_4);break;
		case '5' : SPI_BGT24MTR12_SendByte(Output_Power_Reducion_5);break;
		case '6' : SPI_BGT24MTR12_SendByte(Output_Power_Reducion_6);break;
		case '7' : SPI_BGT24MTR12_SendByte(Output_Power_Reducion_7);break;
		default : SPI_BGT24MTR12_SendByte(NoneOutput);
		break;
	}
	/*#ifdef Output_Power_Reducion_0
	Power_Select = Output_Power_Reducion_0£»
	#enddef*/
  
//	ReadValue = GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_7);
	
  /* Read a byte from the BGT24MTR12 */
//  Temp = SPI_BGT24MTR12_SendByte(Output_Power_Reducion_6);
	
  /* Deselect the BGT24MTR12: Chip Select high */
  macSPI_BGT24MTR12_CS_DISABLE();

//  return Temp;
}

/*******************************************************************************
* Function Name  : SPI_BGT_ByteWrite
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
void SPI_BGT_ByteWrite(u8* pBuffer, u16 ByteWrite)
//void SPI_BGT_ByteWrite(u16 ByteWrite)
{
//	u8 FLASH_Status = 0;

  /* Select the FLASH: Chip Select low */
  macSPI_BGT24MTR12_CS_ENABLE();

//  /* Send WriteAddr medium nibble address byte to write to */
//  SPI_BGT_SendByte((ByteWrite & 0xFF00) >> 8);
//  /* Send WriteAddr low nibble address byte to write to */
//  SPI_BGT_SendByte(ByteWrite & 0xFF);

//  if(NumByteToWrite > SPI_FLASH_PerWritePageSize)
//  {
//     NumByteToWrite = SPI_FLASH_PerWritePageSize;
//     //printf("\n\r Err: SPI_FLASH_PageWrite too large!");
//  }

  /* while there is data to be written on the FLASH */
  while (ByteWrite--)
  {
    /* Send the current byte */
    SPI_BGT_SendByte(*pBuffer);
    /* Point on the next byte to be written */
    pBuffer++;
  }

  /* Wait the end of BGT writing */
//  do
//  {
//    /* Send a dummy byte to generate the clock needed by the FLASH
//    and put the value of the status register in FLASH_Status variable */
//    FLASH_Status = SPI_BGT_SendByte(Dummy_Byte);	 
//  }
//  while ((FLASH_Status & WIP_Flag) == SET); /* Write in progress */
	
  /* Deselect the FLASH: Chip Select high */
  macSPI_BGT24MTR12_CS_DISABLE();
	
}


/*******************************************************************************
* Function Name  : SPI_BGT24MTR12_SendByte
* Description    : Sends a byte through the SPI interface and return the byte
*                  received from the SPI bus.
* Input          : byte : byte to send.
* Output         : None
* Return         : The value of the received byte.
*******************************************************************************/
u16 SPI_BGT24MTR12_SendByte(u16 byte)
{
  /* Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(macSPIx , SPI_I2S_FLAG_TXE) == RESET);

  /* Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(macSPIx , byte);

  /* Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(macSPIx , SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(macSPIx );
}


/*********************************************END OF FILE**********************/
