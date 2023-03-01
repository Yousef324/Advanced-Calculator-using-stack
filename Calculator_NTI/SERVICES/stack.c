#include "STD_TYPES.h"
#include "stack.h"



stack_status_t stack_push(stack_t *s,s16 data)
{
    if (s->sp >= MAX_STACKSIZE)
    {
        return STACK_FULL;
    }

	s->sp++;
    s->dataArr[s->sp] = data;
    return DONE;
}


stack_status_t stack_pop(stack_t *s, s16 *pdata)
{
    if(s->sp == -1)
    {
        return STACK_EMPTY;
    }

    *pdata = s->dataArr[s->sp];
    s->sp--;
    return DONE;
}

s8 stack_GetPeek(stack_t *s)
{
	if((s->sp) != -1)
	{
		return (s->dataArr[s->sp]);
	}
	else
	{
		return -1;
	}
}

void stack_Refresh(stack_t *s)
{
	while (s->sp != -1)
	{
		s->sp--;
	}
}






