/*
 * global.h
 *
 *  Created on: Feb 2, 2022
 *      Author: Developer
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#define SAMPLES_COUNT				4096
#define SOUND_SAMPLES_COUNT			1024

// Accelometer
int xAccl, yAccl, zAccl;

int16_t xAccelMatrix[SAMPLES_COUNT];
int16_t yAccelMatrix[SAMPLES_COUNT];
int16_t zAccelMatrix[SAMPLES_COUNT];
int16_t soundMatrix[SOUND_SAMPLES_COUNT];

int32_t summation_x,summation_y,summation_z;
int16_t	averange_acc[3];
int accel_index;


void Calculo_accel_furier_x(void);
void Calculo_accel_furier_y(void);
void Calculo_accel_furier_z(void);

#endif /* INC_GLOBAL_H_ */
