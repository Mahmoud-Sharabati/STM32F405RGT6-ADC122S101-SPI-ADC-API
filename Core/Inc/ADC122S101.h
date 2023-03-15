/*
 * ADC122S101.h
 *
 *  Created on: Mar 14, 2023
 *      Author: Mahmoud Sharabati
 */

#ifndef INC_ADC122S101_H_
#define INC_ADC122S101_H_

#include "main.h"

typedef struct ADC122s101_Readings {
	/* INA299 variables */
	float channel_0_voltage;
	float channel_1_voltage;
} ADC122s101_Readings;


/* Private variables ---------------------------------------------------------*/
extern  void Error_Handler(void);

/*
 *  ======== ADC122s101_Initialization ========
 *  Initial configuration state for a ADC122s101 External SPI ADC
 */
void ADC122S101_Init(SPI_HandleTypeDef * hspi, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

/*
 *  ======== ADC122S101_get_channel_voltage ========
 * Write and Read register
 */
float ADC122S101_get_channel_voltage(uint16_t channel);

/*
 *  ======== ADC122S101_read_all_channels ========
 * Read all XADC voltages
 */
ADC122s101_Readings ADC122S101_read_all_channels(void);


#endif /* INC_ADC122S101_H_ */
