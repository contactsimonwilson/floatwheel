1、功能说明

	1、I2S 通过 DMA 收发数据

2、使用环境

	/* 硬件环境：工程对应的开发硬件平台 */
	开发板：N32L43XM-STB N32L40XM-STB V1.1

3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
	1、SystemClock：108MHz
	2、GPIO：I2S1（MASTER WS--PA4、 SCK--PA5、   SD--PA7），
                                I2S2（SLAVE    WS--PB12、SCK--PB13、 SD--PB15）,
	3、DMA：I2S1 发送采用 DMA_CH2通道，I2S2 接收采用 DMA_CH4 通道；

	/* 描述Demo的测试步骤和现象 */
	1、编译后下载程序复位运行；
	2、I2S1 通过 DMA_CH2 发送数据，I2S2 通过 DMA_CH4 接收数据 ，运行完成后，查看 TransferStatus 状态为 PASSED

4、注意事项
	无




1. Function description

        1. I2S sends and receives data through DMA

2. Use environment

        /* Hardware environment: the development hardware platform corresponding to the project */
        Development board: N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use

        /* Describe related module configuration methods; for example: clock, I/O, etc. */
        1. SystemClock: 108MHz
        2. GPIO: I2S1 (MASTER WS--PA4, SCK--PA5, SD--PA7),
                     I2S2 (SLAVE WS--PB12, SCK--PB13, SD--PB15),
        3. DMA: I2S1 transmission adopts DMA_CH2 channel, I2S2 reception adopts DMA_CH4 channel;

        /* Describe the test steps and phenomena of the Demo */
        1. After compiling, download the program to reset and run;
        2. I2S1 sends data through DMA_CH2, and I2S2 receives data through DMA_CH4. After the operation is completed,
            check that the TransferStatus status is PASSED

4. Matters needing attention
         none