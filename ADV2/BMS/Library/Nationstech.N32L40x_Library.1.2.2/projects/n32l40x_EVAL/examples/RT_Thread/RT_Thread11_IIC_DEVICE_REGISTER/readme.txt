1、功能说明

	1、此例程展示在 RT_Thread 系统创建 I2C 设备读写操作EEPROM

2、使用环境

	/* 硬件环境：工程对应的开发硬件平台 */
	开发板：N32L43XM-STB N32L40XM-STB V1.1

3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
	SystemClock：64MHz
	GPIO:	LED:D1--PA8、D2--PB4、D3--PB5
                KEY:	KEY1--PA4，KEY2--PA5
                I2C1:	I2C_SCL--PB8、I2C_SDA--PB9
	串口：      TX--PA9

	/* 描述Demo的测试步骤和现象 */
	1.编译后下载程序复位运行
               2.本例程在main()里面创建两个线程，test0 线程和 test1 线程，test0 线程用于控制 D1 250ms闪烁，
                 在test1线程测试I2C设备读写操作EEPROM，测试结果通过串口打印输出。

4、注意事项
	无

1. Function description
    This routine shows how to create an I2C device to read and write operation EEPROM on RT_Thread system

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock：64MHz
	2. GPIO:	LED:D1--PA8、D2--PB4、D3--PB5
        3. KEY:		KEY1--PA4，KEY2--PA5
        4. I2C1:	I2C_SCL--PB8、I2C_SDA--PB9
        Log: TX--PA9 RX--PA10 Baud rate: 115200

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. This routine creates two threads in main(), test0 thread and test1 thread, test0 thread is used to control D1 250ms flashing, 
            test1 thread is used to test I2C device read and write operation EEPROM, test results are printed out through the serial port

4. Matters needing attention
    None