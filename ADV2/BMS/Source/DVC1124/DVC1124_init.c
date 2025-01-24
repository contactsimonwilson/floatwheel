#include "DVC1124_init.h"

/*

*/

DVC1124_Config_Type DVC1124_Config = {
	
	/*	CADC CC1 测量时间控制位
		0 	0.5ms
		1	1.0ms
		2	2.0ms
		3	4.0ms
	*/
	.C1OW_0x56 = 3,
	//保留
	.RES_0x56 = 0,
	//1级放电过流保护阈值寄存器,阈值电压=OCD1T×0.25mV
	.OCD1T_0x59 = 0,	//关闭
	//1级充电过流保护阈值寄存器,阈电压=OCC1T×0.25mV
	.OCC1T_0x5A = 0,	//关闭
	//1级放电过流保护延迟寄存器,延迟时间=(OCD1D+1)×8ms
	.OCD1D_0x5B = 0,	//关闭
	//1级充电过流保护延迟寄存器,延迟时间=(OCC1D+1)×8ms
	.OCC1D_0x5C = 0,	//关闭
	
	//2级放电过流保护阈值寄存器,阈值电压=(OCD2T+1)×4mV
	.OCD2T_0x5E = 0,	//4A
	//保留
	.RES_0x5E = 0,
	
	//2级充电过流保护阈值寄存器，阈值电压=(OCC2T+1)×4mV
	.OCC2T_0x5F = 0,	//4A
	//保留
	.RES_0x5F = 0,
	
	//2级放电过流保护延迟寄存器,延迟时间=(OCD2D+1)×4ms
	.OCD2D_0x60 = 24,	//100ms
	
	//2级充电过流保护延迟寄存器,延迟时间=(OCC2D+1)×4ms
	.OCC2D_0x61 = 24,	//100ms
	
	//放电短路保护阈值寄存器,阈值电压=SCDT×10mV
	.SCDT_0x62 = 40,	//400A
	//保留
	.RES_0x62 = 0,
	
	//放电短路保护延迟寄存器,延迟时间=SCDD×7.81μs
	.SCDD_0x63 = 1,		//7.81μs
	
	//电池过压保护寄存器
	//阈值电压=COVT×1mV+500mV		
	.COVT_H_0x70 = 0xE7,
	.COVT_L_0x71 = 4,	//4.2V
	.COVD_0x71 = 13,	//8-1S 9-2S 10-3S 11-4S 12-5S 13-6S 14-7S 15-8S
	//电压欠压保护寄存器
	//阈值电压=CUVT×1mV
	.CUVT_H_0x72 = 0xCE,
	.CUVT_L_0x73 = 4,	//3.3V
	.CUVD_0x73 = 8,		//1S
};
/**
	* @说明	AFE初始化配置写入
	* @参数	寄存器自定义参数默认值
	* @返回值	成功/失败
	* @注	
*/
static bool DVC11XX_InitRegs(void)
{
	//memcpy((char *)&g_AfeRegs+81,DVC11XX_PresetConfigRegData_R81To121,sizeof(DVC11XX_PresetConfigRegData_R81To121));
	return DVC11XX_WriteRegs(AFE_ADDR_R(81),sizeof(DVC11XX_PresetConfigRegData_R81To121));
}

void CleanError(void)
{
	g_AfeRegs.R0.cleanflag=0;
	while(!DVC11XX_WriteRegs(AFE_ADDR_R(0),1));
}

void DVC1124_Write_Init(void)
{
	//0x51 	充/放电控制寄存器 
	g_AfeRegs.R81.LDPU	= 0;		//关闭 LOAD 上拉
	g_AfeRegs.R81.PDSGC = 0;		//关闭 PDSG 驱动输出
	g_AfeRegs.R81.PCHGC = 0;		//关闭 PCHG 驱动输出
	g_AfeRegs.R81.DSGM 	= 0; 		//DSG 为电荷泵驱动输出模式
	g_AfeRegs.R81.DSGC  = 0;		//关闭 DSG 驱动输出
	g_AfeRegs.R81.CHGC  = 0;		//关闭 CHG 驱动输出
	
	//0x52
	g_AfeRegs.R82.PDWM	= 1;		//I2C 超时不影响 PDSG 驱动输出状态
	g_AfeRegs.R82.R82_RVD = 0;		//保留位
	g_AfeRegs.R82.DPC   = 30;		//下拉强度为 30
	
	//0x53 	放电屏蔽控制寄存器
	g_AfeRegs.R83.PDDM	= 0;		//DON 输入为 0 时关闭 PDSG 驱动输出DON 输入为 0 时关闭 PDSG 驱动输出
	g_AfeRegs.R83.PCWM 	= 1;		//I2C超时不影响 PCHG 驱动输出状态
	g_AfeRegs.R83.PCCM 	= 0;		//CON 输入为 0 时关闭 PCHG 驱动输出
	g_AfeRegs.R83.PCDM 	= 1;		//DON 输入不影响 PCHG 驱动输出状态
	g_AfeRegs.R83.DWM  	= 0;		//I2C 超时关闭 DSG 驱动输出
	g_AfeRegs.R83.DDM  	= 0;		//DON 输入为 0 时关闭 DSG 驱动输出
	g_AfeRegs.R83.DPDM 	= 0;		//PDSG 开启时关闭 DSG 驱动输出
	g_AfeRegs.R83.DBDM 	= 0;		//充电电流大于放电 NFET 体二极管续流阈值时自动开启 DSG 驱动输出
	
	//0x54 	充电屏蔽控制寄存器 
	g_AfeRegs.R84.CWM	= 0;		//I2C 超时关闭 CHG 驱动输出
	g_AfeRegs.R84.CO1M	= 1;		//1 级放电过流时不影响 CHG 驱动输出
	g_AfeRegs.R84.CO2M	= 1;		//2 级放电过流时不影响 CHG 驱动输出
	g_AfeRegs.R84.CSM	= 1;		//放电短路时不影响 CHG 驱动输出
	g_AfeRegs.R84.CDM   = 1;		//DON 输入不影响 CHG 驱动输出状态
	g_AfeRegs.R84.CCM	= 0;		//CON 输入为 0 时关闭 CHG 驱动输出
	g_AfeRegs.R84.CPCM	= 0;		//PCHG 开启时关闭 CHG 驱动输出
	g_AfeRegs.R84.CBDM	= 0;		//放电电流大于充电 NFET 体二极管续流阈值时自动开启 CHG 驱动输出
	
	//0x55	CADC 控制寄存器
	g_AfeRegs.R85.HSFM	= 0;		//允许高边 FET 驱动输出
	g_AfeRegs.R85.R85_RVD4_6 = 2;	//保留位 不能更改否则影响电流采样极性
	g_AfeRegs.R85.CAEW	= 1;		//芯片工作状态下开启 CADC
	g_AfeRegs.R85.CAES	= 1;		//芯片休眠状态下开启电流唤醒
	g_AfeRegs.R85.R85_RVD1 = 0;		//保留位
	g_AfeRegs.R85.CAMZ	= 0;		//CADC 手动校准控制位 无效
	
	//0x56	
	g_AfeRegs.R86.R86_RVD 	= 15;	//保留位 不能更改否则影响电流采集的速率
	
	//g_AfeRegs.R86.C1OW = 3;			//CADC CC1 测量时间控制位	4.0ms
	g_AfeRegs.R86.C1OW = DVC1124_Config.C1OW_0x56;			//CADC CC1 测量时间控制位
	g_AfeRegs.R86.C1OS = 3;			//芯片休眠状态下电流唤醒时间控制位	32ms
	
	//0x57
	g_AfeRegs.R87 = 0x3F;			//保留
	
	//0x58
	g_AfeRegs.R88 = 0x05;			//保留
	
	//0x59	1 级放电过流保护阈值寄存器
	//g_AfeRegs.R89.OCD1T = 0x40;		//阈值电压=OCD1T×0.25mV
	g_AfeRegs.R89.OCD1T = DVC1124_Config.OCD1T_0x59;		//阈值电压=OCD1T×0.25mV
	
	//0x5A	1 级充电过流保护阈值寄存器
	//g_AfeRegs.R90.OCC1T = 0x40;		//阈值电压=OCC1T×0.25mV
	g_AfeRegs.R90.OCC1T = DVC1124_Config.OCC1T_0x5A;		//阈值电压=OCC1T×0.25mV
	
	//0x5B	1 级放电过流保护延迟寄存器
	//g_AfeRegs.R91.OCD1D = 0x18;		//1 级放电过流保护延迟控制位，延迟时间=(OCD1D+1)×8ms
	g_AfeRegs.R91.OCD1D = DVC1124_Config.OCD1D_0x5B;		//1 级放电过流保护延迟控制位，延迟时间=(OCD1D+1)×8ms
	
	//0x5C	1 级充电过流保护延迟寄存器
	//g_AfeRegs.R92.OCC1D	= 0x18;		//1 级充电过流保护延迟控制位，延迟时间=(OCC1D+1)×8ms
	g_AfeRegs.R92.OCC1D	= DVC1124_Config.OCC1D_0x5C;		//1 级充电过流保护延迟控制位，延迟时间=(OCC1D+1)×8ms
	
	//0x5D	
	g_AfeRegs.R93 = 0xB0;			//保留
	
	//0x5E	2 级放电过流保护阈值寄存器
	g_AfeRegs.R94.R94_RVD = 0;		//保留位
	g_AfeRegs.R94.OCD2E = 1;		//2 级放电过流保护使能控制位	开启
	//g_AfeRegs.R94.OCD2T = 7;		//2 级放电过流保护阈值控制位，阈值电压=(OCD2T+1)×4mV
	g_AfeRegs.R94.OCD2T = DVC1124_Config.OCD2T_0x5E;		//2 级放电过流保护阈值控制位，阈值电压=(OCD2T+1)×4mV
	
	//0x5F	2 级充电过流保护阈值寄存器
	g_AfeRegs.R95.R95_RVD = 1;		//保留位
	g_AfeRegs.R95.OCC2E	= 1;		//2 级充电过流保护使能控制位	开启
	//g_AfeRegs.R95.OCC2T = 7;		//2 级充电过流保护阈值控制位，阈值电压=(OCC2T+1)×4mV
	g_AfeRegs.R95.OCC2T = DVC1124_Config.OCC2T_0x5F;		//2 级充电过流保护阈值控制位，阈值电压=(OCC2T+1)×4mV
	
	//0x60	2 级放电过流保护延迟寄存器
	//g_AfeRegs.R96.OCD2D = 0x18;		//2 级放电过流保护延迟控制位，延迟时间=(OCD2D+1)×4ms
	g_AfeRegs.R96.OCD2D = DVC1124_Config.OCD2D_0x60;		//2 级放电过流保护延迟控制位，延迟时间=(OCD2D+1)×4ms
	
	//0x61	2 级充电过流保护延迟寄存器
	//g_AfeRegs.R97.OCC2D	= 0x18;		//2 级充电过流保护延迟控制位，延迟时间=(OCC2D+1)×4ms
	g_AfeRegs.R97.OCC2D	= DVC1124_Config.OCC2D_0x61;		//2 级充电过流保护延迟控制位，延迟时间=(OCC2D+1)×4ms
	
	//0x62	放电短路保护阈值寄存器
	g_AfeRegs.R98.R98_RVD = 0;		//保留位
	g_AfeRegs.R98.SCDE = 1;			//放电短路保护使能控制位	开启
	//g_AfeRegs.R98.SCDT = 16;		//放电短路保护阈值控制位，阈值电压=SCDT×10mV
	g_AfeRegs.R98.SCDT = DVC1124_Config.SCDT_0x62;		//放电短路保护阈值控制位，阈值电压=SCDT×10mV
	
	//0x63	放电短路保护延迟寄存器
	//g_AfeRegs.R99.SCDD = 0x10;		//放电短路保护延迟控制位，延迟时间=SCDD×7.81μs
	g_AfeRegs.R99.SCDD = DVC1124_Config.SCDD_0x63;		//放电短路保护延迟控制位，延迟时间=SCDD×7.81μs
	
	//0x64
	g_AfeRegs.R100 = 0x88;			//保留
	
	//0x65	电流唤醒寄存器;
	g_AfeRegs.R101.CWT = 0x00;		//关闭休眠状态下电流唤醒	阈值电压=CWT×10μV
	
	//0x66	续流保护寄存器
	g_AfeRegs.R102.BDPT	= 0x00;		//关闭充/放电 NFET 体二极管续流保护	阈值电压=BDPT×40μV
	
	//0x67 0x68 0x69	电池被动均衡寄存器
	g_AfeRegs.R103_R105.CB[2] = 0;	//第 n 节电池被动均衡控制位
	g_AfeRegs.R103_R105.CB[1] = 0;	//0	关闭第 n 节电池被动均衡
	g_AfeRegs.R103_R105.CB[0] = 0;	//1 开启第 n 节电池被动均衡，该组寄存器会在 60s 后自动复位为 0
	
	//0x6A 0x6B	0x6C	电池屏蔽寄存器
	g_AfeRegs.R106.CM_H	= 0xF0;		//第 n 节电池保护屏蔽控制位	关闭24-21电池
	g_AfeRegs.R107.CM_M = 0;		//0 开启第 n 节电池保护
	g_AfeRegs.R108.CM_L = 0;		//1 关闭第 n 节电池保护，同时默认关闭第 n 节电池电压测量
	g_AfeRegs.R108.PKM 	= 1;		//关闭 PACK 电压测量
	g_AfeRegs.R108.LDM 	= 1;		//关闭 LOAD 电压测量
	g_AfeRegs.R108.CTM	= 0;		//开启芯片核心温度测量
	g_AfeRegs.R108.V1P8M = 0;		//开启 V1P8 电压测量
	
	//0x6D	电荷泵控制寄存器
	g_AfeRegs.R109.R109_RVD = 0;	//保留位
	g_AfeRegs.R109.CUWM = 1;		//
	g_AfeRegs.R109.CPVS	= 1;		//6V
	g_AfeRegs.R109.COW	= 0;		//电池采集线断线检测控制位 关闭
	g_AfeRegs.R109.CMM	= 0;		//关闭屏蔽电池电压测量
	g_AfeRegs.R109.CVS	= 0;		//电池电压以无符号数显示，LSB=100μV
	
	//0x6E	VADC 控制寄存器 *
	g_AfeRegs.R110.VAE	= 1;		//VADC 使能控制位	开启
	g_AfeRegs.R110.VASM = 1;		//VADC 与 CADC CC2 同步测量
	g_AfeRegs.R110.VAMP = 3;		//每 8 个 CC2 周期 VADC 测量 1 次
	g_AfeRegs.R110.R110_RVD = 3;	//保留位 这两位必须为1
	g_AfeRegs.R110.VAO  = 3;		//VADC 测量时间控制位	6.02ms
	
	//0x6F	
	g_AfeRegs.R111 = 0x28;			//保留
	
	//0x70 0x71	电池过压保护寄存器
	//g_AfeRegs.R112.COVT_H = 0xE7;	//阈值电压=COVT×1mV+500mV	4200mV
	//g_AfeRegs.R113.COVT_L = 4;		//阈值电压
	//g_AfeRegs.R113.COVD = 8;		//电池过压保护延迟控制位 1S
	g_AfeRegs.R112.COVT_H = DVC1124_Config.COVT_H_0x70;		//阈值电压=COVT×1mV+500mV	4200mV
	g_AfeRegs.R113.COVT_L = DVC1124_Config.COVT_L_0x71;		//阈值电压
	g_AfeRegs.R113.COVD   = DVC1124_Config.COVD_0x71;		//电池过压保护延迟控制位 1S
	
	//0x72 0x73	电压欠压保护寄存器
//	g_AfeRegs.R114.CUVT_H = 0x5D;	//阈值电压=CUVT×1mV	1500mV
//	g_AfeRegs.R115.CUVT_L = 12;		//阈值电压
//	g_AfeRegs.R115.CUVD = 8;		//电池欠压保护延迟控制位 1S
	g_AfeRegs.R114.CUVT_H = DVC1124_Config.CUVT_H_0x72;		//阈值电压=CUVT×1mV	1500mV
	g_AfeRegs.R115.CUVT_L = DVC1124_Config.CUVT_L_0x73;		//阈值电压
	g_AfeRegs.R115.CUVD   = DVC1124_Config.CUVD_0x73;		//电池欠压保护延迟控制位 1S
	
	//0x74	GP1 GP2 和 GP3 模式寄存器
	g_AfeRegs.R116.GP1M = 1;		//GP1	热敏电阻检测输入
	g_AfeRegs.R116.GP2M = 6;		//GP2	中断输出
	g_AfeRegs.R116.GP3M = 1;		//GP3	热敏电阻检测输入
	
	//0x75	GP4 GP5 和 GP6 模式寄存器
	g_AfeRegs.R117.GP4M = 1;		//GP4	热敏电阻检测输入
	g_AfeRegs.R117.GP5M = 0;		//GP5   关闭为高阻态
	g_AfeRegs.R117.GP6M = 0;		//GP6   关闭为高阻态
	
	//0x76	芯片过温保护寄存器
	g_AfeRegs.R118.COTF = 0;		//芯片内核过温关机标识位，该 bit 会在读取后自动复位为 0
	g_AfeRegs.R118.COTT = 0;		//关闭芯片内核过温保护
	
	//0x77	I2C 看门狗寄存器
	g_AfeRegs.R119.V3P3ES = 1;		//芯片休眠状态下开启 V3P3 输出
	g_AfeRegs.R119.V3P3EW = 1;		//芯片工作状态下开启 V3P3 输出
	g_AfeRegs.R119.V3P3M = 0;		//I2C 超时不影响 V3P3 输出
	g_AfeRegs.R119.R119_RVD4 = 0;	//保留位
	g_AfeRegs.R119.IWTS = 0;		//I2C 看门狗超时状态位
	g_AfeRegs.R119.IWT  = 0;		//I2C 看门狗定时器控制位 关闭定时器
	
	//0x78	定时唤醒寄存器
	g_AfeRegs.R120.TIWK	= 0;		//定时唤醒状态位 关闭
	g_AfeRegs.R120.R120_RVD = 0;	//保留位
	g_AfeRegs.R120.R120_RVD = 0;	//定时唤醒定时器控制位 关闭
	
	//0x79	中断屏蔽寄存器
	g_AfeRegs.R121.IWM 	= 1;		//芯片唤醒后中断无输出
	g_AfeRegs.R121.IVOM = 1;		//VADC 转换结束后中断无输出
	g_AfeRegs.R121.ICCM = 1;		//CADC CC2 转换结束后中断无输出
	g_AfeRegs.R121.ICOM = 1;		//电池过压后中断无 输出
	g_AfeRegs.R121.ICUM = 1;		//电池欠压后中断无输出
	g_AfeRegs.R121.IOC1M = 1;		//1 级过流后中断无输出
	g_AfeRegs.R121.IOC2M = 1;		//2 级过流后中断无输出
	g_AfeRegs.R121.ISCM	= 0;		//放电短路后中断输出低电平 1ms
}

uint8_t *p; 

void DVC1124_Init(void)
{
	IIC_Wakeup();					//7.唤醒AFE芯片
	IIC_Init();     				//8. 初始化IIC通信接口(MCU跟AFE的通信接口）

#if ADDRESS>=0xC0
	GPIO_INTPUT();
#elif ADDRESS==0x40
	IIC_SLAVE_ADDRESS=ADDRESS>>1;
#endif
	DVC1124_Write_Init();
	
	p = (uint8_t*)&g_AfeRegs.R81;
	
	while(!DVC11XX_InitRegs());  	//8. AFE芯片寄存器初始化（写入用户自定义的配置数据）
	CleanError();					//写入默认值后清除警报
	
	Read_NFRT();//读取电阻修调值
}


