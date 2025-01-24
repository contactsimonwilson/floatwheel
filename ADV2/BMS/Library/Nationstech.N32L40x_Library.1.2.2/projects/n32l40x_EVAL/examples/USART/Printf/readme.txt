1、功能说明

	该测例演示了USARTx与PC间通过查询检测标识实现的基础通信。
    重定向printf函数至USARTx，并使用printf函数输出消息至终端。
    USARTx可以是USART1或USART2。


2、使用环境

	软件开发环境：KEIL MDK-ARM Professional Version 5.26.2.0

        硬件环境：最小系统板N32L40XML-STB_V1.0


3、使用说明
	
    系统时钟配置如下：
    - 时钟源 = HSE + PLL
    - 系统时钟 = 64MHz
    
    USART配置如下：
    - 波特率 = 115200 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 硬件流控制禁用（RTS和CTS信号）
    - 接收器和发送器使能
    
    USART引脚连接如下：
    - USART1_Tx.PA9 
    或
    - USART2_Tx.PA2
    
    测试步骤与现象：
    - Demo在KEIL环境下编译后，下载至MCU
    - 复位运行，查看串口打印信息


4、注意事项

1. Function description

This test example demonstrates the basic communication between USARTx and PC by querying the detection identification.
     Redirect the printf function to USARTx, and use the printf function to output messages to the terminal.
     USARTx can be USART1 or USART2.


2. Use environment

     Software development environment: KEIL MDK-ARM Professional Version 5.26.2.0

     Hardware environment: minimum system board N32L40XML-STB_V1.0


3. Instructions for use

     The system clock configuration is as follows:
     -Clock source = HSE + PLL
     -System clock = 64MHz
    
     The USART configuration is as follows:
     -Baud rate = 115200 baud
     -Word length = 8 data bits
     -1 stop bit
     -Verification control disabled
     -Hardware flow control disabled (RTS and CTS signals)
     -Receiver and transmitter enable
    
     The USART pin connections are as follows:
     -USART1_Tx.PA9
     or
     -USART2_Tx.PA2
    
     Test steps and phenomena:
     -After the Demo is compiled in the KEIL environment, download it to the MCU
     -Reset operation, view serial port print information


4. Matters needing attention