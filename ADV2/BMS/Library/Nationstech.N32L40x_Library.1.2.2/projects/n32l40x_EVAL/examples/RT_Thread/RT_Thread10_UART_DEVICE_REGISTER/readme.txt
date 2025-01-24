1������˵��

	1��������չʾ�� RT_Thread ϵͳ���� UART �豸

2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
	�����壺N32L43XM-STB N32L40XM-STB V1.1

3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
	SystemClock��64MHz
	LED:		D1--PA8��D2--PB4
    KEY:		KEY1--PA4,KEY2--PA5
    USART3:     TX--PB10��RX--PB11

	/* ����Demo�Ĳ��Բ�������� */
	 1.��������س���λ����
   	 2.��������main()���洴�������̣߳�test0 �̺߳� test1 �̣߳�test0 �߳����ڿ��� D1 250ms��˸����test1�߳��в��� 
	    UART �豸���ͽ��չ��ܣ�ͨ�����ڹ��߽��� USART3 �� TX �� RX �ϣ��ϵ�����ͨ�� USART3 �� TX �������ݣ�
	   ��λ�����ͨ�����ڹ��߷������ݵ� USART3 �� RX �ϣ�USART3 �Ὣ���յ�������ͨ�� TX �ٷ��ͳ�ȥ

4��ע������
	��

1. Function description
    This routine shows how to create a UART device on the RT_Thread system

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:     N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1.SystemClock��64MHz
	2.LED:		D1--PA8��D2--PB4
    	3.KEY:		KEY1--PA4,KEY2--PA5
        USART3:     TX--PB10��RX--PB11

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. This routine creates two threads in main(), test0 thread and test1 thread, test0 thread is used to control D1 250ms flashing, Test in test1 thread
	   The UART device has the function of sending and receiving. It is connected to the TX and RX of the USART3 through the serial port tool. After power-on, it will first send data through the TX of the USART3.
	   The host computer software sends data to the RX of USART3 through the serial port tool, and the USART3 will send the received data through TX and then send it out.

4. Matters needing attention
    None