1������˵��

    �������ṩ��һ��DMA�÷������������赽RAM֮�䴫�����ݡ�

2��ʹ�û���

    �������������
        IDE���ߣ�KEIL MDK-ARM 5.26
    
    Ӳ��������
        ������ N32L43XML-STB V1.0


3��ʹ��˵��
	
    1��ʱ��Դ��HSE+PLL
    2����ʱ�ӣ�64MHz
    3��DMAͨ����DMA_CH2��DMA_CH3��DMA_CH4��DMA_CH5
    4��SPI1 ���ã�
            SCK   -->  PA5
            MISO  -->  PA6
            MOSI  -->  PA7
            ȫ˫��
            ��ģʽ
            8bit����
            ���ԣ���ʼΪ��/�ڶ�������
            ���Ƭѡ
            �����ǰMSB
    
    5��SPI2 ���ã�
            SCK   -->  PB13
            MISO  -->  PB14
            MOSI  -->  PB15
            ȫ˫��
            ��ģʽ
            8bit����
            ���ԣ���ʼΪ��/�ڶ�������
            ���Ƭѡ
            �����ǰMSB
    
    6��USART1���ã�
            TX  -->  PA9
            �����ʣ�115200
            ����λ��8bit
            ֹͣλ��1bit
            ��У��

    7�����Բ���������
	a���öŰ��߽�PA5/6/7���ӵ�PB13/14/15
        b���������ش��븴λ����
        c���Ӵ��ڿ���ӡ��Ϣ����֤���
        
4��ע������
    ��


1. Function description
    This routine provides a DMA usage for transferring data between peripherals and RAM.
    
2. Use environment
    Software Development environment:
	IDE tool: KEIL MDK-ARM 5.26   
    Hardware environment:
	Development Board N32L40XML-STB V1.0

3. Instructions for use
    1. Clock source: HSE+PLL
    2. Master clock: 64MHz
    3. DMA channels: DMA_CH2, DMA_CH3, DMA_CH4, DMA_CH5
    4. SPI1 configuration:
        SCK   -->  PA5
        MISO  -->  PA6
        MOSI  -->  PA7
	Full duplex
	Main mode
	8 bit transmission
	Polarity: start at low/second edge
	Piece of software to choose
	Big end in front MSB    
    5. SPI2 Configuration:
        SCK   -->  PB13
        MISO  -->  PB14
        MOSI  -->  PB15
	Full duplex
	From the pattern
	8 bit transmission
	Polarity: start at low/second edge
	Piece of software to choose
	Big end in front MSB    
    6. USART1 configuration:
	TX --> PA9
	Baud rate: 115200
	Data bit: 8 bits
	Stop bit: 1bit
	No check
    7. Test steps and phenomena
	A, Connect PA5/6/7 to PB13/14/15
	B, Compile download code reset run
	C, View the printed information from the serial port and verify the result
        
4. Matters needing attention
    None