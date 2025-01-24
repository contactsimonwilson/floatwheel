1、功能说明

	该测例演示了LPUART与USARTz间通过查询检测标识实现的基础通信。USARTz
可以是USART1或UART4。
    首先，LPUART发送TxBuffer1数据至USARTz，USARTz接收数据存至RxBuffer1。
比较接收数据与发送数据，比较结果存入TransferStatus变量。
    随后，USARTz发送TxBuffer2数据至LPUART，LPUART接收数据存至RxBuffer2。
比较接收数据与发送数据，比较结果存入TransferStatus变量。


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
    
    USART配置如下：
    - 波特率 = 9600 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 硬件流控制禁用（RTS和CTS信号）
    - 接收器和发送器使能
    
    LPUART及USART引脚连接如下：
    - LPUART_Tx.PA4   <------->   USART1_Rx.PA10
    - LPUART_Rx.PA3   <------->   USART1_Tx.PA9
    或
    - LPUART_Tx.PB6   <------->   UART4_Rx.PD12
    - LPUART_Rx.PB7   <------->   UART4_Tx.PD13

    
    测试步骤与现象：
    - Demo在KEIL环境下编译后，下载至MCU
    - 复位运行，分两次查看变量TransferStatus，其中，PASSED为测试通过，
      FAILED为测试异常


4、注意事项

1. Function description

    This test example demonstrates basic communication between the LPUART and USARTz through query detection flag. 
    USARTz can be USART1 or UART4.
    First, LPUART sends TxBuffer1 data to USARTz, and USARTz receives data to RxBuffer1. 
Compare the received data with the sent data, and the comparison result is stored in the TransferStatus variable.
    Then, USARTz sends TxBuffer2 data to LPUART, and LPUART receives data to RxBuffer2.
Compare the received data with the sent data, and the comparison result is stored in the TransferStatus variable.


2. Use environment

        Software development environment: KEIL MDK-ARM Professional Version 5.26.2.0

        Hardware environment: minimum system board N32L40XML-STB_V1.0


3. Instructions for use

    The system clock configuration is as follows:
    - Clock source = HSE + PLL
    - System Clock = 108MHz
    
    The LPUART configuration is as follows:
    - Baud rate = 9600 baud
    - Word length = 8 data bits (fixed)
    - 1 stop bit (fixed)
    - checksum control disabled
    - Hardware flow control disabled (RTS and CTS signals)
    - Receiver and transmitter enable
    
    USART is configured as follows:
    - Baud rate = 9600 baud
    - Word length = 8 data bits
    - 1 stop bit
    - checksum control disabled
    - Hardware flow control disabled (RTS and CTS signals)
    - Receiver and transmitter enable
    
    The LPUART and USART pins are connected as follows:
    - LPUART_Tx.PA4   <------->   USART1_Rx.PA10
    - LPUART_Rx.PA3   <------->   USART1_Tx.PA9
    or
    - LPUART_Tx.PB6   <------->   UART4_Rx.PD12
    - LPUART_Rx.PB7   <------->   UART4_Tx.PD13

    
    Test steps and phenomena:
    - Demo is compiled in KEIL environment and downloaded to MCU
    - Resets the run and views the variable TransferStatus twice, where PASSED indicates that the test passes,
    FAILED indicates a test exception


4. Matters needing attention
