1������˵��

	1��������չʾ�� RT_Thread ϵͳ���� DAC �豸

2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
	�����壺N32L43XM-STB N32L40XM-STB V1.1

3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
	SystemClock��64MHz
	GPIO:	
	    LED:	D1--PA8
        ADC:
				PC0ѡ��Ϊģ�⹦��ADCת��ͨ��
        DAC:
				PA4ѡ��Ϊģ�⹦��DAC OUT
    	���ڣ�  	
				TX--PA9


	/* ����Demo�Ĳ��Բ�������� */
	1.��������س���λ����
    2.��������main()���洴�������̣߳�test0 �̺߳� test1 �̣߳�test0 �߳����ڿ��� D1 250ms��˸��
      ��test1�̲߳��� DAC �豸������������ PA4 �� PC0���� ADC ���� DAC �������ͨ�����ڴ�ӡ��

4��ע������
	��

1. Function description
    This routine shows how to create an DAC device on the RT_Thread system

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock��64MHz
	2. GPIO:  LED:	D1--PA8
        3. ADC:
        	PC0 is selected as the analog function ADC1 conversion channel
        4.DAC:
                PA4 is selected as the analog function DAC1 OUT
        Log(USART1): TX--PA9 Baud rate: 115200

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. This routine creates two threads in main(), test0 thread and test1 thread, test0 thread is used to control D1 250ms flashing, test1 thread is used to test the DAC device, 
            connect PA4 and PC0 with jumper, measure DAC output with ADC, print through serial port

4. Matters needing attention
    None.