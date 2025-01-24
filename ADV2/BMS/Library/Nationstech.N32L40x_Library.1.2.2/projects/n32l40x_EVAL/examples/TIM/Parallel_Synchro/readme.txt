1������˵��
    1��TIM2 �����ſ�TIM3 TIM4
2��ʹ�û���
    �������������  KEIL MDK-ARM V5.26.2.0
    Ӳ��������      ����N32L40XM-STB_V1.0����
3��ʹ��˵��
    ϵͳ���ã�
        1��ʱ��Դ��
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM2 CLK=32M,TIM3 CLK=32M,TIM4 CLK=32M
        2���˿����ã�
            PA0ѡ��ΪTIM2��CH1���
            PA6ѡ��ΪTIM3��CH1���
            PB6ѡ��ΪTIM4��CH1���
        3��TIM��
            TIM2 ���ڴ����ſ�TIM3 TIM4��CH1,��TIM3Ϊ10������TIM2����TIM4Ϊ5������TIM2
    ʹ�÷�����
        1�������򿪵���ģʽ����ʾ���������߼������ǹ۲�TIM2 CH1��TIM3 CH1��TIM4 CH1�Ĳ���
        2��TIM4����5����TIM2��TIM3����10����TIM2
4��ע������
    ��
    
1. Function description
     1. TIM2 cycle gating TIM3 TIM4
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM2 CLK=32M,TIM3 CLK=32M,TIM4 CLK=32M
         2. Port configuration:
             PA0 is selected as the CH1 output of TIM2
             PA6 is selected as the CH1 output of TIM3
             PB6 is selected as the CH1 output of TIM4
         3. TIM:
             TIM2 cycle triggers the CH1 of gated TIM3 TIM4, that is, TIM3 is 10 times the period TIM2, that is, TIM4 is 5 times the period TIM2
     Instructions:
         1. After compiling, turn on the debug mode and use an oscilloscope or logic analyzer to observe the waveforms of TIM2 CH1, TIM3 CH1, and TIM4 CH1
         2. The cycle of TIM4 is 5 times that of TIM2, and the cycle of TIM3 is 10 times that of TIM2.
4. Matters needing attention
     without