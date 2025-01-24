1、功能说明
    1、LP RUN模式的进入和退出。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.25

    硬件环境：
        1、基于评估板N32L40XRL-STB V1.0开发
        2、MCU：N32L406RBL7


3、使用说明
    
    系统配置；
        1、时钟源：HSE+PLL/MSI
        2、时钟频率：48M/4M

    使用方法：
        在KEIL下编译后烧录到评估板，串接电流表，上电后过一会，电流明显变小。又过一会电流又变大 LED1闪烁。
              循环往复。
            


4、注意事项
    当进入LP RUN模式时，系统时钟切换到了MSI，当退出时，需要切回用户默认系统时钟


1. Function description
    1. Enter and exit LP RUN mode.

2. Use environment
    Software development environment: KEIL MDK-ARM V5.25
    Hardware environment:
	1, based on the evaluation board N32L40XRL-STB V1.0 development
	2, MCU: N32L406RBL7

3. Instructions for use    
    System configuration;
	1. Clock source: HSE+PLL/MSI
	2, clock frequency: 48M/4M
    Instructions:
	After compiling under KEIL, it was burned to the evaluation board and connected to the ammeter in series. After powering on for a while, the current decreased significantly. After a while the current increases again,LED1 flashing.
	The cycle repeats.
            
4. Matters needing attention
    When you enter LP RUN mode, the system clock is switched to MSI. When you exit, you need to switch back to the default system clock

