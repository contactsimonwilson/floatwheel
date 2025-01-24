/******************************************************************************
;  *   	@AFE model		 				DVC1110
;  *   	@Create Date         2023.4.10
;  *    @Official website		 http://www.devechip.com/
;  *----------------------Abstract Description---------------------------------
;  *		Header file for generic DVC1110 series.
;  *		Nanjing Devechip Electronic Technology Co., Ltd.
;  *		All rights reserved.
******************************************************************************/
#ifndef DVC1110_H__
#define DVC1110_H__
//------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "stm32f10x.h"
//---------------------------------------------------------------------------
typedef char                            bool;
//------------------------------------------------------------------------------


#define	 AFE_MAX_CELL_CNT               10


#define  AFE_MAX_GP_CNT                 6
#define  AFE_REG_VALUE(Rn)              *((u8 *)&g_AfeRegs.Rn)
#define  AFE_ADDR_R(n)                   n
#define _lsbVCELL                       0.0001 //VADC�����ֱ��ʣ���С�̶ȶ�Ӧ�ĵ�ѹֵ V/bit��
#define _lsbVCELL_signed                0.0002 //VADC�����ֱ��ʣ���С�̶ȶ�Ӧ�ĵ�ѹֵ V/bit��
#define _lsbCC1                        (5e-6)//CC1�Ĳ����ֱ��ʣ���С�̶ȶ�Ӧ�ĵ�ѹֵ��
#define _lsbCC2                        (0.3125e-6)//CC2�Ĳ����ֱ��ʣ���С�̶ȶ�Ӧ�ĵ�ѹֵ��
//------------------------------------------------------------------------------	
#define ADDRESS 												0x40//IIC�豸��ַ40 C0 C2 C4 C6
#define INVALID_TEMPERATURE            -128  //8λ�з���������Сֵ
#define GENERAL_DEBOUNCE_DLY_S          3    //ͨ�ñ�����ʱ
#define AFE_CMD_RETRY_MAX               3	   //SPI����ִ��ʧ�����Դ��� 
//------------------------------------------------------------------------------
#pragma pack (push,1)
enum{GP1=0,GP2,GP3,GP4,GP5,GP6};//GPn
//------------------------------------------------------------------------------
typedef struct{
u8 cleanR0;
}CleanFlag;
typedef struct{  //���ṹ����δ��ע�͵ĳ�ԱΪ�ڲ�Ԥ���Ĵ���������д����ܻ����оƬ�����쳣����
 union {struct{
   u8 SCD:1;   //REGMODE01/R0[0]/0x00/SCD_FLAG, �ŵ��·��ʶλ;0��δ�����ŵ��·;1���ѷ����ŵ��·������bit��0�������
   u8 OCC2:1;  //REGMODE01/R0[1]/0x00/OCIC2_FLAG, 2����������ʶλ;0��δ����2��������;1���ѷ���2��������������bit��0�������
   u8 OCD2:1;  //REGMODE01/R0[2]/0x00/OCID2_FLAG, 2���ŵ������ʶλ;0��δ����2���ŵ����;1���ѷ���2���ŵ����������bit��0�������
   u8 OCC1:1;  //REGMODE01/R0[3]/0x00/OCIC1_FLAG, 1����������ʶλ;0��δ����1��������;1���ѷ���1��������������bit��0�������
   u8 OCD1:1;  //REGMODE01/R0[4]/0x00/OCID1_FLAG, 1���ŵ������ʶλ;0��δ����1���ŵ����;1���ѷ���1���ŵ����������bit��0�������
   u8 CUV:1;   //REGMODE01/R0[5]/0x00/CUV_FLAG, ���Ƿѹ����;0��δ�������Ƿѹ;1���ѷ������Ƿѹ������bit��0�������
   u8 COV:1;   //REGMODE01/R0[6]/0x00/COV_FLAG, ��ع�ѹ��ʶλ;0��δ������ع�ѹ;1���ѷ�����ع�ѹ������bit��0�������
   u8 IWF:1;   //REGMODE01/R0[7]/0x00/I2C_WDTO_FLAG, I2C���Ź������ʶλ;0, δ����I2C���Ź����;1, �ѷ���I2C���Ź����������bit��0�������
	}bitmap;u8 cleanflag;
	}R0;
  struct{//R1
   u8 CST:4;  //REGMODE03/R1[3:0]/0x00/CHIP_ST,оƬ״̬��ʶλ;0000, оƬ�ӹػ�״̬������;0001, оƬ������״̬��I2Cͨ�Ż���;0010, оƬ������״̬����ʱ����;0011, оƬ������״̬���ŵ��������;0100, оƬ������״̬������������;0101, оƬ������״̬��2���ŵ��������;0110, оƬ������״̬��2������������;0111, оƬ������״̬���ŵ��·����;1000, оƬ������״̬�����������;1110, ʹоƬ��������״̬;1111, ʹоƬ����ض�״̬
   u8 CC2F:1; //REGMODE00/R1[4]/0x00/CC2_FLAG, CADC CC1ת����ɱ�ʶλ��I2C��ȡ�õ�ַ����Զ�����;0, CADC CC2δ���ת��;1, CADC CC2�����ת��
   u8 CC1F:1; //REGMODE00/R1[5]/0x00/CC1_FLAG, CADC CC1ת����ɱ�ʶλ��I2C��ȡ�õ�ַ����Զ�����;0, CADC CC1δ���ת��;1, CADC CC1�����ת��
   u8 VADF:1; //REGMODE00/R1[6]/0x00/VADC_FLAG, VADCת����ɱ�ʶλ��I2C��ȡ�õ�ַ����Զ�����;0, VADCδ���ת��;1, VADC�����ת��
   u8 PD:1;   //REGMODE00/R1[7]/0x00/PACK_DET, ���������ʶλ;0, δ��⵽�����;1, �Ѽ�⵽�����
  }R1;
  struct{//CC1: CADC CC1����ֵ[15:0], �з��Ŷ����Ʋ���, LSB=5��V
    u8 CC1_H;  //REGMODE00/R2[7:0]/0x00/CC1����ֵ���ֽ�
    u8 CC1_L;  //REGMODE00/R3[7:0]/0x00/CC1����ֵ���ֽ�
  }R2_3;
  struct{//CC2: CADC CC2����ֵ[19:0], �з��Ŷ����Ʋ���, LSB=5/16��V
    u8 CC2_H;  //REGMODE00/R4[7:0]/0x00/CC2����ֵ���ֽ�
    u8 CC2_M;  //REGMODE00/R5[7:0]/0x00/CC2����ֵ���ֽ�
    u8 CHGF:1; //REGMODE00/R6[0]/0x00/CHG_FLAG, CHG���������ʶλ;0, CHG��������ѹر�;1, CHG��������ѿ���
    u8 DSGF:1; //REGMODE00/R6[1]/0x00/DSG_FLAG, DSG���������ʶλ;0, DSG��������ѹر�;1, DSG��������ѿ���
    u8 PCHGF:1;//REGMODE00/R6[2]/0x00/PCHG_FLAG, PCHG���������ʶλ;0, PCHG��������ѹر�;1, PCHG��������ѿ���
    u8 PDSGF:1;//REGMODE00/R6[3]/0x00/PDSG_FLAG, PDSG���������ʶλ;0, PDSG��������ѹر�;1, PDSG��������ѿ���
    u8 CC2_L:4;//REGMODE00/R6[7:4]/0x00/CC2����ֵ���ֽ�
  }R4_6;
  struct{//VBAT��ѹֵ[15:0], �޷��Ŷ����ƣ�LSB=12.8mV
    u8 VBAT_H; //REGMODE00/R7[7:0]/0x00/VBAT��ѹֵ��8λ
    u8 VBAT_L; //REGMODE00/R8[7:0]/0x00/VBAT��ѹֵ��8λ
  }R7_8;
  struct{//VPACK��ѹֵ[15:0], �޷��Ŷ����ƣ�LSB=12.8mV
    u8 VPK_H; //REGMODE00/R9[7:0]/0x00/VPK��ѹֵ��8λ
    u8 VPK_L; //REGMODE00/R10[7:0]/0x00/VPK��ѹֵ��8λ
  }R9_10;
  struct{//VLOAD��ѹֵ[15:0], �޷��Ŷ����ƣ�LSB=12.8mV
    u8 VLD_H; //REGMODE00/R11[7:0]/0x00/VPK��ѹֵ��8λ
    u8 VLD_L; //REGMODE00/R12[7:0]/0x00/VPK��ѹֵ��8λ
  }R11_12;
  struct{//VCTоƬ�ں��¶�ֵ[15:0], �޷��Ŷ�����, оƬ�ں��¶�=VCT*0.24467-271.03
    u8 VCT_H; //REGMODE00/R13[7:0]/0x00/VCT��ѹֵ��8λ
    u8 VCT_L; //REGMODE00/R14[7:0]/0x00/VCT��ѹֵ��8λ
  }R13_14;
  struct{//V1P8��ѹֵ[15:0], �޷��Ŷ����ƣ�LSB=100��V
    u8 V1P8_H; //REGMODE00/R15[7:0]/0x00/V1P8��ѹֵ��8λ
    u8 V1P8_L; //REGMODE00/R16[7:0]/0x00/V1P8��ѹֵ��8λ
  }R15_16;
  struct{struct{//GPn��ѹֵ[15:0], �޷��Ŷ����ƣ�LSB=100��V
    u8 VGP_H; //REGMODE00/R17[7:0]/0x00/GPn��ѹֵ��8λ
    u8 VGP_L; //REGMODE00/R18[7:0]/0x00/GPn��ѹֵ��8λ
		}VGP[6]; //R17_28
	}R17_28;
  struct{struct{//CELLn��ѹֵ[15:0], �޷��Ŷ����ƣ�LSB=100��V
    u8 VCELL_H; //REGMODE00/R29[7:0]/0x00/CELLn��ѹֵ��8λ
    u8 VCELL_L; //REGMODE00/R30[7:0]/0x00/CELLn��ѹֵ��8λ
  }VCELLS[24];//R29_R76
	}R29_76;
  struct{//VADCֱ��ʧ����ѹֵ[15:0], �޷��Ŷ����ƣ�LSB=100��V
    u8 VVOS_H; //REGMODE00/R77[7:0]/0x00/VADCֱ��ʧ����ѹֵ��8λ
    u8 VVOS_L; //REGMODE00/R78[7:0]/0x00/VADCֱ��ʧ����ѹֵ��8λ
  }R77_78;
  struct{//CADCֱ��ʧ����ѹֵ[15:0],�з��Ŷ����ƣ�LSB=5��V
    u8 CVOS_H; //REGMODE00/R79[7:0]/0x00/CADCֱ��ʧ����ѹֵ��8λ
    u8 CVOS_L; //REGMODE00/R80[7:0]/0x00/CADCֱ��ʧ����ѹֵ��8λ
  }R79_80;
  struct{
    u8 CHGC:2;  //REGMODE03/R81[1:0]/0x00/CHG_CTRL[1:0], CHG�����������λ;00/01, �ر�CHG�������;10, �ر�CHG����������������ڷŵ��������FET�������������ֵʱ����CHG�������;11, ����CHG�������
    u8 DSGC:2;  //REGMODE03/R81[3:2]/0x00/DSG_CTRL[1:0], DSG�����������λ;00/01, �ر�DSG�������;10, �ر�DSG����������������ڳ���������FET�������������ֵʱ����DSG�������;11, ����DSG�������
    u8 DSGM:1;  //REGMODE03/R81[4]/0x00/DSG_MODE, DSG�������ģʽ����λ;0, DSGΪ��ɱ��������ģʽ;1, DSGΪԴ���������ģʽ
    u8 PCHGC:1; //REGMODE03/R81[5]/0x00/PCHG_CTRL, PCHG�����������λ;0, �ر�PCHG�������;1, ����PCHG�������
    u8 PDSGC:1; //REGMODE03/R81[6]/0x00/PDSG_CTRL, PDSG�����������λ;0, �ر�PDSG�������;1, ����PDSG�������
    u8 LDPU:1;  //REGMODE03/R81[7]/0x00/LOAD_PULLUP, LOAD��������λ;0, �ر�LOAD����;1, ����LOAD����
  }R81;
  struct{
    u8 DPC:5;  //REGMODE03/R82[4:0]/0x10/DSG_PD_CTRL[4:0], DSG�����������ǿ�ȿ���λ����ֵԽ����������Խǿ
		u8 R82_RVD:2;
    u8 PDWM:1; //REGMODE03/R82[7]/0x01/PDSG_I2C_WDTO_MASK, I2C��ʱ�ر�PDSG�����������λ;0, I2C��ʱ�ر�PDSG�������;1, I2C��ʱ��Ӱ��PDSG�������״̬
  }R82;
  struct{
    u8 DBDM:1;  //REGMODE03/R83[0]/0x00/DSG_BODY_DIODE_MASK, �ŵ�NFET������ܱ�������λ;0, ���������ڷŵ�NFET�������������ֵʱ�Զ�����DSG�������;1, ���������ڷŵ�NFET�������������ֵʱ��Ӱ��DSG�������״̬
    u8 DPDM:1;  //REGMODE03/R83[1]/0x00/DSG_PDSG_MASK, PDSG����ʱ�ر�DSG�����������λ;0, PDSG����ʱ�ر�DSG�������;1, PDSG����ʱ��Ӱ��DSG�������״̬
    u8 DDM:1;   //REGMODE03/R83[2]/0x00/DSG_DOFFN_MASK, DON(DSG_OFF_N)�ر�DSG�����������λ;0, DON����Ϊ0ʱ�ر�DSG�������;1, DON���벻Ӱ��DSG�������״̬
    u8 DWM:1;   //REGMODE03/R83[3]/0x00/DSG_I2C_WDTO_MASK, I2C��ʱ�ر�DSG�����������λ;0, I2C��ʱ�ر�DSG�������;1, I2C��ʱ��Ӱ��DSG�������
    u8 PCDM:1;  //REGMODE03/R83[4]/0x01/PCHG_DON_MASK, DON(DSG_OFF_N)�ر�PCHG�����������λ;0, DON����Ϊ0ʱ�ر�PCHG�������;1, DON���벻Ӱ��PCHG�������״̬
    u8 PCCM:1;  //REGMODE03/R83[5]/0x00/PCHG_CON_MASK, CON(CHG_OFF_N)�ر�PCHG�����������λ;0, CON����Ϊ0ʱ�ر�PCHG�������;1, CON���벻Ӱ��PCHG�������״̬
    u8 PCWM:1;  //REGMODE03/R83[6]/0x00/PCHG_I2C_WDTO_MASK, I2C��ʱ�ر�PCHG�����������λ;0, I2C��ʱ�ر�PCHG�������;1, I2C��ʱ��Ӱ��PCHG�������״̬
    u8 PDDM:1;  //REGMODE03/R83[7]/0x00/PDSG_DON_MASK, DON(DSG_OFF_N)�ر�PDSG�����������λ;0, DON����Ϊ0ʱ�ر�PDSG�������;1, DON���벻Ӱ��PDSG�������״̬
  }R83;
  struct{
    u8 CBDM:1;  //REGMODE03/R84[0]/0x00/CHG_BODY_DIODE_MASK, ���NFET������ܱ�������λ;0, �ŵ�������ڳ��NFET�������������ֵʱ�Զ�����CHG�������;1, �ŵ�������ڳ��NFET�������������ֵʱ��Ӱ��CHG�������״̬
    u8 CPCM:1;  //REGMODE03/R84[1]/0x00/CHG_PCHG_MASK, PCHG����ʱ�ر�CHG�����������λ;0, PCHG����ʱ�ر�CHG�������;1, PCHG����ʱ��Ӱ��CHG�������״̬
    u8 CCM:1;   //REGMODE03/R84[2]/0x00/CHG_CON_MASK, CON(CHG_OFF_N)�ر�CHG�����������λ;0, CON����Ϊ0ʱ�ر�CHG�������;1, CON���벻Ӱ��CHG�������״̬
    u8 CDM:1;   //REGMODE03/R84[3]/0x01/CHG_DON_MASK, DON(DSG_OFF_N)�ر�CHG�����������λ;0, DON����Ϊ0ʱ�ر�CHG�������;1, DON���벻Ӱ��CHG�������״̬
    u8 CSM:1;   //REGMODE03/R84[4]/0x01/CHG_SCD_MASK, �ŵ��·ʱ�ر�CHG�����������λ;0, �ŵ��·ʱ�ر�CHG�������;1, �ŵ��·ʱ��Ӱ��CHG�������
    u8 CO2M:1;  //REGMODE03/R84[5]/0x01/CHG_OCD2_MASK, 2���ŵ����ʱ�ر�CHG�����������λ;0, 2���ŵ����ʱ�ر�CHG�������;1, 2���ŵ����ʱ��Ӱ��CHG�������
    u8 CO1M:1;  //REGMODE03/R84[6]/0x01/CHG_OCD1_MASK, 1���ŵ����ʱ�ر�CHG�����������λ;0, 1���ŵ����ʱ�ر�CHG�������;1, 1���ŵ����ʱ��Ӱ��CHG�������
    u8 CWM:1;   //REGMODE03/R84[7]/0x00/CHG_I2C_WDTO_MASK, I2C��ʱ�ر�CHG�����������λ;0, I2C��ʱ�ر�CHG�������;1, I2C��ʱ��Ӱ��CHG�������
  }R84;

  struct{
    u8 CAMZ:1;  //REGMODE02/R85[0]/0x00/CADC_MZ, CADC�ֶ�У�����λ;0, ��Ч;1, ����һ��CADCУ׼����bit���Զ���λΪ0
		u8 R85_RVD1:1;
    u8 CAES:1;  //REGMODE03/R85[2]/0x01/CADC_EN_SLEEP, оƬ����״̬��CADCʹ�ܿ���λ;0, оƬ����״̬�¹ر�CADC;1, оƬ����״̬�¿���CADC
    u8 CAEW:1;  //REGMODE03/R85[3]/0x01/CADC_EN_WORK, оƬ����״̬��CADCʹ�ܿ���λ;0, оƬ����״̬�¹ر�CADC;1, оƬ����״̬�¿���CADC
		u8 R85_RVD4_6:3;
    u8 HSFM:1;  //REGMODE03/R85[7]/0x00/HSFET_MASK, �߱�NFET�����������λ;0, ����߱�NFET�������;1, ���θ߱�NFET�������
  }R85;
  struct{
  	u8 C1OS:2;  //REGMODE03/R86[1:0]/0x03/CC1_OSR_SLEEP[1:0], оƬ����״̬��CC1�������ʿ���λ;00, 128;01, 256;10, 512;11, 1024
  	u8 C1OW:2;  //REGMODE03/R86[3:2]/0x03/CC1_OSR_WORK[1:0], оƬ����״̬��CC1�������ʿ���λ;00, 128;01, 256;10, 512;11, 1024
  u8 R86_RVD:4;	
  }R86;  
  u8 R87;
  u8 R88;
  struct{
		u8 OCD1T; //REGMODE03/R89[7:0]/0x00/OCD1_TH[7:0], 1���ŵ����������ֵ����λ, V(OCD1_TH)=OCD1T*0.25mV
  }R89; 
  struct{
		u8 OCC1T; //REGMODE03/R90[7:0]/0xFF/OCC1_TH[7:0], 1��������������ֵ����λ, V(OCC1_TH)=OCD1T*0.25mV
  }R90; 
  struct{
		u8 OCD1D; //REGMODE03/R91[7:0]/0x00/OCD1_DLY[7:0], 1���ŵ���������ӳٿ���λ, T(OCD1_DLY)=OCD1D*8ms
  }R91; 
  struct{
		u8 OCC1D; //REGMODE03/R92[7:0]/0x00/OCC1_DLY[7:0], 1�������������ӳٿ���λ, T(OCD1_DLY)=OCD1D*8ms
  }R92; 
	u8 R93;
  struct{
    u8 OCD2T:6;  //REGMODE03/R94[5:0]/0x00/OCD2_TH[5:0], 2���ŵ���������ֵ����λ, ��ֵ��ѹ=(OCD2T+1)*4mV
    u8 OCD2E:1;  //REGMODE03/R94[6]/0x01/OCD2_EN, 2���ŵ�������ʹ�ܿ���λ;0, �ر�;1, ����
    u8 R94_RVD:1;
  }R94;
  struct{
    u8 OCC2T:6;  //REGMODE03/R95[5:0]/0x00/OCC2_TH[7:0], 2�������������ֵ����λ, ��ֵ��ѹ=(OCC2T+1)*4mV
    u8 OCC2E:1;  //REGMODE03/R95[6]/0x01/OCC2_EN, 2�����������ʹ�ܿ���λ;0, �ر�;1, ����
    u8 R95_RVD:1;
}R95;
  struct{  
   	u8 OCD2D;//REGMODE03/R96[7:0]/0x00/OCD2_DLY[7:0], 2���ŵ���������ӳٿ���λ, �ӳ�ʱ��=OCD2D*4ms  
  }R96;
  struct{  
  	u8 OCC2D;//REGMODE03/R97[7:0]/0x00/OCC2_DLY[7:0], 2�������������ӳٿ���λ, �ӳ�ʱ��=OCC2D*4ms 
  }R97;
  struct{
    u8 SCDT:6;  //REGMODE03/R98[5:0]/0x00/SCD_VTH[5:0], �ŵ��·�����ֵ����λ, ��ֵ��ѹ=SCDT*10mV
    u8 SCDE:1;  //REGMODE03/R98[6]/0x01/SCD_EN, �ŵ��·���ʹ�ܿ���λ;0, �ر�;1, ����
    u8 R98_RVD:1;
  }R98;
  struct{  
		u8 SCDD;//REGMODE03/R99[7:0]/0x00/SCD_DLY[7:0], �ŵ��·����ӳٿ���λ, �ӳ�ʱ��=SCDD*7.81us
  }R99;
  u8 R100;
  struct{    
		u8 CWT;   //REGMODE03/R101[7:0]/0x00/CURRENT_WKUP_TH[7:0], оƬ����״̬�µ���������ֵ����λ, ��ֵ��ѹ=CWT*10��V
  }R101;
  struct{  
		u8 BDPT;  //REGMODE03/R102[7:0]/0x00/BODY_DIODE_PRT_TH[7:0], ��/�ŵ�NFET�����������������ֵ����λ����ֵ��ѹ=BDPT*40��V
  }R102;
  struct{  
		u8 CB[3]; //REGMODE03/R103[7:0],R104[7:0],R105[7:0]/0x00/CELL_BAL[17:1], ��n�ڵ�ر����������λ;0, �رյ�n�ڵ�ر�������;1, ������n�ڵ�ر�������
  }R103_R105;
  struct{
    u8 CM_H;    //REGMODE03/R106[7:0]/0xAA/��10~8�ڵ�ر������ο���λ;0, ������n�ڵ�ر���;1, �رյ�n�ڵ�ر���, ͬʱĬ�Ϲرյ�n�ڵ�ص�ѹ����
  }R106;
  struct{
    u8 CM_M;    //REGMODE03/R107[7:0]/0x55/��7~5�ڵ�ر������ο���λ
  }R107;
  struct{
    u8 V1P8M:1; //REGMODE03/R108[0]/0x00/V1P8_MASK, V1P8��ѹ�������ο���λ;0, ����V1P8��ѹ����;1, �ر�V1P8��ѹ����
    u8 CTM:1;   //REGMODE03/R108[1]/0x00/CORE_TEMP_MASK, оƬ�����¶Ȳ������ο���λ;0, ����оƬ�����¶Ȳ���;1, �ر�оƬ�����¶Ȳ���
    u8 LDM:1;   //REGMODE03/R108[2]/0x00/LOAD_MASK, LOAD��ѹ�������ο���λ;0, ����LOAD��ѹ����;1, �ر�LOAD��ѹ����
    u8 PKM:1;   //REGMODE03/R108[3]/0x00/PACK_MASK, PACK��ѹ�������ο���λ;0, ����PACK��ѹ����;1, �ر�PACK��ѹ����
    u8 CM_L:4;    //REGMODE03/R108[7:4]/0x00/NULL��ر������ο���λ
  }R108;
  struct{
    u8 CVS:1; //REGMODE03/R109[0]/0x00/CELL_VOLTAGE_SIGNED, ��ص�ѹ�з�������ʾ����λ;0, ��ص�ѹ���޷�������ʾ��LSB=100��V;1, ��ص�ѹ���з�������ʾ��LSB=200��V
    u8 CMM:1; //REGMODE03/R109[1]/0x00/ELL_MASK_MEAS, ���ε�ص�ѹ��������λ;0, �ر����ε�ص�ѹ����;1, �������ε�ص�ѹ����
    u8 COW:1; //REGMODE03/R109[2]/0x00/CELL_OPEN_WIRE, ��زɼ��߶��߼�����λ;0, �ر�;1, �������߼�⣬��bit����1s���Զ���λΪ0
    u8 CPVS:3;//REGMODE03/R109[5:3]/0x05/CP_VS[2:0], ��ɱ������ѹ����λ;000, �ر�;001, 6V;010, 7V;011, 8V;100, 9V;101, 10V;110, 11V;111, 12V
    u8 CUWM:1;//REGMODE03/R109[6]/0X00/CUV_WATCHDOG_MODE,���Ƿѹ���Ź����ο���λ;0, ����; 1 �ر�
		u8 R109_RVD:1;
  }R109;
 struct{
  u8 VAO:2;  //REGMODE03/R110[1:0]/0x01/VADC_OSR[1:0], VADC�������ʿ���λ;00, 64;01, 128;10, 256;11, 512
  u8 R110_RVD:2;
  u8 VAMP:2; //REGMODE03/R110[5:4]/0x00/VADC_MEAS_PERIOD[1:0], VADCͬ���������ڿ���λ;00, ÿ1��CC2����VADC����1��;01, ÿ2��CC2����VADC����1��;10, ÿ4��CC2����VADC����1��;11, ÿ8��CC2����VADC����1��
  u8 VASM:1; //REGMODE03/R110[6]/0x01/VADC_SYNC_MEAS_EN, VADC��CADC CC2ͬ����������λ;0, VADC��������;1, VADC��CADC CC2ͬ������
  u8 VAE:1;  //REGMODE03/R110[7]/0x01/VADC_EN, VADCʹ�ܿ���λ;0, �ر�;1, ����
}R110;
  u8 R111;
  struct{
    u8 COVT_H;  //REGMODE03/R112[7:0]/0x00/12λCELL_OV_TH�ĸ�8λ����ѹ������ֵ��ѹ=COVT*1mV+500mV
  }R112;
  struct{
    u8 COVD:4;  //REGMODE03/R113[3:0]/0x00/CELL_OV_DLY[3:0], ��ع�ѹ����ӳٿ���λ;0000, 200ms;0001, 300ms;0010, 400ms;0011, 500ms;0100, 600ms;0101, 700ms;0110, 800ms;0111, 900ms;1000, 1s;1001, 2s;1010, 3s;1011, 4s;1100, 5s;1101, 6s;1110, 7s;1111, 8s
    u8 COVT_L:4;//REGMODE03/R113[7:4/0x00/12λCELL_OV_TH�ĵ�4λ
  }R113;
  struct{
    u8 CUVT_H;  //REGMODE03/R114[7:0]/0x00/12λ���Ƿѹ�����ֵ����λ�ĸ�8λ��Ƿѹ������ֵ��ѹ=CUVT*1mV
  }R114;
  struct{
    u8 CUVD:4;  //REGMODE03/R115[3:0]/0x00/CELL_UV_DLY[3:0], ���Ƿѹ����ӳٿ���λ;0000, 200ms;0001, 300ms;0010, 400ms;0011, 500ms;0100, 600ms;0101, 700ms;0110, 800ms;0111, 900ms;1000, 1s;1001, 2s;1010, 3s;1011, 4s;1100, 5s;1101, 6s;1110, 7s;1111, 8s
    u8 CUVT_L:4;//REGMODE03/R115[7:4]/0x00/12λ���Ƿѹ�����ֵ����λ�ĵ�4λ
  }R115;
  struct{
    u8 GP3M:3;  //REGMODE03/R116[2:0]/0x00/GP3_MODE[2:0], GP3ģʽ����λ;000�ر�;001��������������;010ģ���ѹ�������;011NA;100SCD_Q;101 OCD1_Q;110 INT;111 PCHG_LS
    u8 GP2M:3;  //REGMODE03/R116[5:3]/0x00/GP2_MODE[2:0], GP2ģʽ����λ;000�ر�;001��������������;010ģ���ѹ�������;011NA;100 HALF_CLK;101 PACK_DET;110 INT;111 PDSG_LS
    u8 GP1M:2;  //REGMODE03/R116[7:6]/0x00/GP1_MODE[1:0], GP1ģʽ����λ;00�ر�;01��������������;10ģ���ѹ�������;11 CON(CHG_OFF_N), CHG����Ӳ�߿��ƣ��͵�ƽ�ر�CHG����������ߵ�ƽ��Ӱ��CHG�������״̬
  }R116;

  struct{
    u8 GP6M:3; //REGMODE03/R117[2:0]/0x00/GP6_MODE[2:0], GP6ģʽ����λ;000�ر�;001��������������;010ģ���ѹ�������;011 NA;100 OCD2_Q;101, 0;110, INT;111, DSG_LS
    u8 GP5M:3; //REGMODE03/R117[5:3]/0x00/GP5_MODE[2:0], GP5ģʽ����λ;000�ر�;001��������������;010ģ���ѹ�������;011 NA;100 OCC1_Q;101, OCD2_Q;110, INT;111, CHG_LS
    u8 GP4M:2; //REGMODE03/R117[7:6]/0x00/GP4_MODE[1:0], GP4ģʽ����λ;00�ر�;01��������������;10ģ���ѹ�������;11, DON(DSG_OFF_N), DSG����Ӳ�߿��ƣ��͵�ƽ�ر�DSG����������ߵ�ƽ��Ӱ��DSG�������״̬
  }R117;
  struct{
    u8 COTT:7;  //REGMODE03/R118[6:0]/0x00/CORE_OVER_TEMP_TH[6:0], оƬ�ں˹��¼����ֵ����λ,;0, �ر�оƬ�ں˹��¼��;����, ��ֵ�¶�=(1466+COTT*2)*0.24467-271.03
    u8 COTF:1;  //REGMODE00/R118[7]/0x00/CORE_OVER_TEMP_FLAG, оƬ�ں˹��¹ػ���ʶλ;0, δ������оƬ�ں˹���;1, �ѷ�����оƬ�ں˹��£���bit���ڶ�ȡ���Զ���λΪ0
  }R118;
  struct{
    u8 IWT:3;   //REGMODE03/R119[2:0]/0x00/I2C_WATCHDOG_TIMER[2:0], I2C���Ź���ʱ������λ;0XX, �رն�ʱ��;100, ��ʱ����Ϊ4s;101, ��ʱ����Ϊ8s;110, ��ʱ����Ϊ16s;111, ��ʱ����Ϊ32s
    u8 IWTS:1;  //REGMODE00/R119[3]/0x00/I2C_WATCHDOG_TIMEOUT_STATE, I2C���Ź���ʱ״̬λ;0, δ��ʱ;1, �ѳ�ʱ
    u8 R119_RVD4:1;
    u8 V3P3M:1; //REGMODE03/R119[5]/0x00/V3P3_WDTO_MODE, I2C��ʱ����V3P3����λ;0, I2C��ʱ��Ӱ��V3P3���;1, I2C��ʱ��V3P3����ر�1s������
    u8 V3P3EW:1; //REGMODE03/R119[6]/0x01/V3P3_EN_WORKING, ����ģʽ��V3P3�������λ;0, �ر�V3P3���;1, ����V3P3���
    u8 V3P3ES:1; //REGMODE03/R119[7]/0x00/V3P3_EN_SLEEPING, ����ģʽ��V3P3�������λ;0, �ر�V3P3���;1, ����V3P3���
  }R119;
  struct{
    u8 TWSE:4; //REGMODE03/R120[3:0]/0x00/TIMED_WAKEUP_TIMER[3:0], ��ʱ���Ѷ�ʱ������λ;0000, �ر�;0001, 10s;0010, 20s;0011, 30s;0100, 40s;0101, 50s;0110, 1min;0111, 2min;1000, 3min;1001, 4min;1010, 5min;1011, 6min;1100, 7min;1101, 8min;1110, 9min;1111, 10min
    u8 R120_RVD:3;
    u8 TIWK:1; //REGMODE00/R120[7]/0x00/TIMED_WAKEUP_STATE, ��ʱ����״̬λ;0, �ر�;1, ����
  }R120;
  struct{
    u8 ISCM:1;  //REGMODE03/R121[0]/0x00/INT_SCD_MASK, �ŵ��·�ж�������ο���λ;0, �ŵ��·���ж�����͵�ƽ1ms;1, �ŵ��·���ж������
    u8 IOC2M:1; //REGMODE03/R121[1]/0x00/INT_OC2_MASK, 2������(����2���ŵ������2��������)�ж�������ο���λ;0, 2���������ж�����͵�ƽ1ms;1, 2���������ж������
    u8 IOC1M:1; //REGMODE03/R121[2]/0x00/INT_OC1_MASK, 1������(����1���ŵ������1��������)�ж�������ο���λ;0, 1���������ж�����͵�ƽ1ms;1, 1���������ж������
    u8 ICUM:1;  //REGMODE03/R121[3]/0x00/CUV_MASK, ���Ƿѹ�ж�������ο���λ;0, ���Ƿѹ���ж�����͵�ƽ1ms;1, ���Ƿѹ���ж������
    u8 ICOM:1;  //REGMODE03/R121[4]/0x00/INT_COV_MASK, ��ع�ѹ�ж�������ο���λ;0, ��ع�ѹ���ж�����͵�ƽ1ms;1, ��ع�ѹ���ж������
    u8 ICCM:1;  //REGMODE03/R121[5]/0x00/INT_CADC_CC2_MASK, CADC CC2ת�������ж�������ο���λ;0, CADC CC2ת���������ж�����͵�ƽ1ms;1, CADC CC2ת���������ж������
    u8 IVOM:1;  //REGMODE03/R121[6]/0x00/INT_VADC_OVER_MASK, VADCת�������ж�������ο���λ;0, VADCת���������ж�����͵�ƽ1ms;1, VADCת���������ж������
    u8 IWM:1;   //REGMODE03/R121[7]/0x00/INT_WKUP_MASK, �����ж�������ο���λ;0, оƬ���Ѻ��ж�����͵�ƽ1ms;1, оƬ���Ѻ��ж������
  }R121;
	u8 R122;
	u8 R123;
	u8 R124;
	u8 R125;
  struct{
	u8 F1RT; //REGMODE13/R126[7:0]/0x80/FUSE1_RES_TRIM[7:0], �洢��FUSE1�е����޵�ֵ;����ֵ=6800��+F1RT*25��
  }R126;
	u8 R127;
	u8 R128;
	u8 R129;
	u8 R130;
	u8 R131;
	u8 R132;
	u8 R133;
	u8 R134;
	u8 R135;
	u8 R136;
	u8 R137;
	u8 R138;
	u8 R139;
	u8 R140;
	u8 R141;
	u8 R142;
  struct{
		u8 CV;//REGMODE03/R143[7:0/0x00/CHIP_VERSION[7:0], оƬ�汾
	}R143;
	u8 R144;
}TAFERegs;
//---------------------------------------------------------------------------
#pragma pack (pop)
//�û��Զ����AFE��ʼ���Ĵ����������� ���ӼĴ���R81~R121)
static const unsigned char DVC11XX_PresetConfigRegData_R81To121[]={
  0x00,0x9e,0x50,0x78,0x2c,0xff,0x3f,0x05,0x40,       //R81-89
  0x40,0x18,0x18,0xb0,0x00,0x80,0x00,0x00,0x50,0x10,  //R90-99
  0x88,0x00,0x00,0x00,0x00,0x00,0xDB,0x6D,0xB0,0x68,  //R100-109
  0xcd,0x28,0xe7,0x48,0x5d,0xc8,0x00,0x00,0x00,0x40,  //R110-119
  0x00,0x00                            								//R120-121
};
static const unsigned char CellMask[]={
	0,1,2,3,6,9,12,15,18,21};
//------------------------------------------------------------------------------
void CleanError(void);
void Initial(void);
void DVC11XX_GPIO_Init(void);
void DVC11XX_ForceSleep(void);
bool DVC11XX_WriteRegs(u8 regAddr,u8 regLen);
bool DVC11XX_ReadRegs(u8 regAddr,u8 regLen);
//------------------------------------------------------------------------------
bool IIC_ReadDataWithCRC(u8 regAddr,void *dataPtr,u16 dataLen);
bool IIC_WriteDataWithCRC(u8 regAddr,void *dataPtr,u16 dataLen);
//------------------------------------------------------------------------------
void delay_init(void);
void delay_us(u16 us);
void delay_ms(u16 ms);
//------------------------------------------------------------------------------
extern u8 IIC_SLAVE_ADDRESS;
extern TAFERegs g_AfeRegs;
extern CleanFlag g_cleanflag;
//------------------------------------------------------------------------------
#endif
