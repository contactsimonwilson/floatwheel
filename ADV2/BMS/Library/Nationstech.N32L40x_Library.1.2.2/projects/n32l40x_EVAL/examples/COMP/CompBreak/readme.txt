1、功能说明
    1、COMP1的输出刹车TIM1 TIM8的互补信号，COMP OUT变低后恢复TIM1 TIM8波形
2、使用环境
    软件开发环境：  KEIL MDK-ARM V5.26.2.0
    硬件环境：      基于N32L40XML-STB V1.0开发
3、使用说明
    系统配置；
        1、时钟源：
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,COMP CLK=16M,TIM1 CLK=64M,TIM8 CLK=64M
        2、端口配置：
            PB10选择为模拟功能COMP INP
            PA5选择为模拟功能COMP INM
            PA0选择为模拟功能COMP OUT
            PD2选择为IO输出
            PD3选择为IO输出
            PA8选择为TIM1 CH1输出
            PA9选择为TIM1 CH2输出
            PA10选择为TIM1 CH3输出
            PB13选择为TIM1 CH1N输出
            PB14选择为TIM1 CH2N输出
            PB15选择为TIM1 CH3N输出
            PA11选择为TIM1 CH4输出
            PB12选择为TIM1 breakin输入
            PC6选择为TIM8 CH1输出
            PC7选择为TIM8 CH2输出
            PC8选择为TIM8 CH3输出
            PA7选择为TIM8 CH1N输出
            PB0选择为TIM8 CH2N输出
            PB1选择为TIM8 CH3N输出
        3、TIM：
            TIM1开启CH1 CH2 CH3 CH1N CH2N CH3N输出,COMP作为刹车输入
            TIM8开启CH1 CH2 CH3 CH1N CH2N CH3N输出,COMP作为刹车输入
        4、COMP：
            COMP1输出触发TIM1 TIM8刹车，无输出时恢复TIM1 TIM8输出
    使用方法：
        1、编译后打开调试模式，将PD2连接到PB10，PD3连接到PA5，利用示波器或者逻辑分析仪观察TIM1 TIM8输出波形
        2、当软件输出PD2电平大于PD3时，TIM波形消失，相反时，波形正常输出
4、注意事项
    无



1. Function description
    1. The output of COMP1 brakes the complementary signal of TIM1 and TIM8. After COMP OUT becomes low, the waveform of TIM1 and TIM8 is restored.
2. Use environment
    Software development environment: KEIL MDK-ARM V5.26.2.0
    Hardware environment: Developed based on the evaluation board N32L40XML-STB V1.0
3. Instructions for use
    System Configuration;
        1. Clock source:
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,COMP CLK=16M,TIM1 CLK=64M,TIM8 CLK=64M
        2. Port configuration:
            PB10 is selected as analog function, COMP INP
            PA5 is selected as analog function, COMP INM
            PA0 is selected as analog function, COMP OUT
            PD2 is selected as IO output
            PD3 is selected as IO output
            PA8 is selected as TIM1 CH1 output
            PA9 is selected as TIM1 CH2 output
            PA10 is selected as TIM1 CH3 output
            PB13 is selected as TIM1 CH1N output
            PB14 is selected as TIM1 CH2N output
            PB15 is selected as TIM1 CH3N output
            PA11 is selected as TIM1 CH4 output
            PB12 is selected as TIM1 breakin input
            PC6 is selected as TIM8 CH1 output
            PC7 is selected as TIM8 CH2 output
            PC8 is selected as TIM8 CH3 output
            PA7 is selected as TIM8 CH1N output
            PB0 is selected as TIM8 CH2N output
            PB1 is selected as TIM8 CH3N output
        3. TIM:
            TIM1 turns on CH1 CH2 CH3 CH1N CH2N CH3N output, COMP is used as brake input
            TIM8 turns on CH1 CH2 CH3 CH1N CH2N CH3N output, COMP is used as brake input
        4. COMP:
            The output of COMP1 triggers the brake of TIM1 and TIM8, and the output of TIM1 and TIM8 is restored when there is no output.
    Instructions:
        1. Open the debug mode after compiling, connect PD2 to PB10, connect PD3 to PA5, and use an oscilloscope or logic analyzer to observe the output waveforms of TIM1 and TIM8
        2. When the software output PD2 level is greater than PD3, the TIM waveform disappears, on the contrary, the waveform is output normally
4. Matters needing attention
    without