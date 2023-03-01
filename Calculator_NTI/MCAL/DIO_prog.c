/************************** BIT_MATH AND STD_TYPES INCLUSION FILES *************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"

/************************** DIO INCLUSION FILES *************************************/
#include "DIO_interface.h"
#include "DIO_private.h"


/************************* FUNCTIONS IMPLEMENTATIONS ******************************/

void DIO_SetPinDir(PORT_TYPE port,PIN_TYPE pin,MODE_TYPE mode)
{
	if(mode == OUTPUT)
	{
		switch(port)
		{
			case DIO_PORTA:
			SET_BIT(DDRA,pin);
			CLR_BIT(PORTA,pin);
			break;
			
			case DIO_PORTB:
			SET_BIT(DDRB,pin);
			CLR_BIT(PORTB,pin);
			break;
			
			case DIO_PORTC:
			SET_BIT(DDRC,pin);
			CLR_BIT(PORTC,pin);
			break;
			
			case DIO_PORTD:
			SET_BIT(DDRD,pin);
			CLR_BIT(PORTD,pin);
			break;
		}
	}
	else if (mode == INPUT)
	{
		switch(port)
		{
			case DIO_PORTA:
			CLR_BIT(DDRA,pin);
			CLR_BIT(PORTA,pin);
			break;
			
			case DIO_PORTB:
			CLR_BIT(DDRB,pin);
			CLR_BIT(PORTB,pin);
			break;
			
			case DIO_PORTC:
			CLR_BIT(DDRC,pin);
			CLR_BIT(PORTC,pin);
			break;
			
			case DIO_PORTD:
			CLR_BIT(DDRD,pin);
			CLR_BIT(PORTD,pin);
			break;
		}
	}
}

void DIO_SetPinValue(PORT_TYPE port,PIN_TYPE pin,MODE_TYPE mode)
{
	if(mode == HIGH)
	{
		switch(port)
		{
			case DIO_PORTA:
			SET_BIT(PORTA,pin);
			break;
			
			case DIO_PORTB:
			SET_BIT(PORTB,pin);
			break;
			
			case DIO_PORTC:
			SET_BIT(PORTC,pin);
			break;
			
			case DIO_PORTD:
			SET_BIT(PORTD,pin);
			break;
		}
	}
	else if(mode == LOW)
	{
		switch(port)
		{
			case DIO_PORTA:
			CLR_BIT(PORTA,pin);
			break;
					
			case DIO_PORTB:
			CLR_BIT(PORTB,pin);
			break;
					
			case DIO_PORTC:
			CLR_BIT(PORTC,pin);
			break;
					
			case DIO_PORTD:
			CLR_BIT(PORTD,pin);
			break;
		}
		
	}
}

u8 DIO_GetPinValue(PORT_TYPE port,PIN_TYPE pin)
{
	u8 ReadPin = 0;
	switch(port)
	{
		case DIO_PORTA:
		ReadPin = READ_BIT(PINA,pin);
		break;
		
		case DIO_PORTB:
		ReadPin = READ_BIT(PINB,pin);
		break;
		
		case DIO_PORTC:
		ReadPin = READ_BIT(PINC,pin);
		break;
		
		case DIO_PORTD:
		ReadPin = READ_BIT(PIND,pin);
		break;
	}
	
	return ReadPin;
	
}

void DIO_SetInputPullUp(PORT_TYPE port,PIN_TYPE pin)
{
	switch(port)
	{
		case DIO_PORTA:
		CLR_BIT(DDRA,pin);
		SET_BIT(PORTA,pin);
		break;
	
		case DIO_PORTB:
		CLR_BIT(DDRB,pin);
		SET_BIT(PORTB,pin);
		break;
	
		case DIO_PORTC:
		CLR_BIT(DDRC,pin);
		SET_BIT(PORTC,pin);
		break;
	
		case DIO_PORTD:
		CLR_BIT(DDRD,pin);
		SET_BIT(PORTD,pin);
		break;
	}
}


void DIO_TogglePinValue(PORT_TYPE port,PIN_TYPE pin)
{
	switch(port)
	{
		case DIO_PORTA:
		TOGGLE_BIT(PORTA,pin);
		break;
		
		case DIO_PORTB:
		TOGGLE_BIT(PORTB,pin);
		break;
		
		case DIO_PORTC:
		TOGGLE_BIT(PORTC,pin);
		break;
		
		case DIO_PORTD:
		TOGGLE_BIT(PORTD,pin);
		break;
	}
}