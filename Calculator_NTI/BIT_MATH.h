#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define SET_BIT(REG,BIT)	(REG |= (1<<BIT))
#define CLR_BIT(REG,BIT)	(REG &= ~(1<<BIT))
#define READ_BIT(REG,BIT)	((REG>>BIT)&1)
#define TOGGLE_BIT(REG,BIT) (REG ^= (1<<BIT))



#endif /* BIT_MATH_H_ */