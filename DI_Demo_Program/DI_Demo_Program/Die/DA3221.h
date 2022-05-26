#pragma once
#include "Define.h"

class CDA3221 : public CDieInfo {
public:
	CDA3221() {}
	void Init(uint16_t version) 
	{
		DieName = _T("DA3221");
		switch (version)
		{
		case 10700:
			DieDetail.insert(make_pair(10700, CDieDetail()));
			{
				pDieDetail = &DieDetail.at(10700);
				pRegTable = &pDieDetail->RegisterTable;

				pRegTable->DeviceID = 0x1E;
				pRegTable->RegInfo[0x00] = CRegInfo({ 0x00 }, _T("System Control"));
				{
					pRegTable->BitDetail[_T("System Mode")] = CBitDetail(
						_T("System Mode"), _T(""),
						0x00, 0x07, 0, BOTH_RW, 0x00);

					pRegTable->BitDetail[_T("SWRST")] = CBitDetail(0x00, 2, _T("Softwave Reset"));
				}

				pRegTable->RegInfo[0x01] = CRegInfo({ 0x80 }, _T("Interrupt Status"));
				{
					pRegTable->BitDetail[_T("POR")] = CBitDetail(0x01, 7, _T("POR"));
					pRegTable->BitDetail[_T("IR_OV")] = CBitDetail(0x01, 5, _T("IR_OV"));
					pRegTable->BitDetail[_T("OBJ")] = CBitDetail(0x01, 4, _T("OBJ"));
					pRegTable->BitDetail[_T("PS INT")] = CBitDetail(0x01, 1, _T("PS INT"));
					pRegTable->BitDetail[_T("ALS INT")] = CBitDetail(0x01, 0, _T("ALS INT"));
				}

				pRegTable->RegInfo[0x02] = CRegInfo({ 0x88 }, _T("INT Clear Manner"));
				{
					pRegTable->BitDetail[_T("PIEN")] = CBitDetail(0x02, 7, _T("PS Interrupt Enable"), 0x01);
					pRegTable->BitDetail[_T("AIEN")] = CBitDetail(0x02, 3, _T("ALS Interrupt Enable"), 0x01);
					pRegTable->BitDetail[_T("CLR_MNR")] = CBitDetail(0x02, 0, _T("INT Clear Manner"));
				}

				pRegTable->RegInfo[0x03] = CRegInfo({ 0x00 }, _T("Manufacture ID"));
				pRegTable->RegInfo[0x04] = CRegInfo({ 0x06 }, _T("Product ID"));
				pRegTable->RegInfo[0x05] = CRegInfo({ 0x06 }, _T("Revision ID"));

				pRegTable->RegInfo[0x06] = CRegInfo({ 0x00 }, _T("Waiting Time"));
				{
					pRegTable->BitDetail[_T("Waiting Time")] = CBitDetail(
						_T("Waiting Time"), _T(""),
						0x06, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x0A] = CRegInfo({ 0x00, 0x00 }, _T("IR Data"), 2);
				{
					pRegTable->BitDetail[_T("IR Data")] = CBitDetail(
						_T("IR Data"), _T(""),
						0x0A, { 0xFF, 0x03 },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 3) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x0C] = CRegInfo({ 0x00, 0x00 }, _T("ALS Data"), 2);
				{
					pRegTable->BitDetail[_T("ALS Data")] = CBitDetail(
						_T("ALS Data"), _T(""),
						0x0C, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x0E] = CRegInfo({ 0x00, 0x00 }, _T("PS Data"), 2);
				{
					pRegTable->BitDetail[_T("PS Data")] = CBitDetail(
						_T("PS Data"), _T(""),
						0x0E, { 0xFF, 0x03 },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 3) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x10] = CRegInfo({ 0x00 }, _T("ALS Gain"));
				{
					pRegTable->BitDetail[_T("ALS Gain")] = CBitDetail(
						_T("ALS Gain"), _T(""),
						0x10, 0x30, 4, BOTH_RW, make_pair(0, 3), 0x00);
				}

				pRegTable->RegInfo[0x12] = CRegInfo({ 0x00 }, _T("ALS INT Form"));
				{
					pRegTable->BitDetail[_T("ALS_Suspend")] = CBitDetail(0x12, 4, _T("ALS Suspend"));
					pRegTable->BitDetail[_T("ALS_Algo")] = CBitDetail(0x12, 0, _T("ALS_Algo"));
				}

				pRegTable->RegInfo[0x13] = CRegInfo({ 0x03 }, _T("ALS mean time"));
				{
					pRegTable->BitDetail[_T("Edit ALS mean time")] = CBitDetail(
						_T("ALS Mean Time"), _T(""),
						0x13, 0x03, 0, BOTH_RW, make_pair(0, 3), 0x03);
				}

				pRegTable->RegInfo[0x14] = CRegInfo({ 0x01 }, _T("ALS persist"));
				{
					pRegTable->BitDetail[_T("ALS persist")] = CBitDetail(
						_T("ALS persist"), _T(""),
						0x14, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x01);
				}

				pRegTable->RegInfo[0x19] = CRegInfo({ 0x40 }, _T("ALS calibration"));
				{
					pRegTable->BitDetail[_T("ALS calibration")] = CBitDetail(
						_T("ALS calibration"), _T(""),
						0x19, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x40);
				}

				pRegTable->RegInfo[0x1A] = CRegInfo({ 0x00, 0x00 }, _T("ALS Low Threshold"), 2);
				{
					pRegTable->BitDetail[_T("ALS Low Threshold")] = CBitDetail(
						_T("ALS Low Threshold"), _T(""),
						0x1A, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x1C] = CRegInfo({ 0xFF, 0xFF }, _T("ALS High Threshold"), 2);
				{
					pRegTable->BitDetail[_T("ALS High Threshold")] = CBitDetail(
						_T("ALS High Threshold"), _T(""),
						0x1C, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0xFF, 0xFF });
				}


				pRegTable->RegInfo[0x20] = CRegInfo({ 0x04 }, _T("PS Gain"));
				{
					pRegTable->BitDetail[_T("PS Gain")] = CBitDetail(
						_T("PS Gain"), _T(""),
						0x20, 0x0C, 2, BOTH_RW, make_pair(0, 3), 0x01);
				}

				pRegTable->RegInfo[0x21] = CRegInfo({ 0x03 }, _T("PS LED Driver"));
				{
					pRegTable->BitDetail[_T("PS LED Driver")] = CBitDetail(
						_T("PS LED Driver"), _T(""),
						0x21, 0x03, 0, BOTH_RW, make_pair(0, 3), 0x03);
				}

				pRegTable->RegInfo[0x22] = CRegInfo({ 0x01 }, _T("PS INT Form"));
				{
					pRegTable->BitDetail[_T("PS_Suspend")] = CBitDetail(0x22, 4, _T("PS_Suspend"), 0x00);
					pRegTable->BitDetail[_T("PS_algo")] = CBitDetail(0x22, 0, _T("PS_algo"), 0x01);
				}

				pRegTable->RegInfo[0x23] = CRegInfo({ 0x00 }, _T("PS Mean Time"));
				{
					pRegTable->BitDetail[_T("PS Mean Time")] = CBitDetail(
						_T("PS Mean Time"), _T(""),
						0x23, 0x03, 0, BOTH_RW, 0x00);
				}

				pRegTable->RegInfo[0x24] = CRegInfo({ 0x00 }, _T("PS Smart INT"));
				{
					pRegTable->BitDetail[_T("SMRTINT")] = CBitDetail(0x24, 0, _T("SMRTINT"));
				}

				pRegTable->RegInfo[0x25] = CRegInfo({ 0x00 }, _T("PS/IR Integration time"));
				{
					pRegTable->BitDetail[_T("PS / IR Integration time select")] = CBitDetail(
						_T("PS / IR Integration time select"), _T(""),
						0x25, 0x3F, 0, BOTH_RW, 0x00);
				}

				pRegTable->RegInfo[0x26] = CRegInfo({ 0x00 }, _T("PS Persistence"));
				{
					pRegTable->BitDetail[_T("PS Persist")] = CBitDetail(
						_T("PS Persist"), _T(""),
						0x26, 0x3F, 0, BOTH_RW, 0x02);
				}

				pRegTable->RegInfo[0x28] = CRegInfo({ { 0x00, 0x00 } }, _T("PS Calibration"), 2);
				{
					pRegTable->BitDetail[_T("PS_Cali")] = CBitDetail(
						_T("PS Calibration"), _T(""),
						0x28, { 0xFF, 0x01 },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 1) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2A] = CRegInfo({ { 0x00, 0x00 } }, _T("PS Low Threshold"), 2);
				{
					pRegTable->BitDetail[_T("PS Low Threshold")] = CBitDetail(
						_T("PS Low Threshold"), _T(""),
						0x2A, { 0xFF, 0x03 },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 3) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2C] = CRegInfo({ { 0xFF, 0x03 } }, _T("PS High Threshold"), 2);
				{
					pRegTable->BitDetail[_T("PS High Threshold")] = CBitDetail(
						_T("PS High Threshold"), _T(""),
						0x2C, { 0xFF, 0x03 },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 3) }, { 0xFF, 0x03 });
				}
			}

			break;
		case 10800:
			DieDetail.insert(make_pair(10800, CDieDetail()));
			{
				pDieDetail = &DieDetail.at(10800);
				pRegTable = &pDieDetail->RegisterTable;

				pRegTable->DeviceID = 0x1E;
				pRegTable->RegInfo[0x00] = CRegInfo({0x00}, _T("System Control"));
				{
					pRegTable->BitDetail[_T("System Mode")] = CBitDetail(
						_T("System Mode"), _T(""),
						0x00, 0x07, 0, BOTH_RW, 0x00);

					pRegTable->BitDetail[_T("SWRST")] = CBitDetail(0x00, 2, _T("Softwave Reset"));
				}

				pRegTable->RegInfo[0x01] = CRegInfo({0x80}, _T("Interrupt Status"));
				{
					pRegTable->BitDetail[_T("POR")] = CBitDetail(0x01, 7, _T("POR"));
					pRegTable->BitDetail[_T("IR_OV")] = CBitDetail(0x01, 5, _T("IR_OV"));
					pRegTable->BitDetail[_T("OBJ")] = CBitDetail(0x01, 4, _T("OBJ"));
					pRegTable->BitDetail[_T("PS INT")] = CBitDetail(0x01, 1, _T("PS INT"));
					pRegTable->BitDetail[_T("ALS INT")] = CBitDetail(0x01, 0, _T("ALS INT"));
				}

				pRegTable->RegInfo[0x02] = CRegInfo({0x88}, _T("INT Clear Manner"));
				{
					pRegTable->BitDetail[_T("PIEN")] = CBitDetail(0x02, 7, _T("PS Interrupt Enable"), 0x01);
					pRegTable->BitDetail[_T("AIEN")] = CBitDetail(0x02, 3, _T("ALS Interrupt Enable"), 0x01);
					pRegTable->BitDetail[_T("CLR_MNR")] = CBitDetail(0x02, 0, _T("INT Clear Manner"));
				}

				pRegTable->RegInfo[0x03] = CRegInfo({0x00}, _T("Manufacture ID"));
				pRegTable->RegInfo[0x04] = CRegInfo({0x06}, _T("Product ID"));
				pRegTable->RegInfo[0x05] = CRegInfo({0x07}, _T("Revision ID"));

				pRegTable->RegInfo[0x06] = CRegInfo({0x00}, _T("Waiting Time"));
				{
					pRegTable->BitDetail[_T("Waiting Time")] = CBitDetail(
						_T("Waiting Time"), _T(""),
						0x06, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x0A] = CRegInfo({ 0x00, 0x00 }, _T("IR Data"), 2);
				{
					pRegTable->BitDetail[_T("IR Data")] = CBitDetail(
						_T("IR Data"), _T(""),
						0x0A, { 0xFF, 0x03 },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 3) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x0C] = CRegInfo({ 0x00, 0x00 }, _T("ALS Data"), 2);
				{
					pRegTable->BitDetail[_T("ALS Data")] = CBitDetail(
						_T("ALS Data"), _T(""),
						0x0C, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x0E] = CRegInfo({ 0x00, 0x00 }, _T("PS Data"), 2);
				{
					pRegTable->BitDetail[_T("PS Data")] = CBitDetail(
						_T("PS Data"), _T(""),
						0x0E, { 0xFF, 0x03 },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 3) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x10] = CRegInfo({0x00}, _T("ALS Gain"));
				{
					pRegTable->BitDetail[_T("ALS Gain")] = CBitDetail(
						_T("ALS Gain"), _T(""),
						0x10, 0x30, 4, BOTH_RW, make_pair(0, 3), 0x00);
				}

				pRegTable->RegInfo[0x11] = CRegInfo({ 0x00 }, _T("ALS Pipeline depths"));
				{
					pRegTable->BitDetail[_T("Pipe_Lens")] = CBitDetail(0x11, 0, _T("ALS Pipeline"));
				}

				pRegTable->RegInfo[0x12] = CRegInfo({ 0x00 }, _T("ALS INT Form"));
				{
					pRegTable->BitDetail[_T("ALS_Suspend")] = CBitDetail(0x12, 4, _T("ALS Suspend"));
					pRegTable->BitDetail[_T("ALS_Algo")] = CBitDetail(0x12, 0, _T("ALS_Algo"));
				}

				pRegTable->RegInfo[0x13] = CRegInfo({ 0x03 }, _T("ALS mean time"));
				{
					pRegTable->BitDetail[_T("Edit ALS mean time")] = CBitDetail(
						_T("ALS mean time"), _T(""),
						0x13, 0x03, 0, BOTH_RW, make_pair(0, 3), 0x03);
				}

				pRegTable->RegInfo[0x14] = CRegInfo({ 0x01 }, _T("ALS Persist"));
				{
					pRegTable->BitDetail[_T("ALS Persist")] = CBitDetail(
						_T("ALS Persist"), _T(""),
						0x14, 0x3F, 0, BOTH_RW, make_pair(0, 0x3F), 0x01);
				}

				pRegTable->RegInfo[0x19] = CRegInfo({ 0x40 }, _T("ALS calibration"));
				{
					pRegTable->BitDetail[_T("ALS calibration")] = CBitDetail(
						_T("ALS calibration"), _T(""),
						0x19, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x40);
				}

				pRegTable->RegInfo[0x1A] = CRegInfo({ 0x00, 0x00 }, _T("ALS Low Threshold"), 2);
				{
					pRegTable->BitDetail[_T("ALS Low Threshold")] = CBitDetail(
						_T("ALS Low Threshold"), _T(""),
						0x1A, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x1C] = CRegInfo({ 0xFF, 0xFF }, _T("ALS High Threshold"), 2);
				{
					pRegTable->BitDetail[_T("ALS High Threshold")] = CBitDetail(
						_T("ALS High Threshold"), _T(""),
						0x1C, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0xFF, 0xFF });
				}


				pRegTable->RegInfo[0x20] = CRegInfo({ 0x04 }, _T("PS Gain"));
				{
					pRegTable->BitDetail[_T("PS Gain")] = CBitDetail(
						_T("PS Gain"), _T(""),
						0x20, 0x0C, 2, BOTH_RW, 0x01);
				}

				pRegTable->RegInfo[0x21] = CRegInfo({0x03}, _T("PS LED Driver"));
				{
					pRegTable->BitDetail[_T("PS LED Driver")] = CBitDetail(
						_T("PS LED Driver"), _T(""),
						0x21, 0x03, 0, BOTH_RW, 0x03);
				}

				pRegTable->RegInfo[0x22] = CRegInfo({0x01}, _T("PS INT Form"));
				{
					pRegTable->BitDetail[_T("PS_Suspend")] = CBitDetail(0x22, 4, _T("PS_Suspend"), 0x00);
					pRegTable->BitDetail[_T("PS_algo")] = CBitDetail(0x22, 0, _T("PS_algo"), 0x01);
				}

				pRegTable->RegInfo[0x23] = CRegInfo({0x00}, _T("PS Mean Time"));
				{
					pRegTable->BitDetail[_T("PS Mean Time")] = CBitDetail(
						_T("PS Mean Time"), _T(""),
						0x23, 0x03, 0, BOTH_RW, 0x00);
				}

				pRegTable->RegInfo[0x24] = CRegInfo({0x00}, _T("PS Smart INT"));
				{
					pRegTable->BitDetail[_T("SMRTINT")] = CBitDetail(0x24, 0, _T("SMRTINT"));
				}

				pRegTable->RegInfo[0x25] = CRegInfo({0x00}, _T("PS/IR Integration time"));
				{
					pRegTable->BitDetail[_T("PS / IR Integration time select")] = CBitDetail(
						_T("PS / IR Integration time select"), _T(""),
						0x25, 0x3F, 0, BOTH_RW, 0x00);
				}

				pRegTable->RegInfo[0x26] = CRegInfo({0x00}, _T("PS Persistence"));
				{
					pRegTable->BitDetail[_T("PS Persist")] = CBitDetail(
						_T("PS Persist"), _T(""),
						0x26, 0x3F, 0, BOTH_RW, 0x02);
				}

				pRegTable->RegInfo[0x28] = CRegInfo({{0x00, 0x00}}, _T("PS Calibration"), 2);
				{
					pRegTable->BitDetail[_T("PS_Cali")] = CBitDetail(
						_T("PS Calibration"), _T(""),
						0x28, { 0xFF, 0x01 },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 1) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2A] = CRegInfo({{ 0x00, 0x00 }}, _T("PS Low Threshold"), 2);
				{
					pRegTable->BitDetail[_T("PS Low Threshold")] = CBitDetail(
						_T("PS Low Threshold"), _T(""),
						0x2A, { 0xFF, 0x03 },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 3) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2C] = CRegInfo({{ 0xFF, 0xFF }}, _T("PS High Threshold"), 2);
				{
					pRegTable->BitDetail[_T("PS High Threshold")] = CBitDetail(
						_T("PS High Threshold"), _T(""),
						0x2C, { 0xFF, 0x03 },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 3) }, { 0xFF, 0x03 });
				}
			}

			break;
			default: return;
		}

		MappingBitName2Reg();
	}

	uint32_t GetConversionTime(uint16_t version, CRegisterTable* pRegTable)
	{
		uint8_t Reg0x00;
		double ALS_Time = 0;

		map<CString, CBitDetail>* pBitDetailMap;
		Reg0x00 = pRegTable->RegInfo.at(0x00).RegCurVal.at(0);
		pBitDetailMap = &pRegTable->BitDetail;

		ConversionTime = 0;
		switch (version)
		{
		case 10700:
			switch (pRegTable->GetBitValue(_T("Edit ALS mean time")))
			{
			case 0x00: ALS_Time = 8.3;	break;
			case 0x01: ALS_Time = 25;	break;
			case 0x02: ALS_Time = 50;	break;
			case 0x03: ALS_Time = 100;	break;
			}

			switch (Reg0x00)
			{
			case 0x01:
				ConversionTime = ALS_Time;
				ConversionTime += (5 * (double)pRegTable->GetBitValue(_T("Waiting Time")));
				break;
			case 0x02:
				ConversionTime = (5.0 + (double)pRegTable->GetBitValue(_T("PS Mean Time")) * 4.55
					+ ((double)pRegTable->GetBitValue(_T("PS Mean Time")) + 1)
					* ((double)pRegTable->GetBitValue(_T("PS / IR Integration time select")) + 1)
					* 0.0627);

				if (pRegTable->GetBitValue(_T("PS / IR Integration time select")) == 0x00)
					ConversionTime += ((double)pRegTable->GetBitValue(_T("PS Mean Time")) + 1) * 0.0627;

				ConversionTime += (5 * (double)pRegTable->GetBitValue(_T("Waiting Time")));
				break;
			case 0x03:
				ConversionTime = ALS_Time;
				ConversionTime += (5.0 + (double)pRegTable->GetBitValue(_T("PS Mean Time")) * 4.55
					+ ((double)pRegTable->GetBitValue(_T("PS Mean Time")) + 1)
					* ((double)pRegTable->GetBitValue(_T("PS / IR Integration time select")) + 1)
					* 0.0627); 

				if(pRegTable->GetBitValue(_T("PS / IR Integration time select")) == 0x00)
					ConversionTime += ((double)pRegTable->GetBitValue(_T("PS Mean Time")) + 1) * 0.0627;

				ConversionTime += (5 * (double)pRegTable->GetBitValue(_T("Waiting Time")));
				break;
			case 0x05:
				ConversionTime = ALS_Time;
				ConversionTime += (5 * (double)pRegTable->GetBitValue(_T("Waiting Time")));

				ConversionTime *= 2.5;
				break;
			case 0x06:
				ConversionTime = (5.0 + (double)pRegTable->GetBitValue(_T("PS Mean Time")) * 4.55
					+ ((double)pRegTable->GetBitValue(_T("PS Mean Time")) + 1)
					* ((double)pRegTable->GetBitValue(_T("PS / IR Integration time select")) + 1)
					* 0.0627);

				if (pRegTable->GetBitValue(_T("PS / IR Integration time select")) == 0x00)
					ConversionTime += ((double)pRegTable->GetBitValue(_T("PS Mean Time")) + 1) * 0.0627;

				ConversionTime += (5 * (double)pRegTable->GetBitValue(_T("Waiting Time")));

				ConversionTime *= 2.5;

				break;

			case 0x07:	
				ConversionTime = ALS_Time;
				ConversionTime += (5.0 + (double)pRegTable->GetBitValue(_T("PS Mean Time")) * 4.55
					+ ((double)pRegTable->GetBitValue(_T("PS Mean Time")) + 1)
					* ((double)pRegTable->GetBitValue(_T("PS / IR Integration time select")) + 1)
					* 0.0627);

				if (pRegTable->GetBitValue(_T("PS / IR Integration time select")) == 0x00)
					ConversionTime += ((double)pRegTable->GetBitValue(_T("PS Mean Time")) + 1) * 0.0627;

				ConversionTime += (5 * (double)pRegTable->GetBitValue(_T("Waiting Time")));

				ConversionTime *= 2.0;

				ConversionTime += (5.0 + (double)pRegTable->GetBitValue(_T("PS Mean Time")) * 4.55
					+ ((double)pRegTable->GetBitValue(_T("PS Mean Time")) + 1)
					* ((double)pRegTable->GetBitValue(_T("PS / IR Integration time select")) + 1)
					* 0.0627);

				if (pRegTable->GetBitValue(_T("PS / IR Integration time select")) == 0x00)
					ConversionTime += ((double)pRegTable->GetBitValue(_T("PS Mean Time")) + 1) * 0.0627;

				ConversionTime += (5 * (double)pRegTable->GetBitValue(_T("Waiting Time")));

				break;
			default: break;
			}
			break;
		case 10800:
			switch (pRegTable->GetBitValue(_T("Edit ALS mean time")))
			{
			case 0x00: ALS_Time = 8.3;	break;
			case 0x01: ALS_Time = 25;	break;
			case 0x02: ALS_Time = 50;	break;
			case 0x03: ALS_Time = 100;	break;
			}

			switch (Reg0x00)
			{
			case 0x01:
				ConversionTime = ALS_Time;
				ConversionTime += (5 * (double)pRegTable->GetBitValue(_T("Waiting Time")));
				break;
			case 0x02:
				ConversionTime = (5.0 + (double)pRegTable->GetBitValue(_T("PS Mean Time")) * 4.55
					+ ((double)pRegTable->GetBitValue(_T("PS Mean Time")) + 1)
					* ((double)pRegTable->GetBitValue(_T("PS / IR Integration time select")) + 1)
					* 0.0624);

				if (pRegTable->GetBitValue(_T("PS / IR Integration time select")) == 0x00)
					ConversionTime += ((double)pRegTable->GetBitValue(_T("PS Mean Time")) + 1) * 0.0624;

				ConversionTime += (5 * (double)pRegTable->GetBitValue(_T("Waiting Time")));
				break;
			case 0x03:
				ConversionTime = ALS_Time;
				ConversionTime += (5.0 + (double)pRegTable->GetBitValue(_T("PS Mean Time")) * 4.55
					+ ((double)pRegTable->GetBitValue(_T("PS Mean Time")) + 1)
					* ((double)pRegTable->GetBitValue(_T("PS / IR Integration time select")) + 1)
					* 0.0624);

				if (pRegTable->GetBitValue(_T("PS / IR Integration time select")) == 0x00)
					ConversionTime += ((double)pRegTable->GetBitValue(_T("PS Mean Time")) + 1) * 0.0624;

				ConversionTime += (5 * (double)pRegTable->GetBitValue(_T("Waiting Time")));
				break;
			case 0x05:					
				ConversionTime = ALS_Time;
				ConversionTime += (5 * (double)pRegTable->GetBitValue(_T("Waiting Time")));

				ConversionTime *= 2.5;
				break;
			case 0x06:
				ConversionTime = (5.0 + pRegTable->GetBitValue(_T("PS Mean Time")) * 4.55
					+ ((double)pRegTable->GetBitValue(_T("PS Mean Time")) + 1)
					* ((double)pRegTable->GetBitValue(_T("PS / IR Integration time select")) + 1)
					* 0.0624);

				if (pRegTable->GetBitValue(_T("PS / IR Integration time select")) == 0x00)
					ConversionTime += ((double)pRegTable->GetBitValue(_T("PS Mean Time")) + 1) * 0.0624;

				ConversionTime += (5 * (double)pRegTable->GetBitValue(_T("Waiting Time")));

				ConversionTime *= 2.5;

				break;

			case 0x07:
				ConversionTime = ALS_Time;
				ConversionTime += (5.0 + pRegTable->GetBitValue(_T("PS Mean Time")) * 4.55
					+ ((double)pRegTable->GetBitValue(_T("PS Mean Time")) + 1)
					* ((double)pRegTable->GetBitValue(_T("PS / IR Integration time select")) + 1)
					* 0.0624);

				if (pRegTable->GetBitValue(_T("PS / IR Integration time select")) == 0x00)
					ConversionTime += ((double)pRegTable->GetBitValue(_T("PS Mean Time")) + 1) * 0.0624;

				ConversionTime += (5 * (double)pRegTable->GetBitValue(_T("Waiting Time")));

				ConversionTime *= 2.0;

				ConversionTime += (5.0 + pRegTable->GetBitValue(_T("PS Mean Time")) * 4.55
					+ ((double)pRegTable->GetBitValue(_T("PS Mean Time")) + 1)
					* ((double)pRegTable->GetBitValue(_T("PS / IR Integration time select")) + 1)
					* 0.0624);

				if (pRegTable->GetBitValue(_T("PS / IR Integration time select")) == 0x00)
					ConversionTime += ((double)pRegTable->GetBitValue(_T("PS Mean Time")) + 1) * 0.0624;

				ConversionTime += (5 * (double)pRegTable->GetBitValue(_T("Waiting Time")));

				break;
			default: break;
			}
			break;
		}

		return (uint32_t)(ConversionTime * 1000.0);
	}
};
