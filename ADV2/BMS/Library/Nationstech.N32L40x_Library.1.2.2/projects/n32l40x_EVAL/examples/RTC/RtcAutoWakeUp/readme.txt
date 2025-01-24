1������˵��
    1��ͨ���趨����ʱ�䴥���жϡ�
    2��ͨ�����ѱ�־λ������IO���

2��ʹ�û���

    �������������KEIL MDK-ARM V5.25
    Ӳ��������
        1������������N32L40XML-STB V1.0����
        2��MCU��N32L406MBL7

3��ʹ��˵��
    
    ϵͳ����:
        1�������Ի���ʱ��Դ��RTCCLK��1HZ��
        2����������ڣ�PC13
        3���������ã�
        3���������ã�
                    - ����ΪUSART1��TX��PA9  RX��PA10��:
                    - ����λ��8
                    - ֹͣλ��1
                    - ��żУ�飺��
                    - �����ʣ� 115200 
    ʹ�÷�����
        1���������¼�������壬�ϵ�󣬴���ÿ��5s���ӡ:Stop2 Wakeup From RTC
        2���趨#define  RTC_ALARM_TEST_TYPE  RTC_ALARM_TEST_TYPE_OUTPUT���������¼�������壬
           �ϵ��PC13ÿ��5S��תһ��(4s�ߵ�ƽ��1s�͵�ƽ)��
                
4��ע������
    ��


1. Function description

	1. Trigger interrupt by setting wake up time
	2. Configure IO output by wake up flag bit

2. Use environment

	Software development environment: KEIL MDK-ARM V5.25
	Hardware environment:
		1. based on the evaluation board N32L40XML-STB V1.0 development
		2. MCU��N32L406MBL7

3. Instructions for use

	System configuration:

		1. periodic wake up clock source: RTCCLK (1HZ)
		2. Wakeup IO output: PC13
		3. Serial port configuration:

							- Serial port: USART1 (TX: PA9 RX: PA10) :
							- Data bit: 8
							- Stop bit: 1
							- Parity check: None
							- Baud rate: 115200

	Instructions:
		1. After compilation, it is burned to the evaluation board. After power-on, the serial port will print "Stop2 Wakeup From RTC" every 5s
		2. When set "#define RTC_ALARM_TEST_TYPE RTC_ALARM_TEST_TYPE_OUTPUT", compile and burn to evaluation board,After power-on, the PC13 is turned over every 5S(4s high level, 1S low level).

4. Matters needing attention
	None