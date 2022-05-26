#pragma once
#include "Define.h"
#include "DA3107.h"

class CCS5072 : public CSensorInfo {
public:
	CCS5072() {
		ModelName = _T("CS5072");
		pDieInfo = new CDA3107;
#if defined(_CS5072_6000) || defined(_DEBUG) || defined(_CS5072)
		ModelVersion.insert(6000);
#endif
	}

	void Init(uint16_t version) {
		switch (version) {
		case 6000: {
			DieVersion = 11000;
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

			pDieDetail->DieFunc |= DF_LUX | DF_CCT;

			pDieDetail->DlgStyle[MODEL_2] = MODELLESS1;
			pDieDetail->DlgName[MODEL_2] = _T("Lux & CCT");
			pCtrlInfo[MODEL_2] = &pDieDetail->CtrlInfo[MODEL_2];

			pDieDetail->DlgStyle[MODEL_3] = MODELLESS_LIST;
			pDieDetail->DlgName[MODEL_3] = _T("Register Table");

			pRegTable = &pDieDetail->RegisterTable;
			{
				pRegTable->RegInfo.at(0x00).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("AEN");
					}

					DlgCheck.Init(TAB_1, make_pair(4, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = BUTTON_GROUP;
						pCtrlDetail->CtrlName = make_pair(_T("Softwave Reset"), _T(""));
						pCtrlDetail->CtrlFunc = CTRLFUNC_SWRST;
						pCtrlDetail->BitMapping[0] = _T("SWRST");
						pCtrlDetail->I2CWriteDelayMs = 30;
					}

					DlgCheck.Init(TAB_2, make_pair(4, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IFGCRM");
						pCtrlDetail->NameMapping[0] = _T("Manually Clear");
						pCtrlDetail->NameMapping[1] = _T("Clear after read");
					}
				}

				pRegTable->RegInfo.at(0x01).bEngMode = FALSE;
				{
					DlgCheck.Init(MAIN_DIALOG, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS"), _T("ALS"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("AINT");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(1, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("POR"), _T("POR"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PORINT");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 10));
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
					DlgCheck.Init(TAB_2, make_pair(6, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AIEN");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 1));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("APEND");
					}
				}

				pRegTable->RegInfo.at(0x06).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("WTIME");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("WUNIT");
						pCtrlDetail->NameMapping[0] = _T("2ms");
						pCtrlDetail->NameMapping[1] = _T("20ms");
					}
				}

				pRegTable->RegInfo.at(0x07).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AGAIN");
						pCtrlDetail->NameMapping[0] = _T("x1");
						pCtrlDetail->NameMapping[1] = _T("x2");
						pCtrlDetail->NameMapping[2] = _T("x4");
						pCtrlDetail->NameMapping[3] = _T("x8");
						pCtrlDetail->NameMapping[4] = _T("x16");
						pCtrlDetail->NameMapping[5] = _T("x32");
						pCtrlDetail->NameMapping[6] = _T("x64");
					}

					DlgCheck.Init(TAB_2, make_pair(2, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_SELDATA;
						pCtrlDetail->BitMapping[0] = _T("ASRC");
						pCtrlDetail->NameMapping[0] = _T("RDATA as ADATA");
						pCtrlDetail->NameMapping[1] = _T("GDATA as ADATA");
						pCtrlDetail->NameMapping[2] = _T("BDATA as ADATA");
						pCtrlDetail->NameMapping[3] = _T("CDATA as ADATA");
						pCtrlDetail->RegMapping[0] = 0x2C;
						pCtrlDetail->RegMapping[1] = 0x2E;
						pCtrlDetail->RegMapping[2] = 0x30;
						pCtrlDetail->RegMapping[3] = 0x32;
					}
				}

				pRegTable->RegInfo.at(0x08).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_RANGE;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("ATIME");
						for (int i = 0; i < 64; i++)
							pCtrlDetail->RangeMapping[i] = make_pair(0, 1023 + i * 1024);
						pCtrlDetail->RegMapping[0] = 0x2C;
						pCtrlDetail->RegMapping[1] = 0x2E;
						pCtrlDetail->RegMapping[2] = 0x30;
						pCtrlDetail->RegMapping[3] = 0x32;
						pCtrlDetail->RegMapping[4] = 0x36;
						pCtrlDetail->RegMapping[5] = 0x38;
					}
				}

				pRegTable->RegInfo.at(0x09).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("APERS");
						pCtrlDetail->NameMapping[0] = _T("Every cycles");
						for (int i = 1; i < 64; i++) {
							csTemp.Format(_T("After %d"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x1E).bEngMode = FALSE;
				{
					DlgCheck.Init(MAIN_DIALOG, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("AERR"), _T("AERR"));
						pCtrlDetail->BitMapping[0] = _T("AERR");
						pCtrlDetail->CtrlType = LED;
					}
				}

				/* Red Data */
				pRegTable->RegInfo.at(0x2C).bEngMode = FALSE;
				pRegTable->RegInfo.at(0x2C).RegDesc = _T("RedData");
				pRegTable->BitDetail.at(_T("ACH0")).csDesc = _T("Red Data");
				{
					DlgCheck.Init(MODEL_1, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Red"), _T("Red"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = R_BAR;
						pCtrlDetail->BitMapping[0] = _T("ACH0");
					}

					DlgCheck.Init(TAB_2, make_pair(0, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Red Data"), _T("Red Data"));
						pCtrlDetail->CtrlType = PROGRESS_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_SELDATA;
						pCtrlDetail->BitMapping[0] = _T("ACH0");
						pCtrlDetail->RegMapping[0] = 0x2C;
						pCtrlDetail->RegMapping[1] = 0x2E;
						pCtrlDetail->RegMapping[2] = 0x30;
						pCtrlDetail->RegMapping[3] = 0x32;
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

					DlgCheck.Init(MODEL_2, make_pair(0, 1));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("CCT"), _T(""));
						pCtrlDetail->CtrlType = TEXT_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CCT;
					}
				}

				/* Green Data */
				pRegTable->RegInfo.at(0x2E).bEngMode = FALSE;
				pRegTable->RegInfo.at(0x2E).RegDesc = _T("GreenData");
				pRegTable->BitDetail.at(_T("ACH1")).csDesc = _T("Green Data");
				{
					DlgCheck.Init(MODEL_1, make_pair(1, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Green"), _T("Green"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = G_BAR;
						pCtrlDetail->BitMapping[0] = _T("ACH1");
					}

				}

				/* Blue Data */
				pRegTable->RegInfo.at(0x30).bEngMode = FALSE;
				pRegTable->RegInfo.at(0x30).RegDesc = _T("BlueData");
				pRegTable->BitDetail.at(_T("ACH2")).csDesc = _T("Blue Data");
				{
					DlgCheck.Init(MODEL_1, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Blue"), _T("Blue"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = B_BAR;
						pCtrlDetail->BitMapping[0] = _T("ACH2");
					}
				}

				/* Comp Data */
				pRegTable->RegInfo.at(0x32).bEngMode = FALSE;
				pRegTable->RegInfo.at(0x32).RegDesc = _T("CompData");
				pRegTable->BitDetail.at(_T("ACH3")).csDesc = _T("Comp Data");
				{
					DlgCheck.Init(MODEL_1, make_pair(3, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Comp"), _T("Comp"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = C_BAR;
						pCtrlDetail->BitMapping[0] = _T("ACH3");
					}

				}

				/* ALS Low Threshold */
				pRegTable->RegInfo.at(0x36).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_2, make_pair(0, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS Low Threshold"), _T("ALS Low Threshold"));
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALTH");
					}
				}

				/* ALS High Threshold */
				pRegTable->RegInfo.at(0x38).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_2, make_pair(0, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS High Threshold"), _T("ALS High Threshold"));
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AHTH");
					}
				}
			}

			pLuxCalculate = &pDieDetail->LuxCalculate;
			{
				pLuxCalculate->LuxFunc = FourCH_Color;
				pLuxCalculate->DataRegMapping[0] = 0x2C;
				pLuxCalculate->DataRegMapping[1] = 0x2E;
				pLuxCalculate->DataRegMapping[2] = 0x30;
				pLuxCalculate->DataRegMapping[3] = 0x32;
				pLuxCalculate->RatioBitMapping[0] = _T("AGAIN");
				{
					pLuxCalculate->CountRatioMapping[0][0] = 1.0;
					pLuxCalculate->CountRatioMapping[0][1] = 1.0 / 2.0;
					pLuxCalculate->CountRatioMapping[0][2] = 1.0 / 4.0;
					pLuxCalculate->CountRatioMapping[0][3] = 1.0 / 8.0;
					pLuxCalculate->CountRatioMapping[0][4] = 1.0 / 16.0;
					pLuxCalculate->CountRatioMapping[0][5] = 1.0 / 32.0;
					pLuxCalculate->CountRatioMapping[0][6] = 1.0 / 64.0;
				}
				
				pLuxCalculate->RatioBitMapping[1] = _T("ATIME");
				for (int i = 0; i < 256; i++)
					pLuxCalculate->CountRatioMapping[1][i] = 64.0 / ((double)i + 1);
				
				pLuxCalculate->RatioBitMapping[2] = _T("AUNIT");
				pLuxCalculate->CountRatioMapping[2][0] = 0;
				for (int i = 1; i < 256; i++)
					pLuxCalculate->CountRatioMapping[2][i] = (double)pRegTable->RegInfo.at(0x6E).RegInit.at(0) / i;
			}

			pDieDetail->CCTCalculate = pDieDetail->LuxCalculate;
			pCCTCalculate = &pDieDetail->CCTCalculate;
			{
				pCCTCalculate->RegressCoefMapping[0][0][0] = -1.60589;
				pCCTCalculate->RegressCoefMapping[0][0][1] = -3.89184;
				pCCTCalculate->RegressCoefMapping[0][0][2] = 1.39210;
				pCCTCalculate->RegressCoefMapping[0][0][3] = 4.08301;
				pCCTCalculate->RegressCoefMapping[0][0][4] = 0;

				pCCTCalculate->RegressCoefMapping[0][1][0] = -2.68513;
				pCCTCalculate->RegressCoefMapping[0][1][1] = -4.58637;
				pCCTCalculate->RegressCoefMapping[0][1][2] = 2.75808;
				pCCTCalculate->RegressCoefMapping[0][1][3] = 4.64330;
				pCCTCalculate->RegressCoefMapping[0][1][4] = 0;

				pCCTCalculate->RegressCoefMapping[0][2][0] = -5.21790;
				pCCTCalculate->RegressCoefMapping[0][2][1] = -6.29340;
				pCCTCalculate->RegressCoefMapping[0][2][2] = 6.50788;
				pCCTCalculate->RegressCoefMapping[0][2][3] = 5.37710;
				pCCTCalculate->RegressCoefMapping[0][2][4] = 0;
			}
			
			pRegTable->BitDetail.at(_T("AEN")).DefaultVal.at(0)	= 0x01;
			pRegTable->BitDetail.at(_T("AGAIN")).DefaultVal.at(0) = 4;
			pRegTable->BitDetail.at(_T("ATIME")).DefaultVal.at(0) = 0x3f;

			pReadTable = &pDieDetail->RegisterTable.ReadTable;
			pReadTable->insert(CReadTable(0x01, 1));
			pReadTable->insert(CReadTable(0x1E, 1));
			pReadTable->insert(CReadTable(0x2C, 8, LogDec));

			break;
		}
		}

		CSensorInfo::Init();
	}
};