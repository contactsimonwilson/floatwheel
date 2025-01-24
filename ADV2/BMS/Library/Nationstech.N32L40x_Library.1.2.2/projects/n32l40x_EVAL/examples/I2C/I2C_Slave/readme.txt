1、功能说明

    此例程展示了通过I2C模块作为从设备与外部I2C主设备通信。   

2、使用环境

	软件开发环境：
        IDE工具：KEIL MDK-ARM 5.26
    
    硬件环境：
        开发板 N32L40XML-STB V1.0


3、使用说明
	
    1、时钟源：HSE+PLL
    2、主时钟：64MHz
    3、I2C1从配置：
            SCL   -->  PB8		AF_OD
            SDA   -->  PB9		AF_OD
            ADDR：0xA0(7bit)
            CLOCK:100KHz
            
    4、USART1配置：
            TX  -->  PA9
            波特率：115200
            数据位：8bit
            停止位：1bit
            无校验

    5、测试步骤与现象
        a，用两块NS3602开发板，一块做主设备，另一块做从设备
        b，主设备烧录I2C_Master程序，从设备烧录I2C_Slave程序
        c，将两块板子的PB8/PB9对应连接起来
        d，分别编译下载代码，先复位从设备，再复位主设备
        e，从两个板子的串口看打印信息，验证结果

4、注意事项
    a，需要在SDA和SCL上外接上拉电阻。
    b，必须共地！

1. Function description

    This example demonstrates the use of I2C module as a slave device to communicate with an external I2C master device.

2. Use environment

Software development environment:
        IDE tool: KEIL MDK-ARM 5.26
    
    Hardware environment:
        Development board N32L40XML-STB V1.0


3. Instructions for use

    1. Clock source: HSE+PLL
    2. Main clock: 64MHz
    3. I2C1 slave configuration:
            SCL --> PB8 AF_OD
            SDA --> PB9 AF_OD

            ADDR: 0xA0(7bit)
            CLOCK: 100KHz
            
    4. USART1 configuration:
            TX --> PA9
            Baud rate: 115200
            Data bit: 8bit
            Stop bit: 1bit
            No verification

    5. Test steps and phenomena
        a. Use two NS3602 development boards, one as the master device and the other as the slave device
        b, the master device burns the I2C_Master program, and the slave device burns the I2C_Slave program
        c. Connect the PB8/PB9 of the two boards correspondingly
        d. Compile the downloaded code separately, reset the slave device first, and then reset the master device
        e, view the printed information from the serial ports of the two boards, and verify the result

4. Matters needing attention
    a. It is necessary to connect an external pull-up resistor to SDA and SCL.
    b, must share the ground!