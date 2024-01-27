#include "vesc_uasrt.h"

uint8_t VESC_RX_Buff[256];
uint8_t VESC_RX_Flag = 0;

dataPackage data;

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
	uint8_t command[1];
	
	command[0] = id;
	
	Send_Pack_Data(command,1);
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

			data.tempFET            = buffer_get_float16(pdata, 10.0, &ind);
			data.tempMotor          = buffer_get_float16(pdata, 10.0, &ind);
			data.avgMotorCurrent 	= buffer_get_float32(pdata, 100.0, &ind);
			data.avgInputCurrent 	= buffer_get_float32(pdata, 100.0, &ind);
			ind += 8; // 跳过8个字节
			data.dutyCycleNow 		= buffer_get_float16(pdata, 1000.0, &ind);
			data.rpm 				= buffer_get_int32(pdata, &ind);
			data.inpVoltage 		= buffer_get_float16(pdata, 10.0, &ind);
			data.ampHours 			= buffer_get_float32(pdata, 10000.0, &ind);
			data.ampHoursCharged 	= buffer_get_float32(pdata, 10000.0, &ind);
			ind += 8; // 跳过8个字节
			data.tachometer 		= buffer_get_int32(pdata, &ind);
			data.tachometerAbs 		= buffer_get_int32(pdata, &ind);

		break;
	}
	
	return 0;
}

