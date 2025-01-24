1������˵��
    1��TIM3 TIM4��TIM1�����¼���
2��ʹ�û���
    �������������  KEIL MDK-ARM V5.26.2.0
    Ӳ��������      ����N32L40XM-STB_V1.0����
3��ʹ��˵��
    ϵͳ���ã�
        1��ʱ��Դ��
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM1 CLK=64M,TIM3 CLK=32M,TIM4 CLK=32M
        2���˿����ã�
            PA6ѡ��ΪTIM3��CH1���
            PB6ѡ��ΪTIM4��CH1���
            PA8ѡ��ΪTIM1��CH1���
        3��TIM��
            TIM1 CH1 ���ڴ���TIM3 TIM4���ſ�
    ʹ�÷�����
        1�������򿪵���ģʽ����ʾ���������߼������ǹ۲�TIM1 CH1��TIM3 CH1��TIM4 CH1�Ĳ���
        2���������к�TIM3 15������TIM1��TIM4 10������TIM1
4��ע������
    ��

1. Function description
     1. TIM3 TIM4 counts under the TIM1 cycle
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM1 CLK=64M,TIM3 CLK=32M,TIM4 CLK=32M
         2. Port configuration:
             PA6 is selected as the CH1 output of TIM3
             PB6 is selected as the CH1 output of TIM4
             PA8 is selected as the CH1 output of TIM1
         3. TIM:
             TIM1 CH1 periodically triggers the gating of TIM3 TIM4
     Instructions:
         1. After compiling, turn on the debug mode and use an oscilloscope or logic analyzer to observe the waveforms of TIM1 CH1, TIM3 CH1, and TIM4 CH1
         2. After the program runs, TIM3 15 times cycle TIM1, TIM4 10 times cycle TIM1
4. Matters needing attention
     without