#include "stm32f10x.h"                  // Device header
#include "MyIIC.h"
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
	MyIIC_Start();
	MyIIC_SendByte(MPU6050_Address);//ָ���ӻ���ַ
	MyI2C_ReceiveAck();
	MyIIC_SendByte(RegAddress);//ָ���Ĵ�����ַд����
	MyI2C_ReceiveAck();
	MyIIC_SendByte(Data);//д����
	MyI2C_ReceiveAck();
	MyIIC_Stop();
	
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)//ָ����ַ��һ���ֽ�
{
	uint8_t Data;
	MyIIC_Start();
	MyIIC_SendByte(MPU6050_Address);//ָ���ӻ���ַ
	MyI2C_ReceiveAck();
	MyIIC_SendByte(RegAddress);//ָ���Ĵ�����ַ
	MyI2C_ReceiveAck();
	
	MyIIC_Start();//�ظ���ʼ
	MyIIC_SendByte(MPU6050_Address | 0x01);//ָ���ӻ���ַ������
	MyI2C_ReceiveAck();
	Data = MyI2C_ReceiveByte();
	MyIIC_SendAck(1);//�������ӻ�����Ӧ�𣬴ӻ����ټ���������
	MyIIC_Stop();
	
	return Data;
}
	
void MPU6050_Init(void)
{
	MyIIC_Init();
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


