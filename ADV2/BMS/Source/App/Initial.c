/******************************************************************************
;  *   	@MCU				 STM32F103C8T6
;  *   	@Create Date         2023.09.20
;  *    @Official website		 http://www.devechip.com/
;  *----------------------Abstract Description---------------------------------
;  * 	System initialization	[系统初始化]
******************************************************************************/
#include "DVC11XX.h"
#include "iic1.h"
#if ADDRESS>=0xC0
#include "AddressChange.h"
#endif
//------------------------------------------------------------------------------

/**
	* @Description AFE initialization configuration writing 	[说明	AFE初始化配置写入]
	* @Parameter Register custom parameter default value 		[参数	寄存器自定义参数默认值]
	* @Return value success/failure 							[返回值	成功/失败]
	* @Note 													[注]
*/
static bool DVC11XX_InitRegs(void){
	memcpy((char *)&g_AfeRegs+81,DVC11XX_PresetConfigRegData_R81To121,sizeof(DVC11XX_PresetConfigRegData_R81To121));
	return DVC11XX_WriteRegs(AFE_ADDR_R(81),sizeof(DVC11XX_PresetConfigRegData_R81To121));
}
/**
	* @Description Clear all alerts 	[说明	清除所有警报]
	* @Parameter						[参数]
	* @Return value						[返回值]
	* @Note								[注]
*/
void CleanError(void){
g_AfeRegs.R0.cleanflag=0;
	while(!DVC11XX_WriteRegs(AFE_ADDR_R(0),1));
}
/**
	* @Description GPIO initialization	[说明	GPIO初始化]
	* @Parameter 						[参数]
	* @Return value						[返回值]
	* @Note								[注]
*/
//void DVC11XX_GPIO_Init(void){
//	//IO REMAP(Disable JTAG-DP and enable SW-DP)
//	//STM32有5个IO脚（PA13 PA14 PA15 PB3 PB4)上电时默认用作JTAG专用模式
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);//打开复用时钟
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //PB3,PB4,PA15用作GPIO,而PA13及PA14用作默认的SWD
//}
/**
	* @Description AFE chip reinitialization	[说明	AFE芯片重新初始化]
	* @Parameter 								[参数]
	* @Return value success/failure				[返回值	成功/失败]
	* @Note										[注]
*/
bool DVC11XX_InitRegs_Twice(void){

return DVC11XX_InitRegs();

}

/**
	* @Description System initialization	[说明	系统初始化]
	* @Parameter 							[参数]
	* @Return value							[返回值]
	* @Note									[注]
*/
void Initial(void){
	
//    delay_ms(256);	//4. Delay 256ms (make sure the AFE chip completes at least one cycle of voltage and current measurement) [4. 延时256ms（确保AFE芯片至少完成一个周期的电压和电流值的测量]
	IIC_Wakeup();		//7. Wake up the AFE chip [7.唤醒AFE芯片]
	IIC1_Init();    	//8. Initialize the IIC communication interface (communication interface between MCU and AFE) [8. 初始化IIC通信接口(MCU跟AFE的通信接口）]
#if ADDRESS>=0xC0
	GPIO_INTPUT();
#elif ADDRESS==0x40
	IIC_SLAVE_ADDRESS=ADDRESS>>1;
#endif	
	while(!DVC11XX_InitRegs());		//8. AFE chip register initialization (writing user-defined configuration data)   [8. AFE芯片寄存器初始化（写入用户自定义的配置数据]
	CleanError();	//Clear alert after writing default value [写入默认值后清除警报]
}
