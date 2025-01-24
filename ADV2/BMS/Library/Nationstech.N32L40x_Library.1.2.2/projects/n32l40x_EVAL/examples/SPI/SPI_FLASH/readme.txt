1������˵��

	1��SPI ����д������ W25Q128

2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
	�����壺N32L43XM-STB N32L40XM-STB V1.1

3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
	1��SystemClock��108MHz
	2��SPI1: NSS--PA4��SCK--PA5��MISO--PA6��MOSI--PA7

	/* ����Demo�Ĳ��Բ�������� */
	1.��������س���λ���У�
	2.ͨ�� SPI1 ��ȡ W25Q128 �� ID��Ȼ��д���ݣ��ٶ��������Ƚ϶�д���ݣ��鿴 TransferStatus1 ״̬Ϊ PASSED��Ȼ������飬��������������

4��ע������
	�� N32L43XM-STB N32L40XM-STB V1.1 �������ϵ� SPI1 �ӿڽ��� N32G457QE_EVB ������� W25Q128 �ϣ�������������Ҫ����



1. Function description

	1. SPI read, write, erase W25Q128

2. Use environment

	/* Hardware environment: the development hardware platform corresponding to the project */
	Development board: N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use

	/* Describe related module configuration methods; for example: clock, I/O, etc. */
	1. SystemClock: 108MHz
	2. SPI1: NSS--PA4, SCK--PA5, MISO--PA6, MOSI--PA7

	/* Describe the test steps and phenomena of the Demo */
	1. After compiling, download the program to reset and run;
	2. Read the ID of W25Q128 through SPI1, then write the data, then read it out, compare the read and write data, check that the status of TransferStatus1 is PASSED, then erase the block, and check that the erase block is normal.

4. Matters needing attention
	Connect the SPI1 interface of the N32L43XM-STB N32L40XM-STB V1.1 development board to the W25Q128 of the N32G457QE_EVB development board, the two development boards need to share the ground