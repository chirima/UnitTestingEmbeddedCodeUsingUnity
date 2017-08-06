#include "unity.h"
#include "GPIO.h"
#include "MK20DX256.h"

void setUp(void)
{
    
}

void tearDown(void)
{
    
}

void test_PinOutput_should_ConfigurePinDirection(void)
{
    PORTC.PDDR = 0;
    
    TEST_ASSERT_EQUAL(GPIO_OK, GPIO_SetPinAsOutput(0));
    TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(0), PORTC.PDDR);
    
    TEST_ASSERT_EQUAL(GPIO_OK, GPIO_SetPinAsOutput(22));
    TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(0) | BIT_TO_MASK(22), PORTC.PDDR);
    
    TEST_ASSERT_EQUAL(GPIO_OK, GPIO_SetPinAsOutput(31));    
    TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(0) | BIT_TO_MASK(22) | BIT_TO_MASK(31), 
                            PORTC.PDDR);    
}

void test_PinOutput_should_NotUpdate_whenPinIsNotValid(void)
{
    PORTC.PDDR = 0;
    
    GPIO_SetPinAsOutput(32);
    TEST_ASSERT_EQUAL_HEX32(0, PORTC.PDDR);
}

void test_PinIntput_should_ConfigurePinDirection(void)
{
    PORTC.PDDR = 0xFFFFFFFF;
    
    TEST_ASSERT_EQUAL(GPIO_OK, GPIO_SetPinAsIntput(0));
    TEST_ASSERT_EQUAL_HEX32(~(BIT_TO_MASK(0)), PORTC.PDDR);
    
    TEST_ASSERT_EQUAL(GPIO_OK, GPIO_SetPinAsIntput(16));
    TEST_ASSERT_EQUAL_HEX32(~(BIT_TO_MASK(0) | BIT_TO_MASK(16)), PORTC.PDDR);
    
    TEST_ASSERT_EQUAL(GPIO_OK, GPIO_SetPinAsIntput(31));    
    TEST_ASSERT_EQUAL_HEX32(~(BIT_TO_MASK(0) | BIT_TO_MASK(16) | BIT_TO_MASK(31)), 
                            PORTC.PDDR);    
}

void test_SetPin_should_SetOutputHigh(void)
{
    PORTC.PSOR = 0;
    PORTC.PCOR = 0;
    PORTC.PDDR = 0x50000000;

    TEST_ASSERT_EQUAL(0, GPIO_SetPin(0));
    TEST_ASSERT_NOT_EQUAL(0, GPIO_SetPin(32));
    TEST_ASSERT_EQUAL_HEX32(BIT_TO_MASK(0), PORTC.PSOR);
    TEST_ASSERT_EQUAL_HEX32(0, PORTC.PCOR);
    TEST_ASSERT_EQUAL_HEX32(0x50000001, PORTC.PDDR);
}

void test_ClearPin_(void)
{
}

void test_GPIOInit_should_ConfigurePinsToDefault(void)
{
    PORTC.PDDR = 0;
    PORTC.PCOR = 0;
    PORTC.PSOR = 0;
    
    GPIO_Init();
    
    TEST_ASSERT_EQUAL_HEX32(0x1012A000, PORTC.PDDR);
    TEST_ASSERT_EQUAL_HEX32(0x10102000, PORTC.PCOR);
    TEST_ASSERT_EQUAL_HEX32(0x00028000, PORTC.PSOR);
}

void test_SetPin_should_HandleReversedPins(void)
{
    GPIO_Init();
    PORTC.PSOR = 0;
    PORTC.PCOR = 0;
        
    GPIO_SetPin(1);
    
    TEST_ASSERT_EQUAL(BIT_TO_MASK(1), PORTC.PCOR);
    TEST_ASSERT_EQUAL(0, PORTC.PSOR);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_PinOutput_should_ConfigurePinDirection);
    RUN_TEST(test_PinOutput_should_NotUpdate_whenPinIsNotValid);
    RUN_TEST(test_PinIntput_should_ConfigurePinDirection);
    RUN_TEST(test_SetPin_should_SetOutputHigh);
    RUN_TEST(test_GPIOInit_should_ConfigurePinsToDefault);
    RUN_TEST(test_SetPin_should_HandleReversedPins);
    return UNITY_END();
}
