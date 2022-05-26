#pragma once
#include "Define.h"
#include "DA3221.h"

class CAP314AQ : public CSensorInfo {
public:
	CAP314AQ()
	{
		ModelName = _T("AP314AQ");
		pDieInfo = new CDA3221;
#if defined(_AP314AQ_16000) || defined(_DEBUG) || defined(_AP314AQ)
		ModelVersion.insert(16000);
#endif
	}

	void Init(uint16_t version)
	{
		switch (version) {
		case 16000: {
			DieVersion = 10800;
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
			pDieDetail->DlgName[TAB_2] = _T("ALS + PS");
			pCtrlInfo[TAB_2] = &pDieDetail->CtrlInfo[TAB_2];

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
				pRegTable->DeviceID = 0x1E;

				pRegTable->RegInfo.at(0x00).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = RADIO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("System Mode");
						pCtrlDetail->NameMapping[0] = _T("[0x0] Power down");
						pCtrlDetail->NameMapping[1] = _T("[0x1] ALS function active");
						pCtrlDetail->NameMapping[2] = _T("[0x2] PS+IR function active");
						pCtrlDetail->NameMapping[3] = _T("[0x3] ALS and PS+IR function active");
						pCtrlDetail->NameMapping[5] = _T("[0x5] ALS function once");
						pCtrlDetail->NameMapping[6] = _T("[0x6] PS+IR function once");
						pCtrlDetail->NameMapping[7] = _T("[0x7] ALS and PS+IR function once");

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
						pCtrlDetail->BitMapping[0] = _T("ALS INT");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(1, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS"), _T("PS"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PS INT");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("OBJ"), _T("OBJ"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("OBJ");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(5, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("IR_OV"), _T("IR_OV"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("IR_OV");
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
					DlgCheck.Init(TAB_2, make_pair(4, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("CLR_MNR");
						pCtrlDetail->NameMapping[0] = _T("Auto Clear");
						pCtrlDetail->NameMapping[1] = _T("Manually Clear");
					}

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
						pCtrlDetail->BitMapping[0] = _T("PIEN");
					}
				}


				pRegTable->RegInfo.at(0x06).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("Waiting Time");
					}
				}

				/* IR Data */
				pRegTable->RegInfo.at(0x0A).bEngMode = FALSE;
				{

					DlgCheck.Init(MODEL_1, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("IR"), _T("IR"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = IR_BAR;
						pCtrlDetail->BitMapping[0] = _T("IR Data");
					}
				}

				/* ALS Data */
				pRegTable->RegInfo.at(0x0C).bEngMode = FALSE;
				{

					DlgCheck.Init(MODEL_1, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS"), _T("ALS"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = G_BAR;
						pCtrlDetail->BitMapping[0] = _T("ALS Data");
					}

					DlgCheck.Init(TAB_2, make_pair(0, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS Data"), _T("ALS Data"));
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

				/* PS Data */
				pRegTable->RegInfo.at(0x0E).bEngMode = FALSE;
				{

					DlgCheck.Init(MODEL_1, make_pair(1, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS"), _T("PS"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = PS_BAR;
						pCtrlDetail->BitMapping[0] = _T("PS Data");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Data"), _T("PS Data"));
						pCtrlDetail->CtrlType = PROGRESS_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PS Data");
					}
				}

				pRegTable->RegInfo.at(0x10).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALS Gain");
						pCtrlDetail->NameMapping[0] = _T("65535 lux / Resolution bit");
						pCtrlDetail->NameMapping[1] = _T("16384 lux / Resolution bit");
						pCtrlDetail->NameMapping[2] = _T("4096 lux / Resolution bit");
						pCtrlDetail->NameMapping[3] = _T("1024 lux / Resolution bit");
					}
				}

				/* ALS Low Threshold */
				pRegTable->RegInfo.at(0x1A).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_2, make_pair(0, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS Low Threshold"), _T("ALS Low Threshold"));
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALS Low Threshold");
					}
				}

				/* ALS High Threshold */
				pRegTable->RegInfo.at(0x1C).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_2, make_pair(0, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS High Threshold"), _T("ALS High Threshold"));
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALS High Threshold");
					}
				}

				pRegTable->RegInfo.at(0x20).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PS Gain");
						pCtrlDetail->NameMapping[0] = _T("1");
						pCtrlDetail->NameMapping[1] = _T("2");
						pCtrlDetail->NameMapping[2] = _T("4");
						pCtrlDetail->NameMapping[3] = _T("8");
					}
				}

				pRegTable->RegInfo.at(0x22).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PS_algo");
						pCtrlDetail->NameMapping[0] = _T("Zone INT");
						pCtrlDetail->NameMapping[1] = _T("Hysteresis INT");
					}
				}

				pRegTable->RegInfo.at(0x23).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PS Mean Time");
						pCtrlDetail->NameMapping[0] = _T("1 time");
						pCtrlDetail->NameMapping[1] = _T("2 time");
						pCtrlDetail->NameMapping[2] = _T("3 time");
						pCtrlDetail->NameMapping[3] = _T("4 time");
					}
				}

				pRegTable->RegInfo.at(0x24).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(6, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("SMRTINT");
					}
				}

				pRegTable->RegInfo.at(0x25).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PS / IR Integration time select");
						pCtrlDetail->NameMapping[0] = _T("2T(0)");
						for (int i = 1; i < BIT(6); i++)
						{
							CString csTMP;
							csTMP.Format(_T("%dT"), i + 1);
							pCtrlDetail->NameMapping[i] = csTMP;
						}
					}
				}

				pRegTable->RegInfo.at(0x26).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PS Persist");
						pCtrlDetail->NameMapping[0] = _T("force every coversion time");
						for (int i = 1; i < BIT(6); i++)
						{
							CString csTMP;
							csTMP.Format(_T("%d conversion time"), i);
							pCtrlDetail->NameMapping[i] = csTMP;
						}
					}
				}

				/* PS Calibration */
				pRegTable->RegInfo.at(0x28).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_2, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Calibration"), _T("PS Calibration"));
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PS_Cali");
					}

					DlgCheck.Init(TAB_2, make_pair(2, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = BUTTON_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CALIBRATION;
						pCtrlDetail->BitMapping[0] = _T("PS_Cali");
						pCtrlDetail->RegMapping[0] = 0x0E;
					}
				}

				/* PS Low Threshold */
				pRegTable->RegInfo.at(0x2A).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_2, make_pair(4, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Low Threshold"), _T("PS Low Threshold"));
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PS Low Threshold");
					}
				}

				/* PS High Threshold */
				pRegTable->RegInfo.at(0x2C).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_2, make_pair(4, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS High Threshold"), _T("PS High Threshold"));
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PS High Threshold");
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
				pLuxCalculate->Count2LuxMapping[0] = make_pair(1.71875, 0.0);
			}

			pRegTable->BitDetail.at(_T("System Mode")).DefaultVal.at(0) = 0x03;
			pRegTable->BitDetail.at(_T("PS Mean Time")).DefaultVal.at(0) = 0x03;
			pRegTable->BitDetail.at(_T("PS / IR Integration time select")).DefaultVal.at(0) = 0x09;
			pRegTable->BitDetail.at(_T("PS Persist")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("PS High Threshold")).DefaultVal.at(0) = 0xF4;
			pRegTable->BitDetail.at(_T("PS High Threshold")).DefaultVal.at(1) = 0x01;

			pReadTable = &pDieDetail->RegisterTable.ReadTable;
			pReadTable->insert(CReadTable(0x01, 1));
			pReadTable->insert(CReadTable(0x0A, 6, LogDec));

			break;
		}
		}

		CSensorInfo::Init();
	}
};
