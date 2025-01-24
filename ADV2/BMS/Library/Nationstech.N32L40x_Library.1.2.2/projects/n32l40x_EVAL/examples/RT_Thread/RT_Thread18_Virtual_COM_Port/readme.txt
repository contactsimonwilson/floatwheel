1������˵��

    1��������չʾ USB CDC �豸

2��ʹ�û���

    /* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
    �����壺N32L43XM-STB N32L40XM-STB V1.1

3��ʹ��˵��

    /* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
    SystemClock��48MHz
    USB Clock��48MHz
    GPIO:   LED:D1--PA8��D2--PB4
    ��־��  USART1: TX--PA9  RX--PA10    �����ʣ�115200


    /* ����Demo�Ĳ��Բ�������� */
    1.��������س���λ����
    2.ͨ�� USB ������ J3 USB �ڣ�USB ������ɺ��ڵ����豸�����п��Կ��������Ĵ��ڣ��� USB ���⴮�ڣ����Կ�������һֱ���յ����ݣ����⴮��Ҳ���Է������ݣ����͵����ݿ���ͨ����־���ڽ��д�ӡ���

4��ע������
    ��

1. Function description
    This routine shows a USB CDC device

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock: 48MHz
        2. USB Clock��48MHz
        3. GPIO:   LED:D1--PA8��D2--PB4
        LOG: USART1: TX--PA9 RX--PA10 Baud rate: 115200

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. Connect the USB cable to the J3 USB port. After the USB is mounted, you can see the new serial port in computer device management. 
           Open the USB virtual serial port, you can see that the serial port is directly received, the virtual serial port can also send data, and the transmitted data can be printed through the log serial port.

4. Matters needing attention
    None.