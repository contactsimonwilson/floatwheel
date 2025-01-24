1、功能说明
    1、TIM4周期触发DAC 输出正弦波形
2、使用环境
    软件开发环境：  KEIL MDK-ARM V5.26.2.0
    硬件环境：      基于N32L40XML-STB V1.0开发
3、使用说明
    系统配置；
        1、时钟源：
            HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,DAC CLK=16M,TIM4 CLK=32M
        2、端口配置：
            PA4选择为模拟功能DAC OUT
        3、TIM：
            TIM5 更新事件作为触发输出给DAC
        4、DAC：
            DAC选择TIM4 TRGO信号触发，使能DMA搬运正弦波数据到DAC
        5、DMA:
            DMA通道3回环模式搬移32个字到DAC输出寄存器
    使用方法：
        1、编译后打开调试模式，利用示波器观察PA4输出波形
        2、全速运行时，TIM4的每个周期触发PA4的一个数据，形成正弦波
4、注意事项
    无



1. Function description
     1. TIM4 cycle triggers DAC to output sine waveform
2. Use environment
     Software development environment: KEIL MDK-ARM V5.26.2.0
     Hardware environment: Developed based on the development board N32L40XML-STB V1.0
3. Instructions for use
     System Configuration;
         1. Clock source:
             HSE=8M,PLL=64M,AHB=64M,APB1=16M,APB2=32M,DAC CLK=16M,TIM4 CLK=32M
         2. Port configuration:
             PA4 is selected as analog function, DAC OUT
         3. TIM:
             TIM5 update event as trigger output to DAC
         4. DAC:
             The DAC selects the TIM4 TRGO signal to trigger, and enables the DMA to transfer the sine wave data to the DAC
         5. DMA:
             DMA channel 3 loopback mode moves 32 words to DAC output register
     Instructions:
         1. Open the debug mode after compiling, and use the oscilloscope to observe the output waveform of the PA4
         2. When running at full speed, each cycle of TIM4 triggers a data of PA4 to form a sine wave
4. Matters needing attention
   None