1������˵��

	1��������չʾ�� RT_Thread ϵͳ�����߳�

2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
	�����壺N32L43XM-STB N32L40XM-STB V1.1

3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
	SystemClock��64MHz
	GPIO��PA8 ���� LED(D1) ��˸��PB4 ���� LED(D2) ��˸��


	/* ����Demo�Ĳ��Բ�������� */
	1.��������س���λ����
    2.��������main()���洴�������̣߳�LED1 �̺߳� LED2 �̣߳�LED1 �߳����ڿ��� D1 1s��˸��LED2 �߳����ڿ��� D2 500ms��˸���Դ�ѭ��
	
4��ע������
	��
1. Function description
    This example shows how to create a thread in the RT_Thread system

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock: 64MHz
        2. GPIO: 
                    PA8 controls the LED (D1) to blink; PB4 controls the LED (D2) to blink;

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. This routine creates two threads in main (), LED1 thread and LED2 thread. LED1 thread is used to control D1 1s flashing, and LED2 thread is used to control D2 500ms flashing, so as to cycle

4. Matters needing attention
    None.