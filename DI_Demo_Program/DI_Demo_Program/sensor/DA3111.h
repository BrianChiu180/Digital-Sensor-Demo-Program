#pragma once
#include "Define.h"
#include "DA3111T.h"

class CDA3111 : public CSensorInfo {
public:
	CDA3111()
	{
		ModelName = _T("DA3111");
		pDieInfo = new CDA3111T;
#if defined(_DA3111_1000) || defined(_DEBUG) || defined(_DA3111)
		ModelVersion.insert(1000);//0.1a DA3111TAP
#endif


#if defined(_DEBUG) || defined(_DA3111)
		ModelSelAddress.insert(0x1C);
		ModelSelAddress.insert(0x1D);
		ModelSelAddress.insert(0x1F);
		ModelDefaultAddress = 0x1C;
#endif
	}

	void Init(uint16_t version)
	{
		switch (version) {
		case 1000: {
			DieVersion = 10000;
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
			pDieDetail->DlgName[TAB_2] = _T("PS + ALS");
			pCtrlInfo[TAB_2] = &pDieDetail->CtrlInfo[TAB_2];

			pDieDetail->DlgStyle[TAB_3] = PAGE_STYLE1;
			pDieDetail->DlgName[TAB_3] = _T("IR");
			pCtrlInfo[TAB_3] = &pDieDetail->CtrlInfo[TAB_3];

#ifdef _RD
			pDieDetail->DlgStyle[TAB_4] = PAGE_STYLE1;
			pDieDetail->DlgName[TAB_4] = _T("RD");
			pCtrlInfo[TAB_4] = &pDieDetail->CtrlInfo[TAB_4];

			pDieDetail->DlgStyle[TAB_5] = PAGE_STYLE1;
			pDieDetail->DlgName[TAB_5] = _T("RD2");
			pCtrlInfo[TAB_5] = &pDieDetail->CtrlInfo[TAB_5];
#endif
			pDieDetail->DlgStyle[MODEL_1] = MODELLESS1;
			pDieDetail->DlgName[MODEL_1] = _T("Data Progress Bar");
			pCtrlInfo[MODEL_1] = &pDieDetail->CtrlInfo[MODEL_1];

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
						pCtrlDetail->I2CWriteDelayMs = 10;
						pCtrlDetail->CtrlName = make_pair(_T("ALS Enable"), _T(""));
						pCtrlDetail->BitMapping[0] = _T("EnAls");
					}

					DlgCheck.Init(TAB_1, make_pair(0, 5));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->I2CWriteDelayMs = 10;
						pCtrlDetail->CtrlName = make_pair(_T("PS Enable"), _T(""));
						pCtrlDetail->BitMapping[0] = _T("EnPs");
					}

#ifdef _DEBUG
					DlgCheck.Init(TAB_1, make_pair(0, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->I2CWriteDelayMs = 10;
						pCtrlDetail->CtrlName = make_pair(_T("IR Enable"), _T(""));
						pCtrlDetail->BitMapping[0] = _T("EnIr");
					}
#endif

#ifdef _RD
					DlgCheck.Init(TAB_1, make_pair(0, 7));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->I2CWriteDelayMs = 10;
						pCtrlDetail->BitMapping[0] = _T("EnDyna");
					}

					DlgCheck.Init(TAB_1, make_pair(0, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->I2CWriteDelayMs = 10;
						pCtrlDetail->BitMapping[0] = _T("EnPsAll");
					}

					DlgCheck.Init(TAB_1, make_pair(0, 9));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->I2CWriteDelayMs = 10;
						pCtrlDetail->BitMapping[0] = _T("EnPsAen");
					}
#endif
				}

				pRegTable->RegInfo.at(0xF1).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(6, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsIen");
					}

					DlgCheck.Init(TAB_1, make_pair(6, 5));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsIen");
					}

#ifdef _DEBUG
					DlgCheck.Init(TAB_1, make_pair(6, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrIen");
					}
#endif
#ifdef _RD
					DlgCheck.Init(TAB_1, make_pair(6, 7));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("SyncIen");
					}

					DlgCheck.Init(TAB_1, make_pair(6, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsObjIen");
					}

					DlgCheck.Init(TAB_1, make_pair(6, 9));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PushPull");
					}
#endif
				}

				pRegTable->RegInfo.at(0xF2).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(6, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsHalt");
					}

					DlgCheck.Init(TAB_1, make_pair(6, 13));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsHalt");
					}

#ifdef _DEBUG
					DlgCheck.Init(TAB_3, make_pair(6, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrHalt");
					}
#endif
					DlgCheck.Init(TAB_1, make_pair(2, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ReadClear");
						pCtrlDetail->NameMapping[0] = _T("Manually Clear");
						pCtrlDetail->NameMapping[1] = _T("Auto Clear");
					}
				}

				pRegTable->RegInfo.at(0xF3).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(6, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("Operation");
						pCtrlDetail->NameMapping[0] = _T("Standby Mode");
						pCtrlDetail->NameMapping[1] = _T("Normal Mode");
					}
#ifdef _RD
					DlgCheck.Init(TAB_4, make_pair(0, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("VbgTime");
						pCtrlDetail->NameMapping[0] = _T("30 us");
						pCtrlDetail->NameMapping[1] = _T("15 us");
						pCtrlDetail->NameMapping[2] = _T("20 us");
						pCtrlDetail->NameMapping[3] = _T("25 us");
						pCtrlDetail->NameMapping[4] = _T("40 us");
						pCtrlDetail->NameMapping[5] = _T("50 us");
						pCtrlDetail->NameMapping[6] = _T("60 us");
						pCtrlDetail->NameMapping[6] = _T("70 us");
					}

					DlgCheck.Init(TAB_4, make_pair(2, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("FallingPor");
					}
#endif
				}

				pRegTable->RegInfo.at(0xF4).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(4, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = BUTTON_GROUP;
						pCtrlDetail->CtrlName = make_pair(_T("Softwave Reset"), _T(""));
						pCtrlDetail->CtrlFunc = CTRLFUNC_SWRST;
						pCtrlDetail->BitMapping[0] = _T("EnSw");
						pCtrlDetail->I2CWriteDelayMs = 30;
					}
				}

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
					DlgCheck.Init(MAIN_DIALOG, make_pair(1, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS"), _T("PS"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PsInt");
					}
#ifdef _DEBUG
					DlgCheck.Init(MAIN_DIALOG, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("IR"), _T("IR"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("IrInt");
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

					DlgCheck.Init(TAB_1, make_pair(4, 12));
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
						pCtrlDetail->CtrlName = make_pair(_T("ALS Err"), _T("ALS Err"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("AlsErr");
					}

#ifdef _RD
					DlgCheck.Init(MAIN_DIALOG, make_pair(9, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Err"), _T("PS Err"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PsErr");
					}
#endif
#ifdef _DEBUG
					DlgCheck.Init(MAIN_DIALOG, make_pair(10, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("IR Err"), _T("IR Err"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("IrErr");
					}
#endif
					DlgCheck.Init(MAIN_DIALOG, make_pair(11, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Ps Err Off"), _T("Ps Err Off"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PsErrOff");
					}

#ifdef _RD
					DlgCheck.Init(MAIN_DIALOG, make_pair(12, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Ps Err On"), _T("Ps Err On"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PsErrOn");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(13, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("IR Err Off"), _T("IR Err Off"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("IrErrOff");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(14, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("IR Err On"), _T("IR Err On"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("IrErrOn");
					}
#endif
					DlgCheck.Init(MAIN_DIALOG, make_pair(15, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("OBJ"), _T("OBJ"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PsObj");
					}
				}


				/* PS Data */
				pRegTable->RegInfo.at(0x00).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS"), _T("PS"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = PS_BAR;
						pCtrlDetail->BitMapping[0] = _T("PsCh");
					}

					DlgCheck.Init(TAB_2, make_pair(0, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Data"), _T("PS Data"));
						pCtrlDetail->CtrlType = PROGRESS_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsCh");
					}
				}

#ifdef _DEBUG
				/* IR Data */
				pRegTable->RegInfo.at(0x02).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(1, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("IR"), _T("IR"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = IR_BAR;
						pCtrlDetail->BitMapping[0] = _T("IrCh");
					}
				}
#endif
				/* ALS CH0 Data */
				pRegTable->RegInfo.at(0x04).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ACH0"), _T("ACH0"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = G_BAR;
						pCtrlDetail->BitMapping[0] = _T("AlsCh0");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ACH0 Data"), _T("ACH0 Data"));
						pCtrlDetail->CtrlType = PROGRESS_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_SELDATA;
						pCtrlDetail->BitMapping[0] = _T("AlsCh0");
						pCtrlDetail->RegMapping[0] = 0x04;
						pCtrlDetail->RegMapping[1] = 0x06;
					}
				}

				/* ALS CH1 Data */
				pRegTable->RegInfo.at(0x06).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(3, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ACH1"), _T("ACH1"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = C_BAR;
						pCtrlDetail->BitMapping[0] = _T("AlsCh1");
					}
				}
#ifdef _RD
				/* Debug Data */
				pRegTable->RegInfo.at(0x0C).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Debug"), _T("Debug"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = IR_BAR;
						pCtrlDetail->BitMapping[0] = _T("DbgCh");
					}
				}

				/* Temperature Data */
				pRegTable->RegInfo.at(0x0E).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(5, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("TMP"), _T("TMP"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = IR_BAR;
						pCtrlDetail->BitMapping[0] = _T("TmpCh");
					}
				}

#endif
				pRegTable->RegInfo.at(0x4F).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(6, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Nap Time"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("NapTime");
						for (uint8_t i = 0; i < 0xFF; i++)
						{
							csTemp.Format(_T("%d ms"), i * 20);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x50).bEngMode = FALSE;
				{
#ifdef _RD
					DlgCheck.Init(TAB_1, make_pair(2, 5));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsRand");
					}
#endif
					DlgCheck.Init(TAB_1, make_pair(2, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsCh1On");
					}
				}

#ifdef _RD
				pRegTable->RegInfo.at(0x51).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("AlsIntWdth");
						pCtrlDetail->NameMapping[0] = _T("11.0 ms(0)");
						pCtrlDetail->NameMapping[1] = _T("11.0 ms(1)");
						for (uint8_t i = 2; i < 0x80; i++)
						{
							csTemp.Format(_T("%.1f ms"), (float)10.5f + ((float)i*0.5f));
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}
#endif

				pRegTable->RegInfo.at(0x52).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("AlsIntTime");
						pCtrlDetail->NameMapping[0] = _T("100 ms(0)");
						pCtrlDetail->NameMapping[1] = _T("100 ms(1)");
						for (uint8_t i = 2; i < 0x20; i++)
						{
							csTemp.Format(_T("%d ms"), i * 100);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

#ifdef _RD
				pRegTable->RegInfo.at(0x53).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(0, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("AlsPrePuc");
						for (uint8_t i = 0; i < 0x10; i++)
						{
							csTemp.Format(_T("%d C"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}
#endif

#ifdef _RD
				pRegTable->RegInfo.at(0x54).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(0, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Select driving current"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsDrv");
						pCtrlDetail->NameMapping[0] = _T("0/16 IDrvMax");
						for (uint8_t i = 1; i < 0x10; i++)
						{
							csTemp.Format(_T("%d/16 IDrvMax"), i + 1);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}

					DlgCheck.Init(TAB_5, make_pair(0, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsDrvLed");
						pCtrlDetail->NameMapping[0] = _T("IDrvMax = 16 mA");
						pCtrlDetail->NameMapping[1] = _T("IDrvMax = 160 mA");
					}

					DlgCheck.Init(TAB_5, make_pair(0, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsDrvTurbo");
					}

					DlgCheck.Init(TAB_5, make_pair(0, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsDrvForce");
						pCtrlDetail->NameMapping[0] = _T("Driving Normally (Default)");
						pCtrlDetail->NameMapping[1] = _T("Driving Turn off");
						pCtrlDetail->NameMapping[2] = _T("Force Driving as DC when Operation = 1");
						pCtrlDetail->NameMapping[3] = _T("Driving Normally");
					}
				}

				pRegTable->RegInfo.at(0x58).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(6, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("DachFlor");
					}

					DlgCheck.Init(TAB_5, make_pair(6, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("DachCnst");
					}
				}
#endif

				pRegTable->RegInfo.at(0x5B).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_SELDATA;
						pCtrlDetail->BitMapping[0] = _T("AlsIntSrc");
						pCtrlDetail->NameMapping[0] = _T("AlsCh0 as AlsData");
						pCtrlDetail->NameMapping[1] = _T("AlsCh1 as AlsData");
						pCtrlDetail->RegMapping[0] = 0x04;
						pCtrlDetail->RegMapping[1] = 0x06;
					}

					DlgCheck.Init(TAB_2, make_pair(4, 4));
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

					DlgCheck.Init(TAB_2, make_pair(4, 16));
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

					DlgCheck.Init(TAB_2, make_pair(4, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS High Threshold"), _T("ALS High Threshold"));
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsThHigh");
					}
				}

				pRegTable->RegInfo.at(0x60).bEngMode = FALSE;
				{
#ifdef _RD
					DlgCheck.Init(TAB_4, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsGain");
					}
#endif
					DlgCheck.Init(TAB_2, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsAdcBit");
						pCtrlDetail->NameMapping[0] = _T("9-bit");
						pCtrlDetail->NameMapping[1] = _T("10-bit");
						pCtrlDetail->NameMapping[2] = _T("11-bit");
						pCtrlDetail->NameMapping[3] = _T("12-bit");

						pCtrlDetail->CtrlFunc |= CTRLFUNC_CHANGE_RANGE;
						pCtrlDetail->RegMapping[0] = 0x00;
						pCtrlDetail->RegMapping[1] = 0x6C;
						pCtrlDetail->RegMapping[2] = 0x6E;
						pCtrlDetail->RangeMapping[0] = make_pair(0, 511);
						pCtrlDetail->RangeMapping[1] = make_pair(0, 1023);
						pCtrlDetail->RangeMapping[2] = make_pair(0, 2047);
						pCtrlDetail->RangeMapping[3] = make_pair(0, 4095);

					}
				}

				pRegTable->RegInfo.at(0x61).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsIntPuw");
						pCtrlDetail->NameMapping[0] = _T("1W (Default)");
						for (uint8_t i = 1; i < 0x80; i++)
						{
							csTemp.Format(_T("%d W"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x62).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsIntPuc");
						pCtrlDetail->NameMapping[0] = _T("1 pulse count (Default)");
						for (uint8_t i = 1; i < 0x40; i++)
						{
							csTemp.Format(_T("%d pulse count"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x63).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsPrePuc");
						pCtrlDetail->NameMapping[0] = _T("No Pre-Heat Pulse Count");
						for (uint8_t i = 1; i < 0x10; i++)
						{
							csTemp.Format(_T("%d Pre-Heat Pulse Count"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x64).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Select driving current"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsDrv");
						pCtrlDetail->NameMapping[0] = _T("0/16 IDrvMax");
						for (uint8_t i = 1; i < 0x10; i++)
						{
							csTemp.Format(_T("%d/16 IDrvMax"), i + 1);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}

					DlgCheck.Init(TAB_2, make_pair(2, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsDrvLed");
						pCtrlDetail->NameMapping[0] = _T("IDrvMax = 16 mA");
						pCtrlDetail->NameMapping[1] = _T("IDrvMax = 160 mA");
					}
#ifdef _RD
					DlgCheck.Init(TAB_4, make_pair(0, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsDrvTurbo");
					}

					DlgCheck.Init(TAB_4, make_pair(0, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsDrvForce");
						pCtrlDetail->NameMapping[0] = _T("Driving Normally (Default)");
						pCtrlDetail->NameMapping[1] = _T("Driving Turn off");
						pCtrlDetail->NameMapping[2] = _T("Force Driving as DC when Operation = 1");
						pCtrlDetail->NameMapping[3] = _T("Driving Normally");
					}
#endif
				}

#ifdef _RD
				pRegTable->RegInfo.at(0x65).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_4, make_pair(0, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsCtGain");
						pCtrlDetail->NameMapping[0] = _T("x1");
						pCtrlDetail->NameMapping[1] = _T("x2");
						pCtrlDetail->NameMapping[2] = _T("x3");
					}

					DlgCheck.Init(TAB_4, make_pair(0, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsCtDac");
						for (uint8_t i = 0; i < 0x20; i++)
						{
							csTemp.Format(_T("%d step"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x66).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_4, make_pair(0, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsIambDac");
					}

					DlgCheck.Init(TAB_4, make_pair(0, 15));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsIambOn");
					}
				}

				pRegTable->RegInfo.at(0x67).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_4, make_pair(2, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsIctDac");
					}

					DlgCheck.Init(TAB_4, make_pair(2, 15));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsIctOn");
					}
				}

				pRegTable->RegInfo.at(0x68).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_4, make_pair(6, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("DpchFlor");
					}

					DlgCheck.Init(TAB_4, make_pair(6, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("DpchCnst");
					}
				}
#endif

				pRegTable->RegInfo.at(0x6B).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsPers");
						pCtrlDetail->NameMapping[0] = _T("Every Cycles");
						for (uint8_t i = 1; i < 0x10; i++)
						{
							csTemp.Format(_T("After %d Cycles"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}

					DlgCheck.Init(TAB_2, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsIntAlgo");
						pCtrlDetail->NameMapping[0] = _T("Zone Interrupt Mode");
						pCtrlDetail->NameMapping[1] = _T("Hysterics Interrupt Mode");
					}

					DlgCheck.Init(TAB_2, make_pair(2, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsNapAlgo");
						pCtrlDetail->NameMapping[0] = _T("PsNapTime is fixed");
						pCtrlDetail->NameMapping[1] = _T("PsNapTime is variable");
					}
				}

				/* PS Calibration */
				pRegTable->RegInfo.at(0x69).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_2, make_pair(2, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Calibration"), _T("PS Calibration"));
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsCalb");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = BUTTON_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CALIBRATION;
						pCtrlDetail->BitMapping[0] = _T("PsCalb");
						pCtrlDetail->RegMapping[0] = 0x00;
					}
				}

				/* PS Low Threshold */
				pRegTable->RegInfo.at(0x6C).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_2, make_pair(0, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Low Threshold"), _T("PS Low Threshold"));
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsThLow");
					}
				}

				/* PS High Threshold */
				pRegTable->RegInfo.at(0x6E).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_2, make_pair(0, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS High Threshold"), _T("PS High Threshold"));
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsThHigh");
					}
				}

#ifdef _DEBUG
				pRegTable->RegInfo.at(0x70).bEngMode = FALSE;
				{
#ifdef _RD
					DlgCheck.Init(TAB_3, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrGain");
					}
#endif
					DlgCheck.Init(TAB_3, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("IrAdcBit");
						pCtrlDetail->NameMapping[0] = _T("9-bit");
						pCtrlDetail->NameMapping[1] = _T("10-bit");
						pCtrlDetail->NameMapping[2] = _T("11-bit");
						pCtrlDetail->NameMapping[3] = _T("12-bit");

						pCtrlDetail->CtrlFunc |= CTRLFUNC_CHANGE_RANGE;
						pCtrlDetail->RegMapping[0] = 0x02;
						pCtrlDetail->RangeMapping[0] = make_pair(0, 511);
						pCtrlDetail->RangeMapping[1] = make_pair(0, 1023);
						pCtrlDetail->RangeMapping[2] = make_pair(0, 2047);
						pCtrlDetail->RangeMapping[3] = make_pair(0, 4095);
					}

					DlgCheck.Init(TAB_3, make_pair(0, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("IrMean");
						pCtrlDetail->NameMapping[0] = _T("1 Time");
						pCtrlDetail->NameMapping[1] = _T("2 Time");
						pCtrlDetail->NameMapping[2] = _T("4 Time");
						pCtrlDetail->NameMapping[3] = _T("8 Time");
					}
				}

				pRegTable->RegInfo.at(0x71).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(0, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrIntPuw");
						pCtrlDetail->NameMapping[0] = _T("1 us(Default)");
						pCtrlDetail->NameMapping[1] = _T("1 us");
						for (uint8_t i = 2; i < 0x80; i++)
						{
							csTemp.Format(_T("%d us"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

#ifdef _RD
				pRegTable->RegInfo.at(0x72).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(2, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrIntPuc");
						pCtrlDetail->NameMapping[0] = _T("1C (Default)");
						pCtrlDetail->NameMapping[1] = _T("1C");
						for (uint8_t i = 2; i < 0x10; i++)
						{
							csTemp.Format(_T("%d C"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}
				pRegTable->RegInfo.at(0x73).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(2, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrPrePuc");
						pCtrlDetail->NameMapping[0] = _T("0 C");
						for (uint8_t i = 1; i < 0x10; i++)
						{
							csTemp.Format(_T("%d C"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x74).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(2, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrDrv");
						pCtrlDetail->NameMapping[0] = _T("0/16 IDrvMax");
						for (uint8_t i = 1; i < 0x10; i++)
						{
							csTemp.Format(_T("%d/16 IDrvMax"), i + 1);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}

					DlgCheck.Init(TAB_3, make_pair(2, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrDrvLed");
						pCtrlDetail->NameMapping[0] = _T("IDrvMax = 16 mA");
						pCtrlDetail->NameMapping[1] = _T("IDrvMax = 160 mA");
					}

					DlgCheck.Init(TAB_3, make_pair(2, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrDrvTurbo");
					}

					DlgCheck.Init(TAB_3, make_pair(2, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrDrvForce");
						pCtrlDetail->NameMapping[0] = _T("Driving Normally (Default)");
						pCtrlDetail->NameMapping[1] = _T("Driving Turn off");
						pCtrlDetail->NameMapping[2] = _T("Force Driving as DC when Operation = 1");
						pCtrlDetail->NameMapping[3] = _T("Driving Normally");
					}
				}

				pRegTable->RegInfo.at(0x75).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(0, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrCtGain");
						pCtrlDetail->NameMapping[0] = _T("x1");
						pCtrlDetail->NameMapping[1] = _T("x2");
						pCtrlDetail->NameMapping[2] = _T("x3");
					}

					DlgCheck.Init(TAB_3, make_pair(0, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrCtDac");
						for (uint8_t i = 0; i < 0x20; i++)
						{
							csTemp.Format(_T("%d step"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x76).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(0, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrIambDac");
					}

					DlgCheck.Init(TAB_3, make_pair(0, 15));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrIambOn");
					}
				}

				pRegTable->RegInfo.at(0x77).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(2, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrIctDac");
					}

					DlgCheck.Init(TAB_3, make_pair(2, 15));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrIctOn");
					}
				}

				pRegTable->RegInfo.at(0x78).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("DichFlor");
					}

					DlgCheck.Init(TAB_3, make_pair(4, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("DichCnst");
					}
				}

				pRegTable->RegInfo.at(0x28).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_4, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsUnit");
					}
				}

				pRegTable->RegInfo.at(0x29).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_4, make_pair(2, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsLcf");
					}
				}

				pRegTable->RegInfo.at(0x2A).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_4, make_pair(2, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsTcfLow");
					}
				}

				pRegTable->RegInfo.at(0x2B).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_4, make_pair(2, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsTcfHigh");
					}
				}

				pRegTable->RegInfo.at(0x2C).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(4, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrUnit");
					}
				}

				pRegTable->RegInfo.at(0x2D).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(4, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrLcf");
					}
				}

				pRegTable->RegInfo.at(0x2E).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(4, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrTcfLow");
					}
				}

				pRegTable->RegInfo.at(0x2F).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(4, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrTcfHigh");
					}
				}

				pRegTable->RegInfo.at(0x30).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsUnit0");
					}
				}

				pRegTable->RegInfo.at(0x31).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(2, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsLcf0");
					}
				}

				pRegTable->RegInfo.at(0x32).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(2, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsTcfLow0");
					}
				}

				pRegTable->RegInfo.at(0x33).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(2, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsTcfHigh0");
					}
				}

				pRegTable->RegInfo.at(0x34).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(2, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsUnit0");
					}
				}

				pRegTable->RegInfo.at(0x35).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(2, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsLcf0");
					}
				}

				pRegTable->RegInfo.at(0x36).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(2, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsTcfLow0");
					}
				}

				pRegTable->RegInfo.at(0x37).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(2, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsTcfHigh0");
					}
				}

				pRegTable->RegInfo.at(0x40).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(0, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsV2i");
					}

					DlgCheck.Init(TAB_5, make_pair(0, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsCap");
					}
				}

				pRegTable->RegInfo.at(0x41).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_4, make_pair(2, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsV2i");
					}

					DlgCheck.Init(TAB_4, make_pair(2, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsCap");
					}
				}

				pRegTable->RegInfo.at(0x42).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(4, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrV2i");
					}

					DlgCheck.Init(TAB_3, make_pair(4, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrCap");
					}
				}

				pRegTable->RegInfo.at(0x43).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_4, make_pair(6, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("TmpV2i");
					}

					DlgCheck.Init(TAB_4, make_pair(6, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("TmpCap");
					}
				}

				pRegTable->RegInfo.at(0x44).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_4, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ibtest_sel");
					}

					DlgCheck.Init(TAB_4, make_pair(4, 1));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("test_sel");
					}

					DlgCheck.Init(TAB_4, make_pair(4, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("temp_mux");
					}

					DlgCheck.Init(TAB_4, make_pair(4, 3));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ana_test_en");
					}

					DlgCheck.Init(TAB_4, make_pair(4, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ana_test");
					}
				}

				pRegTable->RegInfo.at(0x45).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_4, make_pair(4, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("clkm_vbs");
					}

					DlgCheck.Init(TAB_4, make_pair(4, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("vref_op_sel");
					}

					DlgCheck.Init(TAB_4, make_pair(4, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("vtoph_set");
					}

					DlgCheck.Init(TAB_4, make_pair(4, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("vdiode_sel");
					}
				}

				pRegTable->RegInfo.at(0x46).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_4, make_pair(4, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("losc_trim");
					}
				}

				pRegTable->RegInfo.at(0x47).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_4, make_pair(6, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ctrl0ana");
					}
				}

				pRegTable->RegInfo.at(0x48).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_4, make_pair(6, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ctrl1ana");
					}
				}

				pRegTable->RegInfo.at(0x49).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_4, make_pair(4, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("CpchCnst");
					}

					DlgCheck.Init(TAB_4, make_pair(6, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("SlotTmp");
					}
				}

				pRegTable->RegInfo.at(0x4A).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("VarDuty");
					}

					DlgCheck.Init(TAB_5, make_pair(4, 1));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("Pxsh");
					}

					DlgCheck.Init(TAB_5, make_pair(4, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ConvMin");
					}

					DlgCheck.Init(TAB_5, make_pair(4, 3));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("LeakOut");
					}

					DlgCheck.Init(TAB_5, make_pair(4, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("TgenDouble");
					}

					DlgCheck.Init(TAB_5, make_pair(4, 5));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("Force");
					}
				}

				pRegTable->RegInfo.at(0x4B).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(4, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrBias");
					}

					DlgCheck.Init(TAB_5, make_pair(4, 7));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsBias");
					}

					DlgCheck.Init(TAB_5, make_pair(4, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsBias");
					}

					DlgCheck.Init(TAB_5, make_pair(4, 9));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrDark");
					}

					DlgCheck.Init(TAB_5, make_pair(4, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsDark");
					}

					DlgCheck.Init(TAB_5, make_pair(4, 11));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsDark");
					}
				}

				pRegTable->RegInfo.at(0x4C).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(4, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsDc");
					}
				}

				pRegTable->RegInfo.at(0x4D).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(4, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsDc");
					}
				}

				pRegTable->RegInfo.at(0x4E).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(4, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrDc");
					}
				}

				pRegTable->RegInfo.at(0x4E).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(6, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("TTAR");
					}
				}

				pRegTable->RegInfo.at(0x4E).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(6, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("LTAR");
					}
				}

				pRegTable->RegInfo.at(0x4E).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(6, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ForceData");
					}
				}

				pRegTable->RegInfo.at(0x4E).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(6, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ForceTmp");
					}
				}

				pRegTable->RegInfo.at(0xD0).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_4, make_pair(0, 0));
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

				pRegTable->RegInfo.at(0xD1).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(6, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ForcePad");
						pCtrlDetail->NameMapping[0] = _T("Digital Output");
						pCtrlDetail->NameMapping[1] = _T("Analog Output");
					}

					DlgCheck.Init(TAB_5, make_pair(6, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("View");
						pCtrlDetail->NameMapping[0] = _T("INT");
						pCtrlDetail->NameMapping[1] = _T("clkt (1.25M)");
						pCtrlDetail->NameMapping[2] = _T("GND");
						pCtrlDetail->NameMapping[3] = _T("VDD");
						pCtrlDetail->NameMapping[4] = _T("led");
						pCtrlDetail->NameMapping[5] = _T("~PsObj");
						pCtrlDetail->NameMapping[10] = _T("en_Fadc0");
						pCtrlDetail->NameMapping[11] = _T("en_Fadc1");
						pCtrlDetail->NameMapping[12] = _T("en_Fadc2");
						pCtrlDetail->NameMapping[13] = _T("en_Fadc3");
						pCtrlDetail->NameMapping[14] = _T("en_Tadc0");
						pCtrlDetail->NameMapping[15] = _T("en_Tadc1");
						pCtrlDetail->NameMapping[16] = _T("clkm (5M)");
						pCtrlDetail->NameMapping[17] = _T("clkw(10K)");
						pCtrlDetail->NameMapping[18] = _T("time_fire");
						pCtrlDetail->NameMapping[19] = _T("tgen");
						pCtrlDetail->NameMapping[20] = _T("led_ctrl");
						pCtrlDetail->NameMapping[21] = _T("vbg_fast");
						pCtrlDetail->NameMapping[26] = _T("Fadc0");
						pCtrlDetail->NameMapping[27] = _T("Fadc1");
						pCtrlDetail->NameMapping[28] = _T("Fadc2");
						pCtrlDetail->NameMapping[29] = _T("Fadc3");
						pCtrlDetail->NameMapping[30] = _T("Tadc0");
						pCtrlDetail->NameMapping[31] = _T("Tadc1");
					}
				}

				pRegTable->RegInfo.at(0xD2).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(6, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("Tbe");
					}
				}

				pRegTable->RegInfo.at(0xD6).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_4, make_pair(6, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("losc_enb");
					}

					DlgCheck.Init(TAB_4, make_pair(6, 13));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("hosc_en");
					}

					DlgCheck.Init(TAB_4, make_pair(6, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("en_ps");
					}

					DlgCheck.Init(TAB_4, make_pair(6, 15));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("enb_bg");
					}
				}

				pRegTable->RegInfo.at(0xEF).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_5, make_pair(2, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("I2cWdog");
					}
				}
#endif
#endif
			}

			pRegTable->BitDetail.at(_T("EnDyna")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("EnPs")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("PsDrv")).DefaultVal.at(0) = 11;		// 12/16 IDrvMax
			pRegTable->BitDetail.at(_T("PsAdcBit")).DefaultVal.at(0) = 1;	// 10 bit
			pRegTable->BitDetail.at(_T("PsIntPuw")).DefaultVal.at(0) = 1;	// 1W
			pRegTable->BitDetail.at(_T("PsIntPuc")).DefaultVal.at(0) = 1;	// 1C

			//By Package
			pRegTable->BitDetail.at(_T("PsTcfLow")).DefaultVal.at(0) = 0x00;
			pRegTable->BitDetail.at(_T("PsTcfHigh")).DefaultVal.at(0) = 0x00;
			pRegTable->BitDetail.at(_T("IrTcfLow")).DefaultVal.at(0) = 0x00;
			pRegTable->BitDetail.at(_T("IrTcfHigh")).DefaultVal.at(0) = 0x00;
			pRegTable->BitDetail.at(_T("AlsTcfLow0")).DefaultVal.at(0) = 0x00;
			pRegTable->BitDetail.at(_T("AlsTcfHigh0")).DefaultVal.at(0) = 0x00;
			pRegTable->BitDetail.at(_T("AlsTcfLow1")).DefaultVal.at(0) = 0x00;
			pRegTable->BitDetail.at(_T("AlsTcfHigh1")).DefaultVal.at(0) = 0x00;

			//RD better setting
			pRegTable->BitDetail.at(_T("PsGain")).DefaultVal.at(0) = 0;
			pRegTable->BitDetail.at(_T("PsUnit")).DefaultVal.at(0) = 0x0C;
			pRegTable->BitDetail.at(_T("PsV2i")).DefaultVal.at(0) = 0x0F;
			pRegTable->BitDetail.at(_T("PsCap")).DefaultVal.at(0) = 0x08;
			pRegTable->BitDetail.at(_T("IrUnit")).DefaultVal.at(0) = 0x0C;
			pRegTable->BitDetail.at(_T("IrV2i")).DefaultVal.at(0) = 0x0F;
			pRegTable->BitDetail.at(_T("IrCap")).DefaultVal.at(0) = 0x08;
			pRegTable->BitDetail.at(_T("SlotTmp")).DefaultVal.at(0) = 0x00;
			pRegTable->BitDetail.at(_T("IrDark")).DefaultVal.at(0) = 0x00;
			pRegTable->BitDetail.at(_T("PsDark")).DefaultVal.at(0) = 0x00;
			pRegTable->BitDetail.at(_T("AlsDark")).DefaultVal.at(0) = 0x00;

			pReadTable = &pDieDetail->RegisterTable.ReadTable;
			pReadTable->insert(CReadTable(0xFE, 2));
#ifdef _DEBUG
			pReadTable->insert(CReadTable(0x00, 4, LogDec));
			pReadTable->insert(CReadTable(0x04, 4, LogDec));
#ifdef _RD
			pReadTable->insert(CReadTable(0x0C, 4, LogDec));
#endif
#else
			pReadTable->insert(CReadTable(0x00, 2, LogDec));
			pReadTable->insert(CReadTable(0x04, 4, LogDec));
#endif
			break;
		}
		}
		CSensorInfo::Init();
	}
};
