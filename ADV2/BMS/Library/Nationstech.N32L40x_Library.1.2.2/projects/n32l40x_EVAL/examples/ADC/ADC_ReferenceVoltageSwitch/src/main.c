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
 * @version v1.2.0
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "main.h"


ADC_InitType ADC_InitStructure;
__IO uint16_t ADCConvertedValue[5];

static ADC_REFERENCE_Volt ADCVrefType  = ADC_REFENCE_Volt_VREF;

void RCC_Configuration(void);
void GPIO_Configuration(void);
uint16_t ADC_GetData(uint8_t ADC_Channel);
void ADC_Initial(void);
uint8_t KEY_SCAN(void);

/**
 * @brief  Configures ADC.
 * @param none.
 */
void ADC_Initial(void)
{
    ADC_DeInit(ADC);
    /* ADC configuration ------------------------------------------------------*/
    ADC_InitStructure.MultiChEn      = DISABLE;
    ADC_InitStructure.ContinueConvEn = DISABLE;
    ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIGCONV_NONE;
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ChsNumber      = 1;
    ADC_Init(ADC, &ADC_InitStructure);

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
}


/**
 * @brief   Main program
 */
int main(void)
{
    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();
	
	/* ADC configuration ------------------------------------------------------*/
    ADC_Initial();

    while (1)
    {
        /* Detect key press,then swich VREFBUFF or VREF+ as ADC reference-------*/
		if(KEY_SCAN())
		{
			if(ADCVrefType == ADC_REFENCE_Volt_VREF)
				ADCVrefType = ADC_REFENCE_Volt_VREFBUFF;
			else
				ADCVrefType = ADC_REFENCE_Volt_VREF;
			
			Reference_Voltage_Switch(ADCVrefType);
		}
		ADCConvertedValue[0]=ADC_GetData(ADC_CH_11_PC0);
        ADCConvertedValue[1]=ADC_GetData(ADC_CH_12_PC1);
    }
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* Enable peripheral clocks ------------------------------------------------*/

    /* Enable GPIOA,GPIOC clocks */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOC, ENABLE);
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
    /* Configure PC0 PC1 as analog input -------------------------*/
    GPIO_InitStructure.Pin       = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Analog;
    GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);
	
	/* Configure PA4 as input key   ------------------------------*/
    GPIO_InitStructure.Pin       = GPIO_PIN_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input;
	GPIO_InitStructure.GPIO_Pull = GPIO_Pull_Up;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}
/**
 * @brief  Get the ADC conversion results.
 * @param  ADC_Channel the ADC channel to configure.
 * @return the ADC conversion result.
 */
uint16_t ADC_GetData(uint8_t ADC_Channel)
{
    uint16_t dat;
    ADC_ConfigRegularChannel(ADC, ADC_Channel, 1, ADC_SAMP_TIME_55CYCLES5);
    /* Start ADC Software Conversion */
    ADC_EnableSoftwareStartConv(ADC,ENABLE);
    while(ADC_GetFlagStatus(ADC,ADC_FLAG_ENDC)==0){
    }
    ADC_ClearFlag(ADC,ADC_FLAG_ENDC);
    ADC_ClearFlag(ADC,ADC_FLAG_STR);
    dat=ADC_GetDat(ADC);
    return dat;
}
/**
 * @brief  Inserts a delay time.
 * @param  count specifies the delay time length.
 */
static void delay(uint16_t n)
{
	uint16_t i=0,j=0;
	for( i = 0;i<n;i++)
		for( j = 0;j<20;j++){
	        __NOP();
			__NOP();
		}
}
/**
 * @brief  Key detection of KEY1(PA4).
 * @return Button PA4 button is pressed or not (1 or 0).
 */
uint8_t KEY_SCAN(void)
{
	uint8_t key_press = 0;
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_PIN_4) == RESET)
	{
		delay(4);
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_PIN_4) == RESET)
			key_press = 1;
	}

	return key_press;
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
