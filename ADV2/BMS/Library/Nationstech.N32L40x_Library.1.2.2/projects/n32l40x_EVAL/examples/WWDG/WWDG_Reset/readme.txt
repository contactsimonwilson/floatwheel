1、功能说明
    1、WWDG复位功能。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.25

    硬件环境：
        1、基于评估板N32L40XRL-STB V1.0开发
        2、MCU：N32L406RBL7


3、使用说明
    
    系统配置；
        1、WWDG时钟源：PCLK1
        2、窗口值：96.3ms < n <131.1ms
        3、指示灯：PA8(LED1)   PB4(LED2)
             



    使用方法：
        1、在KEIL下编译后烧录到评估板，上电后，指示灯LED2不停的闪烁。说明窗口值刷新正常，代码正常运行。
        2、当把Delay(110)函数参数改成132以上，整个系统将一直处于复位状态。LED1、LED2长亮。


4、注意事项
     无

1. Function description
    1. WWDG reset function.
	
2. Use environment
    Software development environment: KEIL MDK-ARM V5.25.
	
    Hardware environment: 
		1.Developed based on the evaluation board N32L40XRL-STB V1.0
		2.N32L406RBL7
	
3. Instructions for use
    System Configuration;
        1. WWDG clock source: PCLK1

		2. window value: 96.3ms < n <131.1ms

		3. Indicator light: PA8(LED1)   PB4(LED2)


    Instructions:
        1. After compiling under KEIL, it is burned to the evaluation board. After powering on, the indicator light LED2 keeps flashing. The window value is refreshed properly, and the code is running properly.
		2. When the parameter of Delay(110) function  is changed to more than 132, the whole system will always be reset. LED1,LED2 are always on.
		
4. Matters needing attention
    None.