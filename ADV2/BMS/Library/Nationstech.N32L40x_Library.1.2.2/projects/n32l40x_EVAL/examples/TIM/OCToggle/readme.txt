1������˵��
    1��TIM3 CH1 CH2 CH3 CH4 �ﵽCCֵ�������ת�����ұȽ�ֵ�ۼ�
2��ʹ�û���
    �������������  KEIL MDK-ARM V5.26.2.0
    Ӳ��������      ����N32L40XM-STB_V1.0����
3��ʹ��˵��
    ϵͳ���ã�
        1��ʱ��Դ��
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM3 CLK=32M
        2���жϣ�
            TIM3 �Ƚ��жϴ򿪣��������ȼ�0�������ȼ�0
        3���˿����ã�
            PA6ѡ��ΪTIM3��CH1���
            PA7ѡ��ΪTIM3��CH2���
            PB0ѡ��ΪTIM3��CH3���
            PB1ѡ��ΪTIM3��CH4���
        4��TIM��
            TIM3 ���ú�CH1 CH2 CH3 CH4�ıȽ�ֵ�����ת�����򿪱Ƚ��ж�
    ʹ�÷�����
        1�������򿪵���ģʽ����ʾ���������߼������ǹ۲�TIM3 ��CH1 CH2 CH3 CH4�Ĳ���
        2��ÿ���ﵽ�Ƚ�ֵʱ�������ת������������ͬ���ıȽ�ֵ������ռ�ձ�Ϊ50%
4��ע������
    ��

1. Function description
    1. When TIM3 CH1 CH2 CH3 CH4 reaches the CC value, the output is reversed, and the comparison value is accumulated
2. Use environment
    Software development environment: KEIL MDK-ARM V5.26.2.0
    Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
    System Configuration;
        1. Clock source:
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM3 CLK=32M
        2. Interruption:
            TIM3 compare interrupt is turned on, preemption priority 0, subpriority 0
        3. Port configuration:
            PA6 is selected as the CH1 output of TIM3
            PA7 is selected as the CH2 output of TIM3
            PB0 is selected as the CH3 output of TIM3
            PB1 is selected as the CH4 output of TIM3
        4. TIM:
            TIM3 configures the comparison value output of CH1, CH2, CH3, CH4, and turns on the comparison interrupt
    Instructions:
        1. After compiling, turn on the debug mode, use an oscilloscope or logic analyzer to observe the waveform of CH1 CH2 CH3 CH4 of TIM3
        2. Whenever the comparison value is reached, the output is reversed, and the same comparison value is increased again, and the waveform duty cycle is 50%
4. Matters needing attention
    without