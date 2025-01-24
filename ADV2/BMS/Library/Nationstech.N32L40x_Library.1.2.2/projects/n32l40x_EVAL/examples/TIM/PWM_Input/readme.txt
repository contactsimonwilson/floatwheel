1������˵��
    1��TIM3 CH2��������ͨ��CH1�½��غ�CH2�����ؼ���ռ�ձȺ�Ƶ��
2��ʹ�û���
    �������������  KEIL MDK-ARM V5.26.2.0
    Ӳ��������      ����N32L40XM-STB_V1.0����
3��ʹ��˵��
    ϵͳ���ã�
        1��ʱ��Դ��
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM3 CLK=32M
        2���жϣ�
            TIM3 CC2�Ƚ��жϴ򿪣��������ȼ�0�������ȼ�0
        3���˿����ã�
            PA7ѡ��ΪTIM3��CH2����
            PA3ѡ��ΪIO���
        4��TIM��
            TIM3 CH1�½��ز���CH2�źţ�CH2�����ز���CH2�ź�
    ʹ�÷�����
        1�������򿪵���ģʽ������PA3��PA7����Frequency��DutyCycle��ӵ�watch����
        2���������к�PA3���͵��������ݿ��Ա�����ռ�ձȺ�Ƶ�ʵ�����
4��ע������
    ��

1. Function description
     1. TIM3 CH2 capture pin calculates the duty cycle and frequency through the falling edge of CH1 and the rising edge of CH2
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM3 CLK=32M
         2. Interruption:
             TIM3 CC2 compare interrupt is turned on, preemption priority 0, subpriority 0
         3. Port configuration:
             PA7 is selected as the CH2 input of TIM3
             PA3 is selected as IO output
         4. TIM:
             TIM3 CH1 falling edge captures CH2 signal, CH2 rising edge captures CH2 signal
     Instructions:
         1. After compiling, open the debug mode, connect PA3 and PA7, and add Frequency and DutyCycle to the watch window
         2. After the program runs, the pulse data sent by PA3 can be captured to the duty cycle and frequency to the variable
4. Matters needing attention
     without