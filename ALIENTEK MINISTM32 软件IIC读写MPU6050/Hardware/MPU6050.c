#include "stm32f10x.h"                  // Device header
#include "MyIIC.h"
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
	MyIIC_Start();
	MyIIC_SendByte(MPU6050_Address);//指定从机地址
	MyI2C_ReceiveAck();
	MyIIC_SendByte(RegAddress);//指定寄存器地址写数据
	MyI2C_ReceiveAck();
	MyIIC_SendByte(Data);//写数据
	MyI2C_ReceiveAck();
	MyIIC_Stop();
	
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)//指定地址读一个字节
{
	uint8_t Data;
	MyIIC_Start();
	MyIIC_SendByte(MPU6050_Address);//指定从机地址
	MyI2C_ReceiveAck();
	MyIIC_SendByte(RegAddress);//指定寄存器地址
	MyI2C_ReceiveAck();
	
	MyIIC_Start();//重复起始
	MyIIC_SendByte(MPU6050_Address | 0x01);//指定从机地址读数据
	MyI2C_ReceiveAck();
	Data = MyI2C_ReceiveByte();
	MyIIC_SendAck(1);//主机给从机发非应答，从机不再继续发数据
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


