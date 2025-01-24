1������˵��
    1��WWDG��λ���ܡ�


2��ʹ�û���

    �������������KEIL MDK-ARM V5.25

    Ӳ��������
        1������������N32L40XRL-STB V1.0����
        2��MCU��N32L406RBL7


3��ʹ��˵��
    
    ϵͳ���ã�
        1��WWDGʱ��Դ��PCLK1
        2������ֵ��96.3ms < n <131.1ms
        3��ָʾ�ƣ�PA8(LED1)   PB4(LED2)
             



    ʹ�÷�����
        1����KEIL�±������¼�������壬�ϵ��ָʾ��LED2��ͣ����˸��˵������ֵˢ�������������������С�
        2������Delay(110)���������ĳ�132���ϣ�����ϵͳ��һֱ���ڸ�λ״̬��LED1��LED2������


4��ע������
     ��

1. Function description
    1. WWDG reset function.
	
2. Use environment
    Software development environment: KEIL MDK-ARM V5.25.
	
    Hardware environment: 
		1.Developed based on the evaluation board N32L40XRL-STB V1.0
		2.N32L406RBL7
	
3. Instructions for use
    System Configuration;
        1. WWDG clock source: PCLK1

		2. window value: 96.3ms < n <131.1ms

		3. Indicator light: PA8(LED1)   PB4(LED2)


    Instructions:
        1. After compiling under KEIL, it is burned to the evaluation board. After powering on, the indicator light LED2 keeps flashing. The window value is refreshed properly, and the code is running properly.
		2. When the parameter of Delay(110) function  is changed to more than 132, the whole system will always be reset. LED1,LED2 are always on.
		
4. Matters needing attention
    None.