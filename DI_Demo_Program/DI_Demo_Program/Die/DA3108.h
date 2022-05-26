#pragma once
#include "Define.h"

class CDA3108 : public CDieInfo {
public:
	CDA3108() {}
	void Init(uint16_t version)
	{
		DieName = _T("DA3108");
		switch (version) {
		case 10000:
			DieDetail.insert(make_pair(10000, CDieDetail()));
			{
				pDieDetail = &DieDetail.at(10000);
				pRegTable = &pDieDetail->RegisterTable;

				pRegTable->DeviceID = 0x10;
				pRegTable->RegInfo[0x00] = CRegInfo({ 0x26 }, _T("SysCtr"));
				{
					pRegTable->BitDetail[_T("SWREST")] = CBitDetail(0x00, 7, _T("Software Reset"));
					pRegTable->BitDetail[_T("ALS_RESET")] = CBitDetail(0x00, 6, _T("ALS Reset"));
					pRegTable->BitDetail[_T("WHITE_EN")] = CBitDetail(0x00, 5, _T("WHITE Enablo"), 0x01);
					pRegTable->BitDetail[_T("ALS_IT")] = CBitDetail(_T("ALS integration time"), _T(""), 0x00, 0x1C, 2, BOTH_RW, make_pair(0, 5), 0x01);
					pRegTable->BitDetail[_T("HS")] = CBitDetail(0x00, 1, _T("ALS Sensitivity Mode"), 0x01);
					pRegTable->BitDetail[_T("SD")] = CBitDetail(0x00, 0, _T("Shut Down Sensor"));
				}

				pRegTable->RegInfo[0x01] = CRegInfo({ 0x80 }, _T("IntFlag"));
				{
					pRegTable->BitDetail[_T("PORINT")] = CBitDetail(0x01, 7, _T("POR INT"));
					pRegTable->BitDetail[_T("DINT")] = CBitDetail(0x01, 3, _T("Data Ready INT"));
					pRegTable->BitDetail[_T("AINT")] = CBitDetail(0x01, 0, _T("ALS INT"));
				}

				pRegTable->RegInfo[0x02] = CRegInfo({ 0x00 }, _T("IntCtr"));
				{
					pRegTable->BitDetail[_T("DPEND")] = CBitDetail(0x02, 7, _T("Suspend Data Ready Function Control"));
					pRegTable->BitDetail[_T("APEND")] = CBitDetail(0x02, 4, _T("Suspend ALS Function Control"));
					pRegTable->BitDetail[_T("DIEND")] = CBitDetail(0x02, 3, _T("Data Ready Interrupt Pin"));
					pRegTable->BitDetail[_T("AIEN")] = CBitDetail(0x02, 0, _T("ALS Interrupt Pin"), 0x01);
				}

				pRegTable->RegInfo[0x03] = CRegInfo({ 0x00 }, _T("Manufacturer ID"));
				pRegTable->RegInfo[0x04] = CRegInfo({ 0x11 }, _T("Product ID"));
				pRegTable->RegInfo[0x05] = CRegInfo({ 0x00 }, _T("Revision ID"));

				pRegTable->RegInfo[0x49] = CRegInfo({ 0x01 }, _T("AlsCtr"));
				{
					pRegTable->BitDetail[_T("ASRC")] = CBitDetail(0x49, 6, _T("Select ADATA Source"));

					pRegTable->BitDetail[_T("APERS")] = CBitDetail(
						_T("ALS conversion cycles"), _T(""),
						0x49, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x01);
				}

				pRegTable->RegInfo[0x4E] = CRegInfo({ 0x00 }, _T("TempAdc"));
				{
					pRegTable->BitDetail[_T("TADC")] = CBitDetail(
						_T("Temperature ADC"), _T(""),
						0x4E, 0xFF, 0, ONLY_R, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x4F] = CRegInfo({ 0x00 }, _T("TempOrg"));
				{
					pRegTable->BitDetail[_T("TORG")] = CBitDetail(
						_T("Temperature Original"), _T(""),
						0x4F, 0xFF, 0, ONLY_R, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x50] = CRegInfo({ 0x00, 0x00 }, _T("AlsCh0"), 2);
				{
					pRegTable->BitDetail[_T("ACH0")] = CBitDetail(
						_T("ALS Channel 0"), _T(""),
						0x50, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x51] = CRegInfo({ 0x00, 0x00 }, _T("AlsCh1"), 2);
				{
					pRegTable->BitDetail[_T("ACH1")] = CBitDetail(
						_T("ALS Channel 1"), _T(""),
						0x51, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x52] = CRegInfo({ 0x00 }, _T("Flag Status"));
				{
					pRegTable->BitDetail[_T("AERR")] = CBitDetail(
						_T("ALS Error"), _T(""),
						0x52, 0x01, 0, ONLY_R, 0x00, 0x00);
				}


				pRegTable->RegInfo[0x54] = CRegInfo({ 0x00, 0x00 }, _T("AlsLowTh"), 2);
				{
					pRegTable->BitDetail[_T("ALTH")] = CBitDetail(
						_T("ALS Low Threshold"), _T(""),
						0x54, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x56] = CRegInfo({ 0xFF, 0xFF }, _T("AlsHighTh"), 2);
				{
					pRegTable->BitDetail[_T("AHTH")] = CBitDetail(
						_T("ALS High Threshold"), _T(""),
						0x56, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0xFF, 0xFF });
				}

				pRegTable->RegInfo[0x65] = CRegInfo({ 0x22 }, _T("RD Control a0"));
				{
					pRegTable->BitDetail[_T("prst_fall_en")]	= CBitDetail(0x65, 0, _T(""), 0x00);
					pRegTable->BitDetail[_T("dc_en")]			= CBitDetail(0x65, 1, _T(""), 0x01);
					pRegTable->BitDetail[_T("dtest_en")]		= CBitDetail(0x65, 2, _T(""), 0x00);
					pRegTable->BitDetail[_T("test_en")]			= CBitDetail(0x65, 3, _T(""), 0x00);
					pRegTable->BitDetail[_T("clkm_vbs")]		= CBitDetail(
						_T(""), _T(""),
						0x65, 0x30, 4, BOTH_RW, make_pair(0, 3), 0x02);
				}


			}

			break;
		default: return;
		}

		MappingBitName2Reg();
	}

	bool CreateEngineerModeTab(DlgSel_ dlgSel, uint16_t version)
	{
		switch (version) {
		case 10000:
		{
			pDieDetail = &DieDetail.at(10000);
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
		case 10000:
			switch (pRegTable->GetBitValue(_T("ALS_IT")))
			{
			case 0x00: ConversionTime = 100; break;
			case 0x01: ConversionTime = 200; break;
			case 0x02: ConversionTime = 400; break;
			case 0x03: ConversionTime = 800; break;
			case 0x04: ConversionTime = 1600; break;
			case 0x05: ConversionTime = 3200; break;
			}
			break;
		}
		return (uint32_t)(ConversionTime * 1000);
	}
};
