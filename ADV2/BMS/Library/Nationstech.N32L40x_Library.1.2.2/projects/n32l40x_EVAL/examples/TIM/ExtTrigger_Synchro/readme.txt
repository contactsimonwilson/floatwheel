1、功能说明
    1、TIM1 CH2门控CH1和TIM3 TIM4
2、使用环境
    软件开发环境：  KEIL MDK-ARM V5.26.2.0
    硬件环境：      基于N32L40XM-STB_V1.0开发
3、使用说明
    系统配置；
        1、时钟源：
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM1 CLK=64M,TIM3 CLK=32M,TIM4 CLK=32M
        2、端口配置：
            PA8选择为TIM1 CH1输出
            PA9选择为TIM1 CH2输入
            PA6选择为TIM3 CH1输出
            PB6选择为TIM4 CH1输出
        3、TIM：
            TIM1 CH2 门控CH1，门控TIM3,TIM4
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM1 CH1,TIM3 CH1,TIM4 CH1的波形
        2、TIM1 CH2高电平定时器开始计数，低电平停止
4、注意事项
    无

1. Function description
     1. TIM1 CH2 gated CH1 and TIM3 TIM4
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM1 CLK=64M,TIM3 CLK=32M,TIM4 CLK=32M
         2. Port configuration:
             PA8 is selected as TIM1 CH1 output
             PA9 is selected as TIM1 CH2 input
             PA6 is selected as TIM3 CH1 output
             PB6 is selected as TIM4 CH1 output
         3. TIM:
             TIM1 CH2 gated CH1, gated TIM3, TIM4
     Instructions:
         1. After compiling, turn on the debug mode, use an oscilloscope or logic analyzer to observe the waveforms of TIM1 CH1, TIM3 CH1, TIM4 CH1
         2. TIM1 CH2 high level timer starts counting, low level stops
4. Matters needing attention
     without