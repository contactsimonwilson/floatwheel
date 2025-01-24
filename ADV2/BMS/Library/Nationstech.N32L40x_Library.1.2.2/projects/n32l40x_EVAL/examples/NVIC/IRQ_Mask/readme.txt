1������˵��

	/* ���������̹��� */
        ����������ò���ʾʹ��EXIT�ⲿ�жϼ�TIM��ʱ���ж�


2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
        �����壺N32L40XML-STBV1.0


3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
        SystemClock��64MHz

        USART��TX - PB4��������115200
	EXIT��PA0Ϊ��������ģʽ���ⲿ�ж��� - EXIT_LINE0�������ⲿ�ж�
	TIM��Ԥ��Ƶϵ�� - ��SystemClock/1200-1�������� - ��1200-1����������ʱ���ж�

	/* ����Demo�Ĳ��Բ�������� */
        1.��������س���λ���У�
        2.�鿴���ڴ�ӡ��Ϣ����ʱ���ж���Ϣÿ1S��ӡһ�Σ����°�����ӡֹͣ���ٴΰ����������ӡ��������������������


4��ע������


1. Function description
	/* A brief description of the engineering function */
	This routine configures and demonstrates the use of EXIT external interrupts and TIM timer interrupts

2. Use environment
	/* Hardware environment: the corresponding development hardware platform */
	Development board: N32L40XML-STBV1.0
        
3. Instructions for use    
	/* Describe the related module configuration method; For example: clock, I/O, etc. */
	SystemClock: 64 MHZ
	USART: TX-PB4, baud rate 115200
	EXIT: PA0 is in floating input mode, and external interrupt line -EXIT_LINE0 is used to enable external interrupt
	TIM: Pre-dividing frequency coefficient - (SystemClock/1200-1), period - (1200-1), start timer interrupt

	/* Describes the test steps and symptoms of Demo */
	1. Reset and run the downloaded program after compilation;
	2. Check the serial port printing information. The timer interrupt information is printed every 1S. Press the button to stop printing, and press it again to continue printing, indicating that the program is running normally.

4. Matters needing attention