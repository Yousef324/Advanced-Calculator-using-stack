#ifndef STACK_H_
#define STACK_H_


/******************************* STACK CONFIGURATION *****************************/
#define MAX_STACKSIZE 60


/********************************************************************************/


typedef enum
{
    STACK_EMPTY,
    STACK_FULL,
    DONE

}stack_status_t;


typedef struct
{
    s8 sp;
    s16 dataArr[MAX_STACKSIZE];
}stack_t;

typedef   stack_t *  STACK;   //ADVANCED


stack_status_t stack_push(stack_t *s,s16 data);
stack_status_t stack_pop(stack_t *s, s16 *pdata);

s8 stack_GetPeek(stack_t *s);
void stack_Refresh(stack_t *s);

#endif