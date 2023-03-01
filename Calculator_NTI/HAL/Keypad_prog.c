/*********************************************** MCAL INCLUSIONS **************************************/
#include "STD_TYPES.h"
#include "DIO_interface.h"


/********************************************* HAL INCLUSIONS ****************************************/

#include "Keypad_conf.h"
#include "Keypad_interface.h"


void Keypad_Init(void)
{
	u8 i = 0;
	/* Configuring KEYPad ROWS*/
	DIO_SetPinDir(DIO_PORTC,Pin2,OUTPUT);
	DIO_SetPinDir(DIO_PORTC,Pin3,OUTPUT);
	DIO_SetPinDir(DIO_PORTC,Pin4,OUTPUT);
	DIO_SetPinDir(DIO_PORTC,Pin5,OUTPUT);
		
		
	/* Configuring KEYPad columns*/
	DIO_SetInputPullUp(DIO_PORTD,Pin7);
	DIO_SetInputPullUp(DIO_PORTD,Pin6);
	DIO_SetInputPullUp(DIO_PORTD,Pin5);
	DIO_SetInputPullUp(DIO_PORTD,Pin3);
	
		
	for(i = 0; i<NO_OF_ROWS; i++)
	{
		DIO_SetPinValue(KEYPAD_ROWS_PORTS,KeypadRows[i],HIGH);
	}
}

u8 Keypad_GetValue(void)
{
	u8 Key = 0;
	u8 i = 0;
	u8 j = 0;
	
	for(i = 0; i<NO_OF_ROWS; i++)
	{
		DIO_SetPinValue(KEYPAD_ROWS_PORTS,KeypadRows[i],LOW);
		
		for(j = 0; j<NO_OF_COLUMNS; j++)
		{
			if(DIO_GetPinValue(KEYPAD_COLUMNS_PORTS,KeypadColumns[j]) == 0)
			{
				Key = KeypadMatrix[i][j];
				while(DIO_GetPinValue(KEYPAD_COLUMNS_PORTS,KeypadColumns[j]) == 0);
			}
		}
		
		DIO_SetPinValue(KEYPAD_ROWS_PORTS,KeypadRows[i],HIGH);
	}
	
	return Key;
}