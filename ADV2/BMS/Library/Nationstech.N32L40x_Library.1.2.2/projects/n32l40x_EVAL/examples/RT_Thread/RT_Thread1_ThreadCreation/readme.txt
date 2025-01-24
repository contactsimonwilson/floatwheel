1、功能说明

	1、此例程展示在 RT_Thread 系统创建线程

2、使用环境

	/* 硬件环境：工程对应的开发硬件平台 */
	开发板：N32L43XM-STB N32L40XM-STB V1.1

3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
	SystemClock：64MHz
	GPIO：PA8 控制 LED(D1) 闪烁；PB4 控制 LED(D2) 闪烁；


	/* 描述Demo的测试步骤和现象 */
	1.编译后下载程序复位运行
    2.本例程在main()里面创建两个线程，LED1 线程和 LED2 线程，LED1 线程用于控制 D1 1s闪烁，LED2 线程用于控制 D2 500ms闪烁，以此循环
	
4、注意事项
	无
1. Function description
    This example shows how to create a thread in the RT_Thread system

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock: 64MHz
        2. GPIO: 
                    PA8 controls the LED (D1) to blink; PB4 controls the LED (D2) to blink;

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. This routine creates two threads in main (), LED1 thread and LED2 thread. LED1 thread is used to control D1 1s flashing, and LED2 thread is used to control D2 500ms flashing, so as to cycle

4. Matters needing attention
    None.