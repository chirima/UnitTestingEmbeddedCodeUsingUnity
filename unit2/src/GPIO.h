#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

//#define BIT_TO_MASK(Pin)   (1<<Pin)
#define GPIO_OK            0

int GPIO_SetPinAsOutput(uint8_t Pin);
int GPIO_SetPinAsIntput(uint8_t Pin);
int GPIO_SetPin(uint8_t Pin);
int GPIO_ClearPin(uint8_t Pin);
void GPIO_Init(void);

#endif //GPIO_H
