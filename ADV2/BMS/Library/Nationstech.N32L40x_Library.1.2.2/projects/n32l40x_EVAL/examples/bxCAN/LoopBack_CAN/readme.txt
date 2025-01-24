1、功能说明

	/* 简单描述工程功能 */
        这个例程配置并演示CAN在环回测试模式下收发CAN报文情况


2、使用环境

        软件开发环境：
        IDE工具：KEIL MDK-ARM 5.26
    
        硬件环境：
        开发板 N32L40XML-STB_V1.0


3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
        SystemClock：64MHz
        USART：TX - PA9， RX - PA10，波特率115200
	    CAN： RX - PA11，TX - PA12，波特率500K，环回测试模式

	/* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.查看串口打印信息，CAN把发送的报文当做接收的报文并保存，当查看到打印信息为接收通过时程序运行正常；


4、注意事项


1. Function description

	/* Briefly describe the project function */
	This routine configures and demonstrates CAN sending and receiving CAN messages in loopback test mode


2. Use environment

	Software development environment:
	IDE tool: KEIL MDK-ARM 5.26
    
	Hardware environment:
	Development Board N32L40XML-STB_V1.0


3. Instructions for use

	/* Describe related module configuration methods; for example: clock, I/O, etc. */
	SystemClock: 64MHz
	USART: TX - PA9, RX - PA10, baud rate 115200
	CAN: RX - PA11, TX - PA12, baud rate 500K, loopback test mode

	/* Describe the test steps and phenomena of the Demo */
	1. After compiling, download the program to reset and run;
	2. Check the serial port printing information, CAN regards the sent message as the received message and saves it, and the program runs normally when the printing information is viewed as received;


4. Matters needing attention

