#include "GPIO.h"
#include "MK20DX256.h"

static uint32_t ReverseMask;

int GPIO_SetPinAsOutput(uint8_t Pin)
{
    if(Pin >= 32)
    {
        return 1;
    }
    PORTC.PDDR |= BIT_TO_MASK(Pin);
    return 0;
}

int GPIO_SetPinAsIntput(uint8_t Pin)
{
    PORTC.PDDR &= ~(BIT_TO_MASK(Pin));
    return 0;
}

int GPIO_SetPin(uint8_t Pin)
{
    uint32_t Mask = BIT_TO_MASK(Pin); 
    if(Pin >= 32)
    {
        return 1;        
    }
    if(Mask & ReverseMask)
    {
        PORTC.PCOR = Mask;              
    }
    else
    {
        PORTC.PSOR = Mask;
    }
    if(!(Mask & PORTC.PDDR))
    {
        PORTC.PDDR |= Mask; 
    }
    return 0;
}

int GPIO_ClearPin(uint8_t Pin)
{
    return 1;
}

void GPIO_Init(void)
{   
    PORTC.PDDR = 0x1012A000;
    PORTC.PCOR = 0x10102000;
    PORTC.PSOR = 0x00028000;
    ReverseMask = 0x00000022;
}