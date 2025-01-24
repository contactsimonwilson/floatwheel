1������˵��
    1��TIM1 CH2�ſ�CH1��TIM3 TIM4
2��ʹ�û���
    �������������  KEIL MDK-ARM V5.26.2.0
    Ӳ��������      ����N32L40XM-STB_V1.0����
3��ʹ��˵��
    ϵͳ���ã�
        1��ʱ��Դ��
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM1 CLK=64M,TIM3 CLK=32M,TIM4 CLK=32M
        2���˿����ã�
            PA8ѡ��ΪTIM1 CH1���
            PA9ѡ��ΪTIM1 CH2����
            PA6ѡ��ΪTIM3 CH1���
            PB6ѡ��ΪTIM4 CH1���
        3��TIM��
            TIM1 CH2 �ſ�CH1���ſ�TIM3,TIM4
    ʹ�÷�����
        1�������򿪵���ģʽ����ʾ���������߼������ǹ۲�TIM1 CH1,TIM3 CH1,TIM4 CH1�Ĳ���
        2��TIM1 CH2�ߵ�ƽ��ʱ����ʼ�������͵�ƽֹͣ
4��ע������
    ��

1. Function description
     1. TIM1 CH2 gated CH1 and TIM3 TIM4
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM1 CLK=64M,TIM3 CLK=32M,TIM4 CLK=32M
         2. Port configuration:
             PA8 is selected as TIM1 CH1 output
             PA9 is selected as TIM1 CH2 input
             PA6 is selected as TIM3 CH1 output
             PB6 is selected as TIM4 CH1 output
         3. TIM:
             TIM1 CH2 gated CH1, gated TIM3, TIM4
     Instructions:
         1. After compiling, turn on the debug mode, use an oscilloscope or logic analyzer to observe the waveforms of TIM1 CH1, TIM3 CH1, TIM4 CH1
         2. TIM1 CH2 high level timer starts counting, low level stops
4. Matters needing attention
     without