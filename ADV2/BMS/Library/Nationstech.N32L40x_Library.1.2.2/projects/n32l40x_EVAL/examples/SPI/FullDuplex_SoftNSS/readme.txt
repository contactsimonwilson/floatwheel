1������˵��

	1��SPI ȫ˫����� NSS ģʽ���ͽ�������

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
	2��SPI1 ��ʼ��λ�������������ݣ�SPI2 ��ʼ��λ�Ի����������� ��������ɺ󣬼�����ݣ��鿴 TransferStatus1 �� TransferStatus2 ״̬Ϊ PASSED��
	     SPI2 ��ʼ��λ�������������ݣ�SPI1 ��ʼ��λ�Ի����������� ��������ɺ󣬼�����ݣ��鿴 TransferStatus3 �� TransferStatus4 ״̬Ϊ PASSED��


4��ע������
	��

1. Function description

	1. SPI full-duplex software NSS mode to send and receive data

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
	2. SPI1 initializes the bit host, sends data, SPI2 initializes the bit cluster machine, receives data, after the transmission is completed, check the data, check that the status of TransferStatus1 and TransferStatus2 is PASSED,
	SPI2 initializes the bit host, sends data, SPI1 initializes the bit cluster machine, receives data, and after the transfer is completed, check the data, and check that the status of TransferStatus3 and TransferStatus4 is PASSED;

4. Matters needing attention
	none