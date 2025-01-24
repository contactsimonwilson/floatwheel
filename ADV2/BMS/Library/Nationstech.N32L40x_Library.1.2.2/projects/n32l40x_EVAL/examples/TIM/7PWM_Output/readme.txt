1、功能说明
    1、TIM1和TIM8输出3路互补波形和一路CH4波形
2、使用环境
    软件开发环境：  KEIL MDK-ARM V5.26.2.0
    硬件环境：      基于N32L40XM-STB_V1.0开发
3、使用说明
    系统配置；
        1、时钟源：
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM1 CLK=64M
        2、端口配置：
            PA8选择为TIM1 CH1输出
            PA9选择为TIM1 CH2输出
            PA10选择为TIM1 CH3输出
            PB13选择为TIM1 CH1N输出
            PB14选择为TIM1 CH2N输出
            PB15选择为TIM1 CH3N输出
            PA11选择为TIM1 CH4输出
            PC6选择为TIM8 CH1输出
            PC7选择为TIM8 CH2输出
            PC8选择为TIM8 CH3输出
            PA7选择为TIM8 CH1N输出
            PB0选择为TIM8 CH2N输出
            PB1选择为TIM8 CH3N输出
            PC9选择为TIM8 CH4输出
        3、TIM：
            TIM1 6路互补输出,CH4输出
            TIM8 6路互补输出,CH4输出
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM1 TIM8的输出波形
        2、输出波形TIM1 3路互补加一路CH4，TIM8 3路互补加一路CH4
4、注意事项
    无

1. Function description
    1. TIM1 and TIM8 output 3 complementary waveforms and one CH4 waveform
2. Use environment
    Software development environment: KEIL MDK-ARM V5.26.2.0
    Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
    System Configuration;
        1. Clock source:
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM1 CLK=64M
        2. Port configuration:
            PA8 is selected as TIM1 CH1 output
            PA9 is selected as TIM1 CH2 output
            PA10 is selected as TIM1 CH3 output
            PB13 is selected as TIM1 CH1N output
            PB14 is selected as TIM1 CH2N output
            PB15 is selected as TIM1 CH3N output
            PA11 is selected as TIM1 CH4 output
            PC6 is selected as TIM8 CH1 output
            PC7 is selected as TIM8 CH2 output
            PC8 is selected as TIM8 CH3 output
            PA7 is selected as TIM8 CH1N output
            PB0 is selected as TIM8 CH2N output
            PB1 is selected as TIM8 CH3N output
            PC9 is selected as TIM8 CH4 output
        3. TIM:
            TIM1 6 complementary outputs, CH4 output
            TIM8 6 complementary outputs, CH4 output
    Instructions:
        1. After compiling, turn on the debug mode, use an oscilloscope or logic analyzer to observe the output waveform of TIM1 TIM8
        2. Output waveform TIM1 3 complementary plus one CH4, TIM8 3 complementary plus one CH4
4. Matters needing attention
    without