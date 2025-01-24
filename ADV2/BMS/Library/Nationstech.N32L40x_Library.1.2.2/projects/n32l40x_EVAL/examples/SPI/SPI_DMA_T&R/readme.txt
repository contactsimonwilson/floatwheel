1������˵��

	1��SPI DMA ���߷��ͺ͵��߽�������

2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
	�����壺N32L43XM-STB N32L40XM-STB V1.1

3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
	1��SystemClock��108MHz
	2��GPIO��SPI1: NSS--PA4  <--> SPI2--PB12
		SPI1: SCK--PA5  <--> SPI2: SCK--PB13
		SPI1: MOSI--PA7 <--> SPI2: MISO--PB14
	3��DMA��DMA_CH4 ͨ���������ݣ�DMA_CH1 ͨ����������

	/* ����Demo�Ĳ��Բ�������� */
	1��.��������س���λ���У�
	2��SPI1 ͨ�� DMA �������ݣ�SPI2 ͨ�� DMA �������ݣ����ݴ�����ɺ󣬲鿴 TransferStatus ״̬Ϊ PASSED��

4��ע������
	�����ߡ������������豸��ΪMOSI���ţ��ڴ��豸��ΪMISO����



1. Function description

	1. SPI DMA single-wire sending and single-wire receiving data

2. Use environment

	/* Hardware environment: the development hardware platform corresponding to the project */
	Development board: N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use

	/* Describe related module configuration methods; for example: clock, I/O, etc. */
	1. SystemClock: 108MHz
	2. GPIO: SPI1: NSS--PA4 <--> SPI2--PB12
	              SPI1: SCK--PA5 <--> SPI2: SCK--PB13
	              SPI1: MOSI--PA7 <--> SPI2: MISO--PB14
	3. DMA: DMA_CH4 channel sends data, DMA_CH1 channel receives data

	/* Describe the test steps and phenomena of the Demo */
	1. After compiling, download the program to reset and run;
	2. SPI1 sends data through DMA, and SPI2 receives data through DMA. After the data transfer is completed, check that the TransferStatus status is PASSED;

4. Matters needing attention
	The "single wire" data lines are MOSI pins on the master side and MISO pins on the slave side