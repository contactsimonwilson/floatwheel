1������˵��

	1��������չʾ�� RT_Thread ϵͳ���� PIN �豸

2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
	�����壺N32L43XM-STB N32L40XM-STB V1.1

3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
	SystemClock��64MHz
	GPIO:	LED:D1--PA8��D2--PB4
	KEY:	KEY1--PA4,KEY2--PA5,KEY3--PA6

	/* ����Demo�Ĳ��Բ�������� */
	1.��������س���λ����
	2.�����̴��������̣߳�LED1 �̡߳� LED2 �̺߳�key�̣߳�LED1 �߳����ڿ��� D1 500ms��˸��LED2 �߳����ڿ��� D2 250ms��˸��
	  key�߳����ڼ��KEY1��KEY2��KEY3״̬��KEY3 ���´����жϣ����ڻص������д�ӡ��־��
    

4�� ע������
    ��

1. Function description
    This routine shows to create PIN devices on the RT_Thread system

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock��64MHz
	2. GPIO:	LED:D1--PA8��D2--PB4
	3. KEY:		KEY1--PA4,KEY2--PA5,KEY3--PA6
                     Log(USART1): TX--PA9 RX--PA10 Baud rate: 115200

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. This routine creates three threads, led1 thread, led2 thread key thread, led1 thread is used to control D1 500ms flashing, led2 thread is used to control D2 250ms flashing, 
            key thread detects KEY0, KEY1 and KEY2, When KEY3 is pressed, the interrupt callback function is called, and the corresponding log is printed when a key is pressed.

4. Matters needing attention
    None.