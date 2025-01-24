1、功能说明

	1、此例程展示在 RT_Thread 系统创建 ADC 设备

2、使用环境

	/* 硬件环境：工程对应的开发硬件平台 */
	开发板：N32L43XM-STB N32L40XM-STB V1.1

3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
	SystemClock：64MHz
	GPIO:	
	LED:   D1--PA8、D2--PB4
    ADC:
				PA5选择为模拟功能ADC1转换通道
           		PA6选择为模拟功能ADC1转换通道
			
  	  日志：  USART1: TX--PA9  RX--PA10    波特率：115200

	/* 描述Demo的测试步骤和现象 */
	1.编译后下载程序复位运行
    2.本例程在main()里面创建两个线程，test0 线程和 test1 线程，test0 线程用于控制 D1 500ms闪烁，
      在test1线程中测试ADC设备,测量PA5和PA6引脚电压，通过串口打印结果。

4、注意事项
	无

1. Function description
    This routine shows how to create an ADC device on the RT_Thread system

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock：64MHz
	2. GPIO:	
	3. LED:   	D1--PA8、D2--PB4
        4. ADC:
        		PA5 is selected as the analog function ADC1 conversion channel
                        PA6 is selected as the analog function ADC1 conversion channel
         Log: TX--PA9 RX--PA10 Baud rate: 115200

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. This routine creates two threads in main(), test0 thread and test1 thread, test0 thread is used to control D1 500ms flashing, 
            test the ADC device in test1 thread, measure the pin voltage of PA5 and PA6, and print the result through serial port

4. Matters needing attention
    None.