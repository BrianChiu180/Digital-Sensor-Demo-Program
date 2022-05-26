#pragma once
#include "Define.h"
#include "DA3110T.h"

class CDA3110 : public CSensorInfo {
public:
	CDA3110()
	{
		ModelName = _T("DA3110");
		pDieInfo = new CDA3110T;
#if defined(_DA3110_1000) || defined(_DEBUG) || defined(_DA3110)
		ModelVersion.insert(1000);//0.1
#endif

#if defined(_DEBUG) || defined(_DA3110)
		ModelSelAddress.insert(0x1C);
		ModelSelAddress.insert(0x1D);
		ModelSelAddress.insert(0x1E);
		ModelDefaultAddress = 0x1C;
#endif
	}

	void Init(uint16_t version)
	{
		switch (version) {
		case 1000: {
			DieVersion = 10000;
			pDieInfo->Init(DieVersion);
			pDieDetail = &pDieInfo->DieDetail.at(DieVersion);

			pDieDetail->DieFunc = DF_NONE;
			pDieDetail->DlgStyle[MAIN_DIALOG] = NOSTYLE;
			pDieDetail->DlgName[MAIN_DIALOG] = _T("Main Dialog");
			pCtrlInfo[MAIN_DIALOG] = &pDieDetail->CtrlInfo[MAIN_DIALOG];

			pDieDetail->DlgStyle[TAB_1] = PAGE_STYLE1;
			pDieDetail->DlgName[TAB_1] = _T("Sys Config");
			pCtrlInfo[TAB_1] = &pDieDetail->CtrlInfo[TAB_1];

			pDieDetail->DlgStyle[TAB_2] = PAGE_STYLE1;
			pDieDetail->DlgName[TAB_2] = _T("PS");
			pCtrlInfo[TAB_2] = &pDieDetail->CtrlInfo[TAB_2];

#ifdef _RD
			pDieDetail->DlgStyle[TAB_3] = PAGE_STYLE1;
			pDieDetail->DlgName[TAB_3] = _T("RD");
			pCtrlInfo[TAB_3] = &pDieDetail->CtrlInfo[TAB_3];
#endif
			pDieDetail->DlgStyle[MODEL_1] = MODELLESS1;
			pDieDetail->DlgName[MODEL_1] = _T("Data Progress Bar");
			pCtrlInfo[MODEL_1] = &pDieDetail->CtrlInfo[MODEL_1];

			pDieDetail->DlgStyle[MODEL_3] = MODELLESS_LIST;
			pDieDetail->DlgName[MODEL_3] = _T("Register Table");

			pRegTable = &pDieDetail->RegisterTable;
			{
				pRegTable->DeviceID = 0x1C;

				pRegTable->RegInfo.at(0xF0).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->I2CWriteDelayMs = 10;
						pCtrlDetail->CtrlName = make_pair(_T("PS Enable"), _T(""));
						pCtrlDetail->BitMapping[0] = _T("EnPs");
					}

#ifdef _DEBUG
					DlgCheck.Init(TAB_1, make_pair(0, 5));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->I2CWriteDelayMs = 10;
						pCtrlDetail->CtrlName = make_pair(_T("IR Enable"), _T(""));
						pCtrlDetail->BitMapping[0] = _T("EnIr");
					}
#endif

#ifdef _RD
					DlgCheck.Init(TAB_1, make_pair(0, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->I2CWriteDelayMs = 10;
						pCtrlDetail->BitMapping[0] = _T("EnDyna");
					}

					DlgCheck.Init(TAB_1, make_pair(0, 7));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->I2CWriteDelayMs = 10;
						pCtrlDetail->BitMapping[0] = _T("EnPsAen");
					}
#endif
				}

				pRegTable->RegInfo.at(0xF1).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(6, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ObjIen");
					}

#ifdef _DEBUG
					DlgCheck.Init(TAB_2, make_pair(6, 1));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrIen");
					}
#endif

					DlgCheck.Init(TAB_2, make_pair(6, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsIen");
					}
				}

				pRegTable->RegInfo.at(0xF2).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(6, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ReadClear");
						pCtrlDetail->NameMapping[0] = _T("Manually Clear");
						pCtrlDetail->NameMapping[1] = _T("Auto Clear");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 5));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsHalt");
					}

#ifdef _DEBUG
					DlgCheck.Init(TAB_2, make_pair(6, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrHalt");
					}
#endif
				}

				pRegTable->RegInfo.at(0xF3).bEngMode = FALSE;
				{
#ifdef _RD
					DlgCheck.Init(TAB_3, make_pair(6, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("FallingPor");
					}
#endif
					DlgCheck.Init(TAB_2, make_pair(6, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("Operation");
						pCtrlDetail->NameMapping[0] = _T("Standby Mode");
						pCtrlDetail->NameMapping[1] = _T("Normal Mode");
					}
				}

				pRegTable->RegInfo.at(0xF4).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(4, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = BUTTON_GROUP;
						pCtrlDetail->CtrlName = make_pair(_T("Softwave Reset"), _T(""));
						pCtrlDetail->CtrlFunc = CTRLFUNC_SWRST;
						pCtrlDetail->BitMapping[0] = _T("EnSw");
						pCtrlDetail->I2CWriteDelayMs = 30;
					}
				}

				pRegTable->RegInfo.at(0xFE).bEngMode = FALSE;
				{
					DlgCheck.Init(MAIN_DIALOG, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS"), _T("PS"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PsInt");
					}
#ifdef _DEBUG
					DlgCheck.Init(MAIN_DIALOG, make_pair(1, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("IR"), _T("IR"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("IrInt");
					}
#endif
					DlgCheck.Init(MAIN_DIALOG, make_pair(7, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("POR"), _T("POR"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PorInt");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Clear Interrupt"), _T(""));
						pCtrlDetail->CtrlType = BUTTON_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CLEAR_INT;
						pCtrlDetail->RegMapping[0] = 0xFE;
					}
				}

				pRegTable->RegInfo.at(0xFF).bEngMode = FALSE;
				{
					DlgCheck.Init(MAIN_DIALOG, make_pair(9, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Err"), _T("PS Err"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PsErr");
					}

#ifdef _DEBUG
					DlgCheck.Init(MAIN_DIALOG, make_pair(10, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("IR Err"), _T("IR Err"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("IrErr");
					}
#endif
					DlgCheck.Init(MAIN_DIALOG, make_pair(11, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Ps Err Off"), _T("Ps Err Off"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PsErrOff");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(15, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("OBJ"), _T("OBJ"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PsObj");
					}
				}


				/* PS Data */
				pRegTable->RegInfo.at(0x00).bEngMode = FALSE;
				{

					DlgCheck.Init(MODEL_1, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS"), _T("PS"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = PS_BAR;
						pCtrlDetail->BitMapping[0] = _T("PsCh");
					}

					DlgCheck.Init(TAB_2, make_pair(0, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Data"), _T("PS Data"));
						pCtrlDetail->CtrlType = PROGRESS_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsCh");
					}
				}

#ifdef _DEBUG
				/* IR Data */
				pRegTable->RegInfo.at(0x02).bEngMode = FALSE;
				{

					DlgCheck.Init(MODEL_1, make_pair(1, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("IR"), _T("IR"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = IR_BAR;
						pCtrlDetail->BitMapping[0] = _T("IrCh");
					}
				}
#endif
				pRegTable->RegInfo.at(0x10).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PsAdcTime");
						pCtrlDetail->NameMapping[0] = _T("8-bit, 30 ms");
						pCtrlDetail->NameMapping[1] = _T("9-bit, 35 ms");
						pCtrlDetail->NameMapping[2] = _T("10-bit, 40 ms");
						pCtrlDetail->NameMapping[3] = _T("11-bit, 45 ms");
						pCtrlDetail->NameMapping[4] = _T("12-bit, 50 ms");

						pCtrlDetail->CtrlFunc |= CTRLFUNC_CHANGE_RANGE;
						pCtrlDetail->RegMapping[0] = 0x00;
						pCtrlDetail->RegMapping[1] = 0x1A;
						pCtrlDetail->RegMapping[2] = 0x1C;
						pCtrlDetail->RangeMapping[0] = make_pair(0, 255);
						pCtrlDetail->RangeMapping[1] = make_pair(0, 511);
						pCtrlDetail->RangeMapping[2] = make_pair(0, 1023);
						pCtrlDetail->RangeMapping[3] = make_pair(0, 2047);
						pCtrlDetail->RangeMapping[4] = make_pair(0, 4095);

					}

					DlgCheck.Init(TAB_2, make_pair(0, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PsMean");
						pCtrlDetail->NameMapping[0] = _T("1 Time");
						pCtrlDetail->NameMapping[1] = _T("2 Time");
						pCtrlDetail->NameMapping[2] = _T("4 Time");
						pCtrlDetail->NameMapping[3] = _T("8 Time");
					}
				}


				pRegTable->RegInfo.at(0x11).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Waiting Time"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PsNapTime");
						for (uint8_t i = 0; i < 0xFF; i++)
						{
							csTemp.Format(_T("%d ms"), i * 20);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x12).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsIntAlgo");
						pCtrlDetail->NameMapping[0] = _T("Zone Interrupt Mode");
						pCtrlDetail->NameMapping[1] = _T("Hysterics Interrupt Mode");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsNapAlgo");
						pCtrlDetail->NameMapping[0] = _T("PsNapTime is fixed");
						pCtrlDetail->NameMapping[1] = _T("PsNapTime is variable");
					}
#ifdef _RD
					DlgCheck.Init(TAB_3, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsGain");
					}
#endif
				}

				pRegTable->RegInfo.at(0x13).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsIntPuw");
						pCtrlDetail->NameMapping[0] = _T("1W (Default)");
						for (uint8_t i = 1; i < 0x80; i++)
						{
							csTemp.Format(_T("%d W"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x14).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsIntPuc");
						pCtrlDetail->NameMapping[0] = _T("1 pulse count (Default)");
						for (uint8_t i = 1; i < 0x40; i++)
						{
							csTemp.Format(_T("%d pulse count"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x15).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsPrePuc");
						pCtrlDetail->NameMapping[0] = _T("No Pre-Heat Pulse Count");
						for (uint8_t i = 1; i < 0x10; i++)
						{
							csTemp.Format(_T("%d Pre-Heat Pulse Count"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x16).bEngMode = FALSE;
				{
#ifdef _RD
					DlgCheck.Init(TAB_3, make_pair(0, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsDrvForce");
						pCtrlDetail->NameMapping[0] = _T("Driving Normally (Default)");
						pCtrlDetail->NameMapping[1] = _T("Driving Turn off");
						pCtrlDetail->NameMapping[2] = _T("Force Driving as DC when Operation = 1");
						pCtrlDetail->NameMapping[3] = _T("Driving Normally");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsDrvLed");
						pCtrlDetail->NameMapping[0] = _T("1 Unit =  1 mA");
						pCtrlDetail->NameMapping[1] = _T("1 Unit = 10 mA");
					}
#endif
					DlgCheck.Init(TAB_2, make_pair(4, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Select driving current"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsDrv");
						pCtrlDetail->NameMapping[0] = _T("0 Unit IDrvLed");
						for (uint8_t i = 1; i < 0x10; i++)
						{
							csTemp.Format(_T("%d Unit IDrvLed"), i + 1);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

#ifdef _RD
				pRegTable->RegInfo.at(0x17).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(0, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsCtGain");
						pCtrlDetail->NameMapping[0] = _T("x1");
						pCtrlDetail->NameMapping[1] = _T("x2");
						pCtrlDetail->NameMapping[2] = _T("x3");
					}

					DlgCheck.Init(TAB_3, make_pair(0, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsCtDac");
						for (uint8_t i = 0; i < 0x20; i++)
						{
							csTemp.Format(_T("%d step"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}
#endif
				pRegTable->RegInfo.at(0x18).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsPers");
						pCtrlDetail->NameMapping[0] = _T("Every Cycles");
						for (uint8_t i = 1; i < 0x40; i++)
						{
							csTemp.Format(_T("After %d Cycles"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}

				}

				/* PS Low Threshold */
				pRegTable->RegInfo.at(0x1A).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_2, make_pair(0, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Low Threshold"), _T("PS Low Threshold"));
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsThLow");
					}
				}

				/* PS High Threshold */
				pRegTable->RegInfo.at(0x1C).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_2, make_pair(0, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS High Threshold"), _T("PS High Threshold"));
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsThHigh");
					}
				}

				/* PS Calibration */
				pRegTable->RegInfo.at(0x1E).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_2, make_pair(4, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Calibration"), _T("PS Calibration"));
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsCalb");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = BUTTON_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CALIBRATION;
						pCtrlDetail->BitMapping[0] = _T("PsCalb");
						pCtrlDetail->RegMapping[0] = 0x00;
					}
				}

#ifdef _DEBUG
				pRegTable->RegInfo.at(0x20).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("IrAdcTime");
						pCtrlDetail->NameMapping[0] = _T("8-bit, 30 ms");
						pCtrlDetail->NameMapping[1] = _T("9-bit, 35 ms");
						pCtrlDetail->NameMapping[2] = _T("10-bit, 40 ms");
						pCtrlDetail->NameMapping[3] = _T("11-bit, 45 ms");
						pCtrlDetail->NameMapping[4] = _T("12-bit, 50 ms");

						pCtrlDetail->CtrlFunc |= CTRLFUNC_CHANGE_RANGE;
						pCtrlDetail->RegMapping[0] = 0x02;
						pCtrlDetail->RangeMapping[0] = make_pair(0, 255);
						pCtrlDetail->RangeMapping[1] = make_pair(0, 511);
						pCtrlDetail->RangeMapping[2] = make_pair(0, 1023);
						pCtrlDetail->RangeMapping[3] = make_pair(0, 2047);
						pCtrlDetail->RangeMapping[4] = make_pair(0, 4095);
					}

					DlgCheck.Init(TAB_2, make_pair(2, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("IrMean");
						pCtrlDetail->NameMapping[0] = _T("1 Time");
						pCtrlDetail->NameMapping[1] = _T("2 Time");
						pCtrlDetail->NameMapping[2] = _T("4 Time");
						pCtrlDetail->NameMapping[3] = _T("8 Time");
					}
				}

				pRegTable->RegInfo.at(0x21).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("IR Dummy Time(N x 20 ms)"), _T(""));
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("IrNapTime");
					}
				}
#endif

#ifdef _RD
				pRegTable->RegInfo.at(0x22).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrGain");
					}
				}
#endif

				pRegTable->RegInfo.at(0x23).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrIntPuw");
						pCtrlDetail->NameMapping[0] = _T("1W (Default)");
						for (uint8_t i = 1; i < 0x80; i++)
						{
							csTemp.Format(_T("%d W"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

#ifdef _RD
				pRegTable->RegInfo.at(0x24).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(2, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrIntPuc");
						pCtrlDetail->NameMapping[0] = _T("1C (Default)");
						for (uint8_t i = 1; i < 0x40; i++)
						{
							csTemp.Format(_T("%d C"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}
				pRegTable->RegInfo.at(0x25).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(2, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrPrePuc");
						pCtrlDetail->NameMapping[0] = _T("No Pre-Heat Pulse Count");
						for (uint8_t i = 1; i < 0x10; i++)
						{
							csTemp.Format(_T("%d Pre-Heat Pulse Count"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x26).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(2, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrDrvForce");
						pCtrlDetail->NameMapping[0] = _T("Driving Normally (Default)");
						pCtrlDetail->NameMapping[1] = _T("Driving Turn off");
						pCtrlDetail->NameMapping[2] = _T("Force Driving as DC when Operation = 1");
						pCtrlDetail->NameMapping[3] = _T("Driving Normally");
					}

					DlgCheck.Init(TAB_3, make_pair(2, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrDrv");
						pCtrlDetail->NameMapping[0] = _T("0 Unit IDrvLed");
						for (uint8_t i = 1; i < 0x10; i++)
						{
							csTemp.Format(_T("%d Unit IDrvLed"), i + 1);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x27).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(2, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrCtGain");
						pCtrlDetail->NameMapping[0] = _T("x1");
						pCtrlDetail->NameMapping[1] = _T("x2");
						pCtrlDetail->NameMapping[2] = _T("x3");
					}

					DlgCheck.Init(TAB_3, make_pair(2, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrCtDac");
						for (uint8_t i = 0; i < 0x20; i++)
						{
							csTemp.Format(_T("%d step"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x31).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(4, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ict_dac_enb");
						pCtrlDetail->bActive = FALSE;
					}

					DlgCheck.Init(TAB_3, make_pair(4, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ict_dac");

						for (uint8_t i = 0; i < 0x80; i++)
						{
							csTemp.Format(_T("%d step"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x32).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(6, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ict_dac_sel");
					}

					DlgCheck.Init(TAB_3, make_pair(6, 11));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ibtest_sel");
					}

					DlgCheck.Init(TAB_3, make_pair(6, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("test_sel");
					}

					DlgCheck.Init(TAB_3, make_pair(6, 13));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("temp_mux");
					}

					DlgCheck.Init(TAB_3, make_pair(6, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("en_ana_test");
					}

					DlgCheck.Init(TAB_3, make_pair(6, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ict_dac_sel");
						pCtrlDetail->NameMapping[0] = _T("0x00");
						pCtrlDetail->NameMapping[1] = _T("0x01");
						pCtrlDetail->NameMapping[2] = _T("0x02");
						pCtrlDetail->NameMapping[3] = _T("0x03");
						pCtrlDetail->NameMapping[4] = _T("0x04");
						pCtrlDetail->NameMapping[5] = _T("0x05");
						pCtrlDetail->NameMapping[6] = _T("0x06");
						pCtrlDetail->NameMapping[7] = _T("0x07");
					}
				}

				pRegTable->RegInfo.at(0xD0).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("Mode");
						pCtrlDetail->NameMapping[0] = _T("Normal");
						pCtrlDetail->NameMapping[1] = _T("Leak Mode");
						pCtrlDetail->NameMapping[2] = _T("Gain Mode");
						pCtrlDetail->NameMapping[3] = _T("Dark Mode");
						pCtrlDetail->NameMapping[6] = _T("Burn Mode");
						pCtrlDetail->NameMapping[7] = _T("Bist Mode");
					}
				}
#else
				pRegTable->RegInfo.at(0x31).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ICtDac"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ict_dac");

						for (uint8_t i = 0; i < 0x80; i++)
						{
							csTemp.Format(_T("%d step"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}
#endif
			}

			pRegTable->BitDetail.at(_T("EnDyna")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("EnPs")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("PsDrv")).DefaultVal.at(0) = 11;		//12 mA
			pRegTable->BitDetail.at(_T("PsAdcTime")).DefaultVal.at(0) = 2;	//10 bit
			pRegTable->BitDetail.at(_T("PsIntPuw")).DefaultVal.at(0) = 1;	//1W
			pRegTable->BitDetail.at(_T("PsIntPuc")).DefaultVal.at(0) = 1;	//1C

			//better setting
			pRegTable->BitDetail.at(_T("PsGain")).DefaultVal.at(0) = 0;
			pRegTable->BitDetail.at(_T("AdcUnit")).DefaultVal.at(0) = 0x15;
			pRegTable->BitDetail.at(_T("PsV2iAdc")).DefaultVal.at(0) = 0x0E;
			pRegTable->BitDetail.at(_T("PsCapAdc")).DefaultVal.at(0) = 0x00;

			//enable ictdac
			pRegTable->BitDetail.at(_T("ict_dac_enb")).DefaultVal.at(0) = 0;
			pRegTable->BitDetail.at(_T("ict_dac_sel")).DefaultVal.at(0) = 1;

			pReadTable = &pDieDetail->RegisterTable.ReadTable;
			pReadTable->insert(CReadTable(0xFE, 2));
#ifdef _DEBUG
			pReadTable->insert(CReadTable(0x00, 4, LogDec));
#else
			pReadTable->insert(CReadTable(0x00, 2, LogDec));
#endif
			break;
		}

		}
		CSensorInfo::Init();
	}
};
