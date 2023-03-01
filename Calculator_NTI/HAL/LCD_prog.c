#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#define F_CPU 16000000
#include <util/delay.h>

#include "LCD_conf.h"
#include "LCD_interface.h"
#include "LCD_private.h"




void LCD_Write_CMD(u8 CMD)
{
	DIO_SetPinValue(RS_EN_PORT,RS,LOW);
	
	DIO_SetPinValue(LCD_PORT,D7,READ_BIT(CMD,7));
	DIO_SetPinValue(LCD_PORT,D6,READ_BIT(CMD,6));
	DIO_SetPinValue(LCD_PORT,D5,READ_BIT(CMD,5));
	DIO_SetPinValue(LCD_PORT,D4,READ_BIT(CMD,4));
	
	DIO_SetPinValue(RS_EN_PORT,EN,HIGH);
	_delay_ms(1);
	DIO_SetPinValue(RS_EN_PORT,EN,LOW);
	_delay_ms(1);
	
	
	DIO_SetPinValue(LCD_PORT,D7,READ_BIT(CMD,3));
	DIO_SetPinValue(LCD_PORT,D6,READ_BIT(CMD,2));
	DIO_SetPinValue(LCD_PORT,D5,READ_BIT(CMD,1));
	DIO_SetPinValue(LCD_PORT,D4,READ_BIT(CMD,0));
	
	DIO_SetPinValue(RS_EN_PORT,EN,HIGH);
	_delay_ms(1);
	DIO_SetPinValue(RS_EN_PORT,EN,LOW);
	_delay_ms(1);
}


void LCD_Write_DATA(u8 DATA)
{
		DIO_SetPinValue(RS_EN_PORT,RS,HIGH);
		
		DIO_SetPinValue(LCD_PORT,D7,READ_BIT(DATA,7));
		DIO_SetPinValue(LCD_PORT,D6,READ_BIT(DATA,6));
		DIO_SetPinValue(LCD_PORT,D5,READ_BIT(DATA,5));
		DIO_SetPinValue(LCD_PORT,D4,READ_BIT(DATA,4));
		
		DIO_SetPinValue(RS_EN_PORT,EN,HIGH);
		_delay_ms(1);
		DIO_SetPinValue(RS_EN_PORT,EN,LOW);
		_delay_ms(1);
		
		
		DIO_SetPinValue(LCD_PORT,D7,READ_BIT(DATA,3));
		DIO_SetPinValue(LCD_PORT,D6,READ_BIT(DATA,2));
		DIO_SetPinValue(LCD_PORT,D5,READ_BIT(DATA,1));
		DIO_SetPinValue(LCD_PORT,D4,READ_BIT(DATA,0));
		
		DIO_SetPinValue(RS_EN_PORT,EN,HIGH);
		_delay_ms(1);
		DIO_SetPinValue(RS_EN_PORT,EN,LOW);
		_delay_ms(1);
}

void LCD_init(void)
{
		/* Configuring LCD pins*/
		
		DIO_SetPinDir(DIO_PORTA,Pin2,OUTPUT);
		DIO_SetPinDir(DIO_PORTA,Pin3,OUTPUT);
		DIO_SetPinDir(DIO_PORTB,Pin0,OUTPUT);
		DIO_SetPinDir(DIO_PORTB,Pin1,OUTPUT);
		DIO_SetPinDir(DIO_PORTB,Pin2,OUTPUT);
		DIO_SetPinDir(DIO_PORTB,Pin4,OUTPUT);
	_delay_ms(30);
	
	/* Function set mode */
	LCD_Write_CMD(0x02);
	LCD_Write_CMD(CMD_LCD_4Bit_Mode_2_Line_5X8);
	
	/* Display ON/OFF Control */
	LCD_Write_CMD(CMD_Display_ON_Cursor_Blink_OFF);
	
	/* Display Clear */
	LCD_Write_CMD(CMD_Clear_Display);
	
	/* Entry Mode Set */
	LCD_Write_CMD(CMD_Shift_Cursor_Right_Per_Read_Write);
}


void LCD_Write_CHAR(u8 data)
{
	LCD_Write_DATA(data);
}


void LCD_WriteString(const u8 * str)
{
	u8 i = 0;
	
	for(i = 0; str[i]!=0; i++)
	{
		LCD_Write_CHAR(str[i]);
	}
}


void LCD_SetCursor(u8 line, u8 cell)
{
	switch (line)
	{
		case 1:
		LCD_Write_CMD(LCD_Line1_1stAddress + (cell - 1));
		break;
		
		case 2:
		LCD_Write_CMD(LCD_Line2_1stAddress + (cell - 1));
		break;
		
		case 3:
		LCD_Write_CMD(LCD_Line1_1stAddress + 0x14 + (cell - 1));
		break;
		
		case 4:
		LCD_Write_CMD(LCD_Line1_1stAddress + 0x54 + (cell - 1));
		break;
		
	}
}
void LCD_Clear(void)
{
	LCD_Write_CMD(CMD_Clear_Display);
}

void LCD_CreateCharacter(u8 Location ,u8 *PatternBytes)
{
	u8 i = 0;
	
	LCD_Write_CMD(CGRAM_CMD_OFFSET + (Location * 8));
	
	for(i = 0; i<8; i++)
	{
		LCD_Write_CHAR(PatternBytes[i]);
	}
	
	LCD_Write_CMD(LCD_Line1_1stAddress);
	
}

void LCD_WriteNUM(s64 NUM)
{
	u8 str[8] = {0};
	u8 i = 0;
	s8 j = 0;
	
	if(NUM == 0)
	{
		LCD_Write_CHAR('0'); 
	}
	if(NUM < 0)
	{
		LCD_Write_CHAR('-');
		NUM = NUM * (-1);
	}
	while(NUM)
	{
		str[i] = ((NUM % 10) + '0');
		
		NUM = NUM / 10;
		i++;
	}
	

	for(j = i - 1;j>=0;j--)
	{
		LCD_Write_CHAR(str[j]);
	}
	
}

void LCD_WriteFLOAT(f64 num,u8 Percision)
{	
	s64 IntNum = (s64)num;
	LCD_WriteNUM(IntNum);
	LCD_Write_CHAR('.');
	
	num -= IntNum;
	
	u8 res = 0;
	
	u8 i = 0;
	
	for(i = 0; i<Percision; i++)
	{
		num = num * 10;
		LCD_Write_CHAR((u8)num + '0');
		res = (u8)num;
		num -= res;
	}
	
	
	
	
}