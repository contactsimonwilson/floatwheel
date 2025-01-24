1、功能说明

	该测例演示了USART2与智能卡间基础通信，查询智能卡随机数


2、使用环境

	软件开发环境：KEIL MDK-ARM Professional Version 5.26.2.0

        硬件环境：最小系统板N32L40XM-STB_V1.1，智能卡，智能卡座


3、使用说明
	
    系统时钟配置如下：
    - 时钟源 = HSE + PLL
    - 系统时钟 = 108MHz
    - 智能卡工作时钟 = 2.7MHz
    
    USART2配置如下：
    - 波特率 =  (根据设置的智能卡工作时钟配置)
    - 字长 = 8数据位
    - 1.5停止位
    - 校验控制 even
    - 硬件流控制禁用（RTS和CTS信号）
    - 接收器和发送器使能

    打印信息USART1配置如下：
    - 波特率 = 115200 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 硬件流控制禁用（RTS和CTS信号）
    - 接收器和发送器使能    
    
    USART引脚连接如下：

    - USART2_Tx.PA2    <-------> SMART_CARD I/O
    - USART2_CLK.PA4   <-------> SMART_CARD CLK   
    - SC_PIN_RESET.PC7 <-------> SMART_CARD RST
    - 3V3 	       <-------> SMART_CARD Vcc
    
    测试步骤与现象：
    - Demo在KEIL环境下编译后，下载至MCU
    - 复位运行，查看串口打印信息


4、注意事项