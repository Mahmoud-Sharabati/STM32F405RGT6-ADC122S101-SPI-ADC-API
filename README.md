# STM32F405RGT6-ADC122S101-SPI-ADC-API
This project is a demonstration of how to interface the STM32F405RGT6 microcontroller with an external ADC122S101 analog-to-digital converter (ADC) over the Serial Peripheral Interface (SPI) bus. The ADC122S101 is a 12-bit, dual-channel ADC that can measure voltages with 2.7V - 5.25V range

## Requirements
* STM32F407 development board
* ADC122S101 SPI ADC module
* STM32 development environment (STM32CubeIDE)
* The STM32CubeMX software, available [here](https://www.st.com/en/development-tools/stm32cubemx.html).

## Installation
1. Clone the repository:
git clone [here](https://github.com/Mahmoud-Sharabati/STM32F405RGT6-ADC122S101-SPI-ADC-API.git).
2. Import the project into STM32CubeMX by selecting File > Import > C/C++ > Existing Code as Makefile Project.
3. Configure the project in STM32CubeMX according to your hardware setup.
4. Generate the code and open the project in your preferred development environment.
5. Build and upload the code to your device.

**Or: you can use this example by modifying the SPI Handler and Chip-Select pin as your connection as follow.**

## Usage

### Before using SPI CAN Driver
1. Modify the Hardware Configuration and Pins using CubeMX software
    This driver use SPI1 with the following pins:
    | SPI2_CS       | SPI2_SCK    | SPI2_MISO   |SPI2_MOSI   |
    | ------------- |:-----------:|:-----------:|:----------:|
    | PB12	    | PB13	  | PB14        | PB15	     |

	#### Notes:																	
	1. You need to modify the name of "Chip-Select pin CS" on your project to be `PCA21125_SPI_CS`.
	2. You must modify the SPI parameters as shown in image below.  
	![SPI_Config](https://user-images.githubusercontent.com/16566502/225283283-8cc0eec3-993b-4e3a-9c0e-acc861ee9e08.png)
	3. Other parameters will be automatically modified when generates the code.

 ### Use ADC122S101 Driver instruction
1. Define your xADC ADC122s101_Readings variable `Xadc_readings` to be used to store the readings.

2. Initialize the ADC122S101 driver using: `ADC122S101_Init(SPI_HandleTypeDef * hspi, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)`

	Parameters:
   | hspi | GPIOx | GPIO_Pin |
   |------------|--------- |--------- |
   | Connected SPI_HandleTypeDef | SPI Chip Select Port | SPI Chip Select Pin |
   
3. Get the ADC readings by `ADC122S101_read_all_channels(void)` function. The diver project uses the `Xadc_readings` variable to store reading values into. 

**NOTE: The ADC122S101 readings in this project can be monitored using the STM32 debugger.**

## Contributing
Contributions are welcome in the form of bug reports, feature requests, or pull requests. If you would like to contribute to the project, please fork this repository, make your changes, and submit a pull request.

## License
This driver is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgements
[ADC122S101 datasheet](https://www.ti.com/lit/gpn/adc122s101).  
[STM32F407 datasheet](https://www.st.com/resource/en/datasheet/stm32f407vg.pdf).
