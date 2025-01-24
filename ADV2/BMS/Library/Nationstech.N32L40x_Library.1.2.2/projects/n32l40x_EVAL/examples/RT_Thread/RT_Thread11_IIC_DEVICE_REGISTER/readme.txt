1������˵��

	1��������չʾ�� RT_Thread ϵͳ���� I2C �豸��д����EEPROM

2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
	�����壺N32L43XM-STB N32L40XM-STB V1.1

3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
	SystemClock��64MHz
	GPIO:	LED:D1--PA8��D2--PB4��D3--PB5
                KEY:	KEY1--PA4��KEY2--PA5
                I2C1:	I2C_SCL--PB8��I2C_SDA--PB9
	���ڣ�      TX--PA9

	/* ����Demo�Ĳ��Բ�������� */
	1.��������س���λ����
               2.��������main()���洴�������̣߳�test0 �̺߳� test1 �̣߳�test0 �߳����ڿ��� D1 250ms��˸��
                 ��test1�̲߳���I2C�豸��д����EEPROM�����Խ��ͨ�����ڴ�ӡ�����

4��ע������
	��

1. Function description
    This routine shows how to create an I2C device to read and write operation EEPROM on RT_Thread system

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock��64MHz
	2. GPIO:	LED:D1--PA8��D2--PB4��D3--PB5
        3. KEY:		KEY1--PA4��KEY2--PA5
        4. I2C1:	I2C_SCL--PB8��I2C_SDA--PB9
        Log: TX--PA9 RX--PA10 Baud rate: 115200

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. This routine creates two threads in main(), test0 thread and test1 thread, test0 thread is used to control D1 250ms flashing, 
            test1 thread is used to test I2C device read and write operation EEPROM, test results are printed out through the serial port

4. Matters needing attention
    None