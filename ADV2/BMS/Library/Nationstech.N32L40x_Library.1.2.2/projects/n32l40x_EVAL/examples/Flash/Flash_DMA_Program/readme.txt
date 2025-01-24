1������˵��

	/* ���������̹��� */
        ����������ò���ʾʹ��DMA��SRAM����д��FLASH


2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
        �����壺N32L40XML-STBV1.0


3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
        SystemClock��64MHz

        USART��TX - PA9��RX - PA10��������115200
	DMA�����ݴ��䷽��ΪSRAM��FLASH

	/* ����Demo�Ĳ��Բ�������� */
        1.��������س���λ���У�
        2.�鿴���ڴ�ӡ��Ϣ���Աȴ�����ɺ��SRAM��FLASH�������ݣ���ȫ��ͬ���ӡ��ϢΪ����ͨ������������������


4��ע������


1. Function description
	/* A brief description of the engineering function */
	This routine configures and demonstrates the use of DMA to write SRAM data to FLASH

2. Use environment
	/* Hardware environment: the corresponding development hardware platform */
	Development board: N32L40XML-STBV1.0
        
3. Instructions for use
    
	/* Describe the related module configuration method; For example: clock, I/O, etc. */
	SystemClock: 64 MHZ
	USART: TX-PA9, RX-PA10, baud rate 115200
	DMA: Data transfer from SRAM to FLASH

	/* Describes the test steps and symptoms of Demo */
	1. Reset and run the downloaded program after compilation;
	2. Check the serial port printed information and compare the SRAM and FLASH array data after transmission. If the printed information is identical, the test is passed and the program runs normally.

4. Matters needing attention