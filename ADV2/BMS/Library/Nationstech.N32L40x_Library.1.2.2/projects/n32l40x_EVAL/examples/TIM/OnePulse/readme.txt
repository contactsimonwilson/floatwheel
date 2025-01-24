1������˵��
    1��TIM4 CH2�����ش���CH1���һ��������
2��ʹ�û���
    �������������  KEIL MDK-ARM V5.26.2.0
    Ӳ��������      ����N32L40XM-STB_V1.0����
3��ʹ��˵��
    ϵͳ���ã�
        1��ʱ��Դ��
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM4 CLK=32M
        2���˿����ã�
            PB6ѡ��ΪTIM4��CH1���
            PB7ѡ��ΪTIM4��CH2����
            PA3ѡ��ΪIO���
        3��TIM��
            TIM4 ����CH2�����ش���CH1���һ��������
    ʹ�÷�����
        1�������򿪵���ģʽ��PA3����PB7����ʾ���������߼������ǹ۲�TIM4 ��CH1 �Ĳ���
        2��������PA3�������أ�TIM4 CH1���һ��������
4��ע������
    ��

/***   For English user ***/
1. Function description
     1. The rising edge of TIM4 CH2 triggers CH1 to output a single pulse
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM4 CLK=32M
         2. Port configuration:
             PB6 is selected as the CH1 output of TIM4
             PB7 is selected as the CH2 input of TIM4
             PA3 is selected as IO output
         3. TIM:
             TIM4 configures the rising edge of CH2 to trigger CH1 to output a single pulse
     Instructions:
         1. After compiling, turn on the debug mode, connect PA3 to PB7, and use an oscilloscope or logic analyzer to observe the waveform of CH1 of TIM4
         2. The program sends the rising edge of PA3, and TIM4 CH1 outputs a single pulse
4. Matters needing attention
     without