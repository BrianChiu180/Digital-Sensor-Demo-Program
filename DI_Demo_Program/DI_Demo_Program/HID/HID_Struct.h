#pragma once

#include "Define.h"

enum cmd_categories {
	CMD_CATEGORY_I2C	= 0x00,
	CMD_CATEGORY_SPI	= 0x10,
	CMD_CATEGORY_GPIO	= 0x20,
	CMD_CATEGORY_SWI	= 0x30,
	CMD_CATEGORY_INFO	= 0x70
};

enum cmd_code {
	CMD_I2C_WRITE			= CMD_CATEGORY_I2C | 0x00,
	CMD_I2C_READ			= CMD_CATEGORY_I2C | 0x01,
	CMD_I2C_LOOP_READ		= CMD_CATEGORY_I2C | 0x02,
	CMD_I2C_WRITE_WITH_INT	= CMD_CATEGORY_I2C | 0x03,
	CMD_I2C_SET_CONFIG		= CMD_CATEGORY_I2C | 0x0E,
	CMD_I2C_GET_CONFIG		= CMD_CATEGORY_I2C | 0x0F,

	CMD_SPI_WRITE		= CMD_CATEGORY_SPI | 0x00,
	CMD_SPI_READ		= CMD_CATEGORY_SPI | 0x01,
	CMD_SPI_TRANSCEIVE	= CMD_CATEGORY_SPI | 0x02,
	CMD_SPI_SET_CONFIG	= CMD_CATEGORY_SPI | 0x0E,
	CMD_SPI_GET_CONFIG	= CMD_CATEGORY_SPI | 0x0F,

	CMD_GPIO_GET_LEVEL	= CMD_CATEGORY_GPIO | 0x00,
	CMD_GPIO_SWITCH		= CMD_CATEGORY_GPIO | 0x01,
	CMD_GPIO_TOGGLE		= CMD_CATEGORY_GPIO | 0x02,
	CMD_GPIO_PWM		= CMD_CATEGORY_GPIO | 0x03,
	CMD_GPIO_SET_INT	= CMD_CATEGORY_GPIO | 0x04,
	CMD_GPIO_GET_INT	= CMD_CATEGORY_GPIO | 0x05,
	CMD_GPIO_SET_CONFIG = CMD_CATEGORY_GPIO | 0x0E,
	CMD_GPIO_GET_CONFIG = CMD_CATEGORY_GPIO | 0x0F,

	CMD_SWI_WRITE		= CMD_CATEGORY_SWI | 0x00,
	CMD_SWI_SET_CONFIG	= CMD_CATEGORY_SWI | 0x0E,
	CMD_SWI_GET_CONFIG	= CMD_CATEGORY_SWI | 0x0F,

	CMD_INFO_CHIP		= CMD_CATEGORY_INFO | 0x0E,
	CMD_INFO_VERSION	= CMD_CATEGORY_INFO | 0x0F
};

#pragma pack(1)
struct I2CReport_ {
	union {
/* CMD_I2C_WRITE 0x00 */
		struct {
			uint8_t num;
			uint8_t reserved;
			uint8_t devid;
			uint8_t reg;
#define I2C_WRITE_MAX_LEN 59
			uint8_t data[I2C_WRITE_MAX_LEN];
		}writeIO;

/* CMD_I2C_READ 0x01 */
		struct {
			uint16_t num;
			uint8_t devid;
			uint8_t reg;
			uint8_t repeat;	/* 0 = read once, 1 = read twice ...*/
			uint16_t delay_ms;
			uint8_t scan;
		}readIN;

/* CMD_I2C_LOOP_READ 0x02 */
		struct {
			uint8_t  mode;
			union {
				uint8_t next;
				struct {
					uint32_t period;	/* 4 byte */
					uint8_t  devnum;	/* 1 byte */
					struct {
						uint8_t devid;
						uint8_t reg;
						uint8_t num;
					} devinfo[19];	/* 57 byte */
				};			/* 62 byte */
			};
		}loopRead;

		struct {
			uint8_t num; /* numbers of package data */
			uint8_t next;/* 0 is final package */
#define I2C_READ_MAX_LEN 61
			uint8_t data[I2C_READ_MAX_LEN];
		}readOUT;

/* CMD_I2C_WRITE_WITH_INT 0x03 */
		struct {
			uint8_t mode;				//read(0) or write(1)
			union {
				uint8_t next;			//(0)read one or (1)read
				struct {
					uint8_t intsel;		//selINT
					uint8_t devid;
					uint8_t clear_reg;
					uint8_t clear_data;
					uint8_t enable_reg;
					uint8_t enable_data;
				};
			};
		}writeWithInt;

		uint32_t countval32;
/* CMD_I2C_SET_CONFIG 0x0E */
/* CMD I2C_GET_CONFIG 0x0F */
		struct {
			uint8_t  enable;
			uint16_t baudrate;
		}configIO;
	};
};

#pragma pack(1)
struct SPIReport_ {
	union {
		/* CMD_SPI_WRITE 0x10 */
		struct {
			uint8_t num;
			uint8_t reserved;
			uint8_t slavePin;
#define SPI_WRITE_MAX_LEN 60
			uint8_t data[SPI_WRITE_MAX_LEN];
		}writeIO;

		/* CMD_SPI_READ 0x11 */
		struct {
			uint16_t num;
			uint8_t  slavePin;
		}readIN;

		struct {
			uint8_t num;
			uint8_t next;
#define SPI_READ_MAX_LEN 61
			uint8_t data[SPI_READ_MAX_LEN];
		}readOUT;

		/* CMD_SPI_TRANSCEIVE 0x12 */
		struct {
			uint16_t numRead;
			uint8_t  slavePin;
			uint8_t  numWrite;
			uint8_t  data[59];
		}transceiveIN;
		/* CMD_SPI_SET_CONFIG 0x1E */
		/* CMD_SPI_GET_CONFIG 0x1F */
		struct {
			uint8_t enable;
			uint8_t mode;
			uint32_t baudrate;
		}configIO;
	};
};

#pragma pack(1)
struct GPIOReport_ {
	uint8_t pin_numbers;
	union {
		uint8_t data[62];

		struct {
			uint8_t pinName;
			uint8_t state;
		}state[31];		/* CMD_GPIO_STATE 0x20 */

		struct {
			uint8_t pinName;
			uint8_t gpioSwitch;
		}gpioSwitch[31];			/* CMD_GPIO_SWITCH 0x21 */

		uint8_t pinName[62];		/* CMD_GPIO_TOGGLE 0x22 */

		struct {
			uint8_t pinName;
			uint8_t enable;
			uint8_t repeat;
			uint8_t prescaler;
			uint32_t period;
			uint32_t match;
		}PWM;						/* CMD_GPIO_PWM 0x23 */

		struct {
			uint8_t pinName;
			uint8_t trigger;		/* CMD_GPIO_GET_INT 0x25 */
		}trigger[31];

		struct {					/* CMD_GPIO_SET_CONFIG 0x2E */
			uint8_t pinName;
			uint8_t enable;
			uint8_t direction;
			uint8_t input_pull;
			uint8_t active_level;
			uint8_t active_on;
		}config[10];	//60
		/* CMD_GPIO_GET_CONFIG 0x2F */
	};
};

#pragma pack(1)
struct SWIReport_ {
	union {
		struct {
			uint16_t num;
			uint8_t data[61];
		}writeIO;
		struct {
			uint8_t enable;
			uint8_t pin;
		}configIO;
	};
};

/* CMD_INFO_CHIP 0x7E */
/* CMD_INFO_CHIP 0x7F */
#pragma pack(1)
struct INFOReport_ {
	char string[63];
};

#pragma pack(1)
typedef struct _HIDReport_ {
	uint8_t cmd;
	union {
		uint8_t err;
		uint8_t data[63];
		struct I2CReport_	I2C;
		struct GPIOReport_	GPIO;
		struct SPIReport_	SPI;
		struct SWIReport_	SWI;
		struct INFOReport_	INFO;
	};
}HIDReport_, *PHIDReport_;

