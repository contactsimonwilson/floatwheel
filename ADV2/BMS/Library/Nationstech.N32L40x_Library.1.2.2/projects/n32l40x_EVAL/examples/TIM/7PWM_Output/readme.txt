1������˵��
    1��TIM1��TIM8���3·�������κ�һ·CH4����
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
            PA11ѡ��ΪTIM1 CH4���
            PC6ѡ��ΪTIM8 CH1���
            PC7ѡ��ΪTIM8 CH2���
            PC8ѡ��ΪTIM8 CH3���
            PA7ѡ��ΪTIM8 CH1N���
            PB0ѡ��ΪTIM8 CH2N���
            PB1ѡ��ΪTIM8 CH3N���
            PC9ѡ��ΪTIM8 CH4���
        3��TIM��
            TIM1 6·�������,CH4���
            TIM8 6·�������,CH4���
    ʹ�÷�����
        1�������򿪵���ģʽ����ʾ���������߼������ǹ۲�TIM1 TIM8���������
        2���������TIM1 3·������һ·CH4��TIM8 3·������һ·CH4
4��ע������
    ��

1. Function description
    1. TIM1 and TIM8 output 3 complementary waveforms and one CH4 waveform
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
            PA11 is selected as TIM1 CH4 output
            PC6 is selected as TIM8 CH1 output
            PC7 is selected as TIM8 CH2 output
            PC8 is selected as TIM8 CH3 output
            PA7 is selected as TIM8 CH1N output
            PB0 is selected as TIM8 CH2N output
            PB1 is selected as TIM8 CH3N output
            PC9 is selected as TIM8 CH4 output
        3. TIM:
            TIM1 6 complementary outputs, CH4 output
            TIM8 6 complementary outputs, CH4 output
    Instructions:
        1. After compiling, turn on the debug mode, use an oscilloscope or logic analyzer to observe the output waveform of TIM1 TIM8
        2. Output waveform TIM1 3 complementary plus one CH4, TIM8 3 complementary plus one CH4
4. Matters needing attention
    without