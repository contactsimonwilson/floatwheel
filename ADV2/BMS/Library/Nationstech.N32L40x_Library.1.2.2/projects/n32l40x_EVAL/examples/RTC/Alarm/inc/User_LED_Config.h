#ifndef __USER_LED_CONFIG_H__
#define __USER_LED_CONFIG_H__


#define LED1_PORT      GPIOA
#define LED2_PORT      GPIOB
#define LED3_PORT      GPIOB

#define LED1_PIN       GPIO_PIN_8
#define LED2_PIN       GPIO_PIN_4
#define LED3_PIN       GPIO_PIN_5

extern void LEDLink(GPIO_Module* GPIOx,uint16_t Pin);
extern void LEDOn(GPIO_Module* GPIOx,uint16_t Pin);
extern void LEDOff(GPIO_Module* GPIOx,uint16_t Pin);
extern void LEDInit(GPIO_Module* GPIOx, uint16_t Pin);

#endif/*__USER_LED_CONFIG_H__*/
