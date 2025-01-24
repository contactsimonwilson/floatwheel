1、功能说明

    1、此例程展示在 RT_Thread 信号量的创建、获取和释放

2、使用环境

    /* 硬件环境：工程对应的开发硬件平台 */
    开发板：N32L43XM-STB N32L40XM-STB V1.1

3、使用说明

    /* 描述相关模块配置方法；例如:时钟，I/O等 */
    SystemClock：64MHz
    GPIO：PA8 控制 LED(D1) 亮灭；PB4 控制 LED(D2) 闪烁
    KEY1--PA4
    日志:   TX--PA9  RX--PA10    波特率：115200

    /* 描述Demo的测试步骤和现象 */
    1.编译后下载程序复位运行
    2.本例程在main()创建三个线程，LED1 线程、 LED2 线程 和 KEY 线程，LED1 线程用于控制 D1 亮灭，LED2 线程用于控制 D2 500ms闪烁，
      KEY 线程扫描按键，当 KEY1 检测到按下时，释放信号量，LED1 线程获取信号量，获取成功后，翻转 D1；

4、注意事项
    无

1. Function description
    This example shows the creation, acquisition and release of the RT_Thread semaphore

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock: 64MHz
        2. GPIO: 
                    PA8 controls the LED (D1) to blink; PB4 controls the LED (D2) to blink;
                    KEY1: --PA4）
                    Log: TX--PA9 RX--PA10 Baud rate: 115200

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. This routine creates three threads in main(), LED1 thread, LED2 thread and KEY thread, LED1 thread is used to control D1 on and off, LED2 thread is used to control D2 500ms blink, 
            KEY thread scans the KEY, when KEY1 detects that it is pressed, release the semaphore, LED1 thread obtains the semaphore, and after obtaining it successfully, reverses D6

4. Matters needing attention
    None.