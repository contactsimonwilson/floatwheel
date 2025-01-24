1、功能说明
    1、STOP2模式的进入和退出。


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
	在KEIL下编译后烧录到评估板，接上电流表，上电后发现电流由mA降到了uA级别，
           按下唤醒按键(PA0),电流又回到了mA级别，过了一会又降到uA,并且LED翻转。


4、注意事项
    ①在评估功耗的时候，要注意去掉LED去测
    ②SRAM1和SRAM2可配置



1. Function description
    1. Enter and exit STOP2 mode.

2. Use environment
    Software development environment: KEIL MDK-ARM V5.25
    Hardware environment:
	1. Development based on evaluation board N32L40XRL-STB V1.0
	2. MCU: N32L406RBL7

3. Instructions for use    
    System configuration;
	1. Clock source: HSE+PLL
	2, clock frequency: 64MHz
	3. Wake up source: PA0
               
    Instructions:
	After compiling in KEIL, it was burned to the evaluation board, connected to the ammeter, and found that the current dropped from mA to uA level after powering on.
	Press the wake button (PA0), and the current returns to mA level. After a while, it drops to uA and LED1 reverses.

4. Matters needing attention
    ①When evaluating power consumption, we should pay attention to removing LED to measure
    ②SRAM1 and SRAM2 are configurable
