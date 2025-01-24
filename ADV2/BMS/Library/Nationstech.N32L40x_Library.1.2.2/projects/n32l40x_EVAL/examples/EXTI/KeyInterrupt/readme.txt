1、功能说明

	1、此例程展示通过外部触发中断，控制 LED 闪烁


2、使用环境

	/* 硬件环境：工程对应的开发硬件平台 */
	开发板：N32L40XM-STB V1.1

3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
	1、SystemClock：64MHz
	2、GPIO：PA8 选择作为外部中断入口，PB4 控制 LED(D2) 常亮，PB5 控制 LED(D3) 闪烁


	/* 描述Demo的测试步骤和现象 */
	1.编译后下载程序复位运行；
	2.LED（D2）常亮，将 PA8 接入 3.3V 再断开，LED（D3） 闪烁；


4、注意事项
	无
	
	
	
1. Function description
    1. This example shows the control of LED flashing through an external trigger interrupt.
	
2. Use environment
    /*Hardware environment: Project corresponding development hardware platform*/
	1.Developed based on the evaluation board N32L40XM-STB V1.1
	
3. Instructions for use
    /* Describe the related module configuration method; For example: clock, I/O, etc. */
	1. SystemClock: 64 MHZ
	2. GPIO: PA8 is selected as the external interrupt entrance. PB4 controls LED(D2) to be on, and PB5 controls LED(D3) to blink.
	
	/* Describes the test steps and symptoms of Demo */
	1. The downloaded program is reset and running after compilation
	2. LED (D2) is steady on. Connect PA8 to 3.3V and then disconnect. LED (D3) blinks.
		
4. Matters needing attention
   None.