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
#include "main.h"

#define ADC_CALDIF_ENABLE		0x00000004

ADC_InitType ADC_InitStructure;

__IO uint16_t ADCTempValue;
volatile static float VINP_VINN_Value = 0.0;   //(Vinp - Vinn ) Value

void RCC_Configuration(void);
void GPIO_Configuration(void);
void ADC_Differential_Channels_Config(ADC_Module* ADCx, uint32_t DIFSEL_CH);
void ADC_Differential_Mode_Enable(ADC_Module* ADCx);
/**
 * @brief   Main program
 */
int main(void)
{
    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    ADC_DeInit(ADC);
    /* ADC1 configuration ------------------------------------------------------*/
    ADC_InitStructure.MultiChEn      = DISABLE;
    ADC_InitStructure.ContinueConvEn = ENABLE;
    ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIGCONV_NONE;
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ChsNumber      = 1;
    ADC_Init(ADC, &ADC_InitStructure);
	 /* ADC1 regular channel2 configuration */
	ADC_ConfigRegularChannel(ADC, ADC_CH_2_PA1, 1, ADC_SAMP_TIME_55CYCLES5);
	/* Enable Different Mode */
	ADC_Differential_Channels_Config(ADC, ADC_DIFSEL_CHS_2);
	/* Enable Different Calibration Bit */
	ADC_Differential_Mode_Enable(ADC);
	
    /* Enable ADC */
    ADC_Enable(ADC, ENABLE);
    /* Check ADC Ready */
    while(ADC_GetFlagStatusNew(ADC,ADC_FLAG_RDY) == RESET)
        ;
    /* Start ADC1 calibration */
    ADC_StartCalibration(ADC);
    /* Check the end of ADC1 calibration */
    while (ADC_GetCalibrationStatus(ADC))
        ;

    /* Start ADC1 Software Conversion */
    ADC_EnableSoftwareStartConv(ADC, ENABLE);

    while (1)
    {
		if(ADC_GetFlagStatus(ADC,ADC_FLAG_ENDC) == SET)
		{
			ADC_ClearFlag(ADC,ADC_FLAG_ENDC);
			ADCTempValue = ADC_GetDat(ADC);
			/* Calcalate (Vinp - Vinn ) Value*/
			VINP_VINN_Value = (float)(((float)(ADCTempValue *2.0f /4095) - 1.0f) *3.3f);
		}

    }
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* Enable peripheral clocks ------------------------------------------------*/
    /* Enable GPIOA clocks */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    /* Enable ADC clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC, ENABLE);

    /* RCC_ADCHCLK_DIV16*/
    ADC_ConfigClk(ADC_CTRL3_CKMOD_AHB, RCC_ADCHCLK_DIV16);
    RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV8);  //selsect HSE as RCC ADC1M CLK Source		
}

/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    /* Configure PA1 (in2),PA2(in3)as analog input -----*/
    GPIO_InitStructure.Pin       = GPIO_PIN_2 | GPIO_PIN_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Analog;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}
/**
 * @brief  ADC_Differential_Channels_Config.
 * @param ADCx where x can be 1, 2 ,3 or 4 to select the ADC peripheral.
 * @param DifChs :
 *     @arg ADC_DIFSEL_CHS_1    
 *     @arg ADC_DIFSEL_CHS_2    
 *     @arg ADC_DIFSEL_CHS_3    
 *     @arg ADC_DIFSEL_CHS_4    
 *     @arg ADC_DIFSEL_CHS_5    
 *     @arg ADC_DIFSEL_CHS_6   
 *     @arg ADC_DIFSEL_CHS_7   
 *     @arg ADC_DIFSEL_CHS_8    
 *     @arg ADC_DIFSEL_CHS_9    
 *     @arg ADC_DIFSEL_CHS_10 
 *     @arg ADC_DIFSEL_CHS_11  
 *     @arg ADC_DIFSEL_CHS_12   
 *     @arg ADC_DIFSEL_CHS_13   
 *     @arg ADC_DIFSEL_CHS_14   
 *     @arg ADC_DIFSEL_CHS_15   
 *     @arg ADC_DIFSEL_CHS_16   
 *     @arg ADC_DIFSEL_CHS_17   
 *     @arg ADC_DIFSEL_CHS_18
 * @return none
*/
void ADC_Differential_Channels_Config(ADC_Module* ADCx, uint32_t DIFSEL_CH)
{
	assert_param(IsAdcModule(ADCx));
	/* Clear the ADC_DIFSEL DIFSEL[18:1] bit */
    ADCx->DIFSEL &= aDC_DIFSEL_CHS_MASK;
	/* Set the ADC_DIFSEL DIFSEL[18:1] bit */
	ADCx->DIFSEL |= DIFSEL_CH;
}
/**
 * @brief  ADC_Differential_Mode_Enable.
 * @param ADCx where x can be 1, 2 ,3 or 4 to select the ADC peripheral.
 * @return none
*/
void ADC_Differential_Mode_Enable(ADC_Module* ADCx)
{   
    /* Set the ADC_CTRL3 CALDIF bit */
    ADCx->CTRL3 |= ADC_CALDIF_ENABLE;
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
