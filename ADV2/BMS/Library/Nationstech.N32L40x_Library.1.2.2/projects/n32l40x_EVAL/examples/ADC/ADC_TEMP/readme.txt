1、功能说明
    1、ADC采样转换内部温度传感器的模拟电压，并转换为温度值
2、使用环境
    软件开发环境：  KEIL MDK-ARM V5.26.2.0
    硬件环境：        基于N32L40XML-STB V1.0开发
3、使用说明
    系统配置；
        1、时钟源：
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,ADC CLK=64M/16,ADC 1M CLK=HSE/8,DMA CLK=64M
        2、DMA：
            DMA_CH1通道回环模式搬运一个半字的ADC转换结果到ADCConvertedValue变量
        3、ADC：
            ADC连续转换、软件触发、12位数据右对齐，转换通道17即内部温度传感器的模拟电压数据
        4、端口配置：
            PA9选择为USART1的TX引脚
            PA10选择为USART1的RX引脚
        5、USART：
            USART1 115200波特率、8位数据位、1位停止位、无奇偶校验位、无硬件流控、发送和接收使能
        6、功能函数：
            TempValue = TempCal(ADCConvertedValue)函数将温度ADC原始格式数据转为度的单位的格式
    使用方法：
        1、编译后打开调试模式，将变量ADCConvertedValue,TempValue添加到watch窗口观察
        2、将串口工具连接到PA9引脚，并打开串口接收工具
        3、全速运行，可以看到温度变量的数值在常温下接近25度左右，同时串口工具显示实时芯片内的温度值
4、注意事项
    当系统采用HSE时钟时（一般HSI也是打开的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV8)可以配置为HSE或者HSI
    当系统采样HSI时钟时（一般HSE是关闭的），RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV8)只能配置为HSI


1. Function description
    1. The ADC samples and converts the analog voltage of the internal temperature sensor and converts it into a temperature value
2. Use environment
    Software development environment: KEIL MDK-ARM V5.26.2.0
    Hardware environment: Developed based on the development board N32L40XML-STB V1.0
3. Instructions for use
    System Configuration;
        1. Clock source:
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,ADC CLK=64M/16,ADC 1M CLK=HSE/8,DMA CLK=64M
        2. DMA:
            DMA_CH1 channel is configuered as circular mode, carries a half-word of ADC1 conversion result to the ADCConvertedValue variable
        3. ADC:
            ADC configuration: continuous conversion, software trigger, right-aligned 12-bit data, conversion channel 17 is the analog voltage data of the internal temperature sensor
        4. Port configuration:
            PA9 is selected as the TX pin of USART1
            PA10 is selected as the RX pin of USART1
        5. USART:
            USART1 configuration: 115200 baud rate, 8 data bits, 1 stop bit, no parity, no hardware flow control, transmit and receive enable
        6. Function function:
            TempValue = TempCal(ADCConvertedValue) function converts the temperature ADC raw format data to the format of the unit of degrees
    Instructions:
        1. Open the debug mode after compiling, and add the variables ADCConvertedValue and TempValue to the watch window to observe
        2. Connect the serial port tool to the PA9 pin, and open the serial port receiving tool
        3. Running at full speed, you can see that the value of the temperature variable is close to 25 degrees at room temperature, and the serial port tool displays the temperature value in the real-time chip
4. Matters needing attention
    When the system uses the HSE clock (HSI is generally enabled), ), RCC_ConfigAdc1mClk (RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV8) can be configured as HSE or HSI
    When the system uses the HSI clock(HSE is generally disabled), RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSI, RCC_ADC1MCLK_DIV8) can only be configured as HSI