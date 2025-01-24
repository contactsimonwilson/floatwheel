1������˵��

	/* ���������̹��� */
        ����������ò���ʾ���ò�ͬ��ϵͳʱ�ӣ�����MCO��PA8�������


2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
        �����壺N32L40XML-STBV1.0


3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
        SystemClock��64MHz

        USART��TX - PB4��������115200
	GPIO��PA8 - ����ΪMC0ʱ�����

	/* ����Demo�Ĳ��Բ�������� */
        1.��������س���λ���У�
        2.�ֱ�����ϵͳʱ��ΪHSI��HSE��PLL���ֱ�ʹ�ô��ڴ�ӡ����ǰSYSCLK��HCLK��PCLK1��PCLK2����Ϣ�����ҿ���ʹ��PA8�����������ʱ�ӣ���ʾ�����鿴��


4��ע������
   PLL���Ƶ�ʱ�����ڵ���32MHz


1. Function description

    /* Briefly describe the engineering function */
        This example configures and demonstrates setting different system clocks, and uses MCO to output from PA8


2. Use environment

    /* Hardware environment: the development hardware platform corresponding to the project */
        Development board: N32L40XML-STBV1.0
        

3. Instructions for use
    
    /* Describe the configuration method of related modules; for example: clock, I/O, etc. */   
    	SystemClock��64MHz
	
        USART: TX-PB4, baud rate 115200
        GPIO: PA8-multiplexed as MC0 clock output

    /* Describe the test steps and phenomena of Demo */
        1. After compiling, download the program to reset and run;
        2. Configure the system clock as HSI, HSE, and PLL, respectively, use the serial port to print out the current SYSCLK, HCLK, PCLK1, PCLK2 and other information, and use the PA8 multiplex pin to output the clock and view it with an oscilloscope;


4. Matters needing attention
   The PLL frequency must be greater than or equal to 32MHz