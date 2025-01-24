1������˵��
    1��TIM1���3·��������
2��ʹ�û���
    �������������  KEIL MDK-ARM V5.26.2.0
    Ӳ��������      ����N32L40XM-STB_V1.0����
3��ʹ��˵��
    ϵͳ���ã�
        1��ʱ��Դ��
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM1 CLK=64M
        2���˿����ã�
            PA8ѡ��ΪTIM1 CH1���
            PA9ѡ��ΪTIM1 CH2���
            PA10ѡ��ΪTIM1 CH3���
            PB13ѡ��ΪTIM1 CH1N���
            PB14ѡ��ΪTIM1 CH2N���
            PB15ѡ��ΪTIM1 CH3N���
            PB12ѡ��ΪTIM1 Breakin����
        3��TIM��
            TIM1 6·��������������IOMɲ��
    ʹ�÷�����
        1�������򿪵���ģʽ����ʾ���������߼������ǹ۲�TIM1�Ĳ���
        2���ɹ۲쵽3·��������
4��ע������
    ��
    
/***   For English user   ***/    
1. Function description
     1. TIM1 outputs 3 complementary waveforms
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM1 CLK=64M
         2. Port configuration:
             PA8 is selected as TIM1 CH1 output
             PA9 is selected as TIM1 CH2 output
             PA10 is selected as TIM1 CH3 output
             PB13 is selected as TIM1 CH1N output
             PB14 is selected as TIM1 CH2N output
             PB15 is selected as TIM1 CH3N output
             PB12 is selected as TIM1 Breakin input
         3. TIM:
             TIM1 6-way complementary with dead zone, no IOM brake
     Instructions:
         1. After compiling, turn on the debug mode, and use the oscilloscope or logic analyzer to observe the waveform of TIM1
         2. 3 complementary waveforms can be observed
4. Matters needing attention
     without