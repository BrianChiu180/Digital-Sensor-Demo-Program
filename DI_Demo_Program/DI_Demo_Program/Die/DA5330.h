#pragma once
#include "Define.h"

class CDA5330 : public CDieInfo {
public:
	CDA5330() {}
	void Init(uint16_t version)
	{
		DieName = _T("DA5330");
		switch (version)
		{
		case 12000:
			DieDetail.insert(make_pair(12000, CDieDetail()));
			{
				pDieDetail = &DieDetail.at(12000);
				pRegTable = &pDieDetail->RegisterTable;

				pRegTable->DeviceID = 0x1C;
				pRegTable->RegInfo[0x00] = CRegInfo({ 0x00 }, _T("System Control"));
				{
					pRegTable->BitDetail[_T("MEN")]		= CBitDetail(0x00, 3, _T("MGS Enable"));
					pRegTable->BitDetail[_T("SWRST")]	= CBitDetail(0x00, 2, _T("Software Reset"));
					pRegTable->BitDetail[_T("PEN")]		= CBitDetail(0x00, 1, _T("PS Enable"));
					pRegTable->BitDetail[_T("AEN")]		= CBitDetail(0x00, 0, _T("ALS Enable"));
				}

				pRegTable->RegInfo[0x01] = CRegInfo({ 0x80 }, _T("Interrupt Flag"));
				{
					pRegTable->BitDetail[_T("PORINT")]	= CBitDetail(0x01, 7, _T("POR INT"));
					pRegTable->BitDetail[_T("MGSINT")]	= CBitDetail(0x01, 6, _T("MGS INT"));
					pRegTable->BitDetail[_T("ERRFLAG")] = CBitDetail(0x01, 5, _T("ERROR FLAG"));
					pRegTable->BitDetail[_T("OBJ")]		= CBitDetail(0x01, 4, _T("OBJ"));
					pRegTable->BitDetail[_T("PSINT")]	= CBitDetail(0x01, 1, _T("PS INT"));
					pRegTable->BitDetail[_T("ALINT")]	= CBitDetail(0x01, 0, _T("ALS INT"));
				}

				pRegTable->RegInfo[0x02] = CRegInfo({ 0xAA }, _T("Interrupt Control"));
				{
					pRegTable->BitDetail[_T("PIEN")] = CBitDetail(0x02, 7, _T("PS Polling"), 0x01);
					pRegTable->BitDetail[_T("PSPEND")] = CBitDetail(0x02, 6, _T("PS suspend"));
					pRegTable->BitDetail[_T("PSMODE")] = CBitDetail(0x02, 5, _T("PS Interrupt Mode"), 0x01);
					pRegTable->BitDetail[_T("PSACC")] = CBitDetail(0x02, 4, _T("PS Smart INT"));
					pRegTable->BitDetail[_T("AIEN")] = CBitDetail(0x02, 3, _T("ALS Polling"), 0x01);
					pRegTable->BitDetail[_T("ALPEND")] = CBitDetail(0x02, 2, _T("ALS suspend"));
					pRegTable->BitDetail[_T("MGSIEN")] = CBitDetail(0x02, 1, _T("MIEN Polling"), 0x01);
				}

				pRegTable->RegInfo[0x03] = CRegInfo({ 0x02 }, _T("Manufacturer ID"));
				pRegTable->RegInfo[0x04] = CRegInfo({ 0x0A }, _T("Product ID"));
				pRegTable->RegInfo[0x05] = CRegInfo({ 0x02 }, _T("Revision ID"));

				pRegTable->RegInfo[0x06] = CRegInfo({ 0x01 }, _T("Waiting Time"));
				{
					pRegTable->BitDetail[_T("WUnit")] = CBitDetail(0x06, 7, _T("Waiting Time Unit"));

					pRegTable->BitDetail[_T("WTime")] = CBitDetail(
						_T("Waiting Time"), _T(""),
						0x06, 0x7F, 0, BOTH_RW, make_pair(0, 127), 0x01);
				}

				pRegTable->RegInfo[0x07] = CRegInfo({ 0x10 }, _T("ALS Control"));
				{
					pRegTable->BitDetail[_T("ALSRC")] = CBitDetail(
						_T("Select ADATA Source"), _T(""),
						0x07, 0x30, 4, BOTH_RW, make_pair(0, 4), 0x01);

					pRegTable->BitDetail[_T("ALGAIN")] = CBitDetail(
						_T("ALS Gain"), _T(""),
						0x07, 0x03, 0, BOTH_RW, make_pair(0, 4), 0x00);
				}

				pRegTable->RegInfo[0x08] = CRegInfo({ 0x01 }, _T("ALS Persistence"));
				{
					pRegTable->BitDetail[_T("ALPERS")] = CBitDetail(
						_T("ALS Persistence"), _T(""),
						0x08, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x01);
				}

				pRegTable->RegInfo[0x0A] = CRegInfo({ 0x00 }, _T("ALS Time"));
				{
					pRegTable->BitDetail[_T("ALTIME")] = CBitDetail(
						_T("ALS Time"), _T(""),
						0x0A, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x0C] = CRegInfo({ 0x00 }, _T("PS Control"));
				{
					pRegTable->BitDetail[_T("PSLPUC")] = CBitDetail(
						_T("PS Pulse count"), _T(""),
						0x0C, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x00);

					pRegTable->BitDetail[_T("PGAIN")] = CBitDetail(0x0C, 0, _T("PS Gain"));
				}

				pRegTable->RegInfo[0x0D] = CRegInfo({ 0x01 }, _T("PS Persistence"));
				{
					pRegTable->BitDetail[_T("PSPERS")] = CBitDetail(
						_T("PS Persistence"), _T(""),
						0x0D, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x01);
				}

				pRegTable->RegInfo[0x0F] = CRegInfo({ 0x00 }, _T("PS Time"));
				{
					pRegTable->BitDetail[_T("PSTIME")] = CBitDetail(
						_T("PS Time"), _T(""),
						0x0F, 0x03, 0, BOTH_RW, make_pair(0, 3), 0x00);
				}

				pRegTable->RegInfo[0x10] = CRegInfo({ 0x40 }, _T("PS LED Control"));
				{
					pRegTable->BitDetail[_T("PSLDR")] = CBitDetail(
						_T("PS LED Driver Ratio"), _T(""),
						0x10, 0xC0, 6, BOTH_RW, make_pair(0, 3), 0x01);

					pRegTable->BitDetail[_T("PSLPUW")] = CBitDetail(
						_T("PS LED Pulse width"), _T(""),
						0x10, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x00);
				}

				pRegTable->RegInfo[0x11] = CRegInfo({ 0x00 }, _T("MGS Control"));
				{
					pRegTable->BitDetail[_T("MGSLPUC")] = CBitDetail(
						_T("MGS LED Pulse count"), _T(""),
						0x11, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x00);

					pRegTable->BitDetail[_T("MGSGAIN")] = CBitDetail(0x11, 0, _T("MGS Gain"));
				}

				pRegTable->RegInfo[0x12] = CRegInfo({ 0x01 }, _T("MGS Z Persistence"));
				{
					pRegTable->BitDetail[_T("MGSPERS")] = CBitDetail(
						_T("MGS Z Persistence"), _T(""),
						0x12, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x01);
				}

				pRegTable->RegInfo[0x13] = CRegInfo({ 0x01 }, _T("MGS Subsystem Control"));
				{
					pRegTable->BitDetail[_T("AUTOPW")]		= CBitDetail(0x13, 6, _T("Auto Power"));
					pRegTable->BitDetail[_T("AUTOCALB")]	= CBitDetail(0x13, 2, _T("Auto Calibration"));
					pRegTable->BitDetail[_T("MGSXYIMD")]	= CBitDetail(0x13, 1, _T("MGS XY INT Mode"));
					pRegTable->BitDetail[_T("MGSZIMD")]		= CBitDetail(0x13, 0, _T("MGS Z INT Mode"), 0x01);
				}

				pRegTable->RegInfo[0x14] = CRegInfo({ 0x1D }, _T("MGS XY Hold"));
				{
					pRegTable->BitDetail[_T("MGSHOLD")] = CBitDetail(
						_T("MGS XY Hold"), _T(""),
						0x14, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x1D);
				}

				pRegTable->RegInfo[0x15] = CRegInfo({ 0x40 }, _T("MGS LED Control"));
				{
					pRegTable->BitDetail[_T("MGSLDR")] = CBitDetail(
						_T("MGS LED Driver Ratio"), _T(""),
						0x15, 0xC0, 6, BOTH_RW, make_pair(0, 3), 0x01);

					pRegTable->BitDetail[_T("MGSLPUW")] = CBitDetail(
						_T("MGS LED Pulse width"), _T(""),
						0x15, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x00);
				}

				pRegTable->RegInfo[0x1D] = CRegInfo({ 0x00 }, _T("MGS Interrupt Status"));
				{
					pRegTable->BitDetail[_T("ZINT")] = CBitDetail(0x1D, 6, _T("Z INT"), ONLY_R);
					pRegTable->BitDetail[_T("YINT")] = CBitDetail(0x1D, 5, _T("Y INT"), ONLY_R);
					pRegTable->BitDetail[_T("XINT")] = CBitDetail(0x1D, 4, _T("X INT"), ONLY_R);
				}

				pRegTable->RegInfo[0x1E] = CRegInfo({ 0x00 }, _T("Error flag Situation"));
				{
					pRegTable->BitDetail[_T("ERRC")] = CBitDetail(0x1E, 3, _T("COMP DATA Error"), ONLY_R);
					pRegTable->BitDetail[_T("ERRB")] = CBitDetail(0x1E, 2, _T("BLUE DATA Error"), ONLY_R);
					pRegTable->BitDetail[_T("ERRG")] = CBitDetail(0x1E, 1, _T("GREEN DATA Error"), ONLY_R);
					pRegTable->BitDetail[_T("ERRR")] = CBitDetail(0x1E, 0, _T("RED DATA Error"), ONLY_R);
				}

				pRegTable->RegInfo[0x1F] = CRegInfo({ 0x00 }, _T("MGS Status"));
				{
					pRegTable->BitDetail[_T("MGSPOW")] = CBitDetail(0x1F, 6, _T("MGS Power Status"), ONLY_R);
					pRegTable->BitDetail[_T("MGSZ")] = CBitDetail(0x1F, 4, _T("MGS Z Status"), ONLY_R);
					pRegTable->BitDetail[_T("MGSY")] = CBitDetail(
						_T("MGS Y Status"), _T(""),
						0x1F, 0x0C, 2, ONLY_R, make_pair(0, 2));

					pRegTable->BitDetail[_T("MGSX")] = CBitDetail(
						_T("MGS X Status"), _T(""),
						0x1F, 0x03, 0, ONLY_R, make_pair(0, 2));
				}

				pRegTable->RegInfo[0x20] = CRegInfo({ 0x00 }, _T("MGS X Motion DATA"));
				{
					pRegTable->BitDetail[_T("X DATA")] = CBitDetail(
						_T("X DATA"), _T(""),
						0x20, 0xFF, 0, ONLY_R, make_pair(0, 255));
				}

				pRegTable->RegInfo[0x21] = CRegInfo({ 0x00 }, _T("MGS Y Motion DATA"));
				{
					pRegTable->BitDetail[_T("Y DATA")] = CBitDetail(
						_T("Y DATA"), _T(""),
						0x21, 0xFF, 0, ONLY_R, make_pair(0, 255));
				}

				pRegTable->RegInfo[0x22] = CRegInfo({ 0x00 }, _T("MGS Z Motion DATA"));
				{
					pRegTable->BitDetail[_T("Z DATA")] = CBitDetail(
						_T("Z DATA"), _T(""),
						0x22, 0xFF, 0, ONLY_R, make_pair(0, 255));
				}

				pRegTable->RegInfo[0x26] = CRegInfo({ 0x00, 0x00 }, _T("PS DATA"), 2);
				{
					pRegTable->BitDetail[_T("PS DATA")] = CBitDetail(
						_T("PS Data"), _T(""),
						0x26, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x28] = CRegInfo({ 0x00, 0x00 }, _T("Red DATA"), 2);
				{
					pRegTable->BitDetail[_T("R DATA")] = CBitDetail(
						_T("R DATA"), _T(""),
						0x28, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2A] = CRegInfo({ 0x00, 0x00 }, _T("Green DATA"), 2);
				{
					pRegTable->BitDetail[_T("G DATA")] = CBitDetail(
						_T("G DATA"), _T(""),
						0x2A, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2C] = CRegInfo({ 0x00, 0x00 }, _T("Blue DATA"), 2);
				{
					pRegTable->BitDetail[_T("B DATA")] = CBitDetail(
						_T("B DATA"), _T(""),
						0x2C, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2E] = CRegInfo({ 0x00, 0x00 }, _T("COMP DATA"), 2);
				{
					pRegTable->BitDetail[_T("C DATA")] = CBitDetail(
						_T("C DATA"), _T(""),
						0x2E, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x30] = CRegInfo({ 0x00, 0x00 }, _T("L DATA"), 2);
				{
					pRegTable->BitDetail[_T("L DATA")] = CBitDetail(
						_T("L DATA"), _T(""),
						0x30, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x32] = CRegInfo({ 0x00, 0x00 }, _T("AL Low Threshold"), 2);
				{
					pRegTable->BitDetail[_T("ALTHSL")] = CBitDetail(
						_T("ALS Low Threshold"), _T(""),
						0x32, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x34] = CRegInfo({ 0xFF, 0xFF }, _T("AL High Threshold"), 2);
				{
					pRegTable->BitDetail[_T("ALTHSH")] = CBitDetail(
						_T("ALS High Threshold"), _T(""),
						0x34, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0xFF, 0xFF });
				}

				pRegTable->RegInfo[0x36] = CRegInfo({ 0x00, 0x00 }, _T("PS Low Threshold"), 2);
				{
					pRegTable->BitDetail[_T("PSTHSL")] = CBitDetail(
						_T("PS Low Threshold"), _T(""),
						0x36, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x38] = CRegInfo({ 0xFF, 0xFF }, _T("PS High Threshold"), 2);
				{
					pRegTable->BitDetail[_T("PSTHSH")] = CBitDetail(
						_T("PS High Threshold"), _T(""),
						0x38, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0xFF, 0xFF });
				}

				pRegTable->RegInfo[0x3A] = CRegInfo({ 0x00, 0x00 }, _T("PS calibration"), 2);
				{
					pRegTable->BitDetail[_T("PSCALB")] = CBitDetail(
						_T("PS Calibration"), _T(""),
						0x3A, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x3C] = CRegInfo({ 0x01 }, _T("Luminance CoefR"));
				{
					pRegTable->BitDetail[_T("LCOFR")] = CBitDetail(
						_T("Luminance Coef R"), _T(""),
						0x3C, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x01);
				}

				pRegTable->RegInfo[0x3D] = CRegInfo({ 0x40 }, _T("Luminance CoefG"));
				{
					pRegTable->BitDetail[_T("LCOFG")] = CBitDetail(
						_T("Luminance Coef G"), _T(""),
						0x3D, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x40);
				}

				pRegTable->RegInfo[0x3E] = CRegInfo({ 0xEA }, _T("Luminance CoefB"));
				{
					pRegTable->BitDetail[_T("LCOFB")] = CBitDetail(
						_T("Luminance Coef B"), _T(""),
						0x3E, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0xEA);
				}

				pRegTable->RegInfo[0x3F] = CRegInfo({ 0x00 }, _T("MGS Z calibration"));
				{
					pRegTable->BitDetail[_T("MGSZCALB")] = CBitDetail(
						_T("MGS Z Calibration"), _T(""),
						0x3F, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x48] = CRegInfo({ 0x00 }, _T("MGS X Low Threshold"));
				{
					pRegTable->BitDetail[_T("MGSXTHSL")] = CBitDetail(
						_T("MGS X Low Threshold"), _T(""),
						0x48, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x49] = CRegInfo({ 0xFF }, _T("MGS X High Threshold"));
				{
					pRegTable->BitDetail[_T("MGSXTHSH")] = CBitDetail(
						_T("MGS X High Threshold"), _T(""),
						0x49, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0xFF);
				}

				pRegTable->RegInfo[0x4A] = CRegInfo({ 0x00 }, _T("MGS Y Low Threshold"));
				{
					pRegTable->BitDetail[_T("MGSYTHSL")] = CBitDetail(
						_T("MGS Y Low Threshold"), _T(""),
						0x4A, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x4B] = CRegInfo({ 0xFF }, _T("MGS Y High Threshold"));
				{
					pRegTable->BitDetail[_T("MGSYTHSH")] = CBitDetail(
						_T("MGS Y High Threshold"), _T(""),
						0x4B, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0xFF);
				}

				pRegTable->RegInfo[0x4C] = CRegInfo({ 0x00 }, _T("MGS Z Low Threshold"));
				{
					pRegTable->BitDetail[_T("MGSZTHSL")] = CBitDetail(
						_T("MGS Z Low Threshold"), _T(""),
						0x4C, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x4D] = CRegInfo({ 0xFF }, _T("MGS Z High Threshold"));
				{
					pRegTable->BitDetail[_T("MGSZTHSH")] = CBitDetail(
						_T("MGS Z High Threshold"), _T(""),
						0x4D, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0xFF);
				}

				pRegTable->RegInfo[0x4E] = CRegInfo({ 0x00 }, _T("MGS X Calibration"));
				{
					pRegTable->BitDetail[_T("MGSXCALB")] = CBitDetail(
						_T("MGS X Calibration"), _T(""),
						0x4E, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x4F] = CRegInfo({ 0x00 }, _T("MGS Y Calibration"));
				{
					pRegTable->BitDetail[_T("MGSYCALB")] = CBitDetail(
						_T("MGS Y Calibration"), _T(""),
						0x4F, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}
			}
			break;

		default: return;
		}

		MappingBitName2Reg();
	}

	bool CreateEngineerModeTab(DlgSel_ dlgSel, uint16_t version)
	{
		switch (version)
		{
		case 12000:
		{
			pDieDetail = &DieDetail.at(12000);
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
		case 12000:
			if (Reg0x00 & pBitDetailMap->at(_T("AEN")).BitMask.at(0))
			{
				ConversionTime += 2.817 + (3.413 * (pRegTable->GetBitValue(_T("ALTIME"))));
			}

			if (Reg0x00 & pBitDetailMap->at(_T("PEN")).BitMask.at(0))
			{
				//T_PS
				ConversionTime += 2.968 + (1.024 * (pRegTable->GetBitValue(_T("PSTIME"))));
				//T_LED
				ConversionTime += (pRegTable->GetBitValue(_T("PSLPUC")) 
					* (0.01333 * (pRegTable->GetBitValue(_T("PSLPUW")))));
			}

			if (Reg0x00 & pBitDetailMap->at(_T("MEN")).BitMask.at(0))
			{
				//T_LED
				ConversionTime += (pRegTable->GetBitValue(_T("MGSLPUC"))
					* (0.01333 * (double)pRegTable->GetBitValue(_T("MGSLPUW"))));
			}

			if (pRegTable->GetBitValue(_T("WTime")) > 0)
			{
				//T_WAIT
				ConversionTime += (pRegTable->GetBitValue(_T("WUnit")) == 0 ? 2 : 20)
					* (double)pRegTable->GetBitValue(_T("WTime"));
			}
			break;
		}

		return (uint32_t)(ConversionTime * 1000);
	}
};