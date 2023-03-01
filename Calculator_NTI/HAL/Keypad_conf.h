#ifndef KEYPAD_CONF_H_
#define KEYPAD_CONF_H_

/**************************** ROWS AND COLUMNS MACROS **************************/
#define NO_OF_ROWS 4
#define NO_OF_COLUMNS 4



/*************************** Keypad Matrix configuration ********************************/

static const u8 KeypadMatrix[NO_OF_ROWS][NO_OF_COLUMNS] = 
{
	{'7' , '8' , '9' , '/'},
	{'4' , '5' , '6' , '*'},
	{'1' , '2' , '3' , '-'},
	{'c' , '0' , '=',  '+'}
};



/************************ Keypad Configuration Pins ***********************************/
#define KEYPAD_ROWS_PORTS			DIO_PORTC
#define KEYPAD_COLUMNS_PORTS		DIO_PORTD

 

static const u8 KeypadRows[NO_OF_ROWS] = 
										{ Pin5,  /* ROW 1*/
										  Pin4,  /* ROW 2 */
										  Pin3,  /* ROW 3 */
										  Pin2   /* ROW 4 */ 
										  };

static const u8 KeypadColumns[NO_OF_COLUMNS] =
										{ Pin7,   /* COL 1 */
										  Pin6,	  /* COL 2 */
										  Pin5,   /* COL 3 */
										  Pin3	  /* COL 4 */ 
										  };



#endif /* KEYPAD_CONF_H_ */