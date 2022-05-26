#pragma once
#include "Define.h"

class CDA3107 : public CDieInfo {
public:
	CDA3107() {}
	void Init(uint16_t version)
	{
		DieName = _T("DA3107");
		switch (version)
		{
		case 10000:
			DieDetail.insert(make_pair(10000, CDieDetail()));
			{
				pDieDetail = &DieDetail.at(10000);
				pRegTable = &pDieDetail->RegisterTable;

				pRegTable->DeviceID = 0x1C;
				pRegTable->RegInfo[0x00] = CRegInfo({ 0x00 }, _T("SysCtr"));
				{
					pRegTable->BitDetail[_T("IFGCRM")] = CBitDetail(0x00, 7, _T("Interrupt Clear Method"));
					pRegTable->BitDetail[_T("SWRST")] = CBitDetail(0x00, 6, _T("Software Reset"));
					pRegTable->BitDetail[_T("IREN")] = CBitDetail(0x00, 2, _T("IR Enable"));
					pRegTable->BitDetail[_T("PEN")] = CBitDetail(0x00, 1, _T("PS Enable"));
					pRegTable->BitDetail[_T("AEN")] = CBitDetail(0x00, 0, _T("ALS Enable"));
				}

				pRegTable->RegInfo[0x01] = CRegInfo({ 0x80 }, _T("IntFlag"));
				{
					pRegTable->BitDetail[_T("PORINT")] = CBitDetail(0x01, 7, _T("POR INT"));
					pRegTable->BitDetail[_T("IRINT")] = CBitDetail(0x01, 2, _T("IR INT"));
					pRegTable->BitDetail[_T("PINT")] = CBitDetail(0x01, 1, _T("PS INT"));
					pRegTable->BitDetail[_T("AINT")] = CBitDetail(0x01, 0, _T("ALS INT"));
				}

				pRegTable->RegInfo[0x02] = CRegInfo({ 0x03 }, _T("IntCtr"));
				{
					pRegTable->BitDetail[_T("IRPEND")] = CBitDetail(0x02, 6, _T("Suspend IR Function Control"));
					pRegTable->BitDetail[_T("PPEND")] = CBitDetail(0x02, 5, _T("Suspend PS Function Control"));
					pRegTable->BitDetail[_T("APEND")] = CBitDetail(0x02, 4, _T("Suspend ALS Function Control"));
					pRegTable->BitDetail[_T("IRIEN")] = CBitDetail(0x02, 2, _T("IR Interrupt Pin"));
					pRegTable->BitDetail[_T("PIEN")] = CBitDetail(0x02, 1, _T("PS Interrupt Pin"), 0x01);
					pRegTable->BitDetail[_T("AIEN")] = CBitDetail(0x02, 0, _T("ALS Interrupt Pin"), 0x01);
				}

				pRegTable->RegInfo[0x03] = CRegInfo({ 0x00 }, _T("Manufacturer ID"));
				pRegTable->RegInfo[0x04] = CRegInfo({ 0x10 }, _T("Product ID"));
				pRegTable->RegInfo[0x05] = CRegInfo({ 0x00 }, _T("Revision ID"));

				pRegTable->RegInfo[0x06] = CRegInfo({ 0x03 }, _T("WaitTime"));
				{
					pRegTable->BitDetail[_T("WUNIT")] = CBitDetail(0x06, 7, _T("Waiting Time Unit"));

					pRegTable->BitDetail[_T("WTIME")] = CBitDetail(
						_T("Waiting Time"), _T(""),
						0x06, 0x7F, 0, BOTH_RW, make_pair(0, 127), 0x00);
				}

				pRegTable->RegInfo[0x07] = CRegInfo({ 0x00 }, _T("AlsCtr"));
				{
					pRegTable->BitDetail[_T("ASRC")] = CBitDetail(
						_T("Select ADATA Source"), _T(""),
						0x07, 0x30, 4, BOTH_RW, make_pair(0, 4), 0x00);

					pRegTable->BitDetail[_T("AGAIN")] = CBitDetail(
						_T("ALS Sensing Gain"), _T(""),
						0x07, 0x07, 0, BOTH_RW, make_pair(0, 6), 0x00);
				}

				pRegTable->RegInfo[0x08] = CRegInfo({ 0x00 }, _T("AlsTime"));
				{
					pRegTable->BitDetail[_T("ATIME")] = CBitDetail(
						_T("ALS Time"), _T(""),
						0x08, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x09] = CRegInfo({ 0x01 }, _T("AlsPers"));
				{
					pRegTable->BitDetail[_T("APERS")] = CBitDetail(
						_T("ALS Persistence"), _T(""),
						0x09, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x01);
				}

				pRegTable->RegInfo[0x0C] = CRegInfo({ 0x10 }, _T("PsCtr"));
				{
					pRegTable->BitDetail[_T("PACC")] = CBitDetail(0x0C, 5, _T("PS Acceleration"));
					pRegTable->BitDetail[_T("PMODE")] = CBitDetail(0x0C, 4, _T("PS Interrupt Mode"), 0x01);

					pRegTable->BitDetail[_T("PGAIN")] = CBitDetail(
						_T("PS Sensing Gain"), _T(""),
						0x0C, 0x03, 0, BOTH_RW, make_pair(0, 2), 0x00);
				}

				pRegTable->RegInfo[0x0D] = CRegInfo({ 0x00 }, _T("PsTime"));
				{
					pRegTable->BitDetail[_T("PTIME")] = CBitDetail(
						_T("PS Time"), _T(""),
						0x0D, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x00);
				}

				pRegTable->RegInfo[0x0E] = CRegInfo({ 0x01 }, _T("PsPers"));
				{
					pRegTable->BitDetail[_T("PPERS")] = CBitDetail(
						_T("PS Persistence"), _T(""),
						0x0E, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x01);
				}

				pRegTable->RegInfo[0x0F] = CRegInfo({ 0x00 }, _T("PsLedPuC"));
				{
					pRegTable->BitDetail[_T("PLPUC")] = CBitDetail(
						_T("PS LED Pulse Count"), _T(""),
						0x0F, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x00);
				}

				pRegTable->RegInfo[0x10] = CRegInfo({ 0x00 }, _T("PsLedPuW"));
				{
					pRegTable->BitDetail[_T("PLPUW")] = CBitDetail(
						_T("PS LED Pulse Width"), _T(""),
						0x10, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x11] = CRegInfo({ 0x10 }, _T("PsLedDrv"));
				{
					pRegTable->BitDetail[_T("PLOFF")] = CBitDetail(0x11, 7, _T("Turn Off PS LED"));
					pRegTable->BitDetail[_T("PLDC")] = CBitDetail(0x11, 6, _T("Force PS LED as DC"));
					pRegTable->BitDetail[_T("PLASER")] = CBitDetail(0x11, 4, _T("Set LED Maxinum Current"), 0x01);

					pRegTable->BitDetail[_T("PLDR")] = CBitDetail(
						_T("PS LED Driving Current"), _T(""),
						0x11, 0x03, 0, BOTH_RW, make_pair(0, 3), 0x00);
				}

				pRegTable->RegInfo[0x12] = CRegInfo({ 0x00 }, _T("PsCtDac"));
				{
					pRegTable->BitDetail[_T("PCTGAIN")] = CBitDetail(
						_T("Crosstalk DAC gain"), _T(""),
						0x12, 0xC0, 6, BOTH_RW, make_pair(0, 2), 0x00);

					pRegTable->BitDetail[_T("PCTDAC")] = CBitDetail(
						_T("Crosstalk DAC step"), _T(""),
						0x12, 0x1F, 0, BOTH_RW, make_pair(0, 31), 0x00);
				}

				pRegTable->RegInfo[0x13] = CRegInfo({ 0x00 }, _T("PsMean"));
				{
					pRegTable->BitDetail[_T("PMEAN")] = CBitDetail(
						_T("PS Mean"), _T(""),
						0x13, 0x07, 0, BOTH_RW, make_pair(0, 6), 0x00);
				}

				pRegTable->RegInfo[0x16] = CRegInfo({ 0x00 }, _T("IrCtr"));
				{
					pRegTable->BitDetail[_T("IRGAIN")] = CBitDetail(
						_T("IR Sensing Gain"), _T(""),
						0x16, 0x03, 0, BOTH_RW, make_pair(0, 2), 0x00);
				}

				pRegTable->RegInfo[0x17] = CRegInfo({ 0x00 }, _T("IrTime"));
				{
					pRegTable->BitDetail[_T("IRTIME")] = CBitDetail(
						_T("IR Time"), _T(""),
						0x17, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x00);
				}

				pRegTable->RegInfo[0x18] = CRegInfo({ 0x00 }, _T("IrPuW"));
				{
					pRegTable->BitDetail[_T("IRPUW")] = CBitDetail(
						_T("IR LED Pulse Width"), _T(""),
						0x18, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x19] = CRegInfo({ 0x00 }, _T("IrMean"));
				{
					pRegTable->BitDetail[_T("IRMEAN")] = CBitDetail(
						_T("IR Mean"), _T(""),
						0x19, 0x07, 0, BOTH_RW, make_pair(0, 6), 0x00);
				}

				pRegTable->RegInfo[0x1E] = CRegInfo({ 0x00 }, _T("FlagStat"));
				{
					pRegTable->BitDetail[_T("OBJ")] = CBitDetail(0x1E, 7, _T("Object Detection"));
					pRegTable->BitDetail[_T("IRERR")] = CBitDetail(0x1E, 2, _T("IR Error"));
					pRegTable->BitDetail[_T("PERR")] = CBitDetail(0x1E, 1, _T("PS Error"));
					pRegTable->BitDetail[_T("AERR")] = CBitDetail(0x1E, 0, _T("ALS Error"));
				}

				pRegTable->RegInfo[0x20] = CRegInfo({ 0x00, 0x00 }, _T("TempAdc"), 2);
				{
					pRegTable->BitDetail[_T("TADC")] = CBitDetail(
						_T("Temperature ADC"), _T(""),
						0x20, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R, 
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x22] = CRegInfo({ 0x00, 0x00 }, _T("TempOrg"), 2);
				{
					pRegTable->BitDetail[_T("TORG")] = CBitDetail(
						_T("Temperature Original"), _T(""),
						0x22, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x24] = CRegInfo({ 0x00, 0x00 }, _T("TempCh"), 2);
				{
					pRegTable->BitDetail[_T("TCH")] = CBitDetail(
						_T("Temperature Channel"), _T(""),
						0x24, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x28] = CRegInfo({ 0x00, 0x00 }, _T("PsCh"), 2);
				{
					pRegTable->BitDetail[_T("PCH")] = CBitDetail(
						_T("PS Channel"), _T(""),
						0x28, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2A] = CRegInfo({ 0x00, 0x00 }, _T("IrCh"), 2);
				{
					pRegTable->BitDetail[_T("IRCH")] = CBitDetail(
						_T("PS Channel"), _T(""),
						0x2A, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2C] = CRegInfo({ 0x00, 0x00 }, _T("AlsCh0"), 2);
				{
					pRegTable->BitDetail[_T("ACH0")] = CBitDetail(
						_T("ALS Channel 0"), _T(""),
						0x2C, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2E] = CRegInfo({ 0x00, 0x00 }, _T("AlsCh1"), 2);
				{
					pRegTable->BitDetail[_T("ACH1")] = CBitDetail(
						_T("ALS Channel 1"), _T(""),
						0x2E, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x30] = CRegInfo({ 0x00, 0x00 }, _T("AlsCh2"), 2);
				{
					pRegTable->BitDetail[_T("ACH2")] = CBitDetail(
						_T("ALS Channel 2"), _T(""),
						0x30, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x32] = CRegInfo({ 0x00, 0x00 }, _T("AlsCh3"), 2);
				{
					pRegTable->BitDetail[_T("ACH3")] = CBitDetail(
						_T("ALS Channel 3"), _T(""),
						0x32, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x36] = CRegInfo({ 0x00, 0x00 }, _T("AlsLowTh"), 2);
				{
					pRegTable->BitDetail[_T("ALTH")] = CBitDetail(
						_T("ALS Low Threshold"), _T(""),
						0x36, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x38] = CRegInfo({ 0xFF, 0xFF }, _T("AlsHighTh"), 2);
				{
					pRegTable->BitDetail[_T("AHTH")] = CBitDetail(
						_T("ALS High Threshold"), _T(""),
						0x38, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0xFF, 0xFF });
				}

				pRegTable->RegInfo[0x3A] = CRegInfo({ 0x00, 0x00 }, _T("PsLowTh"), 2);
				{
					pRegTable->BitDetail[_T("PLTH")] = CBitDetail(
						_T("PS Low Threshold"), _T(""),
						0x3A, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x3C] = CRegInfo({ 0xFF, 0xFF }, _T("PsHighTh"), 2);
				{
					pRegTable->BitDetail[_T("PHTH")] = CBitDetail(
						_T("PS High Threshold"), _T(""),
						0x3C, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0xFF, 0xFF });
				}


				pRegTable->RegInfo[0x3E] = CRegInfo({ 0x00, 0x00 }, _T("PsCalb"), 2);
				{
					pRegTable->BitDetail[_T("PCALB")] = CBitDetail(
						_T("PS Calibration"), _T(""),
						0x3E, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				/* RD Mode */
				{
					/* Fuse0 ~ Fuse7 */
					for (int i = 0; i < 8; i++)
					{
						CString csTemp = _T("");
						csTemp.Format(_T("Fuse%d"), i);
						pRegTable->RegInfo[0x60 + i] = CRegInfo({ 0x00 }, csTemp);
						for (int j = 0; j < 8; j++)
						{
							csTemp.Format(_T("FIELD%d"), i * 8 + j);
							pRegTable->BitDetail[csTemp] = CBitDetail(0x60 + i, j, _T(""));
						}
					}

					pRegTable->RegInfo[0x68] = CRegInfo({ 0x06, 0x1B }, _T("TempTarget"), 2);
					{
						pRegTable->BitDetail[_T("TTAR")] = CBitDetail(
							_T("Temperature"), _T(""),
							0x68, { 0xFF, 0xFF },
							{ 0, 8 }, BOTH_RW,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x06, 0x1B });
					}

					pRegTable->RegInfo[0x6A] = CRegInfo({ 0x01 }, _T("Rd Control0"));
					{
						pRegTable->BitDetail[_T("FORCE")] = CBitDetail(0x6A, 7, _T("Use Force Data"));
						pRegTable->BitDetail[_T("IRPXSH")] = CBitDetail(0x6A, 2, _T("Enable \"pxsh\" at IR"));
						pRegTable->BitDetail[_T("PPXSH")] = CBitDetail(0x6A, 1, _T("Enable \"pxsh\" at PS"));
						pRegTable->BitDetail[_T("GATTING")] = CBitDetail(0x6A, 0, _T("Gating MCU when sleep"), 0x01);
					}

					pRegTable->RegInfo[0x6B] = CRegInfo({ 0x1A }, _T("Rd Control1"));
					{
						pRegTable->BitDetail[_T("vref_op_set")] = CBitDetail(
							_T("Contorl Vref L2F OP Current"), _T(""),
							0x6B, 0xC0, 6, BOTH_RW, make_pair(0, 3), 0x00);
						pRegTable->BitDetail[_T("vtopf_set")] = CBitDetail(
							_T("Control ADC Vtop"), _T(""),
							0x6B, 0x30, 4, BOTH_RW, make_pair(0, 3), 0x01);
						pRegTable->BitDetail[_T("vdiode_sel")] = CBitDetail(
							_T("Control All Diode voltage"), _T(""),
							0x6B, 0x0C, 2, BOTH_RW, make_pair(0, 3), 0x02);
						pRegTable->BitDetail[_T("clkm_vbs")] = CBitDetail(
							_T("Control the pin \"clkm_vbs\""), _T(""),
							0x6B, 0x03, 0, BOTH_RW, make_pair(0, 3), 0x02);
					}

					pRegTable->RegInfo[0x6C] = CRegInfo({ 0x08 }, _T("Rd Control2"));
					{
						pRegTable->BitDetail[_T("prst_fall_en")] = CBitDetail(0x6C, 6, _T(""));
						pRegTable->BitDetail[_T("pxy_v2i_sel")] = CBitDetail(
							_T(""), _T(""),
							0x6C, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x08);
					}

					pRegTable->RegInfo[0x6D] = CRegInfo({ 0x17 }, _T("Rd Control3"));
					{
						pRegTable->BitDetail[_T("temp_mux")] = CBitDetail(0x6D, 7, _T(""));
						pRegTable->BitDetail[_T("ir_int_ultra")] = CBitDetail(0x6D, 6, _T(""));
						pRegTable->BitDetail[_T("ps_int_ultra")] = CBitDetail(0x6D, 5, _T(""));
						pRegTable->BitDetail[_T("adc_en")] = CBitDetail(0x6D, 4, _T(""), 0x01);
						pRegTable->BitDetail[_T("ir_dark_comp_en")] = CBitDetail(0x6D, 2, _T(""), 0x01);
						pRegTable->BitDetail[_T("ps_dark_comp_en")] = CBitDetail(0x6D, 1, _T(""), 0x01);
						pRegTable->BitDetail[_T("als_dark_comp_en")] = CBitDetail(0x6D, 0, _T(""), 0x01);
					}

					pRegTable->RegInfo[0x6E] = CRegInfo({ 0x67 }, _T("ATIME Unit"));
					{
						pRegTable->BitDetail[_T("AUNIT")] = CBitDetail(
							_T(""), _T(""),
							0x6E, 0xFF, 0, BOTH_RW, make_pair(0, 255), 103);
					}

					pRegTable->RegInfo[0x6F] = CRegInfo({ 0x54 }, _T("PTIME Unit"));
					{
						pRegTable->BitDetail[_T("PUNIT")] = CBitDetail(
							_T(""), _T(""),
							0x6F, 0xFF, 0, BOTH_RW, make_pair(0, 255), 84);
					}

					pRegTable->RegInfo[0x70] = CRegInfo({ 0x21 }, _T("ALS Temperature Coef"));
					{
						pRegTable->BitDetail[_T("ATCFa")] = CBitDetail(
							_T(""), _T(""),
							0x70, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x02);
						pRegTable->BitDetail[_T("ATCFb")] = CBitDetail(
							_T(""), _T(""),
							0x70, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x01);
					}

					pRegTable->RegInfo[0x71] = CRegInfo({ 0x31 }, _T("PS Temperature Coef"));
					{
						pRegTable->BitDetail[_T("PTCFa")] = CBitDetail(
							_T(""), _T(""),
							0x71, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x03);
						pRegTable->BitDetail[_T("PTCFb")] = CBitDetail(
							_T(""), _T(""),
							0x71, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x01);
					}

					pRegTable->RegInfo[0x72] = CRegInfo({ 0xEF }, _T("IR Temperature Coef"));
					{
						pRegTable->BitDetail[_T("IRTCFa")] = CBitDetail(
							_T(""), _T(""),
							0x72, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x0E);
						pRegTable->BitDetail[_T("IRTCFb")] = CBitDetail(
							_T(""), _T(""),
							0x72, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x0F);
					}

					pRegTable->RegInfo[0x73] = CRegInfo({ 0x50 }, _T("ALS Leakage Coef"));
					{
						pRegTable->BitDetail[_T("ALCF")] = CBitDetail(
							_T(""), _T(""),
							0x73, 0xFF, 0, BOTH_RW, make_pair(0, 255), 80);
					}

					pRegTable->RegInfo[0x74] = CRegInfo({ 0x00 }, _T("PS Leakage Coef"));
					{
						pRegTable->BitDetail[_T("PLCF")] = CBitDetail(
							_T(""), _T(""),
							0x74, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0);
					}

					pRegTable->RegInfo[0x75] = CRegInfo({ 0x5E }, _T("IR Leakage Coef"));
					{
						pRegTable->BitDetail[_T("IRLCF")] = CBitDetail(
							_T(""), _T(""),
							0x75, 0xFF, 0, BOTH_RW, make_pair(0, 255), 94);
					}

					pRegTable->RegInfo[0x76] = CRegInfo({ 0x06 }, _T("TCH Leakage Coef"));
					{
						pRegTable->BitDetail[_T("TLCF")] = CBitDetail(
							_T(""), _T(""),
							0x76, 0xFF, 0, BOTH_RW, make_pair(0, 255), 6);
					}

					pRegTable->RegInfo[0x77] = CRegInfo({ 0xE4 }, _T("Time Slot"));
					{
						pRegTable->BitDetail[_T("POWER")] = CBitDetail(0x77, 7, _T(""), 1);
						pRegTable->BitDetail[_T("SLOT")] = CBitDetail(
							_T(""), _T(""),
							0x77, 0x7F, 0, BOTH_RW, make_pair(0, 127), 100);
					}

					pRegTable->RegInfo[0x78] = CRegInfo({ 0x00, 0x00 }, _T("Force FCH0"), 2);
					{
						pRegTable->BitDetail[_T("FFCH0/2/P/IR")] = CBitDetail(
							_T(""), _T(""),
							0x78, { 0xFF, 0xFF },
							{ 0, 8 }, BOTH_RW,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
					}

					pRegTable->RegInfo[0x7A] = CRegInfo({ 0x00, 0x00 }, _T("Force FCH1"), 2);
					{
						pRegTable->BitDetail[_T("FFCH1/3")] = CBitDetail(
							_T(""), _T(""),
							0x7A, { 0xFF, 0xFF },
							{ 0, 8 }, BOTH_RW,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
					}

					pRegTable->RegInfo[0x7C] = CRegInfo({ 0x00, 0x00 }, _T("Force FTMP"), 2);
					{
						pRegTable->BitDetail[_T("FFTMP")] = CBitDetail(
							_T(""), _T(""),
							0x7C, { 0xFF, 0xFF },
							{ 0, 8 }, BOTH_RW,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
					}

					pRegTable->RegInfo[0xF0] = CRegInfo({ 0x00 }, _T("Rd Mode"));
					{
						pRegTable->BitDetail[_T("RD")] = CBitDetail(
							_T(""), _T(""),
							0xF0, 0x07, 0, BOTH_RW, make_pair(0, 7), 0);
					}

					pRegTable->RegInfo[0xF1] = CRegInfo({ 0x00 }, _T("Ram Check"));
					{
						pRegTable->BitDetail[_T("BRAM")] = CBitDetail(
							_T(""), _T(""),
							0xF1, 0xFF, 0, ONLY_R, make_pair(0, 255), 0);
					}

					pRegTable->RegInfo[0xF2] = CRegInfo({ 0x00, 0x00 }, _T("Rom Check"), 2);
					{
						pRegTable->BitDetail[_T("BROM")] = CBitDetail(
							_T(""), _T(""),
							0xF2, { 0xFF, 0xFF },
							{ 0, 8 }, ONLY_R,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
					}

					pRegTable->RegInfo[0xF4] = CRegInfo({ 0x09 }, _T("Fuse Read Width"));
					{
						pRegTable->BitDetail[_T("TRD")] = CBitDetail(
							_T(""), _T(""),
							0xF4, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x09);
					}

					pRegTable->RegInfo[0xF5] = CRegInfo({ 0x4A }, _T("Fuse Burn Width"));
					{
						pRegTable->BitDetail[_T("TBE")] = CBitDetail(
							_T(""), _T(""),
							0xF5, 0x7F, 0, BOTH_RW, make_pair(0, 127), 0x4A);
					}

					pRegTable->RegInfo[0xF6] = CRegInfo({ 0x00 }, _T("Fuse Program Enable"));
					{
						pRegTable->BitDetail[_T("BURN")] = CBitDetail(
							_T(""), _T(""),
							0xF6, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x00);
					}

					pRegTable->RegInfo[0xF7] = CRegInfo({ 0x00 }, _T("View Mode"));
					{
						pRegTable->BitDetail[_T("VIEW")] = CBitDetail(
							_T(""), _T(""),
							0xF6, 0x1F, 0, BOTH_RW, make_pair(0, 31), 0x00);
					}

					pRegTable->RegInfo[0xF8] = CRegInfo({ 0x00 }, _T("Analog En Control"));
					{
						pRegTable->BitDetail[_T("en_verf1")] = CBitDetail(0xF8, 3, _T(""));
						pRegTable->BitDetail[_T("en_ps")] = CBitDetail(0xF8, 2, _T(""));
						pRegTable->BitDetail[_T("en_osc")] = CBitDetail(0xF8, 1, _T(""));
						pRegTable->BitDetail[_T("en_bg")] = CBitDetail(0xF8, 0, _T(""));
					}

					pRegTable->RegInfo[0xFE] = CRegInfo({ 0x00 }, _T("I2C Watch Dog"));
					{
						pRegTable->BitDetail[_T("WDOG")] = CBitDetail(
							_T(""), _T(""),
							0xFE, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x00);
					}
				}
			}
			break;

		case 11000:
			DieDetail.insert(make_pair(11000, CDieDetail()));
			{
				pDieDetail = &DieDetail.at(11000);
				pRegTable = &pDieDetail->RegisterTable;

				pRegTable->DeviceID = 0x1C;
				pRegTable->RegInfo[0x00] = CRegInfo({ 0x00 }, _T("SysCtr"));
				{
					pRegTable->BitDetail[_T("IFGCRM")] = CBitDetail(0x00, 7, _T("Interrupt Clear Method"));
					pRegTable->BitDetail[_T("SWRST")] = CBitDetail(0x00, 6, _T("Software Reset"));
					pRegTable->BitDetail[_T("IREN")] = CBitDetail(0x00, 2, _T("IR Enable"));
					pRegTable->BitDetail[_T("PEN")] = CBitDetail(0x00, 1, _T("PS Enable"));
					pRegTable->BitDetail[_T("AEN")] = CBitDetail(0x00, 0, _T("ALS Enable"));
				}

				pRegTable->RegInfo[0x01] = CRegInfo({ 0x80 }, _T("IntFlag"));
				{
					pRegTable->BitDetail[_T("PORINT")] = CBitDetail(0x01, 7, _T("POR INT"));
					pRegTable->BitDetail[_T("IRINT")] = CBitDetail(0x01, 2, _T("IR INT"));
					pRegTable->BitDetail[_T("PINT")] = CBitDetail(0x01, 1, _T("PS INT"));
					pRegTable->BitDetail[_T("AINT")] = CBitDetail(0x01, 0, _T("ALS INT"));
				}

				pRegTable->RegInfo[0x02] = CRegInfo({ 0x03 }, _T("IntCtr"));
				{
					pRegTable->BitDetail[_T("IRPEND")] = CBitDetail(0x02, 6, _T("Suspend IR Function Control"));
					pRegTable->BitDetail[_T("PPEND")] = CBitDetail(0x02, 5, _T("Suspend PS Function Control"));
					pRegTable->BitDetail[_T("APEND")] = CBitDetail(0x02, 4, _T("Suspend ALS Function Control"));
					pRegTable->BitDetail[_T("IRIEN")] = CBitDetail(0x02, 2, _T("IR Interrupt Pin"));
					pRegTable->BitDetail[_T("PIEN")] = CBitDetail(0x02, 1, _T("PS Interrupt Pin"), 0x01);
					pRegTable->BitDetail[_T("AIEN")] = CBitDetail(0x02, 0, _T("ALS Interrupt Pin"), 0x01);
				}

				pRegTable->RegInfo[0x03] = CRegInfo({ 0x01 }, _T("Manufacturer ID"));
				pRegTable->RegInfo[0x04] = CRegInfo({ 0x10 }, _T("Product ID"));
				pRegTable->RegInfo[0x05] = CRegInfo({ 0x01 }, _T("Revision ID"));

				pRegTable->RegInfo[0x06] = CRegInfo({ 0x03 }, _T("WaitTime"));
				{
					pRegTable->BitDetail[_T("WUNIT")] = CBitDetail(0x06, 7, _T("Waiting Time Unit"));

					pRegTable->BitDetail[_T("WTIME")] = CBitDetail(
						_T("Waiting Time"), _T(""),
						0x06, 0x7F, 0, BOTH_RW, make_pair(0, 127), 0x00);
				}

				pRegTable->RegInfo[0x07] = CRegInfo({ 0x00 }, _T("AlsCtr"));
				{
					pRegTable->BitDetail[_T("ASRC")] = CBitDetail(
						_T("Select ADATA Source"), _T(""),
						0x07, 0x30, 4, BOTH_RW, make_pair(0, 4), 0x00);

					pRegTable->BitDetail[_T("AGAIN")] = CBitDetail(
						_T("ALS Sensing Gain"), _T(""),
						0x07, 0x07, 0, BOTH_RW, make_pair(0, 6), 0x00);
				}

				pRegTable->RegInfo[0x08] = CRegInfo({ 0x00 }, _T("AlsTime"));
				{
					pRegTable->BitDetail[_T("ATIME")] = CBitDetail(
						_T("ALS Time"), _T(""),
						0x08, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x09] = CRegInfo({ 0x01 }, _T("AlsPers"));
				{
					pRegTable->BitDetail[_T("APERS")] = CBitDetail(
						_T("ALS Persistence"), _T(""),
						0x09, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x01);
				}

				pRegTable->RegInfo[0x0C] = CRegInfo({ 0x10 }, _T("PsCtr"));
				{
					pRegTable->BitDetail[_T("PACC")] = CBitDetail(0x0C, 5, _T("PS Acceleration"));
					pRegTable->BitDetail[_T("PMODE")] = CBitDetail(0x0C, 4, _T("PS Interrupt Mode"), 0x01);

					pRegTable->BitDetail[_T("PGAIN")] = CBitDetail(
						_T("PS Sensing Gain"), _T(""),
						0x0C, 0x03, 0, BOTH_RW, make_pair(0, 2), 0x00);
				}

				pRegTable->RegInfo[0x0D] = CRegInfo({ 0x00 }, _T("PsTime"));
				{
					pRegTable->BitDetail[_T("PTIME")] = CBitDetail(
						_T("PS Time"), _T(""),
						0x0D, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x00);
				}

				pRegTable->RegInfo[0x0E] = CRegInfo({ 0x01 }, _T("PsPers"));
				{
					pRegTable->BitDetail[_T("PPERS")] = CBitDetail(
						_T("PS Persistence"), _T(""),
						0x0E, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x01);
				}

				pRegTable->RegInfo[0x0F] = CRegInfo({ 0x00 }, _T("PsLedPuC"));
				{
					pRegTable->BitDetail[_T("PLPUC")] = CBitDetail(
						_T("PS LED Pulse Count"), _T(""),
						0x0F, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x00);
				}

				pRegTable->RegInfo[0x10] = CRegInfo({ 0x00 }, _T("PsLedPuW"));
				{
					pRegTable->BitDetail[_T("PLPUW")] = CBitDetail(
						_T("PS LED Pulse Width"), _T(""),
						0x10, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x11] = CRegInfo({ 0x10 }, _T("PsLedDrv"));
				{
					pRegTable->BitDetail[_T("PLOFF")] = CBitDetail(0x11, 7, _T("Turn Off PS LED"));
					pRegTable->BitDetail[_T("PLDC")] = CBitDetail(0x11, 6, _T("Force PS LED as DC"));
					pRegTable->BitDetail[_T("PLASER")] = CBitDetail(0x11, 4, _T("Set LED Maxinum Current"), 0x01);

					pRegTable->BitDetail[_T("PLDR")] = CBitDetail(
						_T("PS LED Driving Current"), _T(""),
						0x11, 0x03, 0, BOTH_RW, make_pair(0, 3), 0x00);
				}

				pRegTable->RegInfo[0x12] = CRegInfo({ 0x00 }, _T("PsCtDac"));
				{
					pRegTable->BitDetail[_T("PCTGAIN")] = CBitDetail(
						_T("Crosstalk DAC gain"), _T(""),
						0x12, 0xC0, 6, BOTH_RW, make_pair(0, 2), 0x00);

					pRegTable->BitDetail[_T("PCTDAC")] = CBitDetail(
						_T("Crosstalk DAC step"), _T(""),
						0x12, 0x1F, 0, BOTH_RW, make_pair(0, 31), 0x00);
				}

				pRegTable->RegInfo[0x13] = CRegInfo({ 0x02 }, _T("PsMean"));
				{
					pRegTable->BitDetail[_T("PMEAN")] = CBitDetail(
						_T("PS Mean"), _T(""),
						0x13, 0x07, 0, BOTH_RW, make_pair(0, 6), 0x02);
				}

				pRegTable->RegInfo[0x16] = CRegInfo({ 0x00 }, _T("IrCtr"));
				{
					pRegTable->BitDetail[_T("IRGAIN")] = CBitDetail(
						_T("IR Sensing Gain"), _T(""),
						0x16, 0x03, 0, BOTH_RW, make_pair(0, 2), 0x00);
				}

				pRegTable->RegInfo[0x17] = CRegInfo({ 0x00 }, _T("IrTime"));
				{
					pRegTable->BitDetail[_T("IRTIME")] = CBitDetail(
						_T("IR Time"), _T(""),
						0x17, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x00);
				}

				pRegTable->RegInfo[0x18] = CRegInfo({ 0x00 }, _T("IrPuW"));
				{
					pRegTable->BitDetail[_T("IRPUW")] = CBitDetail(
						_T("IR LED Pulse Width"), _T(""),
						0x18, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x19] = CRegInfo({ 0x02 }, _T("IrMean"));
				{
					pRegTable->BitDetail[_T("IRMEAN")] = CBitDetail(
						_T("IR Mean"), _T(""),
						0x19, 0x07, 0, BOTH_RW, make_pair(0, 6), 0x02);
				}

				pRegTable->RegInfo[0x1E] = CRegInfo({ 0x00 }, _T("FlagStat"));
				{
					pRegTable->BitDetail[_T("OBJ")] = CBitDetail(0x1E, 7, _T("Object Detection"));
					pRegTable->BitDetail[_T("IRERR")] = CBitDetail(0x1E, 2, _T("IR Error"));
					pRegTable->BitDetail[_T("PERR")] = CBitDetail(0x1E, 1, _T("PS Error"));
					pRegTable->BitDetail[_T("AERR")] = CBitDetail(0x1E, 0, _T("ALS Error"));
				}

				pRegTable->RegInfo[0x20] = CRegInfo({ 0x00, 0x00 }, _T("TempAdc"), 2);
				{
					pRegTable->BitDetail[_T("TADC")] = CBitDetail(
						_T("Temperature ADC"), _T(""),
						0x20, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x22] = CRegInfo({ 0x00, 0x00 }, _T("TempOrg"), 2);
				{
					pRegTable->BitDetail[_T("TORG")] = CBitDetail(
						_T("Temperature Original"), _T(""),
						0x22, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x24] = CRegInfo({ 0x00, 0x00 }, _T("TempCh"), 2);
				{
					pRegTable->BitDetail[_T("TCH")] = CBitDetail(
						_T("Temperature Channel"), _T(""),
						0x24, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x28] = CRegInfo({ 0x00, 0x00 }, _T("PsCh"), 2);
				{
					pRegTable->BitDetail[_T("PCH")] = CBitDetail(
						_T("PS Channel"), _T(""),
						0x28, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2A] = CRegInfo({ 0x00, 0x00 }, _T("IrCh"), 2);
				{
					pRegTable->BitDetail[_T("IRCH")] = CBitDetail(
						_T("PS Channel"), _T(""),
						0x2A, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2C] = CRegInfo({ 0x00, 0x00 }, _T("AlsCh0"), 2);
				{
					pRegTable->BitDetail[_T("ACH0")] = CBitDetail(
						_T("ALS Channel 0"), _T(""),
						0x2C, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2E] = CRegInfo({ 0x00, 0x00 }, _T("AlsCh1"), 2);
				{
					pRegTable->BitDetail[_T("ACH1")] = CBitDetail(
						_T("ALS Channel 1"), _T(""),
						0x2E, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x30] = CRegInfo({ 0x00, 0x00 }, _T("AlsCh2"), 2);
				{
					pRegTable->BitDetail[_T("ACH2")] = CBitDetail(
						_T("ALS Channel 2"), _T(""),
						0x30, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x32] = CRegInfo({ 0x00, 0x00 }, _T("AlsCh3"), 2);
				{
					pRegTable->BitDetail[_T("ACH3")] = CBitDetail(
						_T("ALS Channel 3"), _T(""),
						0x32, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x36] = CRegInfo({ 0x00, 0x00 }, _T("AlsLowTh"), 2);
				{
					pRegTable->BitDetail[_T("ALTH")] = CBitDetail(
						_T("ALS Low Threshold"), _T(""),
						0x36, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x38] = CRegInfo({ 0xFF, 0xFF }, _T("AlsHighTh"), 2);
				{
					pRegTable->BitDetail[_T("AHTH")] = CBitDetail(
						_T("ALS High Threshold"), _T(""),
						0x38, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0xFF, 0xFF });
				}

				pRegTable->RegInfo[0x3A] = CRegInfo({ 0x00, 0x00 }, _T("PsLowTh"), 2);
				{
					pRegTable->BitDetail[_T("PLTH")] = CBitDetail(
						_T("PS Low Threshold"), _T(""),
						0x3A, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x3C] = CRegInfo({ 0xFF, 0xFF }, _T("PsHighTh"), 2);
				{
					pRegTable->BitDetail[_T("PHTH")] = CBitDetail(
						_T("PS High Threshold"), _T(""),
						0x3C, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0xFF, 0xFF });
				}


				pRegTable->RegInfo[0x3E] = CRegInfo({ 0x00, 0x00 }, _T("PsCalb"), 2);
				{
					pRegTable->BitDetail[_T("PCALB")] = CBitDetail(
						_T("PS Calibration"), _T(""),
						0x3E, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				/* RD Mode */
				{
					/* Fuse0 ~ Fuse7 */
					for (int i = 0; i < 8; i++)
					{
						CString csTemp = _T("");
						csTemp.Format(_T("Fuse%d"), i);
						pRegTable->RegInfo[0x60 + i] = CRegInfo({ 0x00 }, csTemp);
						for (int j = 0; j < 8; j++)
						{
							csTemp.Format(_T("FIELD%d"), i * 8 + j);
							pRegTable->BitDetail[csTemp] = CBitDetail(_T(""), _T(""), 0x60 + i, 0xFF, 0, ONLY_R);
						}
					}

					pRegTable->RegInfo[0x68] = CRegInfo({ 0x05, 0x55 }, _T("TempTarget"), 2);
					{
						pRegTable->BitDetail[_T("TTAR")] = CBitDetail(
							_T("Temperature"), _T(""),
							0x68, { 0xFF, 0xFF },
							{ 0, 8 }, BOTH_RW,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x05, 0x55 });
					}

					pRegTable->RegInfo[0x6A] = CRegInfo({ 0x01 }, _T("Rd Control0"));
					{
						pRegTable->BitDetail[_T("FORCE")] = CBitDetail(0x6A, 7, _T("Use Force Data"));
						pRegTable->BitDetail[_T("IRPXSH")] = CBitDetail(0x6A, 2, _T("Enable \"pxsh\" at IR"));
						pRegTable->BitDetail[_T("PPXSH")] = CBitDetail(0x6A, 1, _T("Enable \"pxsh\" at PS"));
						pRegTable->BitDetail[_T("GATTING")] = CBitDetail(0x6A, 0, _T("Gating MCU when sleep"), 0x01);
					}

					pRegTable->RegInfo[0x6B] = CRegInfo({ 0x1A }, _T("Rd Control1"));
					{
						pRegTable->BitDetail[_T("vref_op_set")] = CBitDetail(
							_T("Contorl Vref L2F OP Current"), _T(""),
							0x6B, 0xC0, 6, BOTH_RW, make_pair(0, 3), 0x00);
						pRegTable->BitDetail[_T("vtopf_set")] = CBitDetail(
							_T("Control ADC Vtop"), _T(""),
							0x6B, 0x30, 4, BOTH_RW, make_pair(0, 3), 0x01);
						pRegTable->BitDetail[_T("vdiode_sel")] = CBitDetail(
							_T("Control All Diode voltage"), _T(""),
							0x6B, 0x0C, 2, BOTH_RW, make_pair(0, 3), 0x02);
						pRegTable->BitDetail[_T("clkm_vbs")] = CBitDetail(
							_T("Control the pin \"clkm_vbs\""), _T(""),
							0x6B, 0x03, 0, BOTH_RW, make_pair(0, 3), 0x02);
					}

					pRegTable->RegInfo[0x6C] = CRegInfo({ 0x0F }, _T("Rd Control2"));
					{
						pRegTable->BitDetail[_T("prst_fall_en")] = CBitDetail(0x6C, 6, _T(""));
						pRegTable->BitDetail[_T("pxy_v2i_sel")] = CBitDetail(
							_T(""), _T(""),
							0x6C, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x0F);
					}

					pRegTable->RegInfo[0x6D] = CRegInfo({ 0x10 }, _T("Rd Control3"));
					{
						pRegTable->BitDetail[_T("temp_mux")] = CBitDetail(0x6D, 7, _T(""));
						pRegTable->BitDetail[_T("ir_int_ultra")] = CBitDetail(0x6D, 6, _T(""));
						pRegTable->BitDetail[_T("ps_int_ultra")] = CBitDetail(0x6D, 5, _T(""));
						pRegTable->BitDetail[_T("adc_en")] = CBitDetail(0x6D, 4, _T(""), 0x01);
						pRegTable->BitDetail[_T("ir_dark_comp_en")] = CBitDetail(0x6D, 2, _T(""));
						pRegTable->BitDetail[_T("ps_dark_comp_en")] = CBitDetail(0x6D, 1, _T(""));
						pRegTable->BitDetail[_T("als_dark_comp_en")] = CBitDetail(0x6D, 0, _T(""));
					}

					pRegTable->RegInfo[0x6E] = CRegInfo({ 0x67 }, _T("ATIME Unit"));
					{
						pRegTable->BitDetail[_T("AUNIT")] = CBitDetail(
							_T(""), _T(""),
							0x6E, 0xFF, 0, BOTH_RW, make_pair(0, 255), 103);
					}

					pRegTable->RegInfo[0x6F] = CRegInfo({ 0x1D }, _T("PTIME Unit"));
					{
						pRegTable->BitDetail[_T("PUNIT")] = CBitDetail(
							_T(""), _T(""),
							0x6F, 0xFF, 0, BOTH_RW, make_pair(0, 255), 29);
					}

					pRegTable->RegInfo[0x70] = CRegInfo({ 0x0F }, _T("ALS Temperature Coef"));
					{
						pRegTable->BitDetail[_T("ATCFa")] = CBitDetail(
							_T(""), _T(""),
							0x70, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x00);
						pRegTable->BitDetail[_T("ATCFb")] = CBitDetail(
							_T(""), _T(""),
							0x70, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x0F);
					}

					pRegTable->RegInfo[0x71] = CRegInfo({ 0x00 }, _T("PS Temperature Coef"));
					{
						pRegTable->BitDetail[_T("PTCFa")] = CBitDetail(
							_T(""), _T(""),
							0x71, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x00);
						pRegTable->BitDetail[_T("PTCFb")] = CBitDetail(
							_T(""), _T(""),
							0x71, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x00);
					}

					pRegTable->RegInfo[0x72] = CRegInfo({ 0xED }, _T("IR Temperature Coef"));
					{
						pRegTable->BitDetail[_T("IRTCFa")] = CBitDetail(
							_T(""), _T(""),
							0x72, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x0E);
						pRegTable->BitDetail[_T("IRTCFb")] = CBitDetail(
							_T(""), _T(""),
							0x72, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x0D);
					}

					pRegTable->RegInfo[0x73] = CRegInfo({ 0x43 }, _T("ALS Leakage Coef"));
					{
						pRegTable->BitDetail[_T("ALCF")] = CBitDetail(
							_T(""), _T(""),
							0x73, 0xFF, 0, BOTH_RW, make_pair(0, 255), 67);
					}

					pRegTable->RegInfo[0x74] = CRegInfo({ 0x00 }, _T("PS Leakage Coef"));
					{
						pRegTable->BitDetail[_T("PLCF")] = CBitDetail(
							_T(""), _T(""),
							0x74, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0);
					}

					pRegTable->RegInfo[0x75] = CRegInfo({ 0x37 }, _T("IR Leakage Coef"));
					{
						pRegTable->BitDetail[_T("IRLCF")] = CBitDetail(
							_T(""), _T(""),
							0x75, 0xFF, 0, BOTH_RW, make_pair(0, 255), 55);
					}

					pRegTable->RegInfo[0x76] = CRegInfo({ 0x07 }, _T("TCH Leakage Coef"));
					{
						pRegTable->BitDetail[_T("TLCF")] = CBitDetail(
							_T(""), _T(""),
							0x76, 0xFF, 0, BOTH_RW, make_pair(0, 255), 7);
					}

					pRegTable->RegInfo[0x77] = CRegInfo({ 0xE4 }, _T("Time Slot"));
					{
						pRegTable->BitDetail[_T("POWER")] = CBitDetail(0x77, 7, _T(""), 1);
						pRegTable->BitDetail[_T("SLOT")] = CBitDetail(
							_T(""), _T(""),
							0x77, 0x7F, 0, BOTH_RW, make_pair(0, 127), 100);
					}

					pRegTable->RegInfo[0x78] = CRegInfo({ 0x00, 0x00 }, _T("Force FCH0"), 2);
					{
						pRegTable->BitDetail[_T("FFCH0/2/P/IR")] = CBitDetail(
							_T(""), _T(""),
							0x78, { 0xFF, 0xFF },
							{ 0, 8 }, BOTH_RW,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
					}

					pRegTable->RegInfo[0x7A] = CRegInfo({ 0x00, 0x00 }, _T("Force FCH1"), 2);
					{
						pRegTable->BitDetail[_T("FFCH1/3")] = CBitDetail(
							_T(""), _T(""),
							0x7A, { 0xFF, 0xFF },
							{ 0, 8 }, BOTH_RW,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
					}

					pRegTable->RegInfo[0x7C] = CRegInfo({ 0x00, 0x00 }, _T("Force FTMP"), 2);
					{
						pRegTable->BitDetail[_T("FFTMP")] = CBitDetail(
							_T(""), _T(""),
							0x7C, { 0xFF, 0xFF },
							{ 0, 8 }, BOTH_RW,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
					}

					pRegTable->RegInfo[0xF0] = CRegInfo({ 0x00 }, _T("Rd Mode"));
					{
						pRegTable->BitDetail[_T("RD")] = CBitDetail(
							_T(""), _T(""),
							0xF0, 0x07, 0, BOTH_RW, make_pair(0, 7), 0);
					}

					pRegTable->RegInfo[0xF1] = CRegInfo({ 0x00 }, _T("Ram Check"));
					{
						pRegTable->BitDetail[_T("BRAM")] = CBitDetail(
							_T(""), _T(""),
							0xF1, 0xFF, 0, ONLY_R, make_pair(0, 255), 0);
					}

					pRegTable->RegInfo[0xF2] = CRegInfo({ 0x00, 0x00 }, _T("Rom Check"), 2);
					{
						pRegTable->BitDetail[_T("BROM")] = CBitDetail(
							_T(""), _T(""),
							0xF2, { 0xFF, 0xFF },
							{ 0, 8 }, ONLY_R,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
					}

					pRegTable->RegInfo[0xF4] = CRegInfo({ 0x09 }, _T("Fuse Read Width"));
					{
						pRegTable->BitDetail[_T("TRD")] = CBitDetail(
							_T(""), _T(""),
							0xF4, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x09);
					}

					pRegTable->RegInfo[0xF5] = CRegInfo({ 0x4A }, _T("Fuse Burn Width"));
					{
						pRegTable->BitDetail[_T("TBE")] = CBitDetail(
							_T(""), _T(""),
							0xF5, 0x7F, 0, BOTH_RW, make_pair(0, 127), 0x4A);
					}

					pRegTable->RegInfo[0xF6] = CRegInfo({ 0x00 }, _T("Fuse Program Enable"));
					{
						pRegTable->BitDetail[_T("BURN")] = CBitDetail(
							_T(""), _T(""),
							0xF6, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x00);
					}

					pRegTable->RegInfo[0xF7] = CRegInfo({ 0x00 }, _T("View Mode"));
					{
						pRegTable->BitDetail[_T("VIEW")] = CBitDetail(
							_T(""), _T(""),
							0xF6, 0x1F, 0, BOTH_RW, make_pair(0, 31), 0x00);
					}

					pRegTable->RegInfo[0xF8] = CRegInfo({ 0x00 }, _T("Analog En Control"));
					{
						pRegTable->BitDetail[_T("en_verf1")] = CBitDetail(0xF8, 3, _T(""));
						pRegTable->BitDetail[_T("en_ps")] = CBitDetail(0xF8, 2, _T(""));
						pRegTable->BitDetail[_T("en_osc")] = CBitDetail(0xF8, 1, _T(""));
						pRegTable->BitDetail[_T("en_bg")] = CBitDetail(0xF8, 0, _T(""));
					}

					pRegTable->RegInfo[0xFE] = CRegInfo({ 0x00 }, _T("I2C Watch Dog"));
					{
						pRegTable->BitDetail[_T("WDOG")] = CBitDetail(
							_T(""), _T(""),
							0xFE, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x00);
					}
				}
			}
			break;
		case 12000:
			DieDetail.insert(make_pair(12000, CDieDetail()));
			{
				pDieDetail = &DieDetail.at(12000);
				pRegTable = &pDieDetail->RegisterTable;

				pRegTable->DeviceID = 0x1C;
				pRegTable->RegInfo[0x00] = CRegInfo({ 0x00 }, _T("SysCtr"));
				{
					pRegTable->BitDetail[_T("IFGCRM")] = CBitDetail(0x00, 7, _T("Interrupt Clear Method"));
					pRegTable->BitDetail[_T("SWRST")] = CBitDetail(0x00, 6, _T("Software Reset"));
					pRegTable->BitDetail[_T("IREN")] = CBitDetail(0x00, 2, _T("IR Enable"));
					pRegTable->BitDetail[_T("PEN")] = CBitDetail(0x00, 1, _T("PS Enable"));
					pRegTable->BitDetail[_T("AEN")] = CBitDetail(0x00, 0, _T("ALS Enable"));
				}

				pRegTable->RegInfo[0x01] = CRegInfo({ 0x80 }, _T("IntFlag"));
				{
					pRegTable->BitDetail[_T("PORINT")] = CBitDetail(0x01, 7, _T("POR INT"));
					pRegTable->BitDetail[_T("IRINT")] = CBitDetail(0x01, 2, _T("IR INT"));
					pRegTable->BitDetail[_T("PINT")] = CBitDetail(0x01, 1, _T("PS INT"));
					pRegTable->BitDetail[_T("AINT")] = CBitDetail(0x01, 0, _T("ALS INT"));
				}

				pRegTable->RegInfo[0x02] = CRegInfo({ 0x03 }, _T("IntCtr"));
				{
					pRegTable->BitDetail[_T("IRPEND")] = CBitDetail(0x02, 6, _T("Suspend IR Function Control"));
					pRegTable->BitDetail[_T("PPEND")] = CBitDetail(0x02, 5, _T("Suspend PS Function Control"));
					pRegTable->BitDetail[_T("APEND")] = CBitDetail(0x02, 4, _T("Suspend ALS Function Control"));
					pRegTable->BitDetail[_T("IRIEN")] = CBitDetail(0x02, 2, _T("IR Interrupt Pin"));
					pRegTable->BitDetail[_T("PIEN")] = CBitDetail(0x02, 1, _T("PS Interrupt Pin"), 0x01);
					pRegTable->BitDetail[_T("AIEN")] = CBitDetail(0x02, 0, _T("ALS Interrupt Pin"), 0x01);
				}

				pRegTable->RegInfo[0x03] = CRegInfo({ 0x02 }, _T("Manufacturer ID"));
				pRegTable->RegInfo[0x04] = CRegInfo({ 0x10 }, _T("Product ID"));
				pRegTable->RegInfo[0x05] = CRegInfo({ 0x02 }, _T("Revision ID"));

				pRegTable->RegInfo[0x06] = CRegInfo({ 0x03 }, _T("WaitTime"));
				{
					pRegTable->BitDetail[_T("WUNIT")] = CBitDetail(0x06, 7, _T("Waiting Time Unit")); 

					pRegTable->BitDetail[_T("WTIME")] = CBitDetail(
						_T("Waiting Time"), _T(""),
						0x06, 0x7F, 0, BOTH_RW, make_pair(0, 127), 0x03);
				}

				pRegTable->RegInfo[0x07] = CRegInfo({ 0x01 }, _T("AlsPers"));
				{
					pRegTable->BitDetail[_T("APERS")] = CBitDetail(
						_T("ALS Persistence"), _T(""),
						0x07, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x01);
				}

				pRegTable->RegInfo[0x08] = CRegInfo({ 0x00 }, _T("AlsCtr"));
				{
					pRegTable->BitDetail[_T("ASRC")] = CBitDetail(
						_T("Select ADATA Source"), _T(""),
						0x08, 0x30, 4, BOTH_RW, make_pair(0, 4), 0x00);

					pRegTable->BitDetail[_T("AGAIN")] = CBitDetail(
						_T("ALS Sensing Gain"), _T(""),
						0x08, 0x07, 0, BOTH_RW, make_pair(0, 6), 0x00);
				}

				pRegTable->RegInfo[0x09] = CRegInfo({ 0x00 }, _T("AlsTime"));
				{
					pRegTable->BitDetail[_T("ATIME")] = CBitDetail(
						_T("ALS Time"), _T(""),
						0x09, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x0C] = CRegInfo({ 0x01 }, _T("PsPers"));
				{
					pRegTable->BitDetail[_T("PPERS")] = CBitDetail(
						_T("PS Persistence"), _T(""),
						0x0C, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x01);
				}

				pRegTable->RegInfo[0x0D] = CRegInfo({ 0x02 }, _T("PsMean"));
				{
					pRegTable->BitDetail[_T("PMEAN")] = CBitDetail(
						_T("PS Mean"), _T(""),
						0x0D, 0x07, 0, BOTH_RW, make_pair(0, 6), 0x02);
				}

				pRegTable->RegInfo[0x0E] = CRegInfo({ 0x10 }, _T("PsCtr"));
				{
					pRegTable->BitDetail[_T("PACC")] = CBitDetail(0x0E, 5, _T("PS Acceleration"));
					pRegTable->BitDetail[_T("PMODE")] = CBitDetail(0x0E, 4, _T("PS Interrupt Mode"), 0x01);
					pRegTable->BitDetail[_T("PGAIN")] = CBitDetail(0x0E, 0, _T("PS Sensing Gain"));
				}

				pRegTable->RegInfo[0x0F] = CRegInfo({ 0x00 }, _T("PsTime"));
				{
					pRegTable->BitDetail[_T("PTIME")] = CBitDetail(
						_T("PS Time"), _T(""),
						0x0F, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x00);
				}

				pRegTable->RegInfo[0x10] = CRegInfo({ 0x00 }, _T("PsLedPuW"));
				{
					pRegTable->BitDetail[_T("PLPUW")] = CBitDetail(
						_T("PS LED Pulse Width"), _T(""),
						0x10, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x11] = CRegInfo({ 0x00 }, _T("PsLedPuC"));
				{
					pRegTable->BitDetail[_T("PLPUC")] = CBitDetail(
						_T("PS LED Pulse Count"), _T(""),
						0x11, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x00);
				}

				pRegTable->RegInfo[0x12] = CRegInfo({ 0x10 }, _T("PsLedDrv"));
				{
					pRegTable->BitDetail[_T("PLOFF")] = CBitDetail(0x12, 7, _T("Turn Off PS LED"));
					pRegTable->BitDetail[_T("PLDC")] = CBitDetail(0x12, 6, _T("Force PS LED as DC"));
					pRegTable->BitDetail[_T("PLASER")] = CBitDetail(0x12, 4, _T("Set LED Maxinum Current"), 0x01);

					pRegTable->BitDetail[_T("PLDR")] = CBitDetail(
						_T("PS LED Driving Current"), _T(""),
						0x12, 0x03, 0, BOTH_RW, make_pair(0, 3), 0x00);
				}

				pRegTable->RegInfo[0x13] = CRegInfo({ 0x00 }, _T("PsCtDac"));
				{
					pRegTable->BitDetail[_T("PCTGAIN")] = CBitDetail(
						_T("Crosstalk DAC gain"), _T(""),
						0x13, 0xC0, 6, BOTH_RW, make_pair(0, 2), 0x00);

					pRegTable->BitDetail[_T("PCTDAC")] = CBitDetail(
						_T("Crosstalk DAC step"), _T(""),
						0x13, 0x1F, 0, BOTH_RW, make_pair(0, 31), 0x00);
				}

				pRegTable->RegInfo[0x16] = CRegInfo({ 0x02 }, _T("IrMean"));
				{
					pRegTable->BitDetail[_T("IRMEAN")] = CBitDetail(
						_T("IR Mean"), _T(""),
						0x16, 0x07, 0, BOTH_RW, make_pair(0, 6), 0x02);
				}

				pRegTable->RegInfo[0x17] = CRegInfo({ 0x00 }, _T("IrCtr"));
				{
					pRegTable->BitDetail[_T("IRGAIN")] = CBitDetail(0x17, 0, _T("IR Sensing Gain"));
				}

				pRegTable->RegInfo[0x18] = CRegInfo({ 0x00 }, _T("IrTime"));
				{
					pRegTable->BitDetail[_T("IRTIME")] = CBitDetail(
						_T("IR Time"), _T(""),
						0x18, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x00);
				}

				pRegTable->RegInfo[0x19] = CRegInfo({ 0x00 }, _T("IrPuW"));
				{
					pRegTable->BitDetail[_T("IRPUW")] = CBitDetail(
						_T("IR LED Pulse Width"), _T(""),
						0x19, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x1E] = CRegInfo({ 0x00 }, _T("FlagStat"));
				{
					pRegTable->BitDetail[_T("OBJ")] = CBitDetail(0x1E, 7, _T("Object Detection"));
					pRegTable->BitDetail[_T("IRERR")] = CBitDetail(0x1E, 2, _T("IR Error"));
					pRegTable->BitDetail[_T("PERR")] = CBitDetail(0x1E, 1, _T("PS Error"));
					pRegTable->BitDetail[_T("AERR")] = CBitDetail(0x1E, 0, _T("ALS Error"));
				}

				pRegTable->RegInfo[0x20] = CRegInfo({ 0x00, 0x00 }, _T("TempAdc"), 2);
				{
					pRegTable->BitDetail[_T("TADC")] = CBitDetail(
						_T("Temperature ADC"), _T(""),
						0x20, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x22] = CRegInfo({ 0x00, 0x00 }, _T("TempOrg"), 2);
				{
					pRegTable->BitDetail[_T("TORG")] = CBitDetail(
						_T("Temperature Original"), _T(""),
						0x22, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x24] = CRegInfo({ 0x00, 0x00 }, _T("TempCh"), 2);
				{
					pRegTable->BitDetail[_T("TCH")] = CBitDetail(
						_T("Temperature Channel"), _T(""),
						0x24, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x28] = CRegInfo({ 0x00, 0x00 }, _T("PsCh"), 2);
				{
					pRegTable->BitDetail[_T("PCH")] = CBitDetail(
						_T("PS Channel"), _T(""),
						0x28, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2A] = CRegInfo({ 0x00, 0x00 }, _T("IrCh"), 2);
				{
					pRegTable->BitDetail[_T("IRCH")] = CBitDetail(
						_T("PS Channel"), _T(""),
						0x2A, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2C] = CRegInfo({ 0x00, 0x00 }, _T("AlsCh0"), 2);
				{
					pRegTable->BitDetail[_T("ACH0")] = CBitDetail(
						_T("ALS Channel 0"), _T(""),
						0x2C, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2E] = CRegInfo({ 0x00, 0x00 }, _T("AlsCh1"), 2);
				{
					pRegTable->BitDetail[_T("ACH1")] = CBitDetail(
						_T("ALS Channel 1"), _T(""),
						0x2E, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x30] = CRegInfo({ 0x00, 0x00 }, _T("AlsCh2"), 2);
				{
					pRegTable->BitDetail[_T("ACH2")] = CBitDetail(
						_T("ALS Channel 2"), _T(""),
						0x30, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x32] = CRegInfo({ 0x00, 0x00 }, _T("AlsCh3"), 2);
				{
					pRegTable->BitDetail[_T("ACH3")] = CBitDetail(
						_T("ALS Channel 3"), _T(""),
						0x32, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x36] = CRegInfo({ 0x00, 0x00 }, _T("AlsLowTh"), 2);
				{
					pRegTable->BitDetail[_T("ALTH")] = CBitDetail(
						_T("ALS Low Threshold"), _T(""),
						0x36, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x38] = CRegInfo({ 0xFF, 0xFF }, _T("AlsHighTh"), 2);
				{
					pRegTable->BitDetail[_T("AHTH")] = CBitDetail(
						_T("ALS High Threshold"), _T(""),
						0x38, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0xFF, 0xFF });
				}

				pRegTable->RegInfo[0x3A] = CRegInfo({ 0x00, 0x00 }, _T("PsLowTh"), 2);
				{
					pRegTable->BitDetail[_T("PLTH")] = CBitDetail(
						_T("PS Low Threshold"), _T(""),
						0x3A, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x3C] = CRegInfo({ 0xFF, 0xFF }, _T("PsHighTh"), 2);
				{
					pRegTable->BitDetail[_T("PHTH")] = CBitDetail(
						_T("PS High Threshold"), _T(""),
						0x3C, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0xFF, 0xFF });
				}


				pRegTable->RegInfo[0x3E] = CRegInfo({ 0x00, 0x00 }, _T("PsCalb"), 2);
				{
					pRegTable->BitDetail[_T("PCALB")] = CBitDetail(
						_T("PS Calibration"), _T(""),
						0x3E, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				/* RD Mode */
				{
					/* Fuse0 ~ Fuse7 */
					for (int i = 0; i < 8; i++)
					{
						CString csTemp = _T("");
						csTemp.Format(_T("Fuse%d"), i);
						pRegTable->RegInfo[0x60 + i] = CRegInfo({ 0x00 }, csTemp);
						for (int j = 0; j < 8; j++)
						{
							csTemp.Format(_T("FIELD%d"), i * 8 + j);
							pRegTable->BitDetail[csTemp] = CBitDetail(_T(""), _T(""), 0x60 + i, 0xFF, 0, ONLY_R);
						}
					}

					pRegTable->RegInfo[0x68] = CRegInfo({ 0x04, 0xDD }, _T("TempTarget"), 2);
					{
						pRegTable->BitDetail[_T("TTAR")] = CBitDetail(
							_T("Temperature"), _T(""),
							0x68, { 0xFF, 0xFF },
							{ 0, 8 }, BOTH_RW,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x04, 0xDD });
					}

					pRegTable->RegInfo[0x6A] = CRegInfo({ 0x01 }, _T("Rd Control0"));
					{
						pRegTable->BitDetail[_T("FORCE")] = CBitDetail(0x6A, 7, _T("Use Force Data"));
						pRegTable->BitDetail[_T("IRPXSH")] = CBitDetail(0x6A, 2, _T("Enable \"pxsh\" at IR"));
						pRegTable->BitDetail[_T("PPXSH")] = CBitDetail(0x6A, 1, _T("Enable \"pxsh\" at PS"));
						pRegTable->BitDetail[_T("GATTING")] = CBitDetail(0x6A, 0, _T("Gating MCU when sleep"), 0x01);
					}

					pRegTable->RegInfo[0x6B] = CRegInfo({ 0x16 }, _T("Rd Control1"));
					{
						pRegTable->BitDetail[_T("vref_op_set")] = CBitDetail(
							_T("Contorl Vref L2F OP Current"), _T(""),
							0x6B, 0xC0, 6, BOTH_RW, make_pair(0, 3), 0x00);
						pRegTable->BitDetail[_T("vtopf_set")] = CBitDetail(
							_T("Control ADC Vtop"), _T(""),
							0x6B, 0x30, 4, BOTH_RW, make_pair(0, 3), 0x01);
						pRegTable->BitDetail[_T("vdiode_sel")] = CBitDetail(
							_T("Control All Diode voltage"), _T(""),
							0x6B, 0x0C, 2, BOTH_RW, make_pair(0, 3), 0x01);
						pRegTable->BitDetail[_T("clkm_vbs")] = CBitDetail(
							_T("Control the pin \"clkm_vbs\""), _T(""),
							0x6B, 0x03, 0, BOTH_RW, make_pair(0, 3), 0x02);
					}

					pRegTable->RegInfo[0x6C] = CRegInfo({ 0x0F }, _T("Rd Control2"));
					{
						pRegTable->BitDetail[_T("prst_fall_en")] = CBitDetail(0x6C, 6, _T(""));
						pRegTable->BitDetail[_T("pxy_v2i_sel")] = CBitDetail(
							_T(""), _T(""),
							0x6C, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x0F);
					}

					pRegTable->RegInfo[0x6D] = CRegInfo({ 0x10 }, _T("Rd Control3"));
					{
						pRegTable->BitDetail[_T("temp_mux")] = CBitDetail(0x6D, 7, _T(""));
						pRegTable->BitDetail[_T("ir_int_ultra")] = CBitDetail(0x6D, 6, _T(""));
						pRegTable->BitDetail[_T("ps_int_ultra")] = CBitDetail(0x6D, 5, _T(""));
						pRegTable->BitDetail[_T("adc_en")] = CBitDetail(0x6D, 4, _T(""), 0x01);
						pRegTable->BitDetail[_T("ir_dark_comp_en")] = CBitDetail(0x6D, 2, _T(""));
						pRegTable->BitDetail[_T("ps_dark_comp_en")] = CBitDetail(0x6D, 1, _T(""));
						pRegTable->BitDetail[_T("als_dark_comp_en")] = CBitDetail(0x6D, 0, _T(""));
					}

					pRegTable->RegInfo[0x6E] = CRegInfo({ 0x67 }, _T("ATIME Unit"));
					{
						pRegTable->BitDetail[_T("AUNIT")] = CBitDetail(
							_T(""), _T(""),
							0x6E, 0xFF, 0, BOTH_RW, make_pair(0, 255), 103);
					}

					pRegTable->RegInfo[0x6F] = CRegInfo({ 0x30 }, _T("PTIME Unit"));
					{
						pRegTable->BitDetail[_T("PUNIT")] = CBitDetail(
							_T(""), _T(""),
							0x6F, 0xFF, 0, BOTH_RW, make_pair(0, 255), 48);
					}

					pRegTable->RegInfo[0x70] = CRegInfo({ 0x31 }, _T("ACH0 Temp Coef"));
					{
						pRegTable->BitDetail[_T("ATCF0a")] = CBitDetail(
							_T(""), _T(""),
							0x70, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x03);
						pRegTable->BitDetail[_T("ATCF0b")] = CBitDetail(
							_T(""), _T(""),
							0x70, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x01);
					}

					pRegTable->RegInfo[0x71] = CRegInfo({ 0x0F }, _T("ACH1 Temp Coef"));
					{
						pRegTable->BitDetail[_T("ATCF1a")] = CBitDetail(
							_T(""), _T(""),
							0x71, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x00);
						pRegTable->BitDetail[_T("ATCF1b")] = CBitDetail(
							_T(""), _T(""),
							0x71, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x0F);
					}

					pRegTable->RegInfo[0x72] = CRegInfo({ 0xCA }, _T("ACH2 Temp Coef"));
					{
						pRegTable->BitDetail[_T("ATCF2a")] = CBitDetail(
							_T(""), _T(""),
							0x72, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x0C);
						pRegTable->BitDetail[_T("ATCF2b")] = CBitDetail(
							_T(""), _T(""),
							0x72, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x0A);
					}

					pRegTable->RegInfo[0x73] = CRegInfo({ 0x1F }, _T("ACH3 Temp Coef"));
					{
						pRegTable->BitDetail[_T("ATCF3a")] = CBitDetail(
							_T(""), _T(""),
							0x73, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x01);
						pRegTable->BitDetail[_T("ATCF3b")] = CBitDetail(
							_T(""), _T(""),
							0x73, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x0F);
					}

					pRegTable->RegInfo[0x74] = CRegInfo({ 0x5E }, _T("PS Temp Coef"));
					{
						pRegTable->BitDetail[_T("PTCFa")] = CBitDetail(
							_T(""), _T(""),
							0x74, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x05);
						pRegTable->BitDetail[_T("PTCFb")] = CBitDetail(
							_T(""), _T(""),
							0x74, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x0E);
					}

					pRegTable->RegInfo[0x75] = CRegInfo({ 0xEB }, _T("IR Temp Coef"));
					{
						pRegTable->BitDetail[_T("IRTCFa")] = CBitDetail(
							_T(""), _T(""),
							0x75, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x0E);
						pRegTable->BitDetail[_T("IRTCFb")] = CBitDetail(
							_T(""), _T(""),
							0x75, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x0B);
					}

					pRegTable->RegInfo[0x76] = CRegInfo({ 0x56 }, _T("ALS Leakage Coef"));
					{
						pRegTable->BitDetail[_T("ALCF")] = CBitDetail(
							_T(""), _T(""),
							0x76, 0xFF, 0, BOTH_RW, make_pair(0, 255), 86);
					}

					pRegTable->RegInfo[0x77] = CRegInfo({ 0x00 }, _T("PS Leakage Coef"));
					{
						pRegTable->BitDetail[_T("PLCF")] = CBitDetail(
							_T(""), _T(""),
							0x77, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0);
					}

					pRegTable->RegInfo[0x78] = CRegInfo({ 0x05 }, _T("IR Leakage Coef"));
					{
						pRegTable->BitDetail[_T("IRLCF")] = CBitDetail(
							_T(""), _T(""),
							0x78, 0xFF, 0, BOTH_RW, make_pair(0, 255), 5);
					}

					pRegTable->RegInfo[0x79] = CRegInfo({ 0x64 }, _T("Time Slot"));
					{
						pRegTable->BitDetail[_T("SLOT")] = CBitDetail(
							_T(""), _T(""),
							0x79, 0x7F, 0, BOTH_RW, make_pair(0, 127), 100);
					}

					pRegTable->RegInfo[0x7A] = CRegInfo({ 0x00, 0x00 }, _T("Force FCH0"), 2);
					{
						pRegTable->BitDetail[_T("FFCH0/2/P/IR")] = CBitDetail(
							_T(""), _T(""),
							0x7A, { 0xFF, 0xFF },
							{ 0, 8 }, BOTH_RW,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
					}

					pRegTable->RegInfo[0x7C] = CRegInfo({ 0x00, 0x00 }, _T("Force FCH1"), 2);
					{
						pRegTable->BitDetail[_T("FFCH1/3")] = CBitDetail(
							_T(""), _T(""),
							0x7C, { 0xFF, 0xFF },
							{ 0, 8 }, BOTH_RW,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
					}

					pRegTable->RegInfo[0x7E] = CRegInfo({ 0x00, 0x00 }, _T("Force FTMP"), 2);
					{
						pRegTable->BitDetail[_T("FFTMP")] = CBitDetail(
							_T(""), _T(""),
							0x7E, { 0xFF, 0xFF },
							{ 0, 8 }, BOTH_RW,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
					}

					pRegTable->RegInfo[0xF0] = CRegInfo({ 0x00 }, _T("Rd Mode"));
					{
						pRegTable->BitDetail[_T("RD")] = CBitDetail(
							_T(""), _T(""),
							0xF0, 0x07, 0, BOTH_RW, make_pair(0, 7), 0);
					}

					pRegTable->RegInfo[0xF1] = CRegInfo({ 0x00 }, _T("Ram Check"));
					{
						pRegTable->BitDetail[_T("BRAM")] = CBitDetail(
							_T(""), _T(""),
							0xF1, 0xFF, 0, ONLY_R, make_pair(0, 255), 0);
					}

					pRegTable->RegInfo[0xF2] = CRegInfo({ 0x00, 0x00 }, _T("Rom Check"), 2);
					{
						pRegTable->BitDetail[_T("BROM")] = CBitDetail(
							_T(""), _T(""),
							0xF2, { 0xFF, 0xFF },
							{ 0, 8 }, ONLY_R,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
					}

					pRegTable->RegInfo[0xF4] = CRegInfo({ 0x09 }, _T("Fuse Read Width"));
					{
						pRegTable->BitDetail[_T("TRD")] = CBitDetail(
							_T(""), _T(""),
							0xF4, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x09);
					}

					pRegTable->RegInfo[0xF5] = CRegInfo({ 0x4A }, _T("Fuse Burn Width"));
					{
						pRegTable->BitDetail[_T("TBE")] = CBitDetail(
							_T(""), _T(""),
							0xF5, 0x7F, 0, BOTH_RW, make_pair(0, 127), 0x4A);
					}

					pRegTable->RegInfo[0xF6] = CRegInfo({ 0x00 }, _T("Fuse Program Enable"));
					{
						pRegTable->BitDetail[_T("BURN")] = CBitDetail(
							_T(""), _T(""),
							0xF6, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x00);
					}

					pRegTable->RegInfo[0xF7] = CRegInfo({ 0x00 }, _T("View Mode"));
					{
						pRegTable->BitDetail[_T("VIEW")] = CBitDetail(
							_T(""), _T(""),
							0xF6, 0x1F, 0, BOTH_RW, make_pair(0, 31), 0x00);
					}

					pRegTable->RegInfo[0xF8] = CRegInfo({ 0x00 }, _T("Analog En Control"));
					{
						pRegTable->BitDetail[_T("en_verf1")] = CBitDetail(0xF8, 3, _T(""));
						pRegTable->BitDetail[_T("en_ps")] = CBitDetail(0xF8, 2, _T(""));
						pRegTable->BitDetail[_T("en_osc")] = CBitDetail(0xF8, 1, _T(""));
						pRegTable->BitDetail[_T("en_bg")] = CBitDetail(0xF8, 0, _T(""));
					}

					pRegTable->RegInfo[0xFE] = CRegInfo({ 0x00 }, _T("I2C Watch Dog"));
					{
						pRegTable->BitDetail[_T("WDOG")] = CBitDetail(
							_T(""), _T(""),
							0xFE, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x00);
					}
				}
			}
			break;
		case 12001:	//v1.2a
			DieDetail.insert(make_pair(12001, CDieDetail()));
			{
				pDieDetail = &DieDetail.at(12001);
				pRegTable = &pDieDetail->RegisterTable;

				pRegTable->DeviceID = 0x1C;
				pRegTable->RegInfo[0x00] = CRegInfo({ 0x00 }, _T("SysCtr"));
				{
					pRegTable->BitDetail[_T("IFGCRM")] = CBitDetail(0x00, 7, _T("Interrupt Clear Method"));
					pRegTable->BitDetail[_T("SWRST")] = CBitDetail(0x00, 6, _T("Software Reset"));
					pRegTable->BitDetail[_T("IREN")] = CBitDetail(0x00, 2, _T("IR Enable"));
					pRegTable->BitDetail[_T("PEN")] = CBitDetail(0x00, 1, _T("PS Enable"));
					pRegTable->BitDetail[_T("AEN")] = CBitDetail(0x00, 0, _T("ALS Enable"));
				}

				pRegTable->RegInfo[0x01] = CRegInfo({ 0x80 }, _T("IntFlag"));
				{
					pRegTable->BitDetail[_T("PORINT")] = CBitDetail(0x01, 7, _T("POR INT"));
					pRegTable->BitDetail[_T("IRINT")] = CBitDetail(0x01, 2, _T("IR INT"));
					pRegTable->BitDetail[_T("PINT")] = CBitDetail(0x01, 1, _T("PS INT"));
					pRegTable->BitDetail[_T("AINT")] = CBitDetail(0x01, 0, _T("ALS INT"));
				}

				pRegTable->RegInfo[0x02] = CRegInfo({ 0x03 }, _T("IntCtr"));
				{
					pRegTable->BitDetail[_T("IRPEND")] = CBitDetail(0x02, 6, _T("Suspend IR Function Control"));
					pRegTable->BitDetail[_T("PPEND")] = CBitDetail(0x02, 5, _T("Suspend PS Function Control"));
					pRegTable->BitDetail[_T("APEND")] = CBitDetail(0x02, 4, _T("Suspend ALS Function Control"));
					pRegTable->BitDetail[_T("IRIEN")] = CBitDetail(0x02, 2, _T("IR Interrupt Pin"));
					pRegTable->BitDetail[_T("PIEN")] = CBitDetail(0x02, 1, _T("PS Interrupt Pin"), 0x01);
					pRegTable->BitDetail[_T("AIEN")] = CBitDetail(0x02, 0, _T("ALS Interrupt Pin"), 0x01);
				}

				pRegTable->RegInfo[0x03] = CRegInfo({ 0x01 }, _T("Manufacturer ID"));
				pRegTable->RegInfo[0x04] = CRegInfo({ 0x12 }, _T("Product ID"));
				pRegTable->RegInfo[0x05] = CRegInfo({ 0x01 }, _T("Revision ID"));

				pRegTable->RegInfo[0x06] = CRegInfo({ 0x03 }, _T("WaitTime"));
				{
					pRegTable->BitDetail[_T("WUNIT")] = CBitDetail(0x06, 7, _T("Waiting Time Unit"));

					pRegTable->BitDetail[_T("WTIME")] = CBitDetail(
						_T("Waiting Time"), _T(""),
						0x06, 0x7F, 0, BOTH_RW, make_pair(0, 127), 0x03);
				}

				pRegTable->RegInfo[0x07] = CRegInfo({ 0x01 }, _T("AlsPers"));
				{
					pRegTable->BitDetail[_T("APERS")] = CBitDetail(
						_T("ALS Persistence"), _T(""),
						0x07, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x01);
				}

				pRegTable->RegInfo[0x08] = CRegInfo({ 0x00 }, _T("AlsCtr"));
				{
					pRegTable->BitDetail[_T("ASRC")] = CBitDetail(
						_T("Select ADATA Source"), _T(""),
						0x08, 0x30, 4, BOTH_RW, make_pair(0, 4), 0x00);

					pRegTable->BitDetail[_T("AGAIN")] = CBitDetail(
						_T("ALS Sensing Gain"), _T(""),
						0x08, 0x07, 0, BOTH_RW, make_pair(0, 6), 0x00);
				}

				pRegTable->RegInfo[0x09] = CRegInfo({ 0x00 }, _T("AlsTime"));
				{
					pRegTable->BitDetail[_T("ATIME")] = CBitDetail(
						_T("ALS Time"), _T(""),
						0x09, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x0C] = CRegInfo({ 0x01 }, _T("PsPers"));
				{
					pRegTable->BitDetail[_T("PPERS")] = CBitDetail(
						_T("PS Persistence"), _T(""),
						0x0C, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x01);
				}

				pRegTable->RegInfo[0x0D] = CRegInfo({ 0x02 }, _T("PsMean"));
				{
					pRegTable->BitDetail[_T("PMEAN")] = CBitDetail(
						_T("PS Mean"), _T(""),
						0x0D, 0x07, 0, BOTH_RW, make_pair(0, 6), 0x02);
				}

				pRegTable->RegInfo[0x0E] = CRegInfo({ 0x10 }, _T("PsCtr"));
				{
					pRegTable->BitDetail[_T("PACC")] = CBitDetail(0x0E, 5, _T("PS Acceleration"));
					pRegTable->BitDetail[_T("PMODE")] = CBitDetail(0x0E, 4, _T("PS Interrupt Mode"), 0x01);
					pRegTable->BitDetail[_T("PGAIN")] = CBitDetail(0x0E, 0, _T("PS Sensing Gain"));
				}

				pRegTable->RegInfo[0x0F] = CRegInfo({ 0x00 }, _T("PsTime"));
				{
					pRegTable->BitDetail[_T("PTIME")] = CBitDetail(
						_T("PS Time"), _T(""),
						0x0F, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x00);
				}

				pRegTable->RegInfo[0x10] = CRegInfo({ 0x00 }, _T("PsLedPuW"));
				{
					pRegTable->BitDetail[_T("PLPUW")] = CBitDetail(
						_T("PS LED Pulse Width"), _T(""),
						0x10, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x11] = CRegInfo({ 0x00 }, _T("PsLedPuC"));
				{
					pRegTable->BitDetail[_T("PLPUC")] = CBitDetail(
						_T("PS LED Pulse Count"), _T(""),
						0x11, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x00);
				}

				pRegTable->RegInfo[0x12] = CRegInfo({ 0x10 }, _T("PsLedDrv"));
				{
					pRegTable->BitDetail[_T("PLOFF")] = CBitDetail(0x12, 7, _T("Turn Off PS LED"));
					pRegTable->BitDetail[_T("PLDC")] = CBitDetail(0x12, 6, _T("Force PS LED as DC"));
					pRegTable->BitDetail[_T("PLASER")] = CBitDetail(0x12, 4, _T("Set LED Maxinum Current"), 0x01);

					pRegTable->BitDetail[_T("PLDR")] = CBitDetail(
						_T("PS LED Driving Current"), _T(""),
						0x12, 0x03, 0, BOTH_RW, make_pair(0, 3), 0x00);
				}

				pRegTable->RegInfo[0x13] = CRegInfo({ 0x00 }, _T("PsCtDac"));
				{
					pRegTable->BitDetail[_T("PCTGAIN")] = CBitDetail(
						_T("Crosstalk DAC gain"), _T(""),
						0x13, 0xC0, 6, BOTH_RW, make_pair(0, 2), 0x00);

					pRegTable->BitDetail[_T("PCTDAC")] = CBitDetail(
						_T("Crosstalk DAC step"), _T(""),
						0x13, 0x1F, 0, BOTH_RW, make_pair(0, 31), 0x00);
				}

				pRegTable->RegInfo[0x16] = CRegInfo({ 0x02 }, _T("IrMean"));
				{
					pRegTable->BitDetail[_T("IRMEAN")] = CBitDetail(
						_T("IR Mean"), _T(""),
						0x16, 0x07, 0, BOTH_RW, make_pair(0, 6), 0x02);
				}

				pRegTable->RegInfo[0x17] = CRegInfo({ 0x00 }, _T("IrCtr"));
				{
					pRegTable->BitDetail[_T("IRGAIN")] = CBitDetail(0x17, 0, _T("IR Sensing Gain"));
				}

				pRegTable->RegInfo[0x18] = CRegInfo({ 0x00 }, _T("IrTime"));
				{
					pRegTable->BitDetail[_T("IRTIME")] = CBitDetail(
						_T("IR Time"), _T(""),
						0x18, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x00);
				}

				pRegTable->RegInfo[0x19] = CRegInfo({ 0x00 }, _T("IrPuW"));
				{
					pRegTable->BitDetail[_T("IRPUW")] = CBitDetail(
						_T("IR LED Pulse Width"), _T(""),
						0x19, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x1E] = CRegInfo({ 0x00 }, _T("FlagStat"));
				{
					pRegTable->BitDetail[_T("OBJ")] = CBitDetail(0x1E, 7, _T("Object Detection"));
					pRegTable->BitDetail[_T("IRERR")] = CBitDetail(0x1E, 2, _T("IR Error"));
					pRegTable->BitDetail[_T("PERR")] = CBitDetail(0x1E, 1, _T("PS Error"));
					pRegTable->BitDetail[_T("AERR")] = CBitDetail(0x1E, 0, _T("ALS Error"));
				}

				pRegTable->RegInfo[0x20] = CRegInfo({ 0x00, 0x00 }, _T("TempAdc"), 2);
				{
					pRegTable->BitDetail[_T("TADC")] = CBitDetail(
						_T("Temperature ADC"), _T(""),
						0x20, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x22] = CRegInfo({ 0x00, 0x00 }, _T("TempOrg"), 2);
				{
					pRegTable->BitDetail[_T("TORG")] = CBitDetail(
						_T("Temperature Original"), _T(""),
						0x22, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x24] = CRegInfo({ 0x00, 0x00 }, _T("TempCh"), 2);
				{
					pRegTable->BitDetail[_T("TCH")] = CBitDetail(
						_T("Temperature Channel"), _T(""),
						0x24, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x28] = CRegInfo({ 0x00, 0x00 }, _T("PsCh"), 2);
				{
					pRegTable->BitDetail[_T("PCH")] = CBitDetail(
						_T("PS Channel"), _T(""),
						0x28, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2A] = CRegInfo({ 0x00, 0x00 }, _T("IrCh"), 2);
				{
					pRegTable->BitDetail[_T("IRCH")] = CBitDetail(
						_T("PS Channel"), _T(""),
						0x2A, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2C] = CRegInfo({ 0x00, 0x00 }, _T("AlsCh0"), 2);
				{
					pRegTable->BitDetail[_T("ACH0")] = CBitDetail(
						_T("ALS Channel 0"), _T(""),
						0x2C, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2E] = CRegInfo({ 0x00, 0x00 }, _T("AlsCh1"), 2);
				{
					pRegTable->BitDetail[_T("ACH1")] = CBitDetail(
						_T("ALS Channel 1"), _T(""),
						0x2E, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x30] = CRegInfo({ 0x00, 0x00 }, _T("AlsCh2"), 2);
				{
					pRegTable->BitDetail[_T("ACH2")] = CBitDetail(
						_T("ALS Channel 2"), _T(""),
						0x30, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x32] = CRegInfo({ 0x00, 0x00 }, _T("AlsCh3"), 2);
				{
					pRegTable->BitDetail[_T("ACH3")] = CBitDetail(
						_T("ALS Channel 3"), _T(""),
						0x32, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x36] = CRegInfo({ 0x00, 0x00 }, _T("AlsLowTh"), 2);
				{
					pRegTable->BitDetail[_T("ALTH")] = CBitDetail(
						_T("ALS Low Threshold"), _T(""),
						0x36, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x38] = CRegInfo({ 0xFF, 0xFF }, _T("AlsHighTh"), 2);
				{
					pRegTable->BitDetail[_T("AHTH")] = CBitDetail(
						_T("ALS High Threshold"), _T(""),
						0x38, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0xFF, 0xFF });
				}

				pRegTable->RegInfo[0x3A] = CRegInfo({ 0x00, 0x00 }, _T("PsLowTh"), 2);
				{
					pRegTable->BitDetail[_T("PLTH")] = CBitDetail(
						_T("PS Low Threshold"), _T(""),
						0x3A, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x3C] = CRegInfo({ 0xFF, 0xFF }, _T("PsHighTh"), 2);
				{
					pRegTable->BitDetail[_T("PHTH")] = CBitDetail(
						_T("PS High Threshold"), _T(""),
						0x3C, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0xFF, 0xFF });
				}


				pRegTable->RegInfo[0x3E] = CRegInfo({ 0x00, 0x00 }, _T("PsCalb"), 2);
				{
					pRegTable->BitDetail[_T("PCALB")] = CBitDetail(
						_T("PS Calibration"), _T(""),
						0x3E, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				/* RD Mode */
				{
					/* Fuse0 ~ Fuse7 */
					for (int i = 0; i < 8; i++)
					{
						CString csTemp = _T("");
						csTemp.Format(_T("Fuse%d"), i);
						pRegTable->RegInfo[0x60 + i] = CRegInfo({ 0x00 }, csTemp);
						for (int j = 0; j < 8; j++)
						{
							csTemp.Format(_T("FIELD%d"), i * 8 + j);
							pRegTable->BitDetail[csTemp] = CBitDetail(_T(""), _T(""), 0x60 + i, 0xFF, 0, ONLY_R);
						}
					}

					pRegTable->RegInfo[0x68] = CRegInfo({ 0x04, 0xDD }, _T("TempTarget"), 2);
					{
						pRegTable->BitDetail[_T("TTAR")] = CBitDetail(
							_T("Temperature"), _T(""),
							0x68, { 0xFF, 0xFF },
							{ 0, 8 }, BOTH_RW,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x04, 0xDD });
					}

					pRegTable->RegInfo[0x6A] = CRegInfo({ 0x01 }, _T("Rd Control0"));
					{
						pRegTable->BitDetail[_T("FORCE")] = CBitDetail(0x6A, 7, _T("Use Force Data"));
						pRegTable->BitDetail[_T("IRPXSH")] = CBitDetail(0x6A, 2, _T("Enable \"pxsh\" at IR"));
						pRegTable->BitDetail[_T("PPXSH")] = CBitDetail(0x6A, 1, _T("Enable \"pxsh\" at PS"));
						pRegTable->BitDetail[_T("GATTING")] = CBitDetail(0x6A, 0, _T("Gating MCU when sleep"), 0x01);
					}

					pRegTable->RegInfo[0x6B] = CRegInfo({ 0x16 }, _T("Rd Control1"));
					{
						pRegTable->BitDetail[_T("vref_op_set")] = CBitDetail(
							_T("Contorl Vref L2F OP Current"), _T(""),
							0x6B, 0xC0, 6, BOTH_RW, make_pair(0, 3), 0x00);
						pRegTable->BitDetail[_T("vtopf_set")] = CBitDetail(
							_T("Control ADC Vtop"), _T(""),
							0x6B, 0x30, 4, BOTH_RW, make_pair(0, 3), 0x01);
						pRegTable->BitDetail[_T("vdiode_sel")] = CBitDetail(
							_T("Control All Diode voltage"), _T(""),
							0x6B, 0x0C, 2, BOTH_RW, make_pair(0, 3), 0x01);
						pRegTable->BitDetail[_T("clkm_vbs")] = CBitDetail(
							_T("Control the pin \"clkm_vbs\""), _T(""),
							0x6B, 0x03, 0, BOTH_RW, make_pair(0, 3), 0x02);
					}

					pRegTable->RegInfo[0x6C] = CRegInfo({ 0x0F }, _T("Rd Control2"));
					{
						pRegTable->BitDetail[_T("prst_fall_en")] = CBitDetail(0x6C, 6, _T(""));
						pRegTable->BitDetail[_T("pxy_v2i_sel")] = CBitDetail(
							_T(""), _T(""),
							0x6C, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x0F);
					}

					pRegTable->RegInfo[0x6D] = CRegInfo({ 0x00 }, _T("Rd Control3"));
					{
						pRegTable->BitDetail[_T("temp_mux")] = CBitDetail(0x6D, 7, _T(""));
						pRegTable->BitDetail[_T("ir_int_ultra")] = CBitDetail(0x6D, 6, _T(""));
						pRegTable->BitDetail[_T("ps_int_ultra")] = CBitDetail(0x6D, 5, _T(""));
						pRegTable->BitDetail[_T("adc_en")] = CBitDetail(0x6D, 4, _T(""));
						pRegTable->BitDetail[_T("ir_dark_comp_en")] = CBitDetail(0x6D, 2, _T(""));
						pRegTable->BitDetail[_T("ps_dark_comp_en")] = CBitDetail(0x6D, 1, _T(""));
						pRegTable->BitDetail[_T("als_dark_comp_en")] = CBitDetail(0x6D, 0, _T(""));
					}

					pRegTable->RegInfo[0x6E] = CRegInfo({ 0x67 }, _T("ATIME Unit"));
					{
						pRegTable->BitDetail[_T("AUNIT")] = CBitDetail(
							_T(""), _T(""),
							0x6E, 0xFF, 0, BOTH_RW, make_pair(0, 255), 103);
					}

					pRegTable->RegInfo[0x6F] = CRegInfo({ 0x30 }, _T("PTIME Unit"));
					{
						pRegTable->BitDetail[_T("PUNIT")] = CBitDetail(
							_T(""), _T(""),
							0x6F, 0xFF, 0, BOTH_RW, make_pair(0, 255), 48);
					}

					pRegTable->RegInfo[0x70] = CRegInfo({ 0x31 }, _T("ACH0 Temp Coef"));
					{
						pRegTable->BitDetail[_T("ATCF0a")] = CBitDetail(
							_T(""), _T(""),
							0x70, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x03);
						pRegTable->BitDetail[_T("ATCF0b")] = CBitDetail(
							_T(""), _T(""),
							0x70, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x01);
					}

					pRegTable->RegInfo[0x71] = CRegInfo({ 0x0F }, _T("ACH1 Temp Coef"));
					{
						pRegTable->BitDetail[_T("ATCF1a")] = CBitDetail(
							_T(""), _T(""),
							0x71, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x00);
						pRegTable->BitDetail[_T("ATCF1b")] = CBitDetail(
							_T(""), _T(""),
							0x71, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x0F);
					}

					pRegTable->RegInfo[0x72] = CRegInfo({ 0xCA }, _T("ACH2 Temp Coef"));
					{
						pRegTable->BitDetail[_T("ATCF2a")] = CBitDetail(
							_T(""), _T(""),
							0x72, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x0C);
						pRegTable->BitDetail[_T("ATCF2b")] = CBitDetail(
							_T(""), _T(""),
							0x72, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x0A);
					}

					pRegTable->RegInfo[0x73] = CRegInfo({ 0x1F }, _T("ACH3 Temp Coef"));
					{
						pRegTable->BitDetail[_T("ATCF3a")] = CBitDetail(
							_T(""), _T(""),
							0x73, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x01);
						pRegTable->BitDetail[_T("ATCF3b")] = CBitDetail(
							_T(""), _T(""),
							0x73, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x0F);
					}

					pRegTable->RegInfo[0x74] = CRegInfo({ 0x5E }, _T("PS Temp Coef"));
					{
						pRegTable->BitDetail[_T("PTCFa")] = CBitDetail(
							_T(""), _T(""),
							0x74, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x05);
						pRegTable->BitDetail[_T("PTCFb")] = CBitDetail(
							_T(""), _T(""),
							0x74, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x0E);
					}

					pRegTable->RegInfo[0x75] = CRegInfo({ 0xEB }, _T("IR Temp Coef"));
					{
						pRegTable->BitDetail[_T("IRTCFa")] = CBitDetail(
							_T(""), _T(""),
							0x75, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x0E);
						pRegTable->BitDetail[_T("IRTCFb")] = CBitDetail(
							_T(""), _T(""),
							0x75, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x0B);
					}

					pRegTable->RegInfo[0x76] = CRegInfo({ 0x56 }, _T("ALS Leakage Coef"));
					{
						pRegTable->BitDetail[_T("ALCF")] = CBitDetail(
							_T(""), _T(""),
							0x76, 0xFF, 0, BOTH_RW, make_pair(0, 255), 86);
					}

					pRegTable->RegInfo[0x77] = CRegInfo({ 0x00 }, _T("PS Leakage Coef"));
					{
						pRegTable->BitDetail[_T("PLCF")] = CBitDetail(
							_T(""), _T(""),
							0x77, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0);
					}

					pRegTable->RegInfo[0x78] = CRegInfo({ 0x05 }, _T("IR Leakage Coef"));
					{
						pRegTable->BitDetail[_T("IRLCF")] = CBitDetail(
							_T(""), _T(""),
							0x78, 0xFF, 0, BOTH_RW, make_pair(0, 255), 5);
					}

					pRegTable->RegInfo[0x79] = CRegInfo({ 0x64 }, _T("Time Slot"));
					{
						pRegTable->BitDetail[_T("SLOT")] = CBitDetail(
							_T(""), _T(""),
							0x79, 0x7F, 0, BOTH_RW, make_pair(0, 127), 100);
					}

					pRegTable->RegInfo[0x7A] = CRegInfo({ 0x00, 0x00 }, _T("Force FCH0"), 2);
					{
						pRegTable->BitDetail[_T("FFCH0/2/P/IR")] = CBitDetail(
							_T(""), _T(""),
							0x7A, { 0xFF, 0xFF },
							{ 0, 8 }, BOTH_RW,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
					}

					pRegTable->RegInfo[0x7C] = CRegInfo({ 0x00, 0x00 }, _T("Force FCH1"), 2);
					{
						pRegTable->BitDetail[_T("FFCH1/3")] = CBitDetail(
							_T(""), _T(""),
							0x7C, { 0xFF, 0xFF },
							{ 0, 8 }, BOTH_RW,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
					}

					pRegTable->RegInfo[0x7E] = CRegInfo({ 0x00, 0x00 }, _T("Force FTMP"), 2);
					{
						pRegTable->BitDetail[_T("FFTMP")] = CBitDetail(
							_T(""), _T(""),
							0x7E, { 0xFF, 0xFF },
							{ 0, 8 }, BOTH_RW,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
					}

					pRegTable->RegInfo[0xF0] = CRegInfo({ 0x00 }, _T("Rd Mode"));
					{
						pRegTable->BitDetail[_T("RD")] = CBitDetail(
							_T(""), _T(""),
							0xF0, 0x07, 0, BOTH_RW, make_pair(0, 7), 0);
					}

					pRegTable->RegInfo[0xF1] = CRegInfo({ 0x00 }, _T("Ram Check"));
					{
						pRegTable->BitDetail[_T("BRAM")] = CBitDetail(
							_T(""), _T(""),
							0xF1, 0xFF, 0, ONLY_R, make_pair(0, 255), 0);
					}

					pRegTable->RegInfo[0xF2] = CRegInfo({ 0x00, 0x00 }, _T("Rom Check"), 2);
					{
						pRegTable->BitDetail[_T("BROM")] = CBitDetail(
							_T(""), _T(""),
							0xF2, { 0xFF, 0xFF },
							{ 0, 8 }, ONLY_R,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
					}

					pRegTable->RegInfo[0xF4] = CRegInfo({ 0x09 }, _T("Fuse Read Width"));
					{
						pRegTable->BitDetail[_T("TRD")] = CBitDetail(
							_T(""), _T(""),
							0xF4, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x09);
					}

					pRegTable->RegInfo[0xF5] = CRegInfo({ 0x4A }, _T("Fuse Burn Width"));
					{
						pRegTable->BitDetail[_T("TBE")] = CBitDetail(
							_T(""), _T(""),
							0xF5, 0x7F, 0, BOTH_RW, make_pair(0, 127), 0x4A);
					}

					pRegTable->RegInfo[0xF6] = CRegInfo({ 0x00 }, _T("Fuse Program Enable"));
					{
						pRegTable->BitDetail[_T("BURN")] = CBitDetail(
							_T(""), _T(""),
							0xF6, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x00);
					}

					pRegTable->RegInfo[0xF7] = CRegInfo({ 0x00 }, _T("View Mode"));
					{
						pRegTable->BitDetail[_T("VIEW")] = CBitDetail(
							_T(""), _T(""),
							0xF7, 0x1F, 0, BOTH_RW, make_pair(0, 31), 0x00);
					}

					pRegTable->RegInfo[0xF8] = CRegInfo({ 0x00 }, _T("Analog En Control"));
					{
						pRegTable->BitDetail[_T("en_verf1")] = CBitDetail(0xF8, 3, _T(""));
						pRegTable->BitDetail[_T("en_ps")] = CBitDetail(0xF8, 2, _T(""));
						pRegTable->BitDetail[_T("en_osc")] = CBitDetail(0xF8, 1, _T(""));
						pRegTable->BitDetail[_T("en_bg")] = CBitDetail(0xF8, 0, _T(""));
					}

					pRegTable->RegInfo[0xFE] = CRegInfo({ 0x00 }, _T("I2C Watch Dog"));
					{
						pRegTable->BitDetail[_T("WDOG")] = CBitDetail(
							_T(""), _T(""),
							0xFE, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x00);
					}
				}
			}
			break;
		case 13000:
			DieDetail.insert(make_pair(13000, CDieDetail()));
			{
				pDieDetail = &DieDetail.at(13000);
				pRegTable = &pDieDetail->RegisterTable;

				pRegTable->DeviceID = 0x1C;
				pRegTable->RegInfo[0x00] = CRegInfo({ 0x00 }, _T("SysCtr"));
				{
					pRegTable->BitDetail[_T("IFGCRM")] = CBitDetail(0x00, 7, _T("Interrupt Clear Method"));
					pRegTable->BitDetail[_T("SWRST")] = CBitDetail(0x00, 6, _T("Software Reset"));
					pRegTable->BitDetail[_T("IREN")] = CBitDetail(0x00, 2, _T("IR Enable"));
					pRegTable->BitDetail[_T("PEN")] = CBitDetail(0x00, 1, _T("PS Enable"));
					pRegTable->BitDetail[_T("AEN")] = CBitDetail(0x00, 0, _T("ALS Enable"));
				}

				pRegTable->RegInfo[0x01] = CRegInfo({ 0x80 }, _T("IntFlag"));
				{
					pRegTable->BitDetail[_T("PORINT")] = CBitDetail(0x01, 7, _T("POR INT"));
					pRegTable->BitDetail[_T("IRINT")] = CBitDetail(0x01, 2, _T("IR INT"));
					pRegTable->BitDetail[_T("PINT")] = CBitDetail(0x01, 1, _T("PS INT"));
					pRegTable->BitDetail[_T("AINT")] = CBitDetail(0x01, 0, _T("ALS INT"));
				}

				pRegTable->RegInfo[0x02] = CRegInfo({ 0x03 }, _T("IntCtr"));
				{
					pRegTable->BitDetail[_T("IRPEND")] = CBitDetail(0x02, 6, _T("Suspend IR Function Control"));
					pRegTable->BitDetail[_T("PPEND")] = CBitDetail(0x02, 5, _T("Suspend PS Function Control"));
					pRegTable->BitDetail[_T("APEND")] = CBitDetail(0x02, 4, _T("Suspend ALS Function Control"));
					pRegTable->BitDetail[_T("IRIEN")] = CBitDetail(0x02, 2, _T("IR Interrupt Pin"));
					pRegTable->BitDetail[_T("PIEN")] = CBitDetail(0x02, 1, _T("PS Interrupt Pin"), 0x01);
					pRegTable->BitDetail[_T("AIEN")] = CBitDetail(0x02, 0, _T("ALS Interrupt Pin"), 0x01);
				}

				pRegTable->RegInfo[0x03] = CRegInfo({ 0x02 }, _T("Manufacturer ID"));
				pRegTable->RegInfo[0x04] = CRegInfo({ 0x12 }, _T("Product ID"));
				pRegTable->RegInfo[0x05] = CRegInfo({ 0x02 }, _T("Revision ID"));

				pRegTable->RegInfo[0x06] = CRegInfo({ 0x03 }, _T("WaitTime"));
				{
					pRegTable->BitDetail[_T("WUNIT")] = CBitDetail(0x06, 7, _T("Waiting Time Unit"));

					pRegTable->BitDetail[_T("WTIME")] = CBitDetail(
						_T("Waiting Time"), _T(""),
						0x06, 0x7F, 0, BOTH_RW, make_pair(0, 127), 0x03);
				}

				pRegTable->RegInfo[0x07] = CRegInfo({ 0x01 }, _T("AlsPers"));
				{
					pRegTable->BitDetail[_T("APERS")] = CBitDetail(
						_T("ALS Persistence"), _T(""),
						0x07, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x01);
				}

				pRegTable->RegInfo[0x08] = CRegInfo({ 0x00 }, _T("AlsCtr"));
				{
					pRegTable->BitDetail[_T("ASRC")] = CBitDetail(
						_T("Select ADATA Source"), _T(""),
						0x08, 0x30, 4, BOTH_RW, make_pair(0, 4), 0x00);

					pRegTable->BitDetail[_T("AGAIN")] = CBitDetail(
						_T("ALS Sensing Gain"), _T(""),
						0x08, 0x07, 0, BOTH_RW, make_pair(0, 6), 0x00);
				}

				pRegTable->RegInfo[0x09] = CRegInfo({ 0x00 }, _T("AlsTime"));
				{
					pRegTable->BitDetail[_T("ATIME")] = CBitDetail(
						_T("ALS Time"), _T(""),
						0x09, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x0C] = CRegInfo({ 0x01 }, _T("PsPers"));
				{
					pRegTable->BitDetail[_T("PPERS")] = CBitDetail(
						_T("PS Persistence"), _T(""),
						0x0C, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x01);
				}

				pRegTable->RegInfo[0x0D] = CRegInfo({ 0x02 }, _T("PsMean"));
				{
					pRegTable->BitDetail[_T("PMEAN")] = CBitDetail(
						_T("PS Mean"), _T(""),
						0x0D, 0x07, 0, BOTH_RW, make_pair(0, 6), 0x02);
				}

				pRegTable->RegInfo[0x0E] = CRegInfo({ 0x10 }, _T("PsCtr"));
				{
					pRegTable->BitDetail[_T("PACC")] = CBitDetail(0x0E, 5, _T("PS Acceleration"));
					pRegTable->BitDetail[_T("PMODE")] = CBitDetail(0x0E, 4, _T("PS Interrupt Mode"), 0x01);
				}

				pRegTable->RegInfo[0x0F] = CRegInfo({ 0x00 }, _T("PsTime"));
				{
					pRegTable->BitDetail[_T("PTIME")] = CBitDetail(
						_T("PS Time"), _T(""),
						0x0F, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x00);
				}

				pRegTable->RegInfo[0x10] = CRegInfo({ 0x00 }, _T("PsLedPuW"));
				{
					pRegTable->BitDetail[_T("PLPUW")] = CBitDetail(
						_T("PS LED Pulse Width"), _T(""),
						0x10, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x11] = CRegInfo({ 0x00 }, _T("PsLedPuC"));
				{
					pRegTable->BitDetail[_T("PLPUC")] = CBitDetail(
						_T("PS LED Pulse Count"), _T(""),
						0x11, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x00);
				}

				pRegTable->RegInfo[0x12] = CRegInfo({ 0x10 }, _T("PsLedDrv"));
				{
					pRegTable->BitDetail[_T("PLOFF")] = CBitDetail(0x12, 7, _T("Turn Off PS LED"));
					pRegTable->BitDetail[_T("PLDC")] = CBitDetail(0x12, 6, _T("Force PS LED as DC"));
					pRegTable->BitDetail[_T("PLASER")] = CBitDetail(0x12, 4, _T("Set LED Maxinum Current"), 0x01);

					pRegTable->BitDetail[_T("PLDR")] = CBitDetail(
						_T("PS LED Driving Current"), _T(""),
						0x12, 0x03, 0, BOTH_RW, make_pair(0, 3), 0x00);
				}

				pRegTable->RegInfo[0x13] = CRegInfo({ 0x00 }, _T("PsCtDac"));
				{
					pRegTable->BitDetail[_T("PCTGAIN")] = CBitDetail(
						_T("Crosstalk DAC gain"), _T(""),
						0x13, 0xC0, 6, BOTH_RW, make_pair(0, 2), 0x00);

					pRegTable->BitDetail[_T("PCTDAC")] = CBitDetail(
						_T("Crosstalk DAC step"), _T(""),
						0x13, 0x1F, 0, BOTH_RW, make_pair(0, 31), 0x00);
				}

				pRegTable->RegInfo[0x16] = CRegInfo({ 0x02 }, _T("IrMean"));
				{
					pRegTable->BitDetail[_T("IRMEAN")] = CBitDetail(
						_T("IR Mean"), _T(""),
						0x16, 0x07, 0, BOTH_RW, make_pair(0, 6), 0x02);
				}

				pRegTable->RegInfo[0x18] = CRegInfo({ 0x00 }, _T("IrTime"));
				{
					pRegTable->BitDetail[_T("IRTIME")] = CBitDetail(
						_T("IR Time"), _T(""),
						0x18, 0x3F, 0, BOTH_RW, make_pair(0, 63), 0x00);
				}

				pRegTable->RegInfo[0x19] = CRegInfo({ 0x00 }, _T("IrPuW"));
				{
					pRegTable->BitDetail[_T("IRPUW")] = CBitDetail(
						_T("IR LED Pulse Width"), _T(""),
						0x19, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0x00);
				}

				pRegTable->RegInfo[0x1E] = CRegInfo({ 0x00 }, _T("FlagStat"));
				{
					pRegTable->BitDetail[_T("OBJ")] = CBitDetail(0x1E, 7, _T("Object Detection"));
					pRegTable->BitDetail[_T("IRERR")] = CBitDetail(0x1E, 2, _T("IR Error"));
					pRegTable->BitDetail[_T("PERR")] = CBitDetail(0x1E, 1, _T("PS Error"));
					pRegTable->BitDetail[_T("AERR")] = CBitDetail(0x1E, 0, _T("ALS Error"));
				}

				pRegTable->RegInfo[0x20] = CRegInfo({ 0x00, 0x00 }, _T("TempAdc"), 2);
				{
					pRegTable->BitDetail[_T("TADC")] = CBitDetail(
						_T("Temperature ADC"), _T(""),
						0x20, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x22] = CRegInfo({ 0x00, 0x00 }, _T("TempOrg"), 2);
				{
					pRegTable->BitDetail[_T("TORG")] = CBitDetail(
						_T("Temperature Original"), _T(""),
						0x22, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x24] = CRegInfo({ 0x00, 0x00 }, _T("TempCh"), 2);
				{
					pRegTable->BitDetail[_T("TCH")] = CBitDetail(
						_T("Temperature Channel"), _T(""),
						0x24, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x28] = CRegInfo({ 0x00, 0x00 }, _T("PsCh"), 2);
				{
					pRegTable->BitDetail[_T("PCH")] = CBitDetail(
						_T("PS Channel"), _T(""),
						0x28, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2A] = CRegInfo({ 0x00, 0x00 }, _T("IrCh"), 2);
				{
					pRegTable->BitDetail[_T("IRCH")] = CBitDetail(
						_T("PS Channel"), _T(""),
						0x2A, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2C] = CRegInfo({ 0x00, 0x00 }, _T("AlsCh0"), 2);
				{
					pRegTable->BitDetail[_T("ACH0")] = CBitDetail(
						_T("ALS Channel 0"), _T(""),
						0x2C, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x2E] = CRegInfo({ 0x00, 0x00 }, _T("AlsCh1"), 2);
				{
					pRegTable->BitDetail[_T("ACH1")] = CBitDetail(
						_T("ALS Channel 1"), _T(""),
						0x2E, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x30] = CRegInfo({ 0x00, 0x00 }, _T("AlsCh2"), 2);
				{
					pRegTable->BitDetail[_T("ACH2")] = CBitDetail(
						_T("ALS Channel 2"), _T(""),
						0x30, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x32] = CRegInfo({ 0x00, 0x00 }, _T("AlsCh3"), 2);
				{
					pRegTable->BitDetail[_T("ACH3")] = CBitDetail(
						_T("ALS Channel 3"), _T(""),
						0x32, { 0xFF, 0xFF },
						{ 0, 8 }, ONLY_R,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x36] = CRegInfo({ 0x00, 0x00 }, _T("AlsLowTh"), 2);
				{
					pRegTable->BitDetail[_T("ALTH")] = CBitDetail(
						_T("ALS Low Threshold"), _T(""),
						0x36, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x38] = CRegInfo({ 0xFF, 0xFF }, _T("AlsHighTh"), 2);
				{
					pRegTable->BitDetail[_T("AHTH")] = CBitDetail(
						_T("ALS High Threshold"), _T(""),
						0x38, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0xFF, 0xFF });
				}

				pRegTable->RegInfo[0x3A] = CRegInfo({ 0x00, 0x00 }, _T("PsLowTh"), 2);
				{
					pRegTable->BitDetail[_T("PLTH")] = CBitDetail(
						_T("PS Low Threshold"), _T(""),
						0x3A, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0x00, 0x00 });
				}

				pRegTable->RegInfo[0x3C] = CRegInfo({ 0xFF, 0xFF }, _T("PsHighTh"), 2);
				{
					pRegTable->BitDetail[_T("PHTH")] = CBitDetail(
						_T("PS High Threshold"), _T(""),
						0x3C, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 7) }, { 0xFF, 0xFF });
				}


				pRegTable->RegInfo[0x3E] = CRegInfo({ 0x00, 0x00 }, _T("PsCalb"), 2);
				{
					pRegTable->BitDetail[_T("PCALB")] = CBitDetail(
						_T("PS Calibration"), _T(""),
						0x3E, { 0xFF, 0xFF },
						{ 0, 8 }, BOTH_RW,
						{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
				}

				/* RD Mode */
				{
					/* Fuse0 ~ Fuse7 */
					for (int i = 0; i < 8; i++)
					{
						CString csTemp = _T("");
						csTemp.Format(_T("Fuse%d"), i);
						pRegTable->RegInfo[0x60 + i] = CRegInfo({ 0x00 }, csTemp);
						for (int j = 0; j < 8; j++)
						{
							csTemp.Format(_T("FIELD%d"), i * 8 + j);
							pRegTable->BitDetail[csTemp] = CBitDetail(_T(""), _T(""), 0x60 + i, 0xFF, 0, ONLY_R);
						}
					}

					pRegTable->RegInfo[0x68] = CRegInfo({ 0x9A, 0x05 }, _T("TempTarget"), 2);
					{
						pRegTable->BitDetail[_T("TTAR")] = CBitDetail(
							_T("Temperature"), _T(""),
							0x68, { 0xFF, 0xFF },
							{ 0, 8 }, BOTH_RW,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x9A, 0x05 });
					}

					pRegTable->RegInfo[0x6A] = CRegInfo({ 0x01 }, _T("Rd Control0"));
					{
						pRegTable->BitDetail[_T("FORCE")] = CBitDetail(0x6A, 7, _T("Use Force Data"));
						pRegTable->BitDetail[_T("IRPXSH")] = CBitDetail(0x6A, 2, _T("Enable \"pxsh\" at IR"));
						pRegTable->BitDetail[_T("PPXSH")] = CBitDetail(0x6A, 1, _T("Enable \"pxsh\" at PS"));
						pRegTable->BitDetail[_T("GATTING")] = CBitDetail(0x6A, 0, _T("Gating MCU when sleep"), 0x01);
					}

					pRegTable->RegInfo[0x6B] = CRegInfo({ 0x16 }, _T("Rd Control1"));
					{
						pRegTable->BitDetail[_T("vref_op_set")] = CBitDetail(
							_T("Contorl Vref L2F OP Current"), _T(""),
							0x6B, 0xC0, 6, BOTH_RW, make_pair(0, 3), 0x00);
						pRegTable->BitDetail[_T("vtopf_set")] = CBitDetail(
							_T("Control ADC Vtop"), _T(""),
							0x6B, 0x30, 4, BOTH_RW, make_pair(0, 3), 0x01);
						pRegTable->BitDetail[_T("vdiode_sel")] = CBitDetail(
							_T("Control All Diode voltage"), _T(""),
							0x6B, 0x0C, 2, BOTH_RW, make_pair(0, 3), 0x01);
						pRegTable->BitDetail[_T("clkm_vbs")] = CBitDetail(
							_T("Control the pin \"clkm_vbs\""), _T(""),
							0x6B, 0x03, 0, BOTH_RW, make_pair(0, 3), 0x02);
					}

					pRegTable->RegInfo[0x6C] = CRegInfo({ 0x0F }, _T("Rd Control2"));
					{
						pRegTable->BitDetail[_T("prst_fall_en")] = CBitDetail(0x6C, 6, _T(""));
						pRegTable->BitDetail[_T("pxy_v2i_sel")] = CBitDetail(
							_T(""), _T(""),
							0x6C, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x0F);
					}

					pRegTable->RegInfo[0x6D] = CRegInfo({ 0x00 }, _T("Rd Control3"));
					{
						pRegTable->BitDetail[_T("temp_mux")] = CBitDetail(0x6D, 7, _T(""));
						pRegTable->BitDetail[_T("ir_int_ultra")] = CBitDetail(0x6D, 6, _T(""));
						pRegTable->BitDetail[_T("ps_int_ultra")] = CBitDetail(0x6D, 5, _T(""));
						pRegTable->BitDetail[_T("adc_en")] = CBitDetail(0x6D, 4, _T(""));
						pRegTable->BitDetail[_T("ir_dark_comp_en")] = CBitDetail(0x6D, 2, _T(""));
						pRegTable->BitDetail[_T("ps_dark_comp_en")] = CBitDetail(0x6D, 1, _T(""));
						pRegTable->BitDetail[_T("als_dark_comp_en")] = CBitDetail(0x6D, 0, _T(""));
					}

					pRegTable->RegInfo[0x6E] = CRegInfo({ 0x67 }, _T("ATIME Unit"));
					{
						pRegTable->BitDetail[_T("AUNIT")] = CBitDetail(
							_T(""), _T(""),
							0x6E, 0xFF, 0, BOTH_RW, make_pair(0, 255), 103);
					}

					pRegTable->RegInfo[0x6F] = CRegInfo({ 0x30 }, _T("PTIME Unit"));
					{
						pRegTable->BitDetail[_T("PUNIT")] = CBitDetail(
							_T(""), _T(""),
							0x6F, 0xFF, 0, BOTH_RW, make_pair(0, 255), 48);
					}

					pRegTable->RegInfo[0x70] = CRegInfo({ 0x0F }, _T("ACH0 Temp Coef"));
					{
						pRegTable->BitDetail[_T("ATCF0a")] = CBitDetail(
							_T(""), _T(""),
							0x70, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x00);
						pRegTable->BitDetail[_T("ATCF0b")] = CBitDetail(
							_T(""), _T(""),
							0x70, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x0F);
					}

					pRegTable->RegInfo[0x71] = CRegInfo({ 0x04 }, _T("ACH1 Temp Coef"));
					{
						pRegTable->BitDetail[_T("ATCF1a")] = CBitDetail(
							_T(""), _T(""),
							0x71, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x00);
						pRegTable->BitDetail[_T("ATCF1b")] = CBitDetail(
							_T(""), _T(""),
							0x71, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x04);
					}

					pRegTable->RegInfo[0x72] = CRegInfo({ 0x00 }, _T("ACH2 Temp Coef"));
					{
						pRegTable->BitDetail[_T("ATCF2a")] = CBitDetail(
							_T(""), _T(""),
							0x72, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x00);
						pRegTable->BitDetail[_T("ATCF2b")] = CBitDetail(
							_T(""), _T(""),
							0x72, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x00);
					}

					pRegTable->RegInfo[0x73] = CRegInfo({ 0x00 }, _T("ACH3 Temp Coef"));
					{
						pRegTable->BitDetail[_T("ATCF3a")] = CBitDetail(
							_T(""), _T(""),
							0x73, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x00);
						pRegTable->BitDetail[_T("ATCF3b")] = CBitDetail(
							_T(""), _T(""),
							0x73, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x00);
					}

					pRegTable->RegInfo[0x74] = CRegInfo({ 0x4F }, _T("PS Temp Coef"));
					{
						pRegTable->BitDetail[_T("PTCFa")] = CBitDetail(
							_T(""), _T(""),
							0x74, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x04);
						pRegTable->BitDetail[_T("PTCFb")] = CBitDetail(
							_T(""), _T(""),
							0x74, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x0F);
					}

					pRegTable->RegInfo[0x75] = CRegInfo({ 0xB8 }, _T("IR Temp Coef"));
					{
						pRegTable->BitDetail[_T("IRTCFa")] = CBitDetail(
							_T(""), _T(""),
							0x75, 0xF0, 4, BOTH_RW, make_pair(0, 15), 0x0B);
						pRegTable->BitDetail[_T("IRTCFb")] = CBitDetail(
							_T(""), _T(""),
							0x75, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x08);
					}

					pRegTable->RegInfo[0x76] = CRegInfo({ 0x85 }, _T("ALS Leakage Coef"));
					{
						pRegTable->BitDetail[_T("ALCF")] = CBitDetail(
							_T(""), _T(""),
							0x76, 0xFF, 0, BOTH_RW, make_pair(0, 255), 133);
					}

					pRegTable->RegInfo[0x77] = CRegInfo({ 0x00 }, _T("PS Leakage Coef"));
					{
						pRegTable->BitDetail[_T("PLCF")] = CBitDetail(
							_T(""), _T(""),
							0x77, 0xFF, 0, BOTH_RW, make_pair(0, 255), 0);
					}

					pRegTable->RegInfo[0x78] = CRegInfo({ 0x05 }, _T("IR Leakage Coef"));
					{
						pRegTable->BitDetail[_T("IRLCF")] = CBitDetail(
							_T(""), _T(""),
							0x78, 0xFF, 0, BOTH_RW, make_pair(0, 255), 5);
					}

					pRegTable->RegInfo[0x79] = CRegInfo({ 0x64 }, _T("Time Slot"));
					{
						pRegTable->BitDetail[_T("SLOT")] = CBitDetail(
							_T(""), _T(""),
							0x79, 0x7F, 0, BOTH_RW, make_pair(0, 127), 100);
					}

					pRegTable->RegInfo[0x7A] = CRegInfo({ 0x00, 0x00 }, _T("Force FCH0"), 2);
					{
						pRegTable->BitDetail[_T("FFCH0/2/P/IR")] = CBitDetail(
							_T(""), _T(""),
							0x7A, { 0xFF, 0xFF },
							{ 0, 8 }, BOTH_RW,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
					}

					pRegTable->RegInfo[0x7C] = CRegInfo({ 0x00, 0x00 }, _T("Force FCH1"), 2);
					{
						pRegTable->BitDetail[_T("FFCH1/3")] = CBitDetail(
							_T(""), _T(""),
							0x7C, { 0xFF, 0xFF },
							{ 0, 8 }, BOTH_RW,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
					}

					pRegTable->RegInfo[0x7E] = CRegInfo({ 0x00, 0x00 }, _T("Force FTMP"), 2);
					{
						pRegTable->BitDetail[_T("FFTMP")] = CBitDetail(
							_T(""), _T(""),
							0x7E, { 0xFF, 0xFF },
							{ 0, 8 }, BOTH_RW,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
					}

					pRegTable->RegInfo[0xF0] = CRegInfo({ 0x00 }, _T("Rd Mode"));
					{
						pRegTable->BitDetail[_T("RD")] = CBitDetail(
							_T(""), _T(""),
							0xF0, 0x07, 0, BOTH_RW, make_pair(0, 7), 0);
					}

					pRegTable->RegInfo[0xF1] = CRegInfo({ 0x00 }, _T("Ram Check"));
					{
						pRegTable->BitDetail[_T("BRAM")] = CBitDetail(
							_T(""), _T(""),
							0xF1, 0xFF, 0, ONLY_R, make_pair(0, 255), 0);
					}

					pRegTable->RegInfo[0xF2] = CRegInfo({ 0x00, 0x00 }, _T("Rom Check"), 2);
					{
						pRegTable->BitDetail[_T("BROM")] = CBitDetail(
							_T(""), _T(""),
							0xF2, { 0xFF, 0xFF },
							{ 0, 8 }, ONLY_R,
							{ make_pair(0, 255), make_pair(0, 255) }, { 0x00, 0x00 });
					}

					pRegTable->RegInfo[0xF4] = CRegInfo({ 0x09 }, _T("Fuse Read Width"));
					{
						pRegTable->BitDetail[_T("TRD")] = CBitDetail(
							_T(""), _T(""),
							0xF4, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x09);
					}

					pRegTable->RegInfo[0xF5] = CRegInfo({ 0x4A }, _T("Fuse Burn Width"));
					{
						pRegTable->BitDetail[_T("TBE")] = CBitDetail(
							_T(""), _T(""),
							0xF5, 0x7F, 0, BOTH_RW, make_pair(0, 127), 0x4A);
					}

					pRegTable->RegInfo[0xF6] = CRegInfo({ 0x00 }, _T("Fuse Program Enable"));
					{
						pRegTable->BitDetail[_T("BURN")] = CBitDetail(
							_T(""), _T(""),
							0xF6, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x00);
					}

					pRegTable->RegInfo[0xF7] = CRegInfo({ 0x00 }, _T("View Mode"));
					{
						pRegTable->BitDetail[_T("VIEW")] = CBitDetail(
							_T(""), _T(""),
							0xF6, 0x1F, 0, BOTH_RW, make_pair(0, 31), 0x00);
					}

					pRegTable->RegInfo[0xF8] = CRegInfo({ 0x00 }, _T("Analog En Control"));
					{
						pRegTable->BitDetail[_T("en_verf1")] = CBitDetail(0xF8, 3, _T(""));
						pRegTable->BitDetail[_T("en_ps")] = CBitDetail(0xF8, 2, _T(""));
						pRegTable->BitDetail[_T("en_osc")] = CBitDetail(0xF8, 1, _T(""));
						pRegTable->BitDetail[_T("en_bg")] = CBitDetail(0xF8, 0, _T(""));
					}

					pRegTable->RegInfo[0xFE] = CRegInfo({ 0x00 }, _T("I2C Watch Dog"));
					{
						pRegTable->BitDetail[_T("WDOG")] = CBitDetail(
							_T(""), _T(""),
							0xFE, 0x0F, 0, BOTH_RW, make_pair(0, 15), 0x00);
					}
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
		case 11000:
		{
			pDieDetail = &DieDetail.at(11000);
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
			if (Reg0x00 & pBitDetailMap->at(_T("AEN")).BitMask.at(0))
			{
				//T_ALS
				ConversionTime += (4.51 + (pRegTable->GetBitValue(_T("AUNIT")) / 100.0) * pRegTable->GetBitValue(_T("ATIME")));
			}

			if (Reg0x00 & pBitDetailMap->at(_T("PEN")).BitMask.at(0))
			{
				//T_PS
				ConversionTime += (3.4 + pow(2, pRegTable->GetBitValue(_T("PMEAN")))
					* (1.06 + (pRegTable->GetBitValue(_T("PUNIT")) / 100.0) * pRegTable->GetBitValue(_T("PTIME"))
						+ (0.092 + 0.004 * pRegTable->GetBitValue(_T("PLPUW"))
							* ((double)pRegTable->GetBitValue(_T("PLPUC")) + 1))));
				//T_LED
				ConversionTime += ((pow(2, pRegTable->GetBitValue(_T("PMEAN")))
					* (22 + 2 * (double)pRegTable->GetBitValue(_T("PLPUW")))
					* ((double)pRegTable->GetBitValue(_T("PLPUC")) + 1)) / 1000);
			}

			if (Reg0x00 & pBitDetailMap->at(_T("IREN")).BitMask.at(0))
			{
				//T_IR
				ConversionTime += (3.4 + pow(2, pRegTable->GetBitValue(_T("IRMEAN")))
					* (1.06 + (pRegTable->GetBitValue(_T("PUNIT")) / 100.0) * pRegTable->GetBitValue(_T("IRTIME"))
						+ (0.092 + 0.004 * pRegTable->GetBitValue(_T("IRPUW")))));
			}

			if (pRegTable->GetBitValue(_T("WTIME")) > 0)
			{
				//T_WAIT
				ConversionTime += 1.22 + (pRegTable->GetBitValue(_T("WUNIT")) == 0 ? 2 : 20)
					* (double)pRegTable->GetBitValue(_T("WTIME"));
			}
			break;
		case 11000:
			if (Reg0x00 & pBitDetailMap->at(_T("AEN")).BitMask.at(0))
			{
				//T_ALS
				ConversionTime += (4.51 + (pRegTable->GetBitValue(_T("AUNIT")) / 100.0) * pRegTable->GetBitValue(_T("ATIME")));
			}

			if (Reg0x00 & pBitDetailMap->at(_T("PEN")).BitMask.at(0))
			{
				//T_PS
				ConversionTime += (3.4 + pow(2, pRegTable->GetBitValue(_T("PMEAN")))
					* (0.51 + ((double)pRegTable->GetBitValue(_T("PUNIT")) / 100.0) * (double)pRegTable->GetBitValue(_T("PTIME"))
						+ (0.092 + 0.004 * pRegTable->GetBitValue(_T("PLPUW"))
							* ((double)pRegTable->GetBitValue(_T("PLPUC")) + 1))));
				//T_LED
				//ConversionTime += ((pow(2, pRegTable->GetBitValue(_T("PMEAN")))
				//	* (22 + 2 * pRegTable->GetBitValue(_T("PLPUW"))) 
				//		* (pRegTable->GetBitValue(_T("PLPUC")) + 1)) / 1000);
			}

			if (Reg0x00 & pBitDetailMap->at(_T("IREN")).BitMask.at(0))
			{
				//T_IR
				ConversionTime += (3.4 + pow(2, pRegTable->GetBitValue(_T("IRMEAN")))
					* (0.51 + (pRegTable->GetBitValue(_T("PUNIT")) / 100.0) * pRegTable->GetBitValue(_T("IRTIME"))
						+ (0.092 + 0.004 * pRegTable->GetBitValue(_T("IRPUW")))));
			}

			if (pRegTable->GetBitValue(_T("WTIME")) > 0)
			{
				//T_WAIT
				ConversionTime += 1.22 + (pRegTable->GetBitValue(_T("WUNIT")) == 0 ? 2 : 20) 
					* (double)pRegTable->GetBitValue(_T("WTIME"));
			}
			break;
		case 12000:
		case 12001:
		case 13000:
			if (Reg0x00 & pBitDetailMap->at(_T("AEN")).BitMask.at(0))
			{
				//T_ALS
				ConversionTime += (4.5 + ((double)pRegTable->GetBitValue(_T("AUNIT")) / 100.0) * pRegTable->GetBitValue(_T("ATIME")));
			}

			if (Reg0x00 & pBitDetailMap->at(_T("PEN")).BitMask.at(0))
			{
				//T_PS
				ConversionTime += pow(2, pRegTable->GetBitValue(_T("PMEAN")))
					* (4.1 + ((double)pRegTable->GetBitValue(_T("PUNIT")) / 100.0) * (double)pRegTable->GetBitValue(_T("PTIME"))
						+ (0.092 + 0.004 * pRegTable->GetBitValue(_T("PLPUW"))
							* ((double)pRegTable->GetBitValue(_T("PLPUC")) + 1)));
				//T_LED
				//ConversionTime += ((pow(2, pRegTable->GetBitValue(_T("PMEAN")))
				//	* (22 + 2 * pRegTable->GetBitValue(_T("PLPUW")))
				//	* (pRegTable->GetBitValue(_T("PLPUC")) + 1)) / 1000);
			}

			if (Reg0x00 & pBitDetailMap->at(_T("IREN")).BitMask.at(0))
			{
				//T_IR
				ConversionTime += pow(2, pRegTable->GetBitValue(_T("IRMEAN")))
					* (4.1 + ((double)pRegTable->GetBitValue(_T("PUNIT")) / 100.0) * (double)pRegTable->GetBitValue(_T("IRTIME"))
						+ (0.092 + 0.004 * (double)pRegTable->GetBitValue(_T("IRPUW"))));
			}

			if (pRegTable->GetBitValue(_T("WTIME")) > 0)
			{
				//T_WAIT
				ConversionTime += 1.22 + (pRegTable->GetBitValue(_T("WUNIT")) == 0 ? 2 : 20)
					* (double)pRegTable->GetBitValue(_T("WTIME"));
			}
			break;
		}

		return (uint32_t)(ConversionTime * 1000);
	}
};