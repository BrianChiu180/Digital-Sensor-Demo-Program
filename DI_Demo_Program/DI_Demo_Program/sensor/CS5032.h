#pragma once
#include "Define.h"
#include "DA5330.h"

class CCS5032 : public CSensorInfo {
public:
	CCS5032() {
		ModelName = _T("CS5032");
		pDieInfo = new CDA5330;
#if defined(_CS5032_10300) || defined(_DEBUG) || defined(_CS5032)
		ModelVersion.insert(10300);
#endif
	}

	void Init(uint16_t version) {
		switch (version) {
		case 10300: {
			DieVersion = 12000;
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
				}

				pRegTable->RegInfo.at(0x01).bEngMode = FALSE;
				{
					DlgCheck.Init(MAIN_DIALOG, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS"), _T("ALS"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("ALINT");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(5, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ERR"), _T("ERR"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("ERRFLAG");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(7, 0));
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
						pCtrlDetail->BitMapping[0] = _T("ALPEND");
					}
				}

				pRegTable->RegInfo.at(0x06).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("WTime");
					}

					DlgCheck.Init(TAB_2, make_pair(0, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("WUnit");
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
						pCtrlDetail->BitMapping[0] = _T("ALGAIN");
						pCtrlDetail->NameMapping[0] = _T("x1");
						pCtrlDetail->NameMapping[1] = _T("x4");
						pCtrlDetail->NameMapping[2] = _T("x16");
						pCtrlDetail->NameMapping[3] = _T("x64");
					}

					DlgCheck.Init(TAB_2, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_SELDATA;
						pCtrlDetail->BitMapping[0] = _T("ALSRC");
						pCtrlDetail->NameMapping[0] = _T("Red channel");
						pCtrlDetail->NameMapping[1] = _T("Green channel");
						pCtrlDetail->NameMapping[2] = _T("Blue channel");
						pCtrlDetail->RegMapping[0] = 0x28;
						pCtrlDetail->RegMapping[1] = 0x2A;
						pCtrlDetail->RegMapping[2] = 0x2C;
					}
				}

				pRegTable->RegInfo.at(0x08).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALPERS");
						pCtrlDetail->NameMapping[0] = _T("Every cycles");
						for (int i = 1; i < 64; i++) {
							csTemp.Format(_T("After %d"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x0A).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_RANGE;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("ALTIME");
						for (int i = 0; i < 64; i++)
							pCtrlDetail->RangeMapping[i] = make_pair(0, 1023 + i * 1024);
						pCtrlDetail->RegMapping[0] = 0x28;
						pCtrlDetail->RegMapping[1] = 0x2A;
						pCtrlDetail->RegMapping[2] = 0x2C;
						pCtrlDetail->RegMapping[3] = 0x2E;
						pCtrlDetail->RegMapping[4] = 0x32;
						pCtrlDetail->RegMapping[5] = 0x34;
					}
				}


				pRegTable->RegInfo.at(0x1E).bEngMode = FALSE;
				{
					DlgCheck.Init(MAIN_DIALOG, make_pair(8, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ERRR"), _T("ERRR"));
						pCtrlDetail->BitMapping[0] = _T("ERRR");
						pCtrlDetail->CtrlType = LED;
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(9, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ERRG"), _T("ERRG"));
						pCtrlDetail->BitMapping[0] = _T("ERRG");
						pCtrlDetail->CtrlType = LED;
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(10, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ERRB"), _T("ERRB"));
						pCtrlDetail->BitMapping[0] = _T("ERRB");
						pCtrlDetail->CtrlType = LED;
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(11, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ERRC"), _T("ERRC"));
						pCtrlDetail->BitMapping[0] = _T("ERRC");
						pCtrlDetail->CtrlType = LED;
					}
				}

				/* Red Data */
				pRegTable->RegInfo.at(0x28).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Red"), _T("Red"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = R_BAR;
						pCtrlDetail->BitMapping[0] = _T("R DATA");
					}

					DlgCheck.Init(TAB_2, make_pair(0, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = PROGRESS_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_SELDATA;
						pCtrlDetail->BitMapping[0] = _T("R DATA");
						pCtrlDetail->RegMapping[0] = 0x28;
						pCtrlDetail->RegMapping[1] = 0x2A;
						pCtrlDetail->RegMapping[2] = 0x2C;
					}

					DlgCheck.Init(MODEL_2, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("LUX"), _T(""));
						pCtrlDetail->CtrlType = TEXT_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_LUX;
						pCtrlDetail->BitMapping[0] = _T("R DATA");
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
				pRegTable->RegInfo.at(0x2A).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(1, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Green"), _T("Green"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = G_BAR;
						pCtrlDetail->BitMapping[0] = _T("G DATA");
					}

				}

				/* Blue Data */
				pRegTable->RegInfo.at(0x2C).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Blue"), _T("Blue"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = B_BAR;
						pCtrlDetail->BitMapping[0] = _T("B DATA");
					}
				}

				/* Comp Data */
				pRegTable->RegInfo.at(0x2E).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(3, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Comp"), _T("Comp"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = C_BAR;
						pCtrlDetail->BitMapping[0] = _T("C DATA");
					}

				}

				/* ALS Low Threshold */
				pRegTable->RegInfo.at(0x32).bEngMode = FALSE;
				pRegTable->RegInfo.at(0x32).RegDesc = _T("ALS Low Threshold");
				{
					DlgCheck.Init(TAB_2, make_pair(0, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS Low Threshold"), _T("ALS Low Threshold"));
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALTHSL");
					}
				}

				/* ALS High Threshold */
				pRegTable->RegInfo.at(0x34).bEngMode = FALSE;
				pRegTable->RegInfo.at(0x34).RegDesc = _T("ALS High Threshold");
				{

					DlgCheck.Init(TAB_2, make_pair(0, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS High Threshold"), _T("ALS High Threshold"));
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALTHSH");
					}
				}
			}

			pLuxCalculate = &pDieDetail->LuxCalculate;
			{
				pLuxCalculate->LuxFunc = FourCH_Color;
				pLuxCalculate->DataRegMapping[0] = 0x28;
				pLuxCalculate->DataRegMapping[1] = 0x2A;
				pLuxCalculate->DataRegMapping[2] = 0x2C;
				pLuxCalculate->DataRegMapping[3] = 0x2E;
				pLuxCalculate->RatioBitMapping[0] = _T("ALGAIN");
				{
					pLuxCalculate->CountRatioMapping[0][0] = 1.0;
					pLuxCalculate->CountRatioMapping[0][1] = 1.0 / 4.0;
					pLuxCalculate->CountRatioMapping[0][2] = 1.0 / 16.0;
					pLuxCalculate->CountRatioMapping[0][3] = 1.0 / 64.0;
				}

				pLuxCalculate->RatioBitMapping[1] = _T("ALTIME");
				for (int i = 0; i < 256; i++)
					pLuxCalculate->CountRatioMapping[1][i] = 64.0 / ((double)i + 1);
			}

			pDieDetail->CCTCalculate = pDieDetail->LuxCalculate;
			pCCTCalculate = &pDieDetail->CCTCalculate;
			{
#ifdef _CLIENT_KEDE
				pCCTCalculate->RegressCoefMapping[0][0][0] = -0.96242662363948;
				pCCTCalculate->RegressCoefMapping[0][0][1] = 3.31631103504755;
				pCCTCalculate->RegressCoefMapping[0][0][2] = -3.08127936792892;
				pCCTCalculate->RegressCoefMapping[0][0][3] = 1.32556906275825;
				pCCTCalculate->RegressCoefMapping[0][0][4] = 0;

				pCCTCalculate->RegressCoefMapping[0][1][0] = -0.96467212263381;
				pCCTCalculate->RegressCoefMapping[0][1][1] = 3.20871562918621;
				pCCTCalculate->RegressCoefMapping[0][1][2] = -2.74100019353636;
				pCCTCalculate->RegressCoefMapping[0][1][3] = 1.07301079641496;
				pCCTCalculate->RegressCoefMapping[0][1][4] = 0;

				pCCTCalculate->RegressCoefMapping[0][2][0] = -0.77117314128993;
				pCCTCalculate->RegressCoefMapping[0][2][1] = 1.54607567952890;
				pCCTCalculate->RegressCoefMapping[0][2][2] = 0.04877060769129;
				pCCTCalculate->RegressCoefMapping[0][2][3] = -0.23502487155654;
				pCCTCalculate->RegressCoefMapping[0][2][4] = 0;
#else
				pCCTCalculate->RegressCoefMapping[0][0][0] = -0.4155499554589361;
				pCCTCalculate->RegressCoefMapping[0][0][1] = 3.165330172576616;
				pCCTCalculate->RegressCoefMapping[0][0][2] = -3.292440796485966;
				pCCTCalculate->RegressCoefMapping[0][0][3] = 0.9575622809914199;
				pCCTCalculate->RegressCoefMapping[0][0][4] = 0;

				pCCTCalculate->RegressCoefMapping[0][1][0] = -0.4668777193071851;
				pCCTCalculate->RegressCoefMapping[0][1][1] = 2.957021505546019;
				pCCTCalculate->RegressCoefMapping[0][1][2] = -2.722657757589789;
				pCCTCalculate->RegressCoefMapping[0][1][3] = 0.5673652240664507;
				pCCTCalculate->RegressCoefMapping[0][1][4] = 0;

				pCCTCalculate->RegressCoefMapping[0][2][0] = -0.923350911350027;
				pCCTCalculate->RegressCoefMapping[0][2][1] = 3.760142807177032;
				pCCTCalculate->RegressCoefMapping[0][2][2] = -3.325570907091354;
				pCCTCalculate->RegressCoefMapping[0][2][3] = 1.089522688644398;
				pCCTCalculate->RegressCoefMapping[0][2][4] = 0;
#endif
			}

			pRegTable->BitDetail.at(_T("AEN")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("ALGAIN")).DefaultVal.at(0) = 2;
			pRegTable->BitDetail.at(_T("ALTIME")).DefaultVal.at(0) = 0x3f;

			pReadTable = &pDieDetail->RegisterTable.ReadTable;
			pReadTable->insert(CReadTable(0x01, 1));
			pReadTable->insert(CReadTable(0x1E, 1));
			pReadTable->insert(CReadTable(0x28, 8, LogDec));

			break;
		}
		}

		CSensorInfo::Init();
	}
};