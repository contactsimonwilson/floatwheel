1、功能说明
    1、TIM2 周期门控TIM3 TIM4
2、使用环境
    软件开发环境：  KEIL MDK-ARM V5.26.2.0
    硬件环境：      基于N32L40XM-STB_V1.0开发
3、使用说明
    系统配置；
        1、时钟源：
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM2 CLK=32M,TIM3 CLK=32M,TIM4 CLK=32M
        2、端口配置：
            PA0选择为TIM2的CH1输出
            PA6选择为TIM3的CH1输出
            PB6选择为TIM4的CH1输出
        3、TIM：
            TIM2 周期触发门控TIM3 TIM4的CH1,即TIM3为10倍周期TIM2，即TIM4为5倍周期TIM2
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM2 CH1、TIM3 CH1、TIM4 CH1的波形
        2、TIM4周期5倍于TIM2，TIM3周期10倍于TIM2
4、注意事项
    无
    
1. Function description
     1. TIM2 cycle gating TIM3 TIM4
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM2 CLK=32M,TIM3 CLK=32M,TIM4 CLK=32M
         2. Port configuration:
             PA0 is selected as the CH1 output of TIM2
             PA6 is selected as the CH1 output of TIM3
             PB6 is selected as the CH1 output of TIM4
         3. TIM:
             TIM2 cycle triggers the CH1 of gated TIM3 TIM4, that is, TIM3 is 10 times the period TIM2, that is, TIM4 is 5 times the period TIM2
     Instructions:
         1. After compiling, turn on the debug mode and use an oscilloscope or logic analyzer to observe the waveforms of TIM2 CH1, TIM3 CH1, and TIM4 CH1
         2. The cycle of TIM4 is 5 times that of TIM2, and the cycle of TIM3 is 10 times that of TIM2.
4. Matters needing attention
     without