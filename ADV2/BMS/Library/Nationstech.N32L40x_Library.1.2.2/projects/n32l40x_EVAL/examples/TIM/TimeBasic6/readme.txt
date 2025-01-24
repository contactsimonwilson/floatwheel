1������˵��
    1��TIM6 ���ø����жϣ�������ʱ��תIO
2��ʹ�û���
    �������������  KEIL MDK-ARM V5.26.2.0
    Ӳ��������      ����N32L40XM-STB_V1.0����
3��ʹ��˵��
    ϵͳ���ã�
        1��ʱ��Դ��
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM6 CLK=32M
        2���жϣ�
            TIM6 �����жϴ򿪣��������ȼ�0�������ȼ�1
        3���˿����ã�
            PC6ѡ��ΪIO���
            PC7ѡ��ΪIO���
            PC8ѡ��ΪIO���
            PC9ѡ��ΪIO���
        4��TIM��
            TIM6ʹ�������ж�
    ʹ�÷�����
        1�������򿪵���ģʽ����ʾ���������߼������ǹ۲�PC6�Ĳ���
        2���������к�TIM6�������ж����ٷ�תPC6��ƽ
4��ע������
    ��

1. Function description
     1. TIM6 uses the update interrupt to generate timing rollover IO
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM6 CLK=32M
         2. Interruption:
             TIM6 update interrupt is turned on, steal priority level 0, sub priority level 1
         3. Port configuration:
             PC6 is selected as IO output
             PC7 is selected as IO output
             PC8 is selected as IO output
             PC9 is selected as IO output
         4. TIM:
             TIM6 enables periodic interrupts
     Instructions:
         1. After compiling, turn on the debug mode, and use the oscilloscope or logic analyzer to observe the PC6 waveform
         2. After the program runs, the periodic interrupt of TIM6 comes to flip the PC6 level
4. Matters needing attention
     without