1、功能说明

	该测例演示了LPUART如何通过与PC的通信唤醒STOP2模式。
    MCU进入STOP2模式，再由PC发送正确的数据唤醒MCU。当识别到正确的唤醒事件
时，WUF中断将触发并唤醒MCU。
    为了确认是否唤醒，MCU将发送确认消息给PC，并由PC检查是否是预期的消息。
    流程将重复4次进行，以验证不同的唤醒事件：
    1 起始位检测
    2 接收缓冲器非空检测
    3 一个可配置的接收字节
    4 一个科编程的4字节帧
    

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
    - LPUART_Tx.PC10   
    - LPUART_Rx.PC11     

    
    测试步骤与现象：
    - Demo在KEIL环境下编译后，下载至MCU
    - 复位运行，查看串口打印信息，通过串口发送相应的字符，唤醒MCU，再次
      查看串口打印信息（提示“唤醒”），该步骤需重复4次


4、注意事项

1. Function description

This test case demonstrates how the LPUART wakes up from STOP2 mode by communicating with the PC.
    The MCU enters the STOP2 mode, and then the PC sends the correct data to wake up the MCU. When the correct wake-up event is recognized
, the WUF interrupt will trigger and wake up the MCU.
    In order to confirm whether to wake up, the MCU will send a confirmation message to the PC, and the PC will check whether it is the expected message.
    The process will be repeated 4 times to verify different wake-up events:
    1 Start bit detection
    2 Receive buffer non-empty detection
    3 A configurable receive byte
    4 A section of programmed 4-byte frames
    

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
    - LPUART_Tx.PC10
    - LPUART_Rx.PC11

    
    Test steps and phenomena:
    - Demo is compiled in KEIL environment and downloaded to MCU
    - Reset operation, check the printing information of the serial port, send the corresponding characters through the serial port, wake up the MCU, and again
      Check the serial port printing information (prompt "wake up"), this step needs to be repeated 4 times


4. Matters needing attention
