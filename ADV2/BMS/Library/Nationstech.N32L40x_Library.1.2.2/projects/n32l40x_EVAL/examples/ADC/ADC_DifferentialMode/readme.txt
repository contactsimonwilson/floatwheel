1、功能说明
    1、该例程介绍如何配置和使用ADC转换差分模式下的外部模拟输入即VinN和VinP上的外部电压差。

2、使用环境
    软件开发环境：  KEIL MDK-ARM V5.34.0.0
    硬件环境：      基于N32L40XML-STB V1.0开发
3、使用说明
    系统配置；
        1、时钟源：
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,ADC CLK=64M/16,ADC 1M CLK=HSE/8
        2、端口配置：
            模拟功能ADC VinP选用PA1,VinN选用PA2。
        3、ADC：
            ADC连续转换、扫描模式、软件触发、12位数据右对齐。
    使用方法：
        1、编译后打开调试模式，将变量ADCConvertedValue添加到watch窗口观察;
		2、用户可将ADC_CH2引脚(PA1、PA2)接入外置电源，进行变压操作，电压范围在-3V3到3V3之间;
        3、通过改变PA1，PA2引脚的电压，可以看到转换结果变量 "VINP_VINN_Value" 同步改变。
4、注意事项
    当系统采用HSE时钟时（一般HSI也是打开的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV8)可以配置为HSE或者HSI
    当系统采样HSI时钟时（一般HSE是关闭的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV8)只能配置为HSI


1. Function description
    This example describes how to configure and use the ADC to convert an external analog input in Differential Mode, 
	difference between external voltage on VinN and VinP.
2. Use environment
    Software development environment: KEIL MDK-ARM V5.34.0.0
    Hardware environment: Developed based on the evaluation board N32L40XML-STB V1.0
3. Instructions for use
    System configuration：
       1. Clock source:
              HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,ADC CLK=64M/16,ADC 1M CLK=HSE/8
       2. Port Configuration:
              PA1 is selected as the analog function ADC VinP,PA2 is selected as the analog function ADC VinN.
       3. the ADC:
              ADC continuous conversion, different mode, scan mode, software trigger, 12 bit data right aligned.
    Usage:
       1. After compiling, open the debugging mode and add the variable gCntAwdg to the Watch window 
           for observation.
       2. User can connect ADC_CHANNEL_2 pins (PA1, PA2) to external power supply  and vary voltage
           between -3V3 to 3V3.
       3. By changing the voltage of the PA1,PA2 pin, you can see that the conversion result variable "VINP_VINN_Value" changes synchronously.
4. Precautions
       When the system uses the HSE clock (HSI is also normally turned on), RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, 
       RCC_ADC1MCLK_DIV8)can be configured as HSE or HSI.
       When the system samples the HSI clock (generally, HSE is disabled), RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, 
       RCC_ADC1MCLK_DIV8) can only be set to HSI.