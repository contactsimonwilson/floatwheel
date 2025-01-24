/******************************************************************************
;  *   	@MCU				 STM32F103C8T6
;  *   	@Create Date         2023.09.20
;  *    @Official website		 http://www.devechip.com/
;  *----------------------Abstract Description---------------------------------
;  *			          					系统初始化                              		
******************************************************************************/
#include "DVC11XX.h"
#include "iic1.h"
#if ADDRESS>=0xC0
#include "AddressChange.h"
#endif
//------------------------------------------------------------------------------

/**
	* @说明	AFE初始化配置写入
	* @参数	寄存器自定义参数默认值
	* @返回值	成功/失败
	* @注	
*/
static bool DVC11XX_InitRegs(void){
	memcpy((char *)&g_AfeRegs+81,DVC11XX_PresetConfigRegData_R81To121,sizeof(DVC11XX_PresetConfigRegData_R81To121));
	return DVC11XX_WriteRegs(AFE_ADDR_R(81),sizeof(DVC11XX_PresetConfigRegData_R81To121));
}
/**
	* @说明	清除所有警报
	* @参数	
	* @返回值	
	* @注	
*/
void CleanError(void){
g_AfeRegs.R0.cleanflag=0;
	while(!DVC11XX_WriteRegs(AFE_ADDR_R(0),1));
}
/**
	* @说明	GPIO初始化
	* @参数	
	* @返回值	
	* @注	
*/
//void DVC11XX_GPIO_Init(void){
//	//IO REMAP(Disable JTAG-DP and enable SW-DP)
//	//STM32有5个IO脚（PA13 PA14 PA15 PB3 PB4)上电时默认用作JTAG专用模式
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);//打开复用时钟
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //PB3,PB4,PA15用作GPIO,而PA13及PA14用作默认的SWD
//}
/**
	* @说明	AFE芯片重新初始化
	* @参数	
	* @返回值	成功/失败
	* @注	
*/
bool DVC11XX_InitRegs_Twice(void){

return DVC11XX_InitRegs();

}

/**
	* @说明	系统初始化
	* @参数	
	* @返回值	
	* @注	
*/
void Initial(void){
	
//    delay_ms(256);	//4. 延时256ms（确保AFE芯片至少完成一个周期的电压和电流值的测量）
	IIC_Wakeup();	//7.唤醒AFE芯片
	IIC1_Init();    //8. 初始化IIC通信接口(MCU跟AFE的通信接口）
#if ADDRESS>=0xC0
	GPIO_INTPUT();
#elif ADDRESS==0x40
	IIC_SLAVE_ADDRESS=ADDRESS>>1;
#endif	
	while(!DVC11XX_InitRegs());  //8. AFE芯片寄存器初始化（写入用户自定义的配置数据）
	CleanError();//写入默认值后清除警报
}
