/*
 * ds18b20.h
 *
 *  Created on: Feb 4, 2022
 *      Author: Developer
 */

#ifndef INC_DS18B20_H_
#define INC_DS18B20_H_

uint8_t DS18B20_Start (void);
void DS18B20_Write (uint8_t data);
uint8_t DS18B20_Read (void);
float DS18B20_Temperature(void);

#endif /* INC_DS18B20_H_ */
