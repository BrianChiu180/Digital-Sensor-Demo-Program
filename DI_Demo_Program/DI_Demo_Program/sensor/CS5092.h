#pragma once
#include "Define.h"
#include "DA1990C.h"

class CCS5092 : public CSensorInfo {
public:
	CCS5092() {
		ModelName = _T("CS5092");
#if defined(_CS5092_10000) || defined(_DEBUG) || defined(_CS5092)
		ModelVersion.insert(10000);
#endif

		ModelDefaultAddress = 0x1D;
	}

	void Init(uint16_t version) {
		switch (version) {
		case 10000: {
			pDieInfo = new CDA1990C();
			DieVersion = 10000;
			pDieInfo->Init(DieVersion);
			pDieDetail = &pDieInfo->DieDetail.at(DieVersion);

			pDieDetail->DlgStyle[MAIN_DIALOG] = NOSTYLE;
			pDieDetail->DlgName[MAIN_DIALOG] = _T("Main Dialog");
			pCtrlInfo[MAIN_DIALOG] = &pDieDetail->CtrlInfo[MAIN_DIALOG];

			pDieDetail->DlgStyle[TAB_1] = PAGE_STYLE1;
			pDieDetail->DlgName[TAB_1] = _T("Sys Config");
			pCtrlInfo[TAB_1] = &pDieDetail->CtrlInfo[TAB_1];

			pDieDetail->DlgStyle[TAB_2] = PAGE_STYLE1;
			pDieDetail->DlgName[TAB_2] = _T("Color");
			pCtrlInfo[TAB_2] = &pDieDetail->CtrlInfo[TAB_2];

			pDieDetail->DlgStyle[MODEL_1] = MODELLESS1;
			pDieDetail->DlgName[MODEL_1] = _T("Data Progress Bar");
			pCtrlInfo[MODEL_1] = &pDieDetail->CtrlInfo[MODEL_1];

			//pDieDetail->DieFunc |= DF_LUX;

			//pDieDetail->DlgStyle[MODEL_2] = MODELLESS1;
			//pDieDetail->DlgName[MODEL_2] = _T("Lux(Ref.)");
			//pCtrlInfo[MODEL_2] = &pDieDetail->CtrlInfo[MODEL_2];

			pDieDetail->DlgStyle[MODEL_3] = MODELLESS_LIST;
			pDieDetail->DlgName[MODEL_3] = _T("Register Table");

			pRegTable = &pDieDetail->RegisterTable;
			{
				pRegTable->DeviceID = 0x1D;

				pRegTable->RegInfo.at(0xF0).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->CtrlName = make_pair(_T("ALS Enable"), _T(""));
						pCtrlDetail->BitMapping[0] = _T("AlsEn");
						pCtrlDetail->I2CWriteDelayMs = 10;
					}
				}

				pRegTable->RegInfo.at(0xF1).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(6, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsIntEn");
					}

#ifdef _RD
					DlgCheck.Init(TAB_2, make_pair(6, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("DataIntEn");
					}
#endif
				}

				pRegTable->RegInfo.at(0xF2).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(6, 1));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS Halt Enable"), _T(""));
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsHalt");
					}

#ifdef _RD
					DlgCheck.Init(TAB_2, make_pair(6, 3));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Data Halt Enable"), _T(""));
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("DataHalt");
					}
#endif
					DlgCheck.Init(TAB_2, make_pair(4, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ReadClear");
						pCtrlDetail->NameMapping[0] = _T("Manually Clear");
						pCtrlDetail->NameMapping[1] = _T("Auto Clear");
					}
				}

#ifdef _RD
				pRegTable->RegInfo.at(0xF3).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(2, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("FallPorEn");
					}

					DlgCheck.Init(TAB_1, make_pair(0, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("VbgPuw");
						pCtrlDetail->NameMapping[0] = _T("30 us");
						pCtrlDetail->NameMapping[1] = _T("15 us");
					}

					DlgCheck.Init(TAB_1, make_pair(0, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("Operation");
						pCtrlDetail->NameMapping[0] = _T("Standby Mode");
						pCtrlDetail->NameMapping[1] = _T("Normal Mode");
					}
				}
#endif

				pRegTable->RegInfo.at(0xF4).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(6, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = BUTTON_GROUP;
						pCtrlDetail->CtrlName = make_pair(_T("Softwave Reset"), _T(""));
						pCtrlDetail->CtrlFunc = CTRLFUNC_SWRST;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("SoftReset");
						pCtrlDetail->I2CWriteDelayMs = 30;
					}
				}

#ifdef _DEBUG
				pRegTable->RegInfo.at(0xF5).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(2, 5));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PushPull");
					}

#ifdef _RD
					DlgCheck.Init(TAB_1, make_pair(4, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IoFunc");
						pCtrlDetail->NameMapping[0] = _T("INT Pin is IntFlag Output");
						pCtrlDetail->NameMapping[1] = _T("Int Pin is Obj Output");
						pCtrlDetail->NameMapping[3] = _T("Int Pin is Sync Input");
					}
#endif // _RD
				}
#endif

#ifdef _RD
				pRegTable->RegInfo.at(0xFB).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(4, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("LoscData");
					}
				}
#endif

#ifdef _DEBUG
				pRegTable->RegInfo.at(0xFC).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(4, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Product Code"), _T(""));
						pCtrlDetail->CtrlType = TEXT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IDPod");
					}
				}

				pRegTable->RegInfo.at(0xFD).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(6, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Revision Code"), _T(""));
						pCtrlDetail->CtrlType = TEXT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IDRev");
					}
				}
#endif

				pRegTable->RegInfo.at(0xFE).bEngMode = FALSE;
				{
					DlgCheck.Init(MAIN_DIALOG, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS"), _T("ALS"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("AlsInt");
					}
#ifdef _DEBUG
					DlgCheck.Init(MAIN_DIALOG, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Data"), _T("Data"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("DataInt");
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

					DlgCheck.Init(TAB_1, make_pair(6, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Clear Interrupt"), _T(""));
						pCtrlDetail->CtrlType = BUTTON_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CLEAR_INT;
						pCtrlDetail->RegMapping[0] = 0xFE;
					}
				}

				//Status Flag
				pRegTable->RegInfo.at(0xFF).bEngMode = FALSE;
				{
					DlgCheck.Init(MAIN_DIALOG, make_pair(8, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("AlsErr"), _T("AlsErr"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("AlsErr");
					}

#ifdef _DEBUG
					DlgCheck.Init(MAIN_DIALOG, make_pair(13, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("TmpErr"), _T("TmpErr"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("TmpErr");
					}
#endif // _DEBUG
				}

				/* CH0 Data */
				pRegTable->RegInfo.at(0x04).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("R"), _T("Red"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = R_BAR;
						pCtrlDetail->BitMapping[0] = _T("AlsData0");
					}

					DlgCheck.Init(TAB_2, make_pair(0, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("R"), _T("Red"));
						pCtrlDetail->CtrlType = PROGRESS_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_SELDATA;
						pCtrlDetail->CtrlColor.first = R_BAR;
						pCtrlDetail->BitMapping[0] = _T("AlsData0");
						pCtrlDetail->RegMapping[0] = 0x04;
						pCtrlDetail->RegMapping[1] = 0x06;
						pCtrlDetail->RegMapping[1] = 0x08;
						pCtrlDetail->RegMapping[1] = 0x0A;

					}

					//DlgCheck.Init(MODEL_2, make_pair(0, 0));
					//ASSERT(DlgCheckSet.insert(DlgCheck).second);
					//pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					//{
					//	pCtrlDetail->CtrlName = make_pair(_T("LUX"), _T(""));
					//	pCtrlDetail->CtrlType = TEXT_GROUP;
					//	pCtrlDetail->CtrlFunc = CTRLFUNC_LUX;
					//	pCtrlDetail->BitMapping[0] = _T("AlsData0");
					//}
				}

				/* CH1 Data */
				pRegTable->RegInfo.at(0x06).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(1, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("G"), _T("Green"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = G_BAR;
						pCtrlDetail->BitMapping[0] = _T("AlsData1");
					}
				}

				/* CH2 Data */
				pRegTable->RegInfo.at(0x08).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("B"), _T("Blue"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = B_BAR;
						pCtrlDetail->BitMapping[0] = _T("AlsData2");
					}
				}

				/* CH3 Data */
				pRegTable->RegInfo.at(0x0A).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(3, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("C"), _T("Clean"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = C_BAR;
						pCtrlDetail->BitMapping[0] = _T("AlsData3");
					}
				}

#ifdef _DEBUG
				/* Amb Data */
				pRegTable->RegInfo.at(0x0C).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Amb"), _T("Amb"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = C_BAR;
						pCtrlDetail->BitMapping[0] = _T("AmbData");
					}
				}

				/* Tmp Data */
				pRegTable->RegInfo.at(0x0E).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(5, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Tmp"), _T("Tmp"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = C_BAR;
						pCtrlDetail->BitMapping[0] = _T("TmpData");
					}
				}
#endif

				pRegTable->RegInfo.at(0x4F).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Wait Time"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("WaitTime");
						pCtrlDetail->NameMapping[0] = _T("No Wait Time");
						pCtrlDetail->NameMapping[255] = _T("2550 ms");
						for (uint8_t i = 1; i < 255; i++)
						{
							csTemp.Format(_T("%d ms"), i * 10);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x50).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
#ifdef _DEBUG
						pCtrlDetail->CtrlName = make_pair(_T("AlsGain"), _T(""));
#else
						pCtrlDetail->CtrlName = make_pair(_T("AlsGain"), _T(""));
#endif // _DEBUG
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsGain");
						pCtrlDetail->NameMapping[0] = _T("x1");
						pCtrlDetail->NameMapping[1] = _T("x2");
						pCtrlDetail->NameMapping[2] = _T("x4, Default");
						pCtrlDetail->NameMapping[3] = _T("x8");
						pCtrlDetail->NameMapping[4] = _T("x16");
						pCtrlDetail->NameMapping[5] = _T("x32");
						pCtrlDetail->NameMapping[6] = _T("x64");
					}
				}

				pRegTable->RegInfo.at(0x52).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS Covnersion Time"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("AlsPuc");
						pCtrlDetail->NameMapping[0] = _T("100 ms, Default");
#ifdef _DEBUG
						for (uint8_t i = 1; i < 32; i++)
#else
						for (uint8_t i = 1; i < 16; i++)
#endif // _DEBUG
						{
							csTemp.Format(_T("%d ms"), i * 100);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

#ifdef _DEBUG
				pRegTable->RegInfo.at(0x55).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("AlsPuw0");
						pCtrlDetail->NameMapping[0] = _T("Disable AlsData0");
						for (uint8_t i = 1; i < 128; i++)
						{
							csTemp.Format(_T("%d ms"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
						pCtrlDetail->NameMapping[50] = _T("50 ms, Default");
					}
				}

				pRegTable->RegInfo.at(0x56).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("AlsPuw1");
						pCtrlDetail->NameMapping[0] = _T("Disable AlsData1");
						for (uint8_t i = 1; i < 128; i++)
						{
							csTemp.Format(_T("%d ms"), i);
							pCtrlDetail->NameMapping[0] = csTemp;
						}
						pCtrlDetail->NameMapping[50] = _T("50 ms, Default");
					}
				}

				pRegTable->RegInfo.at(0x57).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("AlsPuw2");
						pCtrlDetail->NameMapping[0] = _T("Disable AlsData2");
						for (uint8_t i = 1; i < 128; i++)
						{
							csTemp.Format(_T("%d ms"), i);
							pCtrlDetail->NameMapping[0] = csTemp;
						}
						pCtrlDetail->NameMapping[50] = _T("50 ms, Default");
					}
				}

				pRegTable->RegInfo.at(0x58).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("AlsPuw3");
						pCtrlDetail->NameMapping[0] = _T("Disable AlsData3");
						for (uint8_t i = 1; i < 128; i++)
						{
							csTemp.Format(_T("%d ms"), i);
							pCtrlDetail->NameMapping[0] = csTemp;
						}
						pCtrlDetail->NameMapping[50] = _T("50 ms, Default");
					}
				}
#endif // _DEBUG

				pRegTable->RegInfo.at(0x5B).bEngMode = FALSE;
				{
#ifdef _DEBUG
					DlgCheck.Init(TAB_2, make_pair(0, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_SELDATA;
						pCtrlDetail->BitMapping[0] = _T("AlsIntSrc");
						pCtrlDetail->NameMapping[0] = _T("Red as AlsData");
						pCtrlDetail->NameMapping[1] = _T("Green as AlsData");
						pCtrlDetail->NameMapping[1] = _T("Blue as AlsData");
						pCtrlDetail->NameMapping[1] = _T("Clean as AlsData");
						pCtrlDetail->RegMapping[0] = 0x04;
						pCtrlDetail->RegMapping[1] = 0x06;
						pCtrlDetail->RegMapping[2] = 0x08;
						pCtrlDetail->RegMapping[3] = 0x0A;
					}
#endif
					DlgCheck.Init(TAB_2, make_pair(0, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsPers");
						pCtrlDetail->NameMapping[0] = _T("Every Cycles");
						for (uint8_t i = 1; i < 0x10; i++)
						{
							csTemp.Format(_T("After %d Cycles"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				/* ALS Low Threshold */
				pRegTable->RegInfo.at(0x5C).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS Low Threshold"), _T("ALS Low Threshold"));
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsThLow");
					}
				}

				/* ALS High Threshold */
				pRegTable->RegInfo.at(0x5E).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_2, make_pair(0, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS High Threshold"), _T("ALS High Threshold"));
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsThHigh");
					}
				}

#ifdef _RD
				pRegTable->RegInfo.at(0xD0).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(0, 2));
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
#endif
			}

			//pLuxCalculate = &pDieDetail->LuxCalculate;
			//{
			//	pLuxCalculate->LuxFunc = TwoCH;
			//	pLuxCalculate->DataRegMapping[0] = 0x00;
			//	pLuxCalculate->DataRegMapping[1] = 0x02;
			//	pLuxCalculate->RatioBitMapping[0] = _T("AlsGain0");
			//	{
			//		pLuxCalculate->CountRatioMapping[0][0] = 4.0;
			//		pLuxCalculate->CountRatioMapping[0][1] = 1.0;
			//		pLuxCalculate->CountRatioMapping[0][2] = 4.0 / 20.0;
			//		pLuxCalculate->CountRatioMapping[0][3] = 4.0 / 125.0;
			//	}

			//	pLuxCalculate->RatioBitMapping[1] = _T("AlsGain1");
			//	{
			//		pLuxCalculate->CountRatioMapping[1][0] = 2.0;
			//		pLuxCalculate->CountRatioMapping[1][1] = 1.0;
			//	}

			//	pLuxCalculate->RatioBitMapping[2] = _T("AlsPuc");
			//	for (int i = 0; i < 256; i++)
			//		pLuxCalculate->CountRatioMapping[2][i] = 64.0 / ((double)i + 1);

			//	//pLuxCalculate->Count2LuxMapping[0.5] = make_pair(0.2113, 0.0);
			//	pLuxCalculate->Count2LuxMapping[0] = make_pair(2.54, 0.0);
			//}

			pRegTable->BitDetail.at(_T("AlsGain")).DefaultVal.at(0) = 0x06;
			pRegTable->BitDetail.at(_T("AlsPuc")).DefaultVal.at(0) = 0x02;
			pRegTable->BitDetail.at(_T("AlsEn")).DefaultVal.at(0) = 0x01;

			pReadTable = &pDieDetail->RegisterTable.ReadTable;
			pReadTable->insert(CReadTable(0xFE, 2));
			pReadTable->insert(CReadTable(0x04, 8, LogDec));
//			pReadTable->insert(CReadTable(0x06, 2, LogDec));
//			pReadTable->insert(CReadTable(0x08, 2, LogDec));
//			pReadTable->insert(CReadTable(0x0A, 2, LogDec));
#ifdef _RD
			pReadTable->insert(CReadTable(0x0C, 4, LogDec));
#endif
			break;
		}
		}

		CSensorInfo::Init();
	}
};