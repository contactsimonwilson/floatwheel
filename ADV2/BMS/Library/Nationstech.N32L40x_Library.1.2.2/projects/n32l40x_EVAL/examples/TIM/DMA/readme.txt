1������˵��
    1��TIM1 CH3 CH3N�����ź�ÿ6�����ڸı�һ��ռ�ձ�
2��ʹ�û���
    �������������  KEIL MDK-ARM V5.26.2.0
    Ӳ��������      ����N32L40XM-STB_V1.0����
3��ʹ��˵��
    ϵͳ���ã�
        1��ʱ��Դ��
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM1 CLK=64M,DMA CLK=64M
        2���˿����ã�
            PA10ѡ��ΪTIM1 CH3���
            PB15ѡ��ΪTIM1 CH3N���
        3��TIM��
            TIM1 CH3 CH3N���������ÿ6�����ڴ���һ��DMA����
        4��DMA��
            DMA1_CH5ͨ��ѭ��ģʽ����3������SRC_Buffer[3]������TIM1 CC3�Ĵ���
    ʹ�÷�����
        1�������򿪵���ģʽ����ʾ���������߼������ǹ۲�TIM1 CH3 CH3N�Ĳ���
        2��TIM1��6�����ڸı�һ��CH3 CH3N��ռ�ձȣ�ѭ���ı�
4��ע������
    ��

1. Function description
     1. TIM1 CH3 CH3N complementary signal changes the duty cycle every 6 cycles
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM1 CLK=64M,DMA CLK=64M
         2. Port configuration:
             PA10 is selected as TIM1 CH3 output
             PB15 is selected as TIM1 CH3N output
         3. TIM:
             TIM1 CH3 CH3N complementary output, trigger a DMA transfer every 6 cycles
         4. DMA:
             DMA1_CH5 channel circular mode transfers 3 half-word SRC_Buffer[3] variables to the TIM1 CC3 register
     Instructions:
         1. After compiling, turn on the debug mode, use an oscilloscope or logic analyzer to observe the waveform of TIM1 CH3 CH3N
         2. Change the duty cycle of CH3 and CH3N once in 6 cycles of TIM1, and change cyclically
4. Matters needing attention
     without