1������˵��

	/* ���������̹��� */
        ����������ò���ʾNVIC���ȼ�����


2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
        �����壺N32L40XML-STBV1.0


3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
        SystemClock��64MHz

        USART��TX - PB4��������115200
	EXIT��PA0Ϊ��������ģʽ���ⲿ�ж��� - EXIT_LINE0�������ⲿ�жϣ����ȼ�Ϊ0
	SysTick���ж����ȼ�����Ϊ0

	/* ����Demo�Ĳ��Բ�������� */
        1.��������س���λ���У�
        2.��������´�ӡSysTick�ж���Ϣ���������ⲿ�жϺ�SysTick�ж�ͬʱ����ʱ���޸�SysTick�ж����ȼ�Ϊ2������ӡ�����Ϣ����������������


4��ע������


1. Function description
	/* A brief description of the engineering function */
	This routine configures and demonstrates NVIC priority Settings

2. Use environment
	/* Hardware environment: the corresponding development hardware platform */
	Development board: N32L40XML-STBV1.0
        
3. Instructions for use    
	/* Describe the related module configuration method; For example: clock, I/O, etc. */
	SystemClock: 64 MHZ
	USART: TX-PB4, baud rate 115200
	EXIT: PA0 is floating input mode, external interrupt line -exit_line0, external interrupt is enabled, and the priority is 0
	SysTick: Set the interrupt priority to 0

	/* Describes the test steps and symptoms of Demo */
	1. Reset and run the downloaded program after compilation;
	2. In normal cases, SysTick interrupt information is displayed. If both the external interrupt and SysTick interrupt are triggered at the same time, change the SysTick interrupt priority to 2 and print related information.

4. Matters needing attention