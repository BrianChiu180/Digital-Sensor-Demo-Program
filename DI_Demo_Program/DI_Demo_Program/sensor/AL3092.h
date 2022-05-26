#pragma once
#include "Define.h"
#include "DA3290.h"

class CAL3092 : public CSensorInfo {
public:
	CAL3092()
	{
		ModelName = _T("AL3092");
		pDieInfo = new CDA3290();
#if defined(_AL3092_10000) 
		ModelVersion.insert(10000);
#elif defined(_AL3092_10100)
		ModelVersion.insert(10100);
#elif defined(_AL3092_10200)
		ModelVersion.insert(10200);
#elif defined(_DEBUG) || defined(_AL3092)
		ModelVersion.insert(10000);
		ModelVersion.insert(10100);
		ModelVersion.insert(10200);
#endif
		ModelDefaultAddress = 0x1C;
	}

	void Init(uint16_t version) {
		switch (version) {
		case 10000: {
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
			pDieDetail->DlgName[TAB_2] = _T("ALS");
			pCtrlInfo[TAB_2] = &pDieDetail->CtrlInfo[TAB_2];

			pDieDetail->DlgStyle[MODEL_1] = MODELLESS1;
			pDieDetail->DlgName[MODEL_1] = _T("Data Progress Bar");
			pCtrlInfo[MODEL_1] = &pDieDetail->CtrlInfo[MODEL_1];

			pDieDetail->DieFunc |= DF_LUX;

			pDieDetail->DlgStyle[MODEL_2] = MODELLESS1;
			pDieDetail->DlgName[MODEL_2] = _T("Lux(Ref.)");
			pCtrlInfo[MODEL_2] = &pDieDetail->CtrlInfo[MODEL_2];

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
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->CtrlName = make_pair(_T("ALS Enable"), _T(""));
						pCtrlDetail->BitMapping[0] = _T("AlsEn");
						pCtrlDetail->I2CWriteDelayMs = 10;
					}
				}

				pRegTable->RegInfo.at(0xF1).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(6, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsIntEn");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("DataIntEn");
					}
				}

				pRegTable->RegInfo.at(0xF2).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(6, 7));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS Halt Enable"), _T(""));
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsHalt");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 9));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Data Halt Enable"), _T(""));
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("DataHalt");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ReadClear");
						pCtrlDetail->NameMapping[0] = _T("Manually Clear");
						pCtrlDetail->NameMapping[1] = _T("Auto Clear");
					}
				}

				pRegTable->RegInfo.at(0xF4).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(6, 8));
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
				DlgCheck.Init(TAB_1, make_pair(2, 4));
				ASSERT(DlgCheckSet.insert(DlgCheck).second);
				pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
				{
					pCtrlDetail->CtrlType = CHECK_GROUP;
					pCtrlDetail->BitMapping[0] = _T("PushPull");
				}
#endif // _DEBUG

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

					DlgCheck.Init(MAIN_DIALOG, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Data"), _T("Data"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("DataInt");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(7, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("POR"), _T("POR"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PorInt");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 10));
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
					DlgCheck.Init(MAIN_DIALOG, make_pair(15, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("TmpErr"), _T("TepErr"));
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
						pCtrlDetail->CtrlName = make_pair(_T("Als0"), _T("AlsData0"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = G_BAR;
						pCtrlDetail->BitMapping[0] = _T("AlsData0");
					}

					DlgCheck.Init(TAB_2, make_pair(0, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Als Data0"), _T("Als Data0"));
						pCtrlDetail->CtrlType = PROGRESS_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_SELDATA;
						pCtrlDetail->CtrlColor.first = G_BAR;
						pCtrlDetail->BitMapping[0] = _T("AlsData0");
						pCtrlDetail->RegMapping[0] = 0x04;
						pCtrlDetail->RegMapping[1] = 0x06;
					}

					DlgCheck.Init(MODEL_2, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("LUX"), _T(""));
						pCtrlDetail->CtrlType = TEXT_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_LUX;
						pCtrlDetail->BitMapping[0] = _T("AlsData0");
					}
				}

				/* CH1 Data */
				pRegTable->RegInfo.at(0x06).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(1, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Als1"), _T("AlsData1"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = R_BAR;
						pCtrlDetail->BitMapping[0] = _T("AlsData1");
					}
				}

#ifdef _DEBUG
				/* Amb Data */
				pRegTable->RegInfo.at(0x0C).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(2, 0));
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
					DlgCheck.Init(MODEL_1, make_pair(3, 0));
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

#ifdef _DEBUG
				pRegTable->RegInfo.at(0x47).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("DarkTrim"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("DarkTrim");
						pCtrlDetail->NameMapping[0] = _T("Off");
						for (uint8_t i = 1; i < 16; i++)
						{
							csTemp.Format(_T("x%d"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
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
						pCtrlDetail->CtrlName = make_pair(_T("AlsGain0"), _T(""));
#else
						pCtrlDetail->CtrlName = make_pair(_T("AlsGain"), _T(""));
#endif // _DEBUG
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsGain0");
						pCtrlDetail->NameMapping[0] = _T("x1");
						pCtrlDetail->NameMapping[1] = _T("x2");
						pCtrlDetail->NameMapping[2] = _T("x4");
						pCtrlDetail->NameMapping[3] = _T("x8");
						pCtrlDetail->NameMapping[4] = _T("x16");
						pCtrlDetail->NameMapping[5] = _T("x32");
						pCtrlDetail->NameMapping[6] = _T("x64");
				}

#ifdef _DEBUG
					DlgCheck.Init(TAB_2, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("AlsGain1"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsGain1");
						pCtrlDetail->NameMapping[0] = _T("x1");
						pCtrlDetail->NameMapping[1] = _T("x2");
						pCtrlDetail->NameMapping[2] = _T("x4");
						pCtrlDetail->NameMapping[3] = _T("x8");
						pCtrlDetail->NameMapping[4] = _T("x16");
						pCtrlDetail->NameMapping[5] = _T("x32");
						pCtrlDetail->NameMapping[6] = _T("x64");
					}
#endif // _DEBUG
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
						pCtrlDetail->BitMapping[1] = _T("AlsTurbo");
						pCtrlDetail->NameMapping2[make_pair(0, 0)] = _T("100 ms(0x00)");
						pCtrlDetail->NameMapping2[make_pair(0, 1)] = _T("10 ms(0x00)");
#ifdef _DEBUG
						for (uint8_t i = 1; i < 32; i++)
#else
						for (uint8_t i = 1; i < 16; i++)
#endif // _DEBUG
						{
							csTemp.Format(_T("%d ms"), i * 100);
							pCtrlDetail->NameMapping2[make_pair(i, 0)] = csTemp;
							csTemp.Format(_T("%d ms"), i * 10);
							pCtrlDetail->NameMapping2[make_pair(i, 1)] = csTemp;
						}
					}
				}

#ifdef _DEBUG
				pRegTable->RegInfo.at(0x55).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("AlsPuw0");
						pCtrlDetail->BitMapping[1] = _T("AlsTurbo");
						pCtrlDetail->NameMapping2[make_pair(0, 0)] = _T("Disable AlsData0");
						pCtrlDetail->NameMapping2[make_pair(0, 1)] = _T("Disable AlsData0");
						for (uint8_t i = 1; i < 128; i++)
						{
							csTemp.Format(_T("%d ms integration widths"), i);
							pCtrlDetail->NameMapping2[make_pair(i, 0)] = csTemp;
							csTemp.Format(_T("%.1f ms integration widths"), (float)i * 0.1);
							pCtrlDetail->NameMapping2[make_pair(i, 1)] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x56).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("AlsPuw1");
						pCtrlDetail->BitMapping[1] = _T("AlsTurbo");
						pCtrlDetail->NameMapping2[make_pair(0, 0)] = _T("Disable AlsData1");
						pCtrlDetail->NameMapping2[make_pair(0, 1)] = _T("Disable AlsData1");
						for (uint8_t i = 1; i < 128; i++)
						{
							csTemp.Format(_T("%d ms integration widths"), i);
							pCtrlDetail->NameMapping2[make_pair(i, 0)] = csTemp;
							csTemp.Format(_T("%.1f ms integration widths"), (float)i * 0.1);
							pCtrlDetail->NameMapping2[make_pair(i, 1)] = csTemp;
						}
					}
				}
#endif // _DEBUG

				pRegTable->RegInfo.at(0x5B).bEngMode = FALSE;
				{
#ifdef _DEBUG
					DlgCheck.Init(TAB_2, make_pair(6, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS Turbo(x10)"), _T(""));
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("AlsTurbo");
					}


					DlgCheck.Init(TAB_2, make_pair(0, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_SELDATA;
						pCtrlDetail->BitMapping[0] = _T("AlsIntSrc");
						pCtrlDetail->NameMapping[0] = _T("Als Data0");
						pCtrlDetail->NameMapping[1] = _T("Als Data1");
						pCtrlDetail->RegMapping[0] = 0x04;
						pCtrlDetail->RegMapping[1] = 0x06;
					}

#endif // _DEBUG
					DlgCheck.Init(TAB_2, make_pair(2, 10));
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
			}

			pLuxCalculate = &pDieDetail->LuxCalculate;
			{
				pLuxCalculate->LuxFunc = TwoCH_New;
				pLuxCalculate->DataRegMapping[0] = 0x04;
				pLuxCalculate->DataRegMapping[1] = 0x06;
				pLuxCalculate->DataRatioBitMapping[0][0] = _T("AlsGain0");
				{
					for (int i = 0; i < 7; i++)
						pLuxCalculate->DataCountRatioMapping[0][make_pair(0, i)] = 1.0 / (double)(1 << i);
				}

				pLuxCalculate->DataRatioBitMapping[0][1] = _T("AlsPuw0");
				{
					pLuxCalculate->DataCountRatioMapping[0][make_pair(1, 0)] = 0.0;
					for (int i = 1; i < 0x80; i++)
						pLuxCalculate->DataCountRatioMapping[0][make_pair(1, i)] = 41.0 / i;
				}

				pLuxCalculate->DataRatioBitMapping[1][0] = _T("AlsGain1");
				{
					for (int i = 0; i < 7; i++)
						pLuxCalculate->DataCountRatioMapping[1][make_pair(0, i)] = 1.0 / (double)(1 << i);
				}

				pLuxCalculate->DataRatioBitMapping[1][1] = _T("AlsPuw1");
				{
					pLuxCalculate->DataCountRatioMapping[1][make_pair(1, 0)] = 0.0;
					for (int i = 1; i < 0x80; i++)
						pLuxCalculate->DataCountRatioMapping[1][make_pair(1, i)] = 10.0 / (double)i;
				}

				pLuxCalculate->RatioBitMapping[0] = _T("AlsPuc");
				{
					pLuxCalculate->CountRatioMapping[0][0] = 1.0;

					for (int i = 1; i < 0x20; i++)
						pLuxCalculate->CountRatioMapping[0][i] = 1.0 / ((double)i);
				}

				pLuxCalculate->Lux_Coef_a = 0;
				pLuxCalculate->Lux_Coef_b = 2.23984;
				pLuxCalculate->Lux_Coef_c = -2.5023;
			}

			pRegTable->BitDetail.at(_T("AlsPuc")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("AlsEn")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("AlsPuc")).DefaultVal.at(0) = 0x04;

			//pRegTable->BitDetail.at(_T("DarkTrim")).DefaultVal.at(0) = 0x00;

			pReadTable = &pDieDetail->RegisterTable.ReadTable;
			pReadTable->insert(CReadTable(0xFE, 2));
			pReadTable->insert(CReadTable(0x04, 4, LogDec));
			break;
		}
		case 10100: {
			DieVersion = 10100;
			pDieInfo->Init(DieVersion);
			pDieDetail = &pDieInfo->DieDetail.at(DieVersion);

			pDieDetail->DlgStyle[MAIN_DIALOG] = NOSTYLE;
			pDieDetail->DlgName[MAIN_DIALOG] = _T("Main Dialog");
			pCtrlInfo[MAIN_DIALOG] = &pDieDetail->CtrlInfo[MAIN_DIALOG];

			pDieDetail->DlgStyle[TAB_1] = PAGE_STYLE1;
			pDieDetail->DlgName[TAB_1] = _T("Sys Config");
			pCtrlInfo[TAB_1] = &pDieDetail->CtrlInfo[TAB_1];

			pDieDetail->DlgStyle[TAB_2] = PAGE_STYLE1;
			pDieDetail->DlgName[TAB_2] = _T("ALS");
			pCtrlInfo[TAB_2] = &pDieDetail->CtrlInfo[TAB_2];

			pDieDetail->DlgStyle[MODEL_1] = MODELLESS1;
			pDieDetail->DlgName[MODEL_1] = _T("Data Progress Bar");
			pCtrlInfo[MODEL_1] = &pDieDetail->CtrlInfo[MODEL_1];

			pDieDetail->DieFunc |= DF_LUX;

			pDieDetail->DlgStyle[MODEL_2] = MODELLESS1;
			pDieDetail->DlgName[MODEL_2] = _T("Lux(Ref.)");
			pCtrlInfo[MODEL_2] = &pDieDetail->CtrlInfo[MODEL_2];

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
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->CtrlName = make_pair(_T("ALS Enable"), _T(""));
						pCtrlDetail->BitMapping[0] = _T("AlsEn");
						pCtrlDetail->I2CWriteDelayMs = 10;
					}
				}

				pRegTable->RegInfo.at(0xF1).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(6, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsIntEn");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("DataIntEn");
					}
				}

				pRegTable->RegInfo.at(0xF2).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(6, 7));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS Halt Enable"), _T(""));
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsHalt");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 9));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Data Halt Enable"), _T(""));
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("DataHalt");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ReadClear");
						pCtrlDetail->NameMapping[0] = _T("Manually Clear");
						pCtrlDetail->NameMapping[1] = _T("Auto Clear");
					}
				}

				pRegTable->RegInfo.at(0xF4).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(6, 8));
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
				DlgCheck.Init(TAB_1, make_pair(2, 4));
				ASSERT(DlgCheckSet.insert(DlgCheck).second);
				pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
				{
					pCtrlDetail->CtrlType = CHECK_GROUP;
					pCtrlDetail->BitMapping[0] = _T("PushPull");
				}
#endif // _DEBUG

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

					DlgCheck.Init(MAIN_DIALOG, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Data"), _T("Data"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("DataInt");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(7, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("POR"), _T("POR"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PorInt");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 10));
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
					DlgCheck.Init(MAIN_DIALOG, make_pair(15, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("TmpErr"), _T("TepErr"));
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
						pCtrlDetail->CtrlName = make_pair(_T("Als0"), _T("AlsData0"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = G_BAR;
						pCtrlDetail->BitMapping[0] = _T("AlsData0");
					}

					DlgCheck.Init(TAB_2, make_pair(0, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Als Data0"), _T("Als Data0"));
						pCtrlDetail->CtrlType = PROGRESS_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_SELDATA;
						pCtrlDetail->CtrlColor.first = G_BAR;
						pCtrlDetail->BitMapping[0] = _T("AlsData0");
						pCtrlDetail->RegMapping[0] = 0x04;
						pCtrlDetail->RegMapping[1] = 0x06;
					}

					DlgCheck.Init(MODEL_2, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("LUX"), _T(""));
						pCtrlDetail->CtrlType = TEXT_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_LUX;
						pCtrlDetail->BitMapping[0] = _T("AlsData0");
					}
				}

				/* CH1 Data */
				pRegTable->RegInfo.at(0x06).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(1, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Als1"), _T("AlsData1"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = R_BAR;
						pCtrlDetail->BitMapping[0] = _T("AlsData1");
					}
				}

#ifdef _DEBUG
				/* Amb Data */
				pRegTable->RegInfo.at(0x0C).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(2, 0));
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
					DlgCheck.Init(MODEL_1, make_pair(3, 0));
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

#ifdef _DEBUG
				pRegTable->RegInfo.at(0x47).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("DarkTrim"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("DarkTrim");
						pCtrlDetail->NameMapping[0] = _T("Off");
						for (uint8_t i = 1; i < 16; i++)
						{
							csTemp.Format(_T("x%d"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
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
						pCtrlDetail->CtrlName = make_pair(_T("AlsGain0"), _T(""));
#else
						pCtrlDetail->CtrlName = make_pair(_T("AlsGain"), _T(""));
#endif // _DEBUG
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsGain0");
						pCtrlDetail->NameMapping[0] = _T("x1");
						pCtrlDetail->NameMapping[1] = _T("x2");
						pCtrlDetail->NameMapping[2] = _T("x4");
						pCtrlDetail->NameMapping[3] = _T("x8");
						pCtrlDetail->NameMapping[4] = _T("x16");
						pCtrlDetail->NameMapping[5] = _T("x32");
						pCtrlDetail->NameMapping[6] = _T("x64");
					}

#ifdef _DEBUG
					DlgCheck.Init(TAB_2, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("AlsGain1"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsGain1");
						pCtrlDetail->NameMapping[0] = _T("x1");
						pCtrlDetail->NameMapping[1] = _T("x2");
						pCtrlDetail->NameMapping[2] = _T("x4");
						pCtrlDetail->NameMapping[3] = _T("x8");
						pCtrlDetail->NameMapping[4] = _T("x16");
						pCtrlDetail->NameMapping[5] = _T("x32");
						pCtrlDetail->NameMapping[6] = _T("x64");
					}
#endif // _DEBUG
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
						pCtrlDetail->BitMapping[1] = _T("AlsTurbo");
						pCtrlDetail->NameMapping2[make_pair(0, 0)] = _T("100 ms(0x00)");
						pCtrlDetail->NameMapping2[make_pair(0, 1)] = _T("10 ms(0x00)");
#ifdef _DEBUG
						for (uint8_t i = 1; i < 32; i++)
#else
						for (uint8_t i = 1; i < 16; i++)
#endif // _DEBUG
						{
							csTemp.Format(_T("%d ms"), i * 100);
							pCtrlDetail->NameMapping2[make_pair(i, 0)] = csTemp;
							csTemp.Format(_T("%d ms"), i * 10);
							pCtrlDetail->NameMapping2[make_pair(i, 1)] = csTemp;
						}
					}
				}

#ifdef _DEBUG
				pRegTable->RegInfo.at(0x55).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("AlsPuw0");
						pCtrlDetail->BitMapping[1] = _T("AlsTurbo");
						pCtrlDetail->NameMapping2[make_pair(0, 0)] = _T("Disable AlsData0");
						pCtrlDetail->NameMapping2[make_pair(0, 1)] = _T("Disable AlsData0");
						for (uint8_t i = 1; i < 128; i++)
						{
							csTemp.Format(_T("%d ms integration widths"), i);
							pCtrlDetail->NameMapping2[make_pair(i, 0)] = csTemp;
							csTemp.Format(_T("%.1f ms integration widths"), (float)i * 0.1);
							pCtrlDetail->NameMapping2[make_pair(i, 1)] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x56).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("AlsPuw1");
						pCtrlDetail->BitMapping[1] = _T("AlsTurbo");
						pCtrlDetail->NameMapping2[make_pair(0, 0)] = _T("Disable AlsData1");
						pCtrlDetail->NameMapping2[make_pair(0, 1)] = _T("Disable AlsData1");
						for (uint8_t i = 1; i < 128; i++)
						{
							csTemp.Format(_T("%d ms integration widths"), i);
							pCtrlDetail->NameMapping2[make_pair(i, 0)] = csTemp;
							csTemp.Format(_T("%.1f ms integration widths"), (float)i * 0.1);
							pCtrlDetail->NameMapping2[make_pair(i, 1)] = csTemp;
						}
					}
				}
#endif // _DEBUG

				pRegTable->RegInfo.at(0x5B).bEngMode = FALSE;
				{
#ifdef _DEBUG
					DlgCheck.Init(TAB_2, make_pair(6, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS Turbo(x10)"), _T(""));
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("AlsTurbo");
					}

					DlgCheck.Init(TAB_2, make_pair(0, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_SELDATA;
						pCtrlDetail->BitMapping[0] = _T("AlsIntSrc");
						pCtrlDetail->NameMapping[0] = _T("Als Data0");
						pCtrlDetail->NameMapping[1] = _T("Als Data1");
						pCtrlDetail->RegMapping[0] = 0x04;
						pCtrlDetail->RegMapping[1] = 0x06;
					}
#endif // _DEBUG

					DlgCheck.Init(TAB_2, make_pair(2, 10));
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
			}

			pLuxCalculate = &pDieDetail->LuxCalculate;
			{
				pLuxCalculate->LuxFunc = TwoCH_New;
				pLuxCalculate->DataRegMapping[0] = 0x04;
				pLuxCalculate->DataRegMapping[1] = 0x06;
				pLuxCalculate->DataRatioBitMapping[0][0] = _T("AlsGain0");
				{
					for (int i = 0; i < 7; i++)
						pLuxCalculate->DataCountRatioMapping[0][make_pair(0, i)] = 1.0 / (double)(1 << i);
				}

				pLuxCalculate->DataRatioBitMapping[0][1] = _T("AlsPuw0");
				{
					pLuxCalculate->DataCountRatioMapping[0][make_pair(1, 0)] = 0.0;
					for (int i = 1; i < 0x80; i++)
						pLuxCalculate->DataCountRatioMapping[0][make_pair(1, i)] = 41.0 / i;
				}

				pLuxCalculate->DataRatioBitMapping[1][0] = _T("AlsGain1");
				{
					for (int i = 0; i < 7; i++)
						pLuxCalculate->DataCountRatioMapping[1][make_pair(0, i)] = 1.0 / (double)(1 << i);
				}

				pLuxCalculate->DataRatioBitMapping[1][1] = _T("AlsPuw1");
				{
					pLuxCalculate->DataCountRatioMapping[1][make_pair(1, 0)] = 0.0;
					for (int i = 1; i < 0x80; i++)
						pLuxCalculate->DataCountRatioMapping[1][make_pair(1, i)] = 10.0 / (double)i;
				}

				pLuxCalculate->RatioBitMapping[0] = _T("AlsPuc");
				{
					pLuxCalculate->CountRatioMapping[0][0] = 3.0;

					for (int i = 1; i < 0x20; i++)
						pLuxCalculate->CountRatioMapping[0][i] = 3.0 / ((double)i);
				}

				pLuxCalculate->Lux_Coef_a = 0;
				pLuxCalculate->Lux_Coef_b = 0.213;
				pLuxCalculate->Lux_Coef_c = -4.6;
			}

			pRegTable->BitDetail.at(_T("DarkTrim")).DefaultVal.at(0) = 0x00;
			pRegTable->BitDetail.at(_T("AlsPuc")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("AlsEn")).DefaultVal.at(0) = 0x01;

			pReadTable = &pDieDetail->RegisterTable.ReadTable;
			pReadTable->insert(CReadTable(0xFE, 2));
			pReadTable->insert(CReadTable(0x04, 4, LogDec));
			break;
		}
		case 10200: {
			DieVersion = 10200;
			pDieInfo->Init(DieVersion);
			pDieDetail = &pDieInfo->DieDetail.at(DieVersion);

			pDieDetail->DlgStyle[MAIN_DIALOG] = NOSTYLE;
			pDieDetail->DlgName[MAIN_DIALOG] = _T("Main Dialog");
			pCtrlInfo[MAIN_DIALOG] = &pDieDetail->CtrlInfo[MAIN_DIALOG];

			pDieDetail->DlgStyle[TAB_1] = PAGE_STYLE1;
			pDieDetail->DlgName[TAB_1] = _T("Sys Config");
			pCtrlInfo[TAB_1] = &pDieDetail->CtrlInfo[TAB_1];

			pDieDetail->DlgStyle[TAB_2] = PAGE_STYLE1;
			pDieDetail->DlgName[TAB_2] = _T("ALS");
			pCtrlInfo[TAB_2] = &pDieDetail->CtrlInfo[TAB_2];

			pDieDetail->DlgStyle[MODEL_1] = MODELLESS1;
			pDieDetail->DlgName[MODEL_1] = _T("Data Progress Bar");
			pCtrlInfo[MODEL_1] = &pDieDetail->CtrlInfo[MODEL_1];

			pDieDetail->DieFunc |= DF_LUX;

			pDieDetail->DlgStyle[MODEL_2] = MODELLESS1;
			pDieDetail->DlgName[MODEL_2] = _T("Lux(Ref.)");
			pCtrlInfo[MODEL_2] = &pDieDetail->CtrlInfo[MODEL_2];

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
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->CtrlName = make_pair(_T("ALS Enable"), _T(""));
						pCtrlDetail->BitMapping[0] = _T("AlsEn");
						pCtrlDetail->I2CWriteDelayMs = 10;
					}
				}

				pRegTable->RegInfo.at(0xF1).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(6, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsIntEn");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("DataIntEn");
					}
				}

				pRegTable->RegInfo.at(0xF2).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(6, 7));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS Halt Enable"), _T(""));
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsHalt");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 9));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Data Halt Enable"), _T(""));
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("DataHalt");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ReadClear");
						pCtrlDetail->NameMapping[0] = _T("Manually Clear");
						pCtrlDetail->NameMapping[1] = _T("Auto Clear");
					}
				}

				pRegTable->RegInfo.at(0xF4).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(6, 8));
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
				DlgCheck.Init(TAB_1, make_pair(2, 4));
				ASSERT(DlgCheckSet.insert(DlgCheck).second);
				pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
				{
					pCtrlDetail->CtrlType = CHECK_GROUP;
					pCtrlDetail->BitMapping[0] = _T("PushPull");
				}
#endif // _DEBUG

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

					DlgCheck.Init(MAIN_DIALOG, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Data"), _T("Data"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("DataInt");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(7, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("POR"), _T("POR"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PorInt");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 10));
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
					DlgCheck.Init(MAIN_DIALOG, make_pair(15, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("TmpErr"), _T("TepErr"));
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
						pCtrlDetail->CtrlName = make_pair(_T("Als0"), _T("AlsData0"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = G_BAR;
						pCtrlDetail->BitMapping[0] = _T("AlsData0");
					}

					DlgCheck.Init(TAB_2, make_pair(0, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Als Data0"), _T("Als Data0"));
						pCtrlDetail->CtrlType = PROGRESS_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_SELDATA;
						pCtrlDetail->CtrlColor.first = G_BAR;
						pCtrlDetail->BitMapping[0] = _T("AlsData0");
						pCtrlDetail->RegMapping[0] = 0x04;
						pCtrlDetail->RegMapping[1] = 0x06;
					}

					DlgCheck.Init(MODEL_2, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("LUX"), _T(""));
						pCtrlDetail->CtrlType = TEXT_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_LUX;
						pCtrlDetail->BitMapping[0] = _T("AlsData0");
					}
				}

				/* CH1 Data */
				pRegTable->RegInfo.at(0x06).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(1, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Als1"), _T("AlsData1"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = R_BAR;
						pCtrlDetail->BitMapping[0] = _T("AlsData1");
					}
				}

#ifdef _DEBUG
				/* Amb Data */
				pRegTable->RegInfo.at(0x0C).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(2, 0));
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
					DlgCheck.Init(MODEL_1, make_pair(3, 0));
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

#ifdef _DEBUG
				pRegTable->RegInfo.at(0x47).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("DarkTrim"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("DarkTrim");
						pCtrlDetail->NameMapping[0] = _T("Off");
						for (uint8_t i = 1; i < 16; i++)
						{
							csTemp.Format(_T("x%d"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
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
						pCtrlDetail->CtrlName = make_pair(_T("AlsGain0"), _T(""));
#else
						pCtrlDetail->CtrlName = make_pair(_T("AlsGain"), _T(""));
#endif // _DEBUG
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsGain0");
						pCtrlDetail->NameMapping[0] = _T("x1");
						pCtrlDetail->NameMapping[1] = _T("x2");
						pCtrlDetail->NameMapping[2] = _T("x4");
						pCtrlDetail->NameMapping[3] = _T("x8");
						pCtrlDetail->NameMapping[4] = _T("x16");
						pCtrlDetail->NameMapping[5] = _T("x32");
						pCtrlDetail->NameMapping[6] = _T("x64");
					}

#ifdef _DEBUG
					DlgCheck.Init(TAB_2, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("AlsGain1"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsGain1");
						pCtrlDetail->NameMapping[0] = _T("x1");
						pCtrlDetail->NameMapping[1] = _T("x4");
						pCtrlDetail->NameMapping[2] = _T("x16");
						pCtrlDetail->NameMapping[3] = _T("x32");
					}
#endif // _DEBUG
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
						pCtrlDetail->BitMapping[1] = _T("AlsTurbo");
						pCtrlDetail->NameMapping2[make_pair(0, 0)] = _T("100 ms(0x00)");
						pCtrlDetail->NameMapping2[make_pair(0, 1)] = _T("10 ms(0x00)");
#ifdef _DEBUG
						for (uint8_t i = 1; i < 32; i++)
#else
						for (uint8_t i = 1; i < 16; i++)
#endif // _DEBUG
						{
							csTemp.Format(_T("%d ms"), i * 100);
							pCtrlDetail->NameMapping2[make_pair(i, 0)] = csTemp;
							csTemp.Format(_T("%d ms"), i * 10);
							pCtrlDetail->NameMapping2[make_pair(i, 1)] = csTemp;
						}
					}
				}

#ifdef _DEBUG
				pRegTable->RegInfo.at(0x55).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("AlsPuw0");
						pCtrlDetail->BitMapping[1] = _T("AlsTurbo");
						pCtrlDetail->NameMapping2[make_pair(0, 0)] = _T("Disable AlsData0");
						pCtrlDetail->NameMapping2[make_pair(0, 1)] = _T("Disable AlsData0");
						for (uint8_t i = 1; i < 128; i++)
						{
							csTemp.Format(_T("%d ms integration widths"), i);
							pCtrlDetail->NameMapping2[make_pair(i, 0)] = csTemp;
							csTemp.Format(_T("%.1f ms integration widths"), (float)i * 0.1);
							pCtrlDetail->NameMapping2[make_pair(i, 1)] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x56).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("AlsPuw1");
						pCtrlDetail->BitMapping[1] = _T("AlsTurbo");
						pCtrlDetail->NameMapping2[make_pair(0, 0)] = _T("Disable AlsData1");
						pCtrlDetail->NameMapping2[make_pair(0, 1)] = _T("Disable AlsData1");
						for (uint8_t i = 1; i < 128; i++)
						{
							csTemp.Format(_T("%d ms integration widths"), i);
							pCtrlDetail->NameMapping2[make_pair(i, 0)] = csTemp;
							csTemp.Format(_T("%.1f ms integration widths"), (float)i * 0.1);
							pCtrlDetail->NameMapping2[make_pair(i, 1)] = csTemp;
						}
					}
				}
#endif // _DEBUG

				pRegTable->RegInfo.at(0x5B).bEngMode = FALSE;
				{
#ifdef _DEBUG
					DlgCheck.Init(TAB_2, make_pair(6, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS Turbo(x10)"), _T(""));
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("AlsTurbo");
					}

#endif // _DEBUG
					DlgCheck.Init(TAB_2, make_pair(0, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_SELDATA;
						pCtrlDetail->BitMapping[0] = _T("AlsIntSrc");
						pCtrlDetail->NameMapping[0] = _T("Als Data0");
						pCtrlDetail->NameMapping[1] = _T("Als Data1");
						pCtrlDetail->RegMapping[0] = 0x04;
						pCtrlDetail->RegMapping[1] = 0x06;
					}

					DlgCheck.Init(TAB_2, make_pair(2, 10));
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
			}

			pLuxCalculate = &pDieDetail->LuxCalculate;
			{
				pLuxCalculate->LuxFunc = TwoCH_New;
				pLuxCalculate->DataRegMapping[0] = 0x04;
				pLuxCalculate->DataRegMapping[1] = 0x06;
				pLuxCalculate->DataRatioBitMapping[0][0] = _T("AlsGain0");
				{
					for (int i = 0; i < 7; i++)
						pLuxCalculate->DataCountRatioMapping[0][make_pair(0, i)] = 1.0 / (double)(1 << i);
				}

				pLuxCalculate->DataRatioBitMapping[0][1] = _T("AlsPuw0");
				{
					pLuxCalculate->DataCountRatioMapping[0][make_pair(1, 0)] = 0.0;
					for (int i = 1; i < 0x80; i++)
						pLuxCalculate->DataCountRatioMapping[0][make_pair(1, i)] = 41.0 / i;
				}

				pLuxCalculate->DataRatioBitMapping[1][0] = _T("AlsGain1");
				{
					for (int i = 0; i < 7; i++)
						pLuxCalculate->DataCountRatioMapping[1][make_pair(0, i)] = 1.0 / (double)(1 << i);
				}

				pLuxCalculate->DataRatioBitMapping[1][1] = _T("AlsPuw1");
				{
					pLuxCalculate->DataCountRatioMapping[1][make_pair(1, 0)] = 0.0;
					for (int i = 1; i < 0x80; i++)
						pLuxCalculate->DataCountRatioMapping[1][make_pair(1, i)] = 10.0 / (double)i;
				}

				pLuxCalculate->RatioBitMapping[0] = _T("AlsPuc");
				{
					pLuxCalculate->CountRatioMapping[0][0] = 3.0;

					for (int i = 1; i < 0x20; i++)
						pLuxCalculate->CountRatioMapping[0][i] = 3.0 / ((double)i);
				}

				pLuxCalculate->Lux_Coef_a = 0;
				pLuxCalculate->Lux_Coef_b = 0.213;
				pLuxCalculate->Lux_Coef_c = -4.6;
			}

			pRegTable->BitDetail.at(_T("DarkTrim")).DefaultVal.at(0) = 0x00;
			pRegTable->BitDetail.at(_T("AlsPuc")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("AlsEn")).DefaultVal.at(0) = 0x01;

			pReadTable = &pDieDetail->RegisterTable.ReadTable;
			pReadTable->insert(CReadTable(0xFE, 2));
			pReadTable->insert(CReadTable(0x04, 4, LogDec));
			break;
		}
		}

		CSensorInfo::Init();
	}
};