1、功能说明

	/* 简单描述工程功能 */
        这个例程配置并演示使用各种算法时的计算结果


2、使用环境

        软件开发环境：
        IDE工具：KEIL MDK-ARM 5.26
    
        硬件环境：
        开发板 N32L40XML-STB V1.0


3、使用说明
	
	/* 描述相关模块配置方法；例如:时钟，I/O等 */
        SystemClock：64MHz
        USART：TX - PA9，波特率115200
	
	/* 描述Demo的测试步骤和现象 */
        1.编译后下载程序复位运行；
        2.查看串口打印信息，分别确认随机数计算结果是否随机，哈希算法的SHA1、SHA224、SHA256计算结果与网上软件计算结果对比是否一致，DES/AES算法的明文plain与密文解密结果decrypt out是否一致；


4、注意事项

1. Function description

         /* Briefly describe the project function */
         This routine configures and demonstrates the computation results when using various algorithms


2. Use environment

         Software development environment:
         IDE tool: KEIL MDK-ARM 5.26
    
         Hardware environment:
         Development Board N32L40XML-STB V1.0


3. Instructions for use

         /* Describe related module configuration methods; for example: clock, I/O, etc. */
         SystemClock: 64MHz
         USART: TX - PA9, baud rate 115200

         /* Describe the test steps and phenomena of the Demo */
         1. After compiling, download the program to reset and run;
         2. Check the serial port printing information to confirm whether the random number calculation result is random, 
             whether the SHA1, SHA224, SHA256 calculation results of the hash algorithm are consistent with the online software calculation results, 
             and the plaintext plain and ciphertext decryption results of the DES/AES algorithm are decrypted out. Is it consistent;


4. Matters needing attention