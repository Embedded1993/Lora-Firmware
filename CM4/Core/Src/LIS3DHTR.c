#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "LIS3DHTR.h"

extern I2C_HandleTypeDef hi2c1;

/*
 * I2C write with address and data
 */
void i2c_write(I2C_HandleTypeDef * hi2c, char* config, int count)
{
	if (HAL_I2C_Master_Transmit(hi2c, LIS3DH_Write_Address_G, (uint8_t*)config, count, 1000) != HAL_OK)
		Error_Handler();
}

/*
 * I2C read with address and data
 */
int i2c_read(I2C_HandleTypeDef * hi2c, char* config, int count)
{
	if (HAL_I2C_Master_Receive(hi2c, (uint16_t)LIS3DH_Read_Address_G, (uint8_t*)config, count, 1000) != HAL_OK)
		return 0;

	return 1;
}

/*
 * Init LIS3DHTR sensor
 */
void init_LIS3DHTR()
{
	xAccl = 0;
	yAccl = 0;
	zAccl = 0;

	// Select control register1(0x20)
	// X, Y and Z axis enabled, power on mode, data rate o/p 5.376KHz(9F)
	char config[2] = {0};
	config[0] = LIS3DH_REG_CTRL1;
	config[1] = 0x9F;

	i2c_write(&hi2c1, config, 2);

	// Select control register4(0x23)
	// Full scale +/- 2g, continuous update, low power(0x00)
	config[0] = LIS3DH_REG_CTRL4;
	config[1] = 0x00;

	i2c_write(&hi2c1, config, 2);
	HAL_Delay(1);

	/* initialize for average matrix*/
	accel_index = 0;
	summation_x=0;
	summation_y=0;
	summation_z=0;
}

void getAccel()
{
	// Read 6 bytes of data
	// lsb first
	// Read xAccl lsb data from register(0x28)
	char data[1] = {0};
	char reg[1] = {LIS3DH_REG_OUT_X_L};
	i2c_write(&hi2c1, reg, 1);
	i2c_read(&hi2c1, data, 1);
	char data_0 = data[0];

	// Read xAccl msb data from register(0x29)
	reg[0] = LIS3DH_REG_OUT_X_H;
	i2c_write(&hi2c1, reg, 1);
	i2c_read(&hi2c1, data, 1);
	char data_1 = data[0];

	// Read yAccl lsb data from register(0x2A)
	reg[0] = LIS3DH_REG_OUT_Y_L;
	i2c_write(&hi2c1, reg, 1);
	i2c_read(&hi2c1, data, 1);
	char data_2 = data[0];

	// Read yAccl msb data from register(0x2B)
	reg[0] = LIS3DH_REG_OUT_Y_H;
	i2c_write(&hi2c1, reg, 1);
	i2c_read(&hi2c1, data, 1);
	char data_3 = data[0];

	// Read zAccl lsb data from register(0x2C)
	reg[0] = LIS3DH_REG_OUT_Z_L;
	i2c_write(&hi2c1, reg, 1);
	i2c_read(&hi2c1, data, 1);
	char data_4 = data[0];

	// Read zAccl msb data from register(0x2D)
	reg[0] = LIS3DH_REG_OUT_Z_H;
	i2c_write(&hi2c1, reg, 1);
	i2c_read(&hi2c1, data, 1);
	char data_5 = data[0];

	// Convert the data
	xAccl = (data_1 * 256 + data_0);
	if(xAccl > 32767)
	{
		xAccl -= 65536;
	}

	yAccl = (data_3 * 256 + data_2);
	if(yAccl > 32767)
	{
		yAccl -= 65536;
	}

	zAccl = (data_5 * 256 + data_4);
	if(zAccl > 32767)
	{
		zAccl -= 65536;
	}

	// Fill to matrix
	xAccelMatrix[accel_index] = xAccl;
	yAccelMatrix[accel_index] = yAccl;
	zAccelMatrix[accel_index] = zAccl;

	// sum for average
	summation_x += xAccl;
	summation_y += yAccl;
	summation_z += zAccl;

	/* if reaches end of matrix */
	if (accel_index >= SAMPLES_COUNT - 1)
	{
		/* average calculate */
		averange_acc[0]= (int16_t) (summation_x/SAMPLES_COUNT);
		averange_acc[1]= (int16_t) (summation_y/SAMPLES_COUNT);
		averange_acc[2]= (int16_t) (summation_z/SAMPLES_COUNT);

		summation_x=0;
		summation_y=0;
		summation_z=0;

		accel_index = 0;

		/* calculate fourier matrix */
		Calculo_accel_furier_x();
	}
	accel_index++;
}
