1、功能说明
    1、通过检测PC13 IO 高电平触发入侵中断。

2、使用环境

    软件开发环境：KEIL MDK-ARM V5.25
    硬件环境：
        1、基于评估板N32L40XRL-STB V1.0开发
        2、MCU：N32L406RBL7

3、使用说明
    
    系统配置:
        1、时钟源：HSE/32
        2、入侵检测IO：PC13
        3、串口配置：
                    - 串口为USART1（TX：PA9  RX：PA10）:
                    - 数据位：8
                    - 停止位：1
                    - 奇偶校验：无
                    - 波特率： 115200 
    使用方法：
        1、编译后烧录到评估板，上电后，人为给PC13灌入高电平，串口输出RTC Tamper Interrupt。说明入侵检测发生了入侵中断
               
4、注意事项
    PC13配置为入侵检测浮空输入，N32L40XRL-STB V1.0 PC13 引脚输入电平不确定容易导致误触发RTC 入侵检测，
	为避免误触发，应该将PC13 固定为低电平


1. Function description

	1. Tamper interrupt is triggered by detecting PC13 IO high level.

2. Use environment

	Software development environment: KEIL MDK-ARM V5.25
	Hardware environment:
		1. based on the evaluation board N32G43XRL-STB V1.0 development
		2. MCU：N32L406RBL7

3. Instructions for use

	System configuration:

		1. RTC Clock source: HSE/32
        2. Tamper detection IO: PC13
		3. Serial port configuration:
							- Serial port: USART1 (TX: PA9 RX: PA10) :
							- Data bit: 8
							- Stop bit: 1
							- Parity check: None
							- Baud rate: 115200

	Instructions:
		1. After compiling, it is burned to the evaluation board. After powering on, high level is artificially injected into PC13 and "RTC Tamper interrupt" is output through the serial port. 
        It indicates that the tamper interrupt is detected
        
4. Matters needing attention
	PC13 is configured as an intrusion detection floating input, n32L40XRL-STB V1.0 PC13 pin input level is uncertain, which can easily trigger RTC tamper detection by mistake.
    PC13 should be fixed to low level to avoid accidental triggering