/*
 * LCD_private.h
 *
 * Created: 9/30/2022 9:49:13 PM
 *  Author: En.EslamEid
 */ 


#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

#define CMD_Clear_Display						             0x01
#define CMD_Return_Home				            			 0x02

#define CMD_Shift_Cursor_Left_Per_Read_Write				 0x04
#define CMD_Shift_Cursor_Right_Per_Read_Write				 0x06
#define CMD_Shift_Display_Right_Per_Read_Write               0x05
#define CMD_Shift_Display_Left_Per_Read_Write                0x07

#define CMD_Display_Cursor_Blink_ALL_OFF				     0x08
#define CMD_Display_Cursor_OFF_Blink_ON						 0x09
#define CMD_Display_OFF_Cursor_ON_Blink_OFF                  0x0A
#define CMD_Display_OFF_Cursor_Blink_ON                      0x0B
#define CMD_Display_ON_Cursor_Blink_OFF					     0x0C
#define CMD_Display_ON_Cursor_OFF_Blink_ON                   0x0D
#define CMD_Display_Cursor_ON_Blink_OFF          0x0E
#define CMD_Display_Cursor_Blink_ALL_ON          0X0F


#define CMD_Shift_Cursor_Position_Left           0x10
#define CMD_Shift_Cursor_Position_Right          0x14

#define CMD_Shift_Entire_Display_Left            0x18
#define CMD_Shift_Entire_Display_Right           0x1C


#define CMD_LCD_4Bit_Mode_1_Line_5X8			 0X20
#define CMD_LCD_4Bit_Mode_2_Line_5X8			 0X28
												
#define CMD_LCD_8Bit_Mode_1Line_5X8              0X30
#define CMD_LCD_8Bit_Mode_2Line_5X8              0X38


#define LCD_Line1_1stAddress                     0x80
#define LCD_Line2_1stAddress                     0xC0 //0X80+0X40=0XC0

#define CGRAM_CMD_OFFSET                         0X40
#define DDRAM_CMD_OFFSET                         0X80






#endif /* LCD_PRIVATE_H_ */