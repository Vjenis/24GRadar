/***************************************************************************

 Author        : CAST

 Date          : March 8th, 2011

 File          : main.c

 Hardware      : ADuC7026 and ADF4158
	
***************************************************************************/
#include <ADuC7026.h>
#include "ADF4158_IO.h"
#include "ADuC7026Driver.h" 
int main (void)
{ 
    ADuC7026_Initiate(); 
	delay(1000);

/*  config();	  	   */

/*---------------------------------------------------------------------------
Reference frequency: 10.000MHz;
   Output frequency: 5800.000MHz;
---------------------------------------------------------------------------*/				 	  
/*
	ADF4158Registers[0]=0x01220000;
	ADF4158Registers[1]=0x00000001;
	ADF4158Registers[2]=0x00408fa2;		
	ADF4158Registers[3]=0x00000043;
	ADF4158Registers[4]=0x00000084;
	ADF4158Registers[5]=0x00480005;
	ADF4158Registers[6]=0x00000326;
	ADF4158Registers[7]=0x00000007;	 */ 

/*---------------------------------------------------------------------------
Reference frequency: 10.000MHz;
   Output frequency: 5800MHz-5815MHz;
---------------------------------------------------------------------------*/				 	  
/*								  
	ADF4158Registers[0]=0x81220000;
	ADF4158Registers[1]=0x00000001;
	ADF4158Registers[2]=0x00408fa2;		
	ADF4158Registers[3]=0x00000043;
	ADF4158Registers[4]=0x00180084;
	ADF4158Registers[5]=0x00481ebd;
	ADF4158Registers[6]=0x00000326;
	ADF4158Registers[7]=0x00000007;	   */
								  
	ADF4158Registers[0]=0x81220000;
	ADF4158Registers[1]=0x00000001;
	ADF4158Registers[2]=0x00408fa2;		
	ADF4158Registers[3]=0x00000443;
	ADF4158Registers[4]=0x00180084;
	ADF4158Registers[5]=0x00481ebd;
	ADF4158Registers[6]=0x00000326;
	ADF4158Registers[7]=0x00000007;	/* */ 	
								 		
	WriteToADF4158(ADF4158Registers,7);
	WriteToADF4158(ADF4158Registers,6);
	WriteToADF4158(ADF4158Registers,5);	
	WriteToADF4158(ADF4158Registers,4);
	WriteToADF4158(ADF4158Registers,3);
	WriteToADF4158(ADF4158Registers,2);
	WriteToADF4158(ADF4158Registers,1);
	WriteToADF4158(ADF4158Registers,0);

	while(1)
    {;}

}

