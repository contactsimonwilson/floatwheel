1、功能说明

    该测例演示了LPUART与USARTz间通过DMA实现的基础通信。USARTz可以是USART3
或UART4。
    首先，DMA传输TxBuffer1数据至LPUART发送数据寄存器，随后数据发送至
USARTz。USARTz接收从DMA传来的数据，存至RxBuffer2。比较收、发数据，比较
结果存入TransferStatus2变量。
    同时，DMA传输TxBuffer2数据至USARTz发送数据寄存器，随后数据发送至
LPUART。LPUART接收从DMA传来的数据，存至RxBuffer1。比较收、发数据，比较
结果存入TransferStatus1变量。   


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
    - DMA发送模式和DMA接收模式使能
    
    USART配置如下：
    - 波特率 = 9600 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 硬件流控制禁用（RTS和CTS信号）
    - 接收器和发送器使能
    - DMA发送模式和DMA接收模式使能
    
    LPUART及USART引脚连接如下：
    - LPUART_Tx.PC10   <------->   USART3_Rx.PB11
    - LPUART_Rx.PC11   <------->   USART3_Tx.PB10
    或
    - LPUART_Tx.PA1    <------->   UART4_Rx.PB1
    - LPUART_Rx.PA0    <------->   UART4_Tx.PB0

    
    测试步骤与现象：
    - Demo在KEIL环境下编译后，下载至MCU
    - 复位运行，依次查看变量TransferStatus1和TransferStatus2，其中，
      PASSED为测试通过，FAILED为测试异常


4、注意事项

1. Function description

    This test example demonstrates basic communication between LPUART and USARTz via DMA. USARTz can be USART3
or UART4.
    First, the DMA transfers the TxBuffer1 data to the LPUART transmit data register, and then the data is sent to
USARTz. USARTz receives data from DMA and stores it in RxBuffer2. Compare incoming and outgoing data, compare
The result is stored in the TransferStatus2 variable.
    At the same time, the DMA transfers the TxBuffer2 data to the USARTz transmit data register, and then the data is sent to
LPUART. LPUART receives data from DMA and stores it in RxBuffer1. Compare incoming and outgoing data, compare
The result is stored in the TransferStatus1 variable.


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
    - DMA transmit mode and DMA receive mode enable
    
    USART is configured as follows:
    - Baud rate = 9600 baud
    - Word length = 8 data bits
    - 1 stop bit
    - checksum control disabled
    - Hardware flow control disabled (RTS and CTS signals)
    - Receiver and transmitter enable
    - DMA transmit mode and DMA receive mode enable
    
    The LPUART and USART pins are connected as follows:
    - LPUART_Tx.PC10 <-------> USART3_Rx.PB11
    - LPUART_Rx.PC11 <-------> USART3_Tx.PB10
    or
    - LPUART_Tx.PA1 <-------> UART4_Rx.PB1
    - LPUART_Rx.PA0 <-------> UART4_Tx.PB0

    
    Test steps and phenomena:
    - Demo is compiled in KEIL environment and downloaded to MCU
    - Reset operation, check the variables TransferStatus1 and TransferStatus2 in turn, where,
      PASSED is the test passed, FAILED is the test abnormal


4. Matters needing attention