1、功能说明

    该测例演示了LPUART与USARTz间使用硬件流控制通过中断实现的基础通信。
    LPUART发送TxBuffer1数据至USARTz，USARTz接收数据存至RxBuffer2。同时，
USARTz发送TxBuffer2数据至LPUART，LPUART接收数据存至RxBuffer1。
    随后，分别比较两组接收数据与发送数据，比较结果存入TransferStatus1变量
和TransferStatus2变量。


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
    - 硬件流控制使能（RTS和CTS信号）
    - 接收器和发送器使能
    
    USART配置如下：
    - 波特率 = 9600 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 硬件流控制使能（RTS和CTS信号）
    - 接收器和发送器使能
    
    LPUART及USART引脚连接如下：
    - LPUART_Tx.PB10    <------->   USART2_Rx.PA3
    - LPUART_Rx.PB11    <------->   USART2_Tx.PA2
    - LPUART_RTS.PB12    <------->   USART2_CTS.PA0
    - LPUART_CTS.PB13    <------->   USART2_RTS.PA1
    测试步骤与现象：
    - Demo在KEIL环境下编译后，下载至MCU
    - 复位运行，依次查看变量TransferStatus1和TransferStatus2，其中，
      PASSED为测试通过，FAILED为测试异常


4、注意事项

1. Function description

    This test example demonstrates basic communication between the LPUART and the USARTz via interrupts using hardware flow control.
    LPUART sends TxBuffer1 data to USARTz, and USARTz receives data and stores it in RxBuffer2. at the same time,
USARTz sends TxBuffer2 data to LPUART, and LPUART receives data and stores it in RxBuffer1.
    Then, compare the two groups of received data and sent data respectively, and store the comparison results in the TransferStatus1 variable.
and the TransferStatus2 variable.


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
    - Hardware flow control enable (RTS and CTS signals)
    - Receiver and transmitter enable
    
    USART is configured as follows:
    - Baud rate = 9600 baud
    - Word length = 8 data bits
    - 1 stop bit
    - checksum control disabled
    - Hardware flow control enable (RTS and CTS signals)
    - Receiver and transmitter enable
    
    The LPUART and USART pins are connected as follows:
    - LPUART_Tx.PB10 <-------> USART2_Rx.PA3
    - LPUART_Rx.PB11 <-------> USART2_Tx.PA2
    - LPUART_RTS.PB12 <-------> USART2_CTS.PA0
    - LPUART_CTS.PB13 <-------> USART2_RTS.PA1

    
    Test steps and phenomena:
    - Demo is compiled in KEIL environment and downloaded to MCU
    - Reset operation, check the variables TransferStatus1 and TransferStatus2 in turn, where,
      PASSED is the test passed, FAILED is the test abnormal


4. Matters needing attention