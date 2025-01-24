1. 功能说明
    USB Printer 打印机

2. 使用环境
    硬件环境：工程对应的开发硬件平台 
    开发板：    N32L43XM-STB N32L40XM-STB V1.1

3. 使用说明
    描述相关模块配置方法；例如:时钟，I/O等 
         1. SystemClock：48MHz
         2. USBClock: 48MHz

    描述Demo的测试步骤和现象 
         1. 编译后下载程序复位运行；
         2. 通过 USB 线连接 J3 USB 口，电脑识别出 USB 打印支持，可以通过EP2向打印机发送数据，在EP2回调函数中打断点可以看到正常接收数据。

4. 注意事项
    无

1. Function description
    USB Printer

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock: 48MHz
        2. USBClock: 48MHz
                  
    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. By connecting the USB cable to the J3 USB port, the computer recognizes the SUPPORT of USB printing and can send data to the printer through EP2,
            and the breakpoint in the EP2 callback function can be seen normally received data.
 
4. Matters needing attention
    None.