1������˵��
    1��LP SLEEPģʽ�Ľ�����˳���


2��ʹ�û���

    �������������KEIL MDK-ARM V5.25

    Ӳ��������
        1������������N32L40XRL-STB V1.0����
        2��MCU��N32L406RBL7


3��ʹ��˵��
    
    ϵͳ���ã�
        1��ʱ��Դ��HSE+PLL/MSI
        2��ʱ��Ƶ�ʣ�48M/4M
        3���������ã�
                 - ����ΪUSART1��TX��PA9  RX��PA10��:
                 - ����λ��8
                 - ֹͣλ��1
                 - ��żУ�飺��
                 - �����ʣ� 115200 



    ʹ�÷�����
        ��KEIL�±������¼�������壬���ӵ������ϵ���һ�ᣬ�������Ա�С�����»��Ѱ���PA0���������
        �ٹ�һ�ᣬ�����ֱ�С��ͬʱLED��˸��
            


4��ע������
    LP RUN���Ѻ���Ƚ���LP RUN������LP RUN�˳���RUNģʽ


1. Function description
	1. Enter and exit LP SLEEP mode.

2. Use environment
	Software development environment: KEIL MDK-ARM V5.25
	Hardware environment:
	1. Development based on evaluation board N32L40XRL-STB V1.0
	2. MCU: N32L406RBL7

3. Instructions for use   
    System configuration;
	1. Clock source: HSE+PLL/MSI
	2. Clock frequency: 48M/4M
	3. Serial port configuration
	- Serial port: USART1 (TX: PA9 RX: PA10) :
	- Data bit: 8
	- Stop bit: 1
	- Parity check: None
	- Baud rate: 115200
    Instructions:
	After compiling under KEIL, it was burned to the evaluation board and connected to the ammeter in series. After powering on for a while, the current decreased significantly. Press the wake button PA0 and the current increases.
	After a while, the current drops again and the LED flashes.
            
4. Matters needing attention
    After waking up from LP RUN, the system enters LP RUN and exits the RUN mode from LP RUN

