1������˵��
    1��BKP�Ĵ�����д

2��ʹ�û���

    �������������KEIL MDK-ARM V5.25
    Ӳ��������
        1������������N32L40XML-STB V1.0����
        2��MCU��N32L406MBL7


3��ʹ��˵��
    
    ϵͳ���ã�
        1��RTCʱ��Դ��LSE
        2���������ã�
                    - ����ΪUSART1��TX��PA9  RX��PA10��:
                    - ����λ��8
                    - ֹͣλ��1
                    - ��żУ�飺��
                    - �����ʣ� 115200 
    ʹ�÷�����
        �������¼�������壬��BKP�Ĵ�����д�����ݣ�Ȼ�������ӡд��BKP�Ĵ����е�����

4��ע������
    ��


1. Function description

	1. The BKP register reads and writes

2. Use environment

	Software development environment: KEIL MDK-ARM V5.25
	Hardware environment:
		1. based on the evaluation board N32L40XML-STB V1.0 development
		2. MCU��N32L406MBL7

3. Instructions for use

	System configuration:

		1. RTC clock source: LSE
		2. Serial port configuration:

							- Serial port: USART1 (TX: PA9 RX: PA10) :
							- Data bit: 8
							- Stop bit: 1
							- Parity check: None
							- Baud rate: 115200

	Instructions:
		1. After compiling, it burns to the evaluation board, writes data to the BKP register, and then reads and prints the data written to the BKP register

4. Matters needing attention
	None