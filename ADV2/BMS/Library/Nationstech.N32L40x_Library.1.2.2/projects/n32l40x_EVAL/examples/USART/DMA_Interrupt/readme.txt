1、功能说明

    该测例演示了USARTy与USARTz间通过DMA实现的基础通信。USARTy和USARTz
可以是USART1和USART2、USART3和UART4或UART4和UART5。
    首先，DMA传输TxBuffer1数据至USARTy发送数据寄存器，随后数据发送至
USARTz。USARTz利用中断接收数据，存至RxBuffer2。
    同时，DMA传输TxBuffer2数据至USARTz发送数据寄存器，随后数据发送至
USARTy。USARTy通过查询检查标志接收数据，存至RxBuffer1。
    最后，分别比较两组收、发数据，比较结果存入TransferStatus1变量
和TransferStatus2变量。


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
    - DMA发送模式使能，DMA接收模式禁用
    
    USART引脚连接如下：
    - USART1_Tx.PB8    <------->   USART2_Rx.PB5
    - USART1_Rx.PB7    <------->   USART2_Tx.PB4 
    或
    - USART3_Tx.PC10   <------->   UART4_Rx.PB15
    - USART3_Rx.PC11   <------->   UART4_Tx.PB14
    或
    - UART4_Tx.PD13    <------->   UART5_Rx.PB9
    - UART4_Rx.PD12    <------->   UART5_Tx.PB8

    
    测试步骤与现象：
    - Demo在KEIL环境下编译后，下载至MCU
    - 复位运行，依次查看变量TransferStatus1和TransferStatus2，其中，
      PASSED为测试通过，FAILED为测试异常


4、注意事项

1. Function description

    This test example demonstrates the basic communication between USARTy and USARTz through DMA. 
	USARTy and USARTz can be USART1 and USART2, USART3 and UART4 or UART4 and UART5.
    First, DMA transfers TxBuffer1 data to the USARTy send data register, and then the data is sent to USARTz. 
	USARTz uses interrupts to receive data and store it in RxBuffer2.
    At the same time, DMA transfers TxBuffer2 data to the USARTz send data register, and then the data is sent to 
	USARTy. USARTy receives data by querying the check mark and storing it in RxBuffer1.
    Finally, compare the two groups of receiving and sending data respectively, and store the comparison results 
	in the TransferStatus1 variable and the TransferStatus2 variable.


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
    -DMA transmission mode is enabled, DMA reception mode is disabled
    
    The USART pin connections are as follows:
    -USART1_Tx.PB8 <-------> USART2_Rx.PB5
    -USART1_Rx.PB7 <-------> USART2_Tx.PB4
    or
    -USART3_Tx.PC10 <-------> UART4_Rx.PB15
    -USART3_Rx.PC11 <-------> UART4_Tx.PB14
    or
    -UART4_Tx.PD13 <-------> UART5_Rx.PB9
    -UART4_Rx.PD12 <-------> UART5_Tx.PB8

    
    Test steps and phenomena:
    -After the Demo is compiled in the KEIL environment, download it to the MCU
    -Reset operation, check the variables TransferStatus1 and TransferStatus2 in turn, among them,
      PASSED means the test passed, FAILED means the test is abnormal


4. Matters needing attention