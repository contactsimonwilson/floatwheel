1、功能说明

	1、SPI 发送接收数据进行 CRC 校验

2、使用环境

	/* 硬件环境：工程对应的开发硬件平台 */
	开发板：N32L43XM-STB N32L40XM-STB V1.1

3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
	1、SystemClock：108MHz
	2、GPIO：SPI1: SCK--PA5  <--> SPI2: SCK--PB13
		SPI1: MISO--PA6 <--> SPI2: MISO--PB14
		SPI1: MOSI--PA7 <--> SPI2: MOSI--PB15  
	 
	/* 描述Demo的测试步骤和现象 */
	1、编译后下载程序复位运行；
	2、SPI1、SPI2 同时收发数据，传输完成后，发送 CRC 数据，检查数据和 CRC 值，查看 TransferStatus1 和 TransferStatus2 状态为 PASSED，再查看 CRC 值；

4、注意事项
	无


1. Function description

	1. SPI sends and receives data for CRC check

2. Use environment

	/* Hardware environment: the development hardware platform corresponding to the project */
	Development board: N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use

	/* Describe related module configuration methods; for example: clock, I/O, etc. */
	1. SystemClock: 108MHz
	2. GPIO: SPI1: SCK--PA5 <--> SPI2: SCK--PB13
	           SPI1: MISO--PA6 <--> SPI2: MISO--PB14
	           SPI1: MOSI--PA7 <--> SPI2: MOSI--PB15

	/* Describe the test steps and phenomena of the Demo */
	1. After compiling, download the program to reset and run;
	2. SPI1 and SPI2 send and receive data at the same time. After the transmission is completed, send the CRC data, check the data and CRC value, check that the status of TransferStatus1 and TransferStatus2 is PASSED, and then check the CRC value;

4. Matters needing attention
	none