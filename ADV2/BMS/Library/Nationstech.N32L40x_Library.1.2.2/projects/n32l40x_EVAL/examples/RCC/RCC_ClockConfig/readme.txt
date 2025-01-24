1、功能说明

	/* 简单描述工程功能 */
        这个例程配置并演示设置不同的系统时钟，并用MCO从PA8输出出来


2、使用环境

	/* 硬件环境：工程对应的开发硬件平台 */
        开发板：N32L40XML-STBV1.0


3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
        SystemClock：64MHz

        USART：TX - PB4，波特率115200
	GPIO：PA8 - 复用为MC0时钟输出

	/* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.分别配置系统时钟为HSI、HSE、PLL，分别使用串口打印出当前SYSCLK、HCLK、PCLK1、PCLK2等信息，并且可以使用PA8复用引脚输出时钟，用示波器查看；


4、注意事项
   PLL输出频率必须大于等于32MHz


1. Function description

    /* Briefly describe the engineering function */
        This example configures and demonstrates setting different system clocks, and uses MCO to output from PA8


2. Use environment

    /* Hardware environment: the development hardware platform corresponding to the project */
        Development board: N32L40XML-STBV1.0
        

3. Instructions for use
    
    /* Describe the configuration method of related modules; for example: clock, I/O, etc. */   
    	SystemClock：64MHz
	
        USART: TX-PB4, baud rate 115200
        GPIO: PA8-multiplexed as MC0 clock output

    /* Describe the test steps and phenomena of Demo */
        1. After compiling, download the program to reset and run;
        2. Configure the system clock as HSI, HSE, and PLL, respectively, use the serial port to print out the current SYSCLK, HCLK, PCLK1, PCLK2 and other information, and use the PA8 multiplex pin to output the clock and view it with an oscilloscope;


4. Matters needing attention
   The PLL frequency must be greater than or equal to 32MHz