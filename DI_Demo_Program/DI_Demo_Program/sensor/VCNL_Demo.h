#pragma once
#include "Define.h"
#include "VCNL36821S.h"

class CVCNL_DEMO : public CSensorInfo {
public:
	CVCNL_DEMO()
	{
		ModelName = _T("VCNL_DEMO");
		pDieInfo = new CVCNL36821S;
#if defined(_DEBUG) || defined(_VCNL_DEMO)
		ModelVersion.insert(10000);
#endif
	}

	void Init(uint16_t version)
	{
		switch (version) {
		case 10000: {
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
			pDieDetail->DlgName[TAB_2] = _T("PS");
			pCtrlInfo[TAB_2] = &pDieDetail->CtrlInfo[TAB_2];

#ifdef _RD
			pDieDetail->DlgStyle[TAB_3] = PAGE_STYLE1;
			pDieDetail->DlgName[TAB_3] = _T("RD");
			pCtrlInfo[TAB_3] = &pDieDetail->CtrlInfo[TAB_3];

#endif
			pDieDetail->DlgStyle[MODEL_1] = MODELLESS1;
			pDieDetail->DlgName[MODEL_1] = _T("Data Progress Bar");
			pCtrlInfo[MODEL_1] = &pDieDetail->CtrlInfo[MODEL_1];

#ifdef _DEBUG
			pDieDetail->DlgStyle[MODEL_3] = MODELLESS_LIST;
			pDieDetail->DlgName[MODEL_3] = _T("Register Table");
#endif

			pRegTable = &pDieDetail->RegisterTable;
			{
				pRegTable->DeviceID = 0x1F;

				pRegTable->RegInfo.at(0xF0).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->I2CWriteDelayMs = 10;
						pCtrlDetail->CtrlName = make_pair(_T("PS Enable"), _T(""));
						pCtrlDetail->BitMapping[0] = _T("PsEn");
					}
#ifdef _DEBUG
					DlgCheck.Init(TAB_1, make_pair(0, 5));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->I2CWriteDelayMs = 10;
						pCtrlDetail->CtrlName = make_pair(_T("IR Enable"), _T(""));
						pCtrlDetail->BitMapping[0] = _T("IrEn");
					}

#endif // _DEBUG
#ifdef _RD
					DlgCheck.Init(TAB_1, make_pair(0, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->I2CWriteDelayMs = 10;
						pCtrlDetail->CtrlName = make_pair(_T("New PS Enable"), _T(""));
						pCtrlDetail->BitMapping[0] = _T("NewPsEn");
					}

#endif // _RD


				}

				pRegTable->RegInfo.at(0xF1).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(2, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsIntEn");
					}

#ifdef _DEBUG
					DlgCheck.Init(TAB_1, make_pair(2, 5));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrIntEn");
					}

					DlgCheck.Init(TAB_1, make_pair(2, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("DataIntEn");
					}

#endif // _DEBUG

					DlgCheck.Init(TAB_1, make_pair(2, 7));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ObjIntEn");
					}

					DlgCheck.Init(TAB_1, make_pair(2, 9));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PushPull");
					}
				}

				pRegTable->RegInfo.at(0xF2).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(4, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsHalt");
					}

#ifdef _DEBUG
					DlgCheck.Init(TAB_1, make_pair(4, 5));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrHalt");
					}

					DlgCheck.Init(TAB_1, make_pair(4, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("DataHalt");
					}

#endif // _DEBUG

					DlgCheck.Init(TAB_2, make_pair(6, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ReadClear");
						pCtrlDetail->NameMapping[0] = _T("Manually Clear");
						pCtrlDetail->NameMapping[1] = _T("Auto Clear");
					}
				}

				pRegTable->RegInfo.at(0xF4).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(6, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = BUTTON_GROUP;
						pCtrlDetail->CtrlName = make_pair(_T("Softwave Reset"), _T(""));
						pCtrlDetail->CtrlFunc = CTRLFUNC_SWRST;
						pCtrlDetail->BitMapping[0] = _T("SoftReset");
						pCtrlDetail->I2CWriteDelayMs = 30;
					}
				}

				pRegTable->RegInfo.at(0xFE).bEngMode = FALSE;
				{
					DlgCheck.Init(MAIN_DIALOG, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS"), _T("PS"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PsInt");
					}

#ifdef _DEBUG
					DlgCheck.Init(MAIN_DIALOG, make_pair(1, 0));
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

#endif // _DEBUG

					DlgCheck.Init(MAIN_DIALOG, make_pair(7, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("POR"), _T("POR"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PorInt");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 8));
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
#ifdef _DEBUG
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

					DlgCheck.Init(MAIN_DIALOG, make_pair(15, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("OBJ"), _T("OBJ"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("Obj");
					}
				}


				/* PS Data */
				pRegTable->BitDetail.at(_T("PsData")).BitRange = { make_pair(0, 255), make_pair(0, 0) };
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

					DlgCheck.Init(TAB_2, make_pair(0, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Data"), _T("PS Data"));
						pCtrlDetail->CtrlType = PROGRESS_GROUP;
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

				pRegTable->RegInfo.at(0x4F).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(6, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Wait Time"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("WaitTime");
						pCtrlDetail->NameMapping[0] = _T("No Wait Time");
						for (uint8_t i = 1; i < 255; i++)
						{
							csTemp.Format(_T("%d ms"), i * 10);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
						pCtrlDetail->NameMapping[255] = _T("2550 ms");
					}
				}

				pRegTable->RegInfo.at(0x60).bEngMode = FALSE;
				{
					//DlgCheck.Init(TAB_2, make_pair(0, 2));
					//ASSERT(DlgCheckSet.insert(DlgCheck).second);
					//pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					//{
					//	pCtrlDetail->CtrlName = make_pair(_T("PsData Bits"), _T(""));
					//	pCtrlDetail->CtrlType = COMBO_GROUP;
					//	pCtrlDetail->BitMapping[0] = _T("PsBits");
					//	pCtrlDetail->NameMapping[0] = _T("9-bit");
					//	pCtrlDetail->NameMapping[1] = _T("10-bit");
					//	pCtrlDetail->NameMapping[2] = _T("11-bit");
					//	pCtrlDetail->NameMapping[3] = _T("12-bit");

					//	pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_RANGE;
					//	pCtrlDetail->CtrlFunc |= CTRLFUNC_CALCULATE_POWER;
					//	pCtrlDetail->RegMapping[0] = 0x00;
					//	pCtrlDetail->RegMapping[1] = 0x6C;
					//	pCtrlDetail->RegMapping[2] = 0x6E;
					//	pCtrlDetail->RangeMapping[0] = make_pair(0, 511);
					//	pCtrlDetail->RangeMapping[1] = make_pair(0, 1023);
					//	pCtrlDetail->RangeMapping[2] = make_pair(0, 2047);
					//	pCtrlDetail->RangeMapping[3] = make_pair(0, 4095);

					//}

					DlgCheck.Init(TAB_2, make_pair(0, 0));
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
					DlgCheck.Init(TAB_2, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("PsPuw");
						pCtrlDetail->NameMapping[0] = _T("1W = 2 us(Default)");
						for (uint8_t i = 1; i < 0x80; i++)
						{
							csTemp.Format(_T("%d W = %d us"), i, i * 2);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x62).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("PsPuc");
						pCtrlDetail->NameMapping[0] = _T("1 pulse count (Default)");
#ifdef _DEBUG
						for (uint8_t i = 1; i < 64; i++)
#else
						for (uint8_t i = 1; i < 8; i++)
#endif
						{
							csTemp.Format(_T("%d pulse count"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x63).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("PsPrePuc");
						pCtrlDetail->NameMapping[0] = _T("No Pre-Heat Pulse Count");
						for (uint8_t i = 1; i < 4; i++)
						{
							csTemp.Format(_T("%d Pre-Heat Pulse Count"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x64).bEngMode = FALSE;
				{
#ifdef _RD
					DlgCheck.Init(TAB_3, make_pair(2, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsDrvDc");
						pCtrlDetail->NameMapping[0] = _T("Driving normally");
						pCtrlDetail->NameMapping[1] = _T("Force driving as DC");
					}

					DlgCheck.Init(TAB_2, make_pair(2, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CHANGE_NAMEMAPPING;
						pCtrlDetail->BitMapping[0] = _T("PsDrvMax");
						pCtrlDetail->NameMapping[0] = _T("16 mA");
						pCtrlDetail->NameMapping[1] = _T("120 mA");
					}

					DlgCheck.Init(TAB_2, make_pair(2, 8));
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
						for (uint8_t i = 1; i < 0x10; i++)
						{
							csTemp.Format(_T("%d mA"), i + 1);
							pCtrlDetail->NameMapping2[make_pair(i, 0)] = csTemp;
							csTemp.Format(_T("%d mA"), i * 8);
							pCtrlDetail->NameMapping2[make_pair(i, 1)] = csTemp;
						}
					}
#else
					DlgCheck.Init(TAB_2, make_pair(2, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Driver Control"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CALCULATE_POWER;
						pCtrlDetail->BitMapping[0] = _T("PsDrv");
						pCtrlDetail->NameMapping[0] = _T("0 mA(Off)");
						for (uint8_t i = 1; i < 0x10; i++)
						{
							csTemp.Format(_T("%d mA"), i + 1);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
#endif // _RD
				}

				pRegTable->RegInfo.at(0x65).bEngMode = FALSE;
				{
#ifdef _DEBUG
					DlgCheck.Init(TAB_2, make_pair(4, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsAmbGain");
					}
#endif
					DlgCheck.Init(TAB_2, make_pair(4, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsCtGain");
					}
				}

#ifdef _DEBUG
				pRegTable->RegInfo.at(0x66).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(6, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsAmbDac");
					}
				}

#endif // _DEBUG

				pRegTable->RegInfo.at(0x67).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsCtDac");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Auto CtDac"), _T("Auto CtDac"));
						pCtrlDetail->CtrlType = BUTTON_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_AUTO_DAC;
						pCtrlDetail->BitMapping[0] = _T("PsCal");
						pCtrlDetail->RegMapping[0] = 0x00;
					}
				}

				/* PS Calibration */
				pRegTable->RegInfo.at(0x69).bEngMode = FALSE;
				{

					DlgCheck.Init(TAB_2, make_pair(4, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Calibration"), _T("PS Calibration"));
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsCal");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 16));
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
					DlgCheck.Init(TAB_2, make_pair(4, 6));
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

					DlgCheck.Init(TAB_2, make_pair(4, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Int Algo"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsIntAlgo");
						pCtrlDetail->NameMapping[0] = _T("Zone Interrupt Mode");
						pCtrlDetail->NameMapping[1] = _T("Hysterics Interrupt Mode");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Wait Algo"), _T(""));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsWaitAlgo");
						pCtrlDetail->NameMapping[0] = _T("non-PS function FSM are kept");
						pCtrlDetail->NameMapping[1] = _T("non-PS function FSM may be ignored");
					}
				}

				/* PS Low Threshold */
				pRegTable->BitDetail.at(_T("PsThLow")).BitRange = { make_pair(0, 255), make_pair(0, 0) };
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
				pRegTable->BitDetail.at(_T("PsThHigh")).BitRange = { make_pair(0, 255), make_pair(0, 0) };
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
					DlgCheck.Init(TAB_2, make_pair(2, 2));
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

					DlgCheck.Init(TAB_2, make_pair(2, 0));
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
					DlgCheck.Init(TAB_2, make_pair(2, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IrPuw");
						pCtrlDetail->NameMapping[0] = _T("2 us(Default)");
						for (uint8_t i = 1; i < 0x80; i++)
						{
							csTemp.Format(_T("%d us"), i * 2);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}
#endif

#ifdef _RD
				pRegTable->RegInfo.at(0x80).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(0, 7));
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
					DlgCheck.Init(TAB_3, make_pair(2, 0));
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

				pRegTable->RegInfo.at(0x60).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsGain");
					}
				}

				pRegTable->RegInfo.at(0x65).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(0, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsCtGain");
					}
				}

				pRegTable->RegInfo.at(0x44).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsV2i");
					}

					DlgCheck.Init(TAB_3, make_pair(0, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsCap");
					}
				}
#endif
			}

			pRegTable->BitDetail.at(_T("PsEn")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("NewPsEn")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("PsDrv")).DefaultVal.at(0) = 11;	// 12 mA
			pRegTable->BitDetail.at(_T("PsBits")).DefaultVal.at(0) = 0;	// 9 bit
			pRegTable->BitDetail.at(_T("PsPuw")).DefaultVal.at(0) = 32;	// 32W
			pRegTable->BitDetail.at(_T("PsGain")).DefaultVal.at(0) = 0xF;	

			//By Package
			//pRegTable->BitDetail.at(_T("PsTcfLow")).DefaultVal.at(0) = 0xEE;
			//pRegTable->BitDetail.at(_T("PsTcfHigh")).DefaultVal.at(0) = 0x22;
			//pRegTable->BitDetail.at(_T("IrTcfLow")).DefaultVal.at(0) = 0x00;
			//pRegTable->BitDetail.at(_T("IrTcfHigh")).DefaultVal.at(0) = 0x00;

			pReadTable = &pDieDetail->RegisterTable.ReadTable;
			pReadTable->insert(CReadTable(0xFE, 2));
			pReadTable->insert(CReadTable(0x00, 4, LogDec));
			break;
		}
		}
		CSensorInfo::Init();
	}
};
