#include "DVC1124_init.h"

/*

*/

DVC1124_Config_Type DVC1124_Config = {
	
	/*	CADC CC1 ����ʱ�����λ
		0 	0.5ms
		1	1.0ms
		2	2.0ms
		3	4.0ms
	*/
	.C1OW_0x56 = 3,
	//����
	.RES_0x56 = 0,
	//1���ŵ����������ֵ�Ĵ���,��ֵ��ѹ=OCD1T��0.25mV
	.OCD1T_0x59 = 0,	//�ر�
	//1��������������ֵ�Ĵ���,�е�ѹ=OCC1T��0.25mV
	.OCC1T_0x5A = 0,	//�ر�
	//1���ŵ���������ӳټĴ���,�ӳ�ʱ��=(OCD1D+1)��8ms
	.OCD1D_0x5B = 0,	//�ر�
	//1�������������ӳټĴ���,�ӳ�ʱ��=(OCC1D+1)��8ms
	.OCC1D_0x5C = 0,	//�ر�
	
	//2���ŵ����������ֵ�Ĵ���,��ֵ��ѹ=(OCD2T+1)��4mV
	.OCD2T_0x5E = 0,	//4A
	//����
	.RES_0x5E = 0,
	
	//2��������������ֵ�Ĵ�������ֵ��ѹ=(OCC2T+1)��4mV
	.OCC2T_0x5F = 0,	//4A
	//����
	.RES_0x5F = 0,
	
	//2���ŵ���������ӳټĴ���,�ӳ�ʱ��=(OCD2D+1)��4ms
	.OCD2D_0x60 = 24,	//100ms
	
	//2�������������ӳټĴ���,�ӳ�ʱ��=(OCC2D+1)��4ms
	.OCC2D_0x61 = 24,	//100ms
	
	//�ŵ��·������ֵ�Ĵ���,��ֵ��ѹ=SCDT��10mV
	.SCDT_0x62 = 40,	//400A
	//����
	.RES_0x62 = 0,
	
	//�ŵ��·�����ӳټĴ���,�ӳ�ʱ��=SCDD��7.81��s
	.SCDD_0x63 = 1,		//7.81��s
	
	//��ع�ѹ�����Ĵ���
	//��ֵ��ѹ=COVT��1mV+500mV		
	.COVT_H_0x70 = 0xE7,
	.COVT_L_0x71 = 4,	//4.2V
	.COVD_0x71 = 13,	//8-1S 9-2S 10-3S 11-4S 12-5S 13-6S 14-7S 15-8S
	//��ѹǷѹ�����Ĵ���
	//��ֵ��ѹ=CUVT��1mV
	.CUVT_H_0x72 = 0xCE,
	.CUVT_L_0x73 = 4,	//3.3V
	.CUVD_0x73 = 8,		//1S
};
/**
	* @˵��	AFE��ʼ������д��
	* @����	�Ĵ����Զ������Ĭ��ֵ
	* @����ֵ	�ɹ�/ʧ��
	* @ע	
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
	//0x51 	��/�ŵ���ƼĴ��� 
	g_AfeRegs.R81.LDPU	= 0;		//�ر� LOAD ����
	g_AfeRegs.R81.PDSGC = 0;		//�ر� PDSG �������
	g_AfeRegs.R81.PCHGC = 0;		//�ر� PCHG �������
	g_AfeRegs.R81.DSGM 	= 0; 		//DSG Ϊ��ɱ��������ģʽ
	g_AfeRegs.R81.DSGC  = 0;		//�ر� DSG �������
	g_AfeRegs.R81.CHGC  = 0;		//�ر� CHG �������
	
	//0x52
	g_AfeRegs.R82.PDWM	= 1;		//I2C ��ʱ��Ӱ�� PDSG �������״̬
	g_AfeRegs.R82.R82_RVD = 0;		//����λ
	g_AfeRegs.R82.DPC   = 30;		//����ǿ��Ϊ 30
	
	//0x53 	�ŵ����ο��ƼĴ���
	g_AfeRegs.R83.PDDM	= 0;		//DON ����Ϊ 0 ʱ�ر� PDSG �������DON ����Ϊ 0 ʱ�ر� PDSG �������
	g_AfeRegs.R83.PCWM 	= 1;		//I2C��ʱ��Ӱ�� PCHG �������״̬
	g_AfeRegs.R83.PCCM 	= 0;		//CON ����Ϊ 0 ʱ�ر� PCHG �������
	g_AfeRegs.R83.PCDM 	= 1;		//DON ���벻Ӱ�� PCHG �������״̬
	g_AfeRegs.R83.DWM  	= 0;		//I2C ��ʱ�ر� DSG �������
	g_AfeRegs.R83.DDM  	= 0;		//DON ����Ϊ 0 ʱ�ر� DSG �������
	g_AfeRegs.R83.DPDM 	= 0;		//PDSG ����ʱ�ر� DSG �������
	g_AfeRegs.R83.DBDM 	= 0;		//���������ڷŵ� NFET �������������ֵʱ�Զ����� DSG �������
	
	//0x54 	������ο��ƼĴ��� 
	g_AfeRegs.R84.CWM	= 0;		//I2C ��ʱ�ر� CHG �������
	g_AfeRegs.R84.CO1M	= 1;		//1 ���ŵ����ʱ��Ӱ�� CHG �������
	g_AfeRegs.R84.CO2M	= 1;		//2 ���ŵ����ʱ��Ӱ�� CHG �������
	g_AfeRegs.R84.CSM	= 1;		//�ŵ��·ʱ��Ӱ�� CHG �������
	g_AfeRegs.R84.CDM   = 1;		//DON ���벻Ӱ�� CHG �������״̬
	g_AfeRegs.R84.CCM	= 0;		//CON ����Ϊ 0 ʱ�ر� CHG �������
	g_AfeRegs.R84.CPCM	= 0;		//PCHG ����ʱ�ر� CHG �������
	g_AfeRegs.R84.CBDM	= 0;		//�ŵ�������ڳ�� NFET �������������ֵʱ�Զ����� CHG �������
	
	//0x55	CADC ���ƼĴ���
	g_AfeRegs.R85.HSFM	= 0;		//����߱� FET �������
	g_AfeRegs.R85.R85_RVD4_6 = 2;	//����λ ���ܸ��ķ���Ӱ�������������
	g_AfeRegs.R85.CAEW	= 1;		//оƬ����״̬�¿��� CADC
	g_AfeRegs.R85.CAES	= 1;		//оƬ����״̬�¿�����������
	g_AfeRegs.R85.R85_RVD1 = 0;		//����λ
	g_AfeRegs.R85.CAMZ	= 0;		//CADC �ֶ�У׼����λ ��Ч
	
	//0x56	
	g_AfeRegs.R86.R86_RVD 	= 15;	//����λ ���ܸ��ķ���Ӱ������ɼ�������
	
	//g_AfeRegs.R86.C1OW = 3;			//CADC CC1 ����ʱ�����λ	4.0ms
	g_AfeRegs.R86.C1OW = DVC1124_Config.C1OW_0x56;			//CADC CC1 ����ʱ�����λ
	g_AfeRegs.R86.C1OS = 3;			//оƬ����״̬�µ�������ʱ�����λ	32ms
	
	//0x57
	g_AfeRegs.R87 = 0x3F;			//����
	
	//0x58
	g_AfeRegs.R88 = 0x05;			//����
	
	//0x59	1 ���ŵ����������ֵ�Ĵ���
	//g_AfeRegs.R89.OCD1T = 0x40;		//��ֵ��ѹ=OCD1T��0.25mV
	g_AfeRegs.R89.OCD1T = DVC1124_Config.OCD1T_0x59;		//��ֵ��ѹ=OCD1T��0.25mV
	
	//0x5A	1 ��������������ֵ�Ĵ���
	//g_AfeRegs.R90.OCC1T = 0x40;		//��ֵ��ѹ=OCC1T��0.25mV
	g_AfeRegs.R90.OCC1T = DVC1124_Config.OCC1T_0x5A;		//��ֵ��ѹ=OCC1T��0.25mV
	
	//0x5B	1 ���ŵ���������ӳټĴ���
	//g_AfeRegs.R91.OCD1D = 0x18;		//1 ���ŵ���������ӳٿ���λ���ӳ�ʱ��=(OCD1D+1)��8ms
	g_AfeRegs.R91.OCD1D = DVC1124_Config.OCD1D_0x5B;		//1 ���ŵ���������ӳٿ���λ���ӳ�ʱ��=(OCD1D+1)��8ms
	
	//0x5C	1 �������������ӳټĴ���
	//g_AfeRegs.R92.OCC1D	= 0x18;		//1 �������������ӳٿ���λ���ӳ�ʱ��=(OCC1D+1)��8ms
	g_AfeRegs.R92.OCC1D	= DVC1124_Config.OCC1D_0x5C;		//1 �������������ӳٿ���λ���ӳ�ʱ��=(OCC1D+1)��8ms
	
	//0x5D	
	g_AfeRegs.R93 = 0xB0;			//����
	
	//0x5E	2 ���ŵ����������ֵ�Ĵ���
	g_AfeRegs.R94.R94_RVD = 0;		//����λ
	g_AfeRegs.R94.OCD2E = 1;		//2 ���ŵ��������ʹ�ܿ���λ	����
	//g_AfeRegs.R94.OCD2T = 7;		//2 ���ŵ����������ֵ����λ����ֵ��ѹ=(OCD2T+1)��4mV
	g_AfeRegs.R94.OCD2T = DVC1124_Config.OCD2T_0x5E;		//2 ���ŵ����������ֵ����λ����ֵ��ѹ=(OCD2T+1)��4mV
	
	//0x5F	2 ��������������ֵ�Ĵ���
	g_AfeRegs.R95.R95_RVD = 1;		//����λ
	g_AfeRegs.R95.OCC2E	= 1;		//2 ������������ʹ�ܿ���λ	����
	//g_AfeRegs.R95.OCC2T = 7;		//2 ��������������ֵ����λ����ֵ��ѹ=(OCC2T+1)��4mV
	g_AfeRegs.R95.OCC2T = DVC1124_Config.OCC2T_0x5F;		//2 ��������������ֵ����λ����ֵ��ѹ=(OCC2T+1)��4mV
	
	//0x60	2 ���ŵ���������ӳټĴ���
	//g_AfeRegs.R96.OCD2D = 0x18;		//2 ���ŵ���������ӳٿ���λ���ӳ�ʱ��=(OCD2D+1)��4ms
	g_AfeRegs.R96.OCD2D = DVC1124_Config.OCD2D_0x60;		//2 ���ŵ���������ӳٿ���λ���ӳ�ʱ��=(OCD2D+1)��4ms
	
	//0x61	2 �������������ӳټĴ���
	//g_AfeRegs.R97.OCC2D	= 0x18;		//2 �������������ӳٿ���λ���ӳ�ʱ��=(OCC2D+1)��4ms
	g_AfeRegs.R97.OCC2D	= DVC1124_Config.OCC2D_0x61;		//2 �������������ӳٿ���λ���ӳ�ʱ��=(OCC2D+1)��4ms
	
	//0x62	�ŵ��·������ֵ�Ĵ���
	g_AfeRegs.R98.R98_RVD = 0;		//����λ
	g_AfeRegs.R98.SCDE = 1;			//�ŵ��·����ʹ�ܿ���λ	����
	//g_AfeRegs.R98.SCDT = 16;		//�ŵ��·������ֵ����λ����ֵ��ѹ=SCDT��10mV
	g_AfeRegs.R98.SCDT = DVC1124_Config.SCDT_0x62;		//�ŵ��·������ֵ����λ����ֵ��ѹ=SCDT��10mV
	
	//0x63	�ŵ��·�����ӳټĴ���
	//g_AfeRegs.R99.SCDD = 0x10;		//�ŵ��·�����ӳٿ���λ���ӳ�ʱ��=SCDD��7.81��s
	g_AfeRegs.R99.SCDD = DVC1124_Config.SCDD_0x63;		//�ŵ��·�����ӳٿ���λ���ӳ�ʱ��=SCDD��7.81��s
	
	//0x64
	g_AfeRegs.R100 = 0x88;			//����
	
	//0x65	�������ѼĴ���;
	g_AfeRegs.R101.CWT = 0x00;		//�ر�����״̬�µ�������	��ֵ��ѹ=CWT��10��V
	
	//0x66	���������Ĵ���
	g_AfeRegs.R102.BDPT	= 0x00;		//�رճ�/�ŵ� NFET ���������������	��ֵ��ѹ=BDPT��40��V
	
	//0x67 0x68 0x69	��ر�������Ĵ���
	g_AfeRegs.R103_R105.CB[2] = 0;	//�� n �ڵ�ر����������λ
	g_AfeRegs.R103_R105.CB[1] = 0;	//0	�رյ� n �ڵ�ر�������
	g_AfeRegs.R103_R105.CB[0] = 0;	//1 ������ n �ڵ�ر������⣬����Ĵ������� 60s ���Զ���λΪ 0
	
	//0x6A 0x6B	0x6C	������μĴ���
	g_AfeRegs.R106.CM_H	= 0xF0;		//�� n �ڵ�ر������ο���λ	�ر�24-21���
	g_AfeRegs.R107.CM_M = 0;		//0 ������ n �ڵ�ر���
	g_AfeRegs.R108.CM_L = 0;		//1 �رյ� n �ڵ�ر�����ͬʱĬ�Ϲرյ� n �ڵ�ص�ѹ����
	g_AfeRegs.R108.PKM 	= 1;		//�ر� PACK ��ѹ����
	g_AfeRegs.R108.LDM 	= 1;		//�ر� LOAD ��ѹ����
	g_AfeRegs.R108.CTM	= 0;		//����оƬ�����¶Ȳ���
	g_AfeRegs.R108.V1P8M = 0;		//���� V1P8 ��ѹ����
	
	//0x6D	��ɱÿ��ƼĴ���
	g_AfeRegs.R109.R109_RVD = 0;	//����λ
	g_AfeRegs.R109.CUWM = 1;		//
	g_AfeRegs.R109.CPVS	= 1;		//6V
	g_AfeRegs.R109.COW	= 0;		//��زɼ��߶��߼�����λ �ر�
	g_AfeRegs.R109.CMM	= 0;		//�ر����ε�ص�ѹ����
	g_AfeRegs.R109.CVS	= 0;		//��ص�ѹ���޷�������ʾ��LSB=100��V
	
	//0x6E	VADC ���ƼĴ��� *
	g_AfeRegs.R110.VAE	= 1;		//VADC ʹ�ܿ���λ	����
	g_AfeRegs.R110.VASM = 1;		//VADC �� CADC CC2 ͬ������
	g_AfeRegs.R110.VAMP = 3;		//ÿ 8 �� CC2 ���� VADC ���� 1 ��
	g_AfeRegs.R110.R110_RVD = 3;	//����λ ����λ����Ϊ1
	g_AfeRegs.R110.VAO  = 3;		//VADC ����ʱ�����λ	6.02ms
	
	//0x6F	
	g_AfeRegs.R111 = 0x28;			//����
	
	//0x70 0x71	��ع�ѹ�����Ĵ���
	//g_AfeRegs.R112.COVT_H = 0xE7;	//��ֵ��ѹ=COVT��1mV+500mV	4200mV
	//g_AfeRegs.R113.COVT_L = 4;		//��ֵ��ѹ
	//g_AfeRegs.R113.COVD = 8;		//��ع�ѹ�����ӳٿ���λ 1S
	g_AfeRegs.R112.COVT_H = DVC1124_Config.COVT_H_0x70;		//��ֵ��ѹ=COVT��1mV+500mV	4200mV
	g_AfeRegs.R113.COVT_L = DVC1124_Config.COVT_L_0x71;		//��ֵ��ѹ
	g_AfeRegs.R113.COVD   = DVC1124_Config.COVD_0x71;		//��ع�ѹ�����ӳٿ���λ 1S
	
	//0x72 0x73	��ѹǷѹ�����Ĵ���
//	g_AfeRegs.R114.CUVT_H = 0x5D;	//��ֵ��ѹ=CUVT��1mV	1500mV
//	g_AfeRegs.R115.CUVT_L = 12;		//��ֵ��ѹ
//	g_AfeRegs.R115.CUVD = 8;		//���Ƿѹ�����ӳٿ���λ 1S
	g_AfeRegs.R114.CUVT_H = DVC1124_Config.CUVT_H_0x72;		//��ֵ��ѹ=CUVT��1mV	1500mV
	g_AfeRegs.R115.CUVT_L = DVC1124_Config.CUVT_L_0x73;		//��ֵ��ѹ
	g_AfeRegs.R115.CUVD   = DVC1124_Config.CUVD_0x73;		//���Ƿѹ�����ӳٿ���λ 1S
	
	//0x74	GP1 GP2 �� GP3 ģʽ�Ĵ���
	g_AfeRegs.R116.GP1M = 1;		//GP1	��������������
	g_AfeRegs.R116.GP2M = 6;		//GP2	�ж����
	g_AfeRegs.R116.GP3M = 1;		//GP3	��������������
	
	//0x75	GP4 GP5 �� GP6 ģʽ�Ĵ���
	g_AfeRegs.R117.GP4M = 1;		//GP4	��������������
	g_AfeRegs.R117.GP5M = 0;		//GP5   �ر�Ϊ����̬
	g_AfeRegs.R117.GP6M = 0;		//GP6   �ر�Ϊ����̬
	
	//0x76	оƬ���±����Ĵ���
	g_AfeRegs.R118.COTF = 0;		//оƬ�ں˹��¹ػ���ʶλ���� bit ���ڶ�ȡ���Զ���λΪ 0
	g_AfeRegs.R118.COTT = 0;		//�ر�оƬ�ں˹��±���
	
	//0x77	I2C ���Ź��Ĵ���
	g_AfeRegs.R119.V3P3ES = 1;		//оƬ����״̬�¿��� V3P3 ���
	g_AfeRegs.R119.V3P3EW = 1;		//оƬ����״̬�¿��� V3P3 ���
	g_AfeRegs.R119.V3P3M = 0;		//I2C ��ʱ��Ӱ�� V3P3 ���
	g_AfeRegs.R119.R119_RVD4 = 0;	//����λ
	g_AfeRegs.R119.IWTS = 0;		//I2C ���Ź���ʱ״̬λ
	g_AfeRegs.R119.IWT  = 0;		//I2C ���Ź���ʱ������λ �رն�ʱ��
	
	//0x78	��ʱ���ѼĴ���
	g_AfeRegs.R120.TIWK	= 0;		//��ʱ����״̬λ �ر�
	g_AfeRegs.R120.R120_RVD = 0;	//����λ
	g_AfeRegs.R120.R120_RVD = 0;	//��ʱ���Ѷ�ʱ������λ �ر�
	
	//0x79	�ж����μĴ���
	g_AfeRegs.R121.IWM 	= 1;		//оƬ���Ѻ��ж������
	g_AfeRegs.R121.IVOM = 1;		//VADC ת���������ж������
	g_AfeRegs.R121.ICCM = 1;		//CADC CC2 ת���������ж������
	g_AfeRegs.R121.ICOM = 1;		//��ع�ѹ���ж��� ���
	g_AfeRegs.R121.ICUM = 1;		//���Ƿѹ���ж������
	g_AfeRegs.R121.IOC1M = 1;		//1 ���������ж������
	g_AfeRegs.R121.IOC2M = 1;		//2 ���������ж������
	g_AfeRegs.R121.ISCM	= 0;		//�ŵ��·���ж�����͵�ƽ 1ms
}

uint8_t *p; 

void DVC1124_Init(void)
{
	IIC_Wakeup();					//7.����AFEоƬ
	IIC_Init();     				//8. ��ʼ��IICͨ�Žӿ�(MCU��AFE��ͨ�Žӿڣ�

#if ADDRESS>=0xC0
	GPIO_INTPUT();
#elif ADDRESS==0x40
	IIC_SLAVE_ADDRESS=ADDRESS>>1;
#endif
	DVC1124_Write_Init();
	
	p = (uint8_t*)&g_AfeRegs.R81;
	
	while(!DVC11XX_InitRegs());  	//8. AFEоƬ�Ĵ�����ʼ����д���û��Զ�����������ݣ�
	CleanError();					//д��Ĭ��ֵ���������
	
	Read_NFRT();//��ȡ�����޵�ֵ
}


