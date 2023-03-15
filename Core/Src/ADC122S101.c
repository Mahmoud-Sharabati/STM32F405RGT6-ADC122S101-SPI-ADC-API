/*
 * ADC122S101.c
 *
 *  Created on: Mar 14, 2023
 *      Author: Mahmoud Sharabati
 */
#include "ADC122S101.h"

SPI_HandleTypeDef * ADC122S101_SPI;
GPIO_TypeDef* ADC122S101_CS_GPIO_port;
uint16_t ADC122S101_CS_pin;

/*
 *  ======== ADC122S101_Initialization ========
 *  Initial configuration state for a ADC122S101 External SPI ADC
 */
void ADC122S101_Init(SPI_HandleTypeDef * hspi, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	ADC122S101_SPI = hspi;
	ADC122S101_CS_GPIO_port = GPIOx;
	ADC122S101_CS_pin = GPIO_Pin;
}

/*
 *  ======== ADC122S101_getVoltages ========
 * Write and Read register
 */
float ADC122S101_get_channel_voltage(uint16_t channel)
{
	uint8_t txBuf[2] = {0,0};
	uint8_t rxBuf[2] = {0};

	if (channel < 3) {
		txBuf[0] = channel << 3;
	} // Not allowed to pass more than 2. The output signal at the DOUT pin is indeterminate if ADD1 is high.

	uint16_t local_channel_binary_voltage = 0;
	float local_channel_voltage = 0;

	/* Select the ADC122S101: Chip Select low */
	HAL_GPIO_WritePin(ADC122S101_CS_GPIO_port, ADC122S101_CS_pin, GPIO_PIN_RESET);

	while (ADC122S101_SPI->State == HAL_SPI_STATE_RESET) {
		HAL_Delay(1);
	}

	HAL_SPI_Transmit(ADC122S101_SPI, (uint8_t*)txBuf, 2, 200);
	HAL_SPI_Receive (ADC122S101_SPI, (uint8_t*)rxBuf, 2, 200);

	//	HAL_SPI_Receive (ADC122S101_SPI, (uint8_t*)rxBuf, sizeof(rxBuf), HAL_MAX_DELAY);

	/* Deselect the ADC122S101: Chip Select high */
	HAL_GPIO_WritePin(ADC122S101_CS_GPIO_port, ADC122S101_CS_pin, GPIO_PIN_SET);

	local_channel_binary_voltage = ((rxBuf[0] << 8 | rxBuf[1]) & 0xFFF);
	local_channel_voltage = (float)(local_channel_binary_voltage * 5.0)/4096.;

	return local_channel_voltage;
}

/*
 *  ======== ADC122S101_read_all_channels ========
 * Read all XADC voltages
 */
ADC122s101_Readings ADC122S101_read_all_channels(void) {
	ADC122s101_Readings local_readings = {0,0};

	local_readings.channel_0_voltage = ADC122S101_get_channel_voltage(0);
	local_readings.channel_1_voltage = ADC122S101_get_channel_voltage(1);

	return local_readings;
}
