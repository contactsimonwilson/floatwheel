1、功能说明
    1、TIM3 CH1 CH2 CH3 CH4 达到CC值后，输出ACTIVE电平
2、使用环境
    软件开发环境：  KEIL MDK-ARM V5.26.2.0
    硬件环境：      基于N32L40XM-STB_V1.0开发
3、使用说明
    系统配置；
        1、时钟源：
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM3 CLK=32M
        2、端口配置：
            PA6选择为TIM3 CH1输出
            PA7选择为TIM3 CH2输出
            PB0选择为TIM3 CH3输出
            PB1选择为TIM3 CH4输出
            PC6选择为IO 输出
        3、TIM：
            TIM3 CH2 上升沿捕获中断打开
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM2 CH1 CH2 CH3 CH4的波形
        2、定时器运行到CC1 CC2 CC3 CC4之后，对应通道的输出变为Active
4、注意事项
    无
    
1. Function description
     1. After TIM3 CH1 CH2 CH3 CH4 reaches the CC value, it outputs ACTIVE level
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM3 CLK=32M
         2. Port configuration:
             PA6 is selected as TIM3 CH1 output
             PA7 is selected as TIM3 CH2 output
             PB0 is selected as TIM3 CH3 output
             PB1 is selected as TIM3 CH4 output
             PC6 is selected as IO output
         3. TIM:
             TIM3 CH2 rising edge capture interrupt is turned on
     Instructions:
         1. After compiling, turn on the debug mode, use an oscilloscope or logic analyzer to observe the waveform of TIM2 CH1 CH2 CH3 CH4
         2. After the timer runs to CC1 CC2 CC3 CC4, the output of the corresponding channel becomes Active
4. Matters needing attention
     without