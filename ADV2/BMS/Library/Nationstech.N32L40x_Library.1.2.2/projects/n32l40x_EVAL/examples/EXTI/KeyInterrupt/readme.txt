1������˵��

	1��������չʾͨ���ⲿ�����жϣ����� LED ��˸


2��ʹ�û���

	/* Ӳ�����������̶�Ӧ�Ŀ���Ӳ��ƽ̨ */
	�����壺N32L40XM-STB V1.1

3��ʹ��˵��
	
	/* �������ģ�����÷���������:ʱ�ӣ�I/O�� */
	1��SystemClock��64MHz
	2��GPIO��PA8 ѡ����Ϊ�ⲿ�ж���ڣ�PB4 ���� LED(D2) ������PB5 ���� LED(D3) ��˸


	/* ����Demo�Ĳ��Բ�������� */
	1.��������س���λ���У�
	2.LED��D2���������� PA8 ���� 3.3V �ٶϿ���LED��D3�� ��˸��


4��ע������
	��
	
	
	
1. Function description
    1. This example shows the control of LED flashing through an external trigger interrupt.
	
2. Use environment
    /*Hardware environment: Project corresponding development hardware platform*/
	1.Developed based on the evaluation board N32L40XM-STB V1.1
	
3. Instructions for use
    /* Describe the related module configuration method; For example: clock, I/O, etc. */
	1. SystemClock: 64 MHZ
	2. GPIO: PA8 is selected as the external interrupt entrance. PB4 controls LED(D2) to be on, and PB5 controls LED(D3) to blink.
	
	/* Describes the test steps and symptoms of Demo */
	1. The downloaded program is reset and running after compilation
	2. LED (D2) is steady on. Connect PA8 to 3.3V and then disconnect. LED (D3) blinks.
		
4. Matters needing attention
   None.