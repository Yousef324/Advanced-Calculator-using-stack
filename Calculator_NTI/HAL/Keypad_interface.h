#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

#define NO_KEY 0

void Keypad_Init(void);

u8 Keypad_GetValue(void);

#endif /* KEYPAD_INTERFACE_H_ */