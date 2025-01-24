1、功能说明

    1、此例程展示在 RT_Thread 系统调用调度器锁

2、使用环境

    /* 硬件环境：工程对应的开发硬件平台 */
    开发板：N32L43XM-STB N32L40XM-STB V1.1

3、使用说明

    /* 描述相关模块配置方法；例如:时钟，I/O等 */
    SystemClock：64MHz
    日志：串口打印 PA9(TX)，波特率：115200

    /* 描述Demo的测试步骤和现象 */
    1.编译后下载程序复位运行
    2.接好串口打印工具
    3.本例程创建两个线程，thread1 线程和 thread2 线程，thread2 线程优先级高于 thread1, thread1 线程将调度器上锁后，在解锁之前，不会切换到 thread2 线程，查看打印日志

4、注意事项
    无

1. Function description
    This routine is shown in the RT_Thread system call scheduler lock

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock: 64MHz
        Log(USART1): TX--PA9 Baud rate: 115200

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. Connect the serial port printing tool;
        3. This example creates two threads, thread1 thread and thread2 thread. Thread2 thread has a higher priority than thread1 thread. 
            The thread1 thread will lock the scheduler, before unlock, will not switch to the thread2 thread, see the print log

4. Matters needing attention
    None.