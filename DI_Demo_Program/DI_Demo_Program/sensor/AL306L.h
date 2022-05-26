#pragma once
#include "Define.h"
#include "DA3108.h"

class CAL306L : public CSensorInfo {
public:
	CAL306L()
	{
		ModelName = _T("AL306L");
		pDieInfo = new CDA3108;
#if defined(_AL306L_3000) || defined(_DEBUG) || defined(_AL306L)
		ModelVersion.insert(3000);
#endif
	}

	void Init(uint16_t version)
	{
		switch (version) {
		case 3000: {
			DieVersion = 10000;
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
					DlgCheck.Init(TAB_1, make_pair(4, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = BUTTON_GROUP;
						pCtrlDetail->CtrlName = make_pair(_T("ALS Reset function"), _T(""));
						pCtrlDetail->CtrlFunc = CTRLFUNC_SWRST;
						pCtrlDetail->BitMapping[0] = _T("ALS_RESET");
						pCtrlDetail->I2CWriteDelayMs = 30;
					}

					DlgCheck.Init(TAB_1, make_pair(6, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("WHITE_EN");
					}

					DlgCheck.Init(TAB_1, make_pair(2, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("ALS_IT");
						pCtrlDetail->NameMapping[0] = _T("100 ms");
						pCtrlDetail->NameMapping[1] = _T("200 ms");
						pCtrlDetail->NameMapping[2] = _T("400 ms");
						pCtrlDetail->NameMapping[3] = _T("800 ms");
						pCtrlDetail->NameMapping[4] = _T("1600 ms");
						pCtrlDetail->NameMapping[5] = _T("3200 ms");

					}

					DlgCheck.Init(TAB_1, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("HS");
						pCtrlDetail->NameMapping[0] = _T("ALS Sensitivity x1");
						pCtrlDetail->NameMapping[1] = _T("ALS Sensitivity x2");
					}

					DlgCheck.Init(TAB_1, make_pair(6, 3));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("SD");
						//pCtrlDetail->bActive = FALSE;
					}
				}

				/* ACH0 Data */
				pRegTable->RegInfo.at(0x50).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ACH0"), _T("ACH0"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = G_BAR;
						pCtrlDetail->BitMapping[0] = _T("ACH0");
					}

					DlgCheck.Init(MODEL_2, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("LUX"), _T(""));
						pCtrlDetail->CtrlType = TEXT_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_LUX;
						pCtrlDetail->BitMapping[0] = _T("ACH0");
					}
				}

				/* ACH1 Data */
				pRegTable->RegInfo.at(0x51).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(1, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ACH1"), _T("ACH1"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = C_BAR;
						pCtrlDetail->BitMapping[0] = _T("ACH1");
					}
				}
			}

			pLuxCalculate = &pDieDetail->LuxCalculate;
			{
				pLuxCalculate->LuxFunc = TwoCH;
				pLuxCalculate->DataRegMapping[0] = 0x50;
				pLuxCalculate->DataRegMapping[1] = 0x51;
				pLuxCalculate->RatioBitMapping[0] = _T("HS");
				pLuxCalculate->CountRatioMapping[0][0] = 2.0 ;
				pLuxCalculate->CountRatioMapping[0][1] = 1.0;

				pLuxCalculate->RatioBitMapping[1] = _T("ALS_IT");
				pLuxCalculate->CountRatioMapping[1][0] = 2.0;
				pLuxCalculate->CountRatioMapping[1][1] = 1.0;
				pLuxCalculate->CountRatioMapping[1][2] = 1.0 / 2.0;
				pLuxCalculate->CountRatioMapping[1][3] = 1.0 / 4.0;
				pLuxCalculate->CountRatioMapping[1][4] = 1.0 / 8.0;
				pLuxCalculate->CountRatioMapping[1][5] = 1.0 / 16.0;

				pLuxCalculate->Count2LuxMapping[0] = make_pair(0.2646 / 16.0, 0.0);
			}

			pRegTable->BitDetail.at(_T("dc_en")).DefaultVal.at(0) = 0x00;

			pRegTable->RegInfo.at(0x50).RegScale = 16.0;
			pRegTable->RegInfo.at(0x51).RegScale = 2.2;

			pReadTable = &pDieDetail->RegisterTable.ReadTable;
			pReadTable->insert(CReadTable(0x50, 2, LogDec));
			pReadTable->insert(CReadTable(0x51, 2, LogDec));
		}
		}

		CSensorInfo::Init();
	}
};

