#include "stm32f10x.h"                  // Device header

#include "MPU6050_Reg.h"


/*
���ģ��ܹ���

�ϲ㣺LCD��ʾ����
�в㣺MPU6050�����㣺���ü���д�Ĵ���
�ײ㣺iicͨ��Э�飺���ż�����

*/
#define MPU6050_Address 0xD0

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)//ָ����ַдһ���ֽ�
{
//	MyIIC_Start();
//	MyIIC_SendByte(MPU6050_Address);//ָ���ӻ���ַ
//	MyI2C_ReceiveAck();//Ӧ��
//	MyIIC_SendByte(RegAddress);//ָ���Ĵ�����ַд����
//	MyI2C_ReceiveAck();
//	MyIIC_SendByte(Data);//д����
//	MyI2C_ReceiveAck();
//	MyIIC_Stop();
	
	I2C_GenerateSTART(I2C2, ENABLE);
	
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT) == ERROR);//������ʽ����Ҫ�жϱ�־λ
	
	I2C_Send7bitAddress(I2C2, MPU6050_Address, I2C_Direction_Transmitter);//���ʹӻ���ַ���Դ�����Ӧ��
	
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR);
	
	I2C_SendData(I2C2, RegAddress);
	
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING) == ERROR);
	
	I2C_SendData(I2C2, Data);
	
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == ERROR);
	
	I2C_GenerateSTOP(I2C2, ENABLE);
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)//ָ����ַ��һ���ֽ�
{
	uint8_t Data;
//	MyIIC_Start();
//	MyIIC_SendByte(MPU6050_Address);//ָ���ӻ���ַ
//	MyI2C_ReceiveAck();
//	MyIIC_SendByte(RedAddress);//ָ���Ĵ�����ַ
//	MyI2C_ReceiveAck();
//	
//	MyIIC_Start();//�ظ���ʼ
//	MyIIC_SendByte(MPU6050_Address | 0x01);//ָ���ӻ���ַ������
//	MyI2C_ReceiveAck();
//	Data = MyI2C_ReceiveByte();
//	MyIIC_SendAck(1);//�������ӻ�����Ӧ�𣬴ӻ����ټ���������
//	MyIIC_Stop();
	
	
	I2C_GenerateSTART(I2C2, ENABLE);
	
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT) == ERROR);//������ʽ����Ҫ�жϱ�־λ
	
	I2C_Send7bitAddress(I2C2, MPU6050_Address, I2C_Direction_Transmitter);//���ʹӻ���ַ���Դ�����Ӧ��
	
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR);
	
	I2C_SendData(I2C2, RegAddress);
	
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == ERROR);
	
	I2C_GenerateSTART(I2C2, ENABLE);//�ظ���ʼ 
	
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT) == ERROR);//������ʽ����Ҫ�жϱ�־λ
	
	I2C_Send7bitAddress(I2C2, MPU6050_Address, I2C_Direction_Receiver);//���ʹӻ���ַ���Դ�����Ӧ��
	
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) == ERROR);
	
	I2C_AcknowledgeConfig(I2C2, DISABLE);//ACK��0 ��Ӧ��
	
	I2C_GenerateSTOP(I2C2, ENABLE);//ֹͣλ
	
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED) == ERROR);

	Data = I2C_ReceiveData(I2C2);
	
	I2C_AcknowledgeConfig(I2C2, ENABLE);//ACK��1 Ĭ��״̬
	
	return Data;
}
	
void MPU6050_Init(void)
{
//	MyIIC_Init();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Pin = GPIO_Mode_AF_OD;//���ÿ�©ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	I2C_InitTypeDef I2C_InitStructure;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 100000;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;
	I2C_Init(I2C2, &I2C_InitStructure);
	
	I2C_Cmd(I2C2, ENABLE);
	
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01); 
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);
	
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);
}

//�෵��ֵ���� ��6��ȫ�ֱ�����ָ��ʵ�ֱ�����ַ���ݣ��ṹ�壩
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
	int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
	uint8_t DATAH, DATAL;
	
	DATAH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);//���ٶȼ�X���8λ����
	DATAL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);//���ٶȼ�X���8λ����
	*AccX = (DATAH << 8) | DATAL;//���ٶȼ�X���16λ����
	
	DATAH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DATAL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY = (DATAH << 8) | DATAL;
	
	DATAH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DATAL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ = (DATAH << 8) | DATAL;
	
	DATAH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);//������X���8λ����
	DATAL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);//������X���8λ����
	*GyroX = (DATAH << 8) | DATAL;//������X��16λ����
	
	DATAH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DATAL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY = (DATAH << 8) | DATAL;
	
	DATAH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DATAL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*GyroZ = (DATAH << 8) | DATAL;
}


