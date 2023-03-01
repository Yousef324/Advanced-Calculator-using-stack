#ifndef CALCULATOR_PRIVATE_H_
#define CALCULATOR_PRIVATE_H_

static void Calculator_WelcomeMessage(void);
static s16 Calculator_StringToInt(u8 *temp);
static s16 Calculator_PerformingOperation(s16 Number_1, s16 Number_2, u8 operation);
static void Calculator_EvaluatingTheFinalResult(void);
static void Calculator_EvaluatingPrecedence(void);


#endif /* CALCULATOR_PRIVATE_H_ */