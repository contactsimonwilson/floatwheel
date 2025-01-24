1������˵��

	1��������չʾ�� RT_Thread ϵͳ���� ADC �豸

2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
	�����壺N32L43XM-STB N32L40XM-STB V1.1

3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
	SystemClock��64MHz
	GPIO:	
	LED:   D1--PA8��D2--PB4
    ADC:
				PA5ѡ��Ϊģ�⹦��ADC1ת��ͨ��
           		PA6ѡ��Ϊģ�⹦��ADC1ת��ͨ��
			
  	  ��־��  USART1: TX--PA9  RX--PA10    �����ʣ�115200

	/* ����Demo�Ĳ��Բ�������� */
	1.��������س���λ����
    2.��������main()���洴�������̣߳�test0 �̺߳� test1 �̣߳�test0 �߳����ڿ��� D1 500ms��˸��
      ��test1�߳��в���ADC�豸,����PA5��PA6���ŵ�ѹ��ͨ�����ڴ�ӡ�����

4��ע������
	��

1. Function description
    This routine shows how to create an ADC device on the RT_Thread system

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock��64MHz
	2. GPIO:	
	3. LED:   	D1--PA8��D2--PB4
        4. ADC:
        		PA5 is selected as the analog function ADC1 conversion channel
                        PA6 is selected as the analog function ADC1 conversion channel
         Log: TX--PA9 RX--PA10 Baud rate: 115200

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. This routine creates two threads in main(), test0 thread and test1 thread, test0 thread is used to control D1 500ms flashing, 
            test the ADC device in test1 thread, measure the pin voltage of PA5 and PA6, and print the result through serial port

4. Matters needing attention
    None.