1������˵��

	1��I2S ͨ���ж��շ�����

2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
	�����壺N32L43XM-STB N32L40XM-STB V1.1

3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
	1��SystemClock��108MHz
	2��GPIO��I2S1��MASTER  WS--PA4��SCK--PA5��SD--PA7����
		 I2S2��SLAVE   WS--PB12��SCK--PB13�� SD--PB15��,
	3���жϣ�I2S1 �ж���ں��� SPI1_IRQHandler��I2S2 �ж���ں���SPI2_IRQHandler


	/* ����Demo�Ĳ��Բ�������� */
	1����������س���λ���У�
	2��2S ��ʼ���� 16 λ���ݸ�ʽ��48K ����Ƶ�ʣ�I2S1�����ݷ���ʱ���� SPI1_IRQHandler �����������ݣ�I2S2 �����ݽ���ʱ���� SPI2_IRQHandler ������������ ��������ɺ󣬲鿴 TransferStatus1 ״̬Ϊ PASSED��
	     I2S ��ʼ���� 24 λ���ݸ�ʽ��16K ����Ƶ�ʣ�I2S1�����ݷ���ʱ���� SPI1_IRQHandler �����������ݣ�I2S2 �����ݽ���ʱ���� SPI2_IRQHandler ������������ ��������ɺ󣬲鿴 TransferStatus2 ״̬Ϊ PASSED��

4��ע������
	��




1. Function description

	1. I2S sends and receives data through interrupts

2. Use environment

	/* Hardware environment: the development hardware platform corresponding to the project */
	Development board: N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use

	/* Describe related module configuration methods; for example: clock, I/O, etc. */
	1. SystemClock: 108MHz
	2. GPIO: I2S1 (MASTER WS--PA4, SCK--PA5, SD--PA7),
	             I2S2 (SLAVE WS--PB12, SCK--PB13, SD--PB15),
	3. Interrupt: I2S1 interrupt entry function SPI1_IRQHandler, I2S2 interrupt entry function SPI2_IRQHandler

	/* Describe the test steps and phenomena of the Demo */
	1. After compiling, download the program to reset and run;
	2. 2S is initialized to 16-bit data format, 48K sampling frequency. When I2S1 has data to send, it enters the SPI1_IRQHandler function to receive data. 
	   When I2S2 has data to receive, it enters the SPI2_IRQHandler function to send data. After the operation is completed, check that the status of TransferStatus1 is PASSED;
	  I2S is initialized to 24-bit data format, 16K sampling frequency. When I2S1 has data to send, it enters the SPI1_IRQHandler function to receive data.
	  When I2S2 has data to receive, it enters the SPI2_IRQHandler function to send data. After the operation is completed, check that the status of TransferStatus2 is PASSED;

4. Matters needing attention
	none