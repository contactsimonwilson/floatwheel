1������˵��

	/* ���������̹��� */
        ����������ò���ʾ����FLASHд����


2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
        �����壺N32L40XML-STBV1.0


3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
        SystemClock��64MHz

        USART��TX - PA9��RX - PA10��������115200

	/* ����Demo�Ĳ��Բ�������� */
        1.��������س���λ���У�
        2.����FLASHд�������鿴������Ϣ����FLASH����д��ʧ��ʱ����ӡ��ϢΪ����ͨ����


4��ע������



1. Function description
	/* A brief description of the engineering function */
	This routine configures and demonstrates enabling FLASH write protection

2. Use environment
	/* Hardware environment: the corresponding development hardware platform */
	Development board: N32L40XML-STBV1.0
        
3. Instructions for use
    
	/* Describe the related module configuration method; For example: clock, I/O, etc. */
	SystemClock: 64 MHZ
	USART: TX-PA9, RX-PA10, baud rate 115200

	/* Describes the test steps and symptoms of Demo */
	1. Reset and run the downloaded program after compilation;
	2. Enable FLASH write protection and view information about the serial port. If data fails to be written to the FLASH, the test passes.

4. Matters needing attention