1������˵��

	1��������չʾ�� RT_Thread Finsh ���

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
   	2.ͨ�����ڹ��߿��Կ�����ӡ finsh>��Ĭ��C-styleģʽ������ͨ������msh()�л���mshģʽ��������help����ӡ��Ϣ���£�
   	 msh >help
     RT-Thread shell commands:
     version          - show RT-Thread version information
     list_thread      - list thread
   	 list_sem         - list semaphore in system
   	 list_mutex       - list mutex in system
   	 list_timer       - list timer in system
     list_device      - list device in system
   	 exit             - return to RT-Thread shell mode.
   	 help             - RT-Thread shell help.
   	 ps               - List threads in the system.
   	 free             - Show the memory usage in the system.

4��ע������
	ͨ�����ڷ�������ʱ��Ҫ��ѡ�������У�����mshģʽ������exti���ص�C-styleģʽ

1. Function description
    This routine is shown in the RT_Thread Finsh component

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock: 64MHz
	2. GPIO:	LED:	D1--PA8  D2--PB4
        Log(USART1): TX--PA9 RX--PA10 Baud rate: 115200

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. This routine creates a led0 thread, in the led0 thread D6 500ms cycle flashing
        3. Print finsh> through the serial tool, the default C-style mode. You can switch to the msh mode by entering msh() and then entering help. The following information is displayed:
             msh >help
             RT-Thread shell commands:
             version           - show RT-Thread version information
             list_thread      - list thread
             list_sem          - list semaphore in system
             list_mutex      - list mutex in system
             list_timer        - list timer in system
             list_device      - list device in system
             exit                - return to RT-Thread shell mode.
             help               - RT-Thread shell help.
             ps                  - List threads in the system.
             free               - Show the memory usage in the system.

4. Matters needing attention
    When sending a command by serial port, you need to select the sending new row. After entering the msh mode, enter exti to return to C-style mode.