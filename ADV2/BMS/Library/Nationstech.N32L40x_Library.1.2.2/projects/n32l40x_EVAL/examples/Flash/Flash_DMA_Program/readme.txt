1、功能说明

	/* 简单描述工程功能 */
        这个例程配置并演示使用DMA将SRAM数据写入FLASH


2、使用环境

	/* 硬件环境：工程对应的开发硬件平台 */
        开发板：N32L40XML-STBV1.0


3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
        SystemClock：64MHz

        USART：TX - PA9，RX - PA10，波特率115200
	DMA：数据传输方向为SRAM到FLASH

	/* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.查看串口打印信息，对比传输完成后的SRAM及FLASH数组数据，完全相同则打印信息为测试通过，程序运行正常；


4、注意事项


1. Function description
	/* A brief description of the engineering function */
	This routine configures and demonstrates the use of DMA to write SRAM data to FLASH

2. Use environment
	/* Hardware environment: the corresponding development hardware platform */
	Development board: N32L40XML-STBV1.0
        
3. Instructions for use
    
	/* Describe the related module configuration method; For example: clock, I/O, etc. */
	SystemClock: 64 MHZ
	USART: TX-PA9, RX-PA10, baud rate 115200
	DMA: Data transfer from SRAM to FLASH

	/* Describes the test steps and symptoms of Demo */
	1. Reset and run the downloaded program after compilation;
	2. Check the serial port printed information and compare the SRAM and FLASH array data after transmission. If the printed information is identical, the test is passed and the program runs normally.

4. Matters needing attention