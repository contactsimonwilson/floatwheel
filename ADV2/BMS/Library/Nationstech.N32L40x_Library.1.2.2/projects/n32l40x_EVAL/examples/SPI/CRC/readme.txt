1������˵��

	1��SPI ���ͽ������ݽ��� CRC У��

2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
	�����壺N32L43XM-STB N32L40XM-STB V1.1

3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
	1��SystemClock��108MHz
	2��GPIO��SPI1: SCK--PA5  <--> SPI2: SCK--PB13
		SPI1: MISO--PA6 <--> SPI2: MISO--PB14
		SPI1: MOSI--PA7 <--> SPI2: MOSI--PB15  
	 
	/* ����Demo�Ĳ��Բ�������� */
	1����������س���λ���У�
	2��SPI1��SPI2 ͬʱ�շ����ݣ�������ɺ󣬷��� CRC ���ݣ�������ݺ� CRC ֵ���鿴 TransferStatus1 �� TransferStatus2 ״̬Ϊ PASSED���ٲ鿴 CRC ֵ��

4��ע������
	��


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