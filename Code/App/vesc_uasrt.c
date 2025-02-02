#include "vesc_uasrt.h"

uint8_t VESC_RX_Buff[256];
uint8_t VESC_RX_Flag = 0;

dataPackage data;

uint8_t protocol_buff[256]; //���ͻ�����
/**************************************************
 * @brie   :Send_Pack_Data()
 * @note   :����һ������
 * @param  :payload Ҫ�������ݰ�����ʼ��ַ
 *          len ���ݰ�����
 * @retval :��
 **************************************************/
void Send_Pack_Data(uint8_t *payload,uint16_t len) 
{
//	uint8_t protocol_buff[256]; //���ͻ�����
	uint8_t count = 0;
	uint16_t crcpayload = crc16(payload, len);  //����У�� 
	
	/*
		Э���ʽ
	
		��ʼ�ֽڣ�һ���ֽڣ� + ���ݰ����ȣ�һ���������ֽڣ� + ���ݰ���N���ֽڣ� + У�飨�����ֽڣ� + ֹͣ�ֽڣ�һ���ֽڣ�
	
		��ʼ�ֽ�:	0x02���ݰ�����1-256���ֽ�
					0x03���ݰ����ȳ���256���ֽ�
	
		���ݰ�����: ��ʼ�ֽ�0x02 ���ݰ�ռһ���ֽ�
	                ��ʼ�ֽ�0x03 ���ݰ�ռ�����ֽ�
	
		���ݰ�:  	���ݰ���һ���ֽ�Ϊ���ݰ�ID
	
		У��:		CRCУ�� �����ֽ� 
	    
		ֹͣ�ֽ�:   �̶�0x03
	
	*/
	
	if (len <= 256) //���ݰ����Ȳ�����256���ֽ�
	{
		protocol_buff[count++] = 2;
		protocol_buff[count++] = len;
	}
	else //���ݰ����ȴ���256���ֽ�
	{
		protocol_buff[count++] = 3;
		protocol_buff[count++] = (uint8_t)(len >> 8);
		protocol_buff[count++] = (uint8_t)(len & 0xFF);
	}

	memcpy(&protocol_buff[count], payload, len);  //�����ݰ����Ƶ�Э����

	count += len;
	protocol_buff[count++] = (uint8_t)(crcpayload >> 8);
	protocol_buff[count++] = (uint8_t)(crcpayload & 0xFF);
	protocol_buff[count++] = 3;
	
	USART1_Send_Bytes(protocol_buff,count);
}

/**************************************************
 * @brie   :Get_Vesc_Pack_Data()
 * @note   :��ȡһ������
 * @param  :id ���ݰ�id
 * @retval :��
 **************************************************/
void Get_Vesc_Pack_Data(COMM_PACKET_ID id)
{
	uint8_t command[1];
	
	command[0] = id;
	
	Send_Pack_Data(command,1);
}

/**************************************************
 * @brie   :buffer_get_int16()
 * @note   :�����������ֽ�ƴһ��int16_t
 * @param  :buffer��ַ  index��ַƫ��
 * @retval :��
 **************************************************/
int16_t buffer_get_int16(const uint8_t *buffer, int32_t *index) {
	int16_t res =	((uint16_t) buffer[*index]) << 8 |
					((uint16_t) buffer[*index + 1]);
	*index += 2;
	return res;
}
/**************************************************
 * @brie   :buffer_get_uint16()
 * @note   :�����������ֽ�ƴһ��uint16_t
 * @param  :buffer��ַ  index��ַƫ��
 * @retval :��
 **************************************************/
uint16_t buffer_get_uint16(const uint8_t *buffer, int32_t *index) {
	uint16_t res = 	((uint16_t) buffer[*index]) << 8 |
					((uint16_t) buffer[*index + 1]);
	*index += 2;
	return res;
}
/**************************************************
 * @brie   :buffer_get_int32()
 * @note   :�������ĸ��ֽ�ƴһ��int32_t
 * @param  :buffer��ַ  index��ַƫ��
 * @retval :��
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
 * @note   :�������ĸ��ֽ�ƴһ��uint32_t
 * @param  :buffer��ַ  index��ַƫ��
 * @retval :��
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
 * @note   :�����������ֽ�ƴһ��float
 * @param  :buffer��ַ  index��ַƫ��  scale��ĸ
 * @retval :��
 **************************************************/
float buffer_get_float16(const uint8_t *buffer, float scale, int32_t *index) {
    return (float)buffer_get_int16(buffer, index) / scale;
}
/**************************************************
 * @brie   :buffer_get_float32()
 * @note   :�������ĸ��ֽ�ƴһ��float
 * @param  :buffer��ַ  index��ַƫ��	scale��ĸ
 * @retval :��
 **************************************************/
float buffer_get_float32(const uint8_t *buffer, float scale, int32_t *index) {
    return (float)buffer_get_int32(buffer, index) / scale;
}

/**************************************************
 * @brie   :Protocol_Parse()
 * @note   :Э�����
 * @param  :message ���յ����ݵ���ʼ��ַ
 * @retval :0 �����ɹ� 1����ʧ��
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
		return 1; //crc����
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
			ind += 8; // ����8���ֽ�
			data.dutyCycleNow 		= buffer_get_float16(pdata, 1000.0, &ind);
			data.rpm 				= buffer_get_int32(pdata, &ind);
			data.inpVoltage 		= buffer_get_float16(pdata, 10.0, &ind);
			data.ampHours 			= buffer_get_float32(pdata, 10000.0, &ind);
			data.ampHoursCharged 	= buffer_get_float32(pdata, 10000.0, &ind);
			ind += 8; // ����8���ֽ�
			data.tachometer 		= buffer_get_int32(pdata, &ind);
			data.tachometerAbs 		= buffer_get_int32(pdata, &ind);

		break;
	}
	
	return 0;
}

