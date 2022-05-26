#pragma once
#include "Define.h"

class CDA3101 : public CDieInfo {
public:
	CDA3101() {}
	void Init(uint16_t version)
	{
		DieName = _T("DA3101");
		switch (version)
		{
		case 16000:
			DieDetail.insert(make_pair(16000, CDieDetail()));
			{
				pDieDetail = &DieDetail.at(16000);
				pRegTable = &pDieDetail->RegisterTable;

				pRegTable->DeviceID = 0x1C;
				pRegTable->RegInfo[0x00] = CRegInfo({ 0x00 }, _T("System Control"));
				{
					pRegTable->BitDetail[_T("OEN")] = CBitDetail(0x00, 4, _T("OX Enable"));
					pRegTable->BitDetail[_T("SWRST")] = CBitDetail(0x00, 2, _T("Software Reset"));
					pRegTable->BitDetail[_T("PEN")] = CBitDetail(0x00, 1, _T("PS Enable"));
					pRegTable->BitDetail[_T("AEN")] = CBitDetail(0x00, 0, _T("ALS Enable"));
				}

				pRegTable->RegInfo[0x01] = CRegInfo({ 0x80 }, _T("Interrupt Flag"));
				{
					pRegTable->BitDetail[_T("PORINT")] = CBitDetail(0x01, 7, _T("POR INT"));
					pRegTable->BitDetail[_T("ERRFLAG")] = CBitDetail(0x01, 5, _T("ERR INT"));
					pRegTable->BitDetail[_T("OBJ")] = CBitDetail(0x01, 4, _T("OBJ INT"));
					pRegTable->BitDetail[_T("OINT")] = CBitDetail(0x01, 2, _T("OX INT"));
					pRegTable->BitDetail[_T("PINT")] = CBitDetail(0x01, 1, _T("PS INT"));
					pRegTable->BitDetail[_T("AINT")] = CBitDetail(0x01, 0, _T("ALS INT"));
				}

				pRegTable->RegInfo[0x02] = CRegInfo({ 0xA8 }, _T("Interrupt Control"));
				{
					pRegTable->BitDetail[_T("PIEN")] = CBitDetail(0x02, 7, _T("PS INT Pin"), 0x01);
					pRegTable->BitDetail[_T("PSPEND")] = CBitDetail(0x02, 6, _T("PS Suspend"));
					pRegTable->BitDetail[_T("PSMODE")] = CBitDetail(0x02, 5, _T("PS Interrupt Mode"), 0x01);
					pRegTable->BitDetail[_T("PSACC")] = CBitDetail(0x02, 4, _T("PS Smart INT"));
					pRegTable->BitDetail[_T("AIEN")] = CBitDetail(0x02, 3, _T("ALS INT Pin"), 0x01);
					pRegTable->BitDetail[_T("ALPEND")] = CBitDetail(0x02, 2, _T("ALS Suspend"));
				}

				pRegTable->RegInfo[0x03] = CRegInfo({ 0x04 }, _T("Manufacturer ID"));
				pRegTable->RegInfo[0x04] = CRegInfo({ 0x0B }, _T("Product ID"));
				pRegTable->RegInfo[0x05] = CRegInfo({ 0x05 }, _T("Revision ID"));

				pRegTable->RegInfo[0x06] = CRegInfo({ 0x01 }, _T("Waiting Time"));
				{
					pRegTable->BitDetail[_T("WUnit")] = CBitDetail(0x06, 7, _T("Waiting Time Unit"));

					pRegTable->BitDetail[_T("WTime")] = CBitDetail(
						_T("Waiting Time"), _T(""),
						0x06, 0x7F, 0, BOTH_RW, make_pair(0, 127), 0x00);
				}

				pRegTable->RegInfo[0x07] = CRegInfo({ 0x00 }, _T("ALS Control"));
				{
					pRegTable->BitDetail[_T("ALXGAIN")] = CBitDetail(0x07, 2, _T("ALS X GAIN"));

					pRegTable->BitDetail[_T("ALGAIN")] = CBitDetail(
						_T("ALS Sensing Gain"), _T(""),
						0x07, 0x03, 0, BOTH_RW, make_pair(0, 3), 0x00);
				}

				pRegTable->RegInfo[0x08] = CRegInfo({ 0x01 }, _T("ALS Persistence"));
				{
					pRegTable->BitDetail[_T("ALPERS")] = CBitDetail(
						_T("ALS Persistence"), _T(""),
						0x08, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x01);
				}

				pRegTable->RegInfo[0x0A] = CRegInfo({ 0x00 }, _T("ALS Time"));
				{
					pRegTable->BitDetail[_T("ATIME")] = CBitDetail(
						_T("ALS Time"), _T(""),
						0x0A, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x0C] = CRegInfo({ 0x00 }, _T("PS Control"));
				{
					pRegTable->BitDetail[_T("PSLPUC")] = CBitDetail(
						_T("PS LED Pulse count"), _T(""),
						0x0C, 0xF0, 4, BOTH_RW, make_pair(0, 2), 0x00);

					pRegTable->BitDetail[_T("PGAIN")] = CBitDetail(0x0C, 0, _T("PS Sensing Gain"));
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

				pRegTable->RegInfo[0x10] = CRegInfo({ 0x00 }, _T("PS LED Control"));
				{
					pRegTable->BitDetail[_T("PSLDR")] = CBitDetail(
						_T("PS LED Driver Ratio"), _T(""),
						0x10, 0xC0, 6, BOTH_RW, make_pair(0, 3), 0x00);

					pRegTable->BitDetail[_T("PSLPUW")] = CBitDetail(
						_T("PS LED Pulse Width"), _T(""),
						0x10, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x00);
				}

				pRegTable->RegInfo[0x1B] = CRegInfo({ 0x00 }, _T("Mean Time"));
				{
					pRegTable->BitDetail[_T("PSMEAN")] = CBitDetail(
						_T("PS Mean"), _T(""),
						0x1B, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x00);
				}

				pRegTable->RegInfo[0x1E] = CRegInfo({ 0x00 }, _T("Error State"));
				{
					pRegTable->BitDetail[_T("ERROIR")] = CBitDetail(0x1E, 3, _T("IR Error"));
					pRegTable->BitDetail[_T("ERROR")] = CBitDetail(0x1E, 2, _T("R Error"));
					pRegTable->BitDetail[_T("ERRCH1")] = CBitDetail(0x1E, 1, _T("CH0 Error"));
					pRegTable->BitDetail[_T("ERRCH0")] = CBitDetail(0x1E, 0, _T("CH1 Error"));
				}

				pRegTable->RegInfo[0x26] = CRegInfo({ 0x00, 0x00 }, _T("PS DATA"), 2);
				{
					pRegTable->BitDetail[_T("PS DATA")] = CBitDetail(
						_T("PS Data"), _T(""),
						0x26, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x28] = CRegInfo({ 0x00, 0x00 }, _T("OR DATA"), 2);
				{
					pRegTable->BitDetail[_T("OR DATA")] = CBitDetail(
						_T("OX Red Data"), _T(""),
						0x28, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2A] = CRegInfo({ 0x00, 0x00 }, _T("OIR DATA"), 2);
				{
					pRegTable->BitDetail[_T("OIR DATA")] = CBitDetail(
						_T("OX IR Data"), _T(""),
						0x2A, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2C] = CRegInfo({ 0x00, 0x00 }, _T("CH0 DATA"), 2);
				{
					pRegTable->BitDetail[_T("CH0 DATA")] = CBitDetail(
						_T("ALS CH0 Data"), _T(""),
						0x2C, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2E] = CRegInfo({ 0x00, 0x00 }, _T("CH1 DATA"), 2);
				{
					pRegTable->BitDetail[_T("CH1 DATA")] = CBitDetail(
						_T("ALS CH1 Data"), _T(""),
						0x2E, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x30] = CRegInfo({ 0x00, 0x00 }, _T("L DATA"), 2);
				{
					pRegTable->BitDetail[_T("L DATA")] = CBitDetail(
						_T("Illuminance Data"), _T(""),
						0x30, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x32] = CRegInfo({ 0x00, 0x00 }, _T("AL LOW THRESHOLD"), 2);
				{
					pRegTable->BitDetail[_T("ALTHSL")] = CBitDetail(
						_T("ALS Low Threshold"), _T(""),
						0x32, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x34] = CRegInfo({ 0xFF, 0xFF }, _T("AL HIGH THRESHOLD"), 2);
				{
					pRegTable->BitDetail[_T("ALTHSH")] = CBitDetail(
						_T("ALS High Threshold"), _T(""),
						0x34, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0xFF, 0xFF });
				}

				pRegTable->RegInfo[0x36] = CRegInfo({ 0x00, 0x00 }, _T("PS LOW THRESHOLD"), 2);
				{
					pRegTable->BitDetail[_T("PSTHSL")] = CBitDetail(
						_T("PS Low Threshold"), _T(""),
						0x36, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x38] = CRegInfo({ 0xFF, 0xFF }, _T("PS HIGH THRESHOLD"), 2);
				{
					pRegTable->BitDetail[_T("PSTHSH")] = CBitDetail(
						_T("PS High Threshold"), _T(""),
						0x38, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0xFF, 0xFF });
				}


				pRegTable->RegInfo[0x3A] = CRegInfo({ 0x00, 0x00 }, _T("PS calibration"), 2);
				{
					pRegTable->BitDetail[_T("PSCALB")] = CBitDetail(
						_T("PS Calibration"), _T(""),
						0x3A, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x3C] = CRegInfo({ 0x40 }, _T("Illuminance Coef"));
				{
					pRegTable->BitDetail[_T("LCOF")] = CBitDetail(
						_T("Illuminance coeffcient"), _T("Illuminance coeffcient for ALS CH1"),
						0x3C, 0xFF, 0, BOTH_RW, make_pair(0, 0xFF), 0x40);
				}

				pRegTable->RegInfo[0x80] = CRegInfo({ 0x01 }, _T("OX Waiting Time"));
				{
					pRegTable->BitDetail[_T("OWUnit")] = CBitDetail(0x80, 7, _T("OX Waiting Time Unit"));

					pRegTable->BitDetail[_T("OWTime")] = CBitDetail(
						_T("OX Waiting Time"), _T(""),
						0x80, 0x7F, 0, BOTH_RW, make_pair(0, 127), 0x00);
				}

				pRegTable->RegInfo[0x81] = CRegInfo({ 0x80 }, _T("OX Control"));
				{
					pRegTable->BitDetail[_T("OIEN")] = CBitDetail(0x81, 7, _T("OX INT pin enable"), 0x01);
					pRegTable->BitDetail[_T("OPEND")] = CBitDetail(0x81, 6, _T("OX suspend enable"));
					pRegTable->BitDetail[_T("HMODE_1")] = CBitDetail(0x81, 5, _T("HMODE[1]"));

					pRegTable->BitDetail[_T("OIRGAIN")] = CBitDetail(
						_T("OX IR Sensing Gain"), _T(""),
						0x81, 0x18, 3, BOTH_RW, make_pair(0, 3), 0x00);

					pRegTable->BitDetail[_T("HMODE_0")] = CBitDetail(0x81, 2, _T("HMODE[0]"));

					pRegTable->BitDetail[_T("ORGAIN")] = CBitDetail(
						_T("OX R Sensing Gain"), _T(""),
						0x81, 0x03, 0, BOTH_RW, make_pair(0, 3), 0x00);
				}

				pRegTable->RegInfo[0x82] = CRegInfo({ 0x40 }, _T("OX Red LED Control"));
				{
					pRegTable->BitDetail[_T("ORLDR")] = CBitDetail(0x82, 6, _T("OX Red LED Driver ratio"), 0x01);

					pRegTable->BitDetail[_T("ORLPUW")] = CBitDetail(
						_T("OX RED LED Pulse width"), _T(""),
						0x82, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x00);
				}

				pRegTable->RegInfo[0x83] = CRegInfo({ 0x40 }, _T("OX IR LED Control"));
				{
					pRegTable->BitDetail[_T("ORLDR")] = CBitDetail(0x83, 6, _T("OX IR LED Driver ratio"), 0x01);

					pRegTable->BitDetail[_T("OIRLPUW")] = CBitDetail(
						_T("OX IR LED Pulse width"), _T(""),
						0x83, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x00);
				}

				pRegTable->RegInfo[0x84] = CRegInfo({ 0x04 }, _T("OX FIFO Level"));
				{
					pRegTable->BitDetail[_T("OFLVL")] = CBitDetail(
						_T("OX FIFO Level"), _T(""),
						0x84, 0x0F, 0, BOTH_RW, make_pair(0, 6), 0x04);
				}

				pRegTable->RegInfo[0x85] = CRegInfo({ 0x00 }, _T("OX FIFO Quantity"));
				{
					pRegTable->BitDetail[_T("OFQTY")] = CBitDetail(
						_T("OX FIFO Quantity"), _T(""),
						0x85, 0x1F, 0, BOTH_RW, make_pair(0, 0x18), 0x00);
				}

				pRegTable->RegInfo[0x86] = CRegInfo({ 0x00 }, _T("OX FIFO Speed"));
				{
					pRegTable->BitDetail[_T("OFSPEED")] = CBitDetail(
						_T("OX FIFO Speed"), _T(""),
						0x86, 0xFF, 0, BOTH_RW, make_pair(0, 0x3F), 0x00);
				}

				pRegTable->RegInfo[0xE1] = CRegInfo({ 0x00 }, _T("OX FIFO"));
				{
					pRegTable->BitDetail[_T("OFTAG")] = CBitDetail(
						_T("OX FIFO Tag"), _T(""),
						0xE1, 0xC0, 6, ONLY_R, make_pair(0, 0x03), 0x00);

					pRegTable->BitDetail[_T("OFIFO")] = CBitDetail(
						_T("OX FIFO"), _T(""),
						0xE1, 0x3F, 0, ONLY_R, make_pair(0, 0x3F), 0x00);
				}
				/* RD Mode */
				{
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
		case 16000:
		{
			pDieDetail = &DieDetail.at(16000);
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
		case 16000:
			if (Reg0x00 & pBitDetailMap->at(_T("OEN")).BitMask.at(0))
			{
				ConversionTime += (2.710 + 0.853 * ((double)pRegTable->GetBitValue(_T("ORLPUW")) + 1));
				ConversionTime += (2.710 + 0.853 * ((double)pRegTable->GetBitValue(_T("OIRLPUW")) + 1));

				if (pRegTable->GetBitValue(_T("OWTime")) > 0)
				{
					//T_WAIT
					ConversionTime += (pRegTable->GetBitValue(_T("OWUnit")) == 0 ? 0.2 : 2)
						* pRegTable->GetBitValue(_T("OWTime"));
				}
			}
			else
			{
				if (Reg0x00 & pBitDetailMap->at(_T("AEN")).BitMask.at(0))
				{
					//T_ALS
					ConversionTime += (2.817 + 2.39 * ((double)pRegTable->GetBitValue(_T("ATIME")) + 1));
				}

				if (Reg0x00 & pBitDetailMap->at(_T("PEN")).BitMask.at(0))
				{
					//T_PS
					ConversionTime += (3.385 + 2 * ((double)pRegTable->GetBitValue(_T("PSLPUC")) + 1)
						* (0.02133 + 0.01333 * pRegTable->GetBitValue(_T("PSLPUW")) 
						+ 1.024 * pow(2, (double)pRegTable->GetBitValue(_T("PSTIME")) + 1)));
				}

				if (pRegTable->GetBitValue(_T("WTime")) > 0)
				{
					//T_WAIT
					ConversionTime += (pRegTable->GetBitValue(_T("WUnit")) == 0 ? 0.2 : 2)
						* pRegTable->GetBitValue(_T("WTime"));
				}
			}
			break;
		}

		return (uint32_t)(ConversionTime * 1000);
	}
};