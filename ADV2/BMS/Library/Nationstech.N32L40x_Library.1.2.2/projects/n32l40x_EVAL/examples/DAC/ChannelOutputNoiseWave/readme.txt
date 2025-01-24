1、功能说明
    1、软件触发DAC输出4094的电平信号，噪声幅度为1
2、使用环境
    软件开发环境：  KEIL MDK-ARM V5.26.2.0
    硬件环境：      基于N32L40XML-STB V1.0开发
3、使用说明
    系统配置；
        1、时钟源：
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,DAC CLK=16M
        2、端口配置：
            PA4选择为模拟功能DAC OUT
        3、DAC：
            DAC选择软件触发，开启幅值为4094，开启噪声模式，噪声幅值为1
        4、主循环：
            一直触发DAC 输出
    使用方法：
        1、编译后打开调试模式，利用示波器观察PA4输出波形
        2、全速运行时，可看到PA4输出大约3.3V电平
4、注意事项
        无



1. Function description
     1. The software triggers the DAC to output a level signal of 4094, and the noise amplitude is 1
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on the development board N32L40XML-STB V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,DAC CLK=16M
         2. Port configuration:
             PA4 is selected as analog function, DAC OUT
         3. DAC:
             DAC selects software trigger, the turn-on amplitude is 4094, the noise mode is turned on, and the noise amplitude is 1
         4. Main loop:
             Always trigger DAC output
     Instructions:
         1. Open the debug mode after compiling, and use the oscilloscope to observe the output waveform of the PA4
         2. When running at full speed, you can see that the PA4 output is about 3.3V level
4. Matters needing attention
   None