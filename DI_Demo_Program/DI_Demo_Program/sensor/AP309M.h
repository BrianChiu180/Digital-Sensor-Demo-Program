#pragma once
#include "Define.h"
#include "DA1990AP.h"

class CAP309M : public CSensorInfo {
public:
	CAP309M() {
		ModelName = _T("AP309M");
#if defined(_AP309M_10000) || defined(_DEBUG) || defined(_AP309M)
		ModelVersion.insert(10000);
#endif

		ModelDefaultAddress = 0x1C;
	}

	void Init(uint16_t version) {
		switch (version) {
		case 10000: {
			pDieInfo = new CDA1990AP();
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

			pDieDetail->DlgStyle[TAB_3] = PAGE_STYLE1;
			pDieDetail->DlgName[TAB_3] = _T("PS");
			pCtrlInfo[TAB_3] = &pDieDetail->CtrlInfo[TAB_3];

			pDieDetail->DlgStyle[MODEL_1] = MODELLESS1;
			pDieDetail->DlgName[MODEL_1] = _T("Data Progress Bar");
			pCtrlInfo[MODEL_1] = &pDieDetail->CtrlInfo[MODEL_1];

			//pDieDetail->DieFunc |= DF_LUX;

			//pDieDetail->DlgStyle[MODEL_2] = MODELLESS1;
			//pDieDetail->DlgName[MODEL_2] = _T("Lux(Ref.)");
			//pCtrlInfo[MODEL_2] = &pDieDetail->CtrlInfo[MODEL_2];

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

					DlgCheck.Init(TAB_1, make_pair(0, 5));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->CtrlName = make_pair(_T("PS Enable"), _T(""));
						pCtrlDetail->BitMapping[0] = _T("PsEn");
						pCtrlDetail->I2CWriteDelayMs = 10;
					}
#ifdef _DEBUG
					DlgCheck.Init(TAB_1, make_pair(0, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->CtrlName = make_pair(_T("IR Enable"), _T(""));
						pCtrlDetail->BitMapping[0] = _T("IrEn");
						pCtrlDetail->I2CWriteDelayMs = 10;
					}
#endif
#ifdef _RD
					DlgCheck.Init(TAB_1, make_pair(0, 7));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CHANGE_NAMEMAPPING;
						pCtrlDetail->CtrlName = make_pair(_T("New PS Enable"), _T(""));
						pCtrlDetail->BitMapping[0] = _T("NewPsEn");
						pCtrlDetail->I2CWriteDelayMs = 10;
					}
#endif
				}

				pRegTable->RegInfo.at(0xF1).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(2, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsIntEn");
					}

					DlgCheck.Init(TAB_1, make_pair(2, 5));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsIntEn");
					}
#ifdef _RD
					DlgCheck.Init(TAB_1, make_pair(2, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrIntEn");
					}

					DlgCheck.Init(TAB_1, make_pair(2, 7));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("DataIntEn");
					}
#endif
				}

				pRegTable->RegInfo.at(0xF2).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(4, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS Halt Enable"), _T(""));
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsHalt");
					}

					DlgCheck.Init(TAB_1, make_pair(4, 5));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Halt Enable"), _T(""));
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsHalt");
					}
#ifdef _RD
					DlgCheck.Init(TAB_1, make_pair(4, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("IR Halt Enable"), _T(""));
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrHalt");
					}

					DlgCheck.Init(TAB_1, make_pair(4, 7));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Data Halt Enable"), _T(""));
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("DataHalt");
					}
#endif
					DlgCheck.Init(TAB_1, make_pair(4, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ReadClear");
						pCtrlDetail->NameMapping[0] = _T("Manually Clear");
						pCtrlDetail->NameMapping[1] = _T("Auto Clear");
					}
				}

#ifdef _RD
				pRegTable->RegInfo.at(0xF3).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(0, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("FallPorEn");
					}

					DlgCheck.Init(TAB_1, make_pair(0, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("VbgPuw");
						pCtrlDetail->NameMapping[0] = _T("30 us");
						pCtrlDetail->NameMapping[1] = _T("15 us");
					}

					DlgCheck.Init(TAB_1, make_pair(0, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("Operation");
						pCtrlDetail->NameMapping[0] = _T("Standby Mode");
						pCtrlDetail->NameMapping[1] = _T("Normal Mode");
					}
				}
#endif

				pRegTable->RegInfo.at(0xF4).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(6, 14));
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
				{
					DlgCheck.Init(TAB_1, make_pair(6, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PushPull");
					}

#ifdef _RD
					DlgCheck.Init(TAB_1, make_pair(4, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IoFunc");
						pCtrlDetail->NameMapping[0] = _T("INT Pin is IntFlag Output");
						pCtrlDetail->NameMapping[1] = _T("Int Pin is Obj Output");
						pCtrlDetail->NameMapping[3] = _T("Int Pin is Sync Input");
					}
#endif // _RD
				}
#endif

#ifdef _RD
				pRegTable->RegInfo.at(0xFB).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(4, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("LoscData");
					}
				}
#endif

#ifdef _DEBUG
				pRegTable->RegInfo.at(0xFC).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(4, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Product Code"), _T(""));
						pCtrlDetail->CtrlType = TEXT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IDPod");
					}
				}

				pRegTable->RegInfo.at(0xFD).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(6, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Revision Code"), _T(""));
						pCtrlDetail->CtrlType = TEXT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IDRev");
					}
				}
#endif

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

					DlgCheck.Init(MAIN_DIALOG, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Data"), _T("Data"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("DataInt");
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

					DlgCheck.Init(TAB_1, make_pair(6, 8));
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
					DlgCheck.Init(MAIN_DIALOG, make_pair(9, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PsErr"), _T("PsErr"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PsErr");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(10, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("IrErr"), _T("IrErr"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("IrErr");
					}
#endif // _DEBUG

					DlgCheck.Init(MAIN_DIALOG, make_pair(11, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PsAmbErr"), _T("PsAmbErr"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PsAmbErr");
					}
#ifdef _DEBUG
					DlgCheck.Init(MAIN_DIALOG, make_pair(12, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PsDrvErr"), _T("PsDrvErr"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PsDrvErr");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(13, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("TmpErr"), _T("TmpErr"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("TmpErr");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(14, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("IrEnvErr"), _T("IrEnvErr"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("IrEnvErr");
					}
#endif // _DEBUG
					DlgCheck.Init(MAIN_DIALOG, make_pair(15, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Obj"), _T("Obj"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("Obj");
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
						pCtrlDetail->BitMapping[0] = _T("PsData");
					}

					DlgCheck.Init(TAB_3, make_pair(0, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Data"), _T("PS Data"));
						pCtrlDetail->CtrlType = PROGRESS_GROUP;
						pCtrlDetail->CtrlColor.first = PS_BAR;
						pCtrlDetail->BitMapping[0] = _T("PsData");
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
						pCtrlDetail->BitMapping[0] = _T("IrData");
					}
				}
#endif

				/* CH0 Data */
				pRegTable->RegInfo.at(0x04).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(2, 0));
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

					//DlgCheck.Init(MODEL_2, make_pair(0, 0));
					//ASSERT(DlgCheckSet.insert(DlgCheck).second);
					//pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					//{
					//	pCtrlDetail->CtrlName = make_pair(_T("LUX"), _T(""));
					//	pCtrlDetail->CtrlType = TEXT_GROUP;
					//	pCtrlDetail->CtrlFunc = CTRLFUNC_LUX;
					//	pCtrlDetail->BitMapping[0] = _T("AlsData0");
					//}
				}

				/* CH1 Data */
				pRegTable->RegInfo.at(0x06).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(3, 0));
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
					DlgCheck.Init(MODEL_1, make_pair(4, 0));
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
					DlgCheck.Init(MODEL_1, make_pair(5, 0));
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

				pRegTable->RegInfo.at(0x4F).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(6, 4));
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
						pCtrlDetail->NameMapping[2] = _T("x4, Default");
						pCtrlDetail->NameMapping[3] = _T("x8");
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

					}
#ifdef _RD
					DlgCheck.Init(TAB_2, make_pair(6, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Als Random"), _T(""));
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AlsRand");
					}
#endif
#endif // _DEBUG
				}

				pRegTable->RegInfo.at(0x52).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS Covnersion Time"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("AlsPuc");
						pCtrlDetail->NameMapping[0] = _T("100 ms, Default");
#ifdef _DEBUG
						for (uint8_t i = 1; i < 32; i++)
#else
						for (uint8_t i = 1; i < 16; i++)
#endif // _DEBUG
						{
							csTemp.Format(_T("%d ms"), i * 100);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

#ifdef _DEBUG
				pRegTable->RegInfo.at(0x55).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("AlsPuw0");
						pCtrlDetail->NameMapping[0] = _T("Disable AlsData0");
						for (uint8_t i = 1; i < 128; i++)
						{
							csTemp.Format(_T("%d ms"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
						pCtrlDetail->NameMapping[50] = _T("50 ms, Default");
					}
				}

				pRegTable->RegInfo.at(0x56).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("AlsPuw1");
						pCtrlDetail->NameMapping[0] = _T("Disable AlsData1");
						for (uint8_t i = 1; i < 128; i++)
						{
							csTemp.Format(_T("%d ms"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
						pCtrlDetail->NameMapping[10] = _T("10 ms, Default");
					}
				}
#endif // _DEBUG

				pRegTable->RegInfo.at(0x5B).bEngMode = FALSE;
				{
#ifdef _DEBUG
					DlgCheck.Init(TAB_2, make_pair(2, 10));
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
#endif
					DlgCheck.Init(TAB_2, make_pair(0, 10));
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

				/* PS Register*/
				pRegTable->RegInfo.at(0x60).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("PsGain");
						pCtrlDetail->BitMapping[1] = _T("NewPsEn");
						pCtrlDetail->NameMapping2[make_pair(0, 0)] = _T("x1");
						pCtrlDetail->NameMapping2[make_pair(1, 0)] = _T("x2");
						pCtrlDetail->NameMapping2[make_pair(0, 1)] = _T("x1");
						pCtrlDetail->NameMapping2[make_pair(1, 1)] = _T("x4");
					}

					DlgCheck.Init(TAB_3, make_pair(0, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PsData Bits"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsBits");
						pCtrlDetail->NameMapping[0] = _T("9-bit");
						pCtrlDetail->NameMapping[1] = _T("10-bit");
						pCtrlDetail->NameMapping[2] = _T("11-bit");
						pCtrlDetail->NameMapping[3] = _T("12-bit");

						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_RANGE;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->RegMapping[0] = 0x00;
						pCtrlDetail->RegMapping[1] = 0x6C;
						pCtrlDetail->RegMapping[2] = 0x6E;
						pCtrlDetail->RangeMapping[0] = make_pair(0, 511);
						pCtrlDetail->RangeMapping[1] = make_pair(0, 1023);
						pCtrlDetail->RangeMapping[2] = make_pair(0, 2047);
						pCtrlDetail->RangeMapping[3] = make_pair(0, 4095);

					}

					DlgCheck.Init(TAB_3, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("PsMean");
						pCtrlDetail->NameMapping[0] = _T("30 ms");
						pCtrlDetail->NameMapping[1] = _T("40 ms");
						pCtrlDetail->NameMapping[2] = _T("50 ms");
						pCtrlDetail->NameMapping[3] = _T("100 ms");
					}
				}
				pRegTable->RegInfo.at(0x61).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(0, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("PsPuw");
						pCtrlDetail->NameMapping[0] = _T("2 us, Default");
#ifdef _DEBUG
						for (uint8_t i = 1; i < 0x80; i++)
#else
						for (uint8_t i = 1; i < 0x40; i++)
#endif
						{
							csTemp.Format(_T("%d us"), i * 2);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x62).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(0, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("PsPuc");
						pCtrlDetail->NameMapping[0] = _T("1C, Default");
#ifdef _DEBUG
						for (uint8_t i = 1; i < 64; i++)
#else
						for (uint8_t i = 1; i < 8; i++)
#endif
						{
							csTemp.Format(_T("%dC"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x63).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(2, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("PsPrePuc");
						pCtrlDetail->NameMapping[0] = _T("0C, Default");
#ifdef _DEBUG
						for (uint8_t i = 1; i < 16; i++)
#else
						for (uint8_t i = 1; i < 4; i++)
#endif
						{
							csTemp.Format(_T("%dC"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x64).bEngMode = FALSE;
				{
#ifdef _RD
					DlgCheck.Init(TAB_3, make_pair(6, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsDrvDc");
						pCtrlDetail->NameMapping[0] = _T("Normally");
						pCtrlDetail->NameMapping[2] = _T("Driving DC");
					}
#endif // _RD

					DlgCheck.Init(TAB_3, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CHANGE_NAMEMAPPING;
						pCtrlDetail->BitMapping[0] = _T("PsDrvMax");
						pCtrlDetail->NameMapping[0] = _T("24 mA");
						pCtrlDetail->NameMapping[1] = _T("160 mA, LED");
						pCtrlDetail->NameMapping[2] = _T("30 mA");
						pCtrlDetail->NameMapping[3] = _T("200 mA, LED");
					}

					DlgCheck.Init(TAB_3, make_pair(4, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Driver Control"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("PsDrv");
						pCtrlDetail->BitMapping[1] = _T("PsDrvMax");
						pCtrlDetail->NameMapping2[make_pair(0, 0)] = _T("Off");
						pCtrlDetail->NameMapping2[make_pair(0, 1)] = _T("Off");
						pCtrlDetail->NameMapping2[make_pair(0, 2)] = _T("Off");
						pCtrlDetail->NameMapping2[make_pair(0, 3)] = _T("Off");
						for (uint8_t i = 1; i < 0x10; i++)
						{
							csTemp.Format(_T("%.1f mA"), (i + 1) * 1.5);
							pCtrlDetail->NameMapping2[make_pair(i, 0)] = csTemp;
							csTemp.Format(_T("%d mA"), (i + 1) * 10);
							pCtrlDetail->NameMapping2[make_pair(i, 1)] = csTemp;
							csTemp.Format(_T("%.3f mA"), (i + 1) * 1.875);
							pCtrlDetail->NameMapping2[make_pair(i, 2)] = csTemp;
							csTemp.Format(_T("%.1f mA"), (i + 1) * 12.5);
							pCtrlDetail->NameMapping2[make_pair(i, 3)] = csTemp;

						}
					}
				}

				pRegTable->RegInfo.at(0x65).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(4, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsCoasGain");
					}
					DlgCheck.Init(TAB_3, make_pair(4, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsFineGain");
					}
				}

#ifdef _DEBUG
				pRegTable->RegInfo.at(0x66).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(6, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsCoasAmb");
					}
				}

#endif // _DEBUG

				pRegTable->RegInfo.at(0x67).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(6, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsCoasCt");
					}
				}

				pRegTable->RegInfo.at(0x68).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(6, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsFineCt");
					}
				}

				/* PS Calibration */
				pRegTable->RegInfo.at(0x69).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_3, make_pair(4, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Calibration"), _T("PS Calibration"));
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsCal");
					}

					DlgCheck.Init(TAB_3, make_pair(6, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Auto Calibration"), _T("Auto Calibration"));
						pCtrlDetail->CtrlType = BUTTON_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CALIBRATION;
						pCtrlDetail->BitMapping[0] = _T("PsCal");
						pCtrlDetail->RegMapping[0] = 0x00;
					}
				}

				pRegTable->RegInfo.at(0x6B).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(0, 10));
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

					DlgCheck.Init(TAB_3, make_pair(4, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Int Algo"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsIntAlgo");
						pCtrlDetail->NameMapping[0] = _T("Zone Interrupt Mode");
						pCtrlDetail->NameMapping[1] = _T("Hysterics Interrupt Mode");
					}

					DlgCheck.Init(TAB_3, make_pair(4, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Wait Algo"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsWaitAlgo");
						pCtrlDetail->NameMapping[0] = _T("non-PS function FSM are kept");
						pCtrlDetail->NameMapping[1] = _T("non-PS function FSM may be ignored");
					}

					DlgCheck.Init(TAB_3, make_pair(4, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Obj Polar"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsObjPolar");
						pCtrlDetail->NameMapping[0] = _T("Obj = Obj");
						pCtrlDetail->NameMapping[1] = _T("Obj = ~Obj");
					}
				}

				/* PS Low Threshold */
				pRegTable->RegInfo.at(0x6C).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_3, make_pair(0, 16));
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

					DlgCheck.Init(TAB_3, make_pair(0, 12));
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
					DlgCheck.Init(TAB_3, make_pair(2, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("IrGain");
						pCtrlDetail->NameMapping[0] = _T("x1");
						pCtrlDetail->NameMapping[1] = _T("x2");
					}

					DlgCheck.Init(TAB_3, make_pair(2, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("IrData Bits"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrBits");
						pCtrlDetail->NameMapping[0] = _T("9-bit");
						pCtrlDetail->NameMapping[1] = _T("10-bit");
						pCtrlDetail->NameMapping[2] = _T("11-bit");
						pCtrlDetail->NameMapping[3] = _T("12-bit");

						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_RANGE;
						pCtrlDetail->RegMapping[0] = 0x02;
						pCtrlDetail->RangeMapping[0] = make_pair(0, 511);
						pCtrlDetail->RangeMapping[1] = make_pair(0, 1023);
						pCtrlDetail->RangeMapping[2] = make_pair(0, 2047);
						pCtrlDetail->RangeMapping[3] = make_pair(0, 4095);
					}

					DlgCheck.Init(TAB_3, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("IrMean");
						pCtrlDetail->NameMapping[0] = _T("30 ms");
						pCtrlDetail->NameMapping[1] = _T("40 ms");
						pCtrlDetail->NameMapping[2] = _T("50 ms");
						pCtrlDetail->NameMapping[3] = _T("100 ms");
					}
				}

				pRegTable->RegInfo.at(0x71).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(2, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrPuw");
						pCtrlDetail->NameMapping[0] = _T("2 us, Default");
						for (uint8_t i = 1; i < 0x80; i++)
						{
							csTemp.Format(_T("%d us"), i * 2);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}
#endif

#ifdef _RD
				pRegTable->RegInfo.at(0x7B).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(0, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->I2CWriteDelayMs = 10;
						pCtrlDetail->CtrlName = make_pair(_T("Fast PS Enable"), _T(""));
						pCtrlDetail->BitMapping[0] = _T("FastEn");
					}
				}

				pRegTable->RegInfo.at(0xD0).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(0, 2));
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
#endif
			}

			//pLuxCalculate = &pDieDetail->LuxCalculate;
			//{
			//	pLuxCalculate->LuxFunc = TwoCH;
			//	pLuxCalculate->DataRegMapping[0] = 0x00;
			//	pLuxCalculate->DataRegMapping[1] = 0x02;
			//	pLuxCalculate->RatioBitMapping[0] = _T("AlsGain0");
			//	{
			//		pLuxCalculate->CountRatioMapping[0][0] = 4.0;
			//		pLuxCalculate->CountRatioMapping[0][1] = 1.0;
			//		pLuxCalculate->CountRatioMapping[0][2] = 4.0 / 20.0;
			//		pLuxCalculate->CountRatioMapping[0][3] = 4.0 / 125.0;
			//	}

			//	pLuxCalculate->RatioBitMapping[1] = _T("AlsGain1");
			//	{
			//		pLuxCalculate->CountRatioMapping[1][0] = 2.0;
			//		pLuxCalculate->CountRatioMapping[1][1] = 1.0;
			//	}

			//	pLuxCalculate->RatioBitMapping[2] = _T("AlsPuc");
			//	for (int i = 0; i < 256; i++)
			//		pLuxCalculate->CountRatioMapping[2][i] = 64.0 / ((double)i + 1);

			//	//pLuxCalculate->Count2LuxMapping[0.5] = make_pair(0.2113, 0.0);
			//	pLuxCalculate->Count2LuxMapping[0] = make_pair(2.54, 0.0);
			//}

			pRegTable->BitDetail.at(_T("AlsPuc")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("AlsEn")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("PsEn")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("PsBits")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("PsDrv")).DefaultVal.at(0) = 0x07;
			pRegTable->BitDetail.at(_T("PsPuc")).DefaultVal.at(0) = 0x02;
			pRegTable->BitDetail.at(_T("PsPuw")).DefaultVal.at(0) = 0x10;
			pRegTable->BitDetail.at(_T("PxyDark")).DefaultVal.at(0) = 0x0;

			pReadTable = &pDieDetail->RegisterTable.ReadTable;
			pReadTable->insert(CReadTable(0xFE, 2));
			pReadTable->insert(CReadTable(0x00, 2, LogDec));
			pReadTable->insert(CReadTable(0x02, 2, LogDec));
			pReadTable->insert(CReadTable(0x04, 2, LogDec));
			pReadTable->insert(CReadTable(0x06, 2, LogDec));
#ifdef _RD
			pReadTable->insert(CReadTable(0x0C, 4, LogDec));
#endif
			break;
		}
		}

		CSensorInfo::Init();
	}
};