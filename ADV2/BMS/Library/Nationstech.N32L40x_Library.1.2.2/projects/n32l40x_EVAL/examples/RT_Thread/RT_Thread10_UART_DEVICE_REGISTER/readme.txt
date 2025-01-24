1、功能说明

	1、此例程展示在 RT_Thread 系统创建 UART 设备

2、使用环境

	/* 硬件环境：工程对应的开发硬件平台 */
	开发板：N32L43XM-STB N32L40XM-STB V1.1

3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
	SystemClock：64MHz
	LED:		D1--PA8、D2--PB4
    KEY:		KEY1--PA4,KEY2--PA5
    USART3:     TX--PB10、RX--PB11

	/* 描述Demo的测试步骤和现象 */
	 1.编译后下载程序复位运行
   	 2.本例程在main()里面创建两个线程，test0 线程和 test1 线程，test0 线程用于控制 D1 250ms闪烁，在test1线程中测试 
	    UART 设备发送接收功能，通过串口工具接在 USART3 的 TX 和 RX 上，上电后会先通过 USART3 的 TX 发送数据，
	   上位机软件通过串口工具发送数据到 USART3 的 RX 上，USART3 会将接收到的数据通过 TX 再发送出去

4、注意事项
	无

1. Function description
    This routine shows how to create a UART device on the RT_Thread system

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:     N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1.SystemClock：64MHz
	2.LED:		D1--PA8、D2--PB4
    	3.KEY:		KEY1--PA4,KEY2--PA5
        USART3:     TX--PB10、RX--PB11

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. This routine creates two threads in main(), test0 thread and test1 thread, test0 thread is used to control D1 250ms flashing, Test in test1 thread
	   The UART device has the function of sending and receiving. It is connected to the TX and RX of the USART3 through the serial port tool. After power-on, it will first send data through the TX of the USART3.
	   The host computer software sends data to the RX of USART3 through the serial port tool, and the USART3 will send the received data through TX and then send it out.

4. Matters needing attention
    None