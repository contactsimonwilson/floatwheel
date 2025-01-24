1、功能说明
    1、TIM3 CH2捕获引脚通过CH1下降沿和CH2上升沿计算占空比和频率
2、使用环境
    软件开发环境：  KEIL MDK-ARM V5.26.2.0
    硬件环境：      基于N32L40XM-STB_V1.0开发
3、使用说明
    系统配置；
        1、时钟源：
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM3 CLK=32M
        2、中断：
            TIM3 CC2比较中断打开，抢断优先级0，子优先级0
        3、端口配置：
            PA7选择为TIM3的CH2输入
            PA3选择为IO输出
        4、TIM：
            TIM3 CH1下降沿捕获CH2信号，CH2上升沿捕获CH2信号
    使用方法：
        1、编译后打开调试模式，连接PA3和PA7，将Frequency、DutyCycle添加到watch窗口
        2、程序运行后，PA3发送的脉冲数据可以被捕获到占空比和频率到变量
4、注意事项
    无

1. Function description
     1. TIM3 CH2 capture pin calculates the duty cycle and frequency through the falling edge of CH1 and the rising edge of CH2
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on N32L40XM-STB_V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,TIM3 CLK=32M
         2. Interruption:
             TIM3 CC2 compare interrupt is turned on, preemption priority 0, subpriority 0
         3. Port configuration:
             PA7 is selected as the CH2 input of TIM3
             PA3 is selected as IO output
         4. TIM:
             TIM3 CH1 falling edge captures CH2 signal, CH2 rising edge captures CH2 signal
     Instructions:
         1. After compiling, open the debug mode, connect PA3 and PA7, and add Frequency and DutyCycle to the watch window
         2. After the program runs, the pulse data sent by PA3 can be captured to the duty cycle and frequency to the variable
4. Matters needing attention
     without