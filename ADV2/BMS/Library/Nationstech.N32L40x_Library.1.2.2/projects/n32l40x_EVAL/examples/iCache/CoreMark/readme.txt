1、功能说明

	/* 简单描述工程功能 */
        这个例程配置并演示MCU跑分测试


2、使用环境

	/* 硬件环境：工程对应的开发硬件平台 */
        开发板：N32L40XML-STBV1.0


3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
        SystemClock：64MHz

        USART：TX - PA9，RX - PA10，波特率115200
	SysTick：时钟滴答配置为1MS

	/* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.通过串口打印出跑分结果；


4、注意事项


1. Function description
	/* A brief description of the engineering function */
	This routine configures and demonstrates MCU running tests

2. Use environment
	/* Hardware environment: the corresponding development hardware platform */
	Development board: N32L40XML-STBV1.0
        
3. Instructions for use   
	/* Describe the related module configuration method; For example: clock, I/O, etc. */
	SystemClock：64MHz
	USART: TX-PA9, RX-PA10, baud rate 115200
	SysTick: clock tick is set to 1MS

	/* Describes the test steps and symptoms of Demo */
	1. Reset and run the downloaded program after compilation;
	2. Print the running result through the serial port;

4. Matters needing attention