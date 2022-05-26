#pragma once
#include "Define.h"

class CDA3110T : public CDieInfo {
public:
	CDA3110T() {}
	void Init(uint16_t version)
	{
		DieName = _T("DA3110T");
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
					pRegTable->SetBitDetail(_T("EnDyna"), 4, _T("Wake up method"));
					pRegTable->SetBitDetail(_T("DnPsAll"), 3, _T("Use A like timing"));
					pRegTable->SetBitDetail(_T("EnIr"), 2, _T("IR Enable"));
					pRegTable->SetBitDetail(_T("EnPs"), 1, _T("PS Enable"));
					pRegTable->SetBitDetail(_T("EnPsAen"), 0, _T("Enable PS P/A like timing"));
				}

				pRegTable->SetRegAddr(0xF1);
				pRegTable->SetRegInfo({ 0x02 }, _T("IntCtrl"));
				{
					pRegTable->SetBitDetail(_T("ObjIen"), 7, _T("Obj Int Enable"));
					pRegTable->SetBitDetail(_T("IrIen"), 2, _T("IR Int Enable"));
					pRegTable->SetBitDetail(_T("PsIen"), 1, _T("PS Int Enable"), 0x01);
				}

				pRegTable->SetRegAddr(0xF2);
				pRegTable->SetRegInfo({ 0x00 }, _T("HaltCtrl"));
				{
					pRegTable->SetBitDetail(_T("ReadClear"), 7, _T("Interrupt clear method"));
					pRegTable->SetBitDetail(_T("IrHalt"), 2, _T("IR Halt"));
					pRegTable->SetBitDetail(_T("PsHalt"), 1, _T("PS Halt"));
				}

				pRegTable->SetRegAddr(0xF3);
				pRegTable->SetRegInfo({ 0x00 }, _T("SysCtrl"));
				{
					pRegTable->SetBitDetail(_T("FallingPor"), 7, _T("Falling POR detection"));
					pRegTable->SetBitDetail(_T("Operation"), 0, _T("Openation Mode"));
				}

				pRegTable->SetRegAddr(0xF4);
				pRegTable->SetRegInfo({ 0x00 }, _T("SwRst"));
				{
					pRegTable->SetBitDetail(_T("EnSw"), _T("Software reset"),_T(""), 0xEE);	//write 0xEE to reset
				}

				pRegTable->RegInfo[0xFC] = CRegInfo({ 0x10 }, _T("IDPod"));
				pRegTable->RegInfo[0xFD] = CRegInfo({ 0x00 }, _T("IDRev"));

				pRegTable->SetRegAddr(0xFE);
				pRegTable->SetRegInfo({ 0x80 }, _T("IntFlag"));
				{
					pRegTable->SetBitDetail(_T("PorInt"), 7, _T("POR INT"), 1);
					pRegTable->SetBitDetail(_T("IrInt"), 2, _T("IR INT"));
					pRegTable->SetBitDetail(_T("PsInt"), 1, _T("PS INT"));
				}

				pRegTable->SetRegAddr(0xFF);
				pRegTable->SetRegInfo({ 0x00 }, _T("StatFlag"));
				{
					pRegTable->SetBitDetail(_T("PsObj"), 7, _T("PS Object"));
					pRegTable->SetBitDetail(_T("IrErrOn"), 6, _T("IR LED On Error Flag"));
					pRegTable->SetBitDetail(_T("IrErrOff"), 5, _T("IR LED Off Error Flag"));
					pRegTable->SetBitDetail(_T("PsErrOn"), 4, _T("PS LED On Error Flag"));
					pRegTable->SetBitDetail(_T("PsErrOff"), 3, _T("PS LED On Error  Flag"));
					pRegTable->SetBitDetail(_T("IrErr"), 2, _T("IR Error Flag"));
					pRegTable->SetBitDetail(_T("PsErr"), 1, _T("PS Error Flag"));
				}

				pRegTable->SetRegAddr(0x00);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("PsCh"), 2);
				{
					pRegTable->SetBitDetail2(_T("PsCh"));
				}

				pRegTable->SetRegAddr(0x02);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("IrCh"), 2);
				{
					pRegTable->SetBitDetail2(_T("IrCh"));
				}

				pRegTable->SetRegAddr(0x04);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("TmpCh"), 2);
				{
					pRegTable->SetBitDetail2(_T("TmpCh"));
				}

				pRegTable->SetRegAddr(0x06);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("LoscCh"), 2);
				{
					pRegTable->SetBitDetail2(_T("LoscCh"));
				}

				pRegTable->SetRegAddr(0x10);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsConvTime"));
				{
					pRegTable->SetBitDetail(_T("PsMean"), _T("PS Mean Time"), 0x30, 4, BOTH_RW, { 0, 0x03 });
					pRegTable->SetBitDetail(_T("PsAdcTime"), _T("PS Adc Time"), 0x07, 0, BOTH_RW, { 0, 4 });
				}

				pRegTable->SetRegAddr(0x11);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsNapTime"));
				{
					pRegTable->SetBitDetail(_T("PsNapTime"), _T("Inserts PS Dummy Time"));
				}

				pRegTable->SetRegAddr(0x12);
				pRegTable->SetRegInfo({ 0x18 }, _T("PsCtrl"));
				{
					pRegTable->SetBitDetail(_T("PsNapAlgo"), 5, _T("PS Nap Algo"));
					pRegTable->SetBitDetail(_T("PsIntAlgo"), 4, _T("PS INT Algo"), 1);
					pRegTable->SetBitDetail(_T("PsGain"), _T("PS Gain"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x08);
				}

				pRegTable->SetRegAddr(0x13);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsIntPuw"));
				{
					pRegTable->SetBitDetail(_T("PsIntPuw"), _T("PS Integration Pulse Width"), 0x7F, 0, BOTH_RW, { 0, 127 });
				}

				pRegTable->SetRegAddr(0x14);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsIntPuc"));
				{
					pRegTable->SetBitDetail(_T("PsIntPuc"), _T("PS Integration Pulse Count"), 0x3F, 0, BOTH_RW, { 0, 63 });
				}

				pRegTable->SetRegAddr(0x15);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsPrePuc"));
				{
					pRegTable->SetBitDetail(_T("PsPrePuc"), _T("PS Pre_Heat Pulse Count"), 0x0F, 0, BOTH_RW, { 0, 15 });
				}

				pRegTable->SetRegAddr(0x16);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsDrvCtrl"));
				{
					pRegTable->SetBitDetail(_T("PsDrvForce"), _T("Fources PS driving waveform"), 0xC0, 6, BOTH_RW, { 0, 3 });
					pRegTable->SetBitDetail(_T("PsDrvTurbo"), 5, _T("Control pin ¡§led_turbo¡¨ at PS function"));
					pRegTable->SetBitDetail(_T("PsDrvLed"), 4, _T("Configures the maximum driving current"));
					pRegTable->SetBitDetail(_T("PsDrv"), _T("PS driving current"), 0x0F, 0, BOTH_RW, { 0, 15 });
				}

				pRegTable->SetRegAddr(0x17);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsCtCtrl"));
				{
					pRegTable->SetBitDetail(_T("PsCtGain"), _T("PS CTDAC Gain"), 0xC0, 6, BOTH_RW, { 0, 2 });
					pRegTable->SetBitDetail(_T("PsCtDac"), _T("PS CTDAC Step"), 0x1F, 0, BOTH_RW, { 0, 31 });
				}

				pRegTable->SetRegAddr(0x18);
				pRegTable->SetRegInfo({ 0x01 }, _T("PsPers"));
				{
					pRegTable->SetBitDetail(_T("PsPers"), _T("PS Persistence"), 0x3F, 0, BOTH_RW, { 0, 0x3F }, 0x01);
				}

				pRegTable->SetRegAddr(0x19);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsIambCtrl"));
				{
					pRegTable->SetBitDetail(_T("PsIambOn"), 7, _T("Enable PS Ambient Dac"));
					pRegTable->SetBitDetail(_T("PSIambDac"), _T("PS Iamb Dac"), 0x3F, 0, BOTH_RW, { 0, 0x3F });
				}

				pRegTable->SetRegAddr(0x1A);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("PsThLow"), 2);
				{
					pRegTable->SetBitDetail2(_T("PsThLow"), { 0x00, 0x00 }, _T(""), _T(""));
				}

				pRegTable->SetRegAddr(0x1C);
				pRegTable->SetRegInfo({ 0xFF, 0xFF }, _T("PsThHigh"), 2);
				{
					pRegTable->SetBitDetail2(_T("PsThHigh"), { 0xFF, 0xFF }, _T(""), _T(""));
				}

				pRegTable->SetRegAddr(0x1E);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("PsCalb"), 2);
				{
					pRegTable->SetBitDetail2(_T("PsCalb"), { 0x00, 0x00 }, _T(""), _T(""));
				}

				pRegTable->SetRegAddr(0x20);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrConvTime"));
				{
					pRegTable->SetBitDetail(_T("IrMean"), _T("IR Mean Time"), 0x30, 4, BOTH_RW, { 0, 3 });
					pRegTable->SetBitDetail(_T("IrAdcTime"), _T("IR ADC Time"), 0x07, 0, BOTH_RW, { 0, 4 });
				}
				pRegTable->SetRegAddr(0x21);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrNapTime"));
				{
					pRegTable->SetBitDetail(_T("IrNapTime"), _T("Inserts IR Dummy Time"));
				}
				pRegTable->SetRegAddr(0x22);
				pRegTable->SetRegInfo({ 0x08 }, _T("IrCtrl"));
				{
					pRegTable->SetBitDetail(_T("IrGain"), _T("IR Gain"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x08);
				}

				pRegTable->SetRegAddr(0x23);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrIntPuw"));
				{
					pRegTable->SetBitDetail(_T("IrIntPuw"), _T("IR Integration Pulse Width"), 0x7F, 0, BOTH_RW, { 0, 127 });
				}

				pRegTable->SetRegAddr(0x24);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrIntPuc"));
				{
					pRegTable->SetBitDetail(_T("IrIntPuc"), _T("IR Integration Pulse Count"), 0x3F, 0, BOTH_RW, { 0, 63 });
				}

				pRegTable->SetRegAddr(0x25);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrPrePuc"));
				{
					pRegTable->SetBitDetail(_T("IrPrePuc"), _T("IR Pre_Heat Pulse Count"), 0x0F, 0, BOTH_RW, { 0, 15 });
				}

				pRegTable->SetRegAddr(0x26);
				pRegTable->SetRegInfo({ 0x40 }, _T("IrDrvCtrl"));
				{
					pRegTable->SetBitDetail(_T("IrDrvForce"), _T("Fources IR driving waveform"), 0xC0, 6, BOTH_RW, { 0, 3 }, 0x01);
					pRegTable->SetBitDetail(_T("IrDrvTurbo"), 5, _T("Control pin ¡§led_turbo¡¨ at IR function"));
					pRegTable->SetBitDetail(_T("IrDrvLed"), 4, _T("Configures the maximum driving current"));
					pRegTable->SetBitDetail(_T("IrDrv"), _T("IR driving current"), 0x0F, 0, BOTH_RW, { 0, 15 });
				}

				pRegTable->SetRegAddr(0x27);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrCtCtrl"));
				{
					pRegTable->SetBitDetail(_T("IrCtGain"), _T("IR CTDAC Gain"), 0xC0, 6, BOTH_RW, { 0, 2 });
					pRegTable->SetBitDetail(_T("IrCtDac"), _T("IR CTDAC Step"), 0x1F, 0, BOTH_RW, { 0, 31 });
				}

				pRegTable->SetRegAddr(0x2B);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrIambCtrl"));
				{
					pRegTable->SetBitDetail(_T("IrIambOn"), 7, _T("Enable IR Ambient Dac"));
					pRegTable->SetBitDetail(_T("IrIambDac"), _T("IR Iamb Dac"), 0x3F, 0, BOTH_RW, { 0, 0x3F });
				}

				pRegTable->SetRegAddr(0x31);
				pRegTable->SetRegInfo({ 0x80 }, _T("Analog ICT DAC"));
				{
					pRegTable->SetBitDetail(_T("ict_dac_enb"), 7, _T("Enable PS ICT"), 1);
					pRegTable->SetBitDetail(_T("ict_dac"), _T("PS ICT DAC"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
				}

				//RD Mode
				{
					//RD Mode SoftWare
					pRegTable->SetRegAddr(0x0A);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("ForceCh"), 2);
					{
						pRegTable->SetBitDetail2(_T("ForceCh"));
					}

					pRegTable->SetRegAddr(0x0C);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("ForceTemp"), 2);
					{
						pRegTable->SetBitDetail2(_T("ForceTemp"));
					}

					pRegTable->SetRegAddr(0x0E);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("TTAR"), 2);
					{
						pRegTable->SetBitDetail2(_T("TTAR"));
					}

					pRegTable->SetRegAddr(0x28);
					pRegTable->SetRegInfo({ 0x11 }, _T("AdcUnit"));
					{
						pRegTable->SetBitDetail(_T("AdcUnit"), _T("ADC Time Unit(10 uS)"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x11);
					}

					pRegTable->SetRegAddr(0x29);
					pRegTable->SetRegInfo({ 0x05 }, _T("ConvUnit"));
					{
						pRegTable->SetBitDetail(_T("ConvUnit"), _T("Conversion Unit(1 ms)"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x05);
					}

					pRegTable->SetRegAddr(0x2A);
					pRegTable->SetRegInfo({ 0xA2 }, _T("DevSlot"));
					{
						pRegTable->SetBitDetail(_T("SlotTmp"), _T("Temperature time slot"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x0A);
						pRegTable->SetBitDetail(_T("SlotAdc"), _T("L2F ADC stable time"), 0x07, 0, BOTH_RW, { 0, 0x07 }, 0x02);
					}

					pRegTable->SetRegAddr(0x2C);
					pRegTable->SetRegInfo({ 0x00 }, _T("PsTmpCoef"));
					{
						pRegTable->SetBitDetail(_T("PsTcfH"), _T("PS TMP Coef High"), 0xF0, 4, BOTH_RW, { 0, 0x0F });
						pRegTable->SetBitDetail(_T("PsTcfL"), _T("PS TMP Coef Low"), 0x0F, 0, BOTH_RW, { 0, 0x0F });
					}

					pRegTable->SetRegAddr(0x2D);
					pRegTable->SetRegInfo({ 0x00 }, _T("IrTmpCoef"));
					{
						pRegTable->SetBitDetail(_T("IrTcfH"), _T("IR TMP Coef High"), 0xF0, 4, BOTH_RW, { 0, 0x0F });
						pRegTable->SetBitDetail(_T("IrTcfL"), _T("IR TMP Coef Low"), 0x0F, 0, BOTH_RW, { 0, 0x0F });
					}

					pRegTable->SetRegAddr(0x2E);
					pRegTable->SetRegInfo({ 0x00 }, _T("PsLeakCoef"));
					{
						pRegTable->SetBitDetail(_T("PsLcf"), _T("PS Leakage Coef"));
					}

					pRegTable->SetRegAddr(0x2F);
					pRegTable->SetRegInfo({ 0x00 }, _T("IrLeakCoef"));
					{
						pRegTable->SetBitDetail(_T("IrLcf"), _T("IR Leakage Coef"));
					}

					pRegTable->SetRegAddr(0x30);
					pRegTable->SetRegInfo({ 0xF0 }, _T("DigiCtrl"));
					{
						pRegTable->SetBitDetail(_T("FastPuc"), 7, _T("Fast Pulse Count"), 0x01);
						pRegTable->SetBitDetail(_T("Pxsh"), 6, _T("Enable \"pxsh\""), 0x01);
						pRegTable->SetBitDetail(_T("IrComp"), 5, _T("Enable \"ir_dark_comp_en\" at IR"), 0x01);
						pRegTable->SetBitDetail(_T("PsComp"), 4, _T("Enable \"ir_dark_comp_en\" at PS"), 0x01);
						pRegTable->SetBitDetail(_T("ConvMin"), 3, _T("Conversion Min Select"));
						pRegTable->SetBitDetail(_T("TmpChSel"), 2, _T("Temperature Channel Select"));
						pRegTable->SetBitDetail(_T("TqenDouble"), 1, _T("Tgen Unit"));
						pRegTable->SetBitDetail(_T("Force"), 0, _T("Select Input data"));
					}

					pRegTable->SetRegAddr(0x32);
					pRegTable->SetRegInfo({ 0x00 }, _T("AnalogTest"));
					{
						pRegTable->SetBitDetail(_T("ict_dac_sel"), 7, _T("Control pin \"ict_dac_sel\""));
						pRegTable->SetBitDetail(_T("ibtest_sel"), 6, _T("Control pin \"ibtest_sel\""));
						pRegTable->SetBitDetail(_T("test_sel"), 5, _T("Control pin \"test_sel\""));
						pRegTable->SetBitDetail(_T("temp_mux"), 4, _T("Control pin \"temp_mux\""));
						pRegTable->SetBitDetail(_T("en_ana_test"), 3, _T("Control pin \"en_ana_test\""));
						pRegTable->SetBitDetail(_T("ana_test"), _T("Control pin \"ana_test\""), 0x07, 0, BOTH_RW, { 0, 0x07 });
					}

					pRegTable->SetRegAddr(0x33);
					pRegTable->SetRegInfo({ 0x9F }, _T("AnalogOther"));
					{
						pRegTable->SetBitDetail(_T("clkm_vbs"), _T("Control pin \"clkm_vbs\""), 0xC0, 6, BOTH_RW, { 0, 0x03 }, 0x02);
						pRegTable->SetBitDetail(_T("vref_op_sel"), _T("Control pin \"vref_op_sel\""), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x01);
						pRegTable->SetBitDetail(_T("vtoph_set"), _T("Control pin \"vtoph_set\""), 0x0C, 2, BOTH_RW, { 0, 0x03 }, 0x03);
						pRegTable->SetBitDetail(_T("vdiode_sel"), _T("Control pin \"vdiode_sel\""), 0x03, 0, BOTH_RW, { 0, 0x03 }, 0x03);
					}

					pRegTable->SetRegAddr(0x34);
					pRegTable->SetRegInfo({ 0x72 }, _T("AnalogTmp"));
					{
						pRegTable->SetBitDetail(_T("TmpV2iAdc"), _T("Control pin \"pxy_v2i_sel\" at TMP ADC"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x07);
						pRegTable->SetBitDetail(_T("TmpCapAdc"), _T("Control pin \"cap_sel\" at TMP ADC"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x02);
					}

					pRegTable->SetRegAddr(0x35);
					pRegTable->SetRegInfo({ 0xF2 }, _T("AnalogPs"));
					{
						pRegTable->SetBitDetail(_T("PsV2iAdc"), _T("Control pin \"pxy_v2i_sel\" at PS ADC"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x0F);
						pRegTable->SetBitDetail(_T("PsCapAdc"), _T("Control pin \"cap_sel\" at PS ADC"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x02);
					}

					pRegTable->SetRegAddr(0x36);
					pRegTable->SetRegInfo({ 0xF2 }, _T("AnalogIr"));
					{
						pRegTable->SetBitDetail(_T("IrV2iAdc"), _T("Control pin \"pxy_v2i_sel\" at IR ADC"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x0F);
						pRegTable->SetBitDetail(_T("IrCapAdc"), _T("Control pin \"cap_sel\" at IR ADC"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x02);
					}

					pRegTable->SetRegAddr(0x38);
					pRegTable->SetRegInfo({ 0x00 }, _T("Fuse0"));
					{
						pRegTable->SetBitDetail(_T("Fuse0"), _T("Fuse0"), 0xFF, 0, ONLY_R);
					}
					pRegTable->SetRegAddr(0x39);
					pRegTable->SetRegInfo({ 0x00 }, _T("Fuse1"));
					{
						pRegTable->SetBitDetail(_T("Fuse1"), _T("Fuse1"), 0xFF, 0, ONLY_R);
					}
					pRegTable->SetRegAddr(0x3A);
					pRegTable->SetRegInfo({ 0x00 }, _T("Fuse2"));
					{
						pRegTable->SetBitDetail(_T("Fuse2"), _T("Fuse2"), 0xFF, 0, ONLY_R);
					}
					pRegTable->SetRegAddr(0x3B);
					pRegTable->SetRegInfo({ 0x00 }, _T("Fuse3"));
					{
						pRegTable->SetBitDetail(_T("Fuse3"), _T("Fuse3"), 0xFF, 0, ONLY_R);
					}
					pRegTable->SetRegAddr(0x3C);
					pRegTable->SetRegInfo({ 0x00 }, _T("Fuse4"));
					{
						pRegTable->SetBitDetail(_T("Fuse4"), _T("Fuse4"), 0xFF, 0, ONLY_R);
					}
					pRegTable->SetRegAddr(0x3D);
					pRegTable->SetRegInfo({ 0x00 }, _T("Fuse5"));
					{
						pRegTable->SetBitDetail(_T("Fus5"), _T("Fuse5"), 0xFF, 0, ONLY_R);
					}
					pRegTable->SetRegAddr(0x3E);
					pRegTable->SetRegInfo({ 0x00 }, _T("Fuse6"));
					{
						pRegTable->SetBitDetail(_T("Fuse6"), _T("Fuse6"), 0xFF, 0, ONLY_R);
					}
					pRegTable->SetRegAddr(0x3F);
					pRegTable->SetRegInfo({ 0x00 }, _T("Fuse7"));
					{
						pRegTable->SetBitDetail(_T("Fuse7"), _T("Fuse7"), 0xFF, 0, ONLY_R);
					}

					//RD Mode Hardware
					pRegTable->SetRegAddr(0xD0);
					pRegTable->SetRegInfo({ 0x00 }, _T("Mode"));
					{
						pRegTable->SetBitDetail(_T("Mode"), _T("Mode Select"), 0x07, 0, BOTH_RW, { 0x00, 0x07 });
					}

					pRegTable->SetRegAddr(0xD1);
					pRegTable->SetRegInfo({ 0x00 }, _T("INTPadCtrl"));
					{
						pRegTable->SetBitDetail(_T("ForcePad"), _T("Force Pad"), 0xC0, 6, BOTH_RW, { 0x00, 0x03 });
						pRegTable->SetBitDetail(_T("View"), _T("View"), 0x1F, 0, BOTH_RW, { 0x00, 0x16 });
					}

					pRegTable->SetRegAddr(0xD2);
					pRegTable->SetRegInfo({ 0x05 }, _T("FuseBurnWidth"));
					{
						pRegTable->SetBitDetail(_T("Tbe"), _T("Burn Time"), 0x0F, 0, BOTH_RW, { 0x00, 0x0F }, 0x05);
					}
#if 0
					pRegTable->SetRegAddr(0xD3);
					pRegTable->SetRegInfo({ 0x00 }, _T("RamCheck"));
					{
						pRegTable->SetBitDetail(_T("BRAM"), _T("Ram Bist"), 0xFF, 0, ONLY_R);
					}

					pRegTable->SetRegAddr(0xD4);
					pRegTable->SetRegInfo({ 0x83 , 0x73}, _T("RomCheck"),0);
					{
						pRegTable->SetBitDetail2(_T("BROM"), _T("Rom Bist"));
					}
#endif
					pRegTable->SetRegAddr(0xD6);
					pRegTable->SetRegInfo({ 0x01 }, _T("AnaEnCtrl"));
					{
						pRegTable->SetBitDetail(_T("en_ps"), 3, _T("Control en_ps pin when Device OFF"));
						pRegTable->SetBitDetail(_T("en_hosc"), 2, _T("Control en_hosc pin when Device OFF"));
						pRegTable->SetBitDetail(_T("enb_losc"), 1, _T("Control enb_losc pin when Device OFF"));
						pRegTable->SetBitDetail(_T("enb_bq"), 0, _T("Control enb_bq pin when Device OFF"), 0x01);
					}

					pRegTable->SetRegAddr(0xEF);
					pRegTable->SetRegInfo({ 0x05 }, _T("I2CWdog"));
					{
						pRegTable->SetBitDetail(_T("I2CWdog"), _T("I2C Watch Dog (6.4 ms)"), 0xFF, 0, ONLY_R, { 0x00, 0xff }, 0x05);
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
		uint8_t Reg0x00;
		map<CString, CBitDetail>* pBitDetailMap;
		Reg0x00 = pRegTable->RegInfo.at(0xF0).RegCurVal.at(0);
		pBitDetailMap = &pRegTable->BitDetail;

		ConversionTime = 0;
		switch (version)
		{
		case 10000:
			if (Reg0x00 & pBitDetailMap->at(_T("EnPs")).BitMask.at(0))
			{
				//T_PS ms
				ConversionTime += (pow(2, pRegTable->GetBitValue(_T("PsMean")))
					* (30 + 5 * (double)pRegTable->GetBitValue(_T("PsAdcTime")) + (20 * (double)pRegTable->GetBitValue(_T("PsNapTime")))));

				//T_LED us
				ConversionTime += ((pow(2, pRegTable->GetBitValue(_T("PsMean")))
					* (6 + (pRegTable->GetBitValue(_T("PsIntPuw")) == 0 ? 1 : (double)pRegTable->GetBitValue(_T("PsIntPuw"))))
					* ((double)pRegTable->GetBitValue(_T("PsIntPuc")) == 0 ? 1 : (double)pRegTable->GetBitValue(_T("PsIntPuc"))
					+ (double)pRegTable->GetBitValue(_T("PsPrePuc")))) / 1000);
			}

			if (Reg0x00 & pBitDetailMap->at(_T("EnIr")).BitMask.at(0))
			{
				//T_IR ms
				ConversionTime += (pow(2, pRegTable->GetBitValue(_T("IrMean")))
					* (30 + 5 * (double)pRegTable->GetBitValue(_T("IrAdcTime")) + (20 * (double)pRegTable->GetBitValue(_T("IrNapTime")))));
			}
			break;
		}

		return (uint32_t)(ConversionTime * 1000);
	}
};