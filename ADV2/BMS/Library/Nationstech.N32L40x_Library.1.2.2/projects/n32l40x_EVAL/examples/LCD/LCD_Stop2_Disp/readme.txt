1、功能说明
    LCD在STOP2模式下正常显示，同时RTC 1s定时唤醒MCU并刷新LCD显示内容
    例程中开启了LCD UDD中断，在写LCD数据寄存器后不用等待LCD刷新完成，直接进入STOP2,可降低MCU功耗

2、使用环境
    软件开发环境：KEIL MDK-ARM V5.34
    硬件环境：基于全功能板N32L436MBL_EVB开发

3、使用说明
    
    系统配置；
        1、时钟源：HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M
        2、LCD端口： 
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
        3、按键IO:
            PD13:KEY3
        4、LED IO:
            PC10:COM4   PC11:COM5   PC12:COM6（仅N32L436MBL_EVB_V1.0）
            PD4:COM4    PD5:COM5    PD6:COM6（其他版本）

    使用方法：
        1、编译后下载到开发板，复位MCU或重新上电
        2、LCD显示“123456” ，D16点亮
        3、保持显示约8秒后，LCD显示开始逐秒刷新，D16闪烁
        
4、注意事项
    1、使用时必须注意以下跳线的连接：
        开发板N32L436MBL_EVB_V1.2：J26必须连接，J1、J19、J25、J88必须断开
        开发板N32L436MBL_EVB_V1.1：J1、J19、J22、J23、J24、J88必须断开
        开发板N32L436MBL_EVB_V1.0：J1、J13、J19、J22、J23、J24、J88必须断开
    1、如果要测试功耗数据，请在main.h中注释掉宏定义USE_STATUS_LED并重新编译下载，
        此时D16不会点亮
    2、如果要对比不使用UDD中断时的功耗，必须先按住KEY3，再复位MCU或重新上电，然
        后再松开按键，MCU继续运行。此时LCD UDD中断不开启
    
1. Function description
    The LCD displays normally in STOP2 mode,at the same time,the RTC wakeup the 
    MCU each second and refresh the LCD display content.
    The LCD UDD interrupt is enabled in the example.So it does not need to wait 
    until the LCD refresh completed after writing the LCD data registers,which 
    can reduce the power consumption.
2. Use environment
    Software development environment: KEIL MDK-ARM V5.34
    Hardware environment: Developed based on the evaluation board N32L436MBL_EVB
3. Instructions for use
    System configuration：
        1. Clock source:
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M
        2. Port Configuration:
            SEG:
            PA1:SEG0    PA2:SEG1    PA3:SEG2    PA6:SEG3
            PA7:SEG4    PB0:SEG5    PB1:SEG6    PB10:SEG10
            PB11:SEG11  PB12:SEG12  PB14:SEG14  PC0: SEG18  
            PC1:SEG19   PC2:SEG20   PC3:SEG21   PC4: SEG22
            PC5:SEG23   PC13:SEG35  PC6: SEG24  PD1: SEG33  
            PD3:SEG34   PD8:SEG36   PD9: SEG37  PD10:SEG38
            PD11:SEG39
            
            COM:
            PD4:COM4    PD5:COM5    PD6:COM6    PD7:COM7（only N32L436MBL_EVB_V1.0）
            PC10:COM4   PC11:COM5   PC12:COM6   PD2:COM7（other board version）
        3. KEY port configuration:
            PD13:KEY3
        4. LED port configuration:
            PC10:COM4   PC11:COM5   PC12:COM6（only N32L436MBL_EVB_V1.0）
            PD4:COM4    PD5:COM5    PD6:COM6（other board version）
    Usage:
       1. After compiling and download the program to the board, reset the MCU 
          or power on again.
       2. The LCD will display "123456",and LED D16 is on.
       3. The LCD will keep the display for about 8 seconds.After that, the LCD 
          display refresh each second,and D16 flash. 
4. Precautions
    1. You must pay attention to the connection of the following jumpers:
        Board N32L436MBL_EVB_V1.2：J26 must be connected，J1、J19、J25、J88 must be disconnected
        Board N32L436MBL_EVB_V1.1：J1,J19,J22,J23,J24,J88 must be disconnected
        Board N32L436MBL_EVB_V1.0：J1,J13,J19,J22,J23,J24,J88 must be disconnected
    2. If you want to test the power consumption data,please comment the macro 
        "USE_STATUS_LED" defined in main.h,then recompile and download again.
        The LED D16 is not used now.
    3. If you want to compare the power consumption with UDD interrupt is not 
        used,you must press and hold KEY3 first,and then reset MCU or power on 
        again.After that,release KEY3 and MCU continues running. The LCD UDD interrupt
        is not used now.