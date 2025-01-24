1������˵��
    1��TIM2 CH1 CH2 CH3 CH4 �ﵽCCֵ�󣬶�Ӧ����PC6 PC7 PC8 PC9��IO��ƽ
2��ʹ�û���
    �������������  KEIL MDK-ARM V5.26.2.0
    Ӳ��������      ����N32L40XM-STB_V1.0����
3��ʹ��˵��
    ϵͳ���ã�
        1��ʱ��Դ��
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM2 CLK=32M
        2���жϣ�
            TIM2 �Ƚ��жϴ򿪣��������ȼ�0�������ȼ�1
        3���˿����ã�
            PC6ѡ��ΪIO ���
            PC7ѡ��ΪIO ���
            PC8ѡ��ΪIO ���
            PC9ѡ��ΪIO ���
        4��TIM��
            TIM2 ���ú�CH1 CH2 CH3 CH4�ıȽ�ֵ�����򿪱Ƚ��ж�
    ʹ�÷�����
        1�������򿪵���ģʽ����ʾ���������߼������ǹ۲�PC6 PC7 PC8 PC9�Ĳ���
        2����ʱ���˽���CC1 CC2 CC3 CC4�жϺ�,��Ӧ����PC6 PC7 PC8 PC9��IO
4��ע������
    ��

1. Function description
     1. After TIM2 CH1 CH2 CH3 CH4 reaches the CC value, correspondingly pull down the IO level of PC6, PC7, PC8, PC9
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM2 CLK=32M
         2. Interruption:
             TIM2 compare interrupt is turned on, preemption priority is 0, subpriority 1
         3. Port configuration:
             PC6 is selected as IO output
             PC7 is selected as IO output
             PC8 is selected as IO output
             PC9 is selected as IO output
         4. TIM:
             TIM2 configures the compare value of CH1, CH2, CH3, CH4, and turns on the compare interrupt
     Instructions:
         1. After compiling, turn on the debug mode, and use an oscilloscope or logic analyzer to observe the waveforms of PC6, PC7, PC8, and PC9
         2. After the timer enters the CC1 CC2 CC3 CC4 interrupt, the corresponding pull down the IO of PC6 PC7 PC8 PC9
4. Matters needing attention
     without