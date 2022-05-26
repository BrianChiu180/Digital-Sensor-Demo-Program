#pragma once
#include "Define.h"

class CDI3135_D : public CDieInfo {
public:
	CDI3135_D() {}
	void Init(uint16_t version)
	{
		DieName = _T("DI3135_D");
		switch (version)
		{
		case 10000:
			DieDetail.insert(make_pair(10000, CDieDetail()));
			{
				pDieDetail = &DieDetail.at(10000);
				pRegTable = &pDieDetail->RegisterTable;

				pRegTable->DeviceID = 0x18;

				pRegTable->SetRegAddr(0x00);
				pRegTable->SetRegInfo({ 0x33 }, _T("WHOAMI"));
				{
					pRegTable->SetBitDetail(_T("WHOAMI"), _T("Who am I"), 0xFF, 0, ONLY_R);
				}

				pRegTable->SetRegAddr(0x01);
				pRegTable->SetRegInfo({ 0x00 }, _T("IRQ_STS"));
				{
					pRegTable->SetBitDetail(_T("STS_ACT"), 7, _T("Status of activity"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("STS_TAP"), 5, _T("Status of Tap Sensing"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("STS_AOI"), 4, _T("Status of AOI (Shock/Freefall/Profile/Gesture)"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("STS_OVN"), 3, _T("Status of FIFO overrun"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("STS_WTM"), 2, _T("Status of FIFO water mark"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("STS_DRDY"), 1, _T("Status of Data ready"), 0, ONLY_R);
				}

				pRegTable->SetRegAddr(0x02);
				pRegTable->SetRegInfo({ 0x00 }, _T("MODE_STS"));
				{
					pRegTable->SetBitDetail(_T("PO_DRDY"), 4, _T("Status of Data ready"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("STS_MEAS"), 2, _T("Measurement mode status"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("STS_WAK"), 1, _T("Wakeup mode status"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("STS_STBY"), 0, _T("Power down mode status"), 0, ONLY_R);
				}

				pRegTable->SetRegAddr(0x07);
				pRegTable->SetRegInfo({ 0x02 }, _T("CTRL_CFG0"));
				{
					pRegTable->SetBitDetail(_T("SELF_TEST"), 4, _T("Self Test"));
					pRegTable->SetBitDetail(_T("NoUse_0x02_Bit2"), 2, _T(""), 1);
				}

				pRegTable->SetRegAddr(0x08);
				pRegTable->SetRegInfo({ 0x00 }, _T("MODE_CFG"));
				{
					pRegTable->SetBitDetail(_T("SPI_MODE"), 5, _T("SPI Mode Selection"));
					pRegTable->SetBitDetail(_T("SW_RST"), 4, _T("Soft reset"));
					pRegTable->SetBitDetail(_T("MEASURE"), _T("Operation mode selection"), 0x03, 0, BOTH_RW, { 0, 2 }, 0x00);
				}

				pRegTable->SetRegAddr(0x09);
				pRegTable->SetRegInfo({ 0x07 }, _T("CTRL_CFG1"));
				{
					pRegTable->SetBitDetail(_T("ODR"), _T("Output data rate"), 0x70, 4, BOTH_RW, { 0, 6 }, 0x00);
					pRegTable->SetBitDetail(_T("HR"), 3, _T("Low pass filter enable"));
					pRegTable->SetBitDetail(_T("ZEN"), 2, _T("Z Axis enable"), 1);
					pRegTable->SetBitDetail(_T("YEN"), 1, _T("Y Axis enable"), 1);
					pRegTable->SetBitDetail(_T("XEN"), 0, _T("X Axis enable"), 1);
				}

				pRegTable->SetRegAddr(0x0A);
				pRegTable->SetRegInfo({ 0x00 }, _T("CTRL_CFG2"));
				{
					pRegTable->SetBitDetail(_T("I2_ACT"), 7, _T("Active status map to INT2"));
					pRegTable->SetBitDetail(_T("I2_SLP"), 6, _T("Inactive status map to INT2"));
					pRegTable->SetBitDetail(_T("I1_ACT"), 5, _T("Active status map to INT1"));
					pRegTable->SetBitDetail(_T("I1_SLP"), 4, _T("Inactive status map to INT1"));
					pRegTable->SetBitDetail(_T("IRQ2_POL"), 3, _T("INT2 polarity"));
					pRegTable->SetBitDetail(_T("IRQ1_POL"), 2, _T("INT1 polarity"));
					pRegTable->SetBitDetail(_T("FSCALE"), _T("Measurement full scale range"), 0x03, 0, BOTH_RW, { 0, 3 }, 0x00);
				}

				pRegTable->SetRegAddr(0x0B);
				pRegTable->SetRegInfo({ 0x00 }, _T("CTRL_CFG3"));
				{
					pRegTable->SetBitDetail(_T("LATCH2_SEL"), _T("INT2 latch duration selection."), 0xF0, 4, BOTH_RW, { 0, 15 }, 0x00);
					pRegTable->SetBitDetail(_T("LATCH1_SEL"), _T("INT1 latch duration selection."), 0x0F, 0, BOTH_RW, { 0, 15 }, 0x00);
				}

				pRegTable->SetRegAddr(0x0D);
				pRegTable->SetRegInfo({ 0x00 }, _T("INACT_TIME_L"));
				{
					pRegTable->SetBitDetail(_T("INACT_TIME"), _T("Inactive Timer"), 0xFF, 0, ONLY_R);
				}

				pRegTable->SetRegAddr(0x10);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("XDATA"), 2);
				{
					pRegTable->SetBitDetail2(_T("XDATA"), _T("X DATA"), _T(""), { 0xF0, 0xFF }, { -4, 4 }, ONLY_R
						, { make_pair(0, 0xF0), make_pair(0, 0xFF) }, { 0, 0 }, TRUE);
				}

				pRegTable->SetRegAddr(0x12);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("YDATA"), 2);
				{
					pRegTable->SetBitDetail2(_T("YDATA"), _T("Y DATA"), _T(""), { 0xF0, 0xFF }, { -4, 4 }, ONLY_R
						, { make_pair(0, 0xF0), make_pair(0, 0xFF) }, { 0, 0 }, TRUE);
				}

				pRegTable->SetRegAddr(0x14);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("ZDATA"), 2);
				{
					pRegTable->SetBitDetail2(_T("ZDATA"), _T("Z DATA"), _T(""), { 0xF0, 0xFF }, { -4, 4 }, ONLY_R
						, { make_pair(0, 0xF0), make_pair(0, 0xFF) }, { 0, 0 }, TRUE);
				}

				pRegTable->SetRegAddr(0x16);
				pRegTable->SetRegInfo({ 0x00 }, _T("FIFO_UNRD"));
				{
					pRegTable->SetBitDetail(_T("FIFO_UNREAD"), _T("FIFO unread number"), 0xFF, 0, ONLY_R);
				}

				pRegTable->SetRegAddr(0x17);
				pRegTable->SetRegInfo({ 0x00 }, _T("FIFO_STS"));
				{
					pRegTable->SetBitDetail(_T("OVN"), 2, _T("Status of FIFO overrun"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("WTM"), 1, _T("Status of FIFO water mark"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("EMPTY"), 0, _T("Status of FIFO empty"), 0, ONLY_R);
				}

				pRegTable->SetRegAddr(0x18);
				pRegTable->SetRegInfo({ 0x00 }, _T("AOI_STS1"));
				{
					pRegTable->SetBitDetail(_T("PO_AOI"), 7, _T("Polling AOI status"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("ZH"), 5, _T("Status of Z-axis"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("ZL"), 4, _T("Status of Z-axis"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("YH"), 3, _T("Status of Y-axis"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("YL"), 2, _T("Status of Y-axis"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("XH"), 1, _T("Status of X-axis"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("XL"), 0, _T("Status of X-axis"), 0, ONLY_R);
				}

				pRegTable->SetRegAddr(0x19);
				pRegTable->SetRegInfo({ 0x00 }, _T("AOI_STS2"));
				{
					pRegTable->SetBitDetail(_T("SIGN_Z"), 2, _T("Signed bit of Z axis"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("SIGN_Y"), 1, _T("Signed bit of Y axis"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("SIGN_X"), 0, _T("Signed bit of X axis"), 0, ONLY_R);
				}

				pRegTable->SetRegAddr(0x1A);
				pRegTable->SetRegInfo({ 0x00 }, _T("AOI_STS1"));
				{
					pRegTable->SetBitDetail(_T("PO_TAP"), 7, _T("Polling tapping status"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("DTAP"), 5, _T("Double tapping status"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("STAP"), 4, _T("Single tapping status"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("SIGN"), 3, _T("Signed bit of the tapping"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("ZTAP"), 2, _T("Status of Z-axis tapping"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("YTAP"), 1, _T("Status of Y-axis tapping"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("XTAP"), 0, _T("Status of X-axis tapping"), 0, ONLY_R);
				}

				pRegTable->SetRegAddr(0x20);
				pRegTable->SetRegInfo({ 0x00 }, _T("IRQ1_MAP"));
				{
					pRegTable->SetBitDetailOne(_T("I1_TIA"), 5, _T("Tap sensing"), _T("Maps tapping status to INT1 pin"));
					pRegTable->SetBitDetailOne(_T("I1_AOI"), 4, _T("AND/OR interrupt"), _T("Maps AOI status to INT1 pin"));
					pRegTable->SetBitDetailOne(_T("I1_OVN"), 3, _T("FIFO overrun"), _T("Maps FIFO full flag to INT1 pin"));
					pRegTable->SetBitDetailOne(_T("I1_WTM"), 2, _T("FIFO water mark"), _T("Maps FIFO WTM flag to INT1 pin"));
					pRegTable->SetBitDetailOne(_T("I1_DRDY"), 1, _T("Data ready"), _T("Maps data ready flag to INT1 pin"));
				}

				pRegTable->SetRegAddr(0x21);
				pRegTable->SetRegInfo({ 0x00 }, _T("IRQ2_MAP"));
				{
					pRegTable->SetBitDetailOne(_T("I2_TIA"), 5, _T("Tap sensing"), _T("Maps tapping status to INT2 pin"));
					pRegTable->SetBitDetailOne(_T("I2_AOI"), 4, _T("AND/OR interrupt"), _T("Maps AOI status to INT2 pin"));
					pRegTable->SetBitDetailOne(_T("I2_OVN"), 3, _T("FIFO overrun"), _T("Maps FIFO full flag to INT2 pin"));
					pRegTable->SetBitDetailOne(_T("I2_WTM"), 2, _T("FIFO water mark"), _T("Maps FIFO WTM flag to INT2 pin"));
					pRegTable->SetBitDetailOne(_T("I2_DRDY"), 1, _T("Data ready"), _T("Maps data ready flag to INT2 pin"));
				}

				pRegTable->SetRegAddr(0x22);
				pRegTable->SetRegInfo({ 0x00 }, _T("FIFO_CFG"));
				{
					pRegTable->SetBitDetail(_T("FIFO_EN"), 7, _T("FIFO function enable"));
					pRegTable->SetBitDetail(_T("FIFO_HR"), 6, _T("FIFO resolution mode"));
					pRegTable->SetBitDetail(_T("FIFO_MODE"), _T("FIFO mode selection"), 0x30, 4, BOTH_RW, { 0, 3 }, 0x00);
					pRegTable->SetBitDetail(_T("FIFO_SKIP"), _T("FIFO skip frames selection"), 0x0C, 2, BOTH_RW, { 0, 3 }, 0x00);
					pRegTable->SetBitDetail(_T("TRIG_SRC"), _T("Trigger mode source selection"), 0x03, 0, BOTH_RW, { 0, 2 }, 0x00);
				}

				pRegTable->SetRegAddr(0x23);
				pRegTable->SetRegInfo({ 0x00 }, _T("FIFO_THS"));
				{
					pRegTable->SetBitDetail(_T("FIFO_THRES"), _T("FIFO water mark threshold"));
				}

				pRegTable->SetRegAddr(0x24);
				pRegTable->SetRegInfo({ 0x00 }, _T("FILTER"));
				{
					pRegTable->SetBitDetail(_T("UNSIGN"), 5, _T("Unsigned format"));
					pRegTable->SetBitDetail(_T("HP_AOI"), 1, _T("AOI HPF enable"));
					pRegTable->SetBitDetail(_T("HP_DATA"), 0, _T("Data register HPF enable"));
				}

				pRegTable->SetRegAddr(0x30);
				pRegTable->SetRegInfo({ 0x00 }, _T("AOI_CFG"));
				{
					pRegTable->SetBitDetail(_T("AOI"), 6, _T("Interrupt AND/OR selection"));
					pRegTable->SetBitDetail(_T("COMP_Z"), _T("Z axis comparator selection"), 0x30, 4, BOTH_RW, { 0, 3 }, 0x00);
					pRegTable->SetBitDetail(_T("COMP_Y"), _T("Y axis comparator selection"), 0x0C, 2, BOTH_RW, { 0, 3 }, 0x00);
					pRegTable->SetBitDetail(_T("COMP_X"), _T("X axis comparator selection"), 0x03, 0, BOTH_RW, { 0, 2 }, 0x00);
				}

				pRegTable->SetRegAddr(0x31);
				pRegTable->SetRegInfo({ 0x00 }, _T("AOI_TIME"));
				{
					pRegTable->SetBitDetail(_T("AOI_ACTIVE_TIME"), _T("AOI active time"));
				}

				pRegTable->SetRegAddr(0x32);
				pRegTable->SetRegInfo({ 0x00 }, _T("AOI_THSX"));
				{
					pRegTable->SetBitDetail(_T("AOI_ACTIVE_THRESH_X"), _T("X axis AOI threshold. (2・s complement w/ signed bit)"));
				}

				pRegTable->SetRegAddr(0x33);
				pRegTable->SetRegInfo({ 0x00 }, _T("AOI_THSY"));
				{
					pRegTable->SetBitDetail(_T("AOI_ACTIVE_THRESH_Y"), _T("Y axis AOI threshold. (2・s complement w/ signed bit)"));
				}

				pRegTable->SetRegAddr(0x34);
				pRegTable->SetRegInfo({ 0x00 }, _T("AOI_THSZ"));
				{
					pRegTable->SetBitDetail(_T("AOI_ACTIVE_THRESH_Z"), _T("Z axis AOI threshold. (2・s complement w/ signed bit)"));
				}

				pRegTable->SetRegAddr(0x35);
				pRegTable->SetRegInfo({ 0x00 }, _T("AOI_HYSX"));
				{
					pRegTable->SetBitDetail(_T("AOI_HYS_X"), _T("X axis hysteresis selection"), 0xF0, 4, BOTH_RW, { 0, 15 }, 0x00);
					pRegTable->SetBitDetail(_T("ZCMP"), 2, _T("Z axis AOI comparison enable"));
					pRegTable->SetBitDetail(_T("YCMP"), 1, _T("Y axis AOI comparison enable"));
					pRegTable->SetBitDetail(_T("XCMP"), 0, _T("X axis AOI comparison enable"));
				}

				pRegTable->SetRegAddr(0x36);
				pRegTable->SetRegInfo({ 0x00 }, _T("AOI_HYSY"));
				{
					pRegTable->SetBitDetail(_T("AOI_HYS_Z"), _T("Z axis hysteresis selection"), 0xF0, 4, BOTH_RW, { 0, 15 }, 0x00);					pRegTable->SetBitDetail(_T("AOI_HYS_Z"), _T("X axis hysteresis selection"), 0xF0, 4, BOTH_RW, { 0, 15 }, 0x00);
					pRegTable->SetBitDetail(_T("AOI_HYS_Y"), _T("Y axis hysteresis selection"), 0x0F, 0, BOTH_RW, { 0, 15 }, 0x00);
				}

				pRegTable->SetRegAddr(0x37);
				pRegTable->SetRegInfo({ 0x00 }, _T("TAP_CFG"));
				{
					pRegTable->SetBitDetail(_T("ZDEN"), 5, _T("Z axis double tapping enable"));
					pRegTable->SetBitDetail(_T("ZSEN"), 4, _T("Z axis single tapping enable"));
					pRegTable->SetBitDetail(_T("YDEN"), 3, _T("Y axis double tapping enable"));
					pRegTable->SetBitDetail(_T("YSEN"), 2, _T("Y axis single tapping enable"));
					pRegTable->SetBitDetail(_T("XDEN"), 1, _T("X axis double tapping enable"));
					pRegTable->SetBitDetail(_T("XSEN"), 0, _T("X axis single tapping enable"));
				}

				pRegTable->SetRegAddr(0x38);
				pRegTable->SetRegInfo({ 0x00 }, _T("TAP_THS"));
				{
					pRegTable->SetBitDetail(_T("TAP_THRESH"), _T("Tapping detected threshold. (2・s complement w/ signed bit)"), 0x7F);
				}

				pRegTable->SetRegAddr(0x39);
				pRegTable->SetRegInfo({ 0x00 }, _T("TAP_LIMIT"));
				{
					pRegTable->SetBitDetail(_T("TAP_LIMIT"), _T("Tapping pulse window (10msec per LSB)"));
				}

				pRegTable->SetRegAddr(0x3A);
				pRegTable->SetRegInfo({ 0x00 }, _T("TAP_LAT"));
				{
					pRegTable->SetBitDetail(_T("TAP_LATENCY"), _T("Tapping quiet window that wrap around the event. (10msec per LSB)"));
				}

				pRegTable->SetRegAddr(0x3B);
				pRegTable->SetRegInfo({ 0x00 }, _T("TAP_WIN"));
				{
					pRegTable->SetBitDetail(_T("TAP_WINDOW"), _T("Tapping interval window between two successive events. (10msec per LSB)"));
				}
			}
			break;

		default: return;
		}

		MappingBitName2Reg();
	}

	uint32_t GetConversionTime(uint16_t version, CRegisterTable* pRegTable)
	{
		uint8_t Reg0x08;
		map<CString, CBitDetail>* pBitDetailMap;
		Reg0x08 = pRegTable->RegInfo.at(0x08).RegCurVal.at(0);
		pBitDetailMap = &pRegTable->BitDetail;

		if (Reg0x08 & 0x02)
		{
			switch (pRegTable->GetBitValue(_T("ODR")))
			{
			case 0: ConversionTime = 1.0 / 6.25;	break;
			case 1: ConversionTime = 1.0 / 12.5;	break;
			case 2: ConversionTime = 1.0 / 25;		break;
			case 3: ConversionTime = 1.0 / 50;		break;
			case 4: ConversionTime = 1.0 / 100;		break;
			case 5: ConversionTime = 1.0 / 200;		break;
			case 6: ConversionTime = 1.0 / 400;		break;
			}
		}
		else
			ConversionTime = 0;

		return (uint32_t)(ConversionTime * 1000 * 1000);
	}
};