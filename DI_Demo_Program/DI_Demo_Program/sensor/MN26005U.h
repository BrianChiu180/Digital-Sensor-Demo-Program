#pragma once
#include "Define.h"
#include "MN26005U_D.h"

class CMN26005U : public CSensorInfo {
public:
	CMN26005U()
	{
		ModelName = _T("MN26005U");
		pDieInfo = new CMN26005U_D;
#if defined(_MN26005U_3000) || defined(_DEBUG) || defined(_MN26005U)
		ModelVersion.insert(3000);//0.3
#endif
	}

	void Init(uint16_t version)
	{
		switch (version) {
		case 3000: {
			DieVersion = 3000;
			pDieInfo->Init(DieVersion);
			pDieDetail = &pDieInfo->DieDetail.at(DieVersion);

			pDieDetail->DieFunc = DF_NONE;
			pDieDetail->DlgStyle[MAIN_DIALOG] = NOSTYLE;
			pDieDetail->DlgName[MAIN_DIALOG] = _T("Main Dialog");
			pCtrlInfo[MAIN_DIALOG] = &pDieDetail->CtrlInfo[MAIN_DIALOG];

			pDieDetail->DlgStyle[TAB_1] = PAGE_STYLE1;
			pDieDetail->DlgName[TAB_1] = _T("Main");
			pCtrlInfo[TAB_1] = &pDieDetail->CtrlInfo[TAB_1];

			pDieDetail->DlgStyle[MODEL_1] = MODELLESS1;
			pDieDetail->DlgName[MODEL_1] = _T("Data Progress Bar");
			pCtrlInfo[MODEL_1] = &pDieDetail->CtrlInfo[MODEL_1];

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
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("WTIME");
						pCtrlDetail->NameMapping[0] = _T("Disable");
						pCtrlDetail->NameMapping[1] = _T("2 ms");
						pCtrlDetail->NameMapping[2] = _T("4 ms");
						pCtrlDetail->NameMapping[3] = _T("8 ms");
						pCtrlDetail->NameMapping[4] = _T("12 ms");
						pCtrlDetail->NameMapping[5] = _T("20 ms");
						pCtrlDetail->NameMapping[6] = _T("30 ms");
						pCtrlDetail->NameMapping[7] = _T("40 ms");
						pCtrlDetail->NameMapping[8] = _T("50 ms");
						pCtrlDetail->NameMapping[9] = _T("75 ms");
						pCtrlDetail->NameMapping[10] = _T("100 ms");
						pCtrlDetail->NameMapping[11] = _T("150 ms");
						pCtrlDetail->NameMapping[12] = _T("200 ms");
						pCtrlDetail->NameMapping[13] = _T("300 ms");
						pCtrlDetail->NameMapping[14] = _T("400 ms");
						pCtrlDetail->NameMapping[15] = _T("Single sensing");
					}

					DlgCheck.Init(TAB_1, make_pair(0, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = RADIO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->I2CWriteDelayMs = 0;
						pCtrlDetail->BitMapping[0] = _T("MODE");
						pCtrlDetail->NameMapping[0] = _T("IDLE mode");
						pCtrlDetail->NameMapping[1] = _T("ALS mode");
					}
				}

				pRegTable->RegInfo.at(0x01).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(4, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("ALS_INTEG");
						pCtrlDetail->NameMapping[2] = _T("8");
						pCtrlDetail->NameMapping[3] = _T("16");
						pCtrlDetail->NameMapping[4] = _T("32");
						pCtrlDetail->NameMapping[5] = _T("64");
						pCtrlDetail->NameMapping[6] = _T("128");
						pCtrlDetail->NameMapping[7] = _T("256");
						pCtrlDetail->NameMapping[8] = _T("512");
						pCtrlDetail->NameMapping[9] = _T("768");
						pCtrlDetail->NameMapping[10] = _T("1024");
						pCtrlDetail->NameMapping[11] = _T("2048");
						pCtrlDetail->NameMapping[12] = _T("4096");
						pCtrlDetail->NameMapping[13] = _T("6144");
						pCtrlDetail->NameMapping[14] = _T("8192");
						pCtrlDetail->NameMapping[15] = _T("10240");
					}

					DlgCheck.Init(TAB_1, make_pair(4, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALS_GAINS");
						pCtrlDetail->NameMapping[1] = _T("Middle gain");
						pCtrlDetail->NameMapping[3] = _T("Low gain");
					}
				}

				pRegTable->RegInfo.at(0x02).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(4, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALS_FILTER");
						pCtrlDetail->NameMapping[0] = _T("1-order filter setting");
						pCtrlDetail->NameMapping[1] = _T("2-order filter setting");
						pCtrlDetail->NameMapping[2] = _T("4-order filter setting");
						pCtrlDetail->NameMapping[3] = _T("8-order filter setting");
						pCtrlDetail->NameMapping[4] = _T("16-order filter setting");
						pCtrlDetail->NameMapping[5] = _T("32-order filter setting");
						pCtrlDetail->NameMapping[6] = _T("64-order filter setting");
						pCtrlDetail->NameMapping[7] = _T("128-order filter setting");
					}
				}

				pRegTable->RegInfo.at(0x06).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(4, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("INT_CTRL");
						pCtrlDetail->NameMapping[1] = _T("ALS_INT_FLAG");
						pCtrlDetail->NameMapping[3] = _T("Not used");
					}
				}

				pRegTable->RegInfo.at(0x07).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(4, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALS_PERSIST");
						pCtrlDetail->NameMapping[0] = _T("After 1 frame");
						pCtrlDetail->NameMapping[1] = _T("After 4 frame");
						pCtrlDetail->NameMapping[2] = _T("After 8 frame");
						pCtrlDetail->NameMapping[3] = _T("After 16 frame");
					}

					DlgCheck.Init(TAB_1, make_pair(4, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALS_INTTY");
						pCtrlDetail->NameMapping[0] = _T("disable mode");
						pCtrlDetail->NameMapping[1] = _T("binary mode");
						pCtrlDetail->NameMapping[2] = _T("active-low mode");
						pCtrlDetail->NameMapping[3] = _T("frame finish notice");
					}
				}

				pRegTable->RegInfo.at(0x08).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_1, make_pair(0, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS Low Threshold"), _T("ALS Low Threshold"));
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALS_INT_L");
					}
				}

				pRegTable->RegInfo.at(0x0A).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_1, make_pair(0, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS High Threshold"), _T("ALS High Threshold"));
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALS_INT_H");
					}
				}

				pRegTable->RegInfo.at(0x11).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_1, make_pair(6, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = BUTTON_GROUP;
						pCtrlDetail->CtrlName = make_pair(_T("Chip Reset"), _T(""));
						pCtrlDetail->CtrlFunc = CTRLFUNC_SWRST;
						pCtrlDetail->BitMapping[0] = _T("RESETN");
						pCtrlDetail->bActive = false;
						pCtrlDetail->I2CWriteDelayMs = 30;
					}

					DlgCheck.Init(TAB_1, make_pair(0, 5));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = RADIO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("SLEEP");
						pCtrlDetail->NameMapping[0] = _T("active mode");
						pCtrlDetail->NameMapping[1] = _T("sleep mode");
					}
				}

				pRegTable->RegInfo.at(0x12).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_1, make_pair(6, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALS_CMP_RSTN");
					}

					DlgCheck.Init(TAB_1, make_pair(6, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = BUTTON_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALS_LOCK");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("LOCK"), _T("LOCK"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("ALS_LOCK");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(1, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS"), _T("ALS"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("ALS_INT_FLAG");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("CMP_L"), _T("CMP_L"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("ALS_CMP_L");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(3, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("CMP_H"), _T("CMP_H"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("ALS_CMP_H");
					}
				}

				pRegTable->RegInfo.at(0x13).bEngMode = FALSE;
				{

					DlgCheck.Init(MODEL_1, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("CH0"), _T("CH0"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = G_BAR;
						pCtrlDetail->BitMapping[0] = _T("CH0_DATA");
					}

				}

				pRegTable->RegInfo.at(0x15).bEngMode = FALSE;
				{

					DlgCheck.Init(MODEL_1, make_pair(1, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("CH1"), _T("CH1"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = G_BAR;
						pCtrlDetail->BitMapping[0] = _T("CH1_DATA");
					}

					DlgCheck.Init(TAB_1, make_pair(0, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("CH1 Data"), _T("CH1 Data"));
						pCtrlDetail->CtrlType = PROGRESS_GROUP;
						pCtrlDetail->BitMapping[0] = _T("CH1_DATA");
					}
				}

				pRegTable->RegInfo.at(0x20).bEngMode = FALSE;
			}// pRegTable = &pDieDetail->RegisterTable;

			pRegTable->BitDetail.at(_T("MODE")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("SLEEP")).DefaultVal.at(0) = 0x00;

			pReadTable = &pDieDetail->RegisterTable.ReadTable;
			pReadTable->insert(CReadTable(0x12, 5, LogDec, true));

			break;
		}// case 3000:

		}// switch (version)
		CSensorInfo::Init();
	}// void Init(uint16_t version)
};
