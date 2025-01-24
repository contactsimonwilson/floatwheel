1、功能说明

	1、此例程展示在 RT_Thread 系统创建 PIN 设备

2、使用环境

	/* 硬件环境：工程对应的开发硬件平台 */
	开发板：N32L43XM-STB N32L40XM-STB V1.1

3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
	SystemClock：64MHz
	GPIO:	LED:D1--PA8、D2--PB4
	KEY:	KEY1--PA4,KEY2--PA5,KEY3--PA6

	/* 描述Demo的测试步骤和现象 */
	1.编译后下载程序复位运行
	2.本例程创建三个线程，LED1 线程、 LED2 线程和key线程，LED1 线程用于控制 D1 500ms闪烁，LED2 线程用于控制 D2 250ms闪烁，
	  key线程用于监控KEY1、KEY2和KEY3状态，KEY3 按下触发中断，并在回调函数中打印日志。
    

4、 注意事项
    无

1. Function description
    This routine shows to create PIN devices on the RT_Thread system

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock：64MHz
	2. GPIO:	LED:D1--PA8、D2--PB4
	3. KEY:		KEY1--PA4,KEY2--PA5,KEY3--PA6
                     Log(USART1): TX--PA9 RX--PA10 Baud rate: 115200

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. This routine creates three threads, led1 thread, led2 thread key thread, led1 thread is used to control D1 500ms flashing, led2 thread is used to control D2 250ms flashing, 
            key thread detects KEY0, KEY1 and KEY2, When KEY3 is pressed, the interrupt callback function is called, and the corresponding log is printed when a key is pressed.

4. Matters needing attention
    None.