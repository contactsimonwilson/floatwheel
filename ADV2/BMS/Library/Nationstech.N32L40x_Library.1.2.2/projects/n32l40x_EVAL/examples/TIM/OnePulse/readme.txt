1、功能说明
    1、TIM4 CH2上升沿触发CH1输出一个单脉冲
2、使用环境
    软件开发环境：  KEIL MDK-ARM V5.26.2.0
    硬件环境：      基于N32L40XM-STB_V1.0开发
3、使用说明
    系统配置；
        1、时钟源：
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM4 CLK=32M
        2、端口配置：
            PB6选择为TIM4的CH1输出
            PB7选择为TIM4的CH2输入
            PA3选择为IO输出
        3、TIM：
            TIM4 配置CH2上升沿触发CH1输出一个单脉冲
    使用方法：
        1、编译后打开调试模式，PA3连接PB7，用示波器或者逻辑分析仪观察TIM4 的CH1 的波形
        2、程序发送PA3的上升沿，TIM4 CH1输出一个单脉冲
4、注意事项
    无

/***   For English user ***/
1. Function description
     1. The rising edge of TIM4 CH2 triggers CH1 to output a single pulse
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM4 CLK=32M
         2. Port configuration:
             PB6 is selected as the CH1 output of TIM4
             PB7 is selected as the CH2 input of TIM4
             PA3 is selected as IO output
         3. TIM:
             TIM4 configures the rising edge of CH2 to trigger CH1 to output a single pulse
     Instructions:
         1. After compiling, turn on the debug mode, connect PA3 to PB7, and use an oscilloscope or logic analyzer to observe the waveform of CH1 of TIM4
         2. The program sends the rising edge of PA3, and TIM4 CH1 outputs a single pulse
4. Matters needing attention
     without