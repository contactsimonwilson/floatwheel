1、功能说明
    1、通过RTC闹钟来唤醒SLEEP。
    2、串口打印进入退出状态

2、使用环境

    软件开发环境：KEIL MDK-ARM V5.25

    硬件环境：
        1、基于评估板N32L40XRL-STB V1.0开发
        2、MCU：N32L406RBL7


3、使用说明
    
    系统配置；
        1、RTC时钟源：LSI
        2、低功耗模式：SLEEP
        3、串口配置：
            - 串口为USART2（TX：PA9  RX：PA10）:
            - 数据位：8
            - 停止位：1
            - 奇偶校验：无


    使用方法：
        在KEIL下编译后烧录到评估板，通电，过了一会串口打印start low power，说明进入低功耗模式了。
        当串口打印输出Exit low power，说明此时闹钟唤醒SLEEP了。


4、注意事项
    无


1. Function description
    1. Wake up SLEEP through the RTC alarm clock.
    2. Serial port printing enters the exit state

2. Use environment
    Software development environment: KEIL MDK-ARM V5.25
    Hardware environment:
	1, based on the evaluation board N32L40XRL-STB V1.0 development
	2, MCU: N32L406RBL7

3. Instructions for use    
    System configuration;
	1. RTC clock source: LSI
	2. low power mode: SLEEP
	3. Serial port configuration
	- Serial port: USART2 (TX: PA9 RX: PA10) :
	- Data bit: 8
	- Stop bit: 1
	- Parity check: None
	- Baud rate: 115200
    Instructions:
	After compiling in KEIL, burn to the evaluation board, power on, after a while, the serial port prints start low power, indicating that it enters the low power mode.
	If Exit Low power is printed through the serial port, the alarm clock wakes up and sleeps.

4. Matters needing attention
    None