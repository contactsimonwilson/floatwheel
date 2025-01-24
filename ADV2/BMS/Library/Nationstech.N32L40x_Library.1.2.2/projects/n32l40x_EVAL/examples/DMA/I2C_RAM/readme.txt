1������˵��

    �������ṩ��һ��DMA�÷���������������RAM֮�䴫�����ݡ�

2��ʹ�û���

    �������������
        IDE���ߣ�KEIL MDK-ARM 5.26
    
    Ӳ��������
        ������ N32L40XML-STB V1.0

3��ʹ��˵��
	
    1��ʱ��Դ��HSE+PLL
    2����ʱ�ӣ�64MHz
    3��DMAͨ����DMA_CH5��DMA_CH6
    4��I2C1 ���ã�
            SCL   -->  PB8
            SDA   -->  PB9
            ADDR��0x30(7bit)
            CLOCK��100K
    
    5��I2C2 ���ã�
            SCL   -->  PB10
            SDA   -->  PB11
            ADDR��0xA0(7bit)
            CLOCK��100K
    
    6��USART1���ã�
            TX  -->  PA9
            �����ʣ�115200
            ����λ��8bit
            ֹͣλ��1bit
            ��У��
            
    7�����Բ���������
	a������PB8��PB10������PB9��PB11
        b���������ش��븴λ����
        c���Ӵ��ڿ���ӡ��Ϣ����֤���

4��ע������
    ��SDA��SCL����Ҫ����������


1. Function description
    This routine provides a DMA usage for transferring data between peripherals and RAM.

2. Use environment
    Software Development environment:
	IDE tool: KEIL MDK-ARM 5.26   
    Hardware environment:
	Development Board N32L40XML-STB V1.0
3. Instructions for use
    1. Clock source: HSE+PLL
    2. Master clock: 108MHz
    3. DMA channels: DMA_CH5, DMA_CH6
    4. I2C1 configuration:
        SCL   -->  PB8
        SDA   -->  PB9
        ADDR��0x30(7bit)
        CLOCK��100K   
    5. I2C2 configuration:
        SCL   -->  PB10
        SDA   -->  PB11
        ADDR��0xA0(7bit)
        CLOCK��100K    
    6. USART1 configuration:
	TX --> PA9
	Baud rate: 115200
	Data bit: 8 bits
	Stop bit: 1bit
	No check            
    7. Test steps and phenomena
	A, Connect PB8 to PB10, connect PB9 to PB11
	B, Compile download code reset run
	C, View the printed information from the serial port and verify the result

4. Matters needing attention
    Pull resistors are required on SDA and SCL