#pragma once
#include "Define.h"
#include "DA3211.h"

class CAL3010 : public CSensorInfo {
public:
	CAL3010()
	{
		ModelName = _T("AL3010");
		pDieInfo = new CDA3211;
#if defined(_AL3010_15000) || defined(_DEBUG) || defined(_AL3010)
		ModelVersion.insert(15000);
#endif

#if defined(_DEBUG) || defined(_AL3010)
		ModelVersion.insert(15000);
		ModelSelAddress.insert(0x1C);
		ModelSelAddress.insert(0x1D);
		ModelSelAddress.insert(0x1E);
		ModelDefaultAddress = 0x1E;
#endif
	}

	void Init(uint16_t version)
	{
		switch (version) {
		case 15000: {
			DieVersion = 11100;
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
						pCtrlDetail->BitMapping[0] = _T("SWRST");
						pCtrlDetail->I2CWriteDelayMs = 30;
					}

					DlgCheck.Init(TAB_1, make_pair(0, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("System Mode"), _T(""));
						pCtrlDetail->CtrlType = RADIO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("System Mode");
						pCtrlDetail->NameMapping[0] = _T("Power Down");
						pCtrlDetail->NameMapping[1] = _T("Enable ALS");
						pCtrlDetail->NameMapping[5] = _T("Execute ALS function once");
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
						pCtrlDetail->BitMapping[0] = _T("ALS Int");
					}
				}

				/* ALS Data */
				pRegTable->RegInfo.at(0x0C).bEngMode = FALSE;
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

				pRegTable->RegInfo.at(0x10).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(0, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("ALS Gain");
						pCtrlDetail->NameMapping[0] = _T("77806 lux");
						pCtrlDetail->NameMapping[1] = _T("19452 lux");
						pCtrlDetail->NameMapping[2] = _T("4863 lux");
						pCtrlDetail->NameMapping[3] = _T("1216 lux");
					}

					DlgCheck.Init(TAB_1, make_pair(2, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALS persist");
						pCtrlDetail->NameMapping[0] = _T("1 conversion time");
						pCtrlDetail->NameMapping[1] = _T("4 conversion time");
						pCtrlDetail->NameMapping[2] = _T("8 conversion time");
						pCtrlDetail->NameMapping[3] = _T("16 conversion time");
					}
				}

				/*ALS Low Threshold*/
				pRegTable->RegInfo.at(0x1A).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(0, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Low Threshold"), _T("Low Threshold"));
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALS Low Threshold");
					}
				}

				/*ALS High Threshold*/
				pRegTable->RegInfo.at(0x1C).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(0, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("High Threshold"), _T("High Threshold"));
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALS High Threshold");
					}
				}
			}

			pLuxCalculate = &pDieDetail->LuxCalculate;
			{
				pLuxCalculate->LuxFunc = OneCH;
				pLuxCalculate->DataRegMapping[0] = 0x0C;

				pLuxCalculate->RatioBitMapping[0] = _T("ALS Gain");
				pLuxCalculate->CountRatioMapping[0][0] = 1.0;
				pLuxCalculate->CountRatioMapping[0][1] = 1.0 / 4.0;
				pLuxCalculate->CountRatioMapping[0][2] = 1.0 / 16.0;
				pLuxCalculate->CountRatioMapping[0][3] = 1.0 / 64.0;

				pLuxCalculate->Count2LuxMapping[0] = make_pair(1.1872, 0.0);
			}

			pRegTable->BitDetail.at(_T("System Mode")).DefaultVal.at(0) = 0x01;

			pReadTable = &pDieDetail->RegisterTable.ReadTable;
			pReadTable->clear();
			pReadTable->insert(CReadTable(0x01, 1));
			pReadTable->insert(CReadTable(0x0C, 2, LogDec, true));
		}
		}

		CSensorInfo::Init();
	}
};
