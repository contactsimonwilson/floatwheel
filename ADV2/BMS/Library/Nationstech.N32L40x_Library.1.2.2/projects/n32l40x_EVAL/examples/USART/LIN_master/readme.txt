1、功能说明
   此例程展示了USART模块LIN模式作主机节点轮询发送主机请求帧（0x3C,8字节数据0xF）和从机应答帧（0x3D）。


2、使用环境

    软件开发环境：KEIL MDK-ARM Professional Version 5.26.2.0

        硬件环境：最小系统板N32L40XML-STB_V1.0
                  LIN收发器模块（NXP1021T）


3、使用说明
    
    系统时钟配置如下：
    - 时钟源 = HSE + PLL
    - 系统时钟 = 108MHz
    
    USART配置如下：
    - 波特率 = 115200 baud
    - 字长 = 8数据位
    - 1停止位
    - 校验控制禁用
    - 硬件流控制禁用（RTS和CTS信号）
    - 接收器和发送器使能
    - LIN模式使能
    
    USART引脚连接如下：
    - LOG打印
    - USART1_Tx.PA9
    - USART1_Rx.PA10

    - USART LIN模式引脚	    LIN收发器
    - USART2_Tx.PB4    <--> Rx
    - USART2_Rx.PB5    <--> Tx
    
    测试步骤与现象：
        a，连接从机节点
        b，编译下载代码复位运行
        c，从串口看打印信息，
           主机机若接收到从机响应的从机应答帧（0x3D）将打印接收到的应答数据8字节的0x01


4、注意事项