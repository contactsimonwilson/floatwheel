1������˵��

	/* ���������̹��� */
        ����������ò���ʾ����޸��߳�ģʽ��Ȩ���ʼ���ջ


2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
        �����壺N32L40XML-STBV1.0


3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
        SystemClock��64MHz

        USART��TX - PA9��RX - PA10��������115200

	/* ����Demo�Ĳ��Բ�������� */
        1.��������س���λ���У�
        2.��ʹ�ñ������ġ�Cortex�Ĵ��������ڲ鿴�߳�ģʽ�£�ʹ�õĶ�ջ������ķ��ʼ�����Ȩ��/����Ȩ������


4��ע������


1. Function description
	/* A brief description of the engineering function */
	This routine configudes and demonstrates how to modify thread mode privileged access and stack

2. Use environment
	/* Hardware environment: the corresponding development hardware platform */
	Development board: N32L40XML-STBV1.0

3. Instructions for use    
	/* Describe the related module configuration method; For example: clock, I/O, etc. */
	SystemClock: 64 MHZ
	USART: TX-PA9, RX-PA10, baud rate 115200

	/* Describes the test steps and symptoms of Demo */
	1. Reset and run the downloaded program after compilation;
	2. Use the Compiler's Cortex Register window to view the stack and code access level (privileged/non-privileged) in thread mode.

4. Matters needing attention