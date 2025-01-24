1������˵��

	1��������չʾ�� RT_Thread ϵͳ���� WATCHDOG �豸

2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
	�����壺N32L43XM-STB N32L40XM-STB V1.1

3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
	SystemClock��64MHz
    IWDGʱ��Դ�� LSI/32
	GPIO:	       
		LED:	D1--PA8
        KEY:	KEY1--PA4
				KEY2--PA5
	����:  USART1: TX--PA9  RX--PA10    ������:115200

	/* ����Demo�Ĳ��Բ�������� */
	1.��������س���λ����
    2.�����̴��������̣߳�test0�̺߳�test1�̣߳�test0�߳����ڿ��� D1 500ms��˸����test1�߳��в��� IWDG �豸������ IWDG �豸�����ó�ʱʱ�䣬���� IWDG���ڿ���ʱι����

4��ע������
	��


1. Function description
    This routine shows how to create a WATCHDOG device on the RT_Thread system

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock��64MHz
    	2.IWDGʱ��Դ�� LSI/32
	3.GPIO:	       LED:	D1--PA8
        Log(USART1): TX--PA9 RX--PA10 Baud rate: 115200

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. This routine creates two threads in main(), test0 thread and test1 thread, test0 thread is used to control D1 500ms flashing, test1 thread is used to test the IWDG device, 
            find the IWDG device, set the timeout, start the IWDG, and feed the dog when idle

4. Matters needing attention
    None.