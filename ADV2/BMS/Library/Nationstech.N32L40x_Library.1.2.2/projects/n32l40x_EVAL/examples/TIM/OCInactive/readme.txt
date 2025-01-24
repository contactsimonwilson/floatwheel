1、功能说明
    1、TIM2 CH1 CH2 CH3 CH4 达到CC值后，对应拉低PC6 PC7 PC8 PC9的IO电平
2、使用环境
    软件开发环境：  KEIL MDK-ARM V5.26.2.0
    硬件环境：      基于N32L40XM-STB_V1.0开发
3、使用说明
    系统配置；
        1、时钟源：
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM2 CLK=32M
        2、中断：
            TIM2 比较中断打开，抢断优先级0，子优先级1
        3、端口配置：
            PC6选择为IO 输出
            PC7选择为IO 输出
            PC8选择为IO 输出
            PC9选择为IO 输出
        4、TIM：
            TIM2 配置好CH1 CH2 CH3 CH4的比较值，并打开比较中断
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察PC6 PC7 PC8 PC9的波形
        2、定时器运进入CC1 CC2 CC3 CC4中断后,对应拉低PC6 PC7 PC8 PC9的IO
4、注意事项
    无

1. Function description
     1. After TIM2 CH1 CH2 CH3 CH4 reaches the CC value, correspondingly pull down the IO level of PC6, PC7, PC8, PC9
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM2 CLK=32M
         2. Interruption:
             TIM2 compare interrupt is turned on, preemption priority is 0, subpriority 1
         3. Port configuration:
             PC6 is selected as IO output
             PC7 is selected as IO output
             PC8 is selected as IO output
             PC9 is selected as IO output
         4. TIM:
             TIM2 configures the compare value of CH1, CH2, CH3, CH4, and turns on the compare interrupt
     Instructions:
         1. After compiling, turn on the debug mode, and use an oscilloscope or logic analyzer to observe the waveforms of PC6, PC7, PC8, and PC9
         2. After the timer enters the CC1 CC2 CC3 CC4 interrupt, the corresponding pull down the IO of PC6 PC7 PC8 PC9
4. Matters needing attention
     without