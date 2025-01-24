#ifndef    __USER_KEY_CONFIG_H__F
#define    __USER_KEY_CONFIG_H__F

#define KEY_INPUT_PORT GPIOA
#define KEY_INPUT_PIN  GPIO_PIN_0
extern void KeyInputExtiInit(GPIO_Module* GPIOx, uint16_t Pin);

#endif/*__USER_KEY_CONFIG_H__F*/
