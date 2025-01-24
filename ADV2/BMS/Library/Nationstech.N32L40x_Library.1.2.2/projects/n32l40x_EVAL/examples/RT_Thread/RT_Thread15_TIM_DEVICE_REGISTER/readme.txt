1������˵��

	1��������չʾ�� RT_Thread ϵͳ���� TIM �豸

2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
	�����壺N32L43XM-STB N32L40XM-STB V1.1

3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
	SystemClock��64MHz
	GPIO:	
		LED:	D1--PA8
				D2--PB4

    ���ڣ�  USART1: TX--PA9  RX--PA10    �����ʣ�115200

	/* ����Demo�Ĳ��Բ�������� */
	1.��������س���λ����
    2.��������main()���洴�������̣߳�test0 �̺߳� test1 �̣߳�test0 �߳����ڿ��� D1 500ms��˸��
      ��test1�߳��в��� TIM1��5�붨ʱ�����ûص���������ͨ�����ڲ鿴��ӡ��Ϣ

4��ע������
	��
1. Function description
    This routine shows how to create a TIM device on the RT_Thread system

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock��64MHz
	2. GPIO:	LED:	D1--PA8
				D2--PB4
        Log(USART1): TX--PA9 RX--PA10 Baud rate: 115200

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. This routine creates two threads in main(), test0 thread and test1 thread, test0 thread is used to control D1 500ms flashing, test TIM1 in test1 thread, 
            5 seconds timing, call the callback function, you can view the printed information through the serial port

4. Matters needing attention
    None.