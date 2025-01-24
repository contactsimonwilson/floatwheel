1、功能说明

    该测例演示了USARTy与USARTz间实现串行IrDA低功耗模式红外解码功能的基础通信。
    首先，USARTy发送TxBuffer1数据至USARTz，USARTz通过中断接收数据存至RxBuffer1。
    随后，比较接收数据与发送数据，比较结果存入TransferStatus变量。
    USARTy和USARTz可以是USART1和USART2、USART3和UART4或UART4和UART5。


2、使用环境

	软件开发环境：KEIL MDK-ARM Professional Version 5.26.2.0

        硬件环境：最小系统板N32L40XML-STB_V1.0、IrDA发送器及接收器


3、使用说明
	
    系统时钟配置如下：
    - 时钟源 = HSE
    - 系统时钟 = 8MHz
    
    USART配置如下：
    - 波特率 = 2400 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 硬件流控制禁用（RTS和CTS信号）
    - 接收器和发送器使能
    - IrDA模式使能
    
    USART引脚连接如下：
    - USART1_Tx.PB8    <------->   IrDA Transmitter
    - USART2_Rx.PA3    <------->   IrDA Receiver
    或
    - USART3_Tx.PC10   <------->   IrDA Transmitter
    - UART4_Rx.PB15    <------->   IrDA Receiver
    或
    - UART4_Tx.PC10    <------->    IrDA Transmitter
    - UART5_Rx.PB5     <------->    IrDA Receiver
    
    - GPIO.PC1        <------->    38kHz carrier

    
    测试步骤与现象：
	- 复位运行MCU，查看变量TransferStatus，其中，PASSED为测试通过，FAILED为测试异常


4、注意事项

1. Function description

    This test example demonstrates the basic communication between USARTy and USARTz to realize the infrared 
	decoding function of serial IrDA low power consumption mode.
    First, USARTy sends TxBuffer1 data to USARTz, and USARTz receives data through interrupt and stores it in RxBuffer1.
    Subsequently, compare the received data with the sent data, and the result of the comparison is stored in the 
	TransferStatus variable.
    USARTy and USARTz can be USART1 and USART2, USART3 and UART4 or UART4 and UART5.


2. Use environment

        Software development environment: KEIL MDK-ARM Professional Version 5.26.2.0

        Hardware environment: minimum system board N32L40XML-STB_V1.0, IrDA transmitter and receiver


3. Instructions for use

    The system clock configuration is as follows:
    -Clock source = HSE
    -System clock = 8MHz
    
    The USART configuration is as follows:
    -Baud rate = 2400 baud
    -Word length = 8 data bits
    -1 stop bit
    -Verification control disabled
    -Hardware flow control disabled (RTS and CTS signals)
    -Receiver and transmitter enable
    -IrDA mode enable
    
    The USART pin connections are as follows:
    -USART1_Tx.PB8 <-------> IrDA Transmitter
    -USART2_Rx.PA3 <-------> IrDA Receiver
    or
    -USART3_Tx.PC10 <-------> IrDA Transmitter
    -UART4_Rx.PB15 <-------> IrDA Receiver
    or
    -UART4_Tx.PC10 <-------> IrDA Transmitter
    -UART5_Rx.PB5 <-------> IrDA Receiver
    
    -GPIO.PC1 <-------> 38kHz carrier

    
    Test steps and phenomena:
-Reset and run the MCU, check the variable TransferStatus, where PASSED means the test passed and FAILED means the test is abnormal


4. Matters needing attention