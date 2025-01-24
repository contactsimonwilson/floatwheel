1、功能说明
    1、TIM3 CH1 CH2 CH3 CH4输出频率相同占空比不同的PWM
2、使用环境
    软件开发环境：  KEIL MDK-ARM V5.26.2.0
    硬件环境：      基于N32L40XM-STB_V1.0开发
3、使用说明
    系统配置；
        1、时钟源：
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM3 CLK=32M
        2、端口配置：
            PA6选择为TIM3的CH1输出
            PA7选择为TIM3的CH2输出
            PB0选择为TIM3的CH3输出
            PB1选择为TIM3的CH4输出
        3、TIM：
            TIM3 CH1 CH2 CH3 CH4周期相等，占空比不等
    使用方法：
        1、编译后打开调试模式，用示波器或者逻辑分析仪观察TIM3 CH1、CH2、CH3、CH4的波形
        2、程序运行后，产生4路周期相等占空比不同的PWM信号
4、注意事项
    无

1. Function description
     1. TIM3 CH1 CH2 CH3 CH4 outputs PWM with the same frequency and different duty cycles
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM3 CLK=32M
         2. Port configuration:
             PA6 is selected as the CH1 output of TIM3
             PA7 is selected as the CH2 output of TIM3
             PB0 is selected as the CH3 output of TIM3
             PB1 is selected as the CH4 output of TIM3
         3. TIM:
             TIM3 CH1 CH2 CH3 CH4 has the same period, and the duty cycle is not equal
     Instructions:
         1. After compiling, turn on the debug mode and use an oscilloscope or logic analyzer to observe the waveforms of TIM3 CH1, CH2, CH3, CH4
         2. After the program runs, 4 PWM signals with equal period and different duty cycle are generated
4. Matters needing attention
     without