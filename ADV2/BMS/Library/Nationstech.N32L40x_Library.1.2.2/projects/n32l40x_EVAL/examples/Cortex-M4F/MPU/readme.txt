1、功能说明

	/* 简单描述工程功能 */
        这个例程配置并演示MPU内存保护功能


2、使用环境

	/* 硬件环境：工程对应的开发硬件平台 */
        开发板：N32L40XML-STBV1.0


3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
        SystemClock：64MHz

        USART：TX - PA9，RX - PA10，波特率115200

	/* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.查看串口打印信息，允许访问则打印允许访问信息，不允许访问则进入内存管理故障中断并打印不允许访问信息；


4、注意事项


1. Function description
	/* A brief description of the engineering function */
	This routine configures and demonstrates MPU memory protection

2. Use environment
	/* Hardware environment: the corresponding development hardware platform */
	Development board: N32L40XML-STBV1.0

3. Instructions for use    
	/* Describe the related module configuration method; For example: clock, I/O, etc. */
	SystemClock: 64 MHZ
	USART: TX-PA9, RX-PA10, baud rate 115200

	/* Describes the test steps and symptoms of Demo */
	1. Reset and run the downloaded program after compilation;
	2. View information about the serial port. If the serial port is allowed to access, the serial port 	displays information about access permission.

4. Matters needing attention