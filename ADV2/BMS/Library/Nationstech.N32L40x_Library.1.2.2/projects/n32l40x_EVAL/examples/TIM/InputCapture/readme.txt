1������˵��
    1��TIM3 CH2�����ؼ���Ƶ��
2��ʹ�û���
    �������������  KEIL MDK-ARM V5.26.2.0
    Ӳ��������      ����N32L40XM-STB_V1.0����
3��ʹ��˵��
    ϵͳ���ã�
        1��ʱ��Դ��
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM3 CLK=32M
        2���жϣ�
            TIM3 CH2�������жϴ򿪣��������ȼ�0�������ȼ�1
        3���˿����ã�
            PA7ѡ��ΪTIM3 CH2����
            PA3ѡ��ΪIO ���
        4��TIM��
            TIM3 CH2 �����ز����жϴ�
    ʹ�÷�����
        1�������򿪵���ģʽ������PA3��PA7��������TIM3Freq��ӵ�watch����
        2���������PA3��ƽ��ת�󣬲鿴TIM3Freq�����Ƶ��ֵ
4��ע������
    ��

1. Function description
     1. TIM3 CH2 rising edge calculation frequency
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM3 CLK=32M
         2. Interruption:
             TIM3 CH2 rising edge interrupt is turned on, the preemption priority is 0, and the subpriority is 1
         3. Port configuration:
             PA7 is selected as TIM3 CH2 input
             PA3 is selected as IO output
         4. TIM:
             TIM3 CH2 rising edge capture interrupt is turned on
     Instructions:
         1. After compiling, open the debug mode, connect PA3 and PA7, and add the variable TIM3Freq to the watch window
         2. After the program controls the level of PA3 to flip, check the frequency value calculated by TIM3Freq
4. Matters needing attention
     without