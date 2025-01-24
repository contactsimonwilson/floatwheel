1������˵��
    1��systick 100ms����TIM1���6�����ನ��
2��ʹ�û���
    �������������  KEIL MDK-ARM V5.26.2.0
    Ӳ��������      ����N32L40XM-STB_V1.0����
3��ʹ��˵��
    ϵͳ���ã�
        1��ʱ��Դ��
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM1 CLK=64M
        2���жϣ�
            TIM1 COM�¼��жϴ򿪣��������ȼ�0�������ȼ�1
            Systick 100ms�жϣ����ȼ�0
        3���˿����ã�
            PA8ѡ��ΪTIM1 CH1���
            PA9ѡ��ΪTIM1 CH2���
            PA10ѡ��ΪTIM1 CH3���
            PB13ѡ��ΪTIM1 CH1N���
            PB14ѡ��ΪTIM1 CH2N���
            PB15ѡ��ΪTIM1 CH3N���
            PB12ѡ��ΪTIM1 Breakin����
        4��TIM��
            TIM1 6·�����������ģʽ����ɲ������COM�ж�
    ʹ�÷�����
        1�������򿪵���ģʽ����ʾ���������߼������ǹ۲�TIM1���������
        2��ÿ��100ms systick����COM�жϣ���TIM��COM�ж��������AB AC BC BA CA CB��6�����ನ��
4��ע������
    ��

1. Function description
    1. Systick 100ms triggers TIM1 to output 6-step commutation waveform
2. Use environment
    Software development environment: KEIL MDK-ARM V5.26.2.0
    Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
    System Configuration;
        1. Clock source:
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM1 CLK=64M
        2. Interruption:
            TIM1 COM event interrupt is turned on, steal priority level 0, sub-priority level 1
            Systick 100ms interrupt, priority 0
        3. Port configuration:
            PA8 is selected as TIM1 CH1 output
            PA9 is selected as TIM1 CH2 output
            PA10 is selected as TIM1 CH3 output
            PB13 is selected as TIM1 CH1N output
            PB14 is selected as TIM1 CH2N output
            PB15 is selected as TIM1 CH3N output
            PB12 is selected as TIM1 Breakin input
        4. TIM:
            TIM1 6-way complementary freeze output mode, no brake, COM interrupt
    Instructions:
        1. After compiling, turn on the debug mode, and use an oscilloscope or logic analyzer to observe the output waveform of TIM1
        2. The COM interrupt is triggered by the systick every 100ms, and the 6-step commutation waveform of AB AC BC BA CA CB is output in the TIM COM interrupt
4. Matters needing attention
    without

    