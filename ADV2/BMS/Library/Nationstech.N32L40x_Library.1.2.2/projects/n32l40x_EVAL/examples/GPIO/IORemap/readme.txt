1、功能说明

	1、此例程展示读取端口高低电平，控制 LED（D2、D3）闪烁
	2、控制 IO 口电平翻转


2、使用环境

	/* 硬件环境：工程对应的开发硬件平台 */
	开发板：N32L40XM-STB V1.1

3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
	1、SystemClock：64MHz
	2、GPIO：PA8 选择作为读取电平端口，PB4、PB5 控制 LED(D2、D3) 闪烁


	/* 描述Demo的测试步骤和现象 */
	1.编译后下载程序复位运行；
	2.检查 PA8 口电平，如果是低电平 LED（D2）闪烁，将 PA8 接入 3.3V，LED（D3）常亮；


4、注意事项
	当检测到 PA8 口为低电平时，关闭 JTAG，PA8 口为高电平时，开启 JTAG
	
	
	
	
1. Function description

	1. This example shows the high and low levels of the read port and controls the flashing of the LEDs (D2, D3)
	
	2. Control IO port level flip


2. Use environment

	/* Hardware environment: the development hardware platform corresponding to the project */
	Development board: N32L40XM-STB V1.1

3. Instructions for use

	/* Describe related module configuration methods; for example: clock, I/O, etc. */
	SystemClock: 64MHz
	GPIO: PA8 is selected as the read level port, PB4, PB5 control LED (D2, D3) to flash


	/* Describe the test steps and phenomena of the Demo */
	1. After compiling, download the program to reset and run;
	2. Check the level of the PA8 port, if it is a low level, the LED (D2) flashes, connect PA8 to 3.3V, and the LED (D3) is always on;


4. Matters needing attention
	When it is detected that the PA8 port is at a low level, close JTAG, and when the PA8 port is at a high level, open the JTAG.