1、功能说明

	/* 简单描述工程功能 */
        这个例程配置并演示直接对FLASH进行读写操作


2、使用环境

	/* 硬件环境：工程对应的开发硬件平台 */
        开发板：N32L40XML-STBV1.0


3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
        SystemClock：64MHz

        USART：TX - PA9，RX - PA10，波特率115200

	/* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.查看串口打印信息，当写入FLASH的数据与读取数据对比均相同时，打印信息为测试结束；


4、注意事项



1. Function description
	/* A brief description of the engineering function */
	This routine configures and demonstrates reading and writing directly to FLASH

2. Use environment
	/* Hardware environment: the corresponding development hardware platform */
	Development board: N32L40XML-STBV1.0
        
3. Instructions for use  
	/* Describe the related module configuration method; For example: clock, I/O, etc. */
	SystemClock: 64 MHZ
	USART: TX-PA9, RX-PA10, baud rate 115200

	/* Describes the test steps and symptoms of Demo */
	1. Reset and run the downloaded program after compilation;
	2. Check the information printed through the serial port. If the data written to the FLASH is the same as the data read from the FLASH, the test is complete.

4. Matters needing attention