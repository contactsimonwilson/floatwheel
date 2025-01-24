1、功能说明
    1、SLEEP模式的进入和退出。


2、使用环境

    软件开发环境：KEIL MDK-ARM V5.25

    硬件环境：
        1、基于评估板N32L40XRL-STB V1.0开发
        2、MCU：N32L406RBL7


3、使用说明
    
    系统配置；
        1、时钟源：HSE+PLL
        2、时钟频率：64MHz
        3、唤醒源：PA0




    使用方法：
        在KEIL下编译后烧录到评估板，串接电流表后，上电后过以一会，电流明显变小。按下唤醒按键PA0，LED反转一次
        电流又明显变大。过一会又变小。


4、注意事项
    无



1. Function description
    1. Enter and exit the SLEEP mode.

2. Use environment
    Software development environment: KEIL MDK-ARM V5.25
    Hardware environment:
	1, Based on the evaluation board N32L40XRL-STB V1.0 development
	2, MCU: N32L406RBL7

3. Instructions for use    
    System configuration;
	1. Clock source: HSE+PLL
	2. Clock frequency: 108MHz
	3. Wake up source: PA0

    Instructions:
	After compiling under KEIL, it was burned to the evaluation board, connected to the ammeter in series, and after powering on for a while, the current decreased significantly. Press the wake up button PA0,LED reversal once,
	The current increases significantly, and then decreases again.

4. Matters needing attention
    None
