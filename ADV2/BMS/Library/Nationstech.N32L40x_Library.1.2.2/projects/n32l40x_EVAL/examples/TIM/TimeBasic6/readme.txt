1、功能说明
    1、TIM6 利用更新中断，产生定时翻转IO
2、使用环境
    软件开发环境：  KEIL MDK-ARM V5.26.2.0
    硬件环境：      基于N32L40XM-STB_V1.0开发
3、使用说明
    系统配置；
        1、时钟源：
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM6 CLK=32M
        2、中断：
            TIM6 更新中断打开，抢断优先级0，子优先级1
        3、端口配置：
            PC6选择为IO输出
            PC7选择为IO输出
            PC8选择为IO输出
            PC9选择为IO输出
        4、TIM：
            TIM6使能周期中断
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察PC6的波形
        2、程序运行后，TIM6的周期中断来临翻转PC6电平
4、注意事项
    无

1. Function description
     1. TIM6 uses the update interrupt to generate timing rollover IO
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM6 CLK=32M
         2. Interruption:
             TIM6 update interrupt is turned on, steal priority level 0, sub priority level 1
         3. Port configuration:
             PC6 is selected as IO output
             PC7 is selected as IO output
             PC8 is selected as IO output
             PC9 is selected as IO output
         4. TIM:
             TIM6 enables periodic interrupts
     Instructions:
         1. After compiling, turn on the debug mode, and use the oscilloscope or logic analyzer to observe the PC6 waveform
         2. After the program runs, the periodic interrupt of TIM6 comes to flip the PC6 level
4. Matters needing attention
     without