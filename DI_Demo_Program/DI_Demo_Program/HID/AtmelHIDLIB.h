#pragma once

unsigned char HID_Open(void);
void		  HID_Close(void);
unsigned char HID_Write(unsigned char hidid, unsigned char* report);
unsigned char HID_Read(unsigned char hidid, unsigned char* report, unsigned long timeout);
unsigned char HID_Report(unsigned char hidid, unsigned char* report, unsigned long timeout);
unsigned char HID_GetDeviceNum(void);

unsigned char I2CWrite(unsigned char hidid, unsigned char devid, unsigned char reg, unsigned char* data, unsigned char num);
unsigned char I2CRead(unsigned char hidid, unsigned char devid, unsigned char reg, unsigned char* data, unsigned short num, unsigned char repaet, unsigned short delay_ms, unsigned long timeout);
unsigned char I2CReadScan(unsigned char hidid, unsigned char devid, unsigned char reg, unsigned char* data, unsigned short num, unsigned char repaet, unsigned short delay_ms, unsigned long timeout);
unsigned char I2CLoopReadSet(unsigned char hidid, unsigned char devnum, unsigned char* devinfo, unsigned long period);
unsigned char I2CLoopRead(unsigned char hidid, unsigned char* data, unsigned short* num, unsigned char next, unsigned long timeout);
unsigned char I2CsetConfig(unsigned char hidid, unsigned char* config, unsigned long timeout);
unsigned char I2CgetConfig(unsigned char hidid, unsigned char* config);

unsigned char SPIWrite(unsigned char hidid, unsigned char slavePin, unsigned char* data, unsigned char num);
unsigned char SPIRead(unsigned char hidid, unsigned char slavePin, unsigned char* data, unsigned short num, unsigned long timeout);
unsigned char SPITransceive(unsigned char hidid, unsigned char slavePin, unsigned char* data, unsigned char numWrite, unsigned short numRead, unsigned long timeout);
unsigned char SPIsetConfig(unsigned char hidid, unsigned char* config, unsigned long timeout);
unsigned char SPIgetConfig(unsigned char hidid, unsigned char* config);

unsigned char GPIOgetLevel(unsigned char hidid, unsigned char pin_number, unsigned char* data);
unsigned char GPIOgetPinLevel(unsigned char hidid, unsigned char pin_name, unsigned char* data);
unsigned char GPIOswitch(unsigned char hidid, unsigned char pin_number, unsigned char* data);
unsigned char GPIOtoggle(unsigned char hidid, unsigned char pin_number, unsigned char* data);
unsigned char GPIOsetConfig(unsigned char hidid, unsigned char pin_number, unsigned char* data);
unsigned char GPIOgetConfig(unsigned char hidid, unsigned char pin_number, unsigned char* data);

unsigned char SWIWrite(unsigned char hidid, unsigned char* data, unsigned char num);
unsigned char SWIsetConfig(unsigned char hidid, unsigned char* config, unsigned long timeout);
unsigned char SWIgetConfig(unsigned char hidid, unsigned char* config);

unsigned char INFOgetChip(unsigned char hidid, unsigned char* value);
unsigned char INFOgetVersion(unsigned char hidid, unsigned char* value);

void		  AtmelDLL_Version(char* string);

#pragma pack(1)
typedef struct {
	unsigned char enable;
	unsigned char mode;
	unsigned int  baudrate;
}SPIConfig_;

#pragma pack(1)
typedef struct {
	unsigned char  enable;
	unsigned short baudrate;
}I2CConfig_;

#pragma pack(1)
typedef struct {
	unsigned char enable;
	unsigned char direction;
	unsigned char input_pull;
	unsigned char active_level; /* 0 = LOW, 1 = HIGH */
	unsigned char active_on;	/* 0 = OFF, 1 = ON */
}GPIOConfig_;

enum gpio_name_ {
	GPIO_PA08,	/* I2C_SDA */
	GPIO_PA09,	/* I2C_SCL */
	GPIO_PA10,	/* INT1 */
	GPIO_PA11,	/* INT2 */
	GPIO_PA12,
	GPIO_PA13,
	GPIO_PA15,
	GPIO_PA16,	/* SPI_MISO */
	GPIO_PA17,	/* SPI_SS */
	GPIO_PA18,	/* SPI_MOSI */
	GPIO_PA19,	/* SPI_SCK */
	GPIO_PA20,	/* OLED_RES */
	GPIO_PA21,	/* OLED_DC */
	GPIO_PB03,	/* BUTTON_S2 */
	GPIO_PB08,	/* UART_TX */
	GPIO_PB09,	/* UART_RX */
	GPIO_PB11,
	GPIO_PB22, /* LED_D8 */
	GPIO_PB23, /* LED_D7 */
	GPIO_PA22, /* VLED_EN */
	GPIO_PA23, /* IVDD_EN */
	GPIO_PA27, /* SVDD_EN */
	GPIO_END
};

enum gpio_direction_ {
	GPIO_INPUT,	/* default */
	GPIO_OUTPUT,
	GPIO_OUTPUT_READBACK
};

enum gpio_input_pull_ {
	GPIO_PULL_NONE,
	GPIO_PULL_UP, /* default */
	GPIO_PULL_DOWN
};

//Error code
enum status_categories {
	STATUS_CATEGORY_OK = 0x00,
	STATUS_CATEGORY_COMMON = 0x10,
	STATUS_CATEGORY_ANALOG = 0x30,
	STATUS_CATEGORY_COM = 0x40,
	STATUS_CATEGORY_IO = 0x50,
	STATUS_CATEGORY_USB = 0xE0
};

enum status_code {
	STATUS_OK = STATUS_CATEGORY_OK | 0x00,
	STATUS_VALID_DATA = STATUS_CATEGORY_OK | 0x01,
	STATUS_NO_CHANGE = STATUS_CATEGORY_OK | 0x02,
	STATUS_ABORTED = STATUS_CATEGORY_OK | 0x04,
	STATUS_BUSY = STATUS_CATEGORY_OK | 0x05,
	STATUS_SUSPEND = STATUS_CATEGORY_OK | 0x06,

	STATUS_ERR_IO = STATUS_CATEGORY_COMMON | 0x00,
	STATUS_ERR_REQ_FLUSHED = STATUS_CATEGORY_COMMON | 0x01,
	STATUS_ERR_TIMEOUT = STATUS_CATEGORY_COMMON | 0x02,
	STATUS_ERR_BAD_DATA = STATUS_CATEGORY_COMMON | 0x03,
	STATUS_ERR_NOT_FOUND = STATUS_CATEGORY_COMMON | 0x04,
	STATUS_ERR_UNSUPPORTED_DEV = STATUS_CATEGORY_COMMON | 0x05,
	STATUS_ERR_NO_MEMORY = STATUS_CATEGORY_COMMON | 0x06,
	STATUS_ERR_INVALID_ARG = STATUS_CATEGORY_COMMON | 0x07,
	STATUS_ERR_BAD_ADDRESS = STATUS_CATEGORY_COMMON | 0x08,
	STATUS_ERR_BAD_FORMAT = STATUS_CATEGORY_COMMON | 0x0A,
	STATUS_ERR_BAD_FRQ = STATUS_CATEGORY_COMMON | 0x0B,
	STATUS_ERR_DENIED = STATUS_CATEGORY_COMMON | 0x0c,
	STATUS_ERR_ALREADY_INITIALIZED = STATUS_CATEGORY_COMMON | 0x0d,
	STATUS_ERR_OVERFLOW = STATUS_CATEGORY_COMMON | 0x0e,
	STATUS_ERR_NOT_INITIALIZED = STATUS_CATEGORY_COMMON | 0x0f,

	STATUS_ERR_SAMPLERATE_UNAVAILABLE = STATUS_CATEGORY_ANALOG | 0x00,
	STATUS_ERR_RESOLUTION_UNAVAILABLE = STATUS_CATEGORY_ANALOG | 0x01,

	STATUS_ERR_BAUDRATE_UNAVAILABLE = STATUS_CATEGORY_COM | 0x00,
	STATUS_ERR_PACKET_COLLISION = STATUS_CATEGORY_COM | 0x01,
	STATUS_ERR_PROTOCOL = STATUS_CATEGORY_COM | 0x02,
	STATUS_ERR_USED_PIN = STATUS_CATEGORY_COM | 0x03,	/* #define ERR_DEFINE_PIN	0x21  //Pin have be used */

	STATUS_ERR_PIN_MUX_INVALID = STATUS_CATEGORY_IO | 0x00,

	STATUS_ERR_USB_NO_DEVICE = STATUS_CATEGORY_USB | 0x00,
	STATUS_ERR_USB_NO_HANDLE = STATUS_CATEGORY_USB | 0x01,
	STATUS_ERR_USB_WRONG_NUM = STATUS_CATEGORY_USB | 0x02,
	STATUS_ERR_USB_UNKNOW_CMD = STATUS_CATEGORY_USB | 0x03,
	STATUS_ERR_USB_TIMEOUT = STATUS_CATEGORY_USB | 0x0F
};

