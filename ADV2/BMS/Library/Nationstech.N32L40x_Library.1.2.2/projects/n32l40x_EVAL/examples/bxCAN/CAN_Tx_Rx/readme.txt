1������˵��
    1��CAN���ͽ�������


2��ʹ�û���

    �������������KEIL MDK-ARM V5.25

    Ӳ��������
        1������������N32L40XML-STB_V1.0����
        2��MCU��N32L406MB


3��ʹ��˵��
    
    ϵͳ���ã�
    /* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
        SystemClock��108MHz
        USART��TX - PA9�� RX - PA10��������115200
        CAN�� RX - PB8�� TX - PB9��������500K������ģʽ

    /* ����Demo�Ĳ��Բ�������� */
        1.��������س���λ���У�
        2.�鿴���ڴ�ӡ��Ϣ��CANÿ��1s����һ֡��׼֡��һ֡��չ֡
          ���ڽ�MCU���յ�������֡��ӡ����
                     
                 
4��ע������


1. Function description
	1. CAN send and receive routines


2. Use environment

	Software development environment: KEIL MDK-ARM V5.25

	Hardware environment:
		1. Developed based on the evaluation board N32L40XML-STB_V1.0
		2. MCU: N32L406MB


3. Instructions for use
    
	 System Configuration;
	/* Describe related module configuration methods; for example: clock, I/O, etc. */
	SystemClock: 108MHz
	USART: TX - PA9, RX - PA10, baud rate 115200
	CAN: RX - PB8, TX - PB9, baud rate 500K, normally mode

	/* Describe the test steps and phenomena of the Demo */
	1. After compiling, download the program to reset and run;
	2. Check the serial port printing information, CAN sends a standard frame and an extended frame every 1s.
	The serial port prints out the extend frame received by the MCU
                     
                 
4. Matters needing attention