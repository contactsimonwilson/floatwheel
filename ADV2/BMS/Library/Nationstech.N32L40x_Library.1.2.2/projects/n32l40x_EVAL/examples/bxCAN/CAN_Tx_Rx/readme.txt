1、功能说明
    1、CAN发送接收例程


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.25

    硬件环境：
        1、基于评估板N32L40XML-STB_V1.0开发
        2、MCU：N32L406MB


3、使用说明
    
    系统配置；
    /* 描述相关模块配置方法；例如:时钟，I/O等 */
        SystemClock：108MHz
        USART：TX - PA9， RX - PA10，波特率115200
        CAN： RX - PB8， TX - PB9，波特率500K，正常模式

    /* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.查看串口打印信息，CAN每隔1s发送一帧标准帧和一帧扩展帧
          串口将MCU接收到的数据帧打印出来
                     
                 
4、注意事项


1. Function description
	1. CAN send and receive routines


2. Use environment

	Software development environment: KEIL MDK-ARM V5.25

	Hardware environment:
		1. Developed based on the evaluation board N32L40XML-STB_V1.0
		2. MCU: N32L406MB


3. Instructions for use
    
	 System Configuration;
	/* Describe related module configuration methods; for example: clock, I/O, etc. */
	SystemClock: 108MHz
	USART: TX - PA9, RX - PA10, baud rate 115200
	CAN: RX - PB8, TX - PB9, baud rate 500K, normally mode

	/* Describe the test steps and phenomena of the Demo */
	1. After compiling, download the program to reset and run;
	2. Check the serial port printing information, CAN sends a standard frame and an extended frame every 1s.
	The serial port prints out the extend frame received by the MCU
                     
                 
4. Matters needing attention