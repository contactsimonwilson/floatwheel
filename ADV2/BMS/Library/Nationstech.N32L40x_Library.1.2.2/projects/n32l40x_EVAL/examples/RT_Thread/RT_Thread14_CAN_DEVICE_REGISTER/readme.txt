1������˵��

	1��������չʾ�� RT_Thread ϵͳ���� CAN �豸

2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
	�����壺N32L43XM-STB N32L40XM-STB V1.1

3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
	SystemClock��64MHz
	GPIO:	
		LED:	D1--PA8
    CAN:    RX--PB8
			TX--PB9
    ����(USART1):   TX--PA9

	/* ����Demo�Ĳ��Բ�������� */
	1.��������س���λ����
    2.��������main()���洴�������̣߳�test0 �̺߳� test1 �̣߳�test0 �߳����ڿ��� D1 250ms��˸��
      ��test1�̲߳���CAN�豸����CAN������RX��TX���ڿ�ʼ�̷߳���CAN���ݣ�����CAN������λ���ϲ鿴���͵����ݣ��������Ժ�ͨ����λ�����յ��������ٷ��͸�MCU��MCU�жϽ��������Ƿ�ͷ��͵�һ�£��ô��ڴ�ӡ���Խ��
      
4��ע������
	��

1. Function description
    This routine shows how to create a CAN device on the RT_Thread system

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock��64MHz
	2. GPIO:   LED:	D1--PA8
    	3. CAN:    RX--PB8
		   TX--PB9
        Log(USART1): TX--PA9

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. This routine creates two threads in main(), test0 thread and test1 thread, test0 thread is used to control D1 250ms flashing, test1 thread is used to test the CAN device, 
            RX and TX are connected with the CAN analyzer and CAN data is sent in the test1 thread. CAN analyzer can be used in the upper computer to check the data sent, after sending, 
            then the data reveived sent to MCU through the upper computer tool. The MCU check wheter the data just sent and received is correct and print the test result using the serial port

4. Matters needing attention
    None.