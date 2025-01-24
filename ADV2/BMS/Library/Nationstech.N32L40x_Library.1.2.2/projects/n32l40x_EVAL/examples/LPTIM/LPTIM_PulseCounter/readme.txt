1、功能说明
    1、LPTIM 计数IN1的上升沿个数
2、使用环境
    软件开发环境：  KEIL MDK-ARM V5.30.0.0
    硬件环境：      基于N32L43XM-STB开发
3、使用说明
    系统配置；
        1、时钟源：
            HSE=8M,PLL=108M,AHB=108M,APB1=27M,APB2=54M,LPTIM CLK=LSI
        2、端口配置：
            PC0选择为LPTIM IN1输入
            PB0选择为IO输出
        3、LPTIM：
            LPTIM外部计数模式，利用内部LSI时钟连续计数IN1上升沿个数
    使用方法：
        1、编译后打开调试模式，连接PB0和PC0，将变量tempCNT添加到watch窗口
        2、程序运行后，PB0输出10个脉冲周期，tempCNT等于10
4、注意事项
    无

1. Function description
     1. LPTIM counts the number of rising edges of IN1
2. Use environment
     Software development environment: KEIL MDK-ARM V5.30.0.0
     Hardware environment: Based on N32L43XM-STB development
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=108M,AHB=108M,APB1=27M,APB2=54M,LPTIM CLK=LSI
         2. Port configuration:
             PC0 selected as LPTIM IN1 input
             PB0 is selected as IO output
         3. LPTIM:
             LPTIM external counting mode, use the internal LSI clock to continuously count the number of rising edges of IN1
     Instructions:
         1. Open the debug mode after compiling, connect PB0 and PC0, and add the variable tempCNT to the watch window
         2. After the program runs, PB0 outputs 10 pulse cycles, and tempCNT is equal to 10
4. Matters needing attention
     none