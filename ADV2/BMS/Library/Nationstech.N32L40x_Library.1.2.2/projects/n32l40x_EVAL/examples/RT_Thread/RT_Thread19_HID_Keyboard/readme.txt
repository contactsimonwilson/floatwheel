1������˵��

    1��������չʾ USB HID Keyboard �豸

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
    2.ͨ�� USB ������ J3 USB �ڣ�USB ������ɺ�һֱ����"A"

4��ע������
    ��

1. Function description
    1.This routine shows a USB HID Keyboard device

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:     N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock: 48MHz
    	2. USB Clock��48MHz
        3. GPIO:   LED:D1--PA8��D2--PB4
        LOG: USART1: TX--PA9 RX--PA10 Baud rate: 115200

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. Connect the J3 USB port with a USB cable, after the USB mount is completed, always input "A".

4. Matters needing attention
    None.