/*****************************************************************************
 * Copyright (c) 2022, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file main.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#define BIT0                     ((uint32_t)1 << 0)
#define BIT1                     ((uint32_t)1 << 1)
#define BIT2                     ((uint32_t)1 << 2)
#define BIT3                     ((uint32_t)1 << 3)
#define BIT4                     ((uint32_t)1 << 4)
#define BIT5                     ((uint32_t)1 << 5)
#define BIT6                     ((uint32_t)1 << 6)
#define BIT7                     ((uint32_t)1 << 7)
#define BIT8                     ((uint32_t)1 << 8)
#define BIT9                     ((uint32_t)1 << 9)
#define BIT10                    ((uint32_t)1 << 10)
#define BIT11                    ((uint32_t)1 << 11)
#define BIT12                    ((uint32_t)1 << 12)
#define BIT13                    ((uint32_t)1 << 13)
#define BIT14                    ((uint32_t)1 << 14)
#define BIT15                    ((uint32_t)1 << 15)
#define BIT16                    ((uint32_t)1 << 16)
#define BIT17                    ((uint32_t)1 << 17)
#define BIT18                    ((uint32_t)1 << 18)
#define BIT19                    ((uint32_t)1 << 19)
#define BIT20                    ((uint32_t)1 << 20)
#define BIT21                    ((uint32_t)1 << 21)
#define BIT22                    ((uint32_t)1 << 22)
#define BIT23                    ((uint32_t)1 << 23)
#define BIT24                    ((uint32_t)1 << 24)
#define BIT25                    ((uint32_t)1 << 25)
#define BIT26                    ((uint32_t)1 << 26)
#define BIT27                    ((uint32_t)1 << 27)
#define BIT28                    ((uint32_t)1 << 28)
#define BIT29                    ((uint32_t)1 << 29)
#define BIT30                    ((uint32_t)1 << 30)
#define BIT31                    ((uint32_t)1 << 31)
#define SetBitMsk(reg, bit, msk) ((reg) = ((reg) & ~(msk) | (bit)))
#define ClrBit(reg, bit)         ((reg) &= ~(bit))
#define SetBit(reg, bit)         ((reg) |= (bit))
#define GetBit(reg, bit)         ((reg) & (bit))

#include "main.h"

/** @addtogroup CompBreak
 * @{
 */

TIM_TimeBaseInitType TIM_TimeBaseStructure;
OCInitType TIM_OCInitStructure;
TIM_BDTRInitType TIM_BDTRInitStructure;
uint16_t TimerPeriod   = 0;
uint16_t Channel1Pulse = 0, Channel2Pulse = 0, Channel3Pulse = 0, Channel4Pulse = 0;

void RCC_Configuration(void);
void GPIO_CompConfiguration(void);
void GPIO_TimConfiguration(void);
void COMP_Configuratoin(void);
void TIM_Intial(TIM_Module* TIMx);
void NVIC_Configuration(void);
void ChangeVmVp(void);

/**
 * @brief   Main program
 */
int main(void)
{
    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* NVIC configuration ------------------------------------------------------*/
    NVIC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_CompConfiguration();
    GPIO_TimConfiguration();

    /* tim pwm configuration ------------------------------------------------------*/
    TIM_Intial(TIM1);
    TIM_Intial(TIM8);

    /* COMP configuration ------------------------------------------------------*/
    COMP_Configuratoin();
    while (1)
    {
        ChangeVmVp();
    }
}

/**
 * @brief  Self Generate Puls ,by skip line connect to vp and vm if need.
 */
void ChangeVmVp(void)
{
    GPIO_SetBits(GPIOD, GPIO_PIN_2);
    GPIO_ResetBits(GPIOD, GPIO_PIN_3);
    {
        uint32_t i = 0;
        while (i++ < 10000)
            ;
    }
    GPIO_ResetBits(GPIOD, GPIO_PIN_2);
    GPIO_SetBits(GPIOD, GPIO_PIN_3);
    {
        uint32_t i = 0;
        while (i++ < 10000)
            ;
    }
}
/**
 * @brief  Configures the comp module.
 */
void COMP_Configuratoin(void)
{
    COMP_InitType COMP_Initial;

    /*Set dac2,dac1. because dac1/PA4 is share pin line,so only PB0 puls 0/1, can find out puls*/
    COMP_SetRefScl(16, true, 32, true);
    /*Initial comp*/
    COMP_StructInit(&COMP_Initial);
    COMP_Initial.InpSel     = COMP1_CTRL_INPSEL_PB10;
    COMP_Initial.InmSel     = COMP1_CTRL_INMSEL_PA5;
    COMP_Initial.SampWindow = 18;       //(0~31)
    COMP_Initial.Thresh     = 12;       //Thresh should be greater than half of SampWindow and should be less than SampWindow at the same time.
    COMP_Init(COMP1, &COMP_Initial);
    /*trig initial as tim1&tim8 break*/
    COMP_SetOutTrig(COMP1, COMP1_CTRL_OUTSEL_TIM1_BKIN_TIM8_BKIN);
    /*enable comp1*/
    COMP_Enable(COMP1, ENABLE);
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* Enable COMP clocks */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_COMP | RCC_APB1_PERIPH_COMP_FILT, ENABLE);
    /* Enable GPIOA, GPIOB, GPIOC and GPIOD clocks */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO | RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_GPIOC
                                | RCC_APB2_PERIPH_GPIOD | RCC_APB2_PERIPH_TIM1 | RCC_APB2_PERIPH_TIM8,
                            ENABLE);

    /* stop tim when debug stop */
    DBG_ConfigPeriph(DBG_TIM1_STOP | DBG_TIM8_STOP , ENABLE);
}

/**
 * @brief   intial timx program
 */
void TIM_Intial(TIM_Module* TIMx)
{
    /* TIMx Configuration ---------------------------------------------------
    Generate 7 PWM signals with 4 different duty cycles:
    TIM1CLK = SystemCoreClock, Prescaler = 0, TIM1 counter clock = SystemCoreClock
    SystemCoreClock is set to 72 MHz for Low-density, Medium-density, High-density
    and Connectivity line devices and to 24 MHz for Low-Density Value line and
    Medium-Density Value line devices

    The objective is to generate 7 PWM signal at 17.57 KHz:
     - TIMx_Period = (SystemCoreClock / 17570) - 1
    The channel 1 and channel 1N duty cycle is set to 50%
    The channel 2 and channel 2N duty cycle is set to 37.5%
    The channel 3 and channel 3N duty cycle is set to 25%
    The channel 4 duty cycle is set to 12.5%
    The Timer pulse is calculated as follows:
     - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100
    ----------------------------------------------------------------------- */
    /* Compute the value to be set in AR regiter to generate signal frequency at 17.57 Khz */
    TimerPeriod = 50; //(SystemCoreClock / 17570 ) - 1;
    /* Compute CCDAT1 value to generate a duty cycle at 50% for channel 1 and 1N */
    Channel1Pulse = (uint16_t)(((uint32_t)5 * (TimerPeriod - 1)) / 10);
    /* Compute CCDAT2 value to generate a duty cycle at 37.5%  for channel 2 and 2N */
    Channel2Pulse = (uint16_t)(((uint32_t)375 * (TimerPeriod - 1)) / 1000);
    /* Compute CCDAT3 value to generate a duty cycle at 25%  for channel 3 and 3N */
    Channel3Pulse = (uint16_t)(((uint32_t)25 * (TimerPeriod - 1)) / 100);
    /* Compute CCDAT4 value to generate a duty cycle at 12.5%  for channel 4 */
    Channel4Pulse = (uint16_t)(((uint32_t)125 * (TimerPeriod - 1)) / 1000);

    /* Time Base configuration */
    TIM_TimeBaseStructure.Prescaler = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_TimeBaseStructure.Period    = TimerPeriod;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.RepetCnt  = 0;

    TIM_InitTimeBase(TIMx, &TIM_TimeBaseStructure);

    /* Channel 1, 2,3 and 4 Configuration in PWM mode */
    TIM_OCInitStructure.OcMode       = TIM_OCMODE_PWM2;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.OutputNState = TIM_OUTPUT_NSTATE_ENABLE;
    TIM_OCInitStructure.Pulse        = Channel1Pulse;
    TIM_OCInitStructure.OcPolarity   = TIM_OC_POLARITY_LOW;
    TIM_OCInitStructure.OcNPolarity  = TIM_OCN_POLARITY_HIGH;
    TIM_OCInitStructure.OcIdleState  = TIM_OC_IDLE_STATE_SET;
    TIM_OCInitStructure.OcNIdleState = TIM_OC_IDLE_STATE_RESET;
    TIM_InitOc1(TIMx, &TIM_OCInitStructure);

    TIM_OCInitStructure.Pulse = Channel3Pulse;
    TIM_InitOc3(TIMx, &TIM_OCInitStructure);
    TIM_OCInitStructure.Pulse = Channel4Pulse;
    // TIM_InitOc4(TIMx, &TIM_OCInitStructure);

    /*TIM_OCInitStructure.OutputNState = TIM_OUTPUT_NSTATE_DISABLE;*/
    TIM_OCInitStructure.Pulse = Channel2Pulse;
    TIM_InitOc2(TIMx, &TIM_OCInitStructure);

    /* TIM1 break */
    TIM_BDTRInitStructure.OssrState       = TIM_OSSR_STATE_ENABLE;
    TIM_BDTRInitStructure.OssiState       = TIM_OSSI_STATE_ENABLE;
    TIM_BDTRInitStructure.LockLevel       = TIM_LOCK_LEVEL_OFF;
    TIM_BDTRInitStructure.DeadTime        = 1;
    TIM_BDTRInitStructure.Break           = TIM_BREAK_IN_ENABLE;
    TIM_BDTRInitStructure.BreakPolarity   = TIM_BREAK_POLARITY_HIGH;
    TIM_BDTRInitStructure.AutomaticOutput = TIM_AUTO_OUTPUT_ENABLE;
    TIM_BDTRInitStructure.IomBreakEn      = false;
    TIM_BDTRInitStructure.LockUpBreakEn   = false;
    TIM_BDTRInitStructure.PvdBreakEn      = false;
    TIM_ConfigBkdt(TIMx, &TIM_BDTRInitStructure);

    /* TIM1 counter enable */
    TIM_Enable(TIMx, ENABLE);

    /* TIM1 Main Output Enable */
    TIM_EnableCtrlPwmOutputs(TIMx, ENABLE);
}

/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_CompConfiguration(void)
{
    GPIO_InitType GPIO_InitStructure;
    
    GPIO_InitStruct(&GPIO_InitStructure);
    /*INP*/
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Analog;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.Pin        = GPIO_PIN_10;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    /*INM*/
    GPIO_InitStructure.Pin = GPIO_PIN_5;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.Pin       = GPIO_PIN_0;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF8_COMP1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    /*PD2,PD3 as connect to INP,INM by external skip line*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.Pin       = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitPeripheral(GPIOD, &GPIO_InitStructure);
}
/**
 * @brief  Configure the TIM1 Pins.
 */
void GPIO_TimConfiguration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    /* Tim1 GPIOA Configuration: Channel 1, 2 and 3 as alternate function push-pull */
    GPIO_InitStructure.Pin        = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    /* GPIOB Configuration: Channel 1N, 2N and 3N as alternate function push-pull */
    GPIO_InitStructure.Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM1;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    /*CH4*/
    GPIO_InitStructure.Pin = GPIO_PIN_11;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    /*iom break if need*/
    GPIO_InitStructure.Pin = GPIO_PIN_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF5_TIM1;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    
    /*TIM8 CHx:PC6,PC7,PC8,PC9     CHxN:PA7,PB0,PB1 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF6_TIM8;
    GPIO_InitStructure.Pin       = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin = GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF6_TIM8;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin = GPIO_PIN_0;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF7_TIM8;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin = GPIO_PIN_1;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF0_TIM8;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
}

/**
 * @brief  Configures Vector Table base location.
 */
void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;

    /* Configure and enable ADC interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = COMP_1_2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

#ifdef USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param file pointer to the source file name
 * @param line assert_param error line source number
 */
void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}

#endif

/**
 * @}
 */

/**
 * @}
 */
