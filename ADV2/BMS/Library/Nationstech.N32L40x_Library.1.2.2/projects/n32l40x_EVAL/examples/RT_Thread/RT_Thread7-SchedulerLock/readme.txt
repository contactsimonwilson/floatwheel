1������˵��

    1��������չʾ�� RT_Thread ϵͳ���õ�������

2��ʹ�û���

    /* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
    �����壺N32L43XM-STB N32L40XM-STB V1.1

3��ʹ��˵��

    /* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
    SystemClock��64MHz
    ��־�����ڴ�ӡ PA9(TX)�������ʣ�115200

    /* ����Demo�Ĳ��Բ�������� */
    1.��������س���λ����
    2.�Ӻô��ڴ�ӡ����
    3.�����̴��������̣߳�thread1 �̺߳� thread2 �̣߳�thread2 �߳����ȼ����� thread1, thread1 �߳̽��������������ڽ���֮ǰ�������л��� thread2 �̣߳��鿴��ӡ��־

4��ע������
    ��

1. Function description
    This routine is shown in the RT_Thread system call scheduler lock

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock: 64MHz
        Log(USART1): TX--PA9 Baud rate: 115200

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. Connect the serial port printing tool;
        3. This example creates two threads, thread1 thread and thread2 thread. Thread2 thread has a higher priority than thread1 thread. 
            The thread1 thread will lock the scheduler, before unlock, will not switch to the thread2 thread, see the print log

4. Matters needing attention
    None.