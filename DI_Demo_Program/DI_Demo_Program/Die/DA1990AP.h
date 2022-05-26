#pragma once
#include "Define.h"

class CDA1990AP : public CDieInfo {
public:
	CDA1990AP() {}
	void Init(uint16_t version)
	{
		DieName = _T("DA1990AP");
		switch (version)
		{
		case 10000:
			DieDetail.insert(make_pair(10000, CDieDetail()));
			{
				pDieDetail = &DieDetail.at(10000);
				pDieDetail->I2CFreqKHz = 10;

				pRegTable = &pDieDetail->RegisterTable;

				pRegTable->DeviceID = 0x1C;

				pRegTable->SetRegAddr(0xF0);
				pRegTable->SetRegInfo({ 0x00 }, _T("DevCtrl"));
				{
					pRegTable->SetBitDetail(_T("NewPsEn"), 4, _T("New PS Enable"));
					pRegTable->SetBitDetail(_T("IrEn"), 2, _T("IR Enable"));
					pRegTable->SetBitDetail(_T("PsEn"), 1, _T("PS Enable"));
					pRegTable->SetBitDetail(_T("AlsEn"), 0, _T("ALS Enable"));
				}

				pRegTable->SetRegAddr(0xF1);
				pRegTable->SetRegInfo({ 0x03 }, _T("IntCtrl"));
				{
					pRegTable->SetBitDetail(_T("DataIntEn"), 4, _T("Data Int Enable"));
					pRegTable->SetBitDetail(_T("IrIntEn"), 2, _T("IR Int Enable"));
					pRegTable->SetBitDetail(_T("PsIntEn"), 1, _T("PS Int Enable"), 0x01);
					pRegTable->SetBitDetail(_T("AlsIntEn"), 0, _T("ALS Int Enable"), 0x01);
				}

				pRegTable->SetRegAddr(0xF2);
				pRegTable->SetRegInfo({ 0x00 }, _T("HaltCtrl"));
				{
					pRegTable->SetBitDetail(_T("ReadClear"), 7, _T("Interrupt clear method"));
					pRegTable->SetBitDetail(_T("DataHalt"), 4, _T("Data INT Halt"));
					pRegTable->SetBitDetail(_T("IrHalt"), 2, _T("IR INT Halt"));
					pRegTable->SetBitDetail(_T("PsHalt"), 1, _T("PS INT Halt"));
					pRegTable->SetBitDetail(_T("AlsHalt"), 0, _T("ALS INT Halt"));
				}

				pRegTable->SetRegAddr(0xF3);
				pRegTable->SetRegInfo({ 0x00 }, _T("SysCtrl"));
				{
					pRegTable->SetBitDetail(_T("FallPorEn"), 7, _T("Enable Falling POR"));
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
					pRegTable->SetBitDetail(_T("IoFunc"), _T("Change INT pin output"), 0x03, 0, BOTH_RW, { 0, 0x03 }, 0x00);
				}

				pRegTable->SetRegAddr(0xFB);
				pRegTable->SetRegInfo({ 0x00 }, _T("LoscData"));
				{
					pRegTable->SetBitDetail(_T("LoscData"), _T("LOSC Period= LoscData x 800ns"), 0xFF, 0, ONLY_R);
				}

				pRegTable->SetRegAddr(0xFC);
				pRegTable->SetRegInfo({ 0x14 }, _T("IDPod"));
				{
					pRegTable->SetBitDetail(_T("IDPod"), _T("IDPod"), 0xFF, 0, ONLY_R);
				}

				pRegTable->SetRegAddr(0xFD);
				pRegTable->SetRegInfo({ 0x03 }, _T("IDRev"));
				{
					pRegTable->SetBitDetail(_T("IDRev"), _T("IDRev"), 0xFF, 0, ONLY_R);
				}

				pRegTable->SetRegAddr(0xFE);
				pRegTable->SetRegInfo({ 0x80 }, _T("IntFlag"));
				{
					pRegTable->SetBitDetail(_T("PorInt"), 7, _T("POR INT"), 1);
					pRegTable->SetBitDetail(_T("DataInt"), 4, _T("Data INT"));
					pRegTable->SetBitDetail(_T("IrInt"), 2, _T("IR INT"));
					pRegTable->SetBitDetail(_T("PsInt"), 1, _T("PS INT"));
					pRegTable->SetBitDetail(_T("AlsInt"), 0, _T("ALS INT"));
				}

				pRegTable->SetRegAddr(0xFF);
				pRegTable->SetRegInfo({ 0x80 }, _T("StatFlag"));
				{
					pRegTable->SetBitDetail(_T("Obj"), 7, _T("PS Object"), 1);
					pRegTable->SetBitDetail(_T("IrEnvErr"), 6, _T("IR ckt Error Flag when Drv Off"));
					pRegTable->SetBitDetail(_T("TmpErr"), 5, _T("TmpData Invalid Flag"));
					pRegTable->SetBitDetail(_T("PsDrvErr"), 4, _T("PS ckt Error Flag when Drv On"));
					pRegTable->SetBitDetail(_T("PsAmbErr"), 3, _T("PS ckt Error Flag when Drv Off"));
					pRegTable->SetBitDetail(_T("IrErr"), 2, _T("IrData Invalid Flag"));
					pRegTable->SetBitDetail(_T("PsErr"), 1, _T("PsData Invalid Flag"));
					pRegTable->SetBitDetail(_T("AlsErr"), 0, _T("AlsData0~1 Invalid Flag"));
				}

				pRegTable->SetRegAddr(0x00);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("PsData"), 2);
				{
					pRegTable->SetBitDetail2(_T("PsData"), _T("PsData"));
				}

				pRegTable->SetRegAddr(0x02);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("IrData"), 2);
				{
					pRegTable->SetBitDetail2(_T("IrData"), _T("IrData"));
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
				pRegTable->SetRegInfo({ 0x06 }, _T("AlsCtrl"));
				{
					pRegTable->SetBitDetail(_T("AlsRand"), 4, _T("Insert 1 bit random at AlsData0~1"), 0);
					pRegTable->SetBitDetail(_T("AlsGain1"), 2, _T("AlsData1 is x4"), 1);
					pRegTable->SetBitDetail(_T("AlsGain0"), _T("AlsData0 Gain"), 0x03, 0, BOTH_RW, { 0, 0x03 }, 0x02);
				}

				pRegTable->SetRegAddr(0x52);
				pRegTable->SetRegInfo({ 0x00 }, _T("AlsPuc"));
				{
					pRegTable->SetBitDetail(_T("AlsPuc"), _T("Als Conversion Time"), 0x1F, 0, BOTH_RW, { 0, 0x1F });
				}

				pRegTable->SetRegAddr(0x55);
				pRegTable->SetRegInfo({ 0x32 }, _T("AlsPuw0"));
				{
					pRegTable->SetBitDetail(_T("AlsPuw0"), _T("AlsData0 Conversion width"), 0x7F, 0, BOTH_RW, { 0, 0x7F }, 0x32);
				}

				pRegTable->SetRegAddr(0x56);
				pRegTable->SetRegInfo({ 0x0A }, _T("AlsPuw1"));
				{
					pRegTable->SetBitDetail(_T("AlsPuw1"), _T("AlsData1 Conversion width"), 0x7F, 0, BOTH_RW, { 0, 0x7F }, 0x0A);
				}

				pRegTable->SetRegAddr(0x5B);
				pRegTable->SetRegInfo({ 0x01 }, _T("AlsAlgoCtrl"));
				{
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

				pRegTable->SetRegAddr(0x60);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsCtrl"));
				{
					pRegTable->SetBitDetail(_T("PsMean"), _T("PS Mean"), 0xC0, 6, BOTH_RW, { 0, 0x03 }, 0x00);
					pRegTable->SetBitDetail(_T("PsBits"), _T("Define PsData bits"), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x00);
					pRegTable->SetBitDetail(_T("PsGain"), 0, _T("PsData is x2"), 0);
				}

				pRegTable->SetRegAddr(0x61);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsPuw"));
				{
					pRegTable->SetBitDetail(_T("PsPuw"), _T("PS Integration Pulse Width"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
				}

				pRegTable->SetRegAddr(0x62);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsPuc"));
				{
					pRegTable->SetBitDetail(_T("PsPuc"), _T("PS Integration Pulse Count"), 0x3F, 0, BOTH_RW, { 0, 0x3F });
				}

				pRegTable->SetRegAddr(0x63);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsPreCtrl"));
				{
					pRegTable->SetBitDetail(_T("PsPrePuc"), _T("PS Pre-Heat Pulse Count"), 0x0F, 0, BOTH_RW, { 0, 15 });
				}

				pRegTable->SetRegAddr(0x64);
				pRegTable->SetRegInfo({ 0x01 }, _T("PsDrvCtrl"));
				{
					pRegTable->SetBitDetail(_T("PsDrvDc"), _T("Driving DC"), 0xC0, 6, BOTH_RW, { 0, 3 });
					pRegTable->SetBitDetail(_T("PsDrvMax"), _T("Configures the Maximum Driving Current"), 0x30, 4, BOTH_RW, { 0, 3 });
					pRegTable->SetBitDetail(_T("PsDrv"), _T("PS Driving Current"), 0x0F, 0, BOTH_RW, { 0, 15 }, 0x01);
				}

				pRegTable->SetRegAddr(0x65);
				pRegTable->SetRegInfo({ 0x51 }, _T("PsDacCtrl"));
				{
					pRegTable->SetBitDetail(_T("PsCoasGain"), _T("PS Coarse Gain"), 0xF0, 4, BOTH_RW, { 0, 15 }, 0x05);
					pRegTable->SetBitDetail(_T("PsFineGain"), _T("PS Fine Gain"), 0x0F, 0, BOTH_RW, { 0, 15 }, 0x01);
				}

				pRegTable->SetRegAddr(0x66);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsCoasAmb"));
				{
					pRegTable->SetBitDetail(_T("PsCoasAmb"), _T("PS Coarse Ambient DAC"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
				}

				pRegTable->SetRegAddr(0x67);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsCoasCt"));
				{
					pRegTable->SetBitDetail(_T("PsCoasCt"), _T("PS Coarse Crosstalk DAC"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
				}

				pRegTable->SetRegAddr(0x68);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsFineCt"));
				{
					pRegTable->SetBitDetail(_T("PsFineCt"), _T("PS Fine Crosstalk DAC"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
				}

				pRegTable->SetRegAddr(0x69);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("PsCal"), 2);
				{
					pRegTable->SetBitDetail2(_T("PsCal"), { 0x00, 0x00 }, _T(""));
				}

				pRegTable->SetRegAddr(0x6B);
				pRegTable->SetRegInfo({ 0x11 }, _T("PsAlgoCtrl"));
				{
					pRegTable->SetBitDetail(_T("PsObjPolar"), 6, _T("Toggle polarity of Obj"));
					pRegTable->SetBitDetail(_T("PsWaitAlgo"), 5, _T("Define WaitTime and non-PS function"));
					pRegTable->SetBitDetail(_T("PsIntAlgo"), 4, _T("Define PsInt behavior."), 1);
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
				pRegTable->SetRegInfo({ 0x00 }, _T("IrCtrl"));
				{
					pRegTable->SetBitDetail(_T("IrMean"), _T("IR Mean"), 0xC0, 6, BOTH_RW, { 0, 0x03 }, 0x00);
					pRegTable->SetBitDetail(_T("IrBits"), _T("Define IrData bits"), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x00);
					pRegTable->SetBitDetail(_T("IrGain"), 0, _T("IrData is x2"), 0);
				}

				pRegTable->SetRegAddr(0x71);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrPuw"));
				{
					pRegTable->SetBitDetail(_T("IrPuw"), _T("IR Integration Pulse Width"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
				}

				pRegTable->SetRegAddr(0x72);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrPuc"));
				{
					pRegTable->SetBitDetail(_T("IrPuc"), _T("IR Integration Pulse Count"), 0x3F, 0, BOTH_RW, { 0, 0x3F });
				}

				pRegTable->SetRegAddr(0x73);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrPreCtrl"));
				{
					pRegTable->SetBitDetail(_T("IrPrePuc"), _T("IR Pre-Heat Pulse Count"), 0x0F, 0, BOTH_RW, { 0, 15 });
				}

				pRegTable->SetRegAddr(0x74);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrDrvCtrl"));
				{
					pRegTable->SetBitDetail(_T("IrDrvDc"), _T("Driving DC"), 0xC0, 6, BOTH_RW, { 0, 3 });
					pRegTable->SetBitDetail(_T("IrDrvMax"), _T("Configures the Maximum Driving Current"), 0x30, 4, BOTH_RW, { 0, 3 });
					pRegTable->SetBitDetail(_T("IrDrv"), _T("IR Driving Current"), 0x0F, 0, BOTH_RW, { 0, 15 }, 0x00);
				}

				pRegTable->SetRegAddr(0x75);
				pRegTable->SetRegInfo({ 0x51 }, _T("IrDacCtrl"));
				{
					pRegTable->SetBitDetail(_T("IrCoasGain"), _T("IR Coarse Gain"), 0xF0, 4, BOTH_RW, { 0, 15 }, 0x05);
					pRegTable->SetBitDetail(_T("IrFineGain"), _T("IR Fine Gain"), 0x0F, 0, BOTH_RW, { 0, 15 }, 0x01);
				}

				pRegTable->SetRegAddr(0x76);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrCoasAmb"));
				{
					pRegTable->SetBitDetail(_T("IrCoasAmb"), _T("IR Coarse Ambient DAC"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
				}

				pRegTable->SetRegAddr(0x77);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrCoasCt"));
				{
					pRegTable->SetBitDetail(_T("IrCoasCt"), _T("IR Coarse Crosstalk DAC"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
				}

				pRegTable->SetRegAddr(0x78);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrFineCt"));
				{
					pRegTable->SetBitDetail(_T("IrFineCt"), _T("IR Fine Crosstalk DAC"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
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

					pRegTable->SetRegAddr(0x22);
					pRegTable->SetRegInfo({ 0x00 }, _T("PsLcf"));
					{
						pRegTable->SetBitDetail(_T("PsLcf"), _T("PsData Lcf = PsLcf/64"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					pRegTable->SetRegAddr(0x23);
					pRegTable->SetRegInfo({ 0x00 }, _T("IrLcf"));
					{
						pRegTable->SetBitDetail(_T("IrLcf"), _T("IrData Lcf = IrLcf/64"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

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

					pRegTable->SetRegAddr(0x28);
					pRegTable->SetRegInfo({ 0x00 }, _T("PsTcfLow"));
					{
						pRegTable->SetBitDetail(_T("PsTcfLow"), _T("PsData Tcf = PsTcfLow/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					pRegTable->SetRegAddr(0x29);
					pRegTable->SetRegInfo({ 0x00 }, _T("PsTcfHigh"));
					{
						pRegTable->SetBitDetail(_T("PsTcfHigh"), _T("PsData Tcf = PsTcfHigh/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					pRegTable->SetRegAddr(0x2A);
					pRegTable->SetRegInfo({ 0x00 }, _T("IrTcfLow"));
					{
						pRegTable->SetBitDetail(_T("IrTcfLow"), _T("IrData Tcf = IrTcfLow/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					pRegTable->SetRegAddr(0x2B);
					pRegTable->SetRegInfo({ 0x00 }, _T("IrTcfHigh"));
					{
						pRegTable->SetBitDetail(_T("IrTcfHigh"), _T("IrData Tcf = IrTcfHigh/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

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
					pRegTable->SetRegInfo({ 0x29 }, _T("TTAR"));
					{
						pRegTable->SetBitDetail(_T("TTAR"), _T("TmpData Unit= TTAR x 10us"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x29);
					}

					pRegTable->SetRegAddr(0x3F);
					pRegTable->SetRegInfo({ 0x1B }, _T("PTAR"));
					{
						pRegTable->SetBitDetail(_T("PTAR"), _T("PsData Unit= PTAR x 10us at 9 bits"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x1B);
					}

					//pRegTable->SetRegAddr(0x40);
					//pRegTable->SetRegInfo({ 0x14 }, _T("ATAR"));
					//{
					//	pRegTable->SetBitDetail(_T("ATAR"), _T("AlsData0~2 Unit= ATAR x 50us"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x14);
					//}

					pRegTable->SetRegAddr(0x41);
					pRegTable->SetRegInfo({ 0x01 }, _T("TmpAdc"));	//TODO: check value
					{					
						pRegTable->SetBitDetail(_T("TmpCap"), 0, _T("Control pin \"pcap_sel\" at TMP ADC"), 1);
					}

					pRegTable->SetRegAddr(0x42);
					pRegTable->SetRegInfo({ 0xF1 }, _T("PxyAdc"));
					{
						pRegTable->SetBitDetail(_T("PsV2i"), _T("Control pin \"pxy_v2i_sel\" at PS/IR ADC"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x0F);
						pRegTable->SetBitDetail(_T("PxyCap"), 0, _T("Control pin \"pcap_sel\" at PS/IR ADC"), 1);
					}

					pRegTable->SetRegAddr(0x43);
					pRegTable->SetRegInfo({ 0x4B }, _T("AnalogA"));
					{
						pRegTable->SetBitDetail(_T("CoasDc"), 7, _T("Control pin \"coas_offset\" at PS/IR"));
						pRegTable->SetBitDetail(_T("TmpBias"), 6, _T("Control pin \"pdvb0d3v_en\" at TMP"), 1);
						pRegTable->SetBitDetail(_T("PxyBias"), 5, _T("Control pin \"pdvb0d3v_en\" at PS/IR"));
						pRegTable->SetBitDetail(_T("AlsBias"), 4, _T("Control pin \"pdvb0d3v_en\" at ALS"));
						pRegTable->SetBitDetail(_T("DfltEn"), 3, _T("Control pin \"dflten\" at all functions"), 1);
						pRegTable->SetBitDetail(_T("DcPath"), 2, _T("Control pin \"dcpath\" at all functions"));
						pRegTable->SetBitDetail(_T("PxyDark"), 1, _T("Control pin \"ir_dark\" at PS/IR"), 1);
						pRegTable->SetBitDetail(_T("AlsDark"), 0, _T("Control pin \"als_dark\" at ALS"), 1);
					}

					pRegTable->SetRegAddr(0x44);
					pRegTable->SetRegInfo({ 0x80 }, _T("AnalogB"));
					{
						pRegTable->SetBitDetail(_T("DiodeVbs"), _T("Control pin \"diode_vbs\""), 0xC0, 6, BOTH_RW, { 0, 0x03 }, 0x02);
						pRegTable->SetBitDetail(_T("IbTest"), 5, _T("Control pin \"ibtest_sel\""));
						pRegTable->SetBitDetail(_T("TestSel"), 4, _T("Control pin \"test_sel\""));
						pRegTable->SetBitDetail(_T("AnaEn"), 3, _T("Control pin \"ana_en\""));
						pRegTable->SetBitDetail(_T("AnaTest"), _T("Control pin \"ana_test\""), 0x07, 0, BOTH_RW, { 0, 0x07 });
					}

					pRegTable->SetRegAddr(0x45);
					pRegTable->SetRegInfo({ 0x07 }, _T("AnalogC"));
					{
						pRegTable->SetBitDetail(_T("AnaReg"), _T("Control pin \"ana_reg\""), 0xF0, 4, BOTH_RW, { 0, 0x0F });
						pRegTable->SetBitDetail(_T("VrefOp"), _T("Control pin \"vref_op\""), 0x0C, 2, BOTH_RW, { 0, 0x03 }, 0x01);
						pRegTable->SetBitDetail(_T("Vtoph"), _T("Control pin \"vtoph_set\""), 0x03, 0, BOTH_RW, { 0, 0x03 }, 0x03);
					}

					pRegTable->SetRegAddr(0x46);
					pRegTable->SetRegInfo({ 0x00 }, _T("AnalogD"));
					{
						pRegTable->SetBitDetail(_T("DarkTrim"), _T("Control pin \"darktriml\""), 0x1F, 0, BOTH_RW, { 0, 0x1F });
					}

					pRegTable->SetRegAddr(0x4B);
					pRegTable->SetRegInfo({ 0x00 }, _T("TxFreq"));
					{
						pRegTable->SetBitDetail(_T("TxFreq"), _T("Tx Frequency"), 0x07, 0, BOTH_RW, { 0, 0x07 });
					}

					pRegTable->SetRegAddr(0x4C);
					pRegTable->SetRegInfo({ 0x00 }, _T("CtPuw"));
					{
						pRegTable->SetBitDetail(_T("CtPuw"), _T("Fine Crosstalk DAC Width"));
					}

					pRegTable->SetRegAddr(0x4D);
					pRegTable->SetRegInfo({ 0x06 }, _T("TxPuw"));
					{
						pRegTable->SetBitDetail(_T("AmbPuw"), _T(""), 0x30, 4, BOTH_RW, { 0, 0x03 });
						pRegTable->SetBitDetail(_T("DrvPuw"), _T(""), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x06);
					}

					pRegTable->SetRegAddr(0x4E);
					pRegTable->SetRegInfo({ 0x00 }, _T("PrePuw"));
					{
						pRegTable->SetBitDetail(_T("PrePuw"), _T("Pre-Heat Pulse Width"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
					}

					pRegTable->SetRegAddr(0x7B);
					pRegTable->SetRegInfo({ 0x00 }, _T("DigCtrl"));
					{
						pRegTable->SetBitDetail(_T("VenOff"), 7, _T("Enable \"power_sel\""));
						pRegTable->SetBitDetail(_T("PreOff"), 6, _T("Enable Pre Timing"));
						pRegTable->SetBitDetail(_T("TmpNoMean"), 5, _T("TmpData mean time"));
						pRegTable->SetBitDetail(_T("FastTmp"), 4, _T("Out TmpData every Conversion"));
						pRegTable->SetBitDetail(_T("FastEn"), 3, _T("Conversion is min"));
						pRegTable->SetBitDetail(_T("LadcEn"), 2, _T("AmbData = Leak Table"));
						pRegTable->SetBitDetail(_T("PxshEn"), 1, _T("Enable \"pxsh\" at Pre-heat"));
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
					pRegTable->SetRegInfo({ 0x19 }, _T("Tbe"));	//TODO: Check Value
					{
						pRegTable->SetBitDetail(_T("Tbe"), _T("Fuse Burn Width"), 0x3F, 0, BOTH_RW, { 0x00, 0x3F }, 0x19);
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
		uint8_t FastEn = pRegTable->GetBitValue(_T("FastEn"));
		uint8_t PsEn = pRegTable->GetBitValue(_T("PsEn"));
		uint8_t IrEn = pRegTable->GetBitValue(_T("IrEn"));
		uint8_t AlsEn = pRegTable->GetBitValue(_T("AlsEn"));
		uint8_t AlsPuc = pRegTable->GetBitValue(_T("AlsPuc"));
		uint8_t PsMean = pRegTable->GetBitValue(_T("PsMean"));
		uint8_t IrMean = pRegTable->GetBitValue(_T("IrMean"));
		uint8_t WaitTime = pRegTable->GetBitValue(_T("WaitTime"));

		ConversionTime = 0;
		switch (version)
		{
		case 10000:
			if (AlsEn)
			{
				ConversionTime += (uint32_t)AlsPuc * 100;
			}

			if (PsEn)
			{
				if (FastEn)
					ConversionTime += 5;
				else
				{
					switch (PsMean)
					{
					case 0:	ConversionTime += 30; break;
					case 1:	ConversionTime += 40; break;
					case 2:	ConversionTime += 50; break;
					case 3:	ConversionTime += 100; break;
					}
				}
			}

			if (IrEn)
			{
				if (FastEn)
					ConversionTime += 5;
				else
				{
					switch (IrMean)
					{
					case 0:	ConversionTime += 30; break;
					case 1:	ConversionTime += 40; break;
					case 2:	ConversionTime += 50; break;
					case 3:	ConversionTime += 100; break;
					}
				}
			}

			if (ConversionTime > 0)
			{
				ConversionTime += ((uint32_t)WaitTime * 10);
			}

			break;
		}

		return (uint32_t)(ConversionTime * 1000);
	}

	double GetPowerConsumption(uint16_t version, CRegisterTable* pRegTable)
	{
		PowerConsumption = 0;

		return PowerConsumption;
	}

	void AutoDac(uint16_t version, CRegisterTable* pRegTable)
	{

	}
};
