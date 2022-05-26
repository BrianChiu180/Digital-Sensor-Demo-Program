#pragma once

#define VID 0x0F43
#define PID 0x2000

#ifdef __cplusplus
extern "C" 
#endif

{
	uint8_t OpenDevice(void);
	void CloseDevice(void);
	uint8_t WriteReport(uint8_t num, BYTE *ReportData);
	uint8_t ReadReport(uint8_t num, BYTE *ReportData, DWORD timeout);
	uint8_t HIDReportIO(uint8_t num, BYTE *ReportData, DWORD timeout);
	uint8_t GetDeviceNum(void);

	/* I2C */
	uint8_t I2C_Write(uint8_t hidid, uint8_t devid, uint8_t reg, uint8_t *data, uint8_t num);
	uint8_t I2C_Read(uint8_t hidid, uint8_t devid, uint8_t reg, uint8_t *value, uint16_t num, uint8_t scan, uint8_t repeat, uint16_t delay_ms, DWORD timeout);
	uint8_t I2C_LoopReadSet(uint8_t hidid, uint8_t devnum, uint8_t* devinfo, uint32_t period);
	uint8_t I2C_LoopRead(uint8_t hidid, uint8_t *value, uint16_t *num, uint8_t next, DWORD timeout);
	uint8_t I2C_SetConfigure(uint8_t hidid, uint8_t *config, DWORD timeout);
	uint8_t I2C_GetConfigure(uint8_t hidid, uint8_t *config);

	/* SPI */
	uint8_t SPI_Write(uint8_t hidid, uint8_t slavePin, uint8_t *value, uint8_t num);
	uint8_t SPI_Read(uint8_t hidid, uint8_t slavePin, uint8_t *value, uint16_t num, DWORD timeout);
	uint8_t SPI_Transceive(uint8_t hidid, uint8_t slavePin, uint8_t *value, uint8_t numWrite, uint16_t numRead, DWORD timeout);
	uint8_t SPI_SetConfigure(uint8_t hidid, uint8_t *config, DWORD timeout);
	uint8_t SPI_GetConfigure(uint8_t hidid, uint8_t *config);

	/* GPIO */
	uint8_t GPIO_GetLevel(uint8_t hidid, uint8_t gpio_num, uint8_t* data);
	uint8_t GPIO_GetPinLevel(uint8_t hidid, uint8_t pin_name, uint8_t* data);
	uint8_t GPIO_Switch(uint8_t hidid, uint8_t gpio_num, uint8_t* data);
	uint8_t GPIO_Toggle(uint8_t hidid, uint8_t gpio_num, uint8_t* data);
	uint8_t GPIO_SetConfigure(uint8_t hidid, uint8_t gpio_num, uint8_t* data);
	uint8_t GPIO_GetConfigure(uint8_t hidid, uint8_t gpio_num, uint8_t* data);

	/* SWI */
	uint8_t SWI_Write(uint8_t hidid, uint8_t *value, uint8_t num);
	uint8_t SWI_SetConfigure(uint8_t hidid, uint8_t *config, DWORD timeout);
	uint8_t SWI_GetConfigure(uint8_t hidid, uint8_t *config);

	/* INFO */
	uint8_t INFO_GetChip(uint8_t hidid, uint8_t *value);
	uint8_t INFO_GetVersion(uint8_t hidid, uint8_t *value);
}