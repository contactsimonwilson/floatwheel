1、功能说明
    1、TIM2 利用CH1 CH2 CH3 CH4 CC值产生定时中断，翻转IO电平
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
            PC6选择为IO输出
            PC7选择为IO输出
            PC8选择为IO输出
            PC9选择为IO输出
        4、TIM：
            TIM2输出冻结模式，CH1 CH2 CH3 CH4比较值产生中断
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察PC6、PC7、PC8、PC9的波形
        2、程序运行后，对应通道达到比较值后，比较值累加并翻转对应IO口电平
4、注意事项
    无

1. Function description
     1. TIM2 uses the CH1 CH2 CH3 CH4 CC value to generate a timing interrupt and flip the IO level
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
             TIM2 output freeze mode, CH1 CH2 CH3 CH4 compare value interrupt
     Instructions:
         1. After compiling, turn on the debug mode, and use an oscilloscope or logic analyzer to observe the waveforms of PC6, PC7, PC8, and PC9
         2. After the program runs, after the corresponding channel reaches the comparison value, the comparison value accumulates and flips the corresponding IO port level
4. Matters needing attention
     without