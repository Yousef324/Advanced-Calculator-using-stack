#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_




void LCD_init(void);
void LCD_Write_CMD(u8 CMD);
void LCD_Write_DATA(u8 DATA);

void LCD_Clear(void);
void LCD_SetCursor(u8 line, u8 cell);
void LCD_CreateCharacter(u8 Location ,u8 *PatternBytes);

void LCD_Write_CHAR(u8 CHAR);
void LCD_WriteString(const u8 * str);
void LCD_WriteNUM(s64 NUM);



#endif /* LCD_INTERFACE_H_ */