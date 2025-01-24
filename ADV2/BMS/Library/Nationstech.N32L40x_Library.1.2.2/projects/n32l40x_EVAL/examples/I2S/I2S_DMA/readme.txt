1������˵��

	1��I2S ͨ�� DMA �շ�����

2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
	�����壺N32L43XM-STB N32L40XM-STB V1.1

3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
	1��SystemClock��108MHz
	2��GPIO��I2S1��MASTER WS--PA4�� SCK--PA5��   SD--PA7����
                                I2S2��SLAVE    WS--PB12��SCK--PB13�� SD--PB15��,
	3��DMA��I2S1 ���Ͳ��� DMA_CH2ͨ����I2S2 ���ղ��� DMA_CH4 ͨ����

	/* ����Demo�Ĳ��Բ�������� */
	1����������س���λ���У�
	2��I2S1 ͨ�� DMA_CH2 �������ݣ�I2S2 ͨ�� DMA_CH4 �������� ��������ɺ󣬲鿴 TransferStatus ״̬Ϊ PASSED

4��ע������
	��




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