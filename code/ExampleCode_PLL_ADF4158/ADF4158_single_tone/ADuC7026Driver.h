/***************************************************************************

 Author        : CAST  

 Date          : March 10th, 2011

 File          : ADuC7026Driver.h

 Hardware      : ADuC7026 and ADF4158
	
***************************************************************************/

#define SET_LE()		GP4DAT = (GP4DAT | 0x00080000)	//P4.3->LE
#define CLR_LE()		GP4DAT = (GP4DAT & 0xFFF7FFFF)

#define	SET_CLK()		GP4DAT = (GP4DAT | 0x00100000)	//P4.4->CLK
#define	CLR_CLK()		GP4DAT = (GP4DAT & 0xffefffff)

#define SET_DATA()		GP4DAT = (GP4DAT | 0x00200000)	//P4.5->DATA
#define CLR_DATA()		GP4DAT = (GP4DAT & 0xffdfffff)

#define SET_DATA_OUT()	GP4DAT = (GP4DAT | 0x38000000)

void ADuC7026_Initiate(void);


