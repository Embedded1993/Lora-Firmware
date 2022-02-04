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

arm_rfft_instance_q15   RealFFT_Instance;
int16_t FFT_Real[3][SAMPLES_COUNT];
int16_t	FFT_Complex[3][SAMPLES_COUNT * 2];

/*
 * Calculate sound matrix's fourier
 */
void Calculo_sound_furier(void)
{
	/*arm_rfft_init_q15(&RealFFT_Instance, SAMPLES_COUNT, 0, 1);
	arm_rfft_q15(&RealFFT_Instance,(q15_t *)xAccelMatrix,(q15_t *)FFT_Complex[0]);

	for(int e=0; e<(SAMPLES_COUNT); e++)
	{
		FFT_Real[0][e] = (int16_t)sqrt((FFT_Complex[0][(2*e)+0])*(FFT_Complex[0][(2*e)+0]) + (FFT_Complex[0][(2*e)+1])*(FFT_Complex[0][(2*e)+1]));
	}*/

	float fft_inputbuf[SOUND_SAMPLES_COUNT * 2];
	float fft_outputbuf[SOUND_SAMPLES_COUNT];
	for(int i=0;i < SOUND_SAMPLES_COUNT;i++)
	{
		fft_inputbuf[i*2] = soundMatrix[i];
		fft_inputbuf[2*i +1] = 0;
	}

	arm_cfft_f32 (&arm_cfft_sR_f32_len1024, fft_inputbuf, 0, 1); // Execute FFT transformation, ARM_CFFT_SR_F32_LEN4096 is macro, define rotary factors
	arm_cmplx_mag_f32 (fft_inputbuf, fft_outputbuf, SOUND_SAMPLES_COUNT); // Multiplexes the calculation result
}

/*
 * Calculate accelx matrix's fourier
 */
void Calculo_accel_furier_x(void)
{
	/*arm_rfft_init_q15(&RealFFT_Instance, SAMPLES_COUNT, 0, 1);
	arm_rfft_q15(&RealFFT_Instance,(q15_t *)xAccelMatrix,(q15_t *)FFT_Complex[0]);

	for(int e=0; e<(SAMPLES_COUNT); e++)
	{
		FFT_Real[0][e] = (int16_t)sqrt((FFT_Complex[0][(2*e)+0])*(FFT_Complex[0][(2*e)+0]) + (FFT_Complex[0][(2*e)+1])*(FFT_Complex[0][(2*e)+1]));
	}*/

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

/*
 * Calculate accely matrix's fourier
 */
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

/*
 * Calculate accelz matrix's fourier
 */
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
