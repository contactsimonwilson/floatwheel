1、功能说明
    1、systick 100ms触发TIM1输出6步换相波形
2、使用环境
    软件开发环境：  KEIL MDK-ARM V5.26.2.0
    硬件环境：      基于N32L40XM-STB_V1.0开发
3、使用说明
    系统配置；
        1、时钟源：
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM1 CLK=64M
        2、中断：
            TIM1 COM事件中断打开，抢断优先级0，子优先级1
            Systick 100ms中断，优先级0
        3、端口配置：
            PA8选择为TIM1 CH1输出
            PA9选择为TIM1 CH2输出
            PA10选择为TIM1 CH3输出
            PB13选择为TIM1 CH1N输出
            PB14选择为TIM1 CH2N输出
            PB15选择为TIM1 CH3N输出
            PB12选择为TIM1 Breakin输入
        4、TIM：
            TIM1 6路互补冻结输出模式，无刹车，开COM中断
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM1的输出波形
        2、每隔100ms systick触发COM中断，在TIM的COM中断里面输出AB AC BC BA CA CB的6步换相波形
4、注意事项
    无

1. Function description
    1. Systick 100ms triggers TIM1 to output 6-step commutation waveform
2. Use environment
    Software development environment: KEIL MDK-ARM V5.26.2.0
    Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
    System Configuration;
        1. Clock source:
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM1 CLK=64M
        2. Interruption:
            TIM1 COM event interrupt is turned on, steal priority level 0, sub-priority level 1
            Systick 100ms interrupt, priority 0
        3. Port configuration:
            PA8 is selected as TIM1 CH1 output
            PA9 is selected as TIM1 CH2 output
            PA10 is selected as TIM1 CH3 output
            PB13 is selected as TIM1 CH1N output
            PB14 is selected as TIM1 CH2N output
            PB15 is selected as TIM1 CH3N output
            PB12 is selected as TIM1 Breakin input
        4. TIM:
            TIM1 6-way complementary freeze output mode, no brake, COM interrupt
    Instructions:
        1. After compiling, turn on the debug mode, and use an oscilloscope or logic analyzer to observe the output waveform of TIM1
        2. The COM interrupt is triggered by the systick every 100ms, and the 6-step commutation waveform of AB AC BC BA CA CB is output in the TIM COM interrupt
4. Matters needing attention
    without

    