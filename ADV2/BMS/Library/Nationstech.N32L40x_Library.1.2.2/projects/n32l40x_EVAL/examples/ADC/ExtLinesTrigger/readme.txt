1、功能说明
    1、ADC规则通道采样PC2、PC3引脚的模拟电压，注入通道采样PA0、PA1引脚的模拟电压
    2、其中规则转换结果通过DMA_CH1通道读取到变量ADC_RegularConvertedValueTab[64]数组
        注入转换结果通过转换结束中断读取到变量ADC_InjectedConvertedValueTab[32]数组
2、使用环境
    软件开发环境：  KEIL MDK-ARM V5.26.2.0
    硬件环境：         基于N32L40XML-STB V1.0开发
3、使用说明
    系统配置；
        1、时钟源：
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,ADC CLK=64M/16,ADC 1M CLK=HSE/8,DMA CLK=64M
        2、中断：
            ADC注入转换结果完成中断打开，抢断优先级0，子优先级0
            中断处理接收注入转换结果到ADC_InjectedConvertedValueTab[32]数组
        3、端口配置：
            PC2选择为模拟功能ADC1转换通道
            PC3选择为模拟功能ADC1转换通道
            PA0选择为模拟功能ADC1转换通道
            PA1选择为模拟功能ADC1转换通道
            PD11选择为外部EXTI事件上升沿触发
            PA15选择为外部EXTI事件上升沿触发
        4、DMA：
            DMA_CH1通道循环模式搬运64个半字的ADC1规则通道转换结果到ADC_RegularConvertedValueTab[64]数组
        5、ADC：
            ADC规则通道扫描间断模式、EXTI11触发、12位数据右对齐，转换通道PC2和PC3的模拟电压数据
            ADC注入通道扫描模式、EXTI15触发、12位数据右对齐，转换通道PA0和PA1的模拟电压数据
    使用方法：
        1、编译后打开调试模式，将变量ADC_RegularConvertedValueTab[64],ADC_InjectedConvertedValueTab[32]添加到watch窗口观察
        2、通过PD11给上升沿可以触发规则通道数据采样，PA15给上升沿可以触发注入通道数据采样
4、注意事项
    当系统采用HSE时钟时（一般HSI也是打开的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV8)可以配置为HSE或者HSI
    当系统采样HSI时钟时（一般HSE是关闭的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV8)只能配置为HSI




1. Function description
    1. The ADC regular channel samples the analog voltage of the PC2 and PC3 pins, and the injection channel samples the analog voltage of the PA0 and PA1 pins
    2. The regular conversion result is read into the variable ADC_RegularConvertedValueTab[64] array through the DMA_CH1 channel
        The injected conversion result is read into the variable ADC_InjectedConvertedValueTab[32] array through the conversion end interrupt
2. Use environment
    Software development environment: KEIL MDK-ARM V5.26.2.0
    Hardware environment: Developed based on the development board N32L40XML-STB V1.0
3. Instructions for use
    System Configuration;
        1. Clock source:
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,ADC CLK=64M/16,ADC 1M CLK=HSE/8,DMA CLK=64M
        2. Interrupt:
            ADC injection conversion result completion interrupt open, steal priority 0, sub-priority 0
            The interrupt handler receives the injected conversion result into the ADC_InjectedConvertedValueTab[32] array
        3. Port configuration:
            PC2 is selected as the analog function, ADC1 conversion channel
            PC3 is selected as the analog function, ADC1 conversion channel
            PA0 is selected as the analog function, ADC1 conversion channel
            PA1 is selected as the analog function, ADC1 conversion channel
            PD11 is selected as external EXTI event rising edge trigger
            PA15 is selected as external EXTI event rising edge trigger
        4. DMA:
            DMA_CH1 channel is configured as circular mode, carries 64 half-word of ADC regular conversion channel results to the ADC_RegularConvertedValueTab[64] array
        5. ADC:
            ADC regular channel configuration: scan discontinuous mode, EXTI11 trigger, 12-bit data right alignment, convert analog voltage data of channels PC2 and PC3
            ADC injection channel configuration: scan mode, EXTI15 trigger, 12-bit data right alignment, convert analog voltage data of channels PA0 and PA1
    Instructions:
        1. Open the debug mode after compiling, and add the variables ADC_RegularConvertedValueTab[64], ADC_InjectedConvertedValueTab[32] to the watch window for observation
        2. The rising edge of PD11 can trigger regular channel data sampling, and the rising edge of PA15 can trigger injection channel data sampling
4. Matters needing attention
    When the system uses the HSE clock (HSI is generally enabled), ), RCC_ConfigAdc1mClk (RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV8) can be configured as HSE or HSI
    When the system uses the HSI clock(HSE is generally disabled), RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV8) can only be configured as HSI