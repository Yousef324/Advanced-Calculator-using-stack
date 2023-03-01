/***************************  UTILS and SERVICES INCLUSION *********************/
#include "STD_TYPES.h"
#include "stack.h"

/************************** MCAL INCLUSIONS *************************************/
#include "DIO_interface.h"

#define F_CPU 8000000
#include <util/delay.h>


/************************** HAL INCLUSIONS ************************************/
#include "LCD_interface.h"
#include "Keypad_interface.h"

/************************* APP INCLUSIONS ************************************/
#include "Calculator_private.h"
#include "Calculator.h"


/************************* GLOBAL VARS ****************************************/
static u8 key = NO_KEY;
static u8 temp[Max_Digits] = {0};
static u8 i = 0;
static u8 PrecedenceArray [50]={0};
static u8 Flag = 0;	
static s16 Input = 0;
static s16 Operand_1 = 0;
static s16 Operand_2 = 0;
static s16 OP = 0;
static s16 result = 0;

static stack_t OperationsStack = {-1,{0}};
static stack_t ResultsStack = {-1,{0}};



void Calculator_Init(void)
{
	LCD_init();
	Keypad_Init();
	Calculator_WelcomeMessage();
	
	/*Initializing the push button for ( and ) */
	DIO_SetInputPullUp(DIO_PORTD,Pin0);
	DIO_SetInputPullUp(DIO_PORTD,Pin1);
	
	/* Initializing the precedence array */
	PrecedenceArray[42]=2;				// precedence of (*)
	PrecedenceArray[47]=2;				// precedence of (/)
	PrecedenceArray[43]=1;				// precedence of (+)
	PrecedenceArray[45]=1;				// precedence of (-)
	
	/* Initializing the Stack Operation to begin with 0 */
	//stack_push(&OperationsStack,0);
}


void Calculator_Runnable(void)
{
	key = Keypad_GetValue();
	
	if(DIO_GetPinValue(DIO_PORTD,Pin0)==LOW)
	{
		key = '(';
		LCD_Write_CHAR(key);
		while(DIO_GetPinValue(DIO_PORTD,Pin0)==LOW);
	}
			
	if(key >= '0' && key <= '9')
	{
		LCD_Write_CHAR(key);
		temp[i] = key;
		i++;
	}
				
	else if(key == '+' || key == '-' || key == '*' || key == '/')
	{
		LCD_Write_CHAR(key);
		if(Flag == 0)
		{
			temp[i] = 0;
			Input = Calculator_StringToInt(temp);
			stack_push(&ResultsStack,Input);
			i = 0;
			Calculator_EvaluatingPrecedence();
			stack_push(&OperationsStack,key);
		}
		else
		{
			Flag = 0;
			stack_push(&OperationsStack,key);
		}	

	}
	
	else if(key == '(')
	{
		while(1)
		{
			key = Keypad_GetValue();
			if(key >= '0' && key <= '9')
			{
				LCD_Write_CHAR(key);
				temp[i] = key;
				i++;
			}
			
			if(DIO_GetPinValue(DIO_PORTD,Pin1)==LOW)
			{
				LCD_Write_CHAR(')');
				temp[i] = 0;
				Input = Calculator_StringToInt(temp);
				i = 0;
				stack_push(&ResultsStack,Input);
				stack_pop(&ResultsStack,&Operand_2);
				stack_pop(&ResultsStack,&Operand_1);
				stack_pop(&OperationsStack,&OP);
				result = Calculator_PerformingOperation(Operand_1,Operand_2,OP);
				stack_push(&ResultsStack,result);
				Flag = 1;
				while(DIO_GetPinValue(DIO_PORTD,Pin1)==LOW);
				break;
			}
			
			if(key == '+' || key == '-' || key == '*' || key == '/')
			{
				LCD_Write_CHAR(key);
				temp[i] = 0;
				Input = Calculator_StringToInt(temp);
				stack_push(&ResultsStack,Input);
				Calculator_EvaluatingPrecedence();
				stack_push(&OperationsStack,key);
				i = 0;
			}
		}
	}
			
	else if(key == '=')
	{
		if(Flag == 0)
		{
			temp[i] = 0;
			Input = Calculator_StringToInt(temp);
			stack_push(&ResultsStack,Input);
			i = 0;
			Calculator_EvaluatingTheFinalResult();
		}
		else
		{
			Flag = 0;
			Calculator_EvaluatingTheFinalResult();
		}

		
	}
			
	else if(key == 'c')
	{
		LCD_Clear();
		result = 0;
		i = 0;
		stack_Refresh(&OperationsStack);
		stack_Refresh(&ResultsStack);
	}		
}

static void Calculator_WelcomeMessage(void)
{
	LCD_SetCursor(1,1);
	LCD_WriteString("===========================");
	LCD_SetCursor(2,1);
	LCD_WriteString("  CALCULATOR APP ");
	LCD_SetCursor(3,1);
	LCD_WriteString("===========================");
	_delay_ms(2500);
	LCD_Clear();
	
}


static s16 Calculator_StringToInt(u8 *temp)
{
	u8 i = 0;
	s16 Num = 0;
	for(i = 0; temp[i]!=0; i++)
	{
		Num = Num * 10 + (temp[i] - '0');
	}
	return Num;
}

static s16 Calculator_PerformingOperation(s16 Number_1, s16 Number_2, u8 operation)
{
	s16 result = 0;
	
	switch (operation)
	{
		case '+': result=Number_1 + Number_2;   break;
		
		case '-': result = Number_1 - Number_2; break;
		
		case '*': result = Number_1 * Number_2; break;
		
		case '/':
		if(Number_2 == 0)
		{
			result = ERROR_VALUE;
		}
		else
		{
			result = Number_1 / Number_2;
		}
		break;
	}

	return result;
}



static void Calculator_EvaluatingTheFinalResult(void)
{

	while (stack_GetPeek(&OperationsStack)!= -1)
	{
		stack_pop(&ResultsStack,&Operand_2);
		stack_pop(&ResultsStack,&Operand_1);
		stack_pop(&OperationsStack,&OP);
		result = Calculator_PerformingOperation(Operand_1,Operand_2,OP);
		
		if(result == ERROR_VALUE)
		{
			break;
		}
		
		stack_push(&ResultsStack,result);
	}
	if(result == ERROR_VALUE)
	{
		LCD_Clear();
		LCD_SetCursor(2,5);
		LCD_WriteString("MATH ERROR");
	}
	else
	{
		result = stack_GetPeek(&ResultsStack);
		LCD_SetCursor(4,1);
		LCD_WriteString("ANS:");
		LCD_WriteNUM(result);
	}
	
}

static void Calculator_EvaluatingPrecedence(void)
{
	/* Checking if the operator precedence is less than the latest operator */
	/* if yes: perform the operation */
	/* case for multiplication and division */
	if(PrecedenceArray[key] < PrecedenceArray[stack_GetPeek(&OperationsStack)])
	{
		stack_pop(&ResultsStack,&Operand_2);
		stack_pop(&ResultsStack,&Operand_1);
		stack_pop(&OperationsStack,&OP);
		result = Calculator_PerformingOperation(Operand_1,Operand_2,OP);
		stack_push(&ResultsStack, result);
	}
	
	/* Checking if the operator precedence is equal to the latest operator */
	/* if yes: perform the operation */
	/* case for Addition and Subtraction */
	else if(PrecedenceArray[key] == PrecedenceArray[stack_GetPeek(&OperationsStack)])
	{
		stack_pop(&ResultsStack,&Operand_2);
		stack_pop(&ResultsStack,&Operand_1);
		stack_pop(&OperationsStack,&OP);
		result = Calculator_PerformingOperation(Operand_1,Operand_2,OP);
		stack_push(&ResultsStack, result);
	}
}


