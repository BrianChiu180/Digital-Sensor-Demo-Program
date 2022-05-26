#pragma once
#include "Define.h"

class CDA3380 : public CDieInfo {
public:
    CDA3380() {}
    void Init(uint16_t version)
    {
        DieName = _T("DA3380");
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
                    pRegTable->SetBitDetail(_T("NewPsEn"), 4, _T("New PS Enable"));
                    pRegTable->SetBitDetail(_T("IrEn"), 2, _T("IR Enable"));
                    pRegTable->SetBitDetail(_T("PsEn"), 1, _T("PS Enable"));
                }

                pRegTable->SetRegAddr(0xF1);
                pRegTable->SetRegInfo({ 0x03 }, _T("IntCtrl"));
                {
                    pRegTable->SetBitDetail(_T("PushPull"), 7, _T("Enable INT Pin push pull"));
                    pRegTable->SetBitDetail(_T("ObjIntEn"), 6, _T("Obj Int Enable"));
                    pRegTable->SetBitDetail(_T("SyncEn"), 5, _T("Enable INT pin as sync input"));
                    pRegTable->SetBitDetail(_T("DataIntEn"), 4, _T("Data Int Enable"));
                    pRegTable->SetBitDetail(_T("IrIntEn"), 2, _T("IR Int Enable"));
                    pRegTable->SetBitDetail(_T("PsIntEn"), 1, _T("PS Int Enable"), 0x01);
                    pRegTable->SetBitDetail(_T("Reserved0xF1_0"), 0, _T("Reserved"), 0x01);
                }

                pRegTable->SetRegAddr(0xF2);
                pRegTable->SetRegInfo({ 0x00 }, _T("HaltCtrl"));
                {
                    pRegTable->SetBitDetail(_T("ReadClear"), 7, _T("Interrupt clear method"));
                    pRegTable->SetBitDetail(_T("DataHalt"), 4, _T("Data INT Halt"));
                    pRegTable->SetBitDetail(_T("IrHalt"), 2, _T("IR INT Halt"));
                    pRegTable->SetBitDetail(_T("PsHalt"), 1, _T("PS INT Halt"));
                }

                pRegTable->SetRegAddr(0xF3);
                pRegTable->SetRegInfo({ 0x00 }, _T("SysCtrl"));
                {
                    pRegTable->SetBitDetail(_T("FallPorEn"), 7, _T("Enable Falling POR"));
                    pRegTable->SetBitDetail(_T("VbgPuw"), _T(""), 0x70, 4, BOTH_RW, { 0, 0x07 }, 0x00);
                    pRegTable->SetBitDetail(_T("Operation"), 0, _T("Openation Mode"));
                }

                pRegTable->SetRegAddr(0xF4);
                pRegTable->SetRegInfo({ 0x00 }, _T("SwRst"));
                {
                    pRegTable->SetBitDetail(_T("SoftReset"), _T("Software Reset"), _T(""), 0xEE);    //write 0xEE to reset
                }

                pRegTable->SetRegAddr(0xFB);
                pRegTable->SetRegInfo({ 0x00 }, _T("LoscData"));
                {
                    pRegTable->SetBitDetail(_T("LoscData"), _T("LOSC Period= LoscData x 800ns"), 0xFF, 0, ONLY_R);
                }

                pRegTable->RegInfo[0xFC] = CRegInfo({ 0x19 }, _T("IDPod"));
                pRegTable->RegInfo[0xFD] = CRegInfo({ 0x00 }, _T("IDRev"));

                pRegTable->SetRegAddr(0xFE);
                pRegTable->SetRegInfo({ 0x80 }, _T("IntFlag"));
                {
                    pRegTable->SetBitDetail(_T("PorInt"), 7, _T("POR INT"), 1);
                    pRegTable->SetBitDetail(_T("PsInt"), 1, _T("PS INT"));
#ifdef _DEBUG
                    pRegTable->SetBitDetail(_T("DataInt"), 4, _T("Data INT"));
                    pRegTable->SetBitDetail(_T("IrInt"), 2, _T("IR INT"));
#endif
                }

                pRegTable->SetRegAddr(0xFF);
                pRegTable->SetRegInfo({ 0x80 }, _T("StatFlag"));
                {
                    pRegTable->SetBitDetail(_T("Obj"), 7, _T("PS Object"), 1);
                    pRegTable->SetBitDetail(_T("PsAmbErr"), 3, _T("PS ckt Error Flag when Drv Off"));
#ifdef _DEBUG
                    pRegTable->SetBitDetail(_T("IrEnvErr"), 6, _T("IR ckt Error Flag when Drv Off"));
                    pRegTable->SetBitDetail(_T("IrRstErr"), 5, _T("IR ckt Error Flag when reset"));
                    pRegTable->SetBitDetail(_T("PsDrvErr"), 4, _T("PS ckt Error Flag when Drv On"));
                    pRegTable->SetBitDetail(_T("IrErr"), 2, _T("IrData Invalid Flag"));
                    pRegTable->SetBitDetail(_T("PsErr"), 1, _T("PsData Invalid Flag"));
#endif
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

                pRegTable->SetRegAddr(0x60);
                pRegTable->SetRegInfo({ 0x08 }, _T("PsCtrl"));
                {
                    pRegTable->SetBitDetail(_T("PsMean"), _T("PS Mean"), 0xC0, 6, BOTH_RW, { 0, 0x03 }, 0x00);
                    pRegTable->SetBitDetail(_T("PsBits"), _T("Define PsData bits"), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x00);
                    pRegTable->SetBitDetail(_T("PsGain"), _T("PS Gain"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x08);
                }

                pRegTable->SetRegAddr(0x61);
                pRegTable->SetRegInfo({ 0x00 }, _T("PsPuw"));
                {
                    pRegTable->SetBitDetail(_T("PsPuw"), _T("PS Integration Pulse Width"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
                }

                pRegTable->SetRegAddr(0x62);
                pRegTable->SetRegInfo({ 0x00 }, _T("PsPuc"));
                {
                    pRegTable->SetBitDetail(_T("PsPuc"), _T("PS Integration Pulse Count"), 0x3F, 0, BOTH_RW, { 0, 63 });
                }

                pRegTable->SetRegAddr(0x63);
                pRegTable->SetRegInfo({ 0x30 }, _T("PsPreCtrl"));
                {
                    pRegTable->SetBitDetail(_T("PsPrePuw"), _T("PS Pre-Heat Pulse Width"), 0xF0, 4, BOTH_RW, { 0, 15 }, 0x03);
                    pRegTable->SetBitDetail(_T("PsPrePuc"), _T("PS Pre-Heat Pulse Count"), 0x0F, 0, BOTH_RW, { 0, 15 });
                }

                pRegTable->SetRegAddr(0x64);
                pRegTable->SetRegInfo({ 0x01 }, _T("PsDrvCtrl"));
                {
                    pRegTable->SetBitDetail(_T("PsDrvDc"), 7, _T("Driving DC"), 0);
                    pRegTable->SetBitDetail(_T("PsDrvMax"), 4, _T("Configures the Maximum Driving Current"));
                    pRegTable->SetBitDetail(_T("PsDrv"), _T("PS Driving Current"), 0x0F, 0, BOTH_RW, { 0, 15 }, 0x01);
                }

                pRegTable->SetRegAddr(0x65);
                pRegTable->SetRegInfo({ 0x11 }, _T("PsDacCtrl"));
                {
                    pRegTable->SetBitDetail(_T("PsAmbGain"), _T("PS Ambient Gain"), 0xF0, 4, BOTH_RW, { 0, 15 }, 0x01);
                    pRegTable->SetBitDetail(_T("PsCtGain"), _T("PS CTDAC Gain"), 0x0F, 0, BOTH_RW, { 0, 15 }, 0x01);
                }

                pRegTable->SetRegAddr(0x66);
                pRegTable->SetRegInfo({ 0x00 }, _T("PsAmbDac"));
                {
                    pRegTable->SetBitDetail(_T("PsAmbDac"), _T("PS Ambient DAC"), 0x3F, 0, BOTH_RW, { 0, 0x3F });
                }

                pRegTable->SetRegAddr(0x67);
                pRegTable->SetRegInfo({ 0x00 }, _T("PsCtDac"));
                {
                    pRegTable->SetBitDetail(_T("PsCtDac"), _T("PS Crosstalk DAC"), 0x7F, 0, BOTH_RW, { 0, 96 });
                }

                pRegTable->SetRegAddr(0x68);
                pRegTable->SetRegInfo({ 0x7F }, _T("PsCtPuw"));
                {
                    pRegTable->SetBitDetail(_T("PsCtPuw"), _T("PS Crosstalk DAC Pulse Width"), 0xFF, 0, BOTH_RW, { 0, 0xFF }, 0x7F);
                }

                pRegTable->SetRegAddr(0x69);
                pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("PsCal"), 2);
                {
                    pRegTable->SetBitDetail2(_T("PsCal"), { 0x00, 0x00 }, _T(""));
                }

                pRegTable->SetRegAddr(0x6B);
                pRegTable->SetRegInfo({ 0x11 }, _T("PsAlgoCtrl"));
                {
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
                pRegTable->SetRegInfo({ 0x08 }, _T("IrCtrl"));
                {
                    pRegTable->SetBitDetail(_T("IrMean"), _T("IR Mean"), 0xC0, 6, BOTH_RW, { 0, 0x03 }, 0x00);
                    pRegTable->SetBitDetail(_T("IrBits"), _T("Define IrData bits"), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x00);
                    pRegTable->SetBitDetail(_T("IrGain"), _T("IR Gain"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x08);
                }

                pRegTable->SetRegAddr(0x71);
                pRegTable->SetRegInfo({ 0x00 }, _T("IrPuw"));
                {
                    pRegTable->SetBitDetail(_T("IrPuw"), _T("IR Integration Pulse Width"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
                }

                pRegTable->SetRegAddr(0x72);
                pRegTable->SetRegInfo({ 0x00 }, _T("IrPuc"));
                {
                    pRegTable->SetBitDetail(_T("IrPuc"), _T("IR Integration Pulse Count"), 0x3F, 0, BOTH_RW, { 0, 63 });
                }

                pRegTable->SetRegAddr(0x73);
                pRegTable->SetRegInfo({ 0x00 }, _T("IrPreCtrl"));
                {
                    pRegTable->SetBitDetail(_T("IrPrePuw"), _T("IR Pre-Heat Pulse Width"), 0xF0, 4, BOTH_RW, { 0, 15 }, 0x03);
                    pRegTable->SetBitDetail(_T("IrPrePuc"), _T("IR Pre-Heat Pulse Count"), 0x0F, 0, BOTH_RW, { 0, 15 });
                }

                pRegTable->SetRegAddr(0x74);
                pRegTable->SetRegInfo({ 0x00 }, _T("IrDrvCtrl"));
                {
                    pRegTable->SetBitDetail(_T("IrDrvDc"), _T("Driving DC"), 0xC0, 6, BOTH_RW, { 0, 3 });
                    pRegTable->SetBitDetail(_T("IrDrvMax"), 4, _T("Configures the Maximum Driving Current"));
                    pRegTable->SetBitDetail(_T("IrDrv"), _T("IR Driving Current"), 0x0F, 0, BOTH_RW, { 0, 15 }, 0x00);
                }

                pRegTable->SetRegAddr(0x75);
                pRegTable->SetRegInfo({ 0x11 }, _T("IrDacCtrl"));
                {
                    pRegTable->SetBitDetail(_T("IrAmbGain"), _T("IR CTDAC Gain"), 0xF0, 4, BOTH_RW, { 0, 15 }, 0x01);
                    pRegTable->SetBitDetail(_T("IrCtGain"), _T("IR CTDAC Step"), 0x0F, 0, BOTH_RW, { 0, 15 }, 0x01);
                }

                pRegTable->SetRegAddr(0x76);
                pRegTable->SetRegInfo({ 0x00 }, _T("IrAmbDac"));
                {
                    pRegTable->SetBitDetail(_T("IrAmbDac"), _T("IR Ambient DAC"), 0x3F, 0, BOTH_RW, { 0, 0x3F });
                }

                pRegTable->SetRegAddr(0x77);
                pRegTable->SetRegInfo({ 0x00 }, _T("IrCtDac"));
                {
                    pRegTable->SetBitDetail(_T("IrCtDac"), _T("IR Crosstalk DAC"), 0x7F, 0, BOTH_RW, { 0, 96 });
                }

                pRegTable->SetRegAddr(0x78);
                pRegTable->SetRegInfo({ 0x7F }, _T("IrCtPuw"));
                {
                    pRegTable->SetBitDetail(_T("IrCtPuw"), _T("IR Crosstalk DAC Pulse Width"), 0xFF, 0, BOTH_RW, { 0, 0xFF }, 0x7F);
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
                    pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak 25"), 2);
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
                    pRegTable->SetRegInfo({ 0x1A }, _T("PsUnit"));
                    {
                        pRegTable->SetBitDetail(_T("PsUnit"), _T("Ps ADC Time Unit(10 uS)"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x1A);
                    }

                    pRegTable->SetRegAddr(0x29);
                    pRegTable->SetRegInfo({ 0x00 }, _T("PsLcf"));
                    {
                        pRegTable->SetBitDetail(_T("PsLcf"), _T("Lcof = PsLcf/128"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
                    }

                    pRegTable->SetRegAddr(0x2A);
                    pRegTable->SetRegInfo({ 0x00 }, _T("PsTcfLow"));
                    {
                        pRegTable->SetBitDetail(_T("PsTcfLow"), _T("Tcof = PsTcfLow/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
                    }

                    pRegTable->SetRegAddr(0x2B);
                    pRegTable->SetRegInfo({ 0x00 }, _T("PsTcfHigh"));
                    {
                        pRegTable->SetBitDetail(_T("PsTcfHigh"), _T("Tcof = PsTcfHigh/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
                    }

                    pRegTable->SetRegAddr(0x2C);
                    pRegTable->SetRegInfo({ 0x1A }, _T("IrUnit"));
                    {
                        pRegTable->SetBitDetail(_T("IrUnit"), _T("Ir ADC Time Unit(10 uS)"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x1A);
                    }

                    pRegTable->SetRegAddr(0x2D);
                    pRegTable->SetRegInfo({ 0x00 }, _T("IrLcf"));
                    {
                        pRegTable->SetBitDetail(_T("IrLcf"), _T("Lcof = IrLcf/128"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
                    }

                    pRegTable->SetRegAddr(0x2E);
                    pRegTable->SetRegInfo({ 0x00 }, _T("IrTcfLow"));
                    {
                        pRegTable->SetBitDetail(_T("IrTcfLow"), _T("Tcof = IrTcfLow/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
                    }

                    pRegTable->SetRegAddr(0x2F);
                    pRegTable->SetRegInfo({ 0x00 }, _T("IrTcfHigh"));
                    {
                        pRegTable->SetBitDetail(_T("IrTcfHigh"), _T("Tcof = IrTcfHigh/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
                    }

                    pRegTable->SetRegAddr(0x44);
                    pRegTable->SetRegInfo({ 0xF9 }, _T("PsAdcCtrl"));
                    {
                        pRegTable->SetBitDetail(_T("PsV2i"), _T("Control pin \"pxy_v2i_sel\" at PS ADC"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x0F);
                        pRegTable->SetBitDetail(_T("PsCap"), _T("Control pin \"cap_sel\" at PS ADC"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x09);
                    }

                    pRegTable->SetRegAddr(0x45);
                    pRegTable->SetRegInfo({ 0x63 }, _T("PsTrimCtrl"));
                    {
                        pRegTable->SetBitDetail(_T("PsCnst"), _T("DPCH Trim Constant "), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x06);
                        pRegTable->SetBitDetail(_T("PsFloor"), _T("DPCH Trim floor number for PsPuc"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x03);
                    }

                    pRegTable->SetRegAddr(0x46);
                    pRegTable->SetRegInfo({ 0x00 }, _T("PsDc"));
                    {
                        pRegTable->SetBitDetail(_T("PsDc"), _T("DPCH Trim dc level"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
                    }

                    pRegTable->SetRegAddr(0x48);
                    pRegTable->SetRegInfo({ 0xF9 }, _T("IrAdcCtrl"));
                    {
                        pRegTable->SetBitDetail(_T("IrV2i"), _T("Control pin \"pxy_v2i_sel\" at IR ADC"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x0F);
                        pRegTable->SetBitDetail(_T("IrCap"), _T("Control pin \"cap_sel\" at IR ADC"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x09);
                    }

                    pRegTable->SetRegAddr(0x49);
                    pRegTable->SetRegInfo({ 0x63 }, _T("IrTrimCtrl"));
                    {
                        pRegTable->SetBitDetail(_T("IrCnst"), _T("DPCH Trim Constant "), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x06);
                        pRegTable->SetBitDetail(_T("IrFloor"), _T("DICH Trim floor number for IrPuc"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x03);
                    }

                    pRegTable->SetRegAddr(0x4A);
                    pRegTable->SetRegInfo({ 0x00 }, _T("IrDc"));
                    {
                        pRegTable->SetBitDetail(_T("IrDc"), _T("DPCH Trim dc level"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
                    }

                    pRegTable->SetRegAddr(0x4C);
                    pRegTable->SetRegInfo({ 0x79 }, _T("TmpAdcCtrl"));
                    {
                        pRegTable->SetBitDetail(_T("TmpV2i"), _T("Control pin \"pxy_v2i_sel\" at TMP ADC"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x07);
                        pRegTable->SetBitDetail(_T("TmpCap"), _T("Control pin \"cap_sel\" at TMP ADC"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x09);
                    }

                    pRegTable->SetRegAddr(0x4D);
                    pRegTable->SetRegInfo({ 0x84 }, _T("PkgTrimCtrl"));
                    {
                        pRegTable->SetBitDetail(_T("CpchCnst"), _T("CPCH Trim Constant "), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x08);
                        pRegTable->SetBitDetail(_T("DpucCnst"), _T("DPUC Trim Constant"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x04);
                    }

                    pRegTable->SetRegAddr(0x79);
                    pRegTable->SetRegInfo({ 0x57 }, _T("TTAR"));
                    {
                        pRegTable->SetBitDetail(_T("TTAR"), _T("TmpData Unit= TTAR x 10us"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x57);
                    }

                    pRegTable->SetRegAddr(0x7A);
                    pRegTable->SetRegInfo({ 0xF4, 0x05 }, _T("LTAR"), 2);
                    {
                        pRegTable->SetBitDetail2(_T("LTAR"), { 0xF4, 0x05 }, _T("Define TmpData at 95C for Leak"));
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

                    pRegTable->SetRegAddr(0x80);
                    pRegTable->SetRegInfo({ 0x00 }, _T("DigiCtrl"));
                    {
                        pRegTable->SetBitDetail(_T("FastEn"), 3, _T("Conversion is min"));
                        pRegTable->SetBitDetail(_T("LadcEn"), 2, _T("AmbData = Leak Table"));
                        pRegTable->SetBitDetail(_T("PxshEn"), 1, _T("Enable \"pxsh\" at Pre-heat"));
                        pRegTable->SetBitDetail(_T("MakeEn"), 0, _T("Use Make Data as input"));
                    }

                    pRegTable->SetRegAddr(0x81);
                    pRegTable->SetRegInfo({ 0x0A }, _T("SlotTmp"));
                    {
                        pRegTable->SetBitDetail(_T("SlotTmp"), _T("The Temperature time slot * 200 ms"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x0A);
                    }

                    pRegTable->SetRegAddr(0x82);
                    pRegTable->SetRegInfo({ 0x63 }, _T("PxshCtrl"));
                    {
                        pRegTable->SetBitDetail(_T("PxshHead"), _T("The time slot before pxsh rising"), 0xE0, 5, BOTH_RW, { 0, 0x07 }, 0x02);
                        pRegTable->SetBitDetail(_T("PxshPuw"), _T("The width of pxsh keeping"), 0x1C, 2, BOTH_RW, { 0, 0x07 }, 0x04);
                        pRegTable->SetBitDetail(_T("PxshTail"), _T("The time slot after pxsh falling"), 0x03, 0, BOTH_RW, { 0, 0x03 }, 0x01);
                    }

                    pRegTable->SetRegAddr(0x84);
                    pRegTable->SetRegInfo({ 0x00 }, _T("AnalogA"));
                    {
                        pRegTable->SetBitDetail(_T("ibtest_sel"), 5, _T("Control pin \"ibtest_sel\""));
                        pRegTable->SetBitDetail(_T("test_sel"), 4, _T("Control pin \"test_sel\""));
                        pRegTable->SetBitDetail(_T("ana_test_en"), 3, _T("Control pin \"ana_test_en\""));
                        pRegTable->SetBitDetail(_T("ana_test"), _T("Control pin \"ana_test\""), 0x07, 0, BOTH_RW, { 0, 0x07 });
                    }

                    pRegTable->SetRegAddr(0x85);
                    pRegTable->SetRegInfo({ 0x1E }, _T("AnalogB"));
                    {
                        pRegTable->SetBitDetail(_T("vref_op_sel"), _T("Control pin \"vref_op_sel\""), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x01);
                        pRegTable->SetBitDetail(_T("vtoph_set"), _T("Control pin \"vtoph_set\""), 0x0C, 2, BOTH_RW, { 0, 0x03 }, 0x03);
                        pRegTable->SetBitDetail(_T("clkm_vbs"), _T("Control pin \"clkm_vbs\""), 0x03, 0, BOTH_RW, { 0, 0x03 }, 0x02);
                    }

                    pRegTable->SetRegAddr(0x86);
                    pRegTable->SetRegInfo({ 0x06 }, _T("AnalogC"));
                    {
                        pRegTable->SetBitDetail(_T("ana_reg"), _T("Control pin \"ana_reg\""), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x00);
                        pRegTable->SetBitDetail(_T("IrDark"), 2, _T("Enable \"ir_dark_comp\" at IR"), 0x01);
                        pRegTable->SetBitDetail(_T("PsDark"), 1, _T("Enable \"ir_dark_comp\" at PS"), 0x01);
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
                    pRegTable->SetRegInfo({ 0x05 }, _T("Tbe"));
                    {
                        pRegTable->SetBitDetail(_T("Tbe"), _T("Burn Time"), 0x0F, 0, BOTH_RW, { 0x00, 0x0F }, 0x05);
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
                    pRegTable->SetRegInfo({ 0x01 }, _T("AnalogEnCtrl"));
                    {
                        pRegTable->SetBitDetail(_T("ext_hosc_en"), 6, _T("Control ext_hosc_en when Device ON"));
                        pRegTable->SetBitDetail(_T("hosc_en"), 4, _T("Control hosc_en pin when Device OFF"));
                        pRegTable->SetBitDetail(_T("en_ps"), 1, _T("Control en_ps pin when Device OFF"));
                        pRegTable->SetBitDetail(_T("enb_bg"), 0, _T("Control enb_bg pin when Device OFF"), 0x01);
                    }

                    pRegTable->SetRegAddr(0xEF);
                    pRegTable->SetRegInfo({ 0x28 }, _T("WatchDog"));
                    {
                        pRegTable->SetBitDetail(_T("WatchDog"), _T("Time Out= WatchDog x 0.8 ms"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x28);
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
                    pRegTable->SetBitDetail(_T("NewPsEn"), 4, _T("New PS Enable"));
                    pRegTable->SetBitDetail(_T("IrEn"), 2, _T("IR Enable"));
                    pRegTable->SetBitDetail(_T("PsEn"), 1, _T("PS Enable"));
                }

                pRegTable->SetRegAddr(0xF1);
                pRegTable->SetRegInfo({ 0x03 }, _T("IntCtrl"));
                {
                    pRegTable->SetBitDetail(_T("PushPull"), 7, _T("Enable INT Pin push pull"));
                    pRegTable->SetBitDetail(_T("ObjIntEn"), 6, _T("Obj Int Enable"));
                    pRegTable->SetBitDetail(_T("SyncEn"), 5, _T("Enable INT pin as sync input"));
                    pRegTable->SetBitDetail(_T("DataIntEn"), 4, _T("Data Int Enable"));
                    pRegTable->SetBitDetail(_T("IrIntEn"), 2, _T("IR Int Enable"));
                    pRegTable->SetBitDetail(_T("PsIntEn"), 1, _T("PS Int Enable"), 0x01);
                    pRegTable->SetBitDetail(_T("Reserved0xF1_0"), 0, _T("Reserved"), 0x01);
                }

                pRegTable->SetRegAddr(0xF2);
                pRegTable->SetRegInfo({ 0x00 }, _T("HaltCtrl"));
                {
                    pRegTable->SetBitDetail(_T("ReadClear"), 7, _T("Interrupt clear method"));
                    pRegTable->SetBitDetail(_T("DataHalt"), 4, _T("Data INT Halt"));
                    pRegTable->SetBitDetail(_T("IrHalt"), 2, _T("IR INT Halt"));
                    pRegTable->SetBitDetail(_T("PsHalt"), 1, _T("PS INT Halt"));
                }

                pRegTable->SetRegAddr(0xF3);
                pRegTable->SetRegInfo({ 0x00 }, _T("SysCtrl"));
                {
                    pRegTable->SetBitDetail(_T("FallPorEn"), 7, _T("Enable Falling POR"));
                    pRegTable->SetBitDetail(_T("VbgPuw"), _T(""), 0x70, 4, BOTH_RW, { 0, 0x07 }, 0x00);
                    pRegTable->SetBitDetail(_T("Operation"), 0, _T("Openation Mode"));
                }

                pRegTable->SetRegAddr(0xF4);
                pRegTable->SetRegInfo({ 0x00 }, _T("SwRst"));
                {
                    pRegTable->SetBitDetail(_T("SoftReset"), _T("Software Reset"), _T(""), 0xEE);    //write 0xEE to reset
                }

                pRegTable->SetRegAddr(0xFB);
                pRegTable->SetRegInfo({ 0x00 }, _T("LoscData"));
                {
                    pRegTable->SetBitDetail(_T("LoscData"), _T("LOSC Period= LoscData x 800ns"), 0xFF, 0, ONLY_R);
                }

                pRegTable->RegInfo[0xFC] = CRegInfo({ 0x19 }, _T("IDPod"));
                pRegTable->RegInfo[0xFD] = CRegInfo({ 0x01 }, _T("IDRev"));

                pRegTable->SetRegAddr(0xFE);
                pRegTable->SetRegInfo({ 0x80 }, _T("IntFlag"));
                {
                    pRegTable->SetBitDetail(_T("PorInt"), 7, _T("POR INT"), 1);
                    pRegTable->SetBitDetail(_T("PsInt"), 1, _T("PS INT"));
#ifdef _DEBUG
                    pRegTable->SetBitDetail(_T("DataInt"), 4, _T("Data INT"));
                    pRegTable->SetBitDetail(_T("IrInt"), 2, _T("IR INT"));
#endif
                }

                pRegTable->SetRegAddr(0xFF);
                pRegTable->SetRegInfo({ 0x80 }, _T("StatFlag"));
                {
                    pRegTable->SetBitDetail(_T("Obj"), 7, _T("PS Object"), 1);
                    pRegTable->SetBitDetail(_T("PsAmbErr"), 3, _T("PS ckt Error Flag when Drv Off"));
#ifdef _DEBUG
                    pRegTable->SetBitDetail(_T("IrEnvErr"), 6, _T("IR ckt Error Flag when Drv Off"));
                    pRegTable->SetBitDetail(_T("IrRstErr"), 5, _T("IR ckt Error Flag when reset"));
                    pRegTable->SetBitDetail(_T("PsDrvErr"), 4, _T("PS ckt Error Flag when Drv On"));
                    pRegTable->SetBitDetail(_T("IrErr"), 2, _T("IrData Invalid Flag"));
                    pRegTable->SetBitDetail(_T("PsErr"), 1, _T("PsData Invalid Flag"));
#endif
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

                pRegTable->SetRegAddr(0x60);
                pRegTable->SetRegInfo({ 0x05 }, _T("PsCtrl"));
                {
                    pRegTable->SetBitDetail(_T("PsMean"), _T("PS Mean"), 0xC0, 6, BOTH_RW, { 0, 0x03 }, 0x00);
                    pRegTable->SetBitDetail(_T("PsBits"), _T("Define PsData bits"), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x00);
                    pRegTable->SetBitDetail(_T("PsGain"), _T("PS Gain"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x05);
                }

                pRegTable->SetRegAddr(0x61);
                pRegTable->SetRegInfo({ 0x00 }, _T("PsPuw"));
                {
                    pRegTable->SetBitDetail(_T("PsPuw"), _T("PS Integration Pulse Width"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
                }

                pRegTable->SetRegAddr(0x62);
                pRegTable->SetRegInfo({ 0x02 }, _T("PsPuc"));
                {
                    pRegTable->SetBitDetail(_T("PsPuc"), _T("PS Integration Pulse Count"), 0x3F, 0, BOTH_RW, { 0, 63 }, 0x02);
                }

                pRegTable->SetRegAddr(0x63);
                pRegTable->SetRegInfo({ 0x00 }, _T("PsPreCtrl"));
                {
                    pRegTable->SetBitDetail(_T("PsPrePuw"), _T("PS Pre-Heat Pulse Width"), 0xF0, 4, BOTH_RW, { 0, 15 });
                    pRegTable->SetBitDetail(_T("PsPrePuc"), _T("PS Pre-Heat Pulse Count"), 0x0F, 0, BOTH_RW, { 0, 15 });
                }

                pRegTable->SetRegAddr(0x64);
                pRegTable->SetRegInfo({ 0x01 }, _T("PsDrvCtrl"));
                {
                    pRegTable->SetBitDetail(_T("PsDrvDc"), _T("Driving DC"), 0xC0, 6, BOTH_RW, { 0, 3 });
                    pRegTable->SetBitDetail(_T("PsDrvMax"), 4, _T("Configures the Maximum Driving Current"));
                    pRegTable->SetBitDetail(_T("PsDrv"), _T("PS Driving Current"), 0x0F, 0, BOTH_RW, { 0, 15 }, 0x01);
                }

                pRegTable->SetRegAddr(0x65);
                pRegTable->SetRegInfo({ 0x11 }, _T("PsDacCtrl"));
                {
                    pRegTable->SetBitDetail(_T("PsAmbGain"), _T("PS Ambient Gain"), 0xF0, 4, BOTH_RW, { 0, 15 }, 0x01);
                    pRegTable->SetBitDetail(_T("PsCtGain"), _T("PS CTDAC Gain"), 0x0F, 0, BOTH_RW, { 0, 15 }, 0x01);
                }

                pRegTable->SetRegAddr(0x66);
                pRegTable->SetRegInfo({ 0x00 }, _T("PsAmbDac"));
                {
                    pRegTable->SetBitDetail(_T("PsAmbDac"), _T("PS Ambient DAC"), 0x3F, 0, BOTH_RW, { 0, 0x3F });
                }

                pRegTable->SetRegAddr(0x67);
                pRegTable->SetRegInfo({ 0x00 }, _T("PsCtDac"));
                {
                    pRegTable->SetBitDetail(_T("PsCtDac"), _T("PS Crosstalk DAC"), 0x7F, 0, BOTH_RW, { 0, 96 });
                }

                pRegTable->SetRegAddr(0x68);
                pRegTable->SetRegInfo({ 0x00 }, _T("PsCtPuw"));
                {
                    pRegTable->SetBitDetail(_T("PsCtPuw"), _T("PS Crosstalk DAC Pulse Width"), 0xFF, 0, BOTH_RW, { 0, 0xFF });
                }

                pRegTable->SetRegAddr(0x69);
                pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("PsCal"), 2);
                {
                    pRegTable->SetBitDetail2(_T("PsCal"), { 0x00, 0x00 }, _T(""));
                }

                pRegTable->SetRegAddr(0x6B);
                pRegTable->SetRegInfo({ 0x11 }, _T("PsAlgoCtrl"));
                {
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
                pRegTable->SetRegInfo({ 0x08 }, _T("IrCtrl"));
                {
                    pRegTable->SetBitDetail(_T("IrMean"), _T("IR Mean"), 0xC0, 6, BOTH_RW, { 0, 0x03 }, 0x00);
                    pRegTable->SetBitDetail(_T("IrBits"), _T("Define IrData bits"), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x00);
                    pRegTable->SetBitDetail(_T("IrGain"), _T("IR Gain"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x08);
                }

                pRegTable->SetRegAddr(0x71);
                pRegTable->SetRegInfo({ 0x00 }, _T("IrPuw"));
                {
                    pRegTable->SetBitDetail(_T("IrPuw"), _T("IR Integration Pulse Width"), 0x7F, 0, BOTH_RW, { 0, 0x7F });
                }

                pRegTable->SetRegAddr(0x72);
                pRegTable->SetRegInfo({ 0x02 }, _T("IrPuc"));
                {
                    pRegTable->SetBitDetail(_T("IrPuc"), _T("IR Integration Pulse Count"), 0x3F, 0, BOTH_RW, { 0, 63 }, 0x02);
                }

                pRegTable->SetRegAddr(0x73);
                pRegTable->SetRegInfo({ 0x00 }, _T("IrPreCtrl"));
                {
                    pRegTable->SetBitDetail(_T("IrPrePuw"), _T("IR Pre-Heat Pulse Width"), 0xF0, 4, BOTH_RW, { 0, 15 });
                    pRegTable->SetBitDetail(_T("IrPrePuc"), _T("IR Pre-Heat Pulse Count"), 0x0F, 0, BOTH_RW, { 0, 15 });
                }

                pRegTable->SetRegAddr(0x74);
                pRegTable->SetRegInfo({ 0x00 }, _T("IrDrvCtrl"));
                {
                    pRegTable->SetBitDetail(_T("IrDrvDc"), _T("Driving DC"), 0xC0, 6, BOTH_RW, { 0, 3 });
                    pRegTable->SetBitDetail(_T("IrDrvMax"), 4, _T("Configures the Maximum Driving Current"));
                    pRegTable->SetBitDetail(_T("IrDrv"), _T("IR Driving Current"), 0x0F, 0, BOTH_RW, { 0, 15 }, 0x00);
                }

                pRegTable->SetRegAddr(0x75);
                pRegTable->SetRegInfo({ 0x11 }, _T("IrDacCtrl"));
                {
                    pRegTable->SetBitDetail(_T("IrAmbGain"), _T("IR CTDAC Gain"), 0xF0, 4, BOTH_RW, { 0, 15 }, 0x01);
                    pRegTable->SetBitDetail(_T("IrCtGain"), _T("IR CTDAC Step"), 0x0F, 0, BOTH_RW, { 0, 15 }, 0x01);
                }

                pRegTable->SetRegAddr(0x76);
                pRegTable->SetRegInfo({ 0x00 }, _T("IrAmbDac"));
                {
                    pRegTable->SetBitDetail(_T("IrAmbDac"), _T("IR Ambient DAC"), 0x3F, 0, BOTH_RW, { 0, 0x3F });
                }

                pRegTable->SetRegAddr(0x77);
                pRegTable->SetRegInfo({ 0x00 }, _T("IrCtDac"));
                {
                    pRegTable->SetBitDetail(_T("IrCtDac"), _T("IR Crosstalk DAC"), 0x7F, 0, BOTH_RW, { 0, 96 });
                }

                pRegTable->SetRegAddr(0x78);
                pRegTable->SetRegInfo({ 0x00 }, _T("IrCtPuw"));
                {
                    pRegTable->SetBitDetail(_T("IrCtPuw"), _T("IR Crosstalk DAC Pulse Width"), 0xFF, 0, BOTH_RW, { 0, 0xFF });
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
                    pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("Leak 25"), 2);
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
                    pRegTable->SetRegInfo({ 0x1A }, _T("PsUnit"));
                    {
                        pRegTable->SetBitDetail(_T("PsUnit"), _T("Ps ADC Time Unit(10 uS)"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x1A);
                    }

                    pRegTable->SetRegAddr(0x29);
                    pRegTable->SetRegInfo({ 0x00 }, _T("PsLcf"));
                    {
                        pRegTable->SetBitDetail(_T("PsLcf"), _T("Lcof = PsLcf/128"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
                    }

                    pRegTable->SetRegAddr(0x2A);
                    pRegTable->SetRegInfo({ 0x00 }, _T("PsTcfLow"));
                    {
                        pRegTable->SetBitDetail(_T("PsTcfLow"), _T("Tcof = PsTcfLow/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
                    }

                    pRegTable->SetRegAddr(0x2B);
                    pRegTable->SetRegInfo({ 0x00 }, _T("PsTcfHigh"));
                    {
                        pRegTable->SetBitDetail(_T("PsTcfHigh"), _T("Tcof = PsTcfHigh/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
                    }

                    pRegTable->SetRegAddr(0x2C);
                    pRegTable->SetRegInfo({ 0x1A }, _T("IrUnit"));
                    {
                        pRegTable->SetBitDetail(_T("IrUnit"), _T("Ir ADC Time Unit(10 uS)"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x1A);
                    }

                    pRegTable->SetRegAddr(0x2D);
                    pRegTable->SetRegInfo({ 0x00 }, _T("IrLcf"));
                    {
                        pRegTable->SetBitDetail(_T("IrLcf"), _T("Lcof = IrLcf/128"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
                    }

                    pRegTable->SetRegAddr(0x2E);
                    pRegTable->SetRegInfo({ 0x00 }, _T("IrTcfLow"));
                    {
                        pRegTable->SetBitDetail(_T("IrTcfLow"), _T("Tcof = IrTcfLow/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
                    }

                    pRegTable->SetRegAddr(0x2F);
                    pRegTable->SetRegInfo({ 0x00 }, _T("IrTcfHigh"));
                    {
                        pRegTable->SetBitDetail(_T("IrTcfHigh"), _T("Tcof = IrTcfHigh/64, 2'c"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
                    }

                    pRegTable->SetRegAddr(0x44);
                    pRegTable->SetRegInfo({ 0xF5 }, _T("PsAdcCtrl"));
                    {
                        pRegTable->SetBitDetail(_T("PsV2i"), _T("Control pin \"pxy_v2i_sel\" at PS ADC"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x0F);
                        pRegTable->SetBitDetail(_T("PsCap"), _T("Control pin \"cap_sel\" at PS ADC"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x05);
                    }

                    pRegTable->SetRegAddr(0x45);
                    pRegTable->SetRegInfo({ 0xF3 }, _T("PsTrimCtrl"));
                    {
                        pRegTable->SetBitDetail(_T("PsCnst"), _T("DPCH Trim Constant "), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x0F);
                        pRegTable->SetBitDetail(_T("PsFloor"), _T("DPCH Trim floor number for PsPuc"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x03);
                    }

                    pRegTable->SetRegAddr(0x46);
                    pRegTable->SetRegInfo({ 0x00 }, _T("PsDc"));
                    {
                        pRegTable->SetBitDetail(_T("PsDc"), _T("DPCH Trim dc level"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
                    }

                    pRegTable->SetRegAddr(0x48);
                    pRegTable->SetRegInfo({ 0xF5 }, _T("IrAdcCtrl"));
                    {
                        pRegTable->SetBitDetail(_T("IrV2i"), _T("Control pin \"pxy_v2i_sel\" at IR ADC"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x0F);
                        pRegTable->SetBitDetail(_T("IrCap"), _T("Control pin \"cap_sel\" at IR ADC"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x05);
                    }

                    pRegTable->SetRegAddr(0x49);
                    pRegTable->SetRegInfo({ 0xF3 }, _T("IrTrimCtrl"));
                    {
                        pRegTable->SetBitDetail(_T("IrCnst"), _T("DPCH Trim Constant "), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x0F);
                        pRegTable->SetBitDetail(_T("IrFloor"), _T("DICH Trim floor number for IrPuc"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x03);
                    }

                    pRegTable->SetRegAddr(0x4A);
                    pRegTable->SetRegInfo({ 0x00 }, _T("IrDc"));
                    {
                        pRegTable->SetBitDetail(_T("IrDc"), _T("DPCH Trim dc level"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x00);
                    }

                    pRegTable->SetRegAddr(0x4C);
                    pRegTable->SetRegInfo({ 0x79 }, _T("TmpAdcCtrl"));
                    {
                        pRegTable->SetBitDetail(_T("TmpV2i"), _T("Control pin \"pxy_v2i_sel\" at TMP ADC"), 0xF0, 4, BOTH_RW, { 0, 0x0F }, 0x07);
                        pRegTable->SetBitDetail(_T("TmpCap"), _T("Control pin \"cap_sel\" at TMP ADC"), 0x0F, 0, BOTH_RW, { 0, 0x0F }, 0x09);
                    }

                    pRegTable->SetRegAddr(0x4D);
                    pRegTable->SetRegInfo({ 0x0E }, _T("DpucCnst"));
                    {
                        pRegTable->SetBitDetail(_T("DpucCnst"), _T("DPUC Trim Constant"), 0xFF, 0, BOTH_RW, { 0, 0xFF }, 0x0E);
                    }

                    pRegTable->SetRegAddr(0x4E);
                    pRegTable->SetRegInfo({ 0x13 }, _T("CpchCnst"));
                    {
                        pRegTable->SetBitDetail(_T("CpchCnst"), _T("CPCH Trim Constant "), 0xFF, 0, BOTH_RW, { 0, 0xFF }, 0x13);
                    }

                    pRegTable->SetRegAddr(0x79);
                    pRegTable->SetRegInfo({ 0x5E }, _T("TTAR"));
                    {
                        pRegTable->SetBitDetail(_T("TTAR"), _T("TmpData Unit= TTAR x 10us"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x5E);
                    }

                    pRegTable->SetRegAddr(0x7A);
                    pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("LTAR"), 2);
                    {
                        pRegTable->SetBitDetail2(_T("LTAR"), { 0x00, 0x00 }, _T("Define TmpData at 95C for Leak"));
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

                    pRegTable->SetRegAddr(0x80);
                    pRegTable->SetRegInfo({ 0x00 }, _T("DigiCtrl"));
                    {
                        pRegTable->SetBitDetail(_T("FastTmp"), 4, _T("Out TmpData every Conversion"));
                        pRegTable->SetBitDetail(_T("FastEn"), 3, _T("Conversion is min"));
                        pRegTable->SetBitDetail(_T("LadcEn"), 2, _T("AmbData = Leak Table"));
                        pRegTable->SetBitDetail(_T("PxshEn"), 1, _T("Enable \"pxsh\" at Pre-heat"));
                        pRegTable->SetBitDetail(_T("MakeEn"), 0, _T("Use Make Data as input"));
                    }

                    pRegTable->SetRegAddr(0x81);
                    pRegTable->SetRegInfo({ 0x03 }, _T("TxPuw"));
                    {
                        pRegTable->SetBitDetail(_T("DrvPuw"), _T("The TX turn on time before integration: Time = DrvPuw x 2us + 6us"), 0x0F, 0, BOTH_RW, { 0x00, 0x0F }, 0x03);
                    }

                    pRegTable->SetRegAddr(0x82);
                    pRegTable->SetRegInfo({ 0x51 }, _T("PxshCtrl"));
                    {
                        pRegTable->SetBitDetail(_T("PxshHead"), _T("The time slot before pxsh rising"), 0xE0, 5, BOTH_RW, { 0, 0x07 }, 0x02);
                        pRegTable->SetBitDetail(_T("PxshPuw"), _T("The width of pxsh keeping"), 0x1C, 2, BOTH_RW, { 0, 0x07 }, 0x04);
                        pRegTable->SetBitDetail(_T("PxshTail"), _T("The time slot after pxsh falling"), 0x03, 0, BOTH_RW, { 0, 0x03 }, 0x01);
                    }

                    pRegTable->SetRegAddr(0x84);
                    pRegTable->SetRegInfo({ 0x00 }, _T("AnalogA"));
                    {
                        pRegTable->SetBitDetail(_T("ibtest_sel"), 5, _T("Control pin \"ibtest_sel\""));
                        pRegTable->SetBitDetail(_T("test_sel"), 4, _T("Control pin \"test_sel\""));
                        pRegTable->SetBitDetail(_T("ana_test_en"), 3, _T("Control pin \"ana_test_en\""));
                        pRegTable->SetBitDetail(_T("ana_test"), _T("Control pin \"ana_test\""), 0x07, 0, BOTH_RW, { 0, 0x07 });
                    }

                    pRegTable->SetRegAddr(0x85);
                    pRegTable->SetRegInfo({ 0x1C }, _T("AnalogB"));
                    {
                        pRegTable->SetBitDetail(_T("vref_op_sel"), _T("Control pin \"vref_op_sel\""), 0x30, 4, BOTH_RW, { 0, 0x03 }, 0x01);
                        pRegTable->SetBitDetail(_T("vtoph_set"), _T("Control pin \"vtoph_set\""), 0x0C, 2, BOTH_RW, { 0, 0x03 }, 0x03);
                        pRegTable->SetBitDetail(_T("clkm_vbs"), _T("Control pin \"clkm_vbs\""), 0x03, 0, BOTH_RW, { 0, 0x03 }, 0x00);
                    }

                    pRegTable->SetRegAddr(0x86);
                    pRegTable->SetRegInfo({ 0x06 }, _T("AnalogC"));
                    {
                        pRegTable->SetBitDetail(_T("IrDark"), 2, _T("Enable \"ir_dark_comp\" at IR"), 0x01);
                        pRegTable->SetBitDetail(_T("PsDark"), 1, _T("Enable \"ir_dark_comp\" at PS"), 0x01);
                    }

                    pRegTable->SetRegAddr(0x87);
                    pRegTable->SetRegInfo({ 0x10 }, _T("LOSC"));
                    {
                        pRegTable->SetBitDetail(_T("LOSC"), _T("Control pin \"losc_trim\""), 0x1F, 0, BOTH_RW, { 0x00, 0x1F }, 0x10);
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
                    pRegTable->SetRegInfo({ 0x05 }, _T("Tbe"));
                    {
                        pRegTable->SetBitDetail(_T("Tbe"), _T("Burn Time"), 0x0F, 0, BOTH_RW, { 0x00, 0x0F }, 0x05);
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
                    pRegTable->SetRegInfo({ 0x01 }, _T("AnalogEnCtrl"));
                    {
                        pRegTable->SetBitDetail(_T("ext_hosc_en"), 6, _T("Control ext_hosc_en when Device ON"));
                        pRegTable->SetBitDetail(_T("hosc_en"), 4, _T("Control hosc_en pin when Device OFF"));
                        pRegTable->SetBitDetail(_T("en_ps"), 1, _T("Control en_ps pin when Device OFF"));
                        pRegTable->SetBitDetail(_T("enb_bg"), 0, _T("Control enb_bg pin when Device OFF"), 0x01);
                    }

                    pRegTable->SetRegAddr(0xEF);
                    pRegTable->SetRegInfo({ 0x28 }, _T("WatchDog"));
                    {
                        pRegTable->SetBitDetail(_T("WatchDog"), _T("Time Out= WatchDog x 0.8 ms"), 0xFF, 0, BOTH_RW, { 0x00, 0xFF }, 0x28);
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
        case 10100:
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
        uint8_t Reg0xF0;
        map<CString, CBitDetail>* pBitDetailMap;
        uint8_t FastEn = pRegTable->GetBitValue(_T("FastEn"));

        Reg0xF0 = pRegTable->RegInfo.at(0xF0).RegCurVal.at(0);
        pBitDetailMap = &pRegTable->BitDetail;

        ConversionTime = 0;
        switch (version)
        {
        case 10000:
        case 10100:
            if (Reg0xF0 & pBitDetailMap->at(_T("PsEn")).BitMask.at(0))
            {
                if (FastEn)
                    ConversionTime += 5;
                else
                {
                    switch (pRegTable->GetBitValue(_T("PsMean")))
                    {
                    case 0:    ConversionTime += 30; break;
                    case 1:    ConversionTime += 40; break;
                    case 2:    ConversionTime += 50; break;
                    case 3:    ConversionTime += 100; break;
                    }
                }
            }

            if (Reg0xF0 & pBitDetailMap->at(_T("IrEn")).BitMask.at(0))
            {
                if (FastEn)
                    ConversionTime += 5;
                else
                {
                    switch (pRegTable->GetBitValue(_T("IrMean")))
                    {
                    case 0:    ConversionTime += 30; break;
                    case 1:    ConversionTime += 40; break;
                    case 2:    ConversionTime += 50; break;
                    case 3:    ConversionTime += 100; break;
                    }
                }
            }

            if (ConversionTime > 0)
            {
                ConversionTime += ((double)pRegTable->GetBitValue(_T("WaitTime")) * 10);
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
            double BitsMeanBase[4][4] =
            {
                { 18.0, 21.5, 29.5, 26.4},
                { 20.0, 24.5, 35.3, 33.7},
                { 25.0, 33.3, 48.0, 49.3},
                { 35.5, 47.5, 70.8, 69.0}
            };

            double MeanTime[4] = { 30.0, 40.0, 50.0, 100.0 };
            double BitsFixTimes[4] = { 9.5, 8.6, 6.3, 4.5 };

            if (Reg0xF0 & pBitDetailMap->at(_T("PsEn")).BitMask.at(0))
            {
                uint8_t FastEn = pRegTable->GetBitValue(_T("FastEn"));
                if (FastEn)
                {
                    return 0;
                }

                uint8_t PsPuw = pRegTable->GetBitValue(_T("PsPuw"));
                uint8_t PsPuc = pRegTable->GetBitValue(_T("PsPuc"));
                uint8_t PsPrePuc = pRegTable->GetBitValue(_T("PsPrePuc"));
                uint8_t PsBits = pRegTable->GetBitValue(_T("PsBits"));
                uint8_t PsMean = pRegTable->GetBitValue(_T("PsMean"));
                uint8_t WaitTime = pRegTable->GetBitValue(_T("WaitTime"));
                uint8_t PsDrv = pRegTable->GetBitValue(_T("PsDrv"));
                uint8_t PsDrvMax = pRegTable->GetBitValue(_T("PsDrvMax"));    //16mA, 120mA

                ConversionTime = MeanTime[PsMean] + (double)WaitTime * 10;    //ms

                PowerConsumption = (0.18 * PsPuw + 2.8) * ((double)PsPuc + (double)PsPrePuc) + BitsMeanBase[PsBits][PsMean] - 2.8;    //uA

                if (WaitTime > 0)
                    PowerConsumption = (PowerConsumption * ((double)(MeanTime[PsMean] + BitsFixTimes[PsBits]))
                        + (double)((double)WaitTime * 10) - BitsFixTimes[PsBits])
                    / (double)ConversionTime;    //uA

                if (PsDrv > 0)
                    PowerConsumption += ((double)PsDrv + (PsDrvMax == 0 ? 1 : 0)) * (PsDrvMax == 0 ? 1 : 8) * (double)((pow(2, PsMean) * 2 * (7 + (double)PsPuw) * ((double)PsPuc + (double)PsPrePuc))
                        / (ConversionTime * 1000)) * 1000;    //uA
            }
            else
                PowerConsumption = 0.7; //uA
            break;
        }

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
        uint8_t PsCtDac = 0;
        uint8_t PsDacCtrl = 0;
        uint8_t PsCtGain = 0;
        int16_t Dac_temp = 0;

        //PI Control variable
        bool PI_Control = true;
        int32_t dp = 0;
        int32_t di = 0;
#if 0       // Morris 20220211
        double Kp = 0.015;
        double Ki = 0.02;
#endif
        uint8_t last_try = 0;

        //Bisection method
        uint8_t DacMax = 96;
        uint8_t DacMin = 1;

        uint16_t FullRange = 1 << (PsBits + 9);
        uint16_t TargetPS = FullRange >> 2;

        //Sensor Initial
        uint8_t reg_data[][3] = {
            {0xF0, 0x00, 0x00},    // Shutdown
            {0xF1, 0x01, 0x00},    // No Interrupt Output 
            {0xF2, 0x10, 0x00},    // DataHalt Enable
            {0x4F, 0x00, 0x00},    // WaitTime = 0
            {0xFE, 0x00, 0x00},    // Clear IntFalg
            {0x80, 0x08, 0x00},    // Interanl Setting => Fast En (no show on custom)
        };

        for (uint8_t i = 0; i < sizeof(reg_data) / (sizeof(uint8_t) * 3); i++)
        {
            I2CRead(0, SlaveID, reg_data[i][0], &reg_data[i][2], 1, 0, 0, 1000);
            I2CWrite(0, SlaveID, reg_data[i][0], &reg_data[i][1], 1);
            if (i == 0)
                Sleep(5); //After Sensor Shutdown, Delay 5 ms
        }


        I2CRead(0, SlaveID, 0x65, buff, 3, 0, 0, 1000);

        PsDacCtrl = (buff[0] & 0xF0) | 0x01;
        buff[0] = PsDacCtrl;
        buff[2] = 0x00;

        I2CWrite(0, SlaveID, 0x65, buff, 3);

        PsCtDac = 0;
        PsCtGain = 1;

        buff[0] = 0x02;
        I2CWrite(0, SlaveID, 0xF0, buff, 1);
        Sleep(10); //After Sensor Enable, Delay 10 ms

        while (1)
        {
            I2CRead(0, SlaveID, 0xFE, buff, 4, 0, 0, 1000);
            if ((buff[0] & 0x10) == 0x10)
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

                if (PsCtDac > 0)
                {
                    if (PsData == 0)
                    {
                        DacMax = (uint8_t)PsCtDac;
                        PI_Control = false;
                    }
                    else if (PsData <= TargetPS)
                        break;
                    else if (PsCtDac == DacMin || PsCtDac == DacMax)    //Reduce calcualate time.
                    {
                        break;
                    }
                }
                else if (PsData <= TargetPS)
                    break;

                if (PI_Control)
                {

                    dp = PsData - TargetPS;

                    di += dp;

#if 0           // Morris 20220211
                    Dac_temp = PsCtDac + (int16_t)((Kp * dp) + (Ki * di)) + (dp >= 0 ? 1 : -1);
#else
                    Dac_temp = PsCtDac + (int16_t)((dp >> 6) + ((di >> 6) + (di >> 8))) + (dp >= 0 ? 1 : -1);
#endif

#if 0           // Morris 20220211
                    if (Dac_temp > 96)
#else
                    if (Dac_temp >= 96)
#endif
                    {
                        if (PsCtGain == 0x0F)
                        {
                            last_try = 1;
                            Dac_temp = 96;
                        }
                        else
                        {
#if 0   // Morris 20220211
                            PsCtGain = (uint8_t)((float)PsCtGain * ((float)Dac_temp / 48.0f));
#else
                            if (dp > (TargetPS << 1))
                            {
                                PsCtGain <<= 1;
                            }
                            else if (dp > TargetPS)
                            {
                                PsCtGain += 2;
                            }
                            else
                            {
                                PsCtGain++;
                            }
#endif

                            if (PsCtGain == 0)
                                PsCtGain = 1;
                            else if (PsCtGain > 0x0F)
                                PsCtGain = 0x0F;

                            Dac_temp = 48;

                            PsDacCtrl = (PsDacCtrl & 0xF0) | PsCtGain;
                            I2CWrite(0, SlaveID, 0x65, &PsDacCtrl, 1);
                        }
                    }
                }
                else
                {
                    if (PsData > TargetPS)
                        DacMin = (uint8_t)Dac_temp;

                    if (PsData < FullRange && PsData > TargetPS)    //Reduce calcualate time.
                        Dac_temp += 1;
                    else
                        Dac_temp = (uint16_t)(DacMin + DacMax) >> 1;
                }

                PsCtDac = (uint8_t)Dac_temp;

                I2CWrite(0, SlaveID, 0x67, &PsCtDac, 1);

                buff[0] = 0x00;
                I2CWrite(0, SlaveID, 0xFE, buff, 1);
            }
        }


        pRegTable->RegInfo.at(0x65).RegCurVal.at(0) = PsDacCtrl;
        pRegTable->RegInfo.at(0x67).RegCurVal.at(0) = PsCtDac;

        buff[0] = 0x00;
        I2CWrite(0, 0x1C, 0xF0, buff, 1);    //Shutdown
        Sleep(5); //After Sensor Shutdown, Delay 5 ms

        for (int8_t i = sizeof(reg_data) / (sizeof(uint8_t) * 3); i > 0;)
        {
            i--;
            I2CWrite(0, SlaveID, reg_data[i][0], &reg_data[i][2], 1);
        }
        Sleep(10); //After Sensor Enable, Delay 10 ms

        CString csTemp;
        csTemp.Format(_T("Auto CtDac is Done.\nPsCtGain = %d\nPsCtDac = %d"),
            PsCtGain,
            PsCtDac);

        MessageBoxW(0, csTemp, _T("Calibration Function"), MB_OK);

    }




};
