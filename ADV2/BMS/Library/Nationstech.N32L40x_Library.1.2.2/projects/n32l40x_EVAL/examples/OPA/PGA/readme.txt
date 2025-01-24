1、功能说明
    1、OPA1 OPA2 PGA模式，放大输入电压2倍
2、使用环境
    软件开发环境：  KEIL MDK-ARM V5.26.2.0
    硬件环境：      基于N32L40XML-STB V1.0开发
3、使用说明
    系统配置；
        1、时钟源：
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,OPA CLK=16M
        2、端口配置：
            PA1选择为模拟功能OPA1 VP
            PA7选择为模拟功能OPA2 VP
            PA2选择为模拟功能OPA1 OUT
            PA6选择为模拟功能OPA2 OUT
        3、OPA：
            OPA1 OPA2 PGA功能，倍数2倍
    使用方法：
        1、编译后打开调试模式，用示波器观察OPA1 OPA2的输入和输出
        2、OPA输出=2*OPA输入
4、注意事项
    无



1. Function description
     1. OPA1 OPA2 PGA mode, amplify the input voltage by 2 times
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on the development board N32L40XML-STB V1.0
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,OPA CLK=16M
         2. Port configuration:
             PA1 selected as analog function, OPA1 VP
             PA7 selected as analog function, OPA2 VP
             PA2 is selected as analog function, OPA1 OUT
             PA6 is selected as analog function, OPA2 OUT
         3. OPA:
             OPA1 OPA2 PGA function, multiple 2 times
     Instructions:
         1. Open the debug mode after compiling, and observe the input and output of OPA1 and OPA2 with an oscilloscope
         2. OPA output=2*OPA input
4. Matters needing attention
   None