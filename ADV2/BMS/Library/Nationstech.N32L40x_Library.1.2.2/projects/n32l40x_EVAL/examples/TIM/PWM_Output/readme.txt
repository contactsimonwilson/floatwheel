1������˵��
    1��TIM3 CH1 CH2 CH3 CH4���Ƶ����ͬռ�ձȲ�ͬ��PWM
2��ʹ�û���
    �������������  KEIL MDK-ARM V5.26.2.0
    Ӳ��������      ����N32L40XM-STB_V1.0����
3��ʹ��˵��
    ϵͳ���ã�
        1��ʱ��Դ��
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM3 CLK=32M
        2���˿����ã�
            PA6ѡ��ΪTIM3��CH1���
            PA7ѡ��ΪTIM3��CH2���
            PB0ѡ��ΪTIM3��CH3���
            PB1ѡ��ΪTIM3��CH4���
        3��TIM��
            TIM3 CH1 CH2 CH3 CH4������ȣ�ռ�ձȲ���
    ʹ�÷�����
        1�������򿪵���ģʽ����ʾ���������߼������ǹ۲�TIM3 CH1��CH2��CH3��CH4�Ĳ���
        2���������к󣬲���4·�������ռ�ձȲ�ͬ��PWM�ź�
4��ע������
    ��

1. Function description
     1. TIM3 CH1 CH2 CH3 CH4 outputs PWM with the same frequency and different duty cycles
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM3 CLK=32M
         2. Port configuration:
             PA6 is selected as the CH1 output of TIM3
             PA7 is selected as the CH2 output of TIM3
             PB0 is selected as the CH3 output of TIM3
             PB1 is selected as the CH4 output of TIM3
         3. TIM:
             TIM3 CH1 CH2 CH3 CH4 has the same period, and the duty cycle is not equal
     Instructions:
         1. After compiling, turn on the debug mode and use an oscilloscope or logic analyzer to observe the waveforms of TIM3 CH1, CH2, CH3, CH4
         2. After the program runs, 4 PWM signals with equal period and different duty cycle are generated
4. Matters needing attention
     without