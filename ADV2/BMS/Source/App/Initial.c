/******************************************************************************
;  *   	@MCU				 STM32F103C8T6
;  *   	@Create Date         2023.09.20
;  *    @Official website		 http://www.devechip.com/
;  *----------------------Abstract Description---------------------------------
;  * 	System initialization	[ϵͳ��ʼ��]
******************************************************************************/
#include "DVC11XX.h"
#include "iic1.h"
#if ADDRESS>=0xC0
#include "AddressChange.h"
#endif
//------------------------------------------------------------------------------

/**
	* @Description AFE initialization configuration writing 	[˵��	AFE��ʼ������д��]
	* @Parameter Register custom parameter default value 		[����	�Ĵ����Զ������Ĭ��ֵ]
	* @Return value success/failure 							[����ֵ	�ɹ�/ʧ��]
	* @Note 													[ע]
*/
static bool DVC11XX_InitRegs(void){
	memcpy((char *)&g_AfeRegs+81,DVC11XX_PresetConfigRegData_R81To121,sizeof(DVC11XX_PresetConfigRegData_R81To121));
	return DVC11XX_WriteRegs(AFE_ADDR_R(81),sizeof(DVC11XX_PresetConfigRegData_R81To121));
}
/**
	* @Description Clear all alerts 	[˵��	������о���]
	* @Parameter						[����]
	* @Return value						[����ֵ]
	* @Note								[ע]
*/
void CleanError(void){
g_AfeRegs.R0.cleanflag=0;
	while(!DVC11XX_WriteRegs(AFE_ADDR_R(0),1));
}
/**
	* @Description GPIO initialization	[˵��	GPIO��ʼ��]
	* @Parameter 						[����]
	* @Return value						[����ֵ]
	* @Note								[ע]
*/
//void DVC11XX_GPIO_Init(void){
//	//IO REMAP(Disable JTAG-DP and enable SW-DP)
//	//STM32��5��IO�ţ�PA13 PA14 PA15 PB3 PB4)�ϵ�ʱĬ������JTAGר��ģʽ
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);//�򿪸���ʱ��
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //PB3,PB4,PA15����GPIO,��PA13��PA14����Ĭ�ϵ�SWD
//}
/**
	* @Description AFE chip reinitialization	[˵��	AFEоƬ���³�ʼ��]
	* @Parameter 								[����]
	* @Return value success/failure				[����ֵ	�ɹ�/ʧ��]
	* @Note										[ע]
*/
bool DVC11XX_InitRegs_Twice(void){

return DVC11XX_InitRegs();

}

/**
	* @Description System initialization	[˵��	ϵͳ��ʼ��]
	* @Parameter 							[����]
	* @Return value							[����ֵ]
	* @Note									[ע]
*/
void Initial(void){
	
//    delay_ms(256);	//4. Delay 256ms (make sure the AFE chip completes at least one cycle of voltage and current measurement) [4. ��ʱ256ms��ȷ��AFEоƬ�������һ�����ڵĵ�ѹ�͵���ֵ�Ĳ���]
	IIC_Wakeup();		//7. Wake up the AFE chip [7.����AFEоƬ]
	IIC1_Init();    	//8. Initialize the IIC communication interface (communication interface between MCU and AFE) [8. ��ʼ��IICͨ�Žӿ�(MCU��AFE��ͨ�Žӿڣ�]
#if ADDRESS>=0xC0
	GPIO_INTPUT();
#elif ADDRESS==0x40
	IIC_SLAVE_ADDRESS=ADDRESS>>1;
#endif	
	while(!DVC11XX_InitRegs());		//8. AFE chip register initialization (writing user-defined configuration data)   [8. AFEоƬ�Ĵ�����ʼ����д���û��Զ������������]
	CleanError();	//Clear alert after writing default value [д��Ĭ��ֵ���������]
}
