1、功能说明
    1、LPTIM 输出PWM信号
2、使用环境
    软件开发环境：  KEIL MDK-ARM V5.30.0.0
    硬件环境：      基于N32L43XM-STB开发
3、使用说明
    系统配置；
        1、时钟源：
            HSE=8M,PLL=108M,AHB=108M,APB1=27M,APB2=54M,LPTIM CLK=LSI
        2、端口配置：
            PC1选择为LPTIM输出
        3、LPTIM：
            LPTIM 4分频LSI，输出PWM信号
    使用方法：
        1、编译后打开调试模式，可观察到PC1引脚PWM信号
4、注意事项
    无


1. Function description
     1. LPTIM output PWM signal
2. Use environment
     Software development environment: KEIL MDK-ARM V5.30.0.0
     Hardware environment: Based on N32L43XM-STB development
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=108M,AHB=108M,APB1=27M,APB2=54M,LPTIM CLK=LSI
         2. Port configuration:
             PC1 selected as LPTIM output
         3. LPTIM:
             LPTIM 4-frequency LSI, output PWM signal
     Instructions:
         1. Open the debug mode after compiling, and you can observe the PWM signal of the PC1 pin
4. Matters needing attention
     none