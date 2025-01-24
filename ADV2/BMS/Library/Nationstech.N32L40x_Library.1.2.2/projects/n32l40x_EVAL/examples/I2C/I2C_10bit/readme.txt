1、功能说明

    此例程展示了I2C模块10bit地址模式的读写操作。   

2、使用环境

	软件开发环境：
        IDE工具：KEIL MDK-ARM 5.26
    
    硬件环境：
        开发板 N32L40XML-STB V1.0


3、使用说明
	
    1、时钟源：HSE+PLL
    2、主时钟：64MHz
    3、I2C1主配置：
            SCL   -->  PB8
            SDA   -->  PB9
            ADDR：0x230(10bit)
            CLOCK:100KHz

    4、I2C2从配置：
            SCL   -->  PB10
            SDA   -->  PB11
            ADDR：0x2A0(10bit)
            CLOCK:100KHz            

    5、USART1配置：
            TX  -->  PA9
            波特率：115200
            数据位：8bit
            停止位：1bit
            无校验

    6、测试步骤与现象
        a，用杜邦线连接PB8-PB10和PB9-PB11
        b，编译下载代码复位运行
        c，从串口看打印信息，验证结果

4、注意事项
    需要在SDA和SCL上外接上拉电阻。
    
1. Function description

    This example shows the read and write operations in the 10-bit address mode of the I2C module.

2. Use environment

    Software development environment:
        IDE tool: KEIL MDK-ARM 5.26
    
    Hardware environment:
        Development board N32L40XML-STB V1.0


3. Instructions for use
    
    1. Clock source: HSE+PLL
    2. Main clock: 64MHz
    3. I2C1 master configuration:
            SCL --> PB8 
            SDA --> PB9 
            ADDR: 0x230(10bit)
            CLOCK: 100KHz

    4. I2C2 slave configuration:
            SCL --> PB10 
            SDA --> PB11 
            ADDR: 0x2A0(10bit)
            CLOCK: 100KHz

    5. USART1 configuration:
            TX --> PA9 
            Baud rate: 115200
            Data bit: 8bit
            Stop bit: 1bit
            No verification

    6. Test steps and phenomena
        a. Connect PB8-PB10 and PB9-PB11 with DuPont cable
        b, compile and download the code, reset and run
        c, view the print information from the serial port and verify the result

4. Matters needing attention
    Ensure that SCL\SDA has an external pull-up