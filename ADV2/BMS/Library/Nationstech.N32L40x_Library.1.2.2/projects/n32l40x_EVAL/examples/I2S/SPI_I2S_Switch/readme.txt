1������˵��

	1��I2S �շ���������Ժ��л��� SPI �շ����ݣ����л��� I2S �շ�����

2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
	�����壺N32L43XM-STB N32L40XM-STB V1.1

3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
	1��SystemClock��108MHz
	2��GPIO��I2S1��MASTER  WS--PA4��SCK--PA5��SD--PA7����
	                I2S2��SLAVE     WS--PB12��SCK--PB13�� SD--PB15��

	/* ����Demo�Ĳ��Բ�������� */
	1����������س���λ���У�
	2��I2S1 �� I2S2 ��ʼ����I2S1 �������ݣ�I2S2 �������� ��������ɺ󣬲鿴 TransferStatus1 ״̬Ϊ PASSED��
	     SPI1 �� SPI2 ��ʼ����SPI1 �������ݣ�SPI2 �������� ��������ɺ󣬲鿴 TransferStatus2 ״̬Ϊ PASSED��
	     I2S1 �� I2S2 ��ʼ����I2S1 �������ݣ�I2S2 �������� ��������ɺ󣬲鿴 TransferStatus3 ״̬Ϊ PASSED��

4��ע������
	��


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