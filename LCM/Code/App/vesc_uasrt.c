#include "vesc_uasrt.h"
#include "flag_bit.h"

uint8_t VESC_RX_Buff[256];
uint8_t VESC_RX_Flag = 0;

// Access ADC values here to determine riding state
extern float ADC1_Val, ADC2_Val;

dataPackage data;
lcmConfig_t lcmConfig;
uint8_t errCode = 0;

uint8_t protocol_buff[256]; //发送缓冲区
/**************************************************
 * @brie   :Send_Pack_Data()
 * @note   :发送一包数据
 * @param  :payload 要发送数据包的起始地址
 *          len 数据包长度
 * @retval :无
 **************************************************/
void Send_Pack_Data(uint8_t *payload,uint16_t len) 
{
//	uint8_t protocol_buff[256]; //发送缓冲区
	uint8_t count = 0;
	uint16_t crcpayload = crc16(payload, len);  //计算校验 
	
	/*
		协议格式
	
		起始字节（一个字节） + 数据包长度（一个或两个字节） + 数据包（N个字节） + 校验（两个字节） + 停止字节（一个字节）
	
		起始字节:	0x02数据包长度1-256个字节
					0x03数据包长度超过256个字节
	
		数据包长度: 起始字节0x02 数据包占一个字节
	                起始字节0x03 数据包占两个字节
	
		数据包:  	数据包第一个字节为数据包ID
	
		校验:		CRC校验 两个字节 
	    
		停止字节:   固定0x03
	
	*/
	
	if (len <= 256) //数据包长度不大于256个字节
	{
		protocol_buff[count++] = 2;
		protocol_buff[count++] = len;
	}
	else //数据包长度大于256个字节
	{
		protocol_buff[count++] = 3;
		protocol_buff[count++] = (uint8_t)(len >> 8);
		protocol_buff[count++] = (uint8_t)(len & 0xFF);
	}

	memcpy(&protocol_buff[count], payload, len);  //把数据包复制到协议里

	count += len;
	protocol_buff[count++] = (uint8_t)(crcpayload >> 8);
	protocol_buff[count++] = (uint8_t)(crcpayload & 0xFF);
	protocol_buff[count++] = 3;
	
	USART1_Send_Bytes(protocol_buff,count);
}

/**************************************************
 * @brie   :Get_Vesc_Pack_Data()
 * @note   :获取一包数据
 * @param  :id 数据包id
 * @retval :无
 **************************************************/
void Get_Vesc_Pack_Data(COMM_PACKET_ID id)
{
	uint8_t command[12];
	int len = 1;
	
	command[0] = id;
	
	if (id == COMM_CUSTOM_APP_DATA) {
		command[1] = 101;
		command[2] = 24; // FLOAT_COMMAND_POLL
		len = 3;
	}
	
	if (id == COMM_CUSTOM_DEBUG) {
		command[0] = COMM_CUSTOM_APP_DATA;
		command[1] = 101;
		command[2] = 28; // FLOAT_COMMAND_LCM_DEBUG
		command[3] = Power_Flag;
		command[4] = Charge_Flag;
		command[5] = Buzzer_Flag;
		command[6] = WS2812_Display_Flag;
		command[7] = WS2812_Flag;
		command[8] = Gear_Position;
		command[9] = errCode;
		len = 10;
	}
	
	Send_Pack_Data(command, len);
}

/**************************************************
 * @brie   :buffer_get_int16()
 * @note   :缓冲区两个字节拼一个int16_t
 * @param  :buffer地址  index地址偏移
 * @retval :无
 **************************************************/
int16_t buffer_get_int16(const uint8_t *buffer, int32_t *index) {
	int16_t res =	((uint16_t) buffer[*index]) << 8 |
					((uint16_t) buffer[*index + 1]);
	*index += 2;
	return res;
}
/**************************************************
 * @brie   :buffer_get_uint16()
 * @note   :缓冲区两个字节拼一个uint16_t
 * @param  :buffer地址  index地址偏移
 * @retval :无
 **************************************************/
uint16_t buffer_get_uint16(const uint8_t *buffer, int32_t *index) {
	uint16_t res = 	((uint16_t) buffer[*index]) << 8 |
					((uint16_t) buffer[*index + 1]);
	*index += 2;
	return res;
}
/**************************************************
 * @brie   :buffer_get_int32()
 * @note   :缓冲区四个字节拼一个int32_t
 * @param  :buffer地址  index地址偏移
 * @retval :无
 **************************************************/
int32_t buffer_get_int32(const uint8_t *buffer, int32_t *index) {
	int32_t res =	((uint32_t) buffer[*index]) << 24 |
					((uint32_t) buffer[*index + 1]) << 16 |
					((uint32_t) buffer[*index + 2]) << 8 |
					((uint32_t) buffer[*index + 3]);
	*index += 4;
	return res;
}
/**************************************************
 * @brie   :buffer_get_uint32()
 * @note   :缓冲区四个字节拼一个uint32_t
 * @param  :buffer地址  index地址偏移
 * @retval :无
 **************************************************/
uint32_t buffer_get_uint32(const uint8_t *buffer, int32_t *index) {
	uint32_t res =	((uint32_t) buffer[*index]) << 24 |
					((uint32_t) buffer[*index + 1]) << 16 |
					((uint32_t) buffer[*index + 2]) << 8 |
					((uint32_t) buffer[*index + 3]);
	*index += 4;
	return res;
}
/**************************************************
 * @brie   :buffer_get_float16()
 * @note   :缓冲区两个字节拼一个float
 * @param  :buffer地址  index地址偏移  scale分母
 * @retval :无
 **************************************************/
float buffer_get_float16(const uint8_t *buffer, float scale, int32_t *index) {
    return (float)buffer_get_int16(buffer, index) / scale;
}
/**************************************************
 * @brie   :buffer_get_float32()
 * @note   :缓冲区四个字节拼一个float
 * @param  :buffer地址  index地址偏移	scale分母
 * @retval :无
 **************************************************/
float buffer_get_float32(const uint8_t *buffer, float scale, int32_t *index) {
    return (float)buffer_get_int32(buffer, index) / scale;
}

/**************************************************
 * @brie   :Protocol_Parse()
 * @note   :协议解析
 * @param  :message 接收到数据的起始地址
 * @retval :0 解析成功 1解析失败
 **************************************************/
uint8_t Protocol_Parse(uint8_t * message)
{
	uint8_t  start = 0;
	uint8_t *pdata;
	uint16_t counter = 0;
	uint16_t len = 0; 
	uint16_t crcpayload;
	uint8_t id;
	int32_t ind = 0;
	
	start = message[counter++];
	
	switch(start)
	{
		case 0x02:
			len = message[counter++];
		break;
		
		case 0x03:
			
		break;
		
	}
	
	crcpayload = crc16(&message[counter], len);
	
	if(crcpayload != (((uint16_t)message[counter+len])<<8|
		             ((uint16_t)message[counter+len+1])))
	{
		return 1; //crc不对
	}
	
	id = message[counter++];
	pdata = &message[counter];  
	
	switch(id)
	{
		case COMM_GET_VALUES: 

			ind += 8;
			data.avgInputCurrent 	= buffer_get_float32(pdata, 100.0, &ind); // negative input current implies braking
			ind += 8; // Skip id/iq currents
			data.dutyCycleNow 		= buffer_get_float16(pdata, 10.0, &ind);	// duty as value 0..100
			data.rpm 				= buffer_get_int32(pdata, &ind);
			data.inpVoltage 		= buffer_get_float16(pdata, 10.0, &ind);

			if ((data.rpm > 100) || (data.rpm < -100) || (data.avgInputCurrent > 1) || (data.avgInputCurrent < -1)) {
				data.state = RUNNING;
			}
			else {
				// Use this fault as a placeholder (we only care that the board is stopped anyways)
				data.state = FAULT_STARTUP;
			}
		
		break;
		
		case COMM_CUSTOM_APP_DATA:

		  if (len < 12) {
				break;
			}
		  uint8_t magicnr = pdata[ind++];
		  uint8_t floatcmd = pdata[ind++];
		  if ((magicnr != 101) || (floatcmd != FLOAT_COMMAND_LCM_POLL)) {
				break;
			}
			data.floatPackageSupported = true;
			uint8_t state = pdata[ind++];
			data.state = state & 0xF;
			//data.switchstate = (state >> 4) & 0x7;
			data.isHandtest = (state & 0x80) > 0;
			data.fault = pdata[ind++];
			data.dutyCycleNow = pdata[ind++];
			data.rpm = buffer_get_float16(pdata, 1.0, &ind);
			data.avgInputCurrent = buffer_get_float16(pdata, 1.0, &ind);
			data.inpVoltage = buffer_get_float16(pdata, 10.0, &ind);

			uint8_t lcmset = pdata[ind++];
			if ((lcmset > 0) && (len >= 17)) {
				// Float package is 0-100 range. Adjust as needed
				uint8_t headlightBrightness = pdata[ind++] * 255/100;
				uint8_t headlightIdleBrightness = pdata[ind++] * 255/100;
				uint8_t statusbarBrightness = pdata[ind++] * 255/100;
				uint8_t statusbarMode = pdata[ind++];
				uint8_t dutyBeep = pdata[ind++];
				uint8_t boardOff = pdata[ind++];

				// Only set isSet if something changed
				// Allows use of the power button to go back to default behaviour
				if (headlightBrightness != lcmConfig.headlightBrightness || headlightIdleBrightness != lcmConfig.headlightIdleBrightness || statusbarBrightness != lcmConfig.statusbarBrightness || statusbarMode != lcmConfig.statusbarMode || dutyBeep != lcmConfig.dutyBeep || boardOff != lcmConfig.boardOff) {
					lcmConfig.isSet = true;
				}

				lcmConfig.headlightBrightness = headlightBrightness;
				lcmConfig.headlightIdleBrightness = headlightIdleBrightness;
				lcmConfig.statusbarBrightness = statusbarBrightness;
				lcmConfig.statusbarMode = statusbarMode;
				lcmConfig.dutyBeep = dutyBeep;
				lcmConfig.boardOff = boardOff;
			}
	}
	if (data.rpm > 500)
		data.isForward = data.state != RUNNING_UPSIDEDOWN;
	if (data.rpm < -500)
		data.isForward = data.state == RUNNING_UPSIDEDOWN;

	return 0;
}

