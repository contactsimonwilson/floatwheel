1������˵��
    1��ͨ��RTC����������SLEEP��
    2�����ڴ�ӡ�����˳�״̬

2��ʹ�û���

    �������������KEIL MDK-ARM V5.25

    Ӳ��������
        1������������N32L40XRL-STB V1.0����
        2��MCU��N32L406RBL7


3��ʹ��˵��
    
    ϵͳ���ã�
        1��RTCʱ��Դ��LSI
        2���͹���ģʽ��SLEEP
        3���������ã�
            - ����ΪUSART2��TX��PA9  RX��PA10��:
            - ����λ��8
            - ֹͣλ��1
            - ��żУ�飺��


    ʹ�÷�����
        ��KEIL�±������¼�������壬ͨ�磬����һ�ᴮ�ڴ�ӡstart low power��˵������͹���ģʽ�ˡ�
        �����ڴ�ӡ���Exit low power��˵����ʱ���ӻ���SLEEP�ˡ�


4��ע������
    ��


1. Function description
    1. Wake up SLEEP through the RTC alarm clock.
    2. Serial port printing enters the exit state

2. Use environment
    Software development environment: KEIL MDK-ARM V5.25
    Hardware environment:
	1, based on the evaluation board N32L40XRL-STB V1.0 development
	2, MCU: N32L406RBL7

3. Instructions for use    
    System configuration;
	1. RTC clock source: LSI
	2. low power mode: SLEEP
	3. Serial port configuration
	- Serial port: USART2 (TX: PA9 RX: PA10) :
	- Data bit: 8
	- Stop bit: 1
	- Parity check: None
	- Baud rate: 115200
    Instructions:
	After compiling in KEIL, burn to the evaluation board, power on, after a while, the serial port prints start low power, indicating that it enters the low power mode.
	If Exit Low power is printed through the serial port, the alarm clock wakes up and sleeps.

4. Matters needing attention
    None