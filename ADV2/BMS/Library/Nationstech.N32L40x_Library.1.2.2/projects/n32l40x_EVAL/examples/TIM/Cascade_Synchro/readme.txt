1������˵��
    1��TIM2�����ſ�TIM3��TIM3�����ſ�TIM4
2��ʹ�û���
    �������������  KEIL MDK-ARM V5.26.2.0
    Ӳ��������      ����N32L40XM-STB_V1.0����
3��ʹ��˵��
    ϵͳ���ã�
        1��ʱ��Դ��
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM2 CLK=32M,TIM3 CLK=32M,TIM4 CLK=32M
        2���˿����ã�
            PA0ѡ��ΪTIM2 CH1���
            PA6ѡ��ΪTIM3 CH1���
            PB6ѡ��ΪTIM4 CH1���
        3��TIM��
            TIM2 �������ſ�TIM3��TIM3�������ſ�TIM4
    ʹ�÷�����
        1�������򿪵���ģʽ����ʾ���������߼������ǹ۲�TIM2 CH1��TIM3 CH1��TIM4 CH1����
        2��TIM3 4������TIM2��TIM4 4������TIM3
4��ע������
    ��

1. Function description
     1. TIM2 cycle gate TIM3, TIM3 cycle gate TIM4
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM2 CLK=32M,TIM3 CLK=32M,TIM4 CLK=32M
         2. Port configuration:
             PA0 is selected as TIM2 CH1 output
             PA6 is selected as TIM3 CH1 output
             PB6 is selected as TIM4 CH1 output
         3. TIM:
             The period gate of TIM2 controls TIM3, the period gate of TIM3 controls TIM4
     Instructions:
         1. After compiling, turn on the debug mode, use an oscilloscope or logic analyzer to observe the waveforms of TIM2 CH1, TIM3 CH1, TIM4 CH1
         2. TIM3 4 times cycle TIM2, TIM4 4 times cycle TIM3
4. Matters needing attention
     without