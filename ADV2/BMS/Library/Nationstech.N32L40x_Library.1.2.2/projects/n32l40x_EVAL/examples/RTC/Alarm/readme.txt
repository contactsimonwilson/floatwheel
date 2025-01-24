1、功能说明
    1、通过设定闹钟时间来触发闹钟中断。
    2、通过闹钟标志位来配置IO输出

2、使用环境

    软件开发环境：KEIL MDK-ARM V5.25
    硬件环境：
        1、基于评估板N32L40XML-STB V1.0开发
        2、MCU：N32L406MBL7

3、使用说明
    
    系统配置:
        1、RTC时钟源：LSE
        2、闹钟IO输出：PC13
        3、串口配置：
                    - 串口为USART1（TX：PA9  RX：PA10）:
                    - 数据位：8
                    - 停止位：1
                    - 奇偶校验：无
                    - 波特率： 115200 
    使用方法：
        编译后烧录到评估板，上电，串口按照闹钟设定时间(间隔1min)打印输出。
        设置#define RTC_ALARM_TEST_TYPE RTC_ALARM_TEST_TYPE_OUTPUT，编译后烧录到评估板，
        此时会切换到闹钟输出，在PC13口会出现翻转电平。

4、注意事项
    无
    

1. Function description

	1. Trigger the alarm interrupt by setting the alarm time.
	2. Configure I/O output through the alarm flag

2. Use environment

	Software development environment: KEIL MDK-ARM V5.25
	Hardware environment:
		1. based on the evaluation board N32L40XML-STB V1.0 development
		2. MCU: N32L406MBL7

3. Instructions for use

	System configuration:
		1. RTC clock source: LSE
		2. alarm IO output: PC13
		3. Serial port configuration:

							- Serial port: USART1 (TX: PA9 RX: PA10) :
							- Data bit: 8
							- Stop bit: 1
							- Parity check: None
							- Baud rate: 115200

	Instructions:
		After compiling, it is burned to the evaluation board, powered on, and the serial port prints the output according to the time set by the alarm clock (1 minute by default).
		When set "#define RTC_ALARM_TEST_TYPE RTC_ALARM_TEST_TYPE_OUTPUT", at this time, the alarm clock output will be switched, and the flipped level will appear at port PC13.

4. Matters needing attention
	None

