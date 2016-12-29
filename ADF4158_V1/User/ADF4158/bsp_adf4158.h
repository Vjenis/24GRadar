#ifndef __ADF4158_H
#define	__ADF4158_H


#include "stm32f10x.h"

/* 带参宏，可以像内联函数一样使用 */
#define CLK(a)	if (a)	\
					GPIO_SetBits(macADF4158_CLK_PORT,macADF4158_CLK_PIN);\
					else		\
					GPIO_ResetBits(macADF4158_CLK_PORT,macADF4158_CLK_PIN)

#define LE(a)	if (a)	\
					GPIO_SetBits(macADF4158_LE_PORT,macADF4158_LE_PIN);\
					else		\
					GPIO_ResetBits(macADF4158_LE_PORT,macADF4158_LE_PIN)

#define DATA(a)	if (a)	\
					GPIO_SetBits(macADF4158_DATA_PORT,macADF4158_DATA_PIN);\
					else		\
					GPIO_ResetBits(macADF4158_DATA_PORT,macADF4158_DATA_PIN)
					
#define TXDATA(a)	if (a)	\
					GPIO_SetBits(macADF4158_TXDATA_PORT,macADF4158_TXDATA_PIN);\
					else		\
					GPIO_ResetBits(macADF4158_TXDATA_PORT,macADF4158_TXDATA_PIN)

#define MUXOUT(a)	if (a)	\
					GPIO_SetBits(macADF4158_MUXOUT_PORT,macADF4158_MUXOUT_PIN);\
					else		\
					GPIO_ResetBits(macADF4158_MUXOUT_PORT,macADF4158_MUXOUT_PIN)

/**************************	ADF4158参数定义 ********************************/
#define      				macADF4158_CLK_APBxClock_FUN             	RCC_APB2PeriphClockCmd
#define      				macADF4158_CLK_CLK                       	RCC_APB2Periph_GPIOC
#define             macADF4158_CLK_PORT                       GPIOC 
#define             macADF4158_CLK_PIN                        GPIO_Pin_8

#define      				macADF4158_LE_APBxClock_FUN           		RCC_APB2PeriphClockCmd
#define      				macADF4158_LE_CLK                     		RCC_APB2Periph_GPIOC
#define             macADF4158_LE_PORT                    		GPIOC   
#define             macADF4158_LE_PIN                     		GPIO_Pin_9

#define      				macADF4158_DATA_APBxClock_FUN           	RCC_APB2PeriphClockCmd
#define      				macADF4158_DATA_CLK                     	RCC_APB2Periph_GPIOC
#define             macADF4158_DATA_PORT                    	GPIOC   
#define             macADF4158_DATA_PIN                     	GPIO_Pin_10

#define      				macADF4158_TXDATA_APBxClock_FUN           RCC_APB2PeriphClockCmd
#define      				macADF4158_TXDATA_CLK                     RCC_APB2Periph_GPIOC
#define             macADF4158_TXDATA_PORT                    GPIOC   
#define             macADF4158_TXDATA_PIN                     GPIO_Pin_11

#define      				macADF4158_MUXOUT_APBxClock_FUN           RCC_APB2PeriphClockCmd
#define      				macADF4158_MUXOUT_CLK                     RCC_APB2Periph_GPIOC
#define             macADF4158_MUXOUT_PORT                    GPIOC 
#define             macADF4158_MUXOUT_PIN                     GPIO_Pin_12


/*********     				  define adf4158  			      ************************/
#define	 FRAC_INT_REGISTER_R0		   0
#define  FRAC_REGISTER_R1   		   1
#define  R_DIVIDER_REGISTER_R2         2
#define  FUNCTION_REGISTER_R3          3 
#define  TEST_REGISTER_R4      		   4
#define  DEVIATION_REGISTER_R5		   5
#define  STEP_REGISTER_R6			   6
#define  DELAY_REGISTER_R7			   7

/***************************************************************************/
/*********       define FRAC&INT_REGISTER_R0        ************************/
#define  MSB_FRACTIONAL_VALUE		   0
#define  INTEGER_VALUE				   580

#define  RAMP_ON					  0x80000000//(0x1<<31)
/***  MUXOUT_CONTROL  ***/
#define  THREE_STATE_OUTPUT			  (0x0<<27)
#define  DVDD						  (0x1<<27)
#define  DGND						  (0x2<<27)
#define  R_DIVIDER_OUTPUT			  (0x3<<27)
#define  N_DIVIDER_OUTPUT			  (0x4<<27)
//#define  RESERVED					  (0x5<<27)
#define  DIGITAL_LOCK_DETECT		  (0x6<<27)
#define  SERIAL_DATA_OUTPUT			  (0x7<<27)
//#define  RESERVED					  (0x8<<27)
//#define  RESERVED					  (0x9<<27)
#define  CLK_DIVIDER_OUTPUT			  (0xa<<27)
//#define  RESERVED					  (0xb<<27)
#define  FAST_LOCK_SWITCH			  (0xc<<27)
#define  R_DIVIDER_By_2				  (0xd<<27)
#define  N_DIVIDER_By_2				  (0xe<<27)
#define  READBACK_TO_MUXOUT			  (0xf<<27)

#define  BIT_12_INTEGER_VALUE		  (INTEGER_VALUE<<15)
#define  BIT_12_MSB_FRACTIONAL_VALUE  (MSB_FRACTIONAL_VALUE<<3)


/***************************************************************************/
/*********       define FRAC_REGISTER_R1     *******************************/

#define  LSB_FRACTIONAL_VALUE		   0

#define  BIT_13_LSB_FRACTIONAL_VALUE  (LSB_FRACTIONAL_VALUE<<15)


/***************************************************************************/
/*********       define R_DIVIDER_REGISTER_R2   ****************************/
#define  R_COUNTER					   1
//#define  MOD_DIVIDER				   0
#define  MOD_DIVIDER				   500

#define  CP_CURRENT_SETTING			   0

#define  CYCLE_SLIP_REDUCTION		   (0x1<<28)
#define  BIT_4_CP_CURRENT_SETTING	   (CP_CURRENT_SETTING<<24)
#define  PRESCALER					   (0x1<<22)
#define  R_DIV2_EN					   (0x1<<21)
#define  REFERENCE_DOUBLER_EN		   (0x1<<20)
#define  BIT_5_R_COUNTER			   (R_COUNTER<<15)
#define  BIT_12_MOD_DIVIDER			   (MOD_DIVIDER<<3)

/***************************************************************************/
/*********       define  FUNCTION_REGISTER_R3           ********************/

#define  N_WORD_LOAD_DELAYED_4_CYCLES  (0x1<<15)
#define  SD_RESET					   (0x1<<14)
/****RAMP MODE	 *******/
#define  CONTINUOUS_SAWTOOTH		   (0x0<<10)
#define  SINGLE_TRIANGULAR			   (0x1<<10)
#define  SINGLE_SAWTOOTH			   (0x2<<10)
#define  CONTINUOUS_TRIANGULAR		   (0x3<<10)

#define  PSK_EN						   (0x1<<9)
#define  FSK_EN						   (0x1<<8)
#define  LDP_40_20_cycle			   (0x1<<7)
#define  PD_POLARITY				   (0x1<<6)
#define  POWER_DOWN					   (0x1<<5)
#define  CP_THREE_STATE				   (0x1<<4)
#define  COUNTER_RESET				   (0x1<<3)

/***************************************************************************/
/*********       define  TEST_REGISTER_R4               ********************/

#define  CLOCK_DIVIDER_VALUE		    1

#define  LE_SEL						   (0x1<<31)
#define  READBACK_TO_MUXOUT_EN		   (0x2<<21)
#define  CLOCK_DIVIDER_OFF			   (0x0<<19)
#define  FAST_LOCK_DIVIDER			   (0x1<<19)
#define  RESERVED					   (0x2<<19)
#define  RAMP_DIVIDER				   (0x3<<19)

#define  BIT_12_CLOCK_DIVIDER_VALUE	   (CLOCK_DIVIDER_VALUE<<7)

/***************************************************************************/
/*********       define  DEVIATION_REGISTER_R5          ********************/
//#define  DEVIATION_WORD		     0
#define  DEVIATION_WORD		     983
#define  DEV_OFFSET_WORD		 9

#define  TX_RAMP_CLK				   (0x1<<29)
#define  PAR_RAMP					   (0x1<<28)
#define  INTERRUPT_OFF				   (0x0<<26)
#define  LOAD_CHANNEL_CONTINUE_SWEEP   (0x1<<26)
#define  NOT_USED					   (0x2<<26)
#define  LOAD_CHANNEL_STOP_SWEEP	   (0x3<<26)
#define  FSK_RAMP_EN				   (0x1<<25)
#define  RAMP_2_EN					   (0x1<<24)
#define  DEV_SEL					   (0x1<<23)
#define  BIT_4_DEV_OFFSET_WORD		   (DEV_OFFSET_WORD<<19)
#define  BIT_16_DEVIATION_WORD		   (DEVIATION_WORD<<3)

/***************************************************************************/
/*********       define  STEP_REGISTER_R6               ********************/

//#define  Step_Word						1
#define  Step_Word						100

#define  Step_SEL 						(0x1<<23)
#define  Bit_20_Step_Word 				(Step_Word<<3)  

/***************************************************************************/
/*********       define  DELAY_REGISTER_R7              ********************/

#define  DELAY_START_WORD				0

#define  RAMP_DEL_FL				   (0x1<<18)
#define  RAMP_DEL					 	   (0x1<<17)
#define  DEL_CLK_SEL				   (0x1<<16)
#define  DEL_START_EN				   (0x1<<15)
#define  BIT_12_DELAY_START_WORD	   (DELAY_START_WORD<<3)




extern  uint32_t ADF4158Registers[8];

void WriteToADF4158(uint32_t* pBuffer , char Adress);
void config(void);
void delay (int length);


void ADF4158_Init(void);


#endif /* __ADF4158_H */
