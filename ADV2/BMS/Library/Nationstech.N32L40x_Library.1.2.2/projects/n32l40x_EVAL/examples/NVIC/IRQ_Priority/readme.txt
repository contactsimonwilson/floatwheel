1、功能说明

	/* 简单描述工程功能 */
        这个例程配置并演示NVIC优先级设置


2、使用环境

	/* 硬件环境：工程对应的开发硬件平台 */
        开发板：N32L40XML-STBV1.0


3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
        SystemClock：64MHz

        USART：TX - PB4，波特率115200
	EXIT：PA0为浮空输入模式，外部中断线 - EXIT_LINE0，开启外部中断，优先级为0
	SysTick：中断优先级设置为0

	/* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.正常情况下打印SysTick中断信息，当按键外部中断和SysTick中断同时触发时，修改SysTick中断优先级为2，并打印相关信息，程序运行正常；


4、注意事项


1. Function description
	/* A brief description of the engineering function */
	This routine configures and demonstrates NVIC priority Settings

2. Use environment
	/* Hardware environment: the corresponding development hardware platform */
	Development board: N32L40XML-STBV1.0
        
3. Instructions for use    
	/* Describe the related module configuration method; For example: clock, I/O, etc. */
	SystemClock: 64 MHZ
	USART: TX-PB4, baud rate 115200
	EXIT: PA0 is floating input mode, external interrupt line -exit_line0, external interrupt is enabled, and the priority is 0
	SysTick: Set the interrupt priority to 0

	/* Describes the test steps and symptoms of Demo */
	1. Reset and run the downloaded program after compilation;
	2. In normal cases, SysTick interrupt information is displayed. If both the external interrupt and SysTick interrupt are triggered at the same time, change the SysTick interrupt priority to 2 and print related information.

4. Matters needing attention