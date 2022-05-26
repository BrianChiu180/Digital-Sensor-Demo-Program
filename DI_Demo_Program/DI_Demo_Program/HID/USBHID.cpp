/**
 * USBHID.cpp
 * 
 * Dyna-Image Corp.
 * Rocky Hsiao <rocky.hsiao@dyan-image.com>
**/

#include "Define.h"
#include "HID_Struct.h"
#include "USBHID.h"
#include <setupapi.h>

#ifdef __cplusplus
extern "C"
#endif
{
#include <dbt.h>
#include <hidsdi.h>
}

#ifdef	_DEBUG
#define	DISPLAY(SS)		puts(SS)
#else
#define	DISPLAY(SS)
#endif	// DEBUG

static HANDLE HID_Handle[10] = { INVALID_HANDLE_VALUE };
OVERLAPPED HIDOverlapped;
uint8_t DeviceNum = 0;
uint8_t number = 0;

HIDReport_ HIDReport[10];

uint8_t OpenDevice(void)
{
	BOOL result;
	GUID HidGuid;
	HDEVINFO hDevInfo;
	SP_DEVINFO_DATA devInfoData;
	SP_DEVICE_INTERFACE_DATA deviceInterfaceData;
	PSP_DEVICE_INTERFACE_DETAIL_DATA deviceInterfaceDetailData;
	DWORD deviceInterfaceDetailDataSize = 0;
	HANDLE DeviceHandle;
	DWORD MemberIndex;

	if (DeviceNum > 0)
		CloseDevice();

	HidD_GetHidGuid(&HidGuid);

	hDevInfo = SetupDiGetClassDevs(
		&HidGuid,
		NULL,
		NULL,
		DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);

	devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	deviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

	for (MemberIndex = 0; SetupDiEnumDeviceInterfaces(hDevInfo, 0, &HidGuid, MemberIndex, &deviceInterfaceData); ++MemberIndex)
	{
		result = SetupDiGetDeviceInterfaceDetail(
			hDevInfo,
			&deviceInterfaceData,
			NULL,
			0,
			&deviceInterfaceDetailDataSize,
			NULL);

		deviceInterfaceDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(deviceInterfaceDetailDataSize);
		deviceInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

		result = SetupDiGetDeviceInterfaceDetail(
			hDevInfo,
			&deviceInterfaceData,
			deviceInterfaceDetailData,
			deviceInterfaceDetailDataSize,
			NULL,
			&devInfoData);

		DeviceHandle = CreateFile(
			deviceInterfaceDetailData->DevicePath,
			0,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);

		HIDD_ATTRIBUTES Attributes;

		Attributes.Size = sizeof(struct _HIDD_ATTRIBUTES);

		HidD_GetAttributes(DeviceHandle, &Attributes);
		CloseHandle(DeviceHandle);

		if ((Attributes.VendorID == VID) && (Attributes.ProductID == PID)) {
			HID_Handle[DeviceNum++] = CreateFile(
				deviceInterfaceDetailData->DevicePath,
				GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				OPEN_EXISTING,
				FILE_FLAG_OVERLAPPED,
				NULL);
		}

		free(deviceInterfaceDetailData);
	}

	SetupDiDestroyDeviceInfoList(hDevInfo);
	return DeviceNum;
}

void CloseDevice(void) {
	for (int i = 0; i < DeviceNum; i++)
		CloseHandle(HID_Handle[i]);

	DeviceNum = 0;
}

uint8_t GetDeviceNum(void)
{
	return DeviceNum;
}

uint8_t CheckDevice(uint8_t num)
{
	if (DeviceNum <= num)
	{
		if (OpenDevice() <= num)
			return STATUS_ERR_USB_NO_DEVICE;
	}

	return STATUS_OK;
}

uint8_t WriteReport(uint8_t num, BYTE *ReportData)
{
	uint8_t status = STATUS_OK;
	BYTE OutputReport[65] = { 0 };
	DWORD lenght = 0;
	DWORD result;
	HANDLE hEvent;

	status = CheckDevice(num);

	if (status != STATUS_OK)
		return status;
	
	hEvent = CreateEvent(NULL, true, true, L"WriteReport");

	HIDOverlapped.hEvent = hEvent;
	HIDOverlapped.Offset = 0;
	HIDOverlapped.OffsetHigh = 0;

	memcpy(&OutputReport[1], ReportData, 64);

	if (HID_Handle[num] != INVALID_HANDLE_VALUE) {
		result = WriteFile(HID_Handle[num],
			OutputReport,
			65,
			&lenght,
			&HIDOverlapped);

		if (!result)
		{
			DWORD errorHandle = GetLastError();
			if (errorHandle != ERROR_IO_PENDING)
			{
				CloseDevice();
				status = CheckDevice(num);

				if (status != STATUS_OK)
					return status;

				result = WriteFile(HID_Handle[num],
					OutputReport,
					65,
					&lenght,
					&HIDOverlapped);
			}
		}
	}
	else
	{
		return STATUS_ERR_USB_NO_HANDLE;
	}

	result = WaitForSingleObject(hEvent, 1000);

	switch (result)
	{
	case WAIT_OBJECT_0:
		return STATUS_OK;
	case WAIT_TIMEOUT:
	default:
		return STATUS_ERR_USB_TIMEOUT;
	}
}

uint8_t ReadReport(uint8_t num, BYTE *ReportData, DWORD timeout)
{
	uint8_t status = STATUS_OK;
	BYTE InputReport[65] = { 0 };
	DWORD length = 0;
	DWORD result;
	HANDLE hEvent;

	status = CheckDevice(num);

	if (status != STATUS_OK)
		return status;

	hEvent = CreateEvent(NULL, true, true, L"ReadReport");

	HIDOverlapped.hEvent = hEvent;
	HIDOverlapped.Offset = 0;
	HIDOverlapped.OffsetHigh = 0;

	if (HID_Handle[num] != INVALID_HANDLE_VALUE) {
		result = ReadFile(HID_Handle[num],
			InputReport,
			65,
			&length,
			&HIDOverlapped);

		if (!result)
		{
			DWORD errorHandle = GetLastError();
			if (errorHandle != ERROR_IO_PENDING)
			{
				CloseDevice();
				status = CheckDevice(num);

				if (status != STATUS_OK)
					return status;

				result = ReadFile(HID_Handle[num],
					InputReport,
					65,
					&length,
					&HIDOverlapped);
			}
		}
	}
	else
	{
		return STATUS_ERR_USB_NO_HANDLE;
	}

	if (timeout == 0)
		timeout = 1000;

	result = WaitForSingleObject(hEvent, timeout);

	switch (result)
	{
	case WAIT_OBJECT_0:
		memcpy(ReportData, &InputReport[1], 64);
		return STATUS_OK;
	case WAIT_TIMEOUT:
	default:
		return STATUS_ERR_USB_TIMEOUT;
	}
}

uint8_t HIDReportIO(uint8_t num, BYTE *ReportData, DWORD timeout)
{
	uint8_t status = STATUS_OK;

	status = WriteReport(num, ReportData);
	if (status != STATUS_OK)
		return status;

	status = ReadReport(num, ReportData, timeout);

	return status;
}

uint8_t I2C_Write(uint8_t hidid, uint8_t devid, uint8_t reg, uint8_t *value, uint8_t num)
{
	uint8_t status = STATUS_OK;

	memset(&HIDReport[hidid], 0, sizeof(HIDReport_));
	HIDReport[hidid].cmd = CMD_I2C_WRITE;
	HIDReport[hidid].I2C.writeIO.devid = devid;
	HIDReport[hidid].I2C.writeIO.reg = reg;
	HIDReport[hidid].I2C.writeIO.num = num;
	memcpy(HIDReport[hidid].I2C.writeIO.data, value, num);

	status = HIDReportIO(hidid, (uint8_t *)&HIDReport[hidid], 1000);

	if (HIDReport[hidid].cmd & 0x80)
		return HIDReport[hidid].err;

	return status;
}

uint8_t I2C_Read(uint8_t hidid, uint8_t devid, uint8_t reg, uint8_t *value, uint16_t num, uint8_t scan, uint8_t repeat, uint16_t delay_ms, DWORD timeout)
{
	uint8_t status = STATUS_OK;
	ULONG NumberBuffers = 0;

	status = CheckDevice(hidid);
	if (status != STATUS_OK)
		return status;

	memset(&HIDReport[hidid], 0, sizeof(HIDReport_));
	HIDReport[hidid].cmd = CMD_I2C_READ;
	HIDReport[hidid].I2C.readIN.devid = devid;
	HIDReport[hidid].I2C.readIN.reg = reg;
	HIDReport[hidid].I2C.readIN.num = num;
	HIDReport[hidid].I2C.readIN.repeat = repeat;
	HIDReport[hidid].I2C.readIN.delay_ms = delay_ms;
	HIDReport[hidid].I2C.readIN.scan = scan;

	if (timeout < (DWORD)delay_ms * repeat)
		timeout = delay_ms * repeat + 1000;

	status = WriteReport(hidid, (uint8_t *)&HIDReport[hidid]);
	if (status != STATUS_OK)
		return status;

	do {
		status = ReadReport(hidid, (uint8_t *)&HIDReport[hidid], timeout);

		if (HIDReport[hidid].cmd & 0x80)
			return HIDReport[hidid].err;

		memcpy(value, HIDReport[hidid].I2C.readOUT.data, HIDReport[hidid].I2C.readOUT.num);

		value += HIDReport[hidid].I2C.readOUT.num;

		if ( status != STATUS_OK)
			return status;
	} while (HIDReport[hidid].I2C.readOUT.next);

	return status;
}

uint8_t I2C_LoopReadSet(uint8_t hidid, uint8_t devnum, uint8_t* devinfo, uint32_t period)
{
	uint8_t status = STATUS_OK;

	status = CheckDevice(hidid);
	if (status != STATUS_OK)
		return status;

	if (devnum > 19)
		return STATUS_ERR_NO_MEMORY;	

	memset(&HIDReport[hidid], 0, sizeof(HIDReport_));
	HIDReport[hidid].cmd = CMD_I2C_LOOP_READ;
	HIDReport[hidid].I2C.loopRead.mode = 0;
	HIDReport[hidid].I2C.loopRead.period = period;
	HIDReport[hidid].I2C.loopRead.devnum = devnum;
	memcpy(HIDReport[hidid].I2C.loopRead.devinfo, devinfo, (sizeof(uint8_t) * 3 * devnum));

	status = HIDReportIO(hidid, (uint8_t *)&HIDReport[hidid], 1000);

	if (HIDReport[hidid].cmd & 0x80)
		return HIDReport[hidid].err;

	return status;
}

uint8_t I2C_LoopRead(uint8_t hidid, uint8_t *value, uint16_t *num, uint8_t next, DWORD timeout)
{
	uint8_t status = STATUS_OK;
	ULONG NumberBuffers = 0;

	num[0] = 0;

	status = CheckDevice(hidid);
	if (status != STATUS_OK)
		return status;
	
	memset(&HIDReport[hidid], 0, sizeof(HIDReport_));
	HIDReport[hidid].cmd = CMD_I2C_LOOP_READ;
	HIDReport[hidid].I2C.loopRead.mode = 1;
	HIDReport[hidid].I2C.loopRead.next = next;

	status = WriteReport(hidid, (uint8_t *)&HIDReport[hidid]);
	if (status != STATUS_OK)
		return status;

	do {
		status = ReadReport(hidid, (uint8_t *)&HIDReport[hidid], timeout);

		if (HIDReport[hidid].cmd & 0x80)
			return HIDReport[hidid].err;

		memcpy(value, HIDReport[hidid].I2C.readOUT.data, HIDReport[hidid].I2C.readOUT.num);

		num[0] += HIDReport[hidid].I2C.readOUT.num;
		value += HIDReport[hidid].I2C.readOUT.num;

		if (status != STATUS_OK)
			return status;
	} while (HIDReport[hidid].I2C.readOUT.next);

	return status;
}

uint8_t I2C_SetConfigure(uint8_t hidid, uint8_t *config, DWORD timeout)
{
	uint8_t status = STATUS_OK;

	memset(&HIDReport[hidid], 0, sizeof(HIDReport_));
	HIDReport[hidid].cmd = CMD_I2C_SET_CONFIG;
	memcpy(&HIDReport[hidid].I2C.configIO, config, sizeof(HIDReport[hidid].I2C.configIO));

	status = HIDReportIO(hidid, (uint8_t *)&HIDReport[hidid], timeout);

	if (HIDReport[hidid].cmd & 0x80)
		return HIDReport[hidid].err;

	return status;
}

uint8_t I2C_GetConfigure(uint8_t hidid, uint8_t *config)
{
	uint8_t status = STATUS_OK;

	memset(&HIDReport[hidid], 0, sizeof(HIDReport_));
	HIDReport[hidid].cmd = CMD_I2C_GET_CONFIG;

	status = HIDReportIO(hidid, (uint8_t *)&HIDReport[hidid], 1000);

	if (HIDReport[hidid].cmd & 0x80)
		return HIDReport[hidid].err;

	memcpy(config, &HIDReport[hidid].I2C.configIO, sizeof(HIDReport[hidid].I2C.configIO));

	return status;
}

uint8_t SPI_Write(uint8_t hidid, uint8_t slavePin, uint8_t *value, uint8_t num)
{
	uint8_t status = STATUS_OK;

	memset(&HIDReport[hidid], 0, sizeof(HIDReport_));
	HIDReport[hidid].cmd = CMD_SPI_WRITE;
	HIDReport[hidid].SPI.writeIO.slavePin = slavePin;
	HIDReport[hidid].SPI.writeIO.num = num;
	memcpy(HIDReport[hidid].SPI.writeIO.data, value, num);

	status = HIDReportIO(hidid, (uint8_t *)&HIDReport[hidid], 1000);

	if (HIDReport[hidid].cmd & 0x80)
		return HIDReport[hidid].err;

	return status;
}

uint8_t SPI_Read(uint8_t hidid, uint8_t slavePin, uint8_t *value, uint16_t num, DWORD timeout)
{
	uint8_t status = STATUS_OK;

	status = CheckDevice(hidid);
	if (status != STATUS_OK)
		return status;

	memset(&HIDReport[hidid], 0, sizeof(HIDReport_));
	HIDReport[hidid].cmd = CMD_SPI_READ;
	HIDReport[hidid].SPI.readIN.slavePin = slavePin;
	HIDReport[hidid].SPI.readIN.num = num;

	status = WriteReport(hidid, (uint8_t *)&HIDReport[hidid]);
	if (status != STATUS_OK)
		return status;

	do {
		status = ReadReport(hidid, (uint8_t *)&HIDReport[hidid], timeout);

		if (HIDReport[hidid].cmd & 0x80)
			return HIDReport[hidid].err;

		memcpy(value, HIDReport[hidid].SPI.readOUT.data, HIDReport[hidid].SPI.readOUT.num);

		value += HIDReport[hidid].SPI.readOUT.num;

		if (status != STATUS_OK)
			return status;
	} while (HIDReport[hidid].SPI.readOUT.next);

	return status;
}

uint8_t SPI_Transceive(uint8_t hidid, uint8_t slavePin, uint8_t *value, uint8_t numWrite, uint16_t numRead, DWORD timeout)
{
	uint8_t status = STATUS_OK;

	status = CheckDevice(hidid);
	if (status != STATUS_OK)
		return status;

	memset(&HIDReport[hidid], 0, sizeof(HIDReport_));
	HIDReport[hidid].cmd = CMD_SPI_TRANSCEIVE;
	HIDReport[hidid].SPI.transceiveIN.slavePin = slavePin;
	HIDReport[hidid].SPI.transceiveIN.numWrite = numWrite;
	HIDReport[hidid].SPI.transceiveIN.numRead = numRead;
	memcpy(HIDReport[hidid].SPI.transceiveIN.data, value, numWrite);

	status = WriteReport(hidid, (uint8_t *)&HIDReport[hidid]);
	if (status != STATUS_OK)
		return status;

	do {
		status = ReadReport(hidid, (uint8_t *)&HIDReport[hidid], timeout);

		if (HIDReport[hidid].cmd & 0x80)
			return HIDReport[hidid].err;

		memcpy(value, HIDReport[hidid].SPI.readOUT.data, HIDReport[hidid].SPI.readOUT.num);

		value += HIDReport[hidid].SPI.readOUT.num;

		if (status != STATUS_OK)
			return status;
	} while (HIDReport[hidid].SPI.readOUT.next);

	return status;
}

uint8_t SPI_SetConfigure(uint8_t hidid, uint8_t *config, DWORD timeout)
{
	uint8_t status = STATUS_OK;

	memset(&HIDReport[hidid], 0, sizeof(HIDReport_));
	HIDReport[hidid].cmd = CMD_SPI_SET_CONFIG;
	memcpy(&HIDReport[hidid].SPI.configIO, config, sizeof(HIDReport[hidid].SPI.configIO));

	status = HIDReportIO(hidid, (uint8_t *)&HIDReport[hidid], timeout);

	if (HIDReport[hidid].cmd & 0x80)
		return HIDReport[hidid].err;

	return status;
}

uint8_t SPI_GetConfigure(uint8_t hidid, uint8_t *config)
{
	uint8_t status = STATUS_OK;

	memset(&HIDReport[hidid], 0, sizeof(HIDReport_));
	HIDReport[hidid].cmd = CMD_SPI_GET_CONFIG;

	status = HIDReportIO(hidid, (uint8_t *)&HIDReport[hidid], 1000);

	if (HIDReport[hidid].cmd & 0x80)
		return HIDReport[hidid].err;

	memcpy(config, &HIDReport[hidid].SPI.configIO, sizeof(HIDReport[hidid].SPI.configIO));

	return status;
}

uint8_t GPIO_GetLevel(uint8_t hidid, uint8_t gpio_num, uint8_t* data)
{
	uint8_t status = STATUS_OK;

	HIDReport[hidid].cmd = CMD_GPIO_GET_LEVEL;
	HIDReport[hidid].GPIO.pin_numbers = gpio_num;
	memcpy(HIDReport[hidid].GPIO.state, data, sizeof(HIDReport[hidid].GPIO.state));

	status = HIDReportIO(hidid, (uint8_t*)& HIDReport[hidid], 1000);

	if (HIDReport[hidid].cmd & 0x80)
		return HIDReport[hidid].err;

	return status;
}

uint8_t GPIO_GetPinLevel(uint8_t hidid, uint8_t pin_name, uint8_t* data)
{
	uint8_t status = STATUS_OK;
	bool pin_state = false;

	HIDReport[hidid].cmd = CMD_GPIO_GET_LEVEL;
	HIDReport[hidid].GPIO.pin_numbers = 1;
	HIDReport[hidid].GPIO.state[0].pinName = pin_name;

	status = HIDReportIO(hidid, (uint8_t*)&HIDReport[hidid], 1000);

	if (HIDReport[hidid].cmd & 0x80)
		return HIDReport[hidid].err;

	*data = (uint8_t)HIDReport[hidid].GPIO.state[0].state;

	return status;
}

uint8_t GPIO_Switch(uint8_t hidid, uint8_t gpio_num, uint8_t* data)
{
	uint8_t status = STATUS_OK;

	HIDReport[hidid].cmd = CMD_GPIO_SWITCH;
	HIDReport[hidid].GPIO.pin_numbers = gpio_num;
	memcpy(HIDReport[hidid].GPIO.gpioSwitch, data, sizeof(HIDReport[hidid].GPIO.gpioSwitch));

	status = HIDReportIO(hidid, (uint8_t*)& HIDReport[hidid], 1000);

	if (HIDReport[hidid].cmd & 0x80)
		return HIDReport[hidid].err;

	return status;
}

uint8_t GPIO_Toggle(uint8_t hidid, uint8_t gpio_num, uint8_t* data)
{
	uint8_t status = STATUS_OK;

	HIDReport[hidid].cmd = CMD_GPIO_TOGGLE;
	HIDReport[hidid].GPIO.pin_numbers = gpio_num;
	memcpy(HIDReport[hidid].GPIO.pinName, data, sizeof(HIDReport[hidid].GPIO.pinName));

	status = HIDReportIO(hidid, (uint8_t*)& HIDReport[hidid], 1000);

	if (HIDReport[hidid].cmd & 0x80)
		return HIDReport[hidid].err;

	return status;
}

uint8_t GPIO_SetConfigure(uint8_t hidid, uint8_t gpio_num, uint8_t* data)
{
	uint8_t status = STATUS_OK;

	memset(&HIDReport[hidid], 0, sizeof(HIDReport_));
	HIDReport[hidid].cmd = CMD_GPIO_SET_CONFIG;
	HIDReport[hidid].GPIO.pin_numbers = gpio_num;
	memcpy(HIDReport[hidid].GPIO.config, data, sizeof(HIDReport[hidid].GPIO.config));

	status = HIDReportIO(hidid, (uint8_t*)& HIDReport[hidid], 1000);

	if (HIDReport[hidid].cmd & 0x80)
		return HIDReport[hidid].err;

	return status;
}

uint8_t GPIO_GetConfigure(uint8_t hidid, uint8_t gpio_num, uint8_t* data)
{
	uint8_t status = STATUS_OK;

	memset(&HIDReport[hidid], 0, sizeof(HIDReport_));
	HIDReport[hidid].cmd = CMD_GPIO_GET_CONFIG;
	HIDReport[hidid].GPIO.pin_numbers = gpio_num;
	memcpy(HIDReport[hidid].GPIO.config, data, sizeof(HIDReport[hidid].GPIO.config));

	status = HIDReportIO(hidid, (uint8_t*)& HIDReport[hidid], 1000);

	if (HIDReport[hidid].cmd & 0x80)
		return HIDReport[hidid].err;

	memcpy(data, &HIDReport[hidid].GPIO.config, sizeof(HIDReport[hidid].GPIO.config));

	return status;
}

uint8_t INFO_GetChip(uint8_t hidid, uint8_t *value)
{
	uint8_t status = STATUS_OK;

	memset(&HIDReport[hidid], 0, sizeof(HIDReport_));
	HIDReport[hidid].cmd = CMD_INFO_CHIP;

	status = HIDReportIO(hidid, (uint8_t *)&HIDReport[hidid], 1000);

	if (HIDReport[hidid].cmd & 0x80)
		return HIDReport[hidid].err;

	memcpy(value, &HIDReport[hidid].INFO.string, sizeof(HIDReport[hidid].INFO.string));

	return status;
}

uint8_t INFO_GetVersion(uint8_t hidid, uint8_t *value)
{
	uint8_t status = STATUS_OK;

	memset(&HIDReport[hidid], 0, sizeof(HIDReport_));
	HIDReport[hidid].cmd = CMD_INFO_VERSION;

	status = HIDReportIO(hidid, (uint8_t *)&HIDReport[hidid], 1000);

	if (HIDReport[hidid].cmd & 0x80)
		return HIDReport[hidid].err;

	memcpy(value, &HIDReport[hidid].INFO.string, sizeof(HIDReport[hidid].INFO.string));

	return status;
}

uint8_t SWI_Write(uint8_t hidid, uint8_t *value, uint8_t num)
{
	uint8_t status = STATUS_OK;

	memset(&HIDReport[hidid], 0, sizeof(HIDReport_));
	HIDReport[hidid].cmd = CMD_SWI_WRITE;
	HIDReport[hidid].SWI.writeIO.num = num;
	memcpy(HIDReport[hidid].SWI.writeIO.data, value, num);

	status = HIDReportIO(hidid, (uint8_t *)&HIDReport[hidid], 1000);

	if (HIDReport[hidid].cmd & 0x80)
		return HIDReport[hidid].err;

	return status;
}

uint8_t SWI_SetConfigure(uint8_t hidid, uint8_t *config, DWORD timeout)
{
	uint8_t status = STATUS_OK;

	memset(&HIDReport[hidid], 0, sizeof(HIDReport_));
	HIDReport[hidid].cmd = CMD_SWI_SET_CONFIG;
	memcpy(&HIDReport[hidid].SWI.configIO, config, sizeof(HIDReport[hidid].SWI.configIO));

	status = HIDReportIO(hidid, (uint8_t *)&HIDReport[hidid], timeout);

	if (HIDReport[hidid].cmd & 0x80)
		return HIDReport[hidid].err;

	return status;
}

uint8_t SWI_GetConfigure(uint8_t hidid, uint8_t *config)
{
	uint8_t status = STATUS_OK;

	memset(&HIDReport[hidid], 0, sizeof(HIDReport_));
	HIDReport[hidid].cmd = CMD_SWI_GET_CONFIG;

	status = HIDReportIO(hidid, (uint8_t *)&HIDReport[hidid], 1000);

	if (HIDReport[hidid].cmd & 0x80)
		return HIDReport[hidid].err;

	memcpy(config, &HIDReport[hidid].SWI.configIO, sizeof(HIDReport[hidid].SWI.configIO));

	return status;
}