1、功能说明

	1、此例程展示在 RT_Thread 系统创建 CAN 设备

2、使用环境

	/* 硬件环境：工程对应的开发硬件平台 */
	开发板：N32L43XM-STB N32L40XM-STB V1.1

3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
	SystemClock：64MHz
	GPIO:	
		LED:	D1--PA8
    CAN:    RX--PB8
			TX--PB9
    串口(USART1):   TX--PA9

	/* 描述Demo的测试步骤和现象 */
	1.编译后下载程序复位运行
    2.本例程在main()里面创建两个线程，test0 线程和 test1 线程，test0 线程用于控制 D1 250ms闪烁，
      在test1线程测试CAN设备，用CAN卡接上RX和TX，在开始线程发送CAN数据，可用CAN卡在上位机上查看发送的数据，发送完以后，通过上位机将收到的数据再发送给MCU，MCU判断接收数据是否和发送的一致，用串口打印测试结果
      
4、注意事项
	无

1. Function description
    This routine shows how to create a CAN device on the RT_Thread system

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock：64MHz
	2. GPIO:   LED:	D1--PA8
    	3. CAN:    RX--PB8
		   TX--PB9
        Log(USART1): TX--PA9

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. This routine creates two threads in main(), test0 thread and test1 thread, test0 thread is used to control D1 250ms flashing, test1 thread is used to test the CAN device, 
            RX and TX are connected with the CAN analyzer and CAN data is sent in the test1 thread. CAN analyzer can be used in the upper computer to check the data sent, after sending, 
            then the data reveived sent to MCU through the upper computer tool. The MCU check wheter the data just sent and received is correct and print the test result using the serial port

4. Matters needing attention
    None.