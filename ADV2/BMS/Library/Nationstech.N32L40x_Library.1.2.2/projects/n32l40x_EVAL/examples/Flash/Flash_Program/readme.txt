1������˵��

	/* ���������̹��� */
        ����������ò���ʾֱ�Ӷ�FLASH���ж�д����


2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
        �����壺N32L40XML-STBV1.0


3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
        SystemClock��64MHz

        USART��TX - PA9��RX - PA10��������115200

	/* ����Demo�Ĳ��Բ�������� */
        1.��������س���λ���У�
        2.�鿴���ڴ�ӡ��Ϣ����д��FLASH���������ȡ���ݶԱȾ���ͬʱ����ӡ��ϢΪ���Խ�����


4��ע������



1. Function description
	/* A brief description of the engineering function */
	This routine configures and demonstrates reading and writing directly to FLASH

2. Use environment
	/* Hardware environment: the corresponding development hardware platform */
	Development board: N32L40XML-STBV1.0
        
3. Instructions for use  
	/* Describe the related module configuration method; For example: clock, I/O, etc. */
	SystemClock: 64 MHZ
	USART: TX-PA9, RX-PA10, baud rate 115200

	/* Describes the test steps and symptoms of Demo */
	1. Reset and run the downloaded program after compilation;
	2. Check the information printed through the serial port. If the data written to the FLASH is the same as the data read from the FLASH, the test is complete.

4. Matters needing attention