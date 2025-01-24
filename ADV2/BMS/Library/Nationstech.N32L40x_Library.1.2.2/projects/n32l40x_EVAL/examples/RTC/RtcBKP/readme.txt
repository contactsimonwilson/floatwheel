1、功能说明
    1、BKP寄存器读写

2、使用环境

    软件开发环境：KEIL MDK-ARM V5.25
    硬件环境：
        1、基于评估板N32L40XML-STB V1.0开发
        2、MCU：N32L406MBL7


3、使用说明
    
    系统配置：
        1、RTC时钟源：LSE
        2、串口配置：
                    - 串口为USART1（TX：PA9  RX：PA10）:
                    - 数据位：8
                    - 停止位：1
                    - 奇偶校验：无
                    - 波特率： 115200 
    使用方法：
        编译后烧录到评估板，向BKP寄存器中写入数据，然后读出打印写入BKP寄存器中的数据

4、注意事项
    无


1. Function description

	1. The BKP register reads and writes

2. Use environment

	Software development environment: KEIL MDK-ARM V5.25
	Hardware environment:
		1. based on the evaluation board N32L40XML-STB V1.0 development
		2. MCU：N32L406MBL7

3. Instructions for use

	System configuration:

		1. RTC clock source: LSE
		2. Serial port configuration:

							- Serial port: USART1 (TX: PA9 RX: PA10) :
							- Data bit: 8
							- Stop bit: 1
							- Parity check: None
							- Baud rate: 115200

	Instructions:
		1. After compiling, it burns to the evaluation board, writes data to the BKP register, and then reads and prints the data written to the BKP register

4. Matters needing attention
	None