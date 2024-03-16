#include "stm32f10x.h"                  // Device header

#include "MPU6050_Reg.h"


/*
多层模块架构：

上层：LCD显示数据
中层：MPU6050驱动层：配置及读写寄存器
底层：iic通信协议：引脚及配置

*/

#define MPU6050_Address 0xD0

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)//指定地址写一个字节
{
//	MyIIC_Start();
//	MyIIC_SendByte(MPU6050_Address);//指定从机地址
//	MyI2C_ReceiveAck();//应答
//	MyIIC_SendByte(RegAddress);//指定寄存器地址写数据
//	MyI2C_ReceiveAck();
//	MyIIC_SendByte(Data);//写数据
//	MyI2C_ReceiveAck();
//	MyIIC_Stop();
	
	I2C_GenerateSTART(I2C2, ENABLE);
	
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT) == ERROR);//非阻塞式程序要判断标志位
	
	I2C_Send7bitAddress(I2C2, MPU6050_Address, I2C_Direction_Transmitter);//发送从机地址（自带接受应答）
	
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR);
	
	I2C_SendData(I2C2, RegAddress);
	
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING) == ERROR);
	
	I2C_SendData(I2C2, Data);
	
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == ERROR);
	
	I2C_GenerateSTOP(I2C2, ENABLE);
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)//指定地址读一个字节
{
	uint8_t Data;
//	MyIIC_Start();
//	MyIIC_SendByte(MPU6050_Address);//指定从机地址
//	MyI2C_ReceiveAck();
//	MyIIC_SendByte(RedAddress);//指定寄存器地址
//	MyI2C_ReceiveAck();
//	
//	MyIIC_Start();//重复起始
//	MyIIC_SendByte(MPU6050_Address | 0x01);//指定从机地址读数据
//	MyI2C_ReceiveAck();
//	Data = MyI2C_ReceiveByte();
//	MyIIC_SendAck(1);//主机给从机发非应答，从机不再继续发数据
//	MyIIC_Stop();
	
	
	I2C_GenerateSTART(I2C2, ENABLE);
	
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT) == ERROR);//非阻塞式程序要判断标志位
	
	I2C_Send7bitAddress(I2C2, MPU6050_Address, I2C_Direction_Transmitter);//发送从机地址（自带接受应答）
	
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == ERROR);
	
	I2C_SendData(I2C2, RegAddress);
	
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED) == ERROR);
	
	I2C_GenerateSTART(I2C2, ENABLE);//重复起始 
	
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT) == ERROR);//非阻塞式程序要判断标志位
	
	I2C_Send7bitAddress(I2C2, MPU6050_Address, I2C_Direction_Receiver);//发送从机地址（自带接受应答）
	
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) == ERROR);
	
	I2C_AcknowledgeConfig(I2C2, DISABLE);//ACK置0 无应答
	
	I2C_GenerateSTOP(I2C2, ENABLE);//停止位
	
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED) == ERROR);

	Data = I2C_ReceiveData(I2C2);
	
	I2C_AcknowledgeConfig(I2C2, ENABLE);//ACK置1 默认状态
	
	return Data;
}
	
void MPU6050_Init(void)
{
//	MyIIC_Init();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;//复用开漏模式
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

//多返回值函数 （6个全局变量；指针实现变量地址传递；结构体）
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
	int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
	uint8_t DATAH, DATAL;
	
	DATAH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);//加速度计X轴高8位数据
	DATAL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);//加速度计X轴低8位数据
	*AccX = (DATAH << 8) | DATAL;//加速度计X轴的16位数据
	
	DATAH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DATAL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY = (DATAH << 8) | DATAL;
	
	DATAH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DATAL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ = (DATAH << 8) | DATAL;
	
	DATAH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);//陀螺仪X轴高8位数据
	DATAL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);//陀螺仪X轴低8位数据
	*GyroX = (DATAH << 8) | DATAL;//陀螺仪X轴16位数据
	
	DATAH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DATAL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY = (DATAH << 8) | DATAL;
	
	DATAH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DATAL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*GyroZ = (DATAH << 8) | DATAL;
}


