/*
 * fourier.c
 *
 *  Created on: Feb 1, 2022
 *      Author: Developer
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "arm_math.h"
#include "arm_const_structs.h"

#include "global.h"

void Calculo_accel_furier_x(void)
{
	float fft_inputbuf[SAMPLES_COUNT * 2];
	float fft_outputbuf[SAMPLES_COUNT];
	for(int i=0;i < SAMPLES_COUNT;i++)
	{
		fft_inputbuf[i*2] = xAccelMatrix[i];
		fft_inputbuf[2*i +1] = 0;
	}

	arm_cfft_f32 (&arm_cfft_sR_f32_len4096, fft_inputbuf, 0, 1); // Execute FFT transformation, ARM_CFFT_SR_F32_LEN4096 is macro, define rotary factors
	arm_cmplx_mag_f32 (fft_inputbuf, fft_outputbuf, SAMPLES_COUNT); // Multiplexes the calculation result
}
void Calculo_accel_furier_y(void)
{
	float fft_inputbuf[SAMPLES_COUNT * 2];
	float fft_outputbuf[SAMPLES_COUNT];
	for(int i=0;i < SAMPLES_COUNT;i++)
	{
		fft_inputbuf[i*2] = yAccelMatrix[i];
		fft_inputbuf[2*i +1] = 0;
	}

	arm_cfft_f32 (&arm_cfft_sR_f32_len4096, fft_inputbuf, 0, 1); // Execute FFT transformation, ARM_CFFT_SR_F32_LEN4096 is macro, define rotary factors
	arm_cmplx_mag_f32 (fft_inputbuf, fft_outputbuf, SAMPLES_COUNT); // Multiplexes the calculation result
}
void Calculo_accel_furier_z(void)
{
	float fft_inputbuf[SAMPLES_COUNT * 2];
	float fft_outputbuf[SAMPLES_COUNT];
	for(int i=0;i < SAMPLES_COUNT;i++)
	{
		fft_inputbuf[i*2] = zAccelMatrix[i];
		fft_inputbuf[2*i +1] = 0;
	}

	arm_cfft_f32 (&arm_cfft_sR_f32_len4096, fft_inputbuf, 0, 1); // Execute FFT transformation, ARM_CFFT_SR_F32_LEN4096 is macro, define rotary factors
	arm_cmplx_mag_f32 (fft_inputbuf, fft_outputbuf, SAMPLES_COUNT); // Multiplexes the calculation result
}
