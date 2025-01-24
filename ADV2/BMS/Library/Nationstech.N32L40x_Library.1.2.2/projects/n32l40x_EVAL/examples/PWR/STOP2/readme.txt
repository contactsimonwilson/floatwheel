1������˵��
    1��STOP2ģʽ�Ľ�����˳���


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
	��KEIL�±������¼�������壬���ϵ������ϵ���ֵ�����mA������uA����
           ���»��Ѱ���(PA0),�����ֻص���mA���𣬹���һ���ֽ���uA,����LED��ת��


4��ע������
    �����������ĵ�ʱ��Ҫע��ȥ��LEDȥ��
    ��SRAM1��SRAM2������



1. Function description
    1. Enter and exit STOP2 mode.

2. Use environment
    Software development environment: KEIL MDK-ARM V5.25
    Hardware environment:
	1. Development based on evaluation board N32L40XRL-STB V1.0
	2. MCU: N32L406RBL7

3. Instructions for use    
    System configuration;
	1. Clock source: HSE+PLL
	2, clock frequency: 64MHz
	3. Wake up source: PA0
               
    Instructions:
	After compiling in KEIL, it was burned to the evaluation board, connected to the ammeter, and found that the current dropped from mA to uA level after powering on.
	Press the wake button (PA0), and the current returns to mA level. After a while, it drops to uA and LED1 reverses.

4. Matters needing attention
    ��When evaluating power consumption, we should pay attention to removing LED to measure
    ��SRAM1 and SRAM2 are configurable
