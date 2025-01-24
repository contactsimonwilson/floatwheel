1、功能说明

	1、I2S 收发数据完成以后切换成 SPI 收发数据，再切换成 I2S 收发数据

2、使用环境

	/* 硬件环境：工程对应的开发硬件平台 */
	开发板：N32L43XM-STB N32L40XM-STB V1.1

3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
	1、SystemClock：108MHz
	2、GPIO：I2S1（MASTER  WS--PA4、SCK--PA5、SD--PA7），
	                I2S2（SLAVE     WS--PB12、SCK--PB13、 SD--PB15）

	/* 描述Demo的测试步骤和现象 */
	1、编译后下载程序复位运行；
	2、I2S1 和 I2S2 初始化，I2S1 发送数据，I2S2 接收数据 ，运行完成后，查看 TransferStatus1 状态为 PASSED；
	     SPI1 和 SPI2 初始化，SPI1 发送数据，SPI2 接收数据 ，运行完成后，查看 TransferStatus2 状态为 PASSED；
	     I2S1 和 I2S2 初始化，I2S1 发送数据，I2S2 接收数据 ，运行完成后，查看 TransferStatus3 状态为 PASSED；

4、注意事项
	无


1. Function description

	1. After I2S sending and receiving data is completed, switch to SPI to send and receive data, and then switch to I2S to send and receive data

2. Use environment

	/* Hardware environment: the development hardware platform corresponding to the project */
	Development board: N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use

	/* Describe related module configuration methods; for example: clock, I/O, etc. */
	1. SystemClock: 108MHz
	2. GPIO: I2S1 (MASTER WS--PA4, SCK--PA5, SD--PA7),
	I2S2 (SLAVE WS--PB12, SCK--PB13, SD--PB15)

/* Describe the test steps and phenomena of the Demo */
	1. After compiling, download the program to reset and run;
	2. I2S1 and I2S2 are initialized, I2S1 sends data, and I2S2 receives data. 
	   After the operation is completed, check that the status of TransferStatus1 is PASSED;
	   SPI1 and SPI2 are initialized, SPI1 sends data, and SPI2 receives data.
	   After the operation is completed, check that the status of TransferStatus2 is PASSED;
	   I2S1 and I2S2 are initialized, I2S1 sends data, and I2S2 receives data. 
	  After the operation is completed, check that the status of TransferStatus3 is PASSED;

4. Matters needing attention
	none