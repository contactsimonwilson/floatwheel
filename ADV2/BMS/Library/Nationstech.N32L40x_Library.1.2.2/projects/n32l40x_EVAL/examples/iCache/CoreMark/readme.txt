1������˵��

	/* ���������̹��� */
        ����������ò���ʾMCU�ֲܷ���


2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
        �����壺N32L40XML-STBV1.0


3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
        SystemClock��64MHz

        USART��TX - PA9��RX - PA10��������115200
	SysTick��ʱ�ӵδ�����Ϊ1MS

	/* ����Demo�Ĳ��Բ�������� */
        1.��������س���λ���У�
        2.ͨ�����ڴ�ӡ���ֽܷ����


4��ע������


1. Function description
	/* A brief description of the engineering function */
	This routine configures and demonstrates MCU running tests

2. Use environment
	/* Hardware environment: the corresponding development hardware platform */
	Development board: N32L40XML-STBV1.0
        
3. Instructions for use   
	/* Describe the related module configuration method; For example: clock, I/O, etc. */
	SystemClock��64MHz
	USART: TX-PA9, RX-PA10, baud rate 115200
	SysTick: clock tick is set to 1MS

	/* Describes the test steps and symptoms of Demo */
	1. Reset and run the downloaded program after compilation;
	2. Print the running result through the serial port;

4. Matters needing attention