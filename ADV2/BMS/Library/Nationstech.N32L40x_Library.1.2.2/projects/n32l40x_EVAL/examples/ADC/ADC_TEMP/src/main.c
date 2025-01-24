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
#include <stdio.h>
#include "main.h"

/** @addtogroup ADC_ADC1_DMA
 * @{
 */

ADC_InitType ADC_InitStructure;
DMA_InitType DMA_InitStructure;
__IO uint16_t ADCConvertedValue;
USART_InitType USART_InitStructure;

void RCC_Configuration(void);
void Delay(__IO uint32_t nCount);
void USART_Config(void);


/*Vc0 is the ADC compensation value*/
#define Vc0        0    //X
/*Tc1 is the temprature compensation value*/
#define Tc1        1.5f
/*V30 is the voltage value at 30 degree Celsius by factory default*/ 
uint16_t  V30 = 0; 
uint16_t  ADvalue = 0;
uint32_t  temp = 0;

#ifdef  DEFINEFLOAT   //Float
__IO float TempValue;
/*xx mv per degree Celsius  by datasheet define*/
#define AVG_SLOPE  0.004f

/**
 * @brief  Cal temp use float result.
 */
float TempCal(uint16_t TempAdVal)
{
    float Temperate;
    /* Get the temperature inside the chip */
    Temperate=((V30+Vc0-TempAdVal)*3.3/4095)/AVG_SLOPE+30.0f-Tc1;
    return Temperate;
}
#else
__IO int16_t TempValue;
/*xx mv per degree Celsius  by datasheet define*/
#define AVG_SLOPE  4
/**
 * @brief  Cal temp use integer result.
 */
 
int16_t TempCal(uint16_t TempAdVal)
{
    int16_t Temperate;
    /* Get the temperature inside the chip */
    Temperate=(int16_t)((((V30+Vc0-TempAdVal)*33*1000)/(4095*10))/AVG_SLOPE+30-Tc1);
    return Temperate;
}
#endif

/**
 * @brief   Main program
 */
int main(void)
{
    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* DMA channel1 configuration ----------------------------------------------*/
    DMA_DeInit(DMA_CH1);
    DMA_InitStructure.PeriphAddr     = (uint32_t)&ADC->DAT;
    DMA_InitStructure.MemAddr        = (uint32_t)&ADCConvertedValue;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize        = 1;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_DISABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_HALFWORD;
    DMA_InitStructure.MemDataSize    = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.CircularMode   = DMA_MODE_CIRCULAR;
    DMA_InitStructure.Priority       = DMA_PRIORITY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
    DMA_Init(DMA_CH1, &DMA_InitStructure);
    DMA_RequestRemap(DMA_REMAP_ADC1, DMA, DMA_CH1, ENABLE);
    
    /* Enable DMA channel1 */
    DMA_EnableChannel(DMA_CH1, ENABLE);
    ADC_DeInit(ADC);
    /* ADC1 configuration ------------------------------------------------------*/
    ADC_InitStructure.MultiChEn      = ENABLE;
    ADC_InitStructure.ContinueConvEn = ENABLE;
    ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIGCONV_NONE;
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ChsNumber      = 1;
    ADC_Init(ADC, &ADC_InitStructure);
    /* ADC1 enable temperature  */
    ADC_EnableTempSensorVrefint( ENABLE);
    
    /* ADC1 regular ADC_CH_TEMP_SENSOR configuration */
    ADC_ConfigRegularChannel(ADC, ADC_CH_TEMP_SENSOR, 1, ADC_SAMP_TIME_239CYCLES5);
    /* Enable ADC DMA */
    ADC_EnableDMA(ADC, ENABLE);

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
    
    /* Config Uart1 as Temperature output */
    USART_Config();
    
    V30 = *(__IO uint32_t*)((uint32_t)0x1FFFF7D0);

    while (1)
    {
 
        /* */
        TempValue = TempCal(ADCConvertedValue);
        #ifdef DEFINEFLOAT
        printf("\r\n Temperature = %.3f C\r\n",TempValue); 
        #else
        printf("\r\n Temperature = %d C\r\n",TempValue); 
        #endif
        
         Delay(500);
    }
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* Enable peripheral clocks ------------------------------------------------*/
    /* Enable DMA clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA, ENABLE);

    /* Enable GPIOC clocks */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
    /* Enable ADC clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC, ENABLE);

    /* RCC_ADCHCLK_DIV16*/
    ADC_ConfigClk(ADC_CTRL3_CKMOD_AHB, RCC_ADCHCLK_DIV16);
    RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV8);  //selsect HSE as RCC ADC1M CLK Source		
}

/**
 * @brief  Delay funciton.
 */
void Delay(__IO uint32_t nCount)
{
	for(; nCount != 0; nCount--);
} 
/*
 * @brief  uart configure as 115200 8-N-1
 */
void USART_Config(void)
{
    GPIO_InitType GPIO_InitStructure;
    
    /* Enable GPIO clock */
    GPIO_APBxClkCmd(USARTx_GPIO_CLK, ENABLE);
    
    /* Enable USARTx Clock */
    USART_APBxClkCmd(USARTx_CLK, ENABLE);
    
    /* Initialize GPIO_InitStructure */
    GPIO_InitStruct(&GPIO_InitStructure);

    /* Configure USARTx Tx as alternate function push-pull */
    GPIO_InitStructure.Pin            = USARTx_TxPin;
    GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = USARTx_Tx_GPIO_AF;
    GPIO_InitPeripheral(USARTx_GPIO, &GPIO_InitStructure);
    
    /* Configure USARTx Rx as alternate function push-pull and pull-up */
    GPIO_InitStructure.Pin            = USARTx_RxPin;
    GPIO_InitStructure.GPIO_Pull      = GPIO_Pull_Up;
    GPIO_InitStructure.GPIO_Alternate = USARTx_Rx_GPIO_AF;
    GPIO_InitPeripheral(USARTx_GPIO, &GPIO_InitStructure);
    
    /* USARTy and USARTz configuration ------------------------------------------------------*/
    USART_InitStructure.BaudRate            = 115200;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;

    /* Configure USARTx */
    USART_Init(USARTx, &USART_InitStructure);
    /* Enable the USARTx */
    USART_Enable(USARTx, ENABLE);
}
/* retarget the C library printf function to the USART */
int fputc(int ch, FILE* f)
{
    USART_SendData(USARTx, (uint8_t)ch);
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TXDE) == RESET)
        ;

    return (ch);
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
