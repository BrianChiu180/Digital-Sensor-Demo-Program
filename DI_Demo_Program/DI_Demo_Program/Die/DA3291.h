#pragma once
#include "Define.h"

#define reg_IrData 0x02

#define reg_WaitTime 0x4f
#define val_WaitTime 0x00

#define reg_PsCtrl 0x60
#define val_PsMean 0x00 // 30 ms
#define val_PsBits 0x01 // 10 bits
#define val_PsGain 0x00 // x1

#define reg_PsPuw 0x61
#define val_PsPuw 0x10 // 32us

#define reg_IrCtrl 0x70
#define val_IrMean 0x00 // 30ms
#define val_IrBits 0x01 // 10 bits
#define val_IrGain 0x00 // x1

#define reg_PsDacCtrl 0x65
#define reg_PsCoasAmb 0x66
#define reg_IrDacCtrl 0x75
#define reg_IrCoasAmb 0x76

#define reg_IntFlag 0xfe
#define reg_StatFlag 0xff



class CDA3291 : public CDieInfo {
public:
	CDA3291() {}
	void Init(uint16_t version)
	{
		DieName = _T("DA3291");
		switch (version)
		{
		case 10100:
			DieDetail.insert(make_pair(10100, CDieDetail()));
			{
				pDieDetail = &DieDetail.at(10100);

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
					pRegTable->SetBitDetail(_T("DataHalt"), 4, _T("Data Halt Control Bit"));
					pRegTable->SetBitDetail(_T("IrHalt"), 2, _T("IR INT Halt"));
					pRegTable->SetBitDetail(_T("PsHalt"), 1, _T("PS INT Halt"));
					pRegTable->SetBitDetail(_T("AlsHalt"), 0, _T("ALS Halt Function Control Bit"));
				}

				pRegTable->SetRegAddr(0xF3);
				pRegTable->SetRegInfo({ 0x00 }, _T("SysCtrl"));
				{
					pRegTable->SetBitDetail(_T("PorFen"), 7, _T("Enable Falling POR"));
					pRegTable->SetBitDetail(_T("Operation"), 5, _T("Openation Mode"));
					pRegTable->SetBitDetail(_T("PushPull"), 4, _T("INT pin is Push Pull"));
					pRegTable->SetBitDetail(_T("IoFunc"), _T("Change INT pin output"), 0x0F, 0, BOTH_RW, { 0, 0x0F });
				}

				pRegTable->SetRegAddr(0xF4);
				pRegTable->SetRegInfo({ 0x00 }, _T("SwRst"));
				{
					pRegTable->SetBitDetail(_T("SoftReset"), _T("Software Reset"), _T(""), 0xEE);	//write 0xEE to reset
				}

				pRegTable->SetRegAddr(0xFC);
				pRegTable->SetRegInfo({ 0x1B }, _T("IdPod"));
				{
					pRegTable->SetBitDetail(_T("IdPod"), _T("IdPod"), 0xFF, 0, ONLY_R);
				}

				pRegTable->SetRegAddr(0xFD);
				pRegTable->SetRegInfo({ 0x01 }, _T("IdRev"));
				{
					pRegTable->SetBitDetail(_T("IdRev"), _T("IdRev"), 0xFF, 0, ONLY_R);
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

				pRegTable->SetRegAddr(0x08);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("AlsData2"), 2);
				{
					pRegTable->SetBitDetail2(_T("AlsData2"), _T("AlsData2"));
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
				pRegTable->SetRegInfo({ 0x52 }, _T("AlsCtrl"));
				{
					pRegTable->SetBitDetail(_T("AlsGain2"), 6, _T("AlsData2 Gain"), 1);
					pRegTable->SetBitDetail(_T("AlsGain1"), _T("AlsData1 Gain"), 0x38, 3, BOTH_RW, { 0, 0x07 }, 0x02);
					pRegTable->SetBitDetail(_T("AlsGain0"), _T("AlsData0 Gain"), 0x07, 0, BOTH_RW, { 0, 0x07 }, 0x02);
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
				pRegTable->SetRegInfo({ 0x00 }, _T("AlsPuw1"));
				{
					pRegTable->SetBitDetail(_T("AlsPuw1"), _T("AlsData1 Conversion width"), 0x7F, 0, BOTH_RW, { 0, 0x7F }, 0x00);
				}

				pRegTable->SetRegAddr(0x57);
				pRegTable->SetRegInfo({ 0x0A }, _T("AlsPuw2"));
				{
					pRegTable->SetBitDetail(_T("AlsPuw2"), _T("AlsData2 Conversion width"), 0x7F, 0, BOTH_RW, { 0, 0x7F }, 0x0A);
				}

				pRegTable->SetRegAddr(0x5B);
				pRegTable->SetRegInfo({ 0x01 }, _T("AlsAlgoCtrl"));
				{
					pRegTable->SetBitDetail(_T("AlsTurbo"), 6, _T("1/10 Time Unit"), 0);
					pRegTable->SetBitDetail(_T("AlsIntSrc"), _T("Define the AlsData to assert AlsInt."), 0x30, 4, BOTH_RW, { 0, 0x02 });
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
					pRegTable->SetBitDetail(_T("PsGain"), 0, _T("PS Gain"), 0);
				}

				pRegTable->SetRegAddr(0x61);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsPuw"));
				{
					pRegTable->SetBitDetail(_T("PsPuw"), _T("PS Integration Pulse Width"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
				}

				pRegTable->SetRegAddr(0x62);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsPuc"));
				{
					pRegTable->SetBitDetail(_T("PsPuc"), _T("PS Integration Pulse Count"), 0x3F, 0, BOTH_RW, { 0, 63 }, 0x00);
				}

				pRegTable->SetRegAddr(0x63);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsPreCtrl"));
				{
					pRegTable->SetBitDetail(_T("PsPrePuc"), _T("PS Pre-Heat Pulse Control"), 0x0F, 0, BOTH_RW, { 0, 15 });
				}

				pRegTable->SetRegAddr(0x64);
				pRegTable->SetRegInfo({ 0x01 }, _T("PsDrvCtrl"));
				{
					pRegTable->SetBitDetail(_T("PsDrvDc"), _T("Driving DC"), 0xC0, 6, BOTH_RW, { 0, 3 }, 0x00);
					pRegTable->SetBitDetail(_T("PsDrvMax"), _T("Configures the Maximum Driving Current"), 0x30, 4, BOTH_RW, { 0, 3 }, 0x00);
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
					pRegTable->SetBitDetail(_T("PsCoasAmb"), _T("PS Coarse DAC for Ambient"), 0x3F, 0, BOTH_RW, { 0, 0x3F });
				}

				pRegTable->SetRegAddr(0x67);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsCoasCt"));
				{
					pRegTable->SetBitDetail(_T("PsCoasCt"), _T("PS Coarse DAC for Crosstalk"), 0x3F, 0, BOTH_RW, { 0, 63 });
				}

				pRegTable->SetRegAddr(0x68);
				pRegTable->SetRegInfo({ 0x00 }, _T("PsFineCt"));
				{
					pRegTable->SetBitDetail(_T("PsFineCt"), _T("PS Fine DAC for Crosstalk"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
				}

				pRegTable->SetRegAddr(0x69);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("PsCal"), 2);
				{
					pRegTable->SetBitDetail2(_T("PsCal"), { 0x00, 0x00 }, _T(""));
				}

				pRegTable->SetRegAddr(0x6B);
				pRegTable->SetRegInfo({ 0x11 }, _T("PsAlgoCtrl"));
				{
					pRegTable->SetBitDetail(_T("PsTurbo"), 6, _T("PS Conversion forces 20ms."));
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
					pRegTable->SetBitDetail(_T("IrMean"), _T("IR data mean time"), 0xC0, 6, BOTH_RW, { 0, 0x03 }, 0x00);
					pRegTable->SetBitDetail(_T("IrBits"), _T("Define IrData bits"), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x00);
					pRegTable->SetBitDetail(_T("IrGain"), 0, _T("IR Gain"), 0);
				}

				pRegTable->SetRegAddr(0x71);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrPuw"));
				{
					pRegTable->SetBitDetail(_T("IrPuw"), _T("IR Integration Pulse Width"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
				}

				pRegTable->SetRegAddr(0x72);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrPuc"));
				{
					pRegTable->SetBitDetail(_T("IrPuc"), _T("IR Integration Pulse Count"), 0x3F, 0, BOTH_RW, { 0, 63 }, 0x00);
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
					pRegTable->SetBitDetail(_T("IrCoasAmb"), _T("IR Coarse DAC for Ambient"), 0x3F, 0, BOTH_RW, { 0, 0x3F });
				}

				pRegTable->SetRegAddr(0x77);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrCoasCt"));
				{
					pRegTable->SetBitDetail(_T("IrCoasCt"), _T("IR Coarse DAC for Crosstalk"), 0x3F, 0, BOTH_RW, { 0, 63 });
				}

				pRegTable->SetRegAddr(0x78);
				pRegTable->SetRegInfo({ 0x00 }, _T("IrFineCt"));
				{
					pRegTable->SetBitDetail(_T("IrFineCt"), _T("IR Fine DAC for Crosstalk"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
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

					pRegTable->SetRegAddr(0x26);
					pRegTable->SetRegInfo({ 0x00 }, _T("AlsLcf2"));
					{
						pRegTable->SetBitDetail(_T("AlsLcf2"), _T("AlsData2 Lcf = PsLcf/64"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

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

					pRegTable->SetRegAddr(0x30);
					pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfLow2"));
					{
						pRegTable->SetBitDetail(_T("AlsTcfLow2"), _T("AlsData2 Tcf = AlsTcfLow2/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

					pRegTable->SetRegAddr(0x31);
					pRegTable->SetRegInfo({ 0x00 }, _T("AlsTcfHigh2"));
					{
						pRegTable->SetBitDetail(_T("AlsTcfHigh2"), _T("AlsData2 Tcf = AlsTcfHigh2/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
					}

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
					pRegTable->SetRegInfo({ 0x32 }, _T("TTAR"));
					{
						pRegTable->SetBitDetail(_T("TTAR"), _T("TmpData Unit= TTAR x 10us"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x32);
					}

					pRegTable->SetRegAddr(0x3F);
					pRegTable->SetRegInfo({ 0x1B }, _T("PTAR"));
					{
						pRegTable->SetBitDetail(_T("PTAR"), _T("PsData Unit= PTAR x 10us at 9 bits"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x1B);
					}

					pRegTable->SetRegAddr(0x40);
					pRegTable->SetRegInfo({ 0x14 }, _T("ATAR"));
					{
						pRegTable->SetBitDetail(_T("ATAR"), _T("AlsData0~2 Unit= ATAR x 50us"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x1B);
					}

					pRegTable->SetRegAddr(0x41);
					pRegTable->SetRegInfo({ 0x71 }, _T("TmpAdc"));	//TODO: check value
					{
						pRegTable->SetBitDetail(_T("TmpV2i"), _T("Pin¡§pxy_v2i_sel¡¨at TmpData"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x07);
						pRegTable->SetBitDetail(_T("TmpCap"), 0, _T("Pin¡§pcap_sel¡¨at TmpData"), 1);
					}

					pRegTable->SetRegAddr(0x42);
					pRegTable->SetRegInfo({ 0x91 }, _T("PxyAdc"));
					{
						pRegTable->SetBitDetail(_T("PxyV2i"), _T("Control pin \"pxy_v2i_sel\" at PS/IR ADC"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x09);
						pRegTable->SetBitDetail(_T("PxyCap"), 0, _T("Control pin \"pcap_sel\" at PS/IR ADC"), 1);
					}

					pRegTable->SetRegAddr(0x43);
					pRegTable->SetRegInfo({ 0x09 }, _T("AnalogA"));
					{
						pRegTable->SetBitDetail(_T("AlsBias1"), 7, _T("Pin ¡§pdvb0d3v_en¡¨ at AlsData1"), 0);
						pRegTable->SetBitDetail(_T("IrBias"), 6, _T("Pin ¡§pdvb0d3v_en¡¨ at IrData , AlsData2"));
						pRegTable->SetBitDetail(_T("PsBias"), 5, _T("Pin ¡§pdvb0d3v_en¡¨ at PsData"));
						pRegTable->SetBitDetail(_T("AlsBias"), 4, _T("Pin ¡§pdvb0d3v_en¡¨ at AlsData0"));
						pRegTable->SetBitDetail(_T("AlsDark1"), 3, _T("Pin¡§als_dark¡¨at AlsData1"), 1);
						pRegTable->SetBitDetail(_T("IrDark"), 2, _T("Pin ¡§ir_dark¡¨	at IrData , AlsData2"), 0);
						pRegTable->SetBitDetail(_T("PsDark"), 1, _T("Pin ¡§ir_dark¡¨	at PsData"));
						pRegTable->SetBitDetail(_T("AlsDark"), 0, _T("Pin ¡§als_dark¡¨	at AlsData0"), 1);
					}

					pRegTable->SetRegAddr(0x44);
					pRegTable->SetRegInfo({ 0x00 }, _T("AnalogB"));
					{
						pRegTable->SetBitDetail(_T("TestSel"), 7, _T("Control pin \"test_sel\""));
						pRegTable->SetBitDetail(_T("IbTest"), 4, _T("Control pin \"ibtest_sel\""));
						pRegTable->SetBitDetail(_T("AnaEn"), 3, _T("Control pin \"ana_en\""));
						pRegTable->SetBitDetail(_T("AnaTest"), _T("Control pin \"ana_test\""), 0x07, 0, BOTH_RW, { 0, 0x07 });
					}

					pRegTable->SetRegAddr(0x45);
					pRegTable->SetRegInfo({ 0x10 }, _T("AnalogC"));
					{
						pRegTable->SetBitDetail(_T("Pmosw"), _T("Pin ¡§pmosw¡¨"), 0xE0, 0, BOTH_RW, { 0, 0x07 });
						pRegTable->SetBitDetail(_T("CoasDc"), 4, _T("Control pin \"coas_offset\" at PS/IR"), 0x01);
						pRegTable->SetBitDetail(_T("AnaReg"), _T("Control pin \"ana_reg\""), 0x0F, 0, BOTH_RW, { 0, 0x0F });
					}

					pRegTable->SetRegAddr(0x46);
					pRegTable->SetRegInfo({ 0x08 }, _T("AnalogD"));
					{
						//pRegTable->SetBitDetail(_T("AlsFreq1"), 7, _T("Control pin \"f2xsel\" at IR(AlsData1)"));
						//pRegTable->SetBitDetail(_T("AlsFreq0"), 6, _T("Control pin \"f2xsel\" at ALS(AlsData0)"));
						//pRegTable->SetBitDetail(_T("DiodeVbs"), _T("Control pin \"diode_vbs\""), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x02);
						//pRegTable->SetBitDetail(_T("Reserved0x46_5_4"), _T("Reserved0x46_5_4"), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x02);
						pRegTable->SetBitDetail(_T("VrefOp"), _T("Control pin \"vref_op\""), 0x0C, 2, BOTH_RW, { 0, 0x03 }, 0x01);
						//pRegTable->SetBitDetail(_T("Vtoph"), _T("Control pin \"vtoph_set\""), 0x03, 0, BOTH_RW, { 0, 0x03 }, 0x03);
						//pRegTable->SetBitDetail(_T("Reserved0x46_1_0"), _T("Reserved0x46_1_0"), 0x03, 0, BOTH_RW, { 0, 0x03 });
					}

					pRegTable->SetRegAddr(0x47);
					pRegTable->SetRegInfo({ 0x00 }, _T("AlsDc0"));
					{
						pRegTable->SetBitDetail(_T("AlsDarkTrim0"), _T("Pin ¡§darktrim¡¨	at AlsData0"), 0x1F, 0, BOTH_RW, { 0, 0x1F }, 0x00);
					}

					pRegTable->SetRegAddr(0x48);
					pRegTable->SetRegInfo({ 0x00 }, _T("AlsDc1"));
					{
						pRegTable->SetBitDetail(_T("AlsDarkTrim1"), _T("Pin ¡§darktrim¡¨	at AlsData1"), 0x1F, 0, BOTH_RW, { 0, 0x1F }, 0x00);
					}

					pRegTable->SetRegAddr(0x49);
					pRegTable->SetRegInfo({ 0x00 }, _T("PsDc"));
					{
						pRegTable->SetBitDetail(_T("PsDarkTrim"), _T("Pin ¡§darktrim¡¨	at PsData"), 0x1F, 0, BOTH_RW, { 0, 0x1F }, 0x00);
					}

					pRegTable->SetRegAddr(0x4A);
					pRegTable->SetRegInfo({ 0x00 }, _T("IrDc"));
					{
						pRegTable->SetBitDetail(_T("IsDarkTrim"), _T("Pin ¡§darktrim¡¨	at IrData , AlsData2"), 0x1F, 0, BOTH_RW, { 0, 0x1F }, 0x00);
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
					pRegTable->SetRegInfo({ 0x0C }, _T("TxPuw"));
					{
						pRegTable->SetBitDetail(_T("PrePuw"), _T(""), 0xE0, 5, BOTH_RW, { 0, 0x00 });
						pRegTable->SetBitDetail(_T("DrvPuw"), _T(""), 0x1C, 2, BOTH_RW, { 0, 0x07 }, 0x03);
						pRegTable->SetBitDetail(_T("OffPuw"), _T(""), 0x03, 0, BOTH_RW, { 0, 0x03 }, 0x00);
					}

					pRegTable->SetRegAddr(0x4E);
					pRegTable->SetRegInfo({ 0x22 }, _T("TgenCtrl"));
					{
						pRegTable->SetBitDetail(_T("TmpMean"), _T(""), 0x07, 0, BOTH_RW, { 0, 0x07 }, 0x04);
					}

					pRegTable->SetRegAddr(0x7A);
					pRegTable->SetRegInfo({ 0x00 }, _T("LoscData"));
					{
						pRegTable->SetBitDetail(_T("LoscData"), _T(""), 0xFF, 0, ONLY_R);
					}

					pRegTable->SetRegAddr(0x7B);
					pRegTable->SetRegInfo({ 0x00 }, _T("DigCtrl"));
					{
						//pRegTable->SetBitDetail(_T("VenOff"), 7, _T("Enable \"power_sel\""));
						//pRegTable->SetBitDetail(_T("PreOff"), 6, _T("Enable Pre Timing"));
						//pRegTable->SetBitDetail(_T("TmpNoMean"), 5, _T("TmpData mean time"));
						pRegTable->SetBitDetail(_T("FastTmp"), 4, _T("Out TmpData every Conversion"));
						pRegTable->SetBitDetail(_T("FastEn"), 3, _T("Conversion is min"));
						pRegTable->SetBitDetail(_T("LadcEn"), 2, _T("AmbData = Leak Table"));
						pRegTable->SetBitDetail(_T("AlsRandOff"), 1, _T("Disable Random at ALS"));
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
					pRegTable->SetRegInfo({ 0x19 }, _T("Tbe"));
					{
						pRegTable->SetBitDetail(_T("IfuseMr"), _T("Fuse Burn Width"), 0xC0, 6, BOTH_RW, { 0x00, 0x04 });
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
						//pRegTable->SetBitDetail(_T("LdoaExt"), 7, _T("Control ldoa_ext when Device ON"));
						pRegTable->SetBitDetail(_T("HoscExt"), 6, _T("Control hosc_ext when Device ON"));
						pRegTable->SetBitDetail(_T("VbgPuw"), 4, _T(""));
						//pRegTable->SetBitDetail(_T("LoscEnb"), 3, _T("Control losc_enb when Device OFF"));
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
		uint8_t AlsPuw2 = pRegTable->GetBitValue(_T("AlsPuw2"));
		uint8_t WaitTime = pRegTable->GetBitValue(_T("WaitTime"));
		uint8_t AlsTurbo = pRegTable->GetBitValue(_T("AlsTurbo"));

		uint8_t PsEn = pRegTable->GetBitValue(_T("PsEn"));
		uint8_t PsMean = pRegTable->GetBitValue(_T("PsMean"));
		uint8_t PsPuw = pRegTable->GetBitValue(_T("PsPuw"));
		uint8_t PsPuc = pRegTable->GetBitValue(_T("PsPuc"));
		uint8_t PsPrePuc = pRegTable->GetBitValue(_T("PsPrePuc"));
		uint8_t PsTurbo = pRegTable->GetBitValue(_T("PsTurbo"));

		uint8_t IrEn = pRegTable->GetBitValue(_T("IrEn"));
		uint8_t IrMean = pRegTable->GetBitValue(_T("IrMean"));


		ConversionTime = 0;
		double AlsPucUnit = 100;
		double AlsPuwUnit = 1;
		double AlsPuwSum = (double)AlsPuw0 * AlsPuwUnit + (double)AlsPuw1 * AlsPuwUnit + (double)AlsPuw2 * AlsPuwUnit;

		if (AlsPuc == 0)
			AlsPuc = 1;

		switch (version)
		{
		case 10100:
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
				AlsPuwSum = ((double)AlsPuw0 * AlsPuwUnit + (double)AlsPuw1 * AlsPuwUnit + (double)AlsPuw2 * AlsPuwUnit) * (double)AlsPuc;

				if (AlsPuwSum > ConversionTime)
					ConversionTime = AlsPuwSum;
			}

			if (PsEn)
			{
				if (PsTurbo)
				{
					ConversionTime += 20;
				}
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
				switch (IrMean)
				{
				case 0:	ConversionTime += 30; break;
				case 1:	ConversionTime += 40; break;
				case 2:	ConversionTime += 50; break;
				case 3:	ConversionTime += 100; break;
				}
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
		//uint8_t Reg0xF0;
		//map<CString, CBitDetail>* pBitDetailMap;
		uint8_t PsEn = pRegTable->GetBitValue(_T("PsEn"));
		uint16_t WaitTime = (uint16_t)pRegTable->GetRegValue(0x4F);
		uint8_t PsBits = pRegTable->GetBitValue(_T("PsBits"));
		uint8_t PsMean = pRegTable->GetBitValue(_T("PsMean"));
		uint8_t PsPuc = pRegTable->GetBitValue(_T("PsPuc"));
		uint8_t PsPuw = pRegTable->GetBitValue(_T("PsPuw"));
		uint8_t PsDrv = pRegTable->GetBitValue(_T("PsDrv"));
		uint8_t PsDrvMax = pRegTable->GetBitValue(_T("PsDrvMax"));

		double A_PWR = 0, B_PWR = 0, C_PWR = 0;
		double PsMeanTime[] = {30.0, 40.0, 50.0, 100.0};
		double Idrvmax[] = {24.0, 160.0, 30.0, 200.0};
		double Idrv = 0;

		PsPuc = PsPuc == 0 ? 1 : PsPuc;
		WaitTime = WaitTime == 0 ? 0 : (WaitTime * 10);
		PsDrv = PsDrv == 0 ? 0 : (PsDrv + 1);
		Idrv = ((double)PsDrv / 16.0) * Idrvmax[PsDrvMax];

		double BitsMeanBase[4][4] = {
			{22.81, 27.78, 39.18, 36.80},
			{24.47, 30.43, 43.38, 41.17},
			{28.11, 35.53, 51.78, 49.55},
			{35.08, 46.24, 68.64, 66.15}
		};

		double da3291_alpha[4][4] = {
			{0.264, 0.4, 0.62, 0.668},
			{0.262, 0.363, 0.633, 0.66},
			{0.251, 0.373, 0.713, 0.593},
			{0.25, 0.42, 0.688, 0.684}
		};

		double da3291_beta[4][4] = {
			{5.540, 8.26, 13.375, 14.003},
			{5.725, 8.207, 13.327, 13.349},
			{5.546, 8.302, 13.608, 13.321},
			{5.605, 8.394, 13.14, 13.072}
		};

		if (PsEn)
		{
			A_PWR = BitsMeanBase[PsBits][PsMean] + ((double)(PsPuc - 1) * da3291_beta[PsBits][PsMean])
				+ ((double)(PsPuw - 1) * (double)PsPuc * da3291_alpha[PsBits][PsMean]);

			PowerConsumption = A_PWR;

			if (WaitTime > 0)
			{
				B_PWR = (A_PWR * PsMeanTime[PsMean]) / ConversionTime;
				PowerConsumption = B_PWR;
			}

			C_PWR = (Idrv * (double)pow(2, PsMean) * 2.0 * (7.0 + (double)PsPuw) * (double)PsPuc) / ConversionTime;

			PowerConsumption += C_PWR;
		}
		else
			PowerConsumption = 0.7;

		return PowerConsumption;
	}

	void AutoDac(uint16_t version, CRegisterTable* pRegTable)
	{
		uint8_t SlaveID = pRegTable->DeviceID;
		uint8_t PsBits = pRegTable->GetBitValue(_T("PsBits"));


		uint8_t buff[5];
		uint16_t PsData;
		bool first_data = true;

		//Setting Variable
		uint8_t DevCtrl_Reg  = 0xF0;
		uint8_t IntCtrl_Reg  = 0xF1;
		uint8_t HaltCtrl_Reg = 0xF2;
		uint8_t WaitTime_Reg = 0x4F;
		uint8_t IntFlag_Reg  = 0xFE;
		uint8_t PsFineCt_Reg = 0x68;
		uint8_t PsFineCt_Val = 0;
		uint8_t PsDacCtrl_Reg = 0x65;
		uint8_t PsDacCtrl_Val = 0;
		uint8_t PsFineGain_Val = 0;
		uint8_t PsCoasGain_Val = 0;		
		int16_t PsFineCt_Val_temp = 0;

		//PI Control variable
		bool PI_Control = true;
		int32_t dp = 0;
		int32_t di = 0;
		//double Kp = 0.015;
		//double Kp = 0.16; // leo for each dac step reduce about 6 count
		//double Ki = 0.02;
		uint8_t last_try = 0;

		//Bisection method
		uint8_t PsFineCt_Val_Max = 127;
		uint8_t PsFineCt_Val_Min = 0;

		uint16_t FullRange = 1 << (PsBits + 9);
		uint16_t TargetPS = FullRange >> 2;

		//Sensor Initial
		uint8_t reg_data[][3] = {
			{DevCtrl_Reg, 0x00, 0x00},	// Shutdown
			{IntCtrl_Reg, 0x00, 0x00},	// No Interrupt Output 
			{HaltCtrl_Reg, 0x10, 0x00},	// DataHalt Enable
			{WaitTime_Reg, 0x00, 0x00},	// WaitTime = 0
			{IntFlag_Reg, 0x00, 0x00},	// Clear IntFalg
			{0x7B, 0x08, 0x00},	// Interanl Setting => Fast En (no show on custom)
		};

		for (uint8_t i = 0; i < sizeof(reg_data) / (sizeof(uint8_t) * 3); i++)
		{
			I2CRead(0, SlaveID, reg_data[i][0], &reg_data[i][2], 1, 0, 0, 1000); // Save Org val
			I2CWrite(0, SlaveID, reg_data[i][0], &reg_data[i][1], 1);
			if (i == 0)
				Sleep(5); //After Sensor Shutdown, Delay 5 ms
		}


		I2CRead(0, SlaveID, PsDacCtrl_Reg, buff, 1, 0, 0, 1000);

		PsFineGain_Val = 1;
		PsCoasGain_Val = buff[0] >> 4;
		PsDacCtrl_Val = (buff[0] & 0xF0) | PsFineGain_Val;		// Set PsFineGain val to 0x01
		I2CWrite(0, SlaveID, PsDacCtrl_Reg, &PsDacCtrl_Val, 1);

		PsFineCt_Val = 0;  // Clear PsFineCt val
		I2CWrite(0, SlaveID, PsFineCt_Reg, &PsFineCt_Val, 1);

		buff[0] = 0x02;  // Enable PS
		I2CWrite(0, SlaveID, DevCtrl_Reg, buff, 1);
		Sleep(10); //After Sensor Enable, Delay 10 ms

		while (1)
		{
			I2CRead(0, SlaveID, IntFlag_Reg, buff, 4, 0, 0, 1000);
			if ((buff[0] & 0x10) == 0x10)  //  Check whether data ready
			{
				PsData = (uint16_t)buff[2] + ((uint16_t)buff[3] << 8);

				if (first_data)
				{
					first_data = false;
					continue;
				}

				if (last_try == 1 && PsData > 0)
				{
					break;
				}
				else
					last_try = 0;

				if (PsFineCt_Val > 0)
				{
					if (PsData == 0)
					{
						PsFineCt_Val_Max = (uint8_t)PsFineCt_Val;
						PI_Control = false;
					}
					else if (PsData <= TargetPS)
						break;
					else if (PsFineCt_Val == PsFineCt_Val_Min || PsFineCt_Val == PsFineCt_Val_Max)	//Reduce calcualate time.
					{
						break;
					}
				}
				else if (PsData <= TargetPS)
					break;

				if (PI_Control)
				{
					dp = PsData - TargetPS;

					//di += dp;

					//PsFineCt_Val_temp = PsFineCt_Val + (int16_t)((Kp * dp) + (Ki * di)) + (dp >= 0 ? 1 : -1);
					//PsFineCt_Val_temp = PsFineCt_Val + (int16_t)((Kp * dp)) + (dp >= 0 ? 1 : -1); // leo
					PsFineCt_Val_temp = (int16_t)PsFineCt_Val
						+ (int16_t)((dp >> 6) + ((di >> 6) + (di >> 8))) + (dp >= 0 ? 1 : -1);

					if (PsFineCt_Val_temp > 127)
					{
						if (PsFineGain_Val == 0x0F)
						{
							last_try = 1;
							PsFineCt_Val_temp = 127;
						}
						else
						{
							//PsFineGain_Val = (uint8_t)((float)PsFineGain_Val * ((float)PsFineCt_Val_temp / 64.0f));
							//PsFineGain_Val += (uint8_t)((float)PsFineCt_Val_temp / 80.0f); // leo

							if (dp > (TargetPS << 1))
							{
								PsFineGain_Val <<= 1;
							}
							else if (dp > TargetPS)
							{
								PsFineGain_Val += 2;
							}
							else
							{
								PsFineGain_Val++;
							}



							if (PsFineGain_Val == 0)
								PsFineGain_Val = 1;
							else if (PsFineGain_Val > 0x0F)
								PsFineGain_Val = 0x0F;

							PsFineCt_Val_temp = 64;
							//leo							
							dp = 0;
							//leo

							PsDacCtrl_Val = (PsDacCtrl_Val & 0xF0) | PsFineGain_Val;
							I2CWrite(0, SlaveID, PsDacCtrl_Reg, &PsDacCtrl_Val, 1);
						}
					}
				}
				else
				{
					if (PsData > TargetPS)
						PsFineCt_Val_Min = (uint8_t)PsFineCt_Val_temp;

					if (PsData < FullRange && PsData > TargetPS)	//Reduce calcualate time.
					{
						//PsFineCt_Val_temp += 2;
						PsFineCt_Val_temp = (uint16_t)(PsFineCt_Val_temp + PsFineCt_Val_Max) >> 1;
					}
					else
						PsFineCt_Val_temp = (uint16_t)(PsFineCt_Val_Min + PsFineCt_Val_Max) >> 1;
				}

				PsFineCt_Val = (uint8_t)PsFineCt_Val_temp;

				I2CWrite(0, SlaveID, PsFineCt_Reg, &PsFineCt_Val, 1);

				buff[0] = 0x00;
				I2CWrite(0, SlaveID, 0xFE, buff, 1);
			}
		}


		pRegTable->RegInfo.at(PsDacCtrl_Reg).RegCurVal.at(0) = PsDacCtrl_Val;
		pRegTable->RegInfo.at(PsFineCt_Reg).RegCurVal.at(0) = PsFineCt_Val;

		buff[0] = 0x00;
		I2CWrite(0, 0x1C, 0xF0, buff, 1);	//Shutdown
		Sleep(5); //After Sensor Shutdown, Delay 5 ms

		for (int8_t i = sizeof(reg_data) / (sizeof(uint8_t) * 3); i > 0;)
		{
			i--;
			I2CWrite(0, SlaveID, reg_data[i][0], &reg_data[i][2], 1);
		}
		Sleep(10); //After Sensor Enable, Delay 10 ms

		CString csTemp;
		csTemp.Format(_T("Auto CtDac is Done.\nPsFineGain_Val = %d\nPsFineCt_Val = %d"),
			PsFineGain_Val,
			PsFineCt_Val);

		MessageBoxW(0, csTemp, _T("Calibration Function"), MB_OK);
	}

	uint8_t GetIntFlag(uint16_t version, CRegisterTable* pRegTable)
	{
		uint8_t IntFlag_val = 0;

		I2CRead(0, pDieDetail->RegisterTable.DeviceID, reg_IntFlag, &IntFlag_val, 1, 0, 0, 1000);

		return IntFlag_val;
	}

	bool SLSuppression(CRegisterTable* pRegTable, uint8_t* SunLight_Status)
	{
		uint8_t PsMean_T[] = { 30, 40, 50, 100 };
		uint8_t IrMean_T[] = { 30, 40, 50, 100 };
		uint8_t SlaveID = pRegTable->DeviceID;

		uint8_t PsBits = pRegTable->GetBitValue(_T("PsBits"));
		uint16_t ps_raw = (1 << (PsBits + 9)) - 1;
		uint16_t TargetIr = ps_raw / 4;
		uint16_t WaitTime_T = pRegTable->GetRegValue(0x4F) * 10;
		uint8_t PsMean = pRegTable->GetBitValue(_T("PsMean"));
		uint8_t IrMean = pRegTable->GetBitValue(_T("IrMean"));
		uint16_t conv_t = PsMean_T[PsMean] + IrMean_T[IrMean] + WaitTime_T;
		uint8_t IrCoasAmb = pRegTable->GetBitValue(_T("IrCoasAmb"));
		uint8_t IrFineGain_Val = pRegTable->GetBitValue(_T("IrFineGain"));
		uint8_t PsDacCtrl_Val = 0;
		uint16_t FullRange = (1 << (PsBits + 9)) - 1;
		uint16_t IrLimitaion = FullRange * 3 / 4;
		
		uint16_t IrCoasAmb_temp = 0;
		uint8_t StatFlag_VAL = 0, IrDacCtrl_VAL = 0, IntFlag_VAL = 0;
		uint8_t IrCoasGain_VAL = 0, IrCoasAmb_VAL = 0, data[2] = { 0 };
		uint16_t IrData = 0, OrgIrData = 0;
		int iloop = 0;
		int32_t old_di = 0;
		float tt = 0;
		clock_t st, et;

		//PI Control variable
		bool PI_Control = true;
		int32_t dp = 0;
		int32_t di = 0;
		double Kp = 0.015;
		double Ki = 0.02;
		uint8_t last_try = 0;

		//Bisection method
		uint8_t IrCoasAmbMax = 0x3f;
		uint8_t IrCoasAmbMin = 0;

		//std::cout << "TargetIr dec: " << std::dec << +TargetIr << std::endl;
		//std::cout << "FullRange dec: " << std::dec << +FullRange << std::endl;

		//clear int flag
		IntFlag_VAL = 0;
		I2CWrite(0, pDieDetail->RegisterTable.DeviceID, reg_IntFlag, &IntFlag_VAL, 1);		

		while (1)
		{
			if ((GetIntFlag(NULL, NULL) & 0x14)) // Waiting for IR data ready
			{
				I2CRead(0, pDieDetail->RegisterTable.DeviceID, reg_IrData, data, 2, 0, 0, 1000);				
				IrData = (data[1] << 8) | data[0];								
				I2CRead(0, pDieDetail->RegisterTable.DeviceID, reg_IrCoasAmb, &IrCoasAmb_VAL, 1, 0, 0, 1000);				
				I2CRead(0, pDieDetail->RegisterTable.DeviceID, reg_IrDacCtrl, &IrDacCtrl_VAL, 1, 0, 0, 1000);				
				IrCoasGain_VAL = IrDacCtrl_VAL >> 4;				

				if (IrData > 600)
				{
					st = clock();
					PI_Control = true;
					OrgIrData = IrData;
					di = old_di;

					if ((IrLimitaion < IrData) && IrCoasAmb_VAL == 63 && IrCoasGain_VAL == 0x0f)
					{						
						*SunLight_Status = SUNLIGHT_TOO_STRONG;
						break;
					}

					++iloop;					

					if (last_try == 1)
					{						
						*SunLight_Status = SUNLIGHT_TOO_STRONG;
						break;
					}
					else
						last_try = 0;

					if (IrCoasAmb_VAL > 0)
					{
						if (IrData == 0)
						{
							IrCoasAmbMax = (uint8_t)IrCoasAmb_VAL;
							PI_Control = false;							
						}
						else if (IrData <= TargetIr)
						{							
							*SunLight_Status = SUNLIGHT_INC;
							break;
						}
						else if (IrCoasAmbMax == IrCoasAmb_VAL || IrCoasAmbMin == IrCoasAmb_VAL)
						{				
							++IrCoasAmb_VAL;
							*SunLight_Status = SUNLIGHT_INC;
							//break;
						}
					}
					else if (IrData <= TargetIr)
					{
						*SunLight_Status = SUNLIGHT_INC;
						break;
					}

					if (IrData > OrgIrData)
					{
						PI_Control = true;
						IrCoasAmbMin = 0;
						IrCoasAmbMax = 0;						
					}

					if (PI_Control)
					{
						dp = IrData - TargetIr;
						di += dp;						

						if (IrCoasGain_VAL == 0x0F)
						{
							if (IrCoasAmb_VAL >= 0x3f)
								IrCoasAmb_temp = 0x3f;
							else
								IrCoasAmb_temp = IrCoasAmb_VAL + 1;
						}
						else
							IrCoasAmb_temp = IrCoasAmb_VAL + (int16_t)((Kp * dp) + (Ki * di)) + (dp >= 0 ? 1 : -1);						

						if (IrCoasAmb_temp > 63)
						{
							if (IrCoasGain_VAL == 0x0F)
							{
								last_try = 1;
								IrCoasAmb_temp = 0x3f;
							}
							else
							{
								IrCoasGain_VAL = (uint8_t)((float)IrCoasAmb_temp / 16.0f);
								
								if (IrCoasGain_VAL < 5)
									IrCoasGain_VAL = 5;
								else if (IrCoasGain_VAL > 0x0F)
									IrCoasGain_VAL = 0x0F;								

								IrCoasAmb_temp = 32;

								IrDacCtrl_VAL = (0x0F & IrDacCtrl_VAL) | (IrCoasGain_VAL << 4);
								
								I2CWrite(0, pDieDetail->RegisterTable.DeviceID, reg_IrDacCtrl, &IrDacCtrl_VAL, 1);

							}
						}
					}
					else
					{
						if (IrData > TargetIr)
						{
							IrCoasAmbMin = (uint8_t)IrCoasAmb_temp;							
						}

						if (IrData < FullRange && IrData > TargetIr)	//Reduce calcualate time.
						{
							IrCoasAmb_temp += 2;							
						}
						else
						{							
							IrCoasAmb_temp = (uint16_t)(IrCoasAmbMin + IrCoasAmbMax) >> 1;							
						}
					}

					IrCoasAmb_VAL = (uint8_t)IrCoasAmb_temp;					
					
					I2CWrite(0, pDieDetail->RegisterTable.DeviceID, reg_IrCoasAmb, &IrCoasAmb_VAL, 1);

					//clear int flag
					IntFlag_VAL = 0;					
					I2CWrite(0, pDieDetail->RegisterTable.DeviceID, reg_IntFlag, &IntFlag_VAL, 1);

					old_di = di;
				}
				else if ((IrData >= 0) && (IrData <= 80) && (IrCoasAmb_VAL > 0 || IrDacCtrl_VAL > 0x51))
				{
					st = clock();
					PI_Control = true;
					OrgIrData = IrData;
					//di = old_di;					


					IrCoasAmb_temp = IrCoasAmb_VAL;

					++iloop;					

					if (IrDacCtrl_VAL == 0x51 && IrCoasAmb_VAL == 0)
					{						
						*SunLight_Status = SUNLIGHT_DEC;
						break;
					}

					if (IrData == 0 && IrCoasAmb_VAL != 0)
					{
						IrCoasAmbMax = (uint8_t)IrCoasAmb_VAL;
						PI_Control = false;						
					}
					else if (IrData >= 0 && IrCoasAmb_VAL == 0 && IrDacCtrl_VAL > 0x51)
					{
						IrCoasAmbMin = (uint8_t)IrCoasAmb_VAL;
						PI_Control = true;						
					}
					else if (IrData > 100 && IrData <= 200)
					{
						*SunLight_Status = SUNLIGHT_DEC;
						break;
					}
					else if (IrData > OrgIrData && !PI_Control)
					{
						*SunLight_Status = SUNLIGHT_DEC;
						break;
					}
					else
						last_try = 0;

					if (PI_Control && IrDacCtrl_VAL > 0x51)
					{
						dp = 150 - IrData;
						di += dp;						

						IrCoasAmb_temp = IrCoasAmb_VAL + (int16_t)((Kp * dp) + (Ki * di)) + (dp >= 0 ? -1 : 1);						

						if (IrCoasAmb_temp >= 0)
						{
							if (IrCoasGain_VAL == 0x05)
							{
								PI_Control = false;
							}
							else
							{
								IrCoasGain_VAL = (uint8_t)((float)IrCoasAmb_temp / 4.0f);
								if (IrCoasGain_VAL == 0)
									IrCoasGain_VAL = 5;
								else if (IrCoasGain_VAL < 0x05)
									IrCoasGain_VAL = 0x05;
								else if (IrCoasGain_VAL > 0x0f)
									IrCoasGain_VAL = 0x0f;

								IrCoasAmb_temp = 32;

								IrDacCtrl_VAL = (0x0F & IrDacCtrl_VAL) | (IrCoasGain_VAL << 4);
								I2CWrite(0, pDieDetail->RegisterTable.DeviceID, reg_IrDacCtrl, &IrDacCtrl_VAL, 1);
							}
						}
					}
					else
					{
						if (IrData < 150)
						{
							IrCoasAmbMax = (uint8_t)IrCoasAmb_temp;							
						}

						if (IrData < 170 && IrData > 0)	//Reduce calcualate time.
						{
							if (IrCoasAmb_temp > 2)
								IrCoasAmb_temp -= 2;
							else if (IrCoasAmb_temp == 1)
								IrCoasAmb_temp -= 1;
							else
								IrCoasAmb_temp = 0;
						}
						else
						{
							IrCoasAmb_temp = (uint16_t)(IrCoasAmbMin + IrCoasAmbMax) >> 1;							
						}
					}

					IrCoasAmb_VAL = (uint8_t)IrCoasAmb_temp;
					I2CWrite(0, pDieDetail->RegisterTable.DeviceID, reg_IrCoasAmb, &IrCoasAmb_VAL, 1);

					//clear int flag
					IntFlag_VAL = 0;
					I2CWrite(0, pDieDetail->RegisterTable.DeviceID, reg_IntFlag, &IntFlag_VAL, 1);

					old_di = di;
				}
				else
				{
					*SunLight_Status = SUNLIGHT_OK;
					break;
				}
			}
		}

		if (iloop > 0)
		{
			et = clock();
			tt = (float)(et - st) / CLOCKS_PER_SEC;
			iloop = 0;			

			I2CWrite(0, pDieDetail->RegisterTable.DeviceID, reg_PsDacCtrl, &IrDacCtrl_VAL, 1);
			I2CWrite(0, pDieDetail->RegisterTable.DeviceID, reg_PsCoasAmb, &IrCoasAmb_VAL, 1);

			pRegTable->RegInfo.at(reg_PsDacCtrl).RegCurVal.at(0) = IrDacCtrl_VAL;
			pRegTable->RegInfo.at(reg_PsCoasAmb).RegCurVal.at(0) = IrCoasAmb_VAL;

			pRegTable->RegInfo.at(reg_IrDacCtrl).RegCurVal.at(0) = IrDacCtrl_VAL;
			pRegTable->RegInfo.at(reg_IrCoasAmb).RegCurVal.at(0) = IrCoasAmb_VAL;

			//clear int flag			
			IntFlag_VAL = 0;
			I2CWrite(0, pDieDetail->RegisterTable.DeviceID, reg_IntFlag, &IntFlag_VAL, 1);			
			while ((GetIntFlag(NULL, NULL)&0x10) != 0x10)
			{	
				Sleep(conv_t);
			}

			return true;
		}

		*SunLight_Status = 0;
		return false;
	}
};

