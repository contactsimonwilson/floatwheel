1、功能说明

    1、此例程展示在 RT_Thread 事件的创建、发送和接收

2、使用环境

    /* 硬件环境：工程对应的开发硬件平台 */
    开发板：N32L43XM-STB N32L40XM-STB V1.1

3、使用说明

    /* 描述相关模块配置方法；例如:时钟，I/O等 */
    SystemClock：64MHz
    GPIO:KEY:	KEY1--PA4,
		KEY2--PA5, 
	 	KEY3--PA6

    串口: USART1:   TX--PA9  RX--PA10    波特率:115200

    /* 描述Demo的测试步骤和现象 */
    1.编译后下载程序复位运行
    2.接好串口打印工具
    3.本例程创建两个线程，key 线程和 test 线程，key 线程检测按键发送事件，test 线程接收事件，按下按键（KEY1、KEY2、KEY3）发送事件，KEY1、KEY2 都按下，接收事件 AND 才会被触发，KEY3 按下，接收事件 OR 被触发，查看打印日志
      

4、注意事项
    无

1. Function description
    This routine shows the creation, sending, and receiving of events in RT_Thread

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock：64MHz
    	2. GPIO:KEY:	KEY1--PA4,
		        KEY2--PA5, 
	 	        KEY3--PA6）
        Log(USART1): TX--PA9 RX--PA10 Baud rate: 115200

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. Connect the serial port printing tool;
        3. This example creates two threads, key thread and test thread, key thread detects the key to send event, test thread receives event, press the key (KEY1、KEY2、KEY3) to send event, 
            KEY1、KEY2 press, receive event AND will be triggered, KEY3 press, receive event OR will be triggered. Viewing Print Logs

4. Matters needing attention
    None.