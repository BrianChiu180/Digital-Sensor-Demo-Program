#pragma once
#include "Define.h"

class CDA3211 : public CDieInfo {
public:
	CDA3211() {}
	void Init(uint16_t version) 
	{
		DieName = _T("DA3211");
		switch (version)
		{
		case 11100:
			DieDetail.insert(make_pair(11100, CDieDetail()));
			{
				pDieDetail = &DieDetail.at(11100);
				pRegTable = &pDieDetail->RegisterTable;

				pRegTable->DeviceID = 0x1E;

				pRegTable->RegInfo[0x00] = CRegInfo({ 0x00 }, _T("System Configuration"));
				{
					pRegTable->BitDetail[_T("System Mode")] = CBitDetail(
						_T("System Mode"), _T(""),
						0x00, 0x07, 0, BOTH_RW, 0x00);

					pRegTable->BitDetail[_T("SWRST")] = CBitDetail(0x00, 2, _T("Softwave Reset"));
				}

				pRegTable->RegInfo[0x01] = CRegInfo({ 0x00 }, _T("INT Status"));
				{
					pRegTable->BitDetail[_T("PS Int")] = CBitDetail(0x01, 1, _T("PS INT"));
					pRegTable->BitDetail[_T("ALS Int")] = CBitDetail(0x01, 0, _T("ALS INT"));
				}

				pRegTable->RegInfo[0x02] = CRegInfo({ 0x00 }, _T("Manufacture ID"));
				pRegTable->RegInfo[0x03] = CRegInfo({ 0x00 }, _T("Product ID"));
				pRegTable->RegInfo[0x04] = CRegInfo({ 0x02 }, _T("Revision ID"));

				pRegTable->RegInfo[0x0A] = CRegInfo({ 0x00, 0x00 }, _T("IR Data"), 2);
				{
					pRegTable->BitDetail[_T("IR Data")] = CBitDetail(
						_T("IR Data"), _T(""),
						0x0A, { 0x03, 0xFF },
						{ 0, 3 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 3) }, { 0x00, 0x00 });

					pRegTable->BitDetail[_T("IR overflow")] = CBitDetail(0x0A, 7, _T("IR_OV"), 0x00, ONLY_R);
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
						0x0E, { 0x1F, 0x3F },
						{ 0, 5 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 3) }, { 0x00, 0x00 });

					pRegTable->BitDetail[_T("Object detect")] = CBitDetail(0x0E, 7, _T("OBJ"), 0x00, ONLY_R);
					//pRegTable->BitDetail[_T("IR overflow")] = CBitDetail(0x0E, 6, _T("IR_OV"));
					//pRegTable->BitDetail[_T("Object detect")] = CBitDetail(0x0F, 7, _T("OBJ"));
					//pRegTable->BitDetail[_T("IR overflow")] = CBitDetail(0x0F, 7, _T("IR_OV"));
				}

				pRegTable->RegInfo[0x10] = CRegInfo({ 0x00 }, _T("ALS Configuration"));
				{
					pRegTable->BitDetail[_T("ALS Gain")] = CBitDetail(
						_T("ALS Gain"), _T(""),
						0x10, 0x70, 4, BOTH_RW, make_pair(0, 7), 0x00);

					pRegTable->BitDetail[_T("ALS persist")] = CBitDetail(
						_T("ALS Persist"), _T(""),
						0x10, 0x03, 0, BOTH_RW, make_pair(0, 3), 0x00);
				}

				pRegTable->RegInfo[0x12] = CRegInfo({ 0x00 }, _T("ALS INT Form"));
				{
					pRegTable->BitDetail[_T("ALS_Algo")] = CBitDetail(0x12, 0, _T("ALS_Algo"));
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


				pRegTable->RegInfo[0x20] = CRegInfo({ 0xC1 }, _T("PS Configuration"));
				{
					pRegTable->BitDetail[_T("PS / IR Integrated time select")] = CBitDetail(
						_T("PS IT"), _T(""),
						0x20, 0xC0, 6, BOTH_RW, make_pair(0, 3), 0x03);

					pRegTable->BitDetail[_T("PS Gain select")] = CBitDetail(
						_T("PS Gain"), _T(""),
						0x20, 0x30, 4, BOTH_RW, make_pair(0, 3), 0x00);

					pRegTable->BitDetail[_T("PS LED waiting time")] = CBitDetail(
						_T("PS LED waiting time"), _T(""),
						0x20, 0x0C, 2, BOTH_RW, make_pair(0, 3), 0x00);

					pRegTable->BitDetail[_T("PS persist")] = CBitDetail(
						_T("PS persist"), _T(""),
						0x20, 0x03, 0, BOTH_RW, make_pair(0, 3), 0x01);
				}

				pRegTable->RegInfo[0x21] = CRegInfo({ 0x33 }, _T("PS LED Driver"));
				{
					pRegTable->BitDetail[_T("Led PWM Test")] = CBitDetail(
						_T("Led PWM Test"), _T(""),
						0x21, 0xC0, 6, BOTH_RW, make_pair(0, 3), 0x00);

					pRegTable->BitDetail[_T("Led Pulse select")] = CBitDetail(
						_T("Led Pulse select"), _T(""),
						0x21, 0x30, 4, BOTH_RW, make_pair(0, 3), 0x03);

					pRegTable->BitDetail[_T("Max LED driver ratio")] = CBitDetail(
						_T("Max LED driver ratio"), _T(""),
						0x21, 0x03, 0, BOTH_RW, make_pair(0, 3), 0x03);
				}

				pRegTable->RegInfo[0x22] = CRegInfo({ 0x00 }, _T("PS INT Form"));
				{
					pRegTable->BitDetail[_T("PS_Algo")] = CBitDetail(0x22, 0, _T("PS_algo"));
				}

				pRegTable->RegInfo[0x2A] = CRegInfo({ { 0x00, 0x80 } }, _T("PS Low Threshold"), 2);
				{
					pRegTable->BitDetail[_T("PS Low Threshold")] = CBitDetail(
						_T("PS Low Threshold"), _T(""),
						0x2A, { 0x07, 0xFF },
						{ 0, 3 }, BOTH_RW,
						{ make_pair(0, 7), make_pair(0, 255) }, { 0x00, 0x80 });
				}

				pRegTable->RegInfo[0x2C] = CRegInfo({ { 0x00, 0x80 } }, _T("PS High Threshold"), 2);
				{
					pRegTable->BitDetail[_T("PS High Threshold")] = CBitDetail(
						_T("PS High Threshold"), _T(""),
						0x2C, { 0x07, 0xFF },
						{ 0, 3 }, BOTH_RW,
						{ make_pair(0, 7), make_pair(0, 255) }, { 0x00, 0x80 });
				}

				//RD Mode (0x30 ~ 0x3F)
			}

			break;
		default: return;
		}

		MappingBitName2Reg();
	}

	uint32_t GetConversionTime(uint16_t version, CRegisterTable* pRegTable)
	{
		uint8_t Reg0x00;

		map<CString, CBitDetail>* pBitDetailMap;
		Reg0x00 = pRegTable->RegInfo.at(0x00).RegCurVal.at(0);
		pBitDetailMap = &pRegTable->BitDetail;

		ConversionTime = 0;
		switch (version)
		{
		case 11100:
			switch (Reg0x00)
			{
			case 0x01: ConversionTime = 50.0; break;
			case 0x02:
				switch (pRegTable->GetBitValue(_T("PS LED waiting time")))
				{
				case 0x00: ConversionTime = 50.0; break;
				case 0x01: ConversionTime = 100.0; break;
				case 0x02: ConversionTime = 200.0; break;
				case 0x03: ConversionTime = 400.0; break;
				}
				break;
			case 0x03:
				switch (pRegTable->GetBitValue(_T("PS LED waiting time")))
				{
				case 0x00: ConversionTime = 100.0; break;
				case 0x01: ConversionTime = 200.0; break;
				case 0x02: ConversionTime = 400.0; break;
				case 0x03: ConversionTime = 800.0; break;
				}
				break;
			case 0x05: case 0x06: ConversionTime = 125.0; break;
			case 0x07: ConversionTime = 225.0; break;
			default: break;
			}
			break;
		default: break;
		}

		return (uint32_t)(ConversionTime * 1000.0);
	}
};
