1������˵��
    1��SLEEPģʽ�Ľ�����˳���


2��ʹ�û���

    �������������KEIL MDK-ARM V5.25

    Ӳ��������
        1������������N32L40XRL-STB V1.0����
        2��MCU��N32L406RBL7


3��ʹ��˵��
    
    ϵͳ���ã�
        1��ʱ��Դ��HSE+PLL
        2��ʱ��Ƶ�ʣ�64MHz
        3������Դ��PA0




    ʹ�÷�����
        ��KEIL�±������¼�������壬���ӵ�������ϵ�����һ�ᣬ�������Ա�С�����»��Ѱ���PA0��LED��תһ��
        ���������Ա�󡣹�һ���ֱ�С��


4��ע������
    ��



1. Function description
    1. Enter and exit the SLEEP mode.

2. Use environment
    Software development environment: KEIL MDK-ARM V5.25
    Hardware environment:
	1, Based on the evaluation board N32L40XRL-STB V1.0 development
	2, MCU: N32L406RBL7

3. Instructions for use    
    System configuration;
	1. Clock source: HSE+PLL
	2. Clock frequency: 108MHz
	3. Wake up source: PA0

    Instructions:
	After compiling under KEIL, it was burned to the evaluation board, connected to the ammeter in series, and after powering on for a while, the current decreased significantly. Press the wake up button PA0,LED reversal once,
	The current increases significantly, and then decreases again.

4. Matters needing attention
    None
