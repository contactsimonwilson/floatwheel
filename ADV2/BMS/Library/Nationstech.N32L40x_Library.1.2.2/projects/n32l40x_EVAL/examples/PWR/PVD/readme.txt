1、功能说明
    1、PVD配置电压产生对应的中断。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.25

    硬件环境：
        1、基于评估板N32L40XRL-STB V1.0开发
        2、MCU：N32L406RBL7


3、使用说明
    
    系统配置；
        1、时钟源：HSE+PLL

    使用方法：
        在KEIL下编译后烧录到评估板，通过仿真器进入调试模式，在PVD_IRQHandler()中设置断点。
                全速运行。然后再把电压调到PVD设置电压附近，此时程序会停在断点处。


4、注意事项
    无



1. Function description
	1, PVD configuration voltage produces the corresponding interrupt.

2. Use environment
    Software development environment: KEIL MDK-ARM V5.25
    Hardware environment:
	1. Development based on evaluation board N32L40XRL-STB V1.0
	2. MCU: N32L406RBL7

3. Instructions for use    
    System configuration;
	1. Clock source: HSE+PLL
    Instructions:
	After compiling under KEIL, burn to the evaluation board, go into debug mode through the emulator, and set breakpoint in PVD_IRQHandler().
	Run at full speed. Then turn the voltage close to the PVD setting voltage, and the program will stop at the breakpoint.

4. Matters needing attention
    None
