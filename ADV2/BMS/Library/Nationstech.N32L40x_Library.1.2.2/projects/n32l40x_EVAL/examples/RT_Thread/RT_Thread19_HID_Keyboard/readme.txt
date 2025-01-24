1、功能说明

    1、此例程展示 USB HID Keyboard 设备

2、使用环境

    /* 硬件环境：工程对应的开发硬件平台 */
    开发板：N32L43XM-STB N32L40XM-STB V1.1

3、使用说明

    /* 描述相关模块配置方法；例如:时钟，I/O等 */
    SystemClock：48MHz
    USB Clock：48MHz
    GPIO:   LED:D1--PA8、D2--PB4
    日志：  USART1: TX--PA9  RX--PA10    波特率：115200


    /* 描述Demo的测试步骤和现象 */
    1.编译后下载程序复位运行
    2.通过 USB 线连接 J3 USB 口，USB 挂载完成后，一直输入"A"

4、注意事项
    无

1. Function description
    1.This routine shows a USB HID Keyboard device

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:     N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock: 48MHz
    	2. USB Clock：48MHz
        3. GPIO:   LED:D1--PA8、D2--PB4
        LOG: USART1: TX--PA9 RX--PA10 Baud rate: 115200

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. Connect the J3 USB port with a USB cable, after the USB mount is completed, always input "A".

4. Matters needing attention
    None.