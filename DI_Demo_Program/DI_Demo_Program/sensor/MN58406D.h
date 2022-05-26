#pragma once
#include "Define.h"
#include "MN58406D_D.h"

class CMN58406D : public CSensorInfo {
public:
	CMN58406D()
	{
		ModelName = _T("MN58406D");
		pDieInfo = new CMN58406D_D;
#if defined(_MN58406D_4000) || defined(_DEBUG) || defined(_MN58406D)
		ModelVersion.insert(4000);//0.4
#endif
	}

	void Init(uint16_t version)
	{
		switch (version) {
		case 4000: {
			DieVersion = 4000;
			pDieInfo->Init(DieVersion);
			pDieDetail = &pDieInfo->DieDetail.at(DieVersion);

			pDieDetail->DieFunc = DF_NONE;
			pDieDetail->DlgStyle[MAIN_DIALOG] = NOSTYLE;
			pDieDetail->DlgName[MAIN_DIALOG] = _T("Main Dialog");
			pCtrlInfo[MAIN_DIALOG] = &pDieDetail->CtrlInfo[MAIN_DIALOG];

			pDieDetail->DlgStyle[TAB_1] = PAGE_STYLE1;
			pDieDetail->DlgName[TAB_1] = _T("System");
			pCtrlInfo[TAB_1] = &pDieDetail->CtrlInfo[TAB_1];

			pDieDetail->DlgStyle[TAB_2] = PAGE_STYLE1;
			pDieDetail->DlgName[TAB_2] = _T("ALS+PS");
			pCtrlInfo[TAB_2] = &pDieDetail->CtrlInfo[TAB_2];

			pDieDetail->DlgStyle[MODEL_1] = MODELLESS1;
			pDieDetail->DlgName[MODEL_1] = _T("Data Progress Bar");
			pCtrlInfo[MODEL_1] = &pDieDetail->CtrlInfo[MODEL_1];

			pDieDetail->DlgStyle[MODEL_3] = MODELLESS_LIST;
			pDieDetail->DlgName[MODEL_3] = _T("Register Table");

			pRegTable = &pDieDetail->RegisterTable;
			{
				pRegTable->RegInfo.at(0x00).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(6, 0));
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
						pCtrlDetail->NameMapping[2] = _T("PS mode");
						pCtrlDetail->NameMapping[3] = _T("PS and ALS mode");
					}
				}

				pRegTable->RegInfo.at(0x01).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 0));
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

					DlgCheck.Init(TAB_2, make_pair(0, 2));
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
					DlgCheck.Init(TAB_2, make_pair(0, 4));
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

				pRegTable->RegInfo.at(0x03).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PS_INTEG");
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

					DlgCheck.Init(TAB_2, make_pair(2, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PS_GAINS");
						pCtrlDetail->NameMapping[1] = _T("Middle gain");
						pCtrlDetail->NameMapping[3] = _T("Low gain");
					}
				}

				pRegTable->RegInfo.at(0x04).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 4));
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

				pRegTable->RegInfo.at(0x05).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PS_IR_MODE");
						pCtrlDetail->NameMapping[0] = _T("current source");
						pCtrlDetail->NameMapping[1] = _T("2-order filter setting");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PS_IR_DRIVE");
						pCtrlDetail->NameMapping[3] = _T("10mA");
					}
				}

				pRegTable->RegInfo.at(0x06).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(6, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("INT_CTRL");
						pCtrlDetail->NameMapping[0] = _T("ALS_INT_FLAG OR PS_INT_FLAG");
						pCtrlDetail->NameMapping[1] = _T("ALS_INT_FLAG");
						pCtrlDetail->NameMapping[2] = _T("PS_INT_FLAG");
						pCtrlDetail->NameMapping[3] = _T("ALS_INT_FLAG AND PS_INT_FLAG");
					}

					DlgCheck.Init(TAB_2, make_pair(2, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PS_PERSIST");
						pCtrlDetail->NameMapping[0] = _T("After 1 frame");
						pCtrlDetail->NameMapping[1] = _T("After 4 frame");
						pCtrlDetail->NameMapping[2] = _T("After 8 frame");
						pCtrlDetail->NameMapping[3] = _T("After 16 frame");
					}

					DlgCheck.Init(TAB_2, make_pair(2, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PS_INTTY");
						pCtrlDetail->NameMapping[0] = _T("disable mode");
						pCtrlDetail->NameMapping[1] = _T("binary mode");
						pCtrlDetail->NameMapping[2] = _T("active-low mode");
						pCtrlDetail->NameMapping[3] = _T("frame finish notice");
					}
				}

				pRegTable->RegInfo.at(0x07).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 6));
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

					DlgCheck.Init(TAB_2, make_pair(0, 8));
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

					DlgCheck.Init(TAB_2, make_pair(0, 16));
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

					DlgCheck.Init(TAB_2, make_pair(0, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS High Threshold"), _T("ALS High Threshold"));
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALS_INT_H");
					}
				}

				pRegTable->RegInfo.at(0x0C).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_2, make_pair(4, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Low Threshold"), _T("PS Low Threshold"));
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PS_INT_L");
					}
				}

				pRegTable->RegInfo.at(0x0E).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_2, make_pair(4, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS High Threshold"), _T("PS High Threshold"));
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PS_INT_H");
					}
				}

				pRegTable->RegInfo.at(0x11).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_1, make_pair(4, 2));
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

					DlgCheck.Init(TAB_1, make_pair(0, 8));
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

					DlgCheck.Init(TAB_2, make_pair(6, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ALS_CMP_RSTN");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 6));
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
						pCtrlDetail->CtrlName = make_pair(_T("ALOCK"), _T("ALOCK"));
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
						pCtrlDetail->CtrlName = make_pair(_T("ACMP_L"), _T("ACMP_L"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("ALS_CMP_L");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(3, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ACMP_H"), _T("ACMP_H"));
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
						pCtrlDetail->CtrlColor.first = C_BAR;
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

					DlgCheck.Init(TAB_2, make_pair(0, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("CH1 Data"), _T("CH1 Data"));
						pCtrlDetail->CtrlType = PROGRESS_GROUP;
						pCtrlDetail->BitMapping[0] = _T("CH1_DATA");
					}
				}

				pRegTable->RegInfo.at(0x1B).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_2, make_pair(6, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PS_CMP_RSTN");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = BUTTON_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PS_LOCK");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PLOCK"), _T("PLOCK"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PS_LOCK");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(5, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS"), _T("PS"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PS_INT_FLAG");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(6, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PCMP_L"), _T("PCMP_L"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PS_CMP_L");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(7, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PCMP_H"), _T("PCMP_H"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PS_CMP_H");
					}
				}

				pRegTable->RegInfo.at(0x1C).bEngMode = FALSE;
				{

					DlgCheck.Init(MODEL_1, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PALS"), _T("PALS"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = IR_BAR;
						pCtrlDetail->BitMapping[0] = _T("PALS_DATA");
					}

				}

				pRegTable->RegInfo.at(0x15).bEngMode = FALSE;
				{

					DlgCheck.Init(MODEL_1, make_pair(3, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS"), _T("PS"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = PS_BAR;
						pCtrlDetail->BitMapping[0] = _T("PS_DATA");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Data"), _T("PS Data"));
						pCtrlDetail->CtrlType = PROGRESS_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PS_DATA");
					}
				}

				pRegTable->RegInfo.at(0x20).bEngMode = FALSE;

				pRegTable->RegInfo.at(0x22).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PS_OFFSET");
					}
				}
			}// pRegTable = &pDieDetail->RegisterTable;

			pRegTable->BitDetail.at(_T("MODE")).DefaultVal.at(0) = 0x03;
			pRegTable->BitDetail.at(_T("SLEEP")).DefaultVal.at(0) = 0x00;

			pReadTable = &pDieDetail->RegisterTable.ReadTable;
			pReadTable->insert(CReadTable(0x12, 5, LogDec, true));
			pReadTable->insert(CReadTable(0x1B, 5, LogDec, true));

			break;
		}// case 4000:

		}// switch (version)
		CSensorInfo::Init();
	}// void Init(uint16_t version)
};
