1、功能说明
    1、COMP1的输出PA11受输入INP PB10和INM PA5的影响
2、使用环境
    软件开发环境：  KEIL MDK-ARM V5.26.2.0
    硬件环境：      基于N32L40XML-STB V1.0开发
3、使用说明
    系统配置；
        1、时钟源：
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,COMP CLK=16M
        2、端口配置：
            PB10选择为模拟功能COMP INP
            PA5选择为模拟功能COMP INM
            PA11选择为模拟功能COMP OUT
            PD2选择为IO输出
            PD3选择为IO输出
        3、COMP：
            COMP1输入PB10，PA5，输出PA11
    使用方法：
        1、编译后打开调试模式，将PD2连接到PB10，PD3连接到PA5，利用示波器或者逻辑分析仪观察PA11输出波形
        2、当软件输出PD2电平大于PD3时，PA11输出高电平，相反时，输出低电平
4、注意事项
    无






1. Function description
     1. The output PA11 of COMP1 is affected by the input INP PB10 and INM PA5
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on the development board N32L40XML-STB V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,COMP CLK=16M
         2. Port configuration:
             PB10 is selected as analog function, COMP INP
             PA5 is selected as analog function, COMP INM
             PA11 is selected as analog function, COMP OUT
             PD2 is selected as IO output
             PD3 is selected as IO output
         3. COMP:
             COMP1 input PB10, PA5, output PA11
     Instructions:
         1. After compiling, open the debug mode, connect PD2 to PB10, connect PD3 to PA5, and use an oscilloscope or logic analyzer to observe the output waveform of PA11
         2. When the software output PD2 level is greater than PD3, PA11 outputs a high level, on the contrary, it outputs a low level
4. Matters needing attention
     without