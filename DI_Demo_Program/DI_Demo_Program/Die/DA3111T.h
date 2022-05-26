#pragma once
#include "Define.h"

class CDA3111T : public CDieInfo {
public:
	CDA3111T() {}
	void Init(uint16_t version)
	{
		DieName = _T("DA3111T");
		switch (version)
		{
		case 10000:	//A+P
			DieDetail.insert(make_pair(10000, CDieDetail()));
			{
				pDieDetail = &DieDetail.at(10000);
				pRegTable = &pDieDetail->RegisterTable;

				pRegTable->DeviceID = 0x1C;

				pRegTable->SetRegAddr(0xF0);
				pRegTable->SetRegInfo({ 0x00 }, _T("DevCtrl"));
				{
					pRegTable->SetBitDetail(_T("EnDyna"), 7, _T("Wake up method"));
					pRegTable->SetBitDetail(_T("EnPsAll"), 4, _T("Use A like timing"));
					pRegTable->SetBitDetail(_T("EnPsAen"), 3, _T("Enable PS P like timing"));
					pRegTable->SetBitDetail(_T("EnIr"), 2, _T("IR Enable"));
					pRegTable->SetBitDetail(_T("EnPs"), 1, _T("PS Enable"));
					pRegTable->SetBitDetail(_T("EnAls"), 0, _T("ALS Enable"));
				}

				pRegTable->SetRegAddr(0xF1);
				pRegTable->SetRegInfo({ 0x03 }, _T("IntCtrl"));
				{
					pRegTable->SetBitDetail(_T("PushPull"), 7, _T("Enable INT Pin push pull"));
					pRegTable->SetBitDetail(_T("PsObjIen"), 6, _T("Obj Int Enable"));
					pRegTable->SetBitDetail(_T("SyncIen"), 6, _T("Enable INT pin as sync input"));
					pRegTable->SetBitDetail(_T("IrIen"), 2, _T("IR Int Enable"));
					pRegTable->SetBitDetail(_T("PsIen"), 1, _T("PS Int Enable"), 0x01);
					pRegTable->SetBitDetail(_T("AlsIen"), 0, _T("ALS Int Enable"), 0x01);
				}

				pRegTable->SetRegAddr(0xF2);
				pRegTable->SetRegInfo({ 0x00 }, _T("HaltCtrl"));
				{
					pRegTable->SetBitDetail(_T("ReadClear"), 7, _T("Interrupt clear method"));
					pRegTable->SetBitDetail(_T("IrHalt"), 2, _T("IR INT Halt"));
					pRegTable->SetBitDetail(_T("PsHalt"), 1, _T("PS INT Halt"));
					pRegTable->SetBitDetail(_T("AlsHalt"), 0, _T("ALS INT Halt"));
				}

				pRegTable->SetRegAddr(0xF3);
				pRegTable->SetRegInfo({ 0x00 }, _T("SysCtrl"));
				{
					pRegTable->SetBitDetail(_T("FallingPor"), 7, _T("Falling POR detection"));
					pRegTable->SetBitDetail(_T("VbgTime"), _T(""), 0x70, 4, BOTH_RW, { 0, 0x07 }, 0x00);
					pRegTable->SetBitDetail(_T("Operation"), 0, _T("Openation Mode"));
				}

				pRegTable->SetRegAddr(0xF4);
				pRegTable->SetRegInfo({ 0x00 }, _T("SwRst"));
				{
					pRegTable->SetBitDetail(_T("EnSw"), _T("Software reset"), _T(""), 0xEE);	//write 0xEE to reset
				}

				pRegTable->RegInfo[0xFC] = CRegInfo({ 0x15 }, _T("IDPod"));
				pRegTable->RegInfo[0xFD] = CRegInfo({ 0x00 }, _T("IDRev"));

				pRegTable->SetRegAddr(0xFE);
				pRegTable->SetRegInfo({ 0x80 }, _T("IntFlag"));
				{
					pRegTable->SetBitDetail(_T("PorInt"), 7, _T("POR INT"), 1);
					pRegTable->SetBitDetail(_T("IrInt"), 2, _T("IR INT"));
					pRegTable->SetBitDetail(_T("PsInt"), 1, _T("PS INT"));
					pRegTable->SetBitDetail(_T("AlsInt"), 0, _T("ALS INT"));
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
					pRegTable->SetBitDetail(_T("AlsErr"), 0, _T("ALS Error Flag"));
				}

				pRegTable->SetRegAddr(0x00);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("PsCh"), 2);
				{
					pRegTable->SetBitDetail2(_T("PsCh"), _T("PsCh"));
				}

				pRegTable->SetRegAddr(0x02);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("IrCh"), 2);
				{
					pRegTable->SetBitDetail2(_T("IrCh"), _T("IrCh"));
				}

				pRegTable->SetRegAddr(0x04);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("AlsCh0"), 2);
				{
					pRegTable->SetBitDetail2(_T("AlsCh0"), _T("AlsCh0"));
				}

				pRegTable->SetRegAddr(0x06);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("AlsCh1"), 2);
				{
					pRegTable->SetBitDetail2(_T("AlsCh1"), _T("AlsCh1"));
				}

				pRegTable->SetRegAddr(0x0C);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("DbgCh"), 2);
				{
					pRegTable->SetBitDetail2(_T("DbgCh"), _T("DbgCh"));
				}

				pRegTable->SetRegAddr(0x0E);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("TmpCh"), 2);
				{
					pRegTable->SetBitDetail2(_T("TmpCh"), _T("TmpCh"));
				}

				pRegTable->SetRegAddr(0x4F);
				pRegTable->SetRegInfo({ 0x00 }, _T("NapTime"));
				{
					pRegTable->SetBitDetail(_T("NapTime"), _T("Inserts Dummy Time"));
				}

				pRegTable->SetRegAddr(0x50);
				pRegTable->SetRegInfo({ 0x00 }, _T("AlsCtrl"));
				{
					pRegTable->SetBitDetail(_T("AlsCh1On"), 5, _T("Enable ALS CH1"));
					pRegTable->SetBitDetail(_T("AlsRand"), 4, _T("Insert 1 random bit"));
				}

				pRegTable->SetRegAddr(0x51);
				pRegTable->SetRegInfo({ 0x4F }, _T("AlsIntWdth"));
				{
					pRegTable->SetBitDetail(_T("AlsIntWdth"), _T("ALS Integration Width"), 0x7F, 0, BOTH_RW, { 0x00, 0x7F }, 0x4F);
				}

				pRegTable->SetRegAddr(0x52);
				pRegTable->SetRegInfo({ 0x00 }, _T("AlsIntTime"));
				{
					pRegTable->SetBitDetail(_T("AlsIntTime"), _T("ALS Integration Time"), 0x3F, 0, BOTH_RW, { 0x00, 0x20 });
				}

				pRegTable->SetRegAddr(0x53);
				pRegTable->SetRegInfo({ 0x00 }, _T("AlsPrePuc"));
				{
					pRegTable->SetBitDetail(_T("AlsPrePuc"), _T("ALS Pre-Heat Pulse Count"), 0x0F, 0, BOTH_RW, { 0x00, 0x0F });
				}

				pRegTable->SetRegAddr(0x54);
				pRegTable->SetRegInfo({ 0x40 }, _T("AlsDrvCtrl"));
				{
					pRegTable->SetBitDetail(_T("AlsDrvForce"), _T("forces the ALS driving waveform"), 0xC0, 6, BOTH_RW, { 0, 0x03 }, 0x01);
					pRegTable->SetBitDetail(_T("AlsDrvTurbo"), 5, _T("Control pin ¡§led_turbo¡¨ at ALS function"));
					pRegTable->SetBitDetail(_T("AlsDrvLed"), 4, _T("Maximun driving current"));
					pRegTable->SetBitDetail(_T("AlsDrv"), _T("Configure the dirving current"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x00);
				}

				pRegTable->SetRegAddr(0x58);
				pRegTable->SetRegInfo({ 0x68 }, _T("ALS Dark Trim"));
				{
					pRegTable->SetBitDetail(_T("DachCnst"), _T("DACH formula constant of AlsCh0-1"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x06);
					pRegTable->SetBitDetail(_T("DachFlor"), _T("DACH formula shifter of AlsCh0-1"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x08);
				}

				pRegTable->SetRegAddr(0x5B);
				pRegTable->SetRegInfo({ 0x01 }, _T("AlsAlgoCtrl"));
				{
					pRegTable->SetBitDetail(_T("AlsIntSrc"), 4, _T("ALS INT Source"));
					pRegTable->SetBitDetail(_T("AlsPers"), _T("PS Persistence"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x01);
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

				pRegTable->SetRegAddr(0x60);
				pRegTable->SetRegInfo({ 0x08 }, _T("PsCtrl"));
				{
					pRegTable->SetBitDetail(_T("PsMean"), _T("PS Mean"), 0xC0, 6, BOTH_RW, { 0, 0x03 }, 0x00);
					pRegTable->SetBitDetail(_T("PsAdcBit"), _T("PS ADC Bit"), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x00);
					pRegTable->SetBitDetail(_T("PsGain"), _T("PS Gain"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x08);
				}

				pRegTable->SetRegAddr(0x61);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsIntPuw"));
				{
					pRegTable->SetBitDetail(_T("PsIntPuw"), _T("PS Integration Pulse Width"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
				}

				pRegTable->SetRegAddr(0x62);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsIntPuc"));
				{
					pRegTable->SetBitDetail(_T("PsIntPuc"), _T("PS Integration Pulse Count"), 0x3F, 0, BOTH_RW, { 0, 63 });
				}

				pRegTable->SetRegAddr(0x63);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsPrePuc"));
				{
					pRegTable->SetBitDetail(_T("PsPrePuc"), _T("PS Pre_Heat Pulse Count"), 0x0F, 0, BOTH_RW, { 0, 15 });
				}

				pRegTable->SetRegAddr(0x64);
				pRegTable->SetRegInfo({ 0x01 }, _T("PsDrvCtrl"));
				{
					pRegTable->SetBitDetail(_T("PsDrvForce"), _T("Fources PS driving waveform"), 0xC0, 6, BOTH_RW, { 0, 3 });
					pRegTable->SetBitDetail(_T("PsDrvTurbo"), 5, _T("Control pin ¡§led_turbo¡¨ at PS function"));
					pRegTable->SetBitDetail(_T("PsDrvLed"), 4, _T("Configures the maximum driving current"));
					pRegTable->SetBitDetail(_T("PsDrv"), _T("PS driving current"), 0x0F, 0, BOTH_RW, { 0, 15 }, 0x01);
				}

				pRegTable->SetRegAddr(0x65);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsCtCtrl"));
				{
					pRegTable->SetBitDetail(_T("PsCtGain"), _T("PS CTDAC Gain"), 0xC0, 6, BOTH_RW, { 0, 2 });
					pRegTable->SetBitDetail(_T("PsCtDac"), _T("PS CTDAC Step"), 0x1F, 0, BOTH_RW, { 0, 31 });
				}

				pRegTable->SetRegAddr(0x66);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsIambCtrl"));
				{
					pRegTable->SetBitDetail(_T("PsIambOn"), 7, _T("Enable PS Ambient Dac"));
					pRegTable->SetBitDetail(_T("PsIambDac"), _T("PS Iamb Dac"), 0x3F, 0, BOTH_RW, { 0, 0x3F });
				}

				pRegTable->SetRegAddr(0x67);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsIctCtrl"));
				{
					pRegTable->SetBitDetail(_T("PsIctOn"), 7, _T("Enable PS ICT"));
					pRegTable->SetBitDetail(_T("PsIctDac"), _T("PS ICT DAC"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
				}

				pRegTable->SetRegAddr(0x68);
				pRegTable->SetRegInfo({ 0x83 }, _T("PS Dark Trim"));
				{
					pRegTable->SetBitDetail(_T("DpchCnst"), _T("DACH formula constant of PsCh"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x08);
					pRegTable->SetBitDetail(_T("DpchFlor"), _T("DACH formula shifter of PsCh"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x03);
				}

				pRegTable->SetRegAddr(0x69);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("PsCalb"), 2);
				{
					pRegTable->SetBitDetail2(_T("PsCalb"), { 0x00, 0x00 });
				}

				pRegTable->SetRegAddr(0x6B);
				pRegTable->SetRegInfo({ 0x11 }, _T("PsAlgoCtrl"));
				{
					pRegTable->SetBitDetail(_T("PsNapAlgo"), 5, _T("PS Nap Algo"));
					pRegTable->SetBitDetail(_T("PsIntAlgo"), 4, _T("PS INT Algo"), 1);
					pRegTable->SetBitDetail(_T("PsPers"), _T("PS Persistence"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x01);
				}

				pRegTable->SetRegAddr(0x6C);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("PsThLow"), 2);
				{
					pRegTable->SetBitDetail2(_T("PsThLow"), { 0x00, 0x00 });
				}

				pRegTable->SetRegAddr(0x6E);
				pRegTable->SetRegInfo({ 0xFF, 0xFF }, _T("PsThHigh"), 2);
				{
					pRegTable->SetBitDetail2(_T("PsThHigh"), { 0xFF, 0xFF });
				}


				pRegTable->SetRegAddr(0x70);
				pRegTable->SetRegInfo({ 0x08 }, _T("IrCtrl"));
				{
					pRegTable->SetBitDetail(_T("IrMean"), _T("IR Mean Time"), 0xC0, 6, BOTH_RW, { 0, 3 });
					pRegTable->SetBitDetail(_T("IrAdcBit"), _T("IR ADC Bit"), 0x30, 4, BOTH_RW, { 0, 3 });
					pRegTable->SetBitDetail(_T("IrGain"), _T("IR Gain"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x08);
				}

				pRegTable->SetRegAddr(0x71);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrIntPuw"));
				{
					pRegTable->SetBitDetail(_T("IrIntPuw"), _T("IR Integration Pulse Width"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
				}

				pRegTable->SetRegAddr(0x72);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrIntPuc"));
				{
					pRegTable->SetBitDetail(_T("IrIntPuc"), _T("IR Integration Pulse Count"), 0x3F, 0, BOTH_RW, { 0, 63 });
				}

				pRegTable->SetRegAddr(0x73);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrPrePuc"));
				{
					pRegTable->SetBitDetail(_T("IrPrePuc"), _T("IR Pre_Heat Pulse Count"), 0x0F, 0, BOTH_RW, { 0, 15 });
				}

				pRegTable->SetRegAddr(0x74);
				pRegTable->SetRegInfo({ 0x01 }, _T("IrDrvCtrl"));
				{
					pRegTable->SetBitDetail(_T("IrDrvForce"), _T("Fources IR driving waveform"), 0xC0, 6, BOTH_RW, { 0, 3 });
					pRegTable->SetBitDetail(_T("IrDrvTurbo"), 5, _T("Control pin ¡§led_turbo¡¨ at IR function"));
					pRegTable->SetBitDetail(_T("IrDrvLed"), 4, _T("Configures the maximum driving current"));
					pRegTable->SetBitDetail(_T("IrDrv"), _T("IR driving current"), 0x0F, 0, BOTH_RW, { 0, 15 }, 0x01);
				}

				pRegTable->SetRegAddr(0x75);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrCtCtrl"));
				{
					pRegTable->SetBitDetail(_T("IrCtGain"), _T("IR CTDAC Gain"), 0xC0, 6, BOTH_RW, { 0, 2 });
					pRegTable->SetBitDetail(_T("IrCtDac"), _T("IR CTDAC Step"), 0x1F, 0, BOTH_RW, { 0, 31 });
				}

				pRegTable->SetRegAddr(0x76);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrIambCtrl"));
				{
					pRegTable->SetBitDetail(_T("IrIambOn"), 7, _T("Enable IR Ambient Dac"));
					pRegTable->SetBitDetail(_T("IrIambDac"), _T("IR Iamb Dac"), 0x3F, 0, BOTH_RW, { 0, 0x3F });
				}

				pRegTable->SetRegAddr(0x77);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrIctCtrl"));
				{
					pRegTable->SetBitDetail(_T("IrIctOn"), 7, _T("Enable IR ICT"));
					pRegTable->SetBitDetail(_T("IrIctDac"), _T("IR ICT DAC"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
				}

				pRegTable->SetRegAddr(0x78);
				pRegTable->SetRegInfo({ 0x93 }, _T("IR Dark Trim"));
				{
					pRegTable->SetBitDetail(_T("DichCnst"), _T("DICH formula constant of IrCh"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x09);
					pRegTable->SetBitDetail(_T("DichFlor"), _T("DICH formula shifter of IrCh"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x03);
				}

				//RD Mode
				{
					//RD Mode SoftWare
					pRegTable->SetRegAddr(0x10);
					pRegTable->SetRegInfo({ 0x00 }, _T("Fuse0"));
					{
						pRegTable->SetBitDetail(_T("Fuse0"), _T("Fuse0"), 0xFF, 0, ONLY_R);
					}
					pRegTable->SetRegAddr(0x11);
					pRegTable->SetRegInfo({ 0x00 }, _T("Fuse1"));
					{
						pRegTable->SetBitDetail(_T("Fuse1"), _T("Fuse1"), 0xFF, 0, ONLY_R);
					}
					pRegTable->SetRegAddr(0x12);
					pRegTable->SetRegInfo({ 0x00 }, _T("Fuse2"));
					{
						pRegTable->SetBitDetail(_T("Fuse2"), _T("Fuse2"), 0xFF, 0, ONLY_R);
					}
					pRegTable->SetRegAddr(0x13);
					pRegTable->SetRegInfo({ 0x00 }, _T("Fuse3"));
					{
						pRegTable->SetBitDetail(_T("Fuse3"), _T("Fuse3"), 0xFF, 0, ONLY_R);
					}
					pRegTable->SetRegAddr(0x14);
					pRegTable->SetRegInfo({ 0x00 }, _T("Fuse4"));
					{
						pRegTable->SetBitDetail(_T("Fuse4"), _T("Fuse4"), 0xFF, 0, ONLY_R);
					}
					pRegTable->SetRegAddr(0x15);
					pRegTable->SetRegInfo({ 0x00 }, _T("Fuse5"));
					{
						pRegTable->SetBitDetail(_T("Fus5"), _T("Fuse5"), 0xFF, 0, ONLY_R);
					}
					pRegTable->SetRegAddr(0x16);
					pRegTable->SetRegInfo({ 0x00 }, _T("Fuse6"));
					{
						pRegTable->SetBitDetail(_T("Fuse6"), _T("Fuse6"), 0xFF, 0, ONLY_R);
					}
					pRegTable->SetRegAddr(0x17);
					pRegTable->SetRegInfo({ 0x00 }, _T("Fuse7"));
					{
						pRegTable->SetBitDetail(_T("Fuse7"), _T("Fuse7"), 0xFF, 0, ONLY_R);
					}

					pRegTable->SetRegAddr(0x18);
					pRegTable->SetRegInfo({ 0x00, 0x00}, _T("Leak 25"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak25"), { 0x00, 0x00 }, _T("Leak25"));
					}
					pRegTable->SetRegAddr(0x1A);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak 35"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak35"), { 0x00, 0x00 }, _T("Leak35"));
					}
					pRegTable->SetRegAddr(0x1C);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak 45"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak45"), { 0x00, 0x00 }, _T("Leak45"));
					}
					pRegTable->SetRegAddr(0x1E);
					pRegTable->SetRegInfo({ 0x05, 0x00 }, _T("Leak 55"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak55"), { 0x05, 0x00 }, _T("Leak55"));
					}
					pRegTable->SetRegAddr(0x20);
					pRegTable->SetRegInfo({ 0x0B, 0x00 }, _T("Leak 65"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak65"), { 0x0B, 0x00 }, _T("Leak65"));
					}
					pRegTable->SetRegAddr(0x22);
					pRegTable->SetRegInfo({ 0x14, 0x00 }, _T("Leak 75"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak75"), { 0x14, 0x00 }, _T("Leak75"));
					}
					pRegTable->SetRegAddr(0x24);
					pRegTable->SetRegInfo({ 0x23, 0x00 }, _T("Leak 85"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak85"), { 0x23, 0x00 }, _T("Leak85"));
					}
					pRegTable->SetRegAddr(0x26);
					pRegTable->SetRegInfo({ 0x38, 0x00 }, _T("Leak 95"), 2);
					{
						pRegTable->SetBitDetail2(_T("Leak95"), { 0x38, 0x00 }, _T("Leak95"));
					}

					pRegTable->SetRegAddr(0x28);
					pRegTable->SetRegInfo({ 0x11 }, _T("PS L2F Unit"));
					{
						pRegTable->SetBitDetail(_T("PsUnit"), _T("Ps ADC Time Unit(10 uS)"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x11);
					}

					pRegTable->SetRegAddr(0x29);
					pRegTable->SetRegInfo({ 0x00 }, _T("PS Tcof"));
					{
						pRegTable->SetBitDetail(_T("PsLcf"), _T("Lcof = PsLcf/128"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					pRegTable->SetRegAddr(0x2A);
					pRegTable->SetRegInfo({ 0x40 }, _T("PS Tcof Low"));
					{
						pRegTable->SetBitDetail(_T("PsTcfLow"), _T("Tcof = PsTcfLow/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x40);
					}

					pRegTable->SetRegAddr(0x2B);
					pRegTable->SetRegInfo({ 0x40 }, _T("PS Tcof High"));
					{
						pRegTable->SetBitDetail(_T("PsTcfHigh"), _T("Tcof = PsTcfHigh/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x40);
					}

					pRegTable->SetRegAddr(0x2C);
					pRegTable->SetRegInfo({ 0x11 }, _T("IR L2F Unit"));
					{
						pRegTable->SetBitDetail(_T("IrUnit"), _T("Ir ADC Time Unit(10 uS)"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x11);
					}

					pRegTable->SetRegAddr(0x2D);
					pRegTable->SetRegInfo({ 0x00 }, _T("IR Tcof"));
					{
						pRegTable->SetBitDetail(_T("IrLcf"), _T("Lcof = IrLcf/128"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					pRegTable->SetRegAddr(0x2E);
					pRegTable->SetRegInfo({ 0x40 }, _T("IR Tcof Low"));
					{
						pRegTable->SetBitDetail(_T("IrTcfLow"), _T("Tcof = IrTcfLow/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x40);
					}

					pRegTable->SetRegAddr(0x2F);
					pRegTable->SetRegInfo({ 0x40 }, _T("IR Tcof High"));
					{
						pRegTable->SetBitDetail(_T("IrTcfHigh"), _T("Tcof = IrTcfHigh/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x40);
					}

					pRegTable->SetRegAddr(0x30);
					pRegTable->SetRegInfo({ 0x7D }, _T("ALS L2F Unit 0"));
					{
						pRegTable->SetBitDetail(_T("AlsUnit0"), _T("Als ADC Time Unit(10 uS)"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x7D);
					}

					pRegTable->SetRegAddr(0x31);
					pRegTable->SetRegInfo({ 0x80 }, _T("ALS Tcof 0"));
					{
						pRegTable->SetBitDetail(_T("AlsLcf0"), _T("Lcof = AlsLcf/128"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x80);
					}

					pRegTable->SetRegAddr(0x32);
					pRegTable->SetRegInfo({ 0x08 }, _T("ALS Tcof Low 0"));
					{
						pRegTable->SetBitDetail(_T("AlsTcfLow0"), _T("Tcof = AlsTcfLow/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x08);
					}

					pRegTable->SetRegAddr(0x33);
					pRegTable->SetRegInfo({ 0x10 }, _T("ALS Tcof High 0"));
					{
						pRegTable->SetBitDetail(_T("AlsTcfHigh0"), _T("Tcof = AlsTcfHigh/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x10);
					}

					pRegTable->SetRegAddr(0x34);
					pRegTable->SetRegInfo({ 0x32 }, _T("ALS L2F Unit 1"));
					{
						pRegTable->SetBitDetail(_T("AlsUnit1"), _T("Als ADC Time Unit(10 uS)"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x32);
					}

					pRegTable->SetRegAddr(0x35);
					pRegTable->SetRegInfo({ 0x33 }, _T("ALS Tcof 1"));
					{
						pRegTable->SetBitDetail(_T("AlsLcf1"), _T("Lcof = AlsLcf/128"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x33);
					}

					pRegTable->SetRegAddr(0x36);
					pRegTable->SetRegInfo({ 0x08 }, _T("ALS Tcof Low 1"));
					{
						pRegTable->SetBitDetail(_T("AlsTcfLow1"), _T("Tcof = AlsTcfLow/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x08);
					}

					pRegTable->SetRegAddr(0x37);
					pRegTable->SetRegInfo({ 0x10 }, _T("ALS Tcof High 1"));
					{
						pRegTable->SetBitDetail(_T("AlsTcfHigh1"), _T("Tcof = AlsTcfHigh/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x10);
					}

					pRegTable->SetRegAddr(0x40);
					pRegTable->SetRegInfo({ 0x7D }, _T("Analog ALS"));
					{
						pRegTable->SetBitDetail(_T("AlsV2i"), _T("Control pin \"pxy_v2i_sel\" at ALS ADC"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x07);
						pRegTable->SetBitDetail(_T("AlsCap"), _T("Control pin \"cap_sel\" at ALS ADC"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x0D);
					}

					pRegTable->SetRegAddr(0x41);
					pRegTable->SetRegInfo({ 0xFD }, _T("Analog PS"));
					{
						pRegTable->SetBitDetail(_T("PsV2i"), _T("Control pin \"pxy_v2i_sel\" at PS ADC"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x0F);
						pRegTable->SetBitDetail(_T("PsCap"), _T("Control pin \"cap_sel\" at PS ADC"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x0D);
					}

					pRegTable->SetRegAddr(0x42);
					pRegTable->SetRegInfo({ 0xFD }, _T("Analog IR"));
					{
						pRegTable->SetBitDetail(_T("IrV2i"), _T("Control pin \"pxy_v2i_sel\" at IR ADC"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x0F);
						pRegTable->SetBitDetail(_T("IrCap"), _T("Control pin \"cap_sel\" at IR ADC"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x0D);
					}

					pRegTable->SetRegAddr(0x43);
					pRegTable->SetRegInfo({ 0x7D }, _T("Analog TMP"));
					{
						pRegTable->SetBitDetail(_T("TmpV2i"), _T("Control pin \"pxy_v2i_sel\" at TMP ADC"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x07);
						pRegTable->SetBitDetail(_T("TmpCap"), _T("Control pin \"cap_sel\" at TMP ADC"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x0D);
					}

					pRegTable->SetRegAddr(0x44);
					pRegTable->SetRegInfo({ 0x00 }, _T("Analog A"));
					{
						pRegTable->SetBitDetail(_T("ibtest_sel"), 6, _T("Control pin \"ibtest_sel\""));
						pRegTable->SetBitDetail(_T("test_sel"), 5, _T("Control pin \"test_sel\""));
						pRegTable->SetBitDetail(_T("temp_mux"), 4, _T("Control pin \"temp_mux\""));
						pRegTable->SetBitDetail(_T("ana_test_en"), 3, _T("Control pin \"ana_test_en\""));
						pRegTable->SetBitDetail(_T("ana_test"), _T("Control pin \"ana_test\""), 0x07, 0, BOTH_RW, { 0, 0x07 });
					}

					pRegTable->SetRegAddr(0x45);
					pRegTable->SetRegInfo({ 0x9E }, _T("Analog B"));
					{
						pRegTable->SetBitDetail(_T("clkm_vbs"), _T("Control pin \"clkm_vbs\""), 0xC0, 6, BOTH_RW, { 0, 0x03 }, 0x02);
						pRegTable->SetBitDetail(_T("vref_op_sel"), _T("Control pin \"vref_op_sel\""), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x01);
						pRegTable->SetBitDetail(_T("vtoph_set"), _T("Control pin \"vtoph_set\""), 0x0C, 2, BOTH_RW, { 0, 0x03 }, 0x03);
						pRegTable->SetBitDetail(_T("vdiode_sel"), _T("Control pin \"vdiode_sel\""), 0x03, 0, BOTH_RW, { 0, 0x03 }, 0x02);
					}

					pRegTable->SetRegAddr(0x46);
					pRegTable->SetRegInfo({ 0x17 }, _T("Analog C"));
					{
						pRegTable->SetBitDetail(_T("losc_trim"), _T("Control pin \"losc_trim\""), 0x1F, 0, BOTH_RW, { 0, 0x1F }, 0x17);
					}

					pRegTable->SetRegAddr(0x47);
					pRegTable->SetRegInfo({ 0x00 }, _T("Analog D"));
					{
						pRegTable->SetBitDetail(_T("ctrl0ana"), _T("Control pin \"ctrl0ana\""));
					}

					pRegTable->SetRegAddr(0x48);
					pRegTable->SetRegInfo({ 0x00 }, _T("Analog E"));
					{
						pRegTable->SetBitDetail(_T("ctrl1ana"), _T("Control pin \"ctrl1ana\""));
					}

					pRegTable->SetRegAddr(0x49);
					pRegTable->SetRegInfo({ 0x5A }, _T("Digital Slot"));
					{
						pRegTable->SetBitDetail(_T("CpchCnst"), _T("CPCH formula constant of PsCh"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x05);
						pRegTable->SetBitDetail(_T("SlotTmp"), _T("The Temperature time slot"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x0A);
					}

					pRegTable->SetRegAddr(0x4A);
					pRegTable->SetRegInfo({ 0xC0 }, _T("Digital A"));
					{
						pRegTable->SetBitDetail(_T("VarDuty"), 7, _T("Var Duty"), 0x01);
						pRegTable->SetBitDetail(_T("Pxsh"), 6, _T("Enable \"pxsh\""), 0x01);
						pRegTable->SetBitDetail(_T("ConvMin"), 3, _T("Conversion Min Select"));
						pRegTable->SetBitDetail(_T("LeakOut"), 2, _T("DbgCh = Leak Enable"));
						pRegTable->SetBitDetail(_T("TgenDouble"), 1, _T("Tgen Unit"));
						pRegTable->SetBitDetail(_T("Force"), 0, _T("Select Input data"));
					}

					pRegTable->SetRegAddr(0x4B);
					pRegTable->SetRegInfo({ 0x67 }, _T("Digital B"));
					{
						pRegTable->SetBitDetail(_T("IrBias"), 6, _T("Enable \"pdvb0d3v_en\" at IR"), 0x01);
						pRegTable->SetBitDetail(_T("PsBias"), 5, _T("Enable \"pdvb0d3v_en\" at PS"), 0x01);
						pRegTable->SetBitDetail(_T("AlsBias"), 4, _T("Enable \"pdvb0d3v_en\" at ALS"));
						pRegTable->SetBitDetail(_T("IrDark"), 2, _T("Enable \"ir_dark_comp\" at IR"), 0x01);
						pRegTable->SetBitDetail(_T("PsDark"), 1, _T("Enable \"ps_dark_comp\" at PS"), 0x01);
						pRegTable->SetBitDetail(_T("AlsDark"), 0, _T("Enable \"als_dark_comp\" at ALS"), 0x01);
					}

					pRegTable->SetRegAddr(0x4C);
					pRegTable->SetRegInfo({ 0x00 }, _T("Digital C"));
					{
						pRegTable->SetBitDetail(_T("AlsDc"), _T("The dark trim level of AlsCh0-3"));
					}

					pRegTable->SetRegAddr(0x4D);
					pRegTable->SetRegInfo({ 0x00 }, _T("Digital D"));
					{
						pRegTable->SetBitDetail(_T("PsDc"), _T("The dark trim level of PsCh"));
					}

					pRegTable->SetRegAddr(0x4E);
					pRegTable->SetRegInfo({ 0x00 }, _T("Digital E"));
					{
						pRegTable->SetBitDetail(_T("IrDc"), _T("The dark trim level of IrCh"));
					}

					pRegTable->SetRegAddr(0x79);
					pRegTable->SetRegInfo({ 0xD6 }, _T("Temperature target"));
					{
						pRegTable->SetBitDetail(_T("TTAR"), _T("TmpCh Unit= TTAR x 10us"), { 0xFF }, 0, BOTH_RW, { 0x00, 0xFF }, 0xD6);
					}

					pRegTable->SetRegAddr(0x7A);
					pRegTable->SetRegInfo({ 0xA9, 0x04 }, _T("Leakage target"), 2);
					{
						pRegTable->SetBitDetail2(_T("LTAR"), { 0xA9, 0x04 }, _T("Define TmpCh at 95C in Leak matrix"));
						pRegTable->BitDetail[_T("LTAR")].BitRW = BOTH_RW;
					}

					pRegTable->SetRegAddr(0x7C);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Force Data"), 2);
					{
						pRegTable->SetBitDetail2(_T("ForceData"), _T("Force Data"));
						pRegTable->BitDetail[_T("ForceData")].BitRW = BOTH_RW;
					}

					pRegTable->SetRegAddr(0x7E);
					pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Force Temperature"), 2);
					{
						pRegTable->SetBitDetail2(_T("ForceTmp"), _T("Force Temperature"));
						pRegTable->BitDetail[_T("ForceTmp")].BitRW = BOTH_RW;
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
					pRegTable->SetRegInfo({ 0x83 , 0x73 }, _T("RomCheck"), 0);
					{
						pRegTable->SetBitDetail2(_T("BROM"), _T("Rom Bist"));
					}
#endif
					pRegTable->SetRegAddr(0xD6);
					pRegTable->SetRegInfo({ 0x01 }, _T("AnaEnCtrl"));
					{
						pRegTable->SetBitDetail(_T("losc_enb"), 5, _T("Control losc_enb pin when Device OFF"));
						pRegTable->SetBitDetail(_T("hosc_en"), 4, _T("Control hosc_en pin when Device OFF"));
						pRegTable->SetBitDetail(_T("en_ps"), 1, _T("Control en_ps pin when Device OFF"));
						pRegTable->SetBitDetail(_T("enb_bg"), 0, _T("Control enb_bg pin when Device OFF"), 0x01);
					}

					pRegTable->SetRegAddr(0xEF);
					pRegTable->SetRegInfo({ 0x05 }, _T("I2CWdog"));
					{
						pRegTable->SetBitDetail(_T("I2cWdog"), _T("I2C Watch Dog (6.4 ms)"), 0xFF, 0, ONLY_R, { 0x00, 0xff }, 0x05);
					}

					pRegTable->SetRegAddr(0xFB);
					pRegTable->SetRegInfo({ 0x00 }, _T("LOSC Channel"));
					{
						pRegTable->SetBitDetail(_T("LoscCh"), _T("Low OSC Period= LoscCh x 800us"), { 0xFF }, 0, ONLY_R, { 0x00, 0xFF }, 0x00);
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
			ConversionTime = 100;
			/*
			if (Reg0x00 & pBitDetailMap->at(_T("EnPs")).BitMask.at(0))
			{
				//T_PS ms
				ConversionTime += (pow(2, pRegTable->GetBitValue(_T("PsMean")))
					* (30 + 5 * pRegTable->GetBitValue(_T("PsAdcBit")) + (20 * pRegTable->GetBitValue(_T("PsNapTime")))));

				//T_LED us
				ConversionTime += ((pow(2, pRegTable->GetBitValue(_T("PsMean")))
					* (6 + (pRegTable->GetBitValue(_T("PsIntPuw")) == 0 ? 1 : pRegTable->GetBitValue(_T("PsIntPuw"))))
					* (pRegTable->GetBitValue(_T("PsIntPuc")) == 0 ? 1 : pRegTable->GetBitValue(_T("PsIntPuc"))
						+ pRegTable->GetBitValue(_T("PsPrePuc")))) / 1000);
			}

			if (Reg0x00 & pBitDetailMap->at(_T("EnIr")).BitMask.at(0))
			{
				//T_IR ms
				ConversionTime += (pow(2, pRegTable->GetBitValue(_T("IrMean")))
					* (30 + 5 * pRegTable->GetBitValue(_T("IrAdcTime")) + (20 * pRegTable->GetBitValue(_T("IrNapTime")))));
			}
			*/
			break;
		}

		return (uint32_t)(ConversionTime * 1000);
	}
};