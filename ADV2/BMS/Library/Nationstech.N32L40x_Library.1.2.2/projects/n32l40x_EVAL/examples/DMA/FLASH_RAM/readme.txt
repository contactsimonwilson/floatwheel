1������˵��

    �������ṩ��һ��DMA MemtoMemģʽ�÷���������FLASH��RAM֮�䴫�����ݡ�  

2��ʹ�û���

    �������������
        IDE���ߣ�KEIL MDK-ARM 5.26
    
    Ӳ��������
        ������ N32L40XML-STB V1.0


3��ʹ��˵��
	
    1��ʱ��Դ��HSE+PLL
    2����ʱ�ӣ�64MHz
    3��DMAͨ����DMA_CH1
    
    4��USART1���ã�
            TX  -->  PA9
            �����ʣ�115200
            ����λ��8bit
            ֹͣλ��1bit
            ��У��

    5�����Բ���������
        a���������ش��븴λ����
        b���Ӵ��ڿ���ӡ��Ϣ����֤���

4��ע������
    ��


1. Function description
    This routine provides a DMA MemtoMem mode usage for transferring data between FLASH and RAM.

2. Use environment
    Software Development environment:
	IDE tool: KEIL MDK-ARM 5.26
    
    Hardware environment:
	Development Board N32L40XML-STB V1.0

3. Instructions for use
    1. Clock source: HSE+PLL
    2. Master clock: 64MHz
    3. DMA channel: DMA_CH1    
    4. USART1 configuration:
	TX --> PA9
	Baud rate: 115200
	Data bit: 8 bits
	Stop bit: 1bit
	No check
    5. Test steps and phenomena
	A. Compile download code reset run
	B. View the printed information from the serial port and verify the result

4. Matters needing attention
    None