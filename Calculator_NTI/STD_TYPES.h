#ifndef STD_TYPES_H_
#define STD_TYPES_H_


typedef unsigned char u8;
typedef signed char   s8;

typedef unsigned short u16;
typedef signed short   s16;


typedef unsigned long u32;
typedef signed long   s32;

typedef unsigned long long u64;
typedef signed long long   s64;

typedef float f32;

typedef double f64;

typedef enum {
	OK,
	NOK,
	NULL_PTR,
	OUT_OF_RANGE
}Error_type;

typedef enum {
	FALSE,
	TRUE
}Bool_type;

#define NULL_PTR  ((void *)0)
#define NULL	  ((char)0)

#define MAX_U8    ((u8)255)
#define MAX_S8    ((s8)127)
#define MIN_S8    ((s8)-128)




#endif /* STD_TYPES_H_ */