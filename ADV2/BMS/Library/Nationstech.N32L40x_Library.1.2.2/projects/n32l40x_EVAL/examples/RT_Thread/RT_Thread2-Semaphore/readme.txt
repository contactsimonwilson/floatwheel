1������˵��

    1��������չʾ�� RT_Thread �ź����Ĵ�������ȡ���ͷ�

2��ʹ�û���

    /* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
    �����壺N32L43XM-STB N32L40XM-STB V1.1

3��ʹ��˵��

    /* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
    SystemClock��64MHz
    GPIO��PA8 ���� LED(D1) ����PB4 ���� LED(D2) ��˸
    KEY1--PA4
    ��־:   TX--PA9  RX--PA10    �����ʣ�115200

    /* ����Demo�Ĳ��Բ�������� */
    1.��������س���λ����
    2.��������main()���������̣߳�LED1 �̡߳� LED2 �߳� �� KEY �̣߳�LED1 �߳����ڿ��� D1 ����LED2 �߳����ڿ��� D2 500ms��˸��
      KEY �߳�ɨ�谴������ KEY1 ��⵽����ʱ���ͷ��ź�����LED1 �̻߳�ȡ�ź�������ȡ�ɹ��󣬷�ת D1��

4��ע������
    ��

1. Function description
    This example shows the creation, acquisition and release of the RT_Thread semaphore

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock: 64MHz
        2. GPIO: 
                    PA8 controls the LED (D1) to blink; PB4 controls the LED (D2) to blink;
                    KEY1: --PA4��
                    Log: TX--PA9 RX--PA10 Baud rate: 115200

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. This routine creates three threads in main(), LED1 thread, LED2 thread and KEY thread, LED1 thread is used to control D1 on and off, LED2 thread is used to control D2 500ms blink, 
            KEY thread scans the KEY, when KEY1 detects that it is pressed, release the semaphore, LED1 thread obtains the semaphore, and after obtaining it successfully, reverses D6

4. Matters needing attention
    None.