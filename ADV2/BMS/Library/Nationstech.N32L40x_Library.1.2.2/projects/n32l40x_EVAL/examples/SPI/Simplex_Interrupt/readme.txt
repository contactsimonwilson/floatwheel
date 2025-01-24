1������˵��

	1��SPI �����жϷ��ͺͽ�������

2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
	�����壺N32L43XM-STB N32L40XM-STB V1.1

3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
	1��SystemClock��108MHz
	2��GPIO��SPI1: SCK--PA5  <--> SPI2: SCK--PB13
	                SPI1: MOSI--PA7 <--> SPI2: MISO--PB14
	3���жϣ�SPI1 �ж���ں��� SPI1_IRQHandler��SPI2 �ж���ں��� SPI2_IRQHandler

	/* ����Demo�Ĳ��Բ�������� */
	1����������س���λ���У�
	2��SPI1 ��������Ҫ����ʱ���� SPI1_IRQHandler �жϺ������ͣ�SPI2 ��������Ҫ����ʱ���� SPI2_IRQHandler �жϺ������գ����ݴ�����ɺ󣬲鿴 TransferStatus ״̬Ϊ PASSED��

4��ע������
	�����ߡ������������豸��ΪMOSI���ţ��ڴ��豸��ΪMISO����



1. Function description

	1. SPI single-wire interrupt sending and receiving data

2. Use environment

	/* Hardware environment: the development hardware platform corresponding to the project */
	Development board: N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use

	/* Describe related module configuration methods; for example: clock, I/O, etc. */
	1. SystemClock: 108MHz
	2. GPIO: SPI1: SCK--PA5 <--> SPI2: SCK--PB13
	              SPI1: MOSI--PA7 <--> SPI2: MISO--PB14
	3. Interrupt: SPI1 interrupt entry function SPI1_IRQHandler, SPI2 interrupt entry function SPI2_IRQHandler

	/* Describe the test steps and phenomena of the Demo */
	1. After compiling, download the program to reset and run;
	2. Enter the SPI1_IRQHandler interrupt function to send when SPI1 has data to send, and enter the SPI2_IRQHandler interrupt function to receive when SPI2 has data to receive. After the data transmission is completed, check the TransferStatus status as PASSED;

4. Matters needing attention
	The "single wire" data lines are MOSI pins on the master side and MISO pins on the slave side