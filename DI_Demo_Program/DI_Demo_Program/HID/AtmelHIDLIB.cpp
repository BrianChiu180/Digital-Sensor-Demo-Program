// AtmelHIDLIB.cpp : Defines the exported functions for the DLL application.
//

#include "Define.h"
#include "HID_Struct.h"
#include "USBHID.h"
#include "AtmelHIDLIB.h"

#define ATMELHIDDLL_VERSION "1.0.3.5 2018/07/31"

unsigned char HID_Open(void) {
	return OpenDevice();
}

unsigned char HID_GetDeviceNum(void) {
	return GetDeviceNum();
}

void HID_Close(void) {
	CloseDevice();
}

unsigned char HID_Write(unsigned char hidid, unsigned char* report) {
	return WriteReport(hidid, report);
}

unsigned char HID_Read(unsigned char hidid, unsigned char* report, unsigned long timeout) {
	return ReadReport(hidid, report, timeout);
}

unsigned char HID_Report(unsigned char hidid, unsigned char* report, unsigned long timeout) {
	return HIDReportIO(hidid, report, timeout);
}

unsigned char I2CWrite(unsigned char hidid, unsigned char devid, unsigned char reg, unsigned char* data, unsigned char num) {
	return I2C_Write(hidid, devid, reg, data, num);
}

unsigned char I2CRead(unsigned char hidid, unsigned char devid, unsigned char reg, unsigned char* data, unsigned short num, unsigned char repeat, unsigned short delay_ms, unsigned long timeout) {
	return I2C_Read(hidid, devid, reg, data, num, 0, repeat, delay_ms, timeout);
}

unsigned char I2CReadScan(unsigned char hidid, unsigned char devid, unsigned char reg, unsigned char* data, unsigned short num, unsigned char repeat, unsigned short delay_ms, unsigned long timeout) {
	return I2C_Read(hidid, devid, reg, data, num, 1, repeat, delay_ms, timeout);
}

unsigned char I2CLoopReadSet(unsigned char hidid, unsigned char devnum, unsigned char* devinfo, unsigned long period) {
	return I2C_LoopReadSet(hidid, devnum, devinfo, period);
}

unsigned char I2CLoopRead(unsigned char hidid, unsigned char* data, unsigned short* num, unsigned char next, unsigned long timeout) {
	return I2C_LoopRead(hidid, data, num, next, timeout);
}

unsigned char I2CsetConfig(unsigned char hidid, unsigned char* config, unsigned long timeout) {
	return I2C_SetConfigure(hidid, config, timeout);
}

unsigned char I2CgetConfig(unsigned char hidid, unsigned char* config) {
	return I2C_GetConfigure(hidid, config);
}

unsigned char SPIWrite(unsigned char hidid, unsigned char slavePin, unsigned char* data, unsigned char num) {
	return SPI_Write(hidid, slavePin, data, num);
}

unsigned char SPIRead(unsigned char hidid, unsigned char slavePin, unsigned char* data, unsigned short num, unsigned long timeout) {
	return SPI_Read(hidid, slavePin, data, num, timeout);
}

unsigned char SPITransceive(unsigned char hidid, unsigned char slavePin, unsigned char* data, unsigned char numWrite, unsigned short numRead, unsigned long timeout) {
	return SPI_Transceive(hidid, slavePin, data, numWrite, numRead, timeout);
}

unsigned char SPIsetConfig(unsigned char hidid, unsigned char* config, unsigned long timeout) {
	return SPI_SetConfigure(hidid, config, timeout);
}

unsigned char SPIgetConfig(unsigned char hidid, unsigned char* config) {
	return SPI_GetConfigure(hidid, config);
}

unsigned char GPIOgetLevel(unsigned char hidid, unsigned char pin_number, unsigned char* data) {
	return GPIO_GetLevel(hidid, pin_number, data);
}

unsigned char GPIOgetPinLevel(unsigned char hidid, unsigned char pin_name, unsigned char* data) {
	return GPIO_GetPinLevel(hidid, pin_name, data);
}

unsigned char GPIOswitch(unsigned char hidid, unsigned char pin_number, unsigned char* data) {
	return GPIO_Switch(hidid, pin_number, data);
}

unsigned char GPIOtoggle(unsigned char hidid, unsigned char pin_number, unsigned char* data) {
	return GPIO_Toggle(hidid, pin_number, data);
}

unsigned char GPIOsetConfig(unsigned char hidid, unsigned char pin_number, unsigned char* data) {
	return GPIO_SetConfigure(hidid, pin_number, data);
}

unsigned char GPIOgetConfig(unsigned char hidid, unsigned char pin_number, unsigned char* data) {
	return GPIO_GetConfigure(hidid, pin_number, data);
}

unsigned char INFOgetChip(unsigned char hidid, unsigned char* value) {
	return INFO_GetChip(hidid, value);
}

unsigned char INFOgetVersion(unsigned char hidid, unsigned char* value) {
	return INFO_GetVersion(hidid, value);
}

unsigned char SWIWrite(unsigned char hidid, unsigned char* data, unsigned char num) {
	return SWI_Write(hidid, data, num);
}

unsigned char SWIsetConfig(unsigned char hidid, unsigned char* config, unsigned long timeout) {
	return SWI_SetConfigure(hidid, config, timeout);
}

unsigned char SWIgetConfig(unsigned char hidid, unsigned char* config) {
	return SWI_GetConfigure(hidid, config);
}

void AtmelDLL_Version(char* string) {
	sprintf_s(string, sizeof(ATMELHIDDLL_VERSION), "%s", (char*)ATMELHIDDLL_VERSION);
}