1������˵��

    1��������չʾ�� RT_Thread ��̬�������Ͷ�̬�������Ĵ�������ȡ���ͷ�

2��ʹ�û���

    /* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
    �����壺N32L43XM-STB N32L40XM-STB V1.1

3��ʹ��˵��

    /* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
    SystemClock��64MHz
    ��־��TX--PA9  RX--PA10 �������ʣ�115200

    /* ����Demo�Ĳ��Բ�������� */
    1.��������س���λ����
    2.�Ӻô��ڴ�ӡ����
    3.��������main()���洴�������̣߳�thread1 �̺߳� thread2 �̣߳�
      �鿴��ӡ��־��thread2 �Ȼ�ȡ��̬���������ȵ� thread2 �ͷž�̬�������� thread1 ���ܻ�ȡ����̬�����������ͷž�̬��������
      Ȼ�� thread2 ��ȡ��̬���������ȵ� thread2 �ͷŶ�̬�������� thread1 ���ܻ�ȡ����̬����������ɾ����̬��������

4��ע������
    ��

1. Function description
    This routine shows the creation, acquisition, and release of static and dynamic mutex in RT_Thread

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock: 64MHz
        2. GPIO: 
                    Log: TX--PA9 RX--PA10 Baud rate: 115200

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. Connect the serial port printing tool;
        3. This example creates two threads in main(), thread1 thread and thread2 thread, and checks the print log. 
            Thread2 first obtains the static mutex, after thread2 releases the static mutex, thread1 can get the static mutex, then release the static mutex;
            Thread2 then gets the dynamic mutex, after thread2 releases the dynamic mutex, thread1 can get the dynamic mutex, and then delete the dynamic mutex

4. Matters needing attention
    None.