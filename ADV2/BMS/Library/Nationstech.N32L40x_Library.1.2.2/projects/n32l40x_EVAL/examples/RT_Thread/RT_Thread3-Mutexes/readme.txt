1、功能说明

    1、此例程展示在 RT_Thread 静态互斥量和动态互斥量的创建、获取和释放

2、使用环境

    /* 硬件环境：工程对应的开发硬件平台 */
    开发板：N32L43XM-STB N32L40XM-STB V1.1

3、使用说明

    /* 描述相关模块配置方法；例如:时钟，I/O等 */
    SystemClock：64MHz
    日志：TX--PA9  RX--PA10 ，波特率：115200

    /* 描述Demo的测试步骤和现象 */
    1.编译后下载程序复位运行
    2.接好串口打印工具
    3.本例程在main()里面创建两个线程，thread1 线程和 thread2 线程，
      查看打印日志，thread2 先获取静态互斥量，等到 thread2 释放静态互斥量后 thread1 才能获取到静态互斥量，再释放静态互斥量；
      然后 thread2 获取动态互斥量，等到 thread2 释放动态互斥量后 thread1 才能获取到动态互斥量，再删除动态互斥量。

4、注意事项
    无

1. Function description
    This routine shows the creation, acquisition, and release of static and dynamic mutex in RT_Thread

2. Use environment
    Hardware environment: development hardware platform corresponding to the project 
    Development board:      N32L43XM-STB N32L40XM-STB V1.1

3. Instructions for use
    Describe the configuration method of related modules; for example: clock, I/O, etc. 
        1. SystemClock: 64MHz
        2. GPIO: 
                    Log: TX--PA9 RX--PA10 Baud rate: 115200

    Describe the test steps and phenomena of Demo 
        1. After compiling, download the program to reset and run;
        2. Connect the serial port printing tool;
        3. This example creates two threads in main(), thread1 thread and thread2 thread, and checks the print log. 
            Thread2 first obtains the static mutex, after thread2 releases the static mutex, thread1 can get the static mutex, then release the static mutex;
            Thread2 then gets the dynamic mutex, after thread2 releases the dynamic mutex, thread1 can get the dynamic mutex, and then delete the dynamic mutex

4. Matters needing attention
    None.