1、功能说明

	/* 简单描述工程功能 */
        这个例程配置并演示开启FLASH写保护


2、使用环境

	/* 硬件环境：工程对应的开发硬件平台 */
        开发板：N32L40XML-STBV1.0


3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
        SystemClock：64MHz

        USART：TX - PA9，RX - PA10，波特率115200

	/* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.开启FLASH写保护，查看串口信息，当FLASH数据写入失败时，打印信息为测试通过；


4、注意事项



1. Function description
	/* A brief description of the engineering function */
	This routine configures and demonstrates enabling FLASH write protection

2. Use environment
	/* Hardware environment: the corresponding development hardware platform */
	Development board: N32L40XML-STBV1.0
        
3. Instructions for use
    
	/* Describe the related module configuration method; For example: clock, I/O, etc. */
	SystemClock: 64 MHZ
	USART: TX-PA9, RX-PA10, baud rate 115200

	/* Describes the test steps and symptoms of Demo */
	1. Reset and run the downloaded program after compilation;
	2. Enable FLASH write protection and view information about the serial port. If data fails to be written to the FLASH, the test passes.

4. Matters needing attention