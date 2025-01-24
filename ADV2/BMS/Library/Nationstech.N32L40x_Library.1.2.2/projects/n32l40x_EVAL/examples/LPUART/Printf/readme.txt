1、功能说明

	该测例演示了LPUART与PC间通过查询检测标识实现的基础通信。
    重定向printf函数至LPUART，并使用printf函数输出消息至终端。


2、使用环境

	软件开发环境：KEIL MDK-ARM Professional Version 5.26.2.0

        硬件环境：最小系统板N32L40XML-STB_V1.0


3、使用说明
	
    系统时钟配置如下：
    - 时钟源 = HSE + PLL
    - 系统时钟 = 64MHz
    
    LPUART配置如下：
    - 波特率 = 9600 baud
    - 字长 = 8数据位（固定）
    - 1停止位（固定）
    - 校验控制禁用
    - 硬件流控制禁用（RTS和CTS信号）
    - 接收器和发送器使能
    
    LPUART引脚连接如下：
    - LPUART_Tx.PA1 
    
    测试步骤与现象：
    - Demo在KEIL环境下编译后，下载至MCU
    - 复位运行，查看串口打印信息


4、注意事项

1. Function description

This test example demonstrates the basic communication between the LPUART and the PC by querying the detection flag.
     Redirect the printf function to the LPUART, and use the printf function to output messages to the terminal.


2. Use environment

Software development environment: KEIL MDK-ARM Professional Version 5.26.2.0

         Hardware environment: minimum system board N32L40XML-STB_V1.0


3. Instructions for use

     The system clock configuration is as follows:
     - Clock source = HSE + PLL
     - System Clock = 64MHz
    
     The LPUART configuration is as follows:
     - Baud rate = 9600 baud
     - Word length = 8 data bits (fixed)
     - 1 stop bit (fixed)
     - checksum control disabled
     - Hardware flow control disabled (RTS and CTS signals)
     - Receiver and transmitter enable
    
     The LPUART pins are connected as follows:
     - LPUART_Tx.PA1
    
     Test steps and phenomena:
     - Demo is compiled in KEIL environment and downloaded to MCU
     - reset operation, view serial port printing information


4. Matters needing attention