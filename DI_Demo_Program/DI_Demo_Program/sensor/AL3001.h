#pragma once
#include "Define.h"
#include "DA3121.h"

class CAL3001 : public CSensorInfo {
public:
	CAL3001()
	{
		ModelName = _T("AL3001");
		pDieInfo = new CDA3121;
#if defined(_AL3001_13000) || defined(_DEBUG) || defined(_AL3001)
		ModelVersion.insert(13000);
#endif

#if defined(_DEBUG) || defined(_AL3320)
		ModelSelAddress.insert(0x1C);
		ModelSelAddress.insert(0x1D);
		ModelSelAddress.insert(0x1E);
		ModelDefaultAddress = 0x1C;
#endif
	}

	void Init(uint16_t version)
	{
		switch (version) {
		case 13000: {
			DieVersion = 13000;
			pDieInfo->Init(DieVersion);
			pDieDetail = &pDieInfo->DieDetail.at(DieVersion);

			pDieDetail->DieFunc = DF_NONE;
			pDieDetail->DlgStyle[MAIN_DIALOG] = NOSTYLE;
			pDieDetail->DlgName[MAIN_DIALOG] = _T("Main Dialog");
			pCtrlInfo[MAIN_DIALOG] = &pDieDetail->CtrlInfo[MAIN_DIALOG];

			pDieDetail->DlgStyle[TAB_1] = PAGE_STYLE1;
			pDieDetail->DlgName[TAB_1] = _T("Sys Config + ALS");
			pCtrlInfo[TAB_1] = &pDieDetail->CtrlInfo[TAB_1];

			pDieDetail->DlgStyle[MODEL_1] = MODELLESS1;
			pDieDetail->DlgName[MODEL_1] = _T("Data Progress Bar");
			pCtrlInfo[MODEL_1] = &pDieDetail->CtrlInfo[MODEL_1];

			pDieDetail->DieFunc |= DF_LUX;
			pDieDetail->DlgStyle[MODEL_2] = MODELLESS1;
			pDieDetail->DlgName[MODEL_2] = _T("Lux");
			pCtrlInfo[MODEL_2] = &pDieDetail->CtrlInfo[MODEL_2];

			pDieDetail->DlgStyle[MODEL_3] = MODELLESS_LIST;
			pDieDetail->DlgName[MODEL_3] = _T("Register Table");

			pRegTable = &pDieDetail->RegisterTable;
			{
				pRegTable->RegInfo.at(0x00).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(6, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = BUTTON_GROUP;
						pCtrlDetail->CtrlName = make_pair(_T("Softwave Reset"), _T(""));
						pCtrlDetail->CtrlFunc = CTRLFUNC_SWRST;
						pCtrlDetail->BitMapping[0] = _T("SWREST");
						pCtrlDetail->I2CWriteDelayMs = 30;
					}

					DlgCheck.Init(TAB_1, make_pair(0, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS Enable"), _T(""));
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AEN");
					}
				}

				pRegTable->RegInfo.at(0x01).bEngMode = FALSE;
				{
					DlgCheck.Init(MAIN_DIALOG, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("AINT"), _T("AINT"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("INT flag");
					}

					DlgCheck.Init(TAB_1, make_pair(6, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Clear Interrupt"), _T(""));
						pCtrlDetail->CtrlType = BUTTON_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CLEAR_INT;
						pCtrlDetail->RegMapping[0] = 0x01;
					}				
				}

				pRegTable->RegInfo.at(0x02).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(6, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS interrupt pin enable"), _T(""));
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALS INT enable");
					}

					DlgCheck.Init(TAB_1, make_pair(6, 3));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS Suspend enable"), _T(""));
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALS_Suspend");
					}
				}
				pRegTable->RegInfo.at(0x06).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(2, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("ALS Waiting");
						pCtrlDetail->NameMapping[0] = _T("No waiting");
						for (int i = 1; i < 256; i++)
						{
							csTemp.Format(_T("%d ms"), i * 2);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x07).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("Gain selection");
						pCtrlDetail->NameMapping[0] = _T("33.28K lux");
						pCtrlDetail->NameMapping[1] = _T("8.32K lux");
						pCtrlDetail->NameMapping[2] = _T("6.25K lux");
						pCtrlDetail->NameMapping[3] = _T("1.95K lux");
					}
				}

				pRegTable->RegInfo.at(0x08).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(2, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS Persist"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALS persist");
						pCtrlDetail->NameMapping[0] = _T("Every conversion time");
						for (int i = 1; i < 64; i++)
						{
							csTemp.Format(_T("After %d"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x09).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(0, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS Mean Time"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("ALS mean time");
						for (int i = 0; i < 16; i++)
						{
							csTemp.Format(_T("Average of %d time"), i+1);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x0A).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(2, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("ALS dummy time slot");
						pCtrlDetail->NameMapping[0] = _T("No dummy time");
						for (int i = 1; i < 256; i++)
						{
							csTemp.Format(_T("Insert %d dummy time solt"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				/* ALS Data */
				pRegTable->RegInfo.at(0x22).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS"), _T("ALS Data"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = G_BAR;
						pCtrlDetail->BitMapping[0] = _T("ALS Data");
					}

					DlgCheck.Init(TAB_1, make_pair(0, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = PROGRESS_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALS Data");
					}

					DlgCheck.Init(MODEL_2, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("LUX"), _T(""));
						pCtrlDetail->CtrlType = TEXT_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_LUX;
						pCtrlDetail->BitMapping[0] = _T("ALS Data");
					}
				}

				/*ALS Low Threshold*/
				pRegTable->RegInfo.at(0x30).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(0, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("Low Threshold");
					}
				}

				/*ALS High Threshold*/
				pRegTable->RegInfo.at(0x32).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(0, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("High Threshold");
					}
				}

#ifdef _RD
				pRegTable->RegInfo.at(0x34).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(0, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("Calibration");
						for (int i = 0; i < 256; i++)
						{
							csTemp.Format(_T("%d / 64"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}
#endif
			}

			pLuxCalculate = &pDieDetail->LuxCalculate;
			{
				pLuxCalculate->LuxFunc = OneCH;
				pLuxCalculate->DataRegMapping[0] = 0x22;

				pLuxCalculate->RatioBitMapping[0] = _T("Gain selection");
				pLuxCalculate->CountRatioMapping[0][0] = 1.0;
				pLuxCalculate->CountRatioMapping[0][1] = 1.0 / 4.0;
				pLuxCalculate->CountRatioMapping[0][2] = 1.0 / 16.0;
				pLuxCalculate->CountRatioMapping[0][3] = 1.0 / 64.0;

				pLuxCalculate->Count2LuxMapping[0] = make_pair(0.512, 0.0);
			}

			pRegTable->BitDetail.at(_T("AEN")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("Gain selection")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("ALS dummy time slot")).DefaultVal.at(0) = 62;

			pReadTable = &pDieDetail->RegisterTable.ReadTable;
			pReadTable->clear();
			pReadTable->insert(CReadTable(0x01, 1));
			pReadTable->insert(CReadTable(0x22, 2, LogDec));
		}
		}

		CSensorInfo::Init();
	}
};
