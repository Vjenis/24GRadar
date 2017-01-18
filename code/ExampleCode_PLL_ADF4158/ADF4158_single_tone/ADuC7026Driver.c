/***************************************************************************

 Author        : CAST  

 Date          : March 10th, 2011

 File          : ADuC7026Driver.c

 Hardware      : ADuC7026 and ADF4158
	
***************************************************************************/
#include <ADuC7026.h>
#include "ADuC7026Driver.h"

void ADuC7026_Initiate(void)
{
    //Clock Initial
    POWKEY1 = 0x01;				//Start PLL Setting
    POWCON = 0x00;				//Set PLL Active Mode With CD = 0  CPU CLOCK DIVIDER = 41.78MHz
    POWKEY2 = 0xF4;				//Finish PLL Setting
	GP1CON = 0x011;				  //PIN set up for UART
   	//UART Initial£¬Baud Rate = 9600								  	
	COMCON0 = 0x080;  
	COMDIV0 = 0x088;    		
	COMDIV1 = 0x000;
	COMCON0 = 0x007; 
} 
