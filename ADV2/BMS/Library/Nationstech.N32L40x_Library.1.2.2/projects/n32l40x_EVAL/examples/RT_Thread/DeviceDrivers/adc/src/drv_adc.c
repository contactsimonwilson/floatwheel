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
 * @file drv_adc.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "drv_adc.h"
#include "n32l40x.h"
#include "drv_gpio.h"

#ifdef RT_USING_ADC

static struct n32l40x_adc_config adc_config[] =
{
#ifdef RT_USING_ADC
    {
        "adc",
        ADC,
    },
#endif
};

static struct n32l40x_adc adc_obj[sizeof(adc_config) / sizeof(adc_config[0])] = {0};

static void n32l40x_adc_init(struct n32l40x_adc_config *config)
{
    ADC_InitType ADC_InitStructure;
    /* ADC configuration ------------------------------------------------------*/
    ADC_InitStructure.MultiChEn      = DISABLE;
    ADC_InitStructure.ContinueConvEn = DISABLE;
    ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIGCONV_NONE;
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ChsNumber      = 1;
    ADC_Init((ADC_Module*)config->adc_periph, &ADC_InitStructure);
    
    /* Enable ADC */
    ADC_Enable((ADC_Module*)config->adc_periph, ENABLE);
    /* Check ADC Ready */
    while(ADC_GetFlagStatusNew((ADC_Module*)config->adc_periph, ADC_FLAG_RDY) == RESET)
        ;
    /* Start ADC calibration */
    ADC_StartCalibration((ADC_Module*)config->adc_periph);
    /* Check the end of ADC calibration */
    while (ADC_GetCalibrationStatus((ADC_Module*)config->adc_periph));
}

static rt_err_t n32l40x_adc_enabled(struct rt_adc_device *device, rt_uint32_t channel, rt_bool_t enabled)
{
    if (channel > ADC_CH_18)
    {
        return RT_EINVAL;
    }
    return RT_EOK;
}

static rt_err_t n32l40x_adc_convert(struct rt_adc_device *device, rt_uint32_t channel, rt_uint32_t *value)
{
    struct n32l40x_adc_config *config;
    RT_ASSERT(device != RT_NULL);

    if (channel > ADC_CH_18)
    {
        return RT_EINVAL;
    }
    config = (struct n32l40x_adc_config *)(device->parent.user_data);
    
    ADC_ConfigRegularChannel((ADC_Module*)config->adc_periph, channel, 1, ADC_SAMP_TIME_239CYCLES5);
    
    /* Start ADC Software Conversion */
    ADC_EnableSoftwareStartConv((ADC_Module*)config->adc_periph, ENABLE);

    while(ADC_GetFlagStatus((ADC_Module*)config->adc_periph, ADC_FLAG_ENDC) == 0)
    {
    }
    ADC_ClearFlag((ADC_Module*)config->adc_periph, ADC_FLAG_ENDC);
    ADC_ClearFlag((ADC_Module*)config->adc_periph, ADC_FLAG_STR);
    *value=ADC_GetDat((ADC_Module*)config->adc_periph);
    
    return RT_EOK;
}

static struct rt_adc_ops n32l40x_adc_ops =
{
    .enabled = n32l40x_adc_enabled,
    .convert = n32l40x_adc_convert,
};

int rt_hw_adc_init(void)
{
    int i = 0;
    int result = RT_EOK;

#if defined(RT_USING_ADC)
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC, ENABLE);
    /* Configure PC.00 PC.01 as analog input -------------------------*/
	GPIOInit(GPIOC, GPIO_Mode_Analog, GPIO_No_Pull, GPIO_PIN_0 | GPIO_PIN_1, GPIO_NO_AF);
#endif /* RT_USING_ADC */
    
    /* RCC_ADCHCLK_DIV16*/
    ADC_ConfigClk(ADC_CTRL3_CKMOD_AHB, RCC_ADCHCLK_DIV16);
	RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV8);  //selsect HSE as RCC ADC1M CLK Source
    
    for (i = 0; i < sizeof(adc_obj) / sizeof(adc_obj[0]); i++)
    {
        adc_obj[i].config = &adc_config[i];
        n32l40x_adc_init(&adc_config[i]);
        rt_hw_adc_register(&adc_obj[i].adc_device, \
                           adc_obj[i].config->name, &n32l40x_adc_ops, adc_obj[i].config);
    }
    return result;
}

INIT_DEVICE_EXPORT(rt_hw_adc_init);

#endif /* RT_USING_ADC */

