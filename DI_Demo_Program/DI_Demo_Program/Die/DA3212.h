#pragma once
#include "Define.h"

class CDA3212 : public CDieInfo {
public:
	CDA3212() {}
	void Init(uint16_t version) 
	{
		DieName = _T("DA3212");
		switch (version)
		{
		case 20311:	//2.3B
			DieDetail.insert(make_pair(20311, CDieDetail()));
			{
				pDieDetail = &DieDetail.at(20311);
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
		case 20500:
			DieDetail.insert(make_pair(20500, CDieDetail()));
			{
				pDieDetail = &DieDetail.at(20500);
				pRegTable = &pDieDetail->RegisterTable;

				pRegTable->DeviceID = 0x1E;

				pRegTable->SetRegAddr(0x00);
				pRegTable->SetRegInfo({ 0x00 }, _T("System Configuration"));
				{
					pRegTable->SetBitDetail(_T("System Mode"), _T("System Mode"), _T(""), 0x07);

					pRegTable->SetBitDetail(_T("SWRST"), 2, _T("Softwave Reset"));
				}

				pRegTable->SetRegAddr(0x01);
				pRegTable->SetRegInfo({ 0x00 }, _T("INT Status"));
				{
					pRegTable->SetBitDetail(_T("PS INT"), 1, _T("PS INT"));
					pRegTable->SetBitDetail(_T("ALS INT"), 0, _T("ALS INT"));
				}

				pRegTable->SetRegAddr(0x02);
				pRegTable->SetRegInfo({ 0x00 }, _T("INT Clear Manner"));
				{
					pRegTable->SetBitDetail(_T("Clear Manner"), 0, _T("Clear Manner"));
				}

				pRegTable->RegInfo[0x03] = CRegInfo({ 0x03 }, _T("Manufacture ID"));
				pRegTable->RegInfo[0x04] = CRegInfo({ 0x02 }, _T("Product ID"));
				pRegTable->RegInfo[0x05] = CRegInfo({ 0x02 }, _T("Revision ID"));

				pRegTable->SetRegAddr(0x0A);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("IR DATA"), 2);
				{
					pRegTable->SetBitDetail(_T("IR overflow"), 7, _T("IR overflow"));

					pRegTable->SetBitDetail2(_T("IR DATA"), _T("IR DATA"), _T(""),
						{ 0x03, 0xFF }, { 0, 2 }, ONLY_R, { make_pair(0, 3), make_pair(0, 255) });

				}

				pRegTable->SetRegAddr(0x0C);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("ALS DATA"), 2);
				{
					pRegTable->SetBitDetail2(_T("ALS DATA"), _T("ALS DATA"));
				}

				pRegTable->SetRegAddr(0x0E);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("PS DATA"), 2);
				{
					pRegTable->SetBitDetail(_T("Object detect"), 7, _T("Object detect"));

					pRegTable->SetBitDetail2(_T("PS DATA"), _T("PS DATA"), _T(""),
						{ 0x0F, 0x3F }, { 0, 4 }, ONLY_R, { make_pair(0, 0x0F), make_pair(0, 0x3F) });
				}

				pRegTable->SetRegAddr(0x10);
				pRegTable->SetRegInfo({ 0x00 }, _T("ALS Configuration"));
				{
					pRegTable->SetBitDetail(_T("ALS Gain"), _T("ALS Gain"), 0x30, 4, BOTH_RW, { 0, 0x03 });
					pRegTable->SetBitDetail(_T("ALS persist"), _T("ALS persist"), 0x0F, 0, BOTH_RW, { 0, 0x0F });
				}

				pRegTable->SetRegAddr(0x11);
				pRegTable->SetRegInfo({ 0x01 }, _T("ALS pipeline"));
				{
					pRegTable->SetBitDetail(_T("ALS pipeline length"), _T("ALS pipeline length")
						, 0x03, 0, BOTH_RW, { 0, 0x03 }, 0x01);
				}

				pRegTable->SetRegAddr(0x12);
				pRegTable->SetRegInfo({ 0x00 }, _T("ALS INT Form"));
				{
					pRegTable->SetBitDetail(_T("ALS_Suspend"), 4, _T("ALS_Suspend"));
					pRegTable->SetBitDetail(_T("ALS_Algo"), 0, _T("ALS_Algo"));
				}

				pRegTable->SetRegAddr(0x13);
				pRegTable->SetRegInfo({ 0x03 }, _T("ALS mean time"));
				{
					pRegTable->SetBitDetail(_T("ALS mean time"), _T("Edit ALS mean time")
						, 0x03, 0, BOTH_RW, { 0, 0x03 }, 0x03);
				}

				pRegTable->SetRegAddr(0x19);
				pRegTable->SetRegInfo({ 0x40 }, _T("ALS calibration"));
				{
					pRegTable->SetBitDetail(_T("ALS calibration"), _T("ALS calibration"), _T("")
						, 0xFF, 0, BOTH_RW, { 0, 0xFF }, 0x40);
				}

				pRegTable->SetRegAddr(0x1A);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("ALS Threshold low"), 2);
				{
					pRegTable->SetBitDetail2(_T("ALS Threshold low"), _T("ALS Threshold low"));
				}

				pRegTable->SetRegAddr(0x1C);
				pRegTable->SetRegInfo({ 0xFF, 0xFF }, _T("ALS Threshold high"), 2);
				{
					pRegTable->SetBitDetail2(_T("ALS Threshold high"), { 0xFF, 0xFF }, _T("ALS Threshold high"));
				}

				pRegTable->SetRegAddr(0x20);
				pRegTable->SetRegInfo({ 0x05 }, _T("PS Configuration"));
				{
					pRegTable->SetBitDetail(_T("PS / IR Integrated time select"), _T("PS / IR IT"), 0xF0, 4, BOTH_RW, { 0, 0x0F });
					pRegTable->SetBitDetail(_T("PS Gain"), _T("PS Gain"), 0x0C, 2, BOTH_RW, { 0, 0x03 }, 0x01);
					pRegTable->SetBitDetail(_T("PS persist"), _T("PS Persist"), 0x03, 0, BOTH_RW, { 0, 0x03 }, 0x01);
				}

				pRegTable->SetRegAddr(0x21);
				pRegTable->SetRegInfo({ 0x13 }, _T("PS LED DRIVER"));
				{
					pRegTable->SetBitDetail(_T("Led DC Test"), _T("Led DC Test"), 0xC0, 6, BOTH_RW, { 0, 0x02 });
					pRegTable->SetBitDetail(_T("LED Pulse"), _T("Led Pulse"), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x01);
					pRegTable->SetBitDetail(_T("LED driver ratio"), _T("Led Drv Ratio"), 0x03, 0, BOTH_RW, { 0, 0x03 }, 0x03);
				}

				pRegTable->SetRegAddr(0x22);
				pRegTable->SetRegInfo({ 0x01 }, _T("PS INT Form"));
				{
					pRegTable->SetBitDetail(_T("PS_Suspend"), 4, _T("PS Suspend"));
					pRegTable->SetBitDetail(_T("PS_Algo"), 0, _T("PS Algo"), 0x01);
				}

				pRegTable->SetRegAddr(0x23);
				pRegTable->SetRegInfo({ 0x00 }, _T("PS mean time"));
				{
					pRegTable->SetBitDetail(_T("PS mean time"), _T("PS Mean Time"), 0x03, 0, BOTH_RW, { 0, 0x03 });
				}

				pRegTable->SetRegAddr(0x24);
				pRegTable->SetRegInfo({ 0x00 }, _T("PS LED waiting"));
				{
					pRegTable->SetBitDetail(_T("PS LED waiting"), _T("PS LED waiting"), 0x3F, 0, BOTH_RW, { 0, 0x3F });
				}

				pRegTable->SetRegAddr(0x28);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("PS calibration"), 2);
				{
					pRegTable->SetBitDetail2(_T("PS calibration"), _T("PS Calibration"), _T(""),
						{ 0x01, 0xFF }, { 0, 1 }, ONLY_R, { make_pair(0, 1), make_pair(0, 255) });
				}

				pRegTable->SetRegAddr(0x2A);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("PS Threshold low"), 2);
				{
					pRegTable->SetBitDetail2(_T("PS Threshold low"), _T("PS Threshold low"), _T(""),
						{ 0x03, 0xFF }, { 0, 2 }, ONLY_R, { make_pair(0, 0x03), make_pair(0, 0xFF) });
				}

				pRegTable->SetRegAddr(0x2C);
				pRegTable->SetRegInfo({ 0x00, 0x80 }, _T("PS Threshold high"), 2);
				{
					pRegTable->SetBitDetail2(_T("PS Threshold high"), _T("PS Threshold high"), _T(""),
						{ 0x03, 0xFF }, { 0, 2 }, ONLY_R, { make_pair(0, 0x03), make_pair(0, 0xFF) }, { 0x00, 0x80 });
				}

				//RD Mode
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
		case 20311:
		case 20500:
			switch (Reg0x00)
			{
			case 0x01: ConversionTime = 100.0; break;
			case 0x02:
				ConversionTime = pRegTable->GetBitValue(_T("PS mean time")) *
					(12.5 + pRegTable->GetBitValue(_T("PS LED waiting")) * 12.5);
				break;
			case 0x03:
				ConversionTime = 100 + pRegTable->GetBitValue(_T("PS mean time")) *
					(12.5 + pRegTable->GetBitValue(_T("PS LED waiting")) * 12.5);
				break;
			case 0x05: ConversionTime = 250.0; break;
			case 0x06: ConversionTime = 2.5 * (pRegTable->GetBitValue(_T("PS mean time")) * 12.5); break;
			case 0x07: ConversionTime = 2.5 * (100 + pRegTable->GetBitValue(_T("PS mean time")) * 12.5);; break;
			default: break;
			}
			break;
		default: break;
		}

		return (uint32_t)(ConversionTime * 1000.0);
	}
};
