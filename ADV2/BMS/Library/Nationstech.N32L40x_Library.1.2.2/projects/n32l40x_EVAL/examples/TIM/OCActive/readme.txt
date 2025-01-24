1������˵��
    1��TIM3 CH1 CH2 CH3 CH4 �ﵽCCֵ�����ACTIVE��ƽ
2��ʹ�û���
    �������������  KEIL MDK-ARM V5.26.2.0
    Ӳ��������      ����N32L40XM-STB_V1.0����
3��ʹ��˵��
    ϵͳ���ã�
        1��ʱ��Դ��
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM3 CLK=32M
        2���˿����ã�
            PA6ѡ��ΪTIM3 CH1���
            PA7ѡ��ΪTIM3 CH2���
            PB0ѡ��ΪTIM3 CH3���
            PB1ѡ��ΪTIM3 CH4���
            PC6ѡ��ΪIO ���
        3��TIM��
            TIM3 CH2 �����ز����жϴ�
    ʹ�÷�����
        1�������򿪵���ģʽ����ʾ���������߼������ǹ۲�TIM2 CH1 CH2 CH3 CH4�Ĳ���
        2����ʱ�����е�CC1 CC2 CC3 CC4֮�󣬶�Ӧͨ���������ΪActive
4��ע������
    ��
    
1. Function description
     1. After TIM3 CH1 CH2 CH3 CH4 reaches the CC value, it outputs ACTIVE level
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM3 CLK=32M
         2. Port configuration:
             PA6 is selected as TIM3 CH1 output
             PA7 is selected as TIM3 CH2 output
             PB0 is selected as TIM3 CH3 output
             PB1 is selected as TIM3 CH4 output
             PC6 is selected as IO output
         3. TIM:
             TIM3 CH2 rising edge capture interrupt is turned on
     Instructions:
         1. After compiling, turn on the debug mode, use an oscilloscope or logic analyzer to observe the waveform of TIM2 CH1 CH2 CH3 CH4
         2. After the timer runs to CC1 CC2 CC3 CC4, the output of the corresponding channel becomes Active
4. Matters needing attention
     without