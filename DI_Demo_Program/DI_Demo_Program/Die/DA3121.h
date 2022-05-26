#pragma once
#include "Define.h"

class CDA3121 : public CDieInfo {
public:
	CDA3121() {}
	void Init(uint16_t version)
	{
		DieName = _T("DA3121");
		switch (version) {
		case 13000:
		{
			DieDetail.insert(make_pair(13000, CDieDetail()));
			{
				pDieDetail = &DieDetail.at(13000);
				pRegTable = &pDieDetail->RegisterTable;

				pRegTable->DeviceID = 0x1C;
				pRegTable->RegInfo[0x00] = CRegInfo({ 0x00 }, _T("System Configuration"));
				{
					pRegTable->BitDetail[_T("SWREST")] = CBitDetail(0x00, 2, _T("Soft Reset"));
					pRegTable->BitDetail[_T("AEN")] = CBitDetail(0x00, 0, _T("ALS Enable"));
				}

				pRegTable->RegInfo[0x01] = CRegInfo({ 0x00 }, _T("Flag Status"));
				{
					pRegTable->BitDetail[_T("INT flag")] = CBitDetail(0x01, 0, _T("ALS INT"));
				}

				pRegTable->RegInfo[0x02] = CRegInfo({ 0x08 }, _T("INT Configuration"));
				{
					pRegTable->BitDetail[_T("ALS INT enable")] = CBitDetail(0x02, 3, _T("ALS Interrupt Pin"), 0x01);
					pRegTable->BitDetail[_T("ALS_Suspend")] = CBitDetail(0x02, 2, _T("ALS Suspend"));
				}

				pRegTable->RegInfo[0x03] = CRegInfo({ 0x01 }, _T("Manufacturer ID"));
				pRegTable->RegInfo[0x04] = CRegInfo({ 0x07 }, _T("Product ID"));
				pRegTable->RegInfo[0x05] = CRegInfo({ 0x06 }, _T("Revision ID"));

				pRegTable->RegInfo[0x06] = CRegInfo({ 0x00 }, _T("ALS Waiting"));
				{
					pRegTable->BitDetail[_T("ALS Waiting")] = CBitDetail(
						_T("ALS Waiting Time"), _T(""),
						0x06, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x07] = CRegInfo({ 0x01 }, _T("ALS Configuration"));
				{
					pRegTable->BitDetail[_T("Gain selection")] = CBitDetail(
						_T("Gain selection"), _T(""),
						0x07, 0x06, 1, BOTH_RW, make_pair(0, 3), 0x00);

					pRegTable->BitDetail[_T("Ext_Gain")] = CBitDetail(0x07, 0, _T("Ext_Gain"), 0x01);
				}

				pRegTable->RegInfo[0x08] = CRegInfo({ 0x01 }, _T("ALS Persist"));
				{
					pRegTable->BitDetail[_T("ALS persist")] = CBitDetail(
						_T("ALS persist"), _T(""),
						0x08, 0x3F, 0, BOTH_RW, make_pair(0, 0x3F), 0x01);
				}

				pRegTable->RegInfo[0x09] = CRegInfo({ 0x00 }, _T("ALS Mean Time"));
				{
					pRegTable->BitDetail[_T("ALS mean time")] = CBitDetail(
						_T("ALS mean time"), _T(""),
						0x09, 0x0F, 0, BOTH_RW, make_pair(0, 0x0F), 0x00);
				}

				pRegTable->RegInfo[0x0A] = CRegInfo({ 0x00 }, _T("A-dummy"));
				{
					pRegTable->BitDetail[_T("ALS dummy time slot")] = CBitDetail(
						_T("ALS dummy time slot"), _T(""),
						0x0A, 0xFF, 0, BOTH_RW, make_pair(0, 0xFF), 0x00);
				}

				pRegTable->RegInfo[0x22] = CRegInfo({ 0x00, 0x00 }, _T("ALS Data"), 2);
				{
					pRegTable->BitDetail[_T("ALS Data")] = CBitDetail(
						_T("ALS Data"), _T(""),
						0x22, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x30] = CRegInfo({ 0x00, 0x00 }, _T("ALS Low Threshold"), 2);
				{
					pRegTable->BitDetail[_T("Low Threshold")] = CBitDetail(
						_T("Low Threshold"), _T(""),
						0x30, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x32] = CRegInfo({ 0xFF, 0xFF }, _T("ALS High Threshold"), 2);
				{
					pRegTable->BitDetail[_T("High Threshold")] = CBitDetail(
						_T("High Threshold"), _T(""),
						0x32, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0xFF, 0xFF });
				}

				pRegTable->RegInfo[0x34] = CRegInfo({ 0x40 }, _T("ALS Calibration"));
				{
					pRegTable->BitDetail[_T("Calibration")] = CBitDetail(
						_T("Calibration"), _T(""),
						0x34, 0xFF, 0, BOTH_RW, make_pair(0, 0xFF), 0x40);
				}
			}
			break;
		}
		case 17000:
		{
			DieDetail.insert(make_pair(17000, CDieDetail()));
			{
				pDieDetail = &DieDetail.at(17000);
				pRegTable = &pDieDetail->RegisterTable;

				pRegTable->DeviceID = 0x1C;
				pRegTable->RegInfo[0x00] = CRegInfo({ 0x00 }, _T("System Configuration"));
				{
					pRegTable->BitDetail[_T("SWREST")] = CBitDetail(0x00, 2, _T("Soft Reset"));
					pRegTable->BitDetail[_T("AEN")] = CBitDetail(0x00, 0, _T("ALS Enable"));
				}

				pRegTable->RegInfo[0x01] = CRegInfo({ 0x00 }, _T("Flag Status"));
				{
					pRegTable->BitDetail[_T("INT flag")] = CBitDetail(0x01, 0, _T("ALS INT"));
				}

				pRegTable->RegInfo[0x02] = CRegInfo({ 0x08 }, _T("INT Configuration"));
				{
					pRegTable->BitDetail[_T("ALS INT enable")] = CBitDetail(0x02, 3, _T("ALS Interrupt Pin"), 0x01);
					pRegTable->BitDetail[_T("ALS_Suspend")] = CBitDetail(0x02, 2, _T("ALS Suspend"));
				}

				pRegTable->RegInfo[0x03] = CRegInfo({ 0x01 }, _T("Manufacturer ID"));
				pRegTable->RegInfo[0x04] = CRegInfo({ 0x07 }, _T("Product ID"));
				pRegTable->RegInfo[0x05] = CRegInfo({ 0x06 }, _T("Revision ID"));

				pRegTable->RegInfo[0x06] = CRegInfo({ 0x00 }, _T("ALS Waiting"));
				{
					pRegTable->BitDetail[_T("ALS Waiting")] = CBitDetail(
						_T("ALS Waiting Time"), _T(""),
						0x06, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x07] = CRegInfo({ 0x01 }, _T("ALS Configuration"));
				{
					pRegTable->BitDetail[_T("Gain selection")] = CBitDetail(
						_T("Gain selection"), _T(""),
						0x07, 0x06, 1, BOTH_RW, make_pair(0, 3), 0x00);

					pRegTable->BitDetail[_T("Ext_Gain")] = CBitDetail(0x07, 0, _T("Ext_Gain"), 0x01);
				}

				pRegTable->RegInfo[0x08] = CRegInfo({ 0x01 }, _T("ALS Persist"));
				{
					pRegTable->BitDetail[_T("ALS persist")] = CBitDetail(
						_T("ALS persist"), _T(""),
						0x08, 0x3F, 0, BOTH_RW, make_pair(0, 0x3F), 0x01);
				}

				pRegTable->RegInfo[0x09] = CRegInfo({ 0x00 }, _T("ALS Mean Time"));
				{
					pRegTable->BitDetail[_T("ALS mean time")] = CBitDetail(
						_T("ALS mean time"), _T(""),
						0x09, 0x0F, 0, BOTH_RW, make_pair(0, 0x0F), 0x00);
				}

				pRegTable->RegInfo[0x0A] = CRegInfo({ 0x00 }, _T("A-dummy"));
				{
					pRegTable->BitDetail[_T("ALS dummy time slot")] = CBitDetail(
						_T("ALS dummy time slot"), _T(""),
						0x0A, 0xFF, 0, BOTH_RW, make_pair(0, 0xFF), 0x00);
				}

				pRegTable->RegInfo[0x22] = CRegInfo({ 0x00, 0x00 }, _T("ALS Data"), 2);
				{
					pRegTable->BitDetail[_T("ALS Data")] = CBitDetail(
						_T("ALS Data"), _T(""),
						0x22, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x30] = CRegInfo({ 0x00, 0x00 }, _T("ALS Low Threshold"), 2);
				{
					pRegTable->BitDetail[_T("Low Threshold")] = CBitDetail(
						_T("Low Threshold"), _T(""),
						0x30, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x32] = CRegInfo({ 0xFF, 0xFF }, _T("ALS High Threshold"), 2);
				{
					pRegTable->BitDetail[_T("High Threshold")] = CBitDetail(
						_T("High Threshold"), _T(""),
						0x32, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0xFF, 0xFF });
				}

				pRegTable->RegInfo[0x34] = CRegInfo({ 0x40 }, _T("ALS Calibration"));
				{
					pRegTable->BitDetail[_T("Calibration")] = CBitDetail(
						_T("Calibration"), _T(""),
						0x34, 0xFF, 0, BOTH_RW, make_pair(0, 0xFF), 0x40);
				}
			}
			break;
		}
		default: return;
		}

		MappingBitName2Reg();
	}

	bool CreateEngineerModeTab(DlgSel_ dlgSel, uint16_t version)
	{
		switch (version) {
		case 13000:
		{
			pDieDetail = &DieDetail.at(13000);
			pDieDetail->DlgStyle[dlgSel] = PAGE_STYLE1;
			pDieDetail->DlgName[dlgSel] = _T("ENG");
			pCtrlInfo[dlgSel] = &pDieDetail->CtrlInfo[dlgSel];
			{
				//TODO: add engineer mode UI.
			}
		}
		break;
		case 17000:
		{
			pDieDetail = &DieDetail.at(17000);
			pDieDetail->DlgStyle[dlgSel] = PAGE_STYLE1;
			pDieDetail->DlgName[dlgSel] = _T("ENG");
			pCtrlInfo[dlgSel] = &pDieDetail->CtrlInfo[dlgSel];
			{
				//TODO: add engineer mode UI.
			}
		}
		break;
		default: return false;
		}
		return true;
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
		case 13000:
			if (Reg0x00 & pBitDetailMap->at(_T("AEN")).BitMask.at(0))
			{
				switch (pRegTable->GetBitValue(_T("Gain selection")))
				{
				case 0:	ConversionTime = 6.53;  break;
				case 1:	ConversionTime = 7.53;  break;
				case 2:	ConversionTime = 11.53; break;
				case 3:	ConversionTime = 22.50; break;
				}
				ConversionTime += ((double)pRegTable->GetBitValue(_T("ALS dummy time slot")) * 0.1);
				ConversionTime *= ((double)pRegTable->GetBitValue(_T("ALS mean time")) + 1);
				ConversionTime += ((double)pRegTable->GetBitValue(_T("ALS Waiting")) * 2.0);
			}
			break;
		case 17000:
			if (Reg0x00 & pBitDetailMap->at(_T("AEN")).BitMask.at(0))
			{
				switch (pRegTable->GetBitValue(_T("Gain selection")))
				{
				case 0:	ConversionTime = 6.53;  break;
				case 1:	ConversionTime = 8.53;  break;
				case 2:	ConversionTime = 12.53; break;
				case 3:	ConversionTime = 26.00; break;
				}
				ConversionTime += ((double)pRegTable->GetBitValue(_T("ALS dummy time slot")) * 0.1);
				ConversionTime *= ((double)pRegTable->GetBitValue(_T("ALS mean time")) + 1);
				ConversionTime += ((double)pRegTable->GetBitValue(_T("ALS Waiting")) * 2.0);
			}
			break;
		}
		return (uint32_t)(ConversionTime * 1000);
	}
};
