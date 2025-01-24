1、功能说明

	该测例演示了如何使用USART多处理器模式。USARTy和USARTz可以是USART1
和USART2、USART3和UART4或UART4和UART5。
    首先，分别设置USARTy和USARTz的地址为0x1和0x2。USARTy连续给USARTz
发送字符0x33。USARTz收到0x33，便翻转LED1、LED2和LED3的引脚。
    一旦KEY1_INT_EXTI_LINE线检测到上升沿，则产生EXTI0中断，在
EXTI0_IRQHandler中断处理函数中(the ControlFlag = 0)，USARTz进入静默
模式，在静默模式中，LED引脚停止翻转，直到KEY1_INT_EXTI_LINE线检测到
上升沿(the ControlFlag = 1)。在EXTI0_IRQHandler中断处理函数中，USARTy
发送地址0x102唤醒USARTz。LED引脚重新启动翻转。


2、使用环境

	软件开发环境：KEIL MDK-ARM Professional Version 5.26.2.0

        硬件环境：最小系统板N32L40XML-STB_V1.0


3、使用说明
	
	系统时钟配置如下：
    - 时钟源 = HSE + PLL
    - 系统时钟 = 64MHz
    
    USARTy配置如下：
    - 波特率 = 115200 baud
    - 字长 = 9数据位
    - 1停止位
    - 校验控制禁用
    - 硬件流控制禁用（RTS和CTS信号）
    - 接收器和发送器使能  
    
    
    USART引脚连接如下：    
    - USART1_Tx.PA9    <------->   USART2_Rx.PA3
    - USART1_Rx.PA10   <------->   USART2_Tx.PA2 
    或
    - USART3_Tx.PB10   <------->   UART4_Rx.PC11
    - USART3_Rx.PB11   <------->   UART4_Tx.PC10
    或
    - UART4_Tx.PD13    <------->   UART5_Rx.PB9
    - UART4_Rx.PD12    <------->   UART5_Tx.PB8   
    
    KEY1_INT_EXTI_LINE.PA0    <------->   WAKEUP_KEY
    
    LED1    <------->   PB5
    LED2    <------->   PB4
    LED3    <------->   PA8

    
    测试步骤与现象：
    - Demo在KEIL环境下编译后，下载至MCU
    - 复位运行，观察LED1~3是否处于闪烁状态
    - 按按键KEY，观察LED1~3是否停止闪烁
    - 再次按按键KEY，观察LED1~3是否恢复闪烁


4、注意事项

1. Function description

This test example demonstrates how to use the USART multi-processor mode. 
USARTy and USARTz can be USART1 and USART2, USART3 and UART4 or UART4 and UART5.
    First, set the addresses of USARTy and USARTz to 0x1 and 0x2 respectively. USARTy continuously sends the 
	character 0x33 to USARTz. When USARTz receives 0x33, it flips the pins of LED1, LED2, and LED3.
    Once the KEY1_INT_EXTI_LINE line detects the rising edge, the EXTI0 interrupt is generated, and the
    In the EXTI0_IRQHandler interrupt processing function (the ControlFlag = 0), USARTz enters the silent mode. 
	In the silent mode, the LED pin stops toggling until the KEY1_INT_EXTI_LINE line detects a rising edge (the ControlFlag = 1). 
	In the EXTI0_IRQHandler interrupt processing function, USARTy sends address 0x102 to wake up USARTz. The LED pin restarts toggling.


2. Use environment

        Software development environment: KEIL MDK-ARM Professional Version 5.26.2.0

        Hardware environment: minimum system board N32L40XML-STB_V1.0


3. Instructions for use

The system clock configuration is as follows:
    -Clock source = HSE + PLL
    -System clock = 64MHz
    
    The USARTy configuration is as follows:
    -Baud rate = 115200 baud
    -Word length = 9 data bits
    -1 stop bit
    -Verification control disabled
    -Hardware flow control disabled (RTS and CTS signals)
    -Receiver and transmitter enable
    
    
    The USART pin connections are as follows:
    -USART1_Tx.PA9 <-------> USART2_Rx.PA3
    -USART1_Rx.PA10 <-------> USART2_Tx.PA2
    or
    -USART3_Tx.PB10 <-------> UART4_Rx.PC11
    -USART3_Rx.PB11 <-------> UART4_Tx.PC10
    or
    -UART4_Tx.PD13 <-------> UART5_Rx.PB9
    -UART4_Rx.PD12 <-------> UART5_Tx.PB8
    
    KEY1_INT_EXTI_LINE.PA0 <-------> WAKEUP_KEY
    
    LED1 <-------> PB5
    LED2 <-------> PB4
    LED3 <-------> PA8

    
    Test steps and phenomena:
    -After the Demo is compiled in the KEIL environment, download it to the MCU
    -Reset operation, observe whether LED1~3 are blinking
    -Press the KEY button and observe whether LED1~3 stop flashing
    -Press the KEY button again and observe whether LED1~3 resume blinking


4. Matters needing attention