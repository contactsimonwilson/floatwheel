1、功能说明
    LCD功能演示

2、使用环境
    软件开发环境：KEIL MDK-ARM V5.26
    硬件环境：基于全功能板N32L436MBL_EVB开发

3、使用说明
    
    系统配置；
        1、时钟源：HSE+PLL
        2、系统时钟：64MHz
        3、LCD端口： 
            SEG:
            PA1:SEG0    PA2:SEG1    PA3:SEG2    PA6:SEG3
            PA7:SEG4    PB0:SEG5    PB1:SEG6    PB10:SEG10
            PB11:SEG11  PB12:SEG12  PB14:SEG14  PC0: SEG18  
            PC1:SEG19   PC2:SEG20   PC3:SEG21   PC4: SEG22
            PC5:SEG23   PC13:SEG35  PC6: SEG24  PD1: SEG33  
            PD3:SEG34   PD8:SEG36   PD9: SEG37  PD10:SEG38
            PD11:SEG39
            
            COM:
            PD4:COM4    PD5:COM5    PD6:COM6    PD7:COM7（仅N32L436MBL_EVB_V1.0）
            PC10:COM4   PC11:COM5   PC12:COM6   PD2:COM7（其他版本）
        4、按键IO:
            PA5:KEY1    PD12:KEY2   PD13:KEY3

    使用方法：
        1、在KEIL下编译后烧录到开发板，通电
        2、LCD显示全部像素
        3、LCD逐个显示单个像素
        4、LCD显示ASCII字符串
        5、进入SLEEP模式，LCD显示保持
        6、按任意按键唤醒，退出SLEEP模式，随后进入LOW POWER SLEEP模式，LCD显示保持
        7、按任意按键唤醒，退出LOW POWER SLEEP模式，随后进入STOP2模式，LCD显示保持
        7、按任意按键唤醒，退出STOP2模式，回到第2步，循环演示
        
4、注意事项
    1、使用时必须注意以下跳线的连接：
        开发板N32L436MBL_EVB_V1.2：J26必须连接，J1、J19、J25、J88必须断开
        开发板N32L436MBL_EVB_V1.1：J1、J19、J22、J23、J24、J88必须断开
        开发板N32L436MBL_EVB_V1.0：J1、J13、J19、J22、J23、J24、J88必须断开

1. Function description
	LCD function demonstration
2. Use environment
	Software development environment: KEIL MDK-ARM V5.26
	Hardware environment: based on full function board N32L436MBL_EVB development

3. Instructions for use  
	System configuration;
	1. Clock source: HSE+PLL
	2. System clock: 64MHz
	3. LCD port:
	SEG:
	PA1: SEG0 PA2: SEG1 PA3: SEG2 PA6: SEG3
	PA7: SEG4 PB0: SEG5 PB1: SEG6 PB10: SEG10
	PB11:SEG11 PB12:SEG12 PB14:SEG14 PC0: SEG18
	PC1:SEG19 PC2:SEG20 PC3:SEG21 PC4: SEG22
	PC5:SEG23 PC13:SEG35 PC6: SEG24 PD1: SEG33
	PD3:SEG34 PD8:SEG36 PD9: SEG37 PD10:SEG38
	PD11: SEG39
            
	COM:
	PD4:COM4 PD5:COM5 PD6:COM6 PD7:COM7（only N32L436MBL_EVB_V1.0）
	PC10:COM4 PC11:COM5 PC12:COM6 PD2:COM7（other board version）
	4. Key IO:
	PA5: KEY1 PD12: KEY2 PD13: KEY3
	Usage:
	1. After compiling under KEIL, burn to the development board and power on
	2. LCD display all pixels
	3. LCD displays individual pixels one by one
	4. The LCD displays an ASCII character string
	5. Enter the SLEEP mode, LCD display hold
	6. Press any key to wake up and exit the SLEEP mode, then enter the LOW POWER SLEEP mode and keep the LCD display
	7. Press any key to wake up, exit the LOW POWER SLEEP mode, then enter the STOP2 mode, and keep the LCD display
	7, press any key to wake up, exit STOP2 mode, return to step 2, cycle demonstration
        
4. Matters needing attention
    1. You must pay attention to the connection of the following jumpers:
        Board N32L436MBL_EVB_V1.2：J26 must be connected，J1、J19、J25、J88 must be disconnected
        Board N32L436MBL_EVB_V1.1：J1,J19,J22,J23,J24,J88 must be disconnected
        Board N32L436MBL_EVB_V1.0：J1,J13,J19,J22,J23,J24,J88 must be disconnected