#pragma once
#include "Define.h"

class CDA3290 : public CDieInfo {
public:
	CDA3290() {}
	void Init(uint16_t version)
	{
		DieName = _T("DA3290");
		switch (version)
		{
		case 10000:
			DieDetail.insert(make_pair(10000, CDieDetail()));
			{
				pDieDetail = &DieDetail.at(10000);

				pRegTable = &pDieDetail->RegisterTable;

				pRegTable->DeviceID = 0x1C;

				pRegTable->SetRegAddr(0xF0);
				pRegTable->SetRegInfo({ 0x00 }, _T("DevCtrl"));
				{
					pRegTable->SetBitDetail(_T("AlsEn"), 0, _T("ALS Enable"));
				}

				pRegTable->SetRegAddr(0xF1);
				pRegTable->SetRegInfo({ 0x03 }, _T("IntCtrl"));
				{
					pRegTable->SetBitDetail(_T("DataIntEn"), 4, _T("Data Int Enable"));
					pRegTable->SetBitDetail(_T("Reserved0xF1_1"), 1, _T("Reserved0xF1_1"), 0x01);
					pRegTable->SetBitDetail(_T("AlsIntEn"), 0, _T("ALS Int Enable"), 0x01);
				}

				pRegTable->SetRegAddr(0xF2);
				pRegTable->SetRegInfo({ 0x00 }, _T("HaltCtrl"));
				{
					pRegTable->SetBitDetail(_T("ReadClear"), 7, _T("Interrupt clear method"));
					pRegTable->SetBitDetail(_T("DataHalt"), 4, _T("Data Halt Control Bit"));
					pRegTable->SetBitDetail(_T("AlsHalt"), 0, _T("ALS Halt Function Control Bit"));
				}

				pRegTable->SetRegAddr(0xF3);
				pRegTable->SetRegInfo({ 0x00 }, _T("SysCtrl"));
				{
					pRegTable->SetBitDetail(_T("PorFen"), 7, _T("Enable Falling POR"));
					pRegTable->SetBitDetail(_T("VbgPuw"), 4, _T("Vbg Puw"));
					pRegTable->SetBitDetail(_T("Operation"), 0, _T("Openation Mode"));
				}

				pRegTable->SetRegAddr(0xF4);
				pRegTable->SetRegInfo({ 0x00 }, _T("SwRst"));
				{
					pRegTable->SetBitDetail(_T("SoftReset"), _T("Software Reset"), _T(""), 0xEE);	//write 0xEE to reset
				}

				pRegTable->SetRegAddr(0xF5);
				pRegTable->SetRegInfo({ 0x00 }, _T("IoCtrl"));
				{
					pRegTable->SetBitDetail(_T("PushPull"), 7, _T("INT pin is Push Pull"));
					pRegTable->SetBitDetail(_T("IoFunc"), _T("Change INT pin output"), 0x03, 0, BOTH_RW, { 0, 0x03 });
				}

				pRegTable->SetRegAddr(0xFB);
				pRegTable->SetRegInfo({ 0x00 }, _T("LoscData"));
				{
					pRegTable->SetBitDetail(_T("LoscData"), _T("LOSC Period= LoscData x 800ns"), 0xFF, 0, ONLY_R);
				}

				pRegTable->SetRegAddr(0xFC);
				pRegTable->SetRegInfo({ 0x1A }, _T("IDPod"));
				{
					pRegTable->SetBitDetail(_T("IDPod"), _T("IDPod"), 0xFF, 0, ONLY_R);
				}

				pRegTable->SetRegAddr(0xFD);
				pRegTable->SetRegInfo({ 0x00 }, _T("IDRev"));
				{
					pRegTable->SetBitDetail(_T("IDRev"), _T("IDRev"), 0xFF, 0, ONLY_R);
				}

				pRegTable->SetRegAddr(0xFE);
				pRegTable->SetRegInfo({ 0x80 }, _T("IntFlag"));
				{
					pRegTable->SetBitDetail(_T("PorInt"), 7, _T("POR INT"), 1);
					pRegTable->SetBitDetail(_T("DataInt"), 4, _T("Data INT"));
					pRegTable->SetBitDetail(_T("AlsInt"), 0, _T("ALS INT"));
				}

				pRegTable->SetRegAddr(0xFF);
				pRegTable->SetRegInfo({ 0x80 }, _T("StatFlag"));
				{
					pRegTable->SetBitDetail(_T("TmpErr"), 5, _T("TmpData Invalid Flag"));
					pRegTable->SetBitDetail(_T("AlsErr"), 0, _T("AlsData0~1 Invalid Flag"));
				}

				pRegTable->SetRegAddr(0x04);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("AlsData0"), 2);
				{
					pRegTable->SetBitDetail2(_T("AlsData0"), _T("AlsData0"));
				}

				pRegTable->SetRegAddr(0x06);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("AlsData1"), 2);
				{
					pRegTable->SetBitDetail2(_T("AlsData1"), _T("AlsData1"));
				}

				pRegTable->SetRegAddr(0x0C);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("AmbData"), 2);
				{
					pRegTable->SetBitDetail2(_T("AmbData"), _T("AmbData"));
				}

				pRegTable->SetRegAddr(0x0E);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("TmpData"), 2);
				{
					pRegTable->SetBitDetail2(_T("TmpData"), _T("TmpData"));
				}

				pRegTable->SetRegAddr(0x4F);
				pRegTable->SetRegInfo({ 0x00 }, _T("WaitTime"));
				{
					pRegTable->SetBitDetail(_T("WaitTime"), _T("The extra time for saving power:"));
				}

				pRegTable->SetRegAddr(0x50);
				pRegTable->SetRegInfo({ 0x22 }, _T("AlsCtrl"));
				{
					pRegTable->SetBitDetail(_T("AlsGain1"), _T("AlsData1 Gain"), 0x70, 4, BOTH_RW, { 0, 0x07 }, 0x02);
					pRegTable->SetBitDetail(_T("AlsGain0"), _T("AlsData0 Gain"), 0x07, 0, BOTH_RW, { 0, 0x07 }, 0x02);
				}

				pRegTable->SetRegAddr(0x52);
				pRegTable->SetRegInfo({ 0x00 }, _T("AlsPuc"));
				{
					pRegTable->SetBitDetail(_T("AlsPuc"), _T("Als Conversion Time"), 0x1F, 0, BOTH_RW, { 0, 0x1F });
				}

				pRegTable->SetRegAddr(0x55);
				pRegTable->SetRegInfo({ 0x29 }, _T("AlsPuw0"));
				{
					pRegTable->SetBitDetail(_T("AlsPuw0"), _T("AlsData0 Conversion width"), 0x7F, 0, BOTH_RW, { 0, 0x7F }, 0x29);
				}

				pRegTable->SetRegAddr(0x56);
				pRegTable->SetRegInfo({ 0x0A }, _T("AlsPuw1"));
				{
					pRegTable->SetBitDetail(_T("AlsPuw1"), _T("AlsData1 Conversion width"), 0x7F, 0, BOTH_RW, { 0, 0x7F }, 0x0A);
				}

				pRegTable->SetRegAddr(0x5B);
				pRegTable->SetRegInfo({ 0x01 }, _T("AlsAlgoCtrl"));
				{
					pRegTable->SetBitDetail(_T("AlsTurbo"), 6, _T("1/10 Time Unit"), 0);
					pRegTable->SetBitDetail(_T("AlsIntSrc"), 4, _T("Define the AlsData to assert AlsInt."), 0);
					pRegTable->SetBitDetail(_T("AlsPers"), _T("Als Persistence"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x01);
				}

				pRegTable->SetRegAddr(0x5C);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("AlsThLow"), 2);
				{
					pRegTable->SetBitDetail2(_T("AlsThLow"), { 0x00, 0x00 });
				}

				pRegTable->SetRegAddr(0x5E);
				pRegTable->SetRegInfo({ 0xFF, 0xFF }, _T("AlsThHigh"), 2);
				{
					pRegTable->SetBitDetail2(_T("AlsThHigh"), { 0xFF, 0xFF });
				}

				//RD Mode
				{
					//RD Mode SoftWare
					pRegTable->SetRegAddr(0x10);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak25"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak25"), { 0x00, 0x00 });
					}
					pRegTable->SetRegAddr(0x12);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak35"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak35"), { 0x00, 0x00 });
					}
					pRegTable->SetRegAddr(0x14);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak45"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak45"), { 0x00, 0x00 });
					}
					pRegTable->SetRegAddr(0x16);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak55"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak55"), { 0x00, 0x00 });
					}
					pRegTable->SetRegAddr(0x18);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak65"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak65"), { 0x00, 0x00 });
					}
					pRegTable->SetRegAddr(0x1A);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak75"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak75"), { 0x00, 0x00 });
					}
					pRegTable->SetRegAddr(0x1C);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak85"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak85"), { 0x00, 0x00 });
					}
					pRegTable->SetRegAddr(0x1E);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak95"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak95"), { 0x00, 0x00 });
					}

					pRegTable->SetRegAddr(0x20);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("LTAR"), 2);
					{
						pRegTable->SetBitDetail2(_T("LTAR"), { 0x00, 0x00 }, _T("Define TmpData at 95C for Leak"));
					}

					//pRegTable->SetRegAddr(0x22);
					//pRegTable->SetRegInfo({ 0x00 }, _T("PsLcf"));
					//{
					//	pRegTable->SetBitDetail(_T("PsLcf"), _T("PsData Lcf = PsLcf/64"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x23);
					//pRegTable->SetRegInfo({ 0x00 }, _T("IrLcf"));
					//{
					//	pRegTable->SetBitDetail(_T("IrLcf"), _T("IrData Lcf = IrLcf/64"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					pRegTable->SetRegAddr(0x24);
					pRegTable->SetRegInfo({ 0x00 }, _T("AlsLcf0"));
					{
						pRegTable->SetBitDetail(_T("AlsLcf0"), _T("AlsData0 Lcf = PsLcf/64"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					pRegTable->SetRegAddr(0x25);
					pRegTable->SetRegInfo({ 0x00 }, _T("AlsLcf1"));
					{
						pRegTable->SetBitDetail(_T("AlsLcf1"), _T("AlsData1 Lcf = PsLcf/64"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					//pRegTable->SetRegAddr(0x26);
					//pRegTable->SetRegInfo({ 0x00 }, _T("AlsLcf2"));
					//{
					//	pRegTable->SetBitDetail(_T("AlsLcf2"), _T("AlsData2 Lcf = PsLcf/64"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x27);
					//pRegTable->SetRegInfo({ 0x00 }, _T("AlsLcf3"));
					//{
					//	pRegTable->SetBitDetail(_T("AlsLcf3"), _T("AlsData3 Lcf = PsLcf/64"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x28);
					//pRegTable->SetRegInfo({ 0x00 }, _T("PsTcfLow"));
					//{
					//	pRegTable->SetBitDetail(_T("PsTcfLow"), _T("PsData Tcf = PsTcfLow/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x29);
					//pRegTable->SetRegInfo({ 0x00 }, _T("PsTcfHigh"));
					//{
					//	pRegTable->SetBitDetail(_T("PsTcfHigh"), _T("PsData Tcf = PsTcfHigh/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x2A);
					//pRegTable->SetRegInfo({ 0x00 }, _T("IrTcfLow"));
					//{
					//	pRegTable->SetBitDetail(_T("IrTcfLow"), _T("IrData Tcf = IrTcfLow/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x2B);
					//pRegTable->SetRegInfo({ 0x00 }, _T("IrTcfHigh"));
					//{
					//	pRegTable->SetBitDetail(_T("IrTcfHigh"), _T("IrData Tcf = IrTcfHigh/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					pRegTable->SetRegAddr(0x2C);
					pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfLow0"));
					{
						pRegTable->SetBitDetail(_T("AlsTcfLow0"), _T("AlsData0 Tcf = AlsTcfLow0/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					pRegTable->SetRegAddr(0x2D);
					pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfHigh0"));
					{
						pRegTable->SetBitDetail(_T("AlsTcfHigh0"), _T("AlsData0 Tcf = AlsTcfHigh0/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					pRegTable->SetRegAddr(0x2E);
					pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfLow1"));
					{
						pRegTable->SetBitDetail(_T("AlsTcfLow1"), _T("AlsData1 Tcf = AlsTcfLow1/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					pRegTable->SetRegAddr(0x2F);
					pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfHigh1"));
					{
						pRegTable->SetBitDetail(_T("AlsTcfHigh1"), _T("AlsData1 Tcf = AlsTcfHigh1/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					//pRegTable->SetRegAddr(0x30);
					//pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfLow2"));
					//{
					//	pRegTable->SetBitDetail(_T("AlsTcfLow2"), _T("AlsData2 Tcf = AlsTcfLow2/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x31);
					//pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfHigh2"));
					//{
					//	pRegTable->SetBitDetail(_T("AlsTcfHigh2"), _T("AlsData2 Tcf = AlsTcfHigh2/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x32);
					//pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfLow3"));
					//{
					//	pRegTable->SetBitDetail(_T("AlsTcfLow3"), _T("AlsData3 Tcf = AlsTcfLow3/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x33);
					//pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfHigh3"));
					//{
					//	pRegTable->SetBitDetail(_T("AlsTcfHigh3"), _T("AlsData3 Tcf = AlsTcfHigh3/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					pRegTable->SetRegAddr(0x3E);
					pRegTable->SetRegInfo({ 0x2D }, _T("TTAR"));
					{
						pRegTable->SetBitDetail(_T("TTAR"), _T("TmpData Unit= TTAR x 10us"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x2D);
					}

					//pRegTable->SetRegAddr(0x3F);
					//pRegTable->SetRegInfo({ 0x1B }, _T("PTAR"));
					//{
					//	pRegTable->SetBitDetail(_T("PTAR"), _T("PsData Unit= PTAR x 10us at 9 bits"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x1B);
					//}

					//pRegTable->SetRegAddr(0x40);
					//pRegTable->SetRegInfo({ 0x14 }, _T("ATAR"));
					//{
					//	pRegTable->SetBitDetail(_T("ATAR"), _T("AlsData0~2 Unit= ATAR x 50us"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x1B);
					//}

					pRegTable->SetRegAddr(0x41);
					pRegTable->SetRegInfo({ 0x03 }, _T("TmpAdc"));	//TODO: check value
					{
						pRegTable->SetBitDetail(_T("TmpCap"), _T("Control pin \"pcap_sel\" at TMP ADC"), 0x07, 0, BOTH_RW, { 0, 0x07 }, 0x03);
					}

					//pRegTable->SetRegAddr(0x42);
					//pRegTable->SetRegInfo({ 0xF1 }, _T("PxyAdc"));
					//{
					//	pRegTable->SetBitDetail(_T("PsV2i"), _T("Control pin \"pxy_v2i_sel\" at PS/IR ADC"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x0F);
					//	pRegTable->SetBitDetail(_T("PxyCap"), 0, _T("Control pin \"pcap_sel\" at PS/IR ADC"), 1);
					//}

					pRegTable->SetRegAddr(0x43);
					pRegTable->SetRegInfo({ 0x8D }, _T("AnalogA"));
					{
						pRegTable->SetBitDetail(_T("TmpBias"), 7, _T("Control pin \"pdvb0d3v_en\" at TMP"), 1);
						pRegTable->SetBitDetail(_T("IrBias"), 6, _T("Control pin \"pdvb0d3v_en\" at IR"));
						//pRegTable->SetBitDetail(_T("PsBias"), 5, _T("Control pin \"pdvb0d3v_en\" at PS"));
						pRegTable->SetBitDetail(_T("AlsBias"), 4, _T("Control pin \"pdvb0d3v_en\" at ALS"));
						pRegTable->SetBitDetail(_T("DfltEn"), 3, _T("Control pin \"dflten\" at all functions"), 1);
						pRegTable->SetBitDetail(_T("IrDark"), 2, _T("Control pin \"ir_dark\" at IR(AlsData1)"), 1);
						//pRegTable->SetBitDetail(_T("PsDark"), 1, _T("Control pin \"ir_dark\" at PS"));
						pRegTable->SetBitDetail(_T("AlsDark"), 0, _T("Control pin \"als_dark\" at ALS(AlsData0)"), 1);
					}

					pRegTable->SetRegAddr(0x44);
					pRegTable->SetRegInfo({ 0x00 }, _T("AnalogB"));
					{
						pRegTable->SetBitDetail(_T("TestSel"), 7, _T("Control pin \"test_sel\""));
						pRegTable->SetBitDetail(_T("IbTest"), _T("Control pin \"ibtest_sel\""), 0x70, 4, BOTH_RW, { 0, 0x07 });
						pRegTable->SetBitDetail(_T("AnaEn"), 3, _T("Control pin \"ana_en\""));
						pRegTable->SetBitDetail(_T("AnaTest"), _T("Control pin \"ana_test\""), 0x07, 0, BOTH_RW, { 0, 0x07 });
					}

					pRegTable->SetRegAddr(0x45);
					pRegTable->SetRegInfo({ 0x00 }, _T("AnalogC"));
					{
						//pRegTable->SetBitDetail(_T("CoasDc"), 4, _T("Control pin \"coas_offset\" at PS/IR"));
						pRegTable->SetBitDetail(_T("AnaReg"), _T("Control pin \"ana_reg\""), 0x0F, 0, BOTH_RW, { 0, 0x0F });
					}

					pRegTable->SetRegAddr(0x46);
					pRegTable->SetRegInfo({ 0x27 }, _T("AnalogD"));
					{
						pRegTable->SetBitDetail(_T("AlsFreq1"), 7, _T("Control pin \"f2xsel\" at IR(AlsData1)"));
						pRegTable->SetBitDetail(_T("AlsFreq0"), 6, _T("Control pin \"f2xsel\" at ALS(AlsData0)"));
						pRegTable->SetBitDetail(_T("DiodeVbs"), _T("Control pin \"diode_vbs\""), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x02);
						pRegTable->SetBitDetail(_T("VrefOp"), _T("Control pin \"vref_op\""), 0x0C, 2, BOTH_RW, { 0, 0x03 }, 0x01);
						pRegTable->SetBitDetail(_T("Vtoph"), _T("Control pin \"vtoph_set\""), 0x03, 0, BOTH_RW, { 0, 0x03 }, 0x03);
					}

					pRegTable->SetRegAddr(0x47);
					pRegTable->SetRegInfo({ 0x04 }, _T("AnalogE"));
					{
						pRegTable->SetBitDetail(_T("DcPath"), 7, _T("Control pin \"dcpath\""));
						pRegTable->SetBitDetail(_T("DarkTrim"), _T("Control pin \"darktrim\""), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x04);
					}

					pRegTable->SetRegAddr(0x48);
					pRegTable->SetRegInfo({ 0x16 }, _T("AnalogF"));
					{
						pRegTable->SetBitDetail(_T("LoscTrim"), _T("Control pin \"losc_trim\""), 0x1F, 0, BOTH_RW, { 0, 0x1F }, 0x16);
					}

					pRegTable->SetRegAddr(0x49);
					pRegTable->SetRegInfo({ 0x20 }, _T("AnalogG"));
					{
						pRegTable->SetBitDetail(_T("HoscVbs"), _T("Control pin \"hosc_vbs\""), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x02);
						pRegTable->SetBitDetail(_T("LdodTrim"), _T("Control pin \"ldod_pmosw\""), 0x07, 0, BOTH_RW, { 0, 0x07 });
					}

					//pRegTable->SetRegAddr(0x4B);
					//pRegTable->SetRegInfo({ 0x00 }, _T("TxFreq"));
					//{
					//	pRegTable->SetBitDetail(_T("TxFreq"), _T("Tx Frequency"), 0x07, 0, BOTH_RW, { 0, 0x07 });
					//}

					//pRegTable->SetRegAddr(0x4C);
					//pRegTable->SetRegInfo({ 0x00 }, _T("CtPuw"));
					//{
					//	pRegTable->SetBitDetail(_T("CtPuw"), _T("Fine Crosstalk DAC Width"));
					//}

					//pRegTable->SetRegAddr(0x4D);
					//pRegTable->SetRegInfo({ 0x06 }, _T("TxPuw"));
					//{
					//	pRegTable->SetBitDetail(_T("AmbPuw"), _T(""), 0x30, 4, BOTH_RW, { 0, 0x03 });
					//	pRegTable->SetBitDetail(_T("DrvPuw"), _T(""), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x06);
					//}

					//pRegTable->SetRegAddr(0x4E);
					//pRegTable->SetRegInfo({ 0x00 }, _T("PrePuw"));
					//{
					//	pRegTable->SetBitDetail(_T("PrePuw"), _T("Pre-Heat Pulse Width"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
					//}

					pRegTable->SetRegAddr(0x7B);
					pRegTable->SetRegInfo({ 0x00 }, _T("DigCtrl"));
					{
						//pRegTable->SetBitDetail(_T("VenOff"), 7, _T("Enable \"power_sel\""));
						//pRegTable->SetBitDetail(_T("PreOff"), 6, _T("Enable Pre Timing"));
						//pRegTable->SetBitDetail(_T("TmpNoMean"), 5, _T("TmpData mean time"));
						pRegTable->SetBitDetail(_T("FastTmp"), 4, _T("Out TmpData every Conversion"));
						pRegTable->SetBitDetail(_T("FastEn"), 3, _T("Conversion is min"));
						pRegTable->SetBitDetail(_T("LadcEn"), 2, _T("AmbData = Leak Table"));
						//pRegTable->SetBitDetail(_T("PxshEn"), 1, _T("Enable \"pxsh\" at Pre-heat"));
						pRegTable->SetBitDetail(_T("MakeEn"), 0, _T("Use Make Data as input"));
					}

					pRegTable->SetRegAddr(0x7C);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("MakeData"), 2);
					{
						pRegTable->SetBitDetail2(_T("MakeData"), { 0x00, 0x00 }, _T("Define fake data to replace ADC data"));
					}

					pRegTable->SetRegAddr(0x7E);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("MakeTmp"), 2);
					{
						pRegTable->SetBitDetail2(_T("MakeTmp"), { 0x00, 0x00 }, _T("Define fake data to replace TmpData"));
					}

					//HardWare
					//RD Mode Hardware
					pRegTable->SetRegAddr(0xD0);
					pRegTable->SetRegInfo({ 0x00 }, _T("Mode"));
					{
						pRegTable->SetBitDetail(_T("Mode"), _T("Mode Select"), 0x07, 0, BOTH_RW, { 0x00, 0x07 });
					}

					pRegTable->SetRegAddr(0xD1);
					pRegTable->SetRegInfo({ 0x00 }, _T("PadCtrl"));
					{
						pRegTable->SetBitDetail(_T("ForcePad"), 7, _T("ForcePad"));
						pRegTable->SetBitDetail(_T("View"), _T("View"), 0x1F, 0, BOTH_RW, { 0x00, 0x1F });
					}

					pRegTable->SetRegAddr(0xD2);
					pRegTable->SetRegInfo({ 0x4B }, _T("Tbe"));
					{
						pRegTable->SetBitDetail(_T("Tbe"), _T("Fuse Burn Width"), 0x7F, 0, BOTH_RW, { 0x00, 0x7F }, 0x4B);
					}
#if 0
					pRegTable->SetRegAddr(0xD3);
					pRegTable->SetRegInfo({ 0x00 }, _T("BRAM"));
					{
						pRegTable->SetBitDetail(_T("BRAM"), _T("Ram Bist"), 0xFF, 0, ONLY_R);
					}

					pRegTable->SetRegAddr(0xD4);
					pRegTable->SetRegInfo({ 0x00 , 0x00 }, _T("BROM"), 2);
					{
						pRegTable->SetBitDetail2(_T("BROM"), _T("Rom Bist"));
					}
#endif
					pRegTable->SetRegAddr(0xD6);
					pRegTable->SetRegInfo({ 0x01 }, _T("AnaCtrl"));
					{
						pRegTable->SetBitDetail(_T("LdoaExt"), 7, _T("Control ldoa_ext when Device ON"));
						pRegTable->SetBitDetail(_T("HoscExt"), 6, _T("Control hosc_ext when Device ON"));
						pRegTable->SetBitDetail(_T("LoscEnb"), 3, _T("Control losc_enb when Device OFF"));
						pRegTable->SetBitDetail(_T("HoscEn"), 2, _T("Control hosc_en pin when Device OFF"));
						pRegTable->SetBitDetail(_T("EnPs"), 1, _T("Control en_ps pin when Device OFF"));
						pRegTable->SetBitDetail(_T("EnbBg"), 0, _T("Control enb_bg pin when Device OFF"), 0x01);
					}

					pRegTable->SetRegAddr(0xEF);
					pRegTable->SetRegInfo({ 0x28 }, _T("WatchDog"));
					{
						pRegTable->SetBitDetail(_T("WatchDog"), _T("Time Out= WatchDog x 0.8 ms"), 0x7F, 0, BOTH_RW, { 0x00, 0x7F }, 0x28);
					}
				}
			}
			break;
		case 10100:
			DieDetail.insert(make_pair(10100, CDieDetail()));
			{
				pDieDetail = &DieDetail.at(10100);

				pRegTable = &pDieDetail->RegisterTable;

				pRegTable->DeviceID = 0x1C;

				pRegTable->SetRegAddr(0xF0);
				pRegTable->SetRegInfo({ 0x00 }, _T("DevCtrl"));
				{
					pRegTable->SetBitDetail(_T("AlsEn"), 0, _T("ALS Enable"));
				}

				pRegTable->SetRegAddr(0xF1);
				pRegTable->SetRegInfo({ 0x03 }, _T("IntCtrl"));
				{
					pRegTable->SetBitDetail(_T("DataIntEn"), 4, _T("Data Int Enable"));
					pRegTable->SetBitDetail(_T("Reserved0xF1_1"), 1, _T("Reserved0xF1_1"), 0x01);
					pRegTable->SetBitDetail(_T("AlsIntEn"), 0, _T("ALS Int Enable"), 0x01);
				}

				pRegTable->SetRegAddr(0xF2);
				pRegTable->SetRegInfo({ 0x00 }, _T("HaltCtrl"));
				{
					pRegTable->SetBitDetail(_T("ReadClear"), 7, _T("Interrupt clear method"));
					pRegTable->SetBitDetail(_T("DataHalt"), 4, _T("Data Halt Control Bit"));
					pRegTable->SetBitDetail(_T("AlsHalt"), 0, _T("ALS Halt Function Control Bit"));
				}

				pRegTable->SetRegAddr(0xF3);
				pRegTable->SetRegInfo({ 0x00 }, _T("SysCtrl"));
				{
					pRegTable->SetBitDetail(_T("PorFen"), 7, _T("Enable Falling POR"));
					pRegTable->SetBitDetail(_T("VbgPuw"), 4, _T("Vbg Puw"));
					pRegTable->SetBitDetail(_T("Operation"), 0, _T("Openation Mode"));
				}

				pRegTable->SetRegAddr(0xF4);
				pRegTable->SetRegInfo({ 0x00 }, _T("SwRst"));
				{
					pRegTable->SetBitDetail(_T("SoftReset"), _T("Software Reset"), _T(""), 0xEE);	//write 0xEE to reset
				}

				pRegTable->SetRegAddr(0xF5);
				pRegTable->SetRegInfo({ 0x00 }, _T("IoCtrl"));
				{
					pRegTable->SetBitDetail(_T("PushPull"), 7, _T("INT pin is Push Pull"));
					pRegTable->SetBitDetail(_T("IoFunc"), _T("Change INT pin output"), 0x03, 0, BOTH_RW, { 0, 0x03 });
				}

				pRegTable->SetRegAddr(0xFB);
				pRegTable->SetRegInfo({ 0x00 }, _T("LoscData"));
				{
					pRegTable->SetBitDetail(_T("LoscData"), _T("LOSC Period= LoscData x 800ns"), 0xFF, 0, ONLY_R);
				}

				pRegTable->SetRegAddr(0xFC);
				pRegTable->SetRegInfo({ 0x1A }, _T("IDPod"));
				{
					pRegTable->SetBitDetail(_T("IDPod"), _T("IDPod"), 0xFF, 0, ONLY_R);
				}

				pRegTable->SetRegAddr(0xFD);
				pRegTable->SetRegInfo({ 0x01 }, _T("IDRev"));
				{
					pRegTable->SetBitDetail(_T("IDRev"), _T("IDRev"), 0xFF, 0, ONLY_R);
				}

				pRegTable->SetRegAddr(0xFE);
				pRegTable->SetRegInfo({ 0x80 }, _T("IntFlag"));
				{
					pRegTable->SetBitDetail(_T("PorInt"), 7, _T("POR INT"), 1);
					pRegTable->SetBitDetail(_T("DataInt"), 4, _T("Data INT"));
					pRegTable->SetBitDetail(_T("AlsInt"), 0, _T("ALS INT"));
				}

				pRegTable->SetRegAddr(0xFF);
				pRegTable->SetRegInfo({ 0x80 }, _T("StatFlag"));
				{
					pRegTable->SetBitDetail(_T("TmpErr"), 5, _T("TmpData Invalid Flag"));
					pRegTable->SetBitDetail(_T("AlsErr"), 0, _T("AlsData0~1 Invalid Flag"));
				}

				pRegTable->SetRegAddr(0x04);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("AlsData0"), 2);
				{
					pRegTable->SetBitDetail2(_T("AlsData0"), _T("AlsData0"));
				}

				pRegTable->SetRegAddr(0x06);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("AlsData1"), 2);
				{
					pRegTable->SetBitDetail2(_T("AlsData1"), _T("AlsData1"));
				}

				pRegTable->SetRegAddr(0x0C);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("AmbData"), 2);
				{
					pRegTable->SetBitDetail2(_T("AmbData"), _T("AmbData"));
				}

				pRegTable->SetRegAddr(0x0E);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("TmpData"), 2);
				{
					pRegTable->SetBitDetail2(_T("TmpData"), _T("TmpData"));
				}

				pRegTable->SetRegAddr(0x4F);
				pRegTable->SetRegInfo({ 0x00 }, _T("WaitTime"));
				{
					pRegTable->SetBitDetail(_T("WaitTime"), _T("The extra time for saving power:"));
				}

				pRegTable->SetRegAddr(0x50);
				pRegTable->SetRegInfo({ 0x22 }, _T("AlsCtrl"));
				{
					pRegTable->SetBitDetail(_T("AlsGain1"), _T("AlsData1 Gain"), 0x70, 4, BOTH_RW, { 0, 0x07 }, 0x02);
					pRegTable->SetBitDetail(_T("AlsGain0"), _T("AlsData0 Gain"), 0x07, 0, BOTH_RW, { 0, 0x07 }, 0x02);
				}

				pRegTable->SetRegAddr(0x52);
				pRegTable->SetRegInfo({ 0x00 }, _T("AlsPuc"));
				{
					pRegTable->SetBitDetail(_T("AlsPuc"), _T("Als Conversion Time"), 0x1F, 0, BOTH_RW, { 0, 0x1F });
				}

				pRegTable->SetRegAddr(0x55);
				pRegTable->SetRegInfo({ 0x29 }, _T("AlsPuw0"));
				{
					pRegTable->SetBitDetail(_T("AlsPuw0"), _T("AlsData0 Conversion width"), 0x7F, 0, BOTH_RW, { 0, 0x7F }, 0x29);
				}

				pRegTable->SetRegAddr(0x56);
				pRegTable->SetRegInfo({ 0x0A }, _T("AlsPuw1"));
				{
					pRegTable->SetBitDetail(_T("AlsPuw1"), _T("AlsData1 Conversion width"), 0x7F, 0, BOTH_RW, { 0, 0x7F }, 0x0A);
				}

				pRegTable->SetRegAddr(0x5B);
				pRegTable->SetRegInfo({ 0x01 }, _T("AlsAlgoCtrl"));
				{
					pRegTable->SetBitDetail(_T("AlsTurbo"), 6, _T("1/10 Time Unit"), 0);
					pRegTable->SetBitDetail(_T("AlsIntSrc"), 4, _T("Define the AlsData to assert AlsInt."), 0);
					pRegTable->SetBitDetail(_T("AlsPers"), _T("Als Persistence"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x01);
				}

				pRegTable->SetRegAddr(0x5C);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("AlsThLow"), 2);
				{
					pRegTable->SetBitDetail2(_T("AlsThLow"), { 0x00, 0x00 });
				}

				pRegTable->SetRegAddr(0x5E);
				pRegTable->SetRegInfo({ 0xFF, 0xFF }, _T("AlsThHigh"), 2);
				{
					pRegTable->SetBitDetail2(_T("AlsThHigh"), { 0xFF, 0xFF });
				}

				//RD Mode
				{
					//RD Mode SoftWare
					pRegTable->SetRegAddr(0x10);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak25"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak25"), { 0x00, 0x00 });
					}
					pRegTable->SetRegAddr(0x12);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak35"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak35"), { 0x00, 0x00 });
					}
					pRegTable->SetRegAddr(0x14);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak45"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak45"), { 0x00, 0x00 });
					}
					pRegTable->SetRegAddr(0x16);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak55"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak55"), { 0x00, 0x00 });
					}
					pRegTable->SetRegAddr(0x18);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak65"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak65"), { 0x00, 0x00 });
					}
					pRegTable->SetRegAddr(0x1A);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak75"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak75"), { 0x00, 0x00 });
					}
					pRegTable->SetRegAddr(0x1C);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak85"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak85"), { 0x00, 0x00 });
					}
					pRegTable->SetRegAddr(0x1E);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak95"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak95"), { 0x00, 0x00 });
					}

					pRegTable->SetRegAddr(0x20);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("LTAR"), 2);
					{
						pRegTable->SetBitDetail2(_T("LTAR"), { 0x00, 0x00 }, _T("Define TmpData at 95C for Leak"));
					}

					//pRegTable->SetRegAddr(0x22);
					//pRegTable->SetRegInfo({ 0x00 }, _T("PsLcf"));
					//{
					//	pRegTable->SetBitDetail(_T("PsLcf"), _T("PsData Lcf = PsLcf/64"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x23);
					//pRegTable->SetRegInfo({ 0x00 }, _T("IrLcf"));
					//{
					//	pRegTable->SetBitDetail(_T("IrLcf"), _T("IrData Lcf = IrLcf/64"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					pRegTable->SetRegAddr(0x24);
					pRegTable->SetRegInfo({ 0x00 }, _T("AlsLcf0"));
					{
						pRegTable->SetBitDetail(_T("AlsLcf0"), _T("AlsData0 Lcf = PsLcf/64"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					pRegTable->SetRegAddr(0x25);
					pRegTable->SetRegInfo({ 0x00 }, _T("AlsLcf1"));
					{
						pRegTable->SetBitDetail(_T("AlsLcf1"), _T("AlsData1 Lcf = PsLcf/64"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					//pRegTable->SetRegAddr(0x26);
					//pRegTable->SetRegInfo({ 0x00 }, _T("AlsLcf2"));
					//{
					//	pRegTable->SetBitDetail(_T("AlsLcf2"), _T("AlsData2 Lcf = PsLcf/64"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x27);
					//pRegTable->SetRegInfo({ 0x00 }, _T("AlsLcf3"));
					//{
					//	pRegTable->SetBitDetail(_T("AlsLcf3"), _T("AlsData3 Lcf = PsLcf/64"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x28);
					//pRegTable->SetRegInfo({ 0x00 }, _T("PsTcfLow"));
					//{
					//	pRegTable->SetBitDetail(_T("PsTcfLow"), _T("PsData Tcf = PsTcfLow/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x29);
					//pRegTable->SetRegInfo({ 0x00 }, _T("PsTcfHigh"));
					//{
					//	pRegTable->SetBitDetail(_T("PsTcfHigh"), _T("PsData Tcf = PsTcfHigh/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x2A);
					//pRegTable->SetRegInfo({ 0x00 }, _T("IrTcfLow"));
					//{
					//	pRegTable->SetBitDetail(_T("IrTcfLow"), _T("IrData Tcf = IrTcfLow/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x2B);
					//pRegTable->SetRegInfo({ 0x00 }, _T("IrTcfHigh"));
					//{
					//	pRegTable->SetBitDetail(_T("IrTcfHigh"), _T("IrData Tcf = IrTcfHigh/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					pRegTable->SetRegAddr(0x2C);
					pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfLow0"));
					{
						pRegTable->SetBitDetail(_T("AlsTcfLow0"), _T("AlsData0 Tcf = AlsTcfLow0/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					pRegTable->SetRegAddr(0x2D);
					pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfHigh0"));
					{
						pRegTable->SetBitDetail(_T("AlsTcfHigh0"), _T("AlsData0 Tcf = AlsTcfHigh0/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					pRegTable->SetRegAddr(0x2E);
					pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfLow1"));
					{
						pRegTable->SetBitDetail(_T("AlsTcfLow1"), _T("AlsData1 Tcf = AlsTcfLow1/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					pRegTable->SetRegAddr(0x2F);
					pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfHigh1"));
					{
						pRegTable->SetBitDetail(_T("AlsTcfHigh1"), _T("AlsData1 Tcf = AlsTcfHigh1/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					//pRegTable->SetRegAddr(0x30);
					//pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfLow2"));
					//{
					//	pRegTable->SetBitDetail(_T("AlsTcfLow2"), _T("AlsData2 Tcf = AlsTcfLow2/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x31);
					//pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfHigh2"));
					//{
					//	pRegTable->SetBitDetail(_T("AlsTcfHigh2"), _T("AlsData2 Tcf = AlsTcfHigh2/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x32);
					//pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfLow3"));
					//{
					//	pRegTable->SetBitDetail(_T("AlsTcfLow3"), _T("AlsData3 Tcf = AlsTcfLow3/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x33);
					//pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfHigh3"));
					//{
					//	pRegTable->SetBitDetail(_T("AlsTcfHigh3"), _T("AlsData3 Tcf = AlsTcfHigh3/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					pRegTable->SetRegAddr(0x3E);
					pRegTable->SetRegInfo({ 0x37 }, _T("TTAR"));
					{
						pRegTable->SetBitDetail(_T("TTAR"), _T("TmpData Unit= TTAR x 10us"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x37);
					}

					//pRegTable->SetRegAddr(0x3F);
					//pRegTable->SetRegInfo({ 0x1B }, _T("PTAR"));
					//{
					//	pRegTable->SetBitDetail(_T("PTAR"), _T("PsData Unit= PTAR x 10us at 9 bits"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x1B);
					//}

					//pRegTable->SetRegAddr(0x40);
					//pRegTable->SetRegInfo({ 0x14 }, _T("ATAR"));
					//{
					//	pRegTable->SetBitDetail(_T("ATAR"), _T("AlsData0~2 Unit= ATAR x 50us"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x1B);
					//}

					pRegTable->SetRegAddr(0x41);
					pRegTable->SetRegInfo({ 0x03 }, _T("TmpAdc"));	//TODO: check value
					{
						pRegTable->SetBitDetail(_T("TmpCap"), _T("Control pin \"pcap_sel\" at TMP ADC"), 0x07, 0, BOTH_RW, { 0, 0x07 }, 0x03);
					}

					//pRegTable->SetRegAddr(0x42);
					//pRegTable->SetRegInfo({ 0xF1 }, _T("PxyAdc"));
					//{
					//	pRegTable->SetBitDetail(_T("PsV2i"), _T("Control pin \"pxy_v2i_sel\" at PS/IR ADC"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x0F);
					//	pRegTable->SetBitDetail(_T("PxyCap"), 0, _T("Control pin \"pcap_sel\" at PS/IR ADC"), 1);
					//}

					pRegTable->SetRegAddr(0x43);
					pRegTable->SetRegInfo({ 0x8D }, _T("AnalogA"));
					{
						pRegTable->SetBitDetail(_T("TmpBias"), 7, _T("Control pin \"pdvb0d3v_en\" at TMP"), 1);
						pRegTable->SetBitDetail(_T("IrBias"), 6, _T("Control pin \"pdvb0d3v_en\" at IR"));
						//pRegTable->SetBitDetail(_T("PsBias"), 5, _T("Control pin \"pdvb0d3v_en\" at PS"));
						pRegTable->SetBitDetail(_T("AlsBias"), 4, _T("Control pin \"pdvb0d3v_en\" at ALS"));
						pRegTable->SetBitDetail(_T("Reserved0x43_3"), 3, _T("Reserved0x43_3"), 1);
						//pRegTable->SetBitDetail(_T("DfltEn"), 3, _T("Control pin \"dflten\" at all functions"), 1);
						pRegTable->SetBitDetail(_T("IrDark"), 2, _T("Control pin \"ir_dark\" at IR(AlsData1)"), 1);
						//pRegTable->SetBitDetail(_T("PsDark"), 1, _T("Control pin \"ir_dark\" at PS"));
						pRegTable->SetBitDetail(_T("AlsDark"), 0, _T("Control pin \"als_dark\" at ALS(AlsData0)"), 1);
					}

					pRegTable->SetRegAddr(0x44);
					pRegTable->SetRegInfo({ 0x00 }, _T("AnalogB"));
					{
						pRegTable->SetBitDetail(_T("TestSel"), 7, _T("Control pin \"test_sel\""));
						pRegTable->SetBitDetail(_T("IbTest"), _T("Control pin \"ibtest_sel\""), 0x70, 4, BOTH_RW, { 0, 0x07 });
						pRegTable->SetBitDetail(_T("AnaEn"), 3, _T("Control pin \"ana_en\""));
						pRegTable->SetBitDetail(_T("AnaTest"), _T("Control pin \"ana_test\""), 0x07, 0, BOTH_RW, { 0, 0x07 });
					}

					pRegTable->SetRegAddr(0x45);
					pRegTable->SetRegInfo({ 0x00 }, _T("AnalogC"));
					{
						//pRegTable->SetBitDetail(_T("CoasDc"), 4, _T("Control pin \"coas_offset\" at PS/IR"));
						pRegTable->SetBitDetail(_T("AnaReg"), _T("Control pin \"ana_reg\""), 0x0F, 0, BOTH_RW, { 0, 0x0F });
					}

					pRegTable->SetRegAddr(0x46);
					pRegTable->SetRegInfo({ 0x20 }, _T("AnalogD"));
					{
						pRegTable->SetBitDetail(_T("AlsFreq1"), 7, _T("Control pin \"f2xsel\" at IR(AlsData1)"));
						pRegTable->SetBitDetail(_T("AlsFreq0"), 6, _T("Control pin \"f2xsel\" at ALS(AlsData0)"));
						//pRegTable->SetBitDetail(_T("DiodeVbs"), _T("Control pin \"diode_vbs\""), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x02);
						pRegTable->SetBitDetail(_T("Reserved0x46_5_4"), _T("Reserved0x46_5_4"), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x02);
						pRegTable->SetBitDetail(_T("VrefOp"), _T("Control pin \"vref_op\""), 0x0C, 2, BOTH_RW, { 0, 0x03 }, 0x00);
						//pRegTable->SetBitDetail(_T("Vtoph"), _T("Control pin \"vtoph_set\""), 0x03, 0, BOTH_RW, { 0, 0x03 }, 0x03);
						pRegTable->SetBitDetail(_T("Reserved0x46_1_0"), _T("Reserved0x46_1_0"), 0x03, 0, BOTH_RW, { 0, 0x03 });
					}

					pRegTable->SetRegAddr(0x47);
					pRegTable->SetRegInfo({ 0x04 }, _T("AnalogE"));
					{
						pRegTable->SetBitDetail(_T("DcPath"), 7, _T("Control pin \"dcpath\""));
						pRegTable->SetBitDetail(_T("DarkTrim"), _T("Control pin \"darktrim\""), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x04);
					}

					pRegTable->SetRegAddr(0x48);
					pRegTable->SetRegInfo({ 0x16 }, _T("AnalogF"));
					{
						pRegTable->SetBitDetail(_T("LoscTrim"), _T("Control pin \"losc_trim\""), 0x1F, 0, BOTH_RW, { 0, 0x1F }, 0x16);
					}

					pRegTable->SetRegAddr(0x49);
					pRegTable->SetRegInfo({ 0x20 }, _T("AnalogG"));
					{
						pRegTable->SetBitDetail(_T("HoscVbs"), _T("Control pin \"hosc_vbs\""), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x02);
						pRegTable->SetBitDetail(_T("LdodTrim"), _T("Control pin \"ldod_pmosw\""), 0x07, 0, BOTH_RW, { 0, 0x07 });
					}

					//pRegTable->SetRegAddr(0x4B);
					//pRegTable->SetRegInfo({ 0x00 }, _T("TxFreq"));
					//{
					//	pRegTable->SetBitDetail(_T("TxFreq"), _T("Tx Frequency"), 0x07, 0, BOTH_RW, { 0, 0x07 });
					//}

					//pRegTable->SetRegAddr(0x4C);
					//pRegTable->SetRegInfo({ 0x00 }, _T("CtPuw"));
					//{
					//	pRegTable->SetBitDetail(_T("CtPuw"), _T("Fine Crosstalk DAC Width"));
					//}

					//pRegTable->SetRegAddr(0x4D);
					//pRegTable->SetRegInfo({ 0x06 }, _T("TxPuw"));
					//{
					//	pRegTable->SetBitDetail(_T("AmbPuw"), _T(""), 0x30, 4, BOTH_RW, { 0, 0x03 });
					//	pRegTable->SetBitDetail(_T("DrvPuw"), _T(""), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x06);
					//}

					//pRegTable->SetRegAddr(0x4E);
					//pRegTable->SetRegInfo({ 0x00 }, _T("PrePuw"));
					//{
					//	pRegTable->SetBitDetail(_T("PrePuw"), _T("Pre-Heat Pulse Width"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
					//}

					pRegTable->SetRegAddr(0x7B);
					pRegTable->SetRegInfo({ 0x00 }, _T("DigCtrl"));
					{
						//pRegTable->SetBitDetail(_T("VenOff"), 7, _T("Enable \"power_sel\""));
						//pRegTable->SetBitDetail(_T("PreOff"), 6, _T("Enable Pre Timing"));
						//pRegTable->SetBitDetail(_T("TmpNoMean"), 5, _T("TmpData mean time"));
						pRegTable->SetBitDetail(_T("FastTmp"), 4, _T("Out TmpData every Conversion"));
						pRegTable->SetBitDetail(_T("FastEn"), 3, _T("Conversion is min"));
						pRegTable->SetBitDetail(_T("LadcEn"), 2, _T("AmbData = Leak Table"));
						//pRegTable->SetBitDetail(_T("PxshEn"), 1, _T("Enable \"pxsh\" at Pre-heat"));
						pRegTable->SetBitDetail(_T("MakeEn"), 0, _T("Use Make Data as input"));
					}

					pRegTable->SetRegAddr(0x7C);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("MakeData"), 2);
					{
						pRegTable->SetBitDetail2(_T("MakeData"), { 0x00, 0x00 }, _T("Define fake data to replace ADC data"));
					}

					pRegTable->SetRegAddr(0x7E);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("MakeTmp"), 2);
					{
						pRegTable->SetBitDetail2(_T("MakeTmp"), { 0x00, 0x00 }, _T("Define fake data to replace TmpData"));
					}

					//HardWare
					//RD Mode Hardware
					pRegTable->SetRegAddr(0xD0);
					pRegTable->SetRegInfo({ 0x00 }, _T("Mode"));
					{
						pRegTable->SetBitDetail(_T("Mode"), _T("Mode Select"), 0x07, 0, BOTH_RW, { 0x00, 0x07 });
					}

					pRegTable->SetRegAddr(0xD1);
					pRegTable->SetRegInfo({ 0x00 }, _T("PadCtrl"));
					{
						pRegTable->SetBitDetail(_T("ForcePad"), 7, _T("ForcePad"));
						pRegTable->SetBitDetail(_T("View"), _T("View"), 0x1F, 0, BOTH_RW, { 0x00, 0x1F });
					}

					pRegTable->SetRegAddr(0xD2);
					pRegTable->SetRegInfo({ 0x4B }, _T("Tbe"));
					{
						pRegTable->SetBitDetail(_T("Tbe"), _T("Fuse Burn Width"), 0x7F, 0, BOTH_RW, { 0x00, 0x7F }, 0x4B);
					}
#if 0
					pRegTable->SetRegAddr(0xD3);
					pRegTable->SetRegInfo({ 0x00 }, _T("BRAM"));
					{
						pRegTable->SetBitDetail(_T("BRAM"), _T("Ram Bist"), 0xFF, 0, ONLY_R);
					}

					pRegTable->SetRegAddr(0xD4);
					pRegTable->SetRegInfo({ 0x00 , 0x00 }, _T("BROM"), 2);
					{
						pRegTable->SetBitDetail2(_T("BROM"), _T("Rom Bist"));
					}
#endif
					pRegTable->SetRegAddr(0xD6);
					pRegTable->SetRegInfo({ 0x01 }, _T("AnaCtrl"));
					{
						pRegTable->SetBitDetail(_T("LdoaExt"), 7, _T("Control ldoa_ext when Device ON"));
						pRegTable->SetBitDetail(_T("HoscExt"), 6, _T("Control hosc_ext when Device ON"));
						pRegTable->SetBitDetail(_T("LoscEnb"), 3, _T("Control losc_enb when Device OFF"));
						pRegTable->SetBitDetail(_T("HoscEn"), 2, _T("Control hosc_en pin when Device OFF"));
						pRegTable->SetBitDetail(_T("EnPs"), 1, _T("Control en_ps pin when Device OFF"));
						pRegTable->SetBitDetail(_T("EnbBg"), 0, _T("Control enb_bg pin when Device OFF"), 0x01);
					}

					pRegTable->SetRegAddr(0xEF);
					pRegTable->SetRegInfo({ 0x28 }, _T("WatchDog"));
					{
						pRegTable->SetBitDetail(_T("WatchDog"), _T("Time Out= WatchDog x 0.8 ms"), 0x7F, 0, BOTH_RW, { 0x00, 0x7F }, 0x28);
					}
				}
			}
			break;
		case 10200:
			DieDetail.insert(make_pair(10200, CDieDetail()));
			{
				pDieDetail = &DieDetail.at(10200);

				pRegTable = &pDieDetail->RegisterTable;

				pRegTable->DeviceID = 0x1C;

				pRegTable->SetRegAddr(0xF0);
				pRegTable->SetRegInfo({ 0x00 }, _T("DevCtrl"));
				{
					pRegTable->SetBitDetail(_T("AlsEn"), 0, _T("ALS Enable"));
				}

				pRegTable->SetRegAddr(0xF1);
				pRegTable->SetRegInfo({ 0x03 }, _T("IntCtrl"));
				{
					pRegTable->SetBitDetail(_T("DataIntEn"), 4, _T("Data Int Enable"));
					pRegTable->SetBitDetail(_T("Reserved0xF1_1"), 1, _T("Reserved0xF1_1"), 0x01);
					pRegTable->SetBitDetail(_T("AlsIntEn"), 0, _T("ALS Int Enable"), 0x01);
				}

				pRegTable->SetRegAddr(0xF2);
				pRegTable->SetRegInfo({ 0x00 }, _T("HaltCtrl"));
				{
					pRegTable->SetBitDetail(_T("ReadClear"), 7, _T("Interrupt clear method"));
					pRegTable->SetBitDetail(_T("DataHalt"), 4, _T("Data Halt Control Bit"));
					pRegTable->SetBitDetail(_T("AlsHalt"), 0, _T("ALS Halt Function Control Bit"));
				}

				pRegTable->SetRegAddr(0xF3);
				pRegTable->SetRegInfo({ 0x00 }, _T("SysCtrl"));
				{
					pRegTable->SetBitDetail(_T("PorFen"), 7, _T("Enable Falling POR"));
					pRegTable->SetBitDetail(_T("VbgPuw"), 4, _T("Vbg Puw"));
					pRegTable->SetBitDetail(_T("Operation"), 0, _T("Openation Mode"));
				}

				pRegTable->SetRegAddr(0xF4);
				pRegTable->SetRegInfo({ 0x00 }, _T("SwRst"));
				{
					pRegTable->SetBitDetail(_T("SoftReset"), _T("Software Reset"), _T(""), 0xEE);	//write 0xEE to reset
				}

				pRegTable->SetRegAddr(0xF5);
				pRegTable->SetRegInfo({ 0x00 }, _T("IoCtrl"));
				{
					pRegTable->SetBitDetail(_T("PushPull"), 7, _T("INT pin is Push Pull"));
					pRegTable->SetBitDetail(_T("IoFunc"), _T("Change INT pin output"), 0x03, 0, BOTH_RW, { 0, 0x03 });
				}

				pRegTable->SetRegAddr(0xFB);
				pRegTable->SetRegInfo({ 0x00 }, _T("LoscData"));
				{
					pRegTable->SetBitDetail(_T("LoscData"), _T("LOSC Period= LoscData x 800ns"), 0xFF, 0, ONLY_R);
				}

				pRegTable->SetRegAddr(0xFC);
				pRegTable->SetRegInfo({ 0x1A }, _T("IDPod"));
				{
					pRegTable->SetBitDetail(_T("IDPod"), _T("IDPod"), 0xFF, 0, ONLY_R);
				}

				pRegTable->SetRegAddr(0xFD);
				pRegTable->SetRegInfo({ 0x02 }, _T("IDRev"));
				{
					pRegTable->SetBitDetail(_T("IDRev"), _T("IDRev"), 0xFF, 0, ONLY_R);
				}

				pRegTable->SetRegAddr(0xFE);
				pRegTable->SetRegInfo({ 0x80 }, _T("IntFlag"));
				{
					pRegTable->SetBitDetail(_T("PorInt"), 7, _T("POR INT"), 1);
					pRegTable->SetBitDetail(_T("DataInt"), 4, _T("Data INT"));
					pRegTable->SetBitDetail(_T("AlsInt"), 0, _T("ALS INT"));
				}

				pRegTable->SetRegAddr(0xFF);
				pRegTable->SetRegInfo({ 0x80 }, _T("StatFlag"));
				{
					pRegTable->SetBitDetail(_T("TmpErr"), 5, _T("TmpData Invalid Flag"));
					pRegTable->SetBitDetail(_T("AlsErr"), 0, _T("AlsData0~1 Invalid Flag"));
				}

				pRegTable->SetRegAddr(0x04);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("AlsData0"), 2);
				{
					pRegTable->SetBitDetail2(_T("AlsData0"), _T("AlsData0"));
				}

				pRegTable->SetRegAddr(0x06);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("AlsData1"), 2);
				{
					pRegTable->SetBitDetail2(_T("AlsData1"), _T("AlsData1"));
				}

				pRegTable->SetRegAddr(0x0C);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("AmbData"), 2);
				{
					pRegTable->SetBitDetail2(_T("AmbData"), _T("AmbData"));
				}

				pRegTable->SetRegAddr(0x0E);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("TmpData"), 2);
				{
					pRegTable->SetBitDetail2(_T("TmpData"), _T("TmpData"));
				}

				pRegTable->SetRegAddr(0x4F);
				pRegTable->SetRegInfo({ 0x00 }, _T("WaitTime"));
				{
					pRegTable->SetBitDetail(_T("WaitTime"), _T("The extra time for saving power"));
				}

				pRegTable->SetRegAddr(0x50);
				pRegTable->SetRegInfo({ 0x12 }, _T("AlsCtrl"));
				{
					pRegTable->SetBitDetail(_T("AlsGain1"), _T("AlsData1 Gain"), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x01);
					pRegTable->SetBitDetail(_T("AlsGain0"), _T("AlsData0 Gain"), 0x07, 0, BOTH_RW, { 0, 0x06 }, 0x02);
				}

				pRegTable->SetRegAddr(0x52);
				pRegTable->SetRegInfo({ 0x00 }, _T("AlsPuc"));
				{
					pRegTable->SetBitDetail(_T("AlsPuc"), _T("Als Conversion Time"), 0x1F, 0, BOTH_RW, { 0, 0x1F });
				}

				pRegTable->SetRegAddr(0x55);
				pRegTable->SetRegInfo({ 0x29 }, _T("AlsPuw0"));
				{
					pRegTable->SetBitDetail(_T("AlsPuw0"), _T("AlsData0 Conversion width"), 0x7F, 0, BOTH_RW, { 0, 0x7F }, 0x29);
				}

				pRegTable->SetRegAddr(0x56);
				pRegTable->SetRegInfo({ 0x0A }, _T("AlsPuw1"));
				{
					pRegTable->SetBitDetail(_T("AlsPuw1"), _T("AlsData1 Conversion width"), 0x7F, 0, BOTH_RW, { 0, 0x7F }, 0x0A);
				}

				pRegTable->SetRegAddr(0x5B);
				pRegTable->SetRegInfo({ 0x01 }, _T("AlsAlgoCtrl"));
				{
					pRegTable->SetBitDetail(_T("AlsTurbo"), 6, _T("1/10 Time Unit"), 0);
					pRegTable->SetBitDetail(_T("AlsIntSrc"), 4, _T("Define the AlsData to assert AlsInt."), 0);
					pRegTable->SetBitDetail(_T("AlsPers"), _T("Als Persistence"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x01);
				}

				pRegTable->SetRegAddr(0x5C);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("AlsThLow"), 2);
				{
					pRegTable->SetBitDetail2(_T("AlsThLow"), { 0x00, 0x00 });
				}

				pRegTable->SetRegAddr(0x5E);
				pRegTable->SetRegInfo({ 0xFF, 0xFF }, _T("AlsThHigh"), 2);
				{
					pRegTable->SetBitDetail2(_T("AlsThHigh"), { 0xFF, 0xFF });
				}

				//RD Mode
				{
					//RD Mode SoftWare
					pRegTable->SetRegAddr(0x10);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak25"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak25"), { 0x00, 0x00 });
					}
					pRegTable->SetRegAddr(0x12);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak35"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak35"), { 0x00, 0x00 });
					}
					pRegTable->SetRegAddr(0x14);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak45"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak45"), { 0x00, 0x00 });
					}
					pRegTable->SetRegAddr(0x16);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak55"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak55"), { 0x00, 0x00 });
					}
					pRegTable->SetRegAddr(0x18);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak65"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak65"), { 0x00, 0x00 });
					}
					pRegTable->SetRegAddr(0x1A);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak75"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak75"), { 0x00, 0x00 });
					}
					pRegTable->SetRegAddr(0x1C);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak85"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak85"), { 0x00, 0x00 });
					}
					pRegTable->SetRegAddr(0x1E);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak95"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak95"), { 0x00, 0x00 });
					}

					pRegTable->SetRegAddr(0x20);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("LTAR"), 2);
					{
						pRegTable->SetBitDetail2(_T("LTAR"), { 0x00, 0x00 }, _T("Define TmpData at 95C for Leak"));
					}

					//pRegTable->SetRegAddr(0x22);
					//pRegTable->SetRegInfo({ 0x00 }, _T("PsLcf"));
					//{
					//	pRegTable->SetBitDetail(_T("PsLcf"), _T("PsData Lcf = PsLcf/64"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x23);
					//pRegTable->SetRegInfo({ 0x00 }, _T("IrLcf"));
					//{
					//	pRegTable->SetBitDetail(_T("IrLcf"), _T("IrData Lcf = IrLcf/64"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					pRegTable->SetRegAddr(0x24);
					pRegTable->SetRegInfo({ 0x00 }, _T("AlsLcf0"));
					{
						pRegTable->SetBitDetail(_T("AlsLcf0"), _T("AlsData0 Lcf = PsLcf/64"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					pRegTable->SetRegAddr(0x25);
					pRegTable->SetRegInfo({ 0x00 }, _T("AlsLcf1"));
					{
						pRegTable->SetBitDetail(_T("AlsLcf1"), _T("AlsData1 Lcf = PsLcf/64"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					//pRegTable->SetRegAddr(0x26);
					//pRegTable->SetRegInfo({ 0x00 }, _T("AlsLcf2"));
					//{
					//	pRegTable->SetBitDetail(_T("AlsLcf2"), _T("AlsData2 Lcf = PsLcf/64"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x27);
					//pRegTable->SetRegInfo({ 0x00 }, _T("AlsLcf3"));
					//{
					//	pRegTable->SetBitDetail(_T("AlsLcf3"), _T("AlsData3 Lcf = PsLcf/64"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x28);
					//pRegTable->SetRegInfo({ 0x00 }, _T("PsTcfLow"));
					//{
					//	pRegTable->SetBitDetail(_T("PsTcfLow"), _T("PsData Tcf = PsTcfLow/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x29);
					//pRegTable->SetRegInfo({ 0x00 }, _T("PsTcfHigh"));
					//{
					//	pRegTable->SetBitDetail(_T("PsTcfHigh"), _T("PsData Tcf = PsTcfHigh/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x2A);
					//pRegTable->SetRegInfo({ 0x00 }, _T("IrTcfLow"));
					//{
					//	pRegTable->SetBitDetail(_T("IrTcfLow"), _T("IrData Tcf = IrTcfLow/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x2B);
					//pRegTable->SetRegInfo({ 0x00 }, _T("IrTcfHigh"));
					//{
					//	pRegTable->SetBitDetail(_T("IrTcfHigh"), _T("IrData Tcf = IrTcfHigh/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					pRegTable->SetRegAddr(0x2C);
					pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfLow0"));
					{
						pRegTable->SetBitDetail(_T("AlsTcfLow0"), _T("AlsData0 Tcf = AlsTcfLow0/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					pRegTable->SetRegAddr(0x2D);
					pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfHigh0"));
					{
						pRegTable->SetBitDetail(_T("AlsTcfHigh0"), _T("AlsData0 Tcf = AlsTcfHigh0/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					pRegTable->SetRegAddr(0x2E);
					pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfLow1"));
					{
						pRegTable->SetBitDetail(_T("AlsTcfLow1"), _T("AlsData1 Tcf = AlsTcfLow1/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					pRegTable->SetRegAddr(0x2F);
					pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfHigh1"));
					{
						pRegTable->SetBitDetail(_T("AlsTcfHigh1"), _T("AlsData1 Tcf = AlsTcfHigh1/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					//pRegTable->SetRegAddr(0x30);
					//pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfLow2"));
					//{
					//	pRegTable->SetBitDetail(_T("AlsTcfLow2"), _T("AlsData2 Tcf = AlsTcfLow2/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x31);
					//pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfHigh2"));
					//{
					//	pRegTable->SetBitDetail(_T("AlsTcfHigh2"), _T("AlsData2 Tcf = AlsTcfHigh2/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x32);
					//pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfLow3"));
					//{
					//	pRegTable->SetBitDetail(_T("AlsTcfLow3"), _T("AlsData3 Tcf = AlsTcfLow3/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					//pRegTable->SetRegAddr(0x33);
					//pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfHigh3"));
					//{
					//	pRegTable->SetBitDetail(_T("AlsTcfHigh3"), _T("AlsData3 Tcf = AlsTcfHigh3/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					//}

					pRegTable->SetRegAddr(0x3E);
					pRegTable->SetRegInfo({ 0x6E }, _T("TTAR"));
					{
						pRegTable->SetBitDetail(_T("TTAR"), _T("TmpData Unit= TTAR x 10us"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x6E);
					}

					//pRegTable->SetRegAddr(0x3F);
					//pRegTable->SetRegInfo({ 0x1B }, _T("PTAR"));
					//{
					//	pRegTable->SetBitDetail(_T("PTAR"), _T("PsData Unit= PTAR x 10us at 9 bits"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x1B);
					//}

					//pRegTable->SetRegAddr(0x40);
					//pRegTable->SetRegInfo({ 0x14 }, _T("ATAR"));
					//{
					//	pRegTable->SetBitDetail(_T("ATAR"), _T("AlsData0~2 Unit= ATAR x 50us"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x1B);
					//}

					pRegTable->SetRegAddr(0x41);
					pRegTable->SetRegInfo({ 0x03 }, _T("TmpAdc"));	//TODO: check value
					{
						pRegTable->SetBitDetail(_T("TmpCap"), _T("Control pin \"pcap_sel\" at TMP ADC"), 0x07, 0, BOTH_RW, { 0, 0x07 }, 0x03);
					}

					//pRegTable->SetRegAddr(0x42);
					//pRegTable->SetRegInfo({ 0xF1 }, _T("PxyAdc"));
					//{
					//	pRegTable->SetBitDetail(_T("PsV2i"), _T("Control pin \"pxy_v2i_sel\" at PS/IR ADC"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x0F);
					//	pRegTable->SetBitDetail(_T("PxyCap"), 0, _T("Control pin \"pcap_sel\" at PS/IR ADC"), 1);
					//}

					pRegTable->SetRegAddr(0x43);
					pRegTable->SetRegInfo({ 0x8D }, _T("AnalogA"));
					{
						pRegTable->SetBitDetail(_T("TmpBias"), 7, _T("Control pin \"pdvb0d3v_en\" at TMP"), 1);
						pRegTable->SetBitDetail(_T("IrBias"), 6, _T("Control pin \"pdvb0d3v_en\" at IR"));
						//pRegTable->SetBitDetail(_T("PsBias"), 5, _T("Control pin \"pdvb0d3v_en\" at PS"));
						pRegTable->SetBitDetail(_T("AlsBias"), 4, _T("Control pin \"pdvb0d3v_en\" at ALS"));
						pRegTable->SetBitDetail(_T("Reserved0x43_3"), 3, _T("Reserved0x43_3"), 1);
						//pRegTable->SetBitDetail(_T("DfltEn"), 3, _T("Control pin \"dflten\" at all functions"), 1);
						pRegTable->SetBitDetail(_T("IrDark"), 2, _T("Control pin \"ir_dark\" at IR(AlsData1)"), 1);
						//pRegTable->SetBitDetail(_T("PsDark"), 1, _T("Control pin \"ir_dark\" at PS"));
						pRegTable->SetBitDetail(_T("AlsDark"), 0, _T("Control pin \"als_dark\" at ALS(AlsData0)"), 1);
					}

					pRegTable->SetRegAddr(0x44);
					pRegTable->SetRegInfo({ 0x00 }, _T("AnalogB"));
					{
						pRegTable->SetBitDetail(_T("TestSel"), 7, _T("Control pin \"test_sel\""));
						pRegTable->SetBitDetail(_T("IbTest"), _T("Control pin \"ibtest_sel\""), 0x70, 4, BOTH_RW, { 0, 0x07 });
						pRegTable->SetBitDetail(_T("AnaEn"), 3, _T("Control pin \"ana_en\""));
						pRegTable->SetBitDetail(_T("AnaTest"), _T("Control pin \"ana_test\""), 0x07, 0, BOTH_RW, { 0, 0x07 });
					}

					pRegTable->SetRegAddr(0x45);
					pRegTable->SetRegInfo({ 0x00 }, _T("AnalogC"));
					{
						//pRegTable->SetBitDetail(_T("CoasDc"), 4, _T("Control pin \"coas_offset\" at PS/IR"));
						pRegTable->SetBitDetail(_T("AnaReg"), _T("Control pin \"ana_reg\""), 0x0F, 0, BOTH_RW, { 0, 0x0F });
					}

					pRegTable->SetRegAddr(0x46);
					pRegTable->SetRegInfo({ 0x20 }, _T("AnalogD"));
					{
						pRegTable->SetBitDetail(_T("AlsFreq1"), 7, _T("Control pin \"f2xsel\" at IR(AlsData1)"));
						pRegTable->SetBitDetail(_T("AlsFreq0"), 6, _T("Control pin \"f2xsel\" at ALS(AlsData0)"));
						//pRegTable->SetBitDetail(_T("DiodeVbs"), _T("Control pin \"diode_vbs\""), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x02);
						pRegTable->SetBitDetail(_T("Reserved0x46_5_4"), _T("Reserved0x46_5_4"), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x02);
						pRegTable->SetBitDetail(_T("VrefOp"), _T("Control pin \"vref_op\""), 0x0C, 2, BOTH_RW, { 0, 0x03 }, 0x00);
						//pRegTable->SetBitDetail(_T("Vtoph"), _T("Control pin \"vtoph_set\""), 0x03, 0, BOTH_RW, { 0, 0x03 }, 0x03);
						pRegTable->SetBitDetail(_T("Reserved0x46_1_0"), _T("Reserved0x46_1_0"), 0x03, 0, BOTH_RW, { 0, 0x03 });
					}

					pRegTable->SetRegAddr(0x47);
					pRegTable->SetRegInfo({ 0x00 }, _T("AnalogE"));
					{
						pRegTable->SetBitDetail(_T("DcPath"), 7, _T("Control pin \"dcpath\""));
						pRegTable->SetBitDetail(_T("DarkTrim"), _T("Control pin \"darktrim\""), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x00);
					}

					pRegTable->SetRegAddr(0x48);
					pRegTable->SetRegInfo({ 0x16 }, _T("AnalogF"));
					{
						pRegTable->SetBitDetail(_T("LoscTrim"), _T("Control pin \"losc_trim\""), 0x1F, 0, BOTH_RW, { 0, 0x1F }, 0x16);
					}

					pRegTable->SetRegAddr(0x49);
					pRegTable->SetRegInfo({ 0x20 }, _T("AnalogG"));
					{
						pRegTable->SetBitDetail(_T("HoscVbs"), _T("Control pin \"hosc_vbs\""), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x02);
						pRegTable->SetBitDetail(_T("LdodTrim"), _T("Control pin \"ldod_pmosw\""), 0x07, 0, BOTH_RW, { 0, 0x07 });
					}

					//pRegTable->SetRegAddr(0x4B);
					//pRegTable->SetRegInfo({ 0x00 }, _T("TxFreq"));
					//{
					//	pRegTable->SetBitDetail(_T("TxFreq"), _T("Tx Frequency"), 0x07, 0, BOTH_RW, { 0, 0x07 });
					//}

					//pRegTable->SetRegAddr(0x4C);
					//pRegTable->SetRegInfo({ 0x00 }, _T("CtPuw"));
					//{
					//	pRegTable->SetBitDetail(_T("CtPuw"), _T("Fine Crosstalk DAC Width"));
					//}

					//pRegTable->SetRegAddr(0x4D);
					//pRegTable->SetRegInfo({ 0x06 }, _T("TxPuw"));
					//{
					//	pRegTable->SetBitDetail(_T("AmbPuw"), _T(""), 0x30, 4, BOTH_RW, { 0, 0x03 });
					//	pRegTable->SetBitDetail(_T("DrvPuw"), _T(""), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x06);
					//}

					//pRegTable->SetRegAddr(0x4E);
					//pRegTable->SetRegInfo({ 0x00 }, _T("PrePuw"));
					//{
					//	pRegTable->SetBitDetail(_T("PrePuw"), _T("Pre-Heat Pulse Width"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
					//}

					pRegTable->SetRegAddr(0x7B);
					pRegTable->SetRegInfo({ 0x00 }, _T("DigCtrl"));
					{
						//pRegTable->SetBitDetail(_T("VenOff"), 7, _T("Enable \"power_sel\""));
						//pRegTable->SetBitDetail(_T("PreOff"), 6, _T("Enable Pre Timing"));
						//pRegTable->SetBitDetail(_T("TmpNoMean"), 5, _T("TmpData mean time"));
						pRegTable->SetBitDetail(_T("FastTmp"), 4, _T("Out TmpData every Conversion"));
						pRegTable->SetBitDetail(_T("FastEn"), 3, _T("Conversion is min"));
						pRegTable->SetBitDetail(_T("LadcEn"), 2, _T("AmbData = Leak Table"));
						//pRegTable->SetBitDetail(_T("PxshEn"), 1, _T("Enable \"pxsh\" at Pre-heat"));
						pRegTable->SetBitDetail(_T("MakeEn"), 0, _T("Use Make Data as input"));
					}

					pRegTable->SetRegAddr(0x7C);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("MakeData"), 2);
					{
						pRegTable->SetBitDetail2(_T("MakeData"), { 0x00, 0x00 }, _T("Define fake data to replace ADC data"));
					}

					pRegTable->SetRegAddr(0x7E);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("MakeTmp"), 2);
					{
						pRegTable->SetBitDetail2(_T("MakeTmp"), { 0x00, 0x00 }, _T("Define fake data to replace TmpData"));
					}

					//HardWare
					//RD Mode Hardware
					pRegTable->SetRegAddr(0xD0);
					pRegTable->SetRegInfo({ 0x00 }, _T("Mode"));
					{
						pRegTable->SetBitDetail(_T("Mode"), _T("Mode Select"), 0x07, 0, BOTH_RW, { 0x00, 0x07 });
					}

					pRegTable->SetRegAddr(0xD1);
					pRegTable->SetRegInfo({ 0x00 }, _T("PadCtrl"));
					{
						pRegTable->SetBitDetail(_T("ForcePad"), 7, _T("ForcePad"));
						pRegTable->SetBitDetail(_T("View"), _T("View"), 0x1F, 0, BOTH_RW, { 0x00, 0x1F });
					}

					pRegTable->SetRegAddr(0xD2);
					pRegTable->SetRegInfo({ 0x4B }, _T("Tbe"));
					{
						pRegTable->SetBitDetail(_T("Tbe"), _T("Fuse Burn Width"), 0x7F, 0, BOTH_RW, { 0x00, 0x7F }, 0x4B);
					}
#if 0
					pRegTable->SetRegAddr(0xD3);
					pRegTable->SetRegInfo({ 0x00 }, _T("BRAM"));
					{
						pRegTable->SetBitDetail(_T("BRAM"), _T("Ram Bist"), 0xFF, 0, ONLY_R);
					}

					pRegTable->SetRegAddr(0xD4);
					pRegTable->SetRegInfo({ 0x00 , 0x00 }, _T("BROM"), 2);
					{
						pRegTable->SetBitDetail2(_T("BROM"), _T("Rom Bist"));
					}
#endif
					pRegTable->SetRegAddr(0xD6);
					pRegTable->SetRegInfo({ 0x01 }, _T("AnaCtrl"));
					{
						pRegTable->SetBitDetail(_T("LdoaExt"), 7, _T("Control ldoa_ext when Device ON"));
						pRegTable->SetBitDetail(_T("HoscExt"), 6, _T("Control hosc_ext when Device ON"));
						pRegTable->SetBitDetail(_T("LoscEnb"), 3, _T("Control losc_enb when Device OFF"));
						pRegTable->SetBitDetail(_T("HoscEn"), 2, _T("Control hosc_en pin when Device OFF"));
						pRegTable->SetBitDetail(_T("EnPs"), 1, _T("Control en_ps pin when Device OFF"));
						pRegTable->SetBitDetail(_T("EnbBg"), 0, _T("Control enb_bg pin when Device OFF"), 0x01);
					}

					pRegTable->SetRegAddr(0xEF);
					pRegTable->SetRegInfo({ 0x28 }, _T("WatchDog"));
					{
						pRegTable->SetBitDetail(_T("WatchDog"), _T("Time Out= WatchDog x 0.8 ms"), 0x7F, 0, BOTH_RW, { 0x00, 0x7F }, 0x28);
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
		//uint8_t Reg0xF0;
		//map<CString, CBitDetail>* pBitDetailMap;
		uint8_t AlsEn = pRegTable->GetBitValue(_T("AlsEn"));
		uint8_t AlsPuc = pRegTable->GetBitValue(_T("AlsPuc"));
		uint8_t AlsPuw0 = pRegTable->GetBitValue(_T("AlsPuw0"));
		uint8_t AlsPuw1 = pRegTable->GetBitValue(_T("AlsPuw1"));
		uint8_t WaitTime = pRegTable->GetBitValue(_T("WaitTime"));
		uint8_t AlsTurbo = pRegTable->GetBitValue(_T("AlsTurbo"));

		ConversionTime = 0;
		double AlsPucUnit = 100;
		double AlsPuwUnit = 1;
		double AlsPuwSum = (double)AlsPuw0 * AlsPuwUnit + (double)AlsPuw1 * AlsPuwUnit;

		if (AlsPuc == 0)
			AlsPuc = 1;

		switch (version)
		{
		case 10000: case 10100: case 10200:
			if (AlsEn)
			{
				if (AlsTurbo)
				{
					AlsPucUnit = 10;
					AlsPuwUnit = 0.1;
				}
				else
				{
					AlsPucUnit = 100;
					AlsPuwUnit = 1;
				}
				ConversionTime = (double)AlsPuc * AlsPucUnit;
				AlsPuwSum = ((double)AlsPuw0 * AlsPuwUnit + (double)AlsPuw1 * AlsPuwUnit) * (double)AlsPuc;

				if (AlsPuwSum > ConversionTime)
					ConversionTime = AlsPuwSum;
			}

			if (ConversionTime > 0)
			{
				ConversionTime += ((double)WaitTime * 10);
			}

			break;
		}

		return (uint32_t)(ConversionTime * 1000);
	}

	double GetPowerConsumption(uint16_t version, CRegisterTable* pRegTable)
	{
		uint8_t Reg0xF0;
		map<CString, CBitDetail>* pBitDetailMap;
		Reg0xF0 = pRegTable->RegInfo.at(0xF0).RegCurVal.at(0);
		pBitDetailMap = &pRegTable->BitDetail;

		PowerConsumption = 0;
		switch (version)
		{
			case 10000:
			case 10100:
			case 10200:
				uint8_t AlsPuc = pRegTable->GetBitValue(_T("AlsPuc"));
				uint8_t WaitTime = pRegTable->GetBitValue(_T("WaitTime"));
				double AlsPuc_T = (double)AlsPuc*100;
				double WaitTime_T = (double)WaitTime*10;
				ConversionTime = AlsPuc_T + WaitTime_T;

				if (AlsPuc == 0x00 && WaitTime == 0x00)
					PowerConsumption = 118.0;
				else
				{
					PowerConsumption = (AlsPuc_T * 118.0) + (0.5 * WaitTime_T);
					PowerConsumption /= ConversionTime;  //uA
				}
		}

		return PowerConsumption;
	}

	void AutoDac(uint16_t version, CRegisterTable* pRegTable)
	{

	}
};
