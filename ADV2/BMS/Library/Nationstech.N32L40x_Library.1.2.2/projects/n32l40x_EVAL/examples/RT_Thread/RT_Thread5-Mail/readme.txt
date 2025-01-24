1������˵��

    1��������չʾ�� RT_Thread �¼��Ĵ��������ͺͽ���

2��ʹ�û���

    /* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
    �����壺N32L43XM-STB N32L40XM-STB V1.1

3��ʹ��˵��

    /* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
    SystemClock��64MHz
    GPIO:KEY:	KEY1--PA4,
		KEY2--PA5, 
	 	KEY3--PA6

    ����: USART1:   TX--PA9  RX--PA10    ������:115200

    /* ����Demo�Ĳ��Բ�������� */
    1.��������س���λ����
    2.�Ӻô��ڴ�ӡ����
    3.�����̴��������̣߳�key �̺߳� test �̣߳�key �̼߳�ⰴ�������¼���test �߳̽����¼������°�����KEY1��KEY2��KEY3�������¼���KEY1��KEY2 �����£������¼� AND �Żᱻ������KEY3 ���£������¼� OR ���������鿴��ӡ��־
      

4��ע������
    ��

1. Function description
    This routine shows the creation, sending, and receiving of events in RT_Thread

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock��64MHz
    	2. GPIO:KEY:	KEY1--PA4,
		        KEY2--PA5, 
	 	        KEY3--PA6��
        Log(USART1): TX--PA9 RX--PA10 Baud rate: 115200

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. Connect the serial port printing tool;
        3. This example creates two threads, key thread and test thread, key thread detects the key to send event, test thread receives event, press the key (KEY1��KEY2��KEY3) to send event, 
            KEY1��KEY2 press, receive event AND will be triggered, KEY3 press, receive event OR will be triggered. Viewing Print Logs

4. Matters needing attention
    None.