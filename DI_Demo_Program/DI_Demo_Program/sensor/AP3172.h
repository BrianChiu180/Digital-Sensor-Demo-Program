#pragma once
#include "Define.h"
#include "DA3107.h"

class CAP3172 : public CSensorInfo {
public:
	CAP3172() {
		ModelName = _T("AP3172");
		pDieInfo = new CDA3107;
#if defined(_AP3172_6000) || defined(_DEBUG)
		ModelVersion.insert(6000);
#endif
#if defined(_AP3172_7100) || defined(_DEBUG)
		ModelVersion.insert(7100);
#endif
#if defined(_AP3172_7200) || defined(_DEBUG)	//µL0.72ªºDatasheet, for die v1.2
		ModelVersion.insert(7200);
#endif
#if defined(_AP3172_8000) || defined(_DEBUG) || defined(_AP3172)
		ModelVersion.insert(8000);
#endif
	}

	void Init(uint16_t version) {
		switch (version) {
		case 6000:
		case 7100:
		{
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
			pDieDetail->DlgName[TAB_2] = _T("ALS + PS");
			pCtrlInfo[TAB_2] = &pDieDetail->CtrlInfo[TAB_2];

			pDieDetail->DlgStyle[MODEL_1] = MODELLESS1;
			pDieDetail->DlgName[MODEL_1] = _T("Data Progress Bar");
			pCtrlInfo[MODEL_1] = &pDieDetail->CtrlInfo[MODEL_1];

			//pDieDetail->DlgStyle[MODEL_2] = MODELLESS1;
			//pDieDetail->DlgName[MODEL_2] = _T("Lux");
			//pCtrlInfo[MODEL_2] = &pDieDetail->CtrlInfo[MODEL_2];

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

					DlgCheck.Init(TAB_1, make_pair(0, 5));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PEN");
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

					DlgCheck.Init(TAB_2, make_pair(4, 10));
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
						pCtrlDetail->CtrlName = make_pair(_T("PS"), _T("PS"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PINT");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(3, 0));
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
						pCtrlDetail->BitMapping[0] = _T("PIEN");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("APEND");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 3));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PPEND");
					}
				}

				pRegTable->RegInfo.at(0x06).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(6, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("WTIME");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 8));
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
					DlgCheck.Init(TAB_2, make_pair(0, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AGAIN");
						switch (version)
						{
						case 6000:
							pCtrlDetail->NameMapping[0] = _T("x1");
							pCtrlDetail->NameMapping[1] = _T("x2");
							pCtrlDetail->NameMapping[2] = _T("x4");
							pCtrlDetail->NameMapping[3] = _T("x8");
							pCtrlDetail->NameMapping[4] = _T("x16");
							pCtrlDetail->NameMapping[5] = _T("x32");
							pCtrlDetail->NameMapping[6] = _T("x64");
							break;
						case 7100:
							pCtrlDetail->NameMapping[0] = _T("1X");
							pCtrlDetail->NameMapping[1] = _T("2X");
							pCtrlDetail->NameMapping[2] = _T("4X");
							pCtrlDetail->NameMapping[3] = _T("8X");
							pCtrlDetail->NameMapping[4] = _T("16X");
							pCtrlDetail->NameMapping[5] = _T("32X");
							pCtrlDetail->NameMapping[6] = _T("64X");
							break;
						}
					}

					DlgCheck.Init(TAB_2, make_pair(2, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_SELDATA;
						pCtrlDetail->BitMapping[0] = _T("ASRC");
						pCtrlDetail->NameMapping[0] = _T("ACH0 as ADATA");
						pCtrlDetail->NameMapping[1] = _T("ACH1 as ADATA");
						pCtrlDetail->RegMapping[0] = 0x2C;
						pCtrlDetail->RegMapping[1] = 0x2E;
					}
				}

				pRegTable->RegInfo.at(0x08).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 8));
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
						pCtrlDetail->RegMapping[2] = 0x36;
						pCtrlDetail->RegMapping[3] = 0x38;
					}
				}

				pRegTable->RegInfo.at(0x09).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("APERS");
						pCtrlDetail->NameMapping[0] = _T("Every cycles");
						for (int i = 1; i < 64; i++)
						{
							csTemp.Format(_T("After %d"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x0C).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PGAIN");
						pCtrlDetail->NameMapping[0] = _T("1X");
						pCtrlDetail->NameMapping[1] = _T("4X");
						pCtrlDetail->NameMapping[2] = _T("16X");

					}

					DlgCheck.Init(TAB_2, make_pair(2, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PMODE");
						pCtrlDetail->NameMapping[0] = _T("Zone Interrupt");
						pCtrlDetail->NameMapping[1] = _T("Hysteresis Interrupt");

					}

					DlgCheck.Init(TAB_2, make_pair(6, 5));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Acceleration"), _T(""));
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PACC");

					}
				}

				pRegTable->RegInfo.at(0x0D).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_RANGE;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PTIME");
						for (int i = 0; i < 16; i++)
							pCtrlDetail->RangeMapping[i] = make_pair(0, 255 + i * 256);
						pCtrlDetail->RegMapping[0] = 0x28;
						pCtrlDetail->RegMapping[1] = 0x3A;
						pCtrlDetail->RegMapping[2] = 0x3C;
					}
				}

				pRegTable->RegInfo.at(0x0E).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PPERS");
						pCtrlDetail->NameMapping[0] = _T("Every cycles");
						for (int i = 1; i < 64; i++)
						{
							csTemp.Format(_T("After %d"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x0F).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PLPUC");
						for (int i = 0; i < 64; i++)
						{
							csTemp.Format(_T("%d LED Pulse"), i + 1);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x10).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PLPUW");
						for (int i = 0; i < 256; i++)
						{
							csTemp.Format(_T("%3d us"), (i + 1) * 2);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x11).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PLDR");
						pCtrlDetail->NameMapping[0] = _T("25% Iledmax");
						pCtrlDetail->NameMapping[1] = _T("50% Iledmax");
						pCtrlDetail->NameMapping[2] = _T("75% Iledmax");
						pCtrlDetail->NameMapping[3] = _T("100% Iledmax");
					}

					DlgCheck.Init(TAB_2, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PLASER");
						pCtrlDetail->NameMapping[0] = _T("160 mA");
						pCtrlDetail->NameMapping[1] = _T("10 mA");
					}
				}

				pRegTable->RegInfo.at(0x12).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PCTDAC");
						for (int i = 0; i < 32; i++)
						{
							csTemp.Format(_T("%2d step"), i);
							pCtrlDetail->NameMapping[i] = csTemp;

						}
					}

					DlgCheck.Init(TAB_2, make_pair(0, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PCTGAIN");
						pCtrlDetail->NameMapping[0] = _T("x1");
						pCtrlDetail->NameMapping[1] = _T("x2");
						pCtrlDetail->NameMapping[2] = _T("x3");
					}
				}

				pRegTable->RegInfo.at(0x13).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PMEAN");
						pCtrlDetail->NameMapping[0] = _T("1 Time");
						pCtrlDetail->NameMapping[1] = _T("2 Times");
						pCtrlDetail->NameMapping[2] = _T("4 Times");
						pCtrlDetail->NameMapping[3] = _T("8 Times");
						pCtrlDetail->NameMapping[4] = _T("16 Times");
						pCtrlDetail->NameMapping[5] = _T("32 Times");
						pCtrlDetail->NameMapping[6] = _T("64 Times");
					}
				}

				pRegTable->RegInfo.at(0x1E).bEngMode = FALSE;
				{
					DlgCheck.Init(MAIN_DIALOG, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("AERR"), _T("AERR"));
						pCtrlDetail->BitMapping[0] = _T("AERR");
						pCtrlDetail->CtrlType = LED;
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(7, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("OBJ"), _T("OBJ"));
						pCtrlDetail->BitMapping[0] = _T("OBJ");
						pCtrlDetail->CtrlType = LED;
					}
				}

				/* PS Data */
				pRegTable->RegInfo.at(0x28).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PCH"), _T("PCH"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = PS_BAR;
						pCtrlDetail->BitMapping[0] = _T("PCH");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Channel"), _T("PS Channel"));
						pCtrlDetail->CtrlType = PROGRESS_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PCH");
					}
				}

				/* ACH0 Data */
				pRegTable->RegInfo.at(0x2C).bEngMode = FALSE;
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

					DlgCheck.Init(TAB_2, make_pair(0, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS Channel 0"), _T("ALS Channel 0"));
						pCtrlDetail->CtrlType = PROGRESS_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_SELDATA;
						pCtrlDetail->BitMapping[0] = _T("ACH0");
						pCtrlDetail->RegMapping[0] = 0x2C;
						pCtrlDetail->RegMapping[1] = 0x2E;
					}
				}

				/* ACH1 Data */
				pRegTable->RegInfo.at(0x2E).bEngMode = FALSE;
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

				/* ALS Low Threshold */
				pRegTable->RegInfo.at(0x36).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
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
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AHTH");
					}
				}

				/* PS Low Threshold */
				pRegTable->RegInfo.at(0x3A).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PLTH");
					}
				}

				/* PS High Threshold */
				pRegTable->RegInfo.at(0x3C).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PHTH");
					}
				}

				/* PS Calibration */
				pRegTable->RegInfo.at(0x3E).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PCALB");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = BUTTON_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CALIBRATION;
						pCtrlDetail->BitMapping[0] = _T("PCALB");
						pCtrlDetail->RegMapping[0] = 0x28;
					}
				}
			}

#if defined(_DEBUG)
			pDieDetail->DlgStyle[TAB_3] = PAGE_STYLE1;
			pDieDetail->DlgName[TAB_3] = _T("IR");
			pCtrlInfo[TAB_3] = &pDieDetail->CtrlInfo[TAB_3];

			DlgCheck.Init(TAB_1, make_pair(0, 6));
			ASSERT(DlgCheckSet.insert(DlgCheck).second);
			pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
			{
				pCtrlDetail->CtrlType = CHECK_GROUP;
				pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
				pCtrlDetail->BitMapping[0] = _T("IREN");
			}

			DlgCheck.Init(MAIN_DIALOG, make_pair(2, 0));
			ASSERT(DlgCheckSet.insert(DlgCheck).second);
			pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
			{
				pCtrlDetail->CtrlName = make_pair(_T("IR"), _T("IR"));
				pCtrlDetail->CtrlType = LED;
				pCtrlDetail->BitMapping[0] = _T("IRINT");
			}

			DlgCheck.Init(TAB_3, make_pair(6, 0));
			ASSERT(DlgCheckSet.insert(DlgCheck).second);
			pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
			{
				pCtrlDetail->CtrlType = CHECK_GROUP;
				pCtrlDetail->BitMapping[0] = _T("IRIEN");
			}

			DlgCheck.Init(TAB_3, make_pair(6, 1));
			ASSERT(DlgCheckSet.insert(DlgCheck).second);
			pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
			{
				pCtrlDetail->CtrlType = CHECK_GROUP;
				pCtrlDetail->BitMapping[0] = _T("IRPEND");
			}

			pRegTable->RegInfo.at(0x16).bEngMode = FALSE;
			{
				DlgCheck.Init(TAB_3, make_pair(0, 0));
				ASSERT(DlgCheckSet.insert(DlgCheck).second);
				pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
				{
					pCtrlDetail->CtrlType = COMBO_GROUP;
					pCtrlDetail->BitMapping[0] = _T("IRGAIN");
					pCtrlDetail->NameMapping[0] = _T("1X");
					pCtrlDetail->NameMapping[1] = _T("4X");
					pCtrlDetail->NameMapping[2] = _T("16X");

				}
			}

			pRegTable->RegInfo.at(0x17).bEngMode = FALSE;
			{
				DlgCheck.Init(TAB_3, make_pair(2, 0));
				ASSERT(DlgCheckSet.insert(DlgCheck).second);
				pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
				{
					pCtrlDetail->CtrlType = EDIT_GROUP;
					pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_RANGE;
					pCtrlDetail->CtrlFunc |= CTRLFUNC_CHANGE_CONVERSION_TIME;
					pCtrlDetail->BitMapping[0] = _T("IRTIME");
					for (int i = 0; i < 0x3f; i++)
						pCtrlDetail->RangeMapping[i] = make_pair(0, 255 + i * 256);
					pCtrlDetail->RegMapping[0] = 0x2A;
				}
			}

			pRegTable->RegInfo.at(0x18).bEngMode = FALSE;
			{
				DlgCheck.Init(TAB_3, make_pair(4, 0));
				ASSERT(DlgCheckSet.insert(DlgCheck).second);
				pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
				{
					pCtrlDetail->CtrlType = COMBO_GROUP;
					pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
					pCtrlDetail->BitMapping[0] = _T("IRPUW");
					for (int i = 0; i < 256; i++)
					{
						csTemp.Format(_T("%3d us"), (i + 1) * 2);
						pCtrlDetail->NameMapping[i] = csTemp;
					}
				}
			}

			pRegTable->RegInfo.at(0x19).bEngMode = FALSE;
			{
				DlgCheck.Init(TAB_3, make_pair(0, 2));
				ASSERT(DlgCheckSet.insert(DlgCheck).second);
				pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
				{
					pCtrlDetail->CtrlType = COMBO_GROUP;
					pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
					pCtrlDetail->BitMapping[0] = _T("IRMEAN");
					pCtrlDetail->NameMapping[0] = _T("1 Time");
					pCtrlDetail->NameMapping[1] = _T("2 Times");
					pCtrlDetail->NameMapping[2] = _T("4 Times");
					pCtrlDetail->NameMapping[3] = _T("8 Times");
					pCtrlDetail->NameMapping[4] = _T("16 Times");
					pCtrlDetail->NameMapping[5] = _T("32 Times");
					pCtrlDetail->NameMapping[6] = _T("64 Times");
				}
			}

			DlgCheck.Init(MAIN_DIALOG, make_pair(5, 0));
			ASSERT(DlgCheckSet.insert(DlgCheck).second);
			pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
			{
				pCtrlDetail->CtrlName = make_pair(_T("PERR"), _T("PERR"));
				pCtrlDetail->BitMapping[0] = _T("PERR");
				pCtrlDetail->CtrlType = LED;
			}

			DlgCheck.Init(MAIN_DIALOG, make_pair(6, 0));
			ASSERT(DlgCheckSet.insert(DlgCheck).second);
			pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
			{
				pCtrlDetail->CtrlName = make_pair(_T("IRERR"), _T("IRERR"));
				pCtrlDetail->BitMapping[0] = _T("IRERR");
				pCtrlDetail->CtrlType = LED;
			}

			/* IR Data */
			pRegTable->RegInfo.at(0x2A).bEngMode = FALSE;
			{
				DlgCheck.Init(MODEL_1, make_pair(3, 0));
				ASSERT(DlgCheckSet.insert(DlgCheck).second);
				pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
				{
					pCtrlDetail->CtrlName = make_pair(_T("IRCH"), _T("IRCH"));
					pCtrlDetail->CtrlType = PROGRESSBAR;
					pCtrlDetail->BitMapping[0] = _T("IRCH");
				}
			}
#endif

			pRegTable->BitDetail.at(_T("AEN")).DefaultVal.at(0)	= 0x01;
			pRegTable->BitDetail.at(_T("PEN")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("ATIME")).DefaultVal.at(0) = 63;
			pRegTable->BitDetail.at(_T("PTIME")).DefaultVal.at(0) = 0x0F;
			pRegTable->BitDetail.at(_T("PLPUW")).DefaultVal.at(0) = 0x3F;
			pRegTable->BitDetail.at(_T("PLASER")).DefaultVal.at(0) = 0x00;
			pRegTable->BitDetail.at(_T("PLDR")).DefaultVal.at(0) = 0x03;

			pReadTable = &pRegTable->ReadTable;
			pReadTable->insert(CReadTable(0x01, 1));
			pReadTable->insert(CReadTable(0x1E, 1));
#if defined(_DEBUG)
			pReadTable->insert(CReadTable(0x28, 8, LogDec));
#else
			pReadTable->insert(CReadTable(0x28, 2, LogDec));
			pReadTable->insert(CReadTable(0x2C, 4, LogDec));
#endif

			break;
		}
		case 7200: {
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
			pDieDetail->DlgName[TAB_2] = _T("ALS + PS");
			pCtrlInfo[TAB_2] = &pDieDetail->CtrlInfo[TAB_2];

			pDieDetail->DlgStyle[MODEL_1] = MODELLESS1;
			pDieDetail->DlgName[MODEL_1] = _T("Data Progress Bar");
			pCtrlInfo[MODEL_1] = &pDieDetail->CtrlInfo[MODEL_1];

			//pDieDetail->DlgStyle[MODEL_2] = MODELLESS1;
			//pDieDetail->DlgName[MODEL_2] = _T("Lux");
			//pCtrlInfo[MODEL_2] = &pDieDetail->CtrlInfo[MODEL_2];

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

					DlgCheck.Init(TAB_1, make_pair(0, 5));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PEN");
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

					DlgCheck.Init(TAB_2, make_pair(4, 10));
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
						pCtrlDetail->CtrlName = make_pair(_T("PS"), _T("PS"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PINT");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(3, 0));
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
						pCtrlDetail->BitMapping[0] = _T("PIEN");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("APEND");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 3));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PPEND");
					}
				}

				pRegTable->RegInfo.at(0x06).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(6, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("WTIME");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 8));
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
					DlgCheck.Init(TAB_2, make_pair(0, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("APERS");
						pCtrlDetail->NameMapping[0] = _T("Every cycles");
						for (int i = 1; i < 64; i++)
						{
							csTemp.Format(_T("After %d"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x08).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 8));
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

					DlgCheck.Init(TAB_2, make_pair(2, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_SELDATA;
						pCtrlDetail->BitMapping[0] = _T("ASRC");
						pCtrlDetail->NameMapping[0] = _T("ACH0 as ADATA");
						pCtrlDetail->NameMapping[1] = _T("ACH1 as ADATA");
						pCtrlDetail->RegMapping[0] = 0x2C;
						pCtrlDetail->RegMapping[1] = 0x2E;
					}
				}

				pRegTable->RegInfo.at(0x09).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 8));
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
						pCtrlDetail->RegMapping[2] = 0x36;
						pCtrlDetail->RegMapping[3] = 0x38;
					}
				}

				pRegTable->RegInfo.at(0x0C).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PPERS");
						pCtrlDetail->NameMapping[0] = _T("Every cycles");
						for (int i = 1; i < 64; i++)
						{
							csTemp.Format(_T("After %d"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x0D).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PMEAN");
						pCtrlDetail->NameMapping[0] = _T("1 Time");
						pCtrlDetail->NameMapping[1] = _T("2 Times");
						pCtrlDetail->NameMapping[2] = _T("4 Times");
						pCtrlDetail->NameMapping[3] = _T("8 Times");
						pCtrlDetail->NameMapping[4] = _T("16 Times");
						pCtrlDetail->NameMapping[5] = _T("32 Times");
						pCtrlDetail->NameMapping[6] = _T("64 Times");
					}
				}

				pRegTable->RegInfo.at(0x0E).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PGAIN");
						pCtrlDetail->NameMapping[0] = _T("1X");
						pCtrlDetail->NameMapping[1] = _T("4X");
					}

					DlgCheck.Init(TAB_2, make_pair(2, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PMODE");
						pCtrlDetail->NameMapping[0] = _T("Zone Interrupt");
						pCtrlDetail->NameMapping[1] = _T("Hysteresis Interrupt");

					}

					DlgCheck.Init(TAB_2, make_pair(6, 5));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Acceleration"), _T(""));
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PACC");

					}
				}

				pRegTable->RegInfo.at(0x0F).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_RANGE;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PTIME");
						for (int i = 0; i < 16; i++)
							pCtrlDetail->RangeMapping[i] = make_pair(0, 255 + i * 256);
						pCtrlDetail->RegMapping[0] = 0x28;
						pCtrlDetail->RegMapping[1] = 0x3A;
						pCtrlDetail->RegMapping[2] = 0x3C;
					}
				}

				pRegTable->RegInfo.at(0x10).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PLPUW");
						for (int i = 0; i < 256; i++)
						{
							csTemp.Format(_T("%3d us"), (i + 1) * 2);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x11).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PLPUC");
						for (int i = 0; i < 64; i++)
						{
							csTemp.Format(_T("%d LED Pulse"), i + 1);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x12).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PLDR");
						pCtrlDetail->NameMapping[0] = _T("25% Iledmax");
						pCtrlDetail->NameMapping[1] = _T("50% Iledmax");
						pCtrlDetail->NameMapping[2] = _T("75% Iledmax");
						pCtrlDetail->NameMapping[3] = _T("100% Iledmax");
					}

					DlgCheck.Init(TAB_2, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PLASER");
						pCtrlDetail->NameMapping[0] = _T("160 mA");
						pCtrlDetail->NameMapping[1] = _T("16 mA");
					}
				}

				pRegTable->RegInfo.at(0x13).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PCTDAC");
						for (int i = 0; i < 32; i++)
						{
							csTemp.Format(_T("%2d step"), i);
							pCtrlDetail->NameMapping[i] = csTemp;

						}
					}

					DlgCheck.Init(TAB_2, make_pair(0, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PCTGAIN");
						pCtrlDetail->NameMapping[0] = _T("x1");
						pCtrlDetail->NameMapping[1] = _T("x2");
						pCtrlDetail->NameMapping[2] = _T("x3");
					}
				}

				pRegTable->RegInfo.at(0x1E).bEngMode = FALSE;
				{
					DlgCheck.Init(MAIN_DIALOG, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("AERR"), _T("AERR"));
						pCtrlDetail->BitMapping[0] = _T("AERR");
						pCtrlDetail->CtrlType = LED;
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(7, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("OBJ"), _T("OBJ"));
						pCtrlDetail->BitMapping[0] = _T("OBJ");
						pCtrlDetail->CtrlType = LED;
					}
				}

				/* PS Data */
				pRegTable->RegInfo.at(0x28).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PCH"), _T("PCH"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = PS_BAR;
						pCtrlDetail->BitMapping[0] = _T("PCH");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Channel"), _T("PS Channel"));
						pCtrlDetail->CtrlType = PROGRESS_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PCH");
					}
				}

				/* ACH0 Data */
				pRegTable->RegInfo.at(0x2C).bEngMode = FALSE;
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

					DlgCheck.Init(TAB_2, make_pair(0, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS Channel 0"), _T("ALS Channel 0"));
						pCtrlDetail->CtrlType = PROGRESS_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_SELDATA;
						pCtrlDetail->BitMapping[0] = _T("ACH0");
						pCtrlDetail->RegMapping[0] = 0x2C;
						pCtrlDetail->RegMapping[1] = 0x2E;
					}
				}

				/* ACH1 Data */
				pRegTable->RegInfo.at(0x2E).bEngMode = FALSE;
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

				/* ALS Low Threshold */
				pRegTable->RegInfo.at(0x36).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
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
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AHTH");
					}
				}

				/* PS Low Threshold */
				pRegTable->RegInfo.at(0x3A).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PLTH");
					}
				}

				/* PS High Threshold */
				pRegTable->RegInfo.at(0x3C).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PHTH");
					}
				}

				/* PS Calibration */
				pRegTable->RegInfo.at(0x3E).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PCALB");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = BUTTON_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CALIBRATION;
						pCtrlDetail->BitMapping[0] = _T("PCALB");
						pCtrlDetail->RegMapping[0] = 0x28;
					}
				}
			}

#if defined(_DEBUG)
			pDieDetail->DlgStyle[TAB_3] = PAGE_STYLE1;
			pDieDetail->DlgName[TAB_3] = _T("IR");
			pCtrlInfo[TAB_3] = &pDieDetail->CtrlInfo[TAB_3];

			DlgCheck.Init(TAB_1, make_pair(0, 6));
			ASSERT(DlgCheckSet.insert(DlgCheck).second);
			pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
			{
				pCtrlDetail->CtrlType = CHECK_GROUP;
				pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
				pCtrlDetail->BitMapping[0] = _T("IREN");
			}

			DlgCheck.Init(MAIN_DIALOG, make_pair(2, 0));
			ASSERT(DlgCheckSet.insert(DlgCheck).second);
			pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
			{
				pCtrlDetail->CtrlName = make_pair(_T("IR"), _T("IR"));
				pCtrlDetail->CtrlType = LED;
				pCtrlDetail->BitMapping[0] = _T("IRINT");
			}

			DlgCheck.Init(TAB_3, make_pair(6, 0));
			ASSERT(DlgCheckSet.insert(DlgCheck).second);
			pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
			{
				pCtrlDetail->CtrlType = CHECK_GROUP;
				pCtrlDetail->BitMapping[0] = _T("IRIEN");
			}

			DlgCheck.Init(TAB_3, make_pair(6, 1));
			ASSERT(DlgCheckSet.insert(DlgCheck).second);
			pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
			{
				pCtrlDetail->CtrlType = CHECK_GROUP;
				pCtrlDetail->BitMapping[0] = _T("IRPEND");
			}

			pRegTable->RegInfo.at(0x16).bEngMode = FALSE;
			{
				DlgCheck.Init(TAB_3, make_pair(0, 0));
				ASSERT(DlgCheckSet.insert(DlgCheck).second);
				pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
				{
					pCtrlDetail->CtrlType = COMBO_GROUP;
					pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
					pCtrlDetail->BitMapping[0] = _T("IRMEAN");
					pCtrlDetail->NameMapping[0] = _T("1 Time");
					pCtrlDetail->NameMapping[1] = _T("2 Times");
					pCtrlDetail->NameMapping[2] = _T("4 Times");
					pCtrlDetail->NameMapping[3] = _T("8 Times");
					pCtrlDetail->NameMapping[4] = _T("16 Times");
					pCtrlDetail->NameMapping[5] = _T("32 Times");
					pCtrlDetail->NameMapping[6] = _T("64 Times");
				}
			}

			pRegTable->RegInfo.at(0x18).bEngMode = FALSE;
			{
				DlgCheck.Init(TAB_3, make_pair(2, 0));
				ASSERT(DlgCheckSet.insert(DlgCheck).second);
				pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
				{
					pCtrlDetail->CtrlType = EDIT_GROUP;
					pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_RANGE;
					pCtrlDetail->CtrlFunc |= CTRLFUNC_CHANGE_CONVERSION_TIME;
					pCtrlDetail->BitMapping[0] = _T("IRTIME");
					for (int i = 0; i < 0x3f; i++)
						pCtrlDetail->RangeMapping[i] = make_pair(0, 255 + i * 256);
					pCtrlDetail->RegMapping[0] = 0x2A;
				}
			}

			pRegTable->RegInfo.at(0x19).bEngMode = FALSE;
			{
				DlgCheck.Init(TAB_3, make_pair(4, 0));
				ASSERT(DlgCheckSet.insert(DlgCheck).second);
				pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
				{
					pCtrlDetail->CtrlType = COMBO_GROUP;
					pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
					pCtrlDetail->BitMapping[0] = _T("IRPUW");
					for (int i = 0; i < 256; i++)
					{
						csTemp.Format(_T("%3d us"), (i + 1) * 2);
						pCtrlDetail->NameMapping[i] = csTemp;
					}
				}
			}

			DlgCheck.Init(MAIN_DIALOG, make_pair(5, 0));
			ASSERT(DlgCheckSet.insert(DlgCheck).second);
			pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
			{
				pCtrlDetail->CtrlName = make_pair(_T("PERR"), _T("PERR"));
				pCtrlDetail->BitMapping[0] = _T("PERR");
				pCtrlDetail->CtrlType = LED;
			}

			DlgCheck.Init(MAIN_DIALOG, make_pair(6, 0));
			ASSERT(DlgCheckSet.insert(DlgCheck).second);
			pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
			{
				pCtrlDetail->CtrlName = make_pair(_T("IRERR"), _T("IRERR"));
				pCtrlDetail->BitMapping[0] = _T("IRERR");
				pCtrlDetail->CtrlType = LED;
			}

			/* IR Data */
			pRegTable->RegInfo.at(0x2A).bEngMode = FALSE;
			{
				DlgCheck.Init(MODEL_1, make_pair(3, 0));
				ASSERT(DlgCheckSet.insert(DlgCheck).second);
				pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
				{
					pCtrlDetail->CtrlName = make_pair(_T("IRCH"), _T("IRCH"));
					pCtrlDetail->CtrlType = PROGRESSBAR;
					pCtrlDetail->BitMapping[0] = _T("IRCH");
				}
			}
#endif

			pRegTable->BitDetail.at(_T("AEN")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("PEN")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("ATIME")).DefaultVal.at(0) = 63;
			pRegTable->BitDetail.at(_T("PTIME")).DefaultVal.at(0) = 0x0F;
			pRegTable->BitDetail.at(_T("PLPUW")).DefaultVal.at(0) = 0x3F;
			pRegTable->BitDetail.at(_T("PLASER")).DefaultVal.at(0) = 0x00;
			pRegTable->BitDetail.at(_T("PLDR")).DefaultVal.at(0) = 0x03;

			pReadTable = &pRegTable->ReadTable;
			pReadTable->insert(CReadTable(0x01, 1));
			pReadTable->insert(CReadTable(0x1E, 1));
#if defined(_DEBUG)
			pReadTable->insert(CReadTable(0x28, 8, LogDec));
#else
			pReadTable->insert(CReadTable(0x28, 2, LogDec));
			pReadTable->insert(CReadTable(0x2C, 4, LogDec));
#endif
			break;
		}
		case 8000: {
			DieVersion = 13000;
			pDieInfo->Init(DieVersion);
			pDieDetail = &pDieInfo->DieDetail.at(DieVersion);

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

			//pDieDetail->DlgStyle[MODEL_2] = MODELLESS1;
			//pDieDetail->DlgName[MODEL_2] = _T("Lux");
			//pCtrlInfo[MODEL_2] = &pDieDetail->CtrlInfo[MODEL_2];

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

					DlgCheck.Init(TAB_1, make_pair(0, 5));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PEN");
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

					DlgCheck.Init(TAB_2, make_pair(4, 10));
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
						pCtrlDetail->CtrlName = make_pair(_T("PS"), _T("PS"));
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->BitMapping[0] = _T("PINT");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(3, 0));
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
						pCtrlDetail->BitMapping[0] = _T("PIEN");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("APEND");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 3));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PPEND");
					}
				}

				pRegTable->RegInfo.at(0x06).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(6, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("WTIME");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 8));
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
					DlgCheck.Init(TAB_2, make_pair(0, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("APERS");
						pCtrlDetail->NameMapping[0] = _T("Every cycles");
						for (int i = 1; i < 64; i++)
						{
							csTemp.Format(_T("After %d"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x08).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 8));
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

					DlgCheck.Init(TAB_2, make_pair(2, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_SELDATA;
						pCtrlDetail->BitMapping[0] = _T("ASRC");
						pCtrlDetail->NameMapping[0] = _T("ACH0 as ADATA");
						pCtrlDetail->NameMapping[1] = _T("ACH1 as ADATA");
						pCtrlDetail->RegMapping[0] = 0x2C;
						pCtrlDetail->RegMapping[1] = 0x2E;
					}
				}

				pRegTable->RegInfo.at(0x09).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 8));
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
						pCtrlDetail->RegMapping[2] = 0x36;
						pCtrlDetail->RegMapping[3] = 0x38;
					}
				}

				pRegTable->RegInfo.at(0x0C).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PPERS");
						pCtrlDetail->NameMapping[0] = _T("Every cycles");
						for (int i = 1; i < 64; i++)
						{
							csTemp.Format(_T("After %d"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x0D).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PMEAN");
						pCtrlDetail->NameMapping[0] = _T("1 Time");
						pCtrlDetail->NameMapping[1] = _T("2 Times");
						pCtrlDetail->NameMapping[2] = _T("4 Times");
						pCtrlDetail->NameMapping[3] = _T("8 Times");
						pCtrlDetail->NameMapping[4] = _T("16 Times");
						pCtrlDetail->NameMapping[5] = _T("32 Times");
						pCtrlDetail->NameMapping[6] = _T("64 Times");
					}
				}

				pRegTable->RegInfo.at(0x0E).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PMODE");
						pCtrlDetail->NameMapping[0] = _T("Zone Interrupt");
						pCtrlDetail->NameMapping[1] = _T("Hysteresis Interrupt");

					}

					DlgCheck.Init(TAB_2, make_pair(6, 5));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Acceleration"), _T(""));
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PACC");

					}
				}

				pRegTable->RegInfo.at(0x0F).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_RANGE;
						pCtrlDetail->CtrlFunc |= CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PTIME");
						for (int i = 0; i < 16; i++)
							pCtrlDetail->RangeMapping[i] = make_pair(0, 255 + i * 256);
						pCtrlDetail->RegMapping[0] = 0x28;
						pCtrlDetail->RegMapping[1] = 0x3A;
						pCtrlDetail->RegMapping[2] = 0x3C;
					}
				}

				pRegTable->RegInfo.at(0x10).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PLPUW");
						for (int i = 0; i < 256; i++)
						{
							csTemp.Format(_T("%3d us"), (i + 1) * 2);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x11).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->BitMapping[0] = _T("PLPUC");
						for (int i = 0; i < 64; i++)
						{
							csTemp.Format(_T("%d LED Pulse"), i + 1);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x12).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PLDR");
						pCtrlDetail->NameMapping[0] = _T("25% Iledmax");
						pCtrlDetail->NameMapping[1] = _T("50% Iledmax");
						pCtrlDetail->NameMapping[2] = _T("75% Iledmax");
						pCtrlDetail->NameMapping[3] = _T("100% Iledmax");
					}

					DlgCheck.Init(TAB_2, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PLASER");
						pCtrlDetail->NameMapping[0] = _T("160 mA");
						pCtrlDetail->NameMapping[1] = _T("16 mA");
					}
				}

				pRegTable->RegInfo.at(0x13).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PCTDAC");
						for (int i = 0; i < 32; i++)
						{
							csTemp.Format(_T("%2d step"), i);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}

					DlgCheck.Init(TAB_2, make_pair(0, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PCTGAIN");
						pCtrlDetail->NameMapping[0] = _T("x1");
						pCtrlDetail->NameMapping[1] = _T("x2");
						pCtrlDetail->NameMapping[2] = _T("x3");
					}
				}

				pRegTable->RegInfo.at(0x1E).bEngMode = FALSE;
				{
					DlgCheck.Init(MAIN_DIALOG, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("AERR"), _T("AERR"));
						pCtrlDetail->BitMapping[0] = _T("AERR");
						pCtrlDetail->CtrlType = LED;
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(7, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("OBJ"), _T("OBJ"));
						pCtrlDetail->BitMapping[0] = _T("OBJ");
						pCtrlDetail->CtrlType = LED;
					}
				}
				/* PS Data */
				pRegTable->RegInfo.at(0x28).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PCH"), _T("PCH"));
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor.first = PS_BAR;
						pCtrlDetail->BitMapping[0] = _T("PCH");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Channel"), _T("PS Channel"));
						pCtrlDetail->CtrlType = PROGRESS_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PCH");
					}
				}

				/* ACH0 Data */
				pRegTable->RegInfo.at(0x2C).bEngMode = FALSE;
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

					DlgCheck.Init(TAB_2, make_pair(0, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("ALS Channel 0"), _T("ALS Channel 0"));
						pCtrlDetail->CtrlType = PROGRESS_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_SELDATA;
						pCtrlDetail->BitMapping[0] = _T("ACH0");
						pCtrlDetail->RegMapping[0] = 0x2C;
						pCtrlDetail->RegMapping[1] = 0x2E;
					}
				}

				/* ACH1 Data */
				pRegTable->RegInfo.at(0x2E).bEngMode = FALSE;
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

				/* ALS Low Threshold */
				pRegTable->RegInfo.at(0x36).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
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
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AHTH");
					}
				}

				/* PS Low Threshold */
				pRegTable->RegInfo.at(0x3A).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PLTH");
					}
				}

				/* PS High Threshold */
				pRegTable->RegInfo.at(0x3C).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = SLIDER_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PHTH");
					}
				}

				/* PS Calibration */
				pRegTable->RegInfo.at(0x3E).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PCALB");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = BUTTON_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CALIBRATION;
						pCtrlDetail->BitMapping[0] = _T("PCALB");
						pCtrlDetail->RegMapping[0] = 0x28;
					}
				}
			}

#if defined(_DEBUG)
			pDieDetail->DlgStyle[TAB_3] = PAGE_STYLE1;
			pDieDetail->DlgName[TAB_3] = _T("IR");
			pCtrlInfo[TAB_3] = &pDieDetail->CtrlInfo[TAB_3];

			DlgCheck.Init(TAB_1, make_pair(0, 6));
			ASSERT(DlgCheckSet.insert(DlgCheck).second);
			pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
			{
				pCtrlDetail->CtrlType = CHECK_GROUP;
				pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
				pCtrlDetail->BitMapping[0] = _T("IREN");
			}

			DlgCheck.Init(MAIN_DIALOG, make_pair(2, 0));
			ASSERT(DlgCheckSet.insert(DlgCheck).second);
			pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
			{
				pCtrlDetail->CtrlName = make_pair(_T("IR"), _T("IR"));
				pCtrlDetail->CtrlType = LED;
				pCtrlDetail->BitMapping[0] = _T("IRINT");
			}

			DlgCheck.Init(TAB_3, make_pair(6, 0));
			ASSERT(DlgCheckSet.insert(DlgCheck).second);
			pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
			{
				pCtrlDetail->CtrlType = CHECK_GROUP;
				pCtrlDetail->BitMapping[0] = _T("IRIEN");
			}

			DlgCheck.Init(TAB_3, make_pair(6, 1));
			ASSERT(DlgCheckSet.insert(DlgCheck).second);
			pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
			{
				pCtrlDetail->CtrlType = CHECK_GROUP;
				pCtrlDetail->BitMapping[0] = _T("IRPEND");
			}

			pRegTable->RegInfo.at(0x16).bEngMode = FALSE;
			{
				DlgCheck.Init(TAB_3, make_pair(0, 0));
				ASSERT(DlgCheckSet.insert(DlgCheck).second);
				pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
				{
					pCtrlDetail->CtrlType = COMBO_GROUP;
					pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
					pCtrlDetail->BitMapping[0] = _T("IRMEAN");
					pCtrlDetail->NameMapping[0] = _T("1 Time");
					pCtrlDetail->NameMapping[1] = _T("2 Times");
					pCtrlDetail->NameMapping[2] = _T("4 Times");
					pCtrlDetail->NameMapping[3] = _T("8 Times");
					pCtrlDetail->NameMapping[4] = _T("16 Times");
					pCtrlDetail->NameMapping[5] = _T("32 Times");
					pCtrlDetail->NameMapping[6] = _T("64 Times");
				}
			}

			pRegTable->RegInfo.at(0x18).bEngMode = FALSE;
			{
				DlgCheck.Init(TAB_3, make_pair(2, 0));
				ASSERT(DlgCheckSet.insert(DlgCheck).second);
				pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
				{
					pCtrlDetail->CtrlType = EDIT_GROUP;
					pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_RANGE;
					pCtrlDetail->CtrlFunc |= CTRLFUNC_CHANGE_CONVERSION_TIME;
					pCtrlDetail->BitMapping[0] = _T("IRTIME");
					for (int i = 0; i < 0x3f; i++)
						pCtrlDetail->RangeMapping[i] = make_pair(0, 255 + i * 256);
					pCtrlDetail->RegMapping[0] = 0x2A;
				}
			}

			pRegTable->RegInfo.at(0x19).bEngMode = FALSE;
			{
				DlgCheck.Init(TAB_3, make_pair(4, 0));
				ASSERT(DlgCheckSet.insert(DlgCheck).second);
				pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
				{
					pCtrlDetail->CtrlType = COMBO_GROUP;
					pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
					pCtrlDetail->BitMapping[0] = _T("IRPUW");
					for (int i = 0; i < 256; i++)
					{
						csTemp.Format(_T("%3d us"), (i + 1) * 2);
						pCtrlDetail->NameMapping[i] = csTemp;
					}
				}
			}

			DlgCheck.Init(MAIN_DIALOG, make_pair(5, 0));
			ASSERT(DlgCheckSet.insert(DlgCheck).second);
			pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
			{
				pCtrlDetail->CtrlName = make_pair(_T("PERR"), _T("PERR"));
				pCtrlDetail->BitMapping[0] = _T("PERR");
				pCtrlDetail->CtrlType = LED;
			}

			DlgCheck.Init(MAIN_DIALOG, make_pair(6, 0));
			ASSERT(DlgCheckSet.insert(DlgCheck).second);
			pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
			{
				pCtrlDetail->CtrlName = make_pair(_T("IRERR"), _T("IRERR"));
				pCtrlDetail->BitMapping[0] = _T("IRERR");
				pCtrlDetail->CtrlType = LED;
			}

			/* IR Data */
			pRegTable->RegInfo.at(0x2A).bEngMode = FALSE;
			{
				DlgCheck.Init(MODEL_1, make_pair(3, 0));
				ASSERT(DlgCheckSet.insert(DlgCheck).second);
				pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
				{
					pCtrlDetail->CtrlName = make_pair(_T("IRCH"), _T("IRCH"));
					pCtrlDetail->CtrlType = PROGRESSBAR;
					pCtrlDetail->BitMapping[0] = _T("IRCH");
				}
			}
#endif

			pRegTable->BitDetail.at(_T("AEN")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("PEN")).DefaultVal.at(0) = 0x01;
			pRegTable->BitDetail.at(_T("ATIME")).DefaultVal.at(0) = 63;
			pRegTable->BitDetail.at(_T("PTIME")).DefaultVal.at(0) = 0x0F;
			pRegTable->BitDetail.at(_T("PLPUW")).DefaultVal.at(0) = 0x3F;
			pRegTable->BitDetail.at(_T("PLASER")).DefaultVal.at(0) = 0x00;
			pRegTable->BitDetail.at(_T("PLDR")).DefaultVal.at(0) = 0x03;

			pReadTable = &pRegTable->ReadTable;
			pReadTable->insert(CReadTable(0x01, 1));
			pReadTable->insert(CReadTable(0x1E, 1));
#if defined(_DEBUG)
			pReadTable->insert(CReadTable(0x28, 8, LogDec));
#else
			pReadTable->insert(CReadTable(0x28, 2, LogDec));
			pReadTable->insert(CReadTable(0x2C, 4, LogDec));
#endif
			break;
		}
		default: return; 
		}

		DlgCheck.Init(TAB_1, make_pair(0, 0));
		ASSERT(DlgCheckSet.insert(DlgCheck).second);
		pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
		{
			pCtrlDetail->CtrlName = make_pair(_T("Sensor Name"), ModelName);
			pCtrlDetail->CtrlType = TEXT_GROUP;
			pCtrlDetail->CtrlFunc = CTRLFUNC_SHOWTEXT;
		}

		DlgCheck.Init(TAB_1, make_pair(2, 0));
		ASSERT(DlgCheckSet.insert(DlgCheck).second);
		pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
		{
			pCtrlDetail->CtrlName = make_pair(_T("Data Sheet Version"), _T(""));
			pCtrlDetail->CtrlType = TEXT_GROUP;
			pCtrlDetail->CtrlFunc = CTRLFUNC_SHOW_DATASHEET;
		}

		DlgCheck.Init(TAB_1, make_pair(4, 0));
		ASSERT(DlgCheckSet.insert(DlgCheck).second);
		pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
		{
			pCtrlDetail->CtrlName = make_pair(_T("Control Board Version"), _T(""));
			pCtrlDetail->CtrlType = TEXT_GROUP;
			pCtrlDetail->CtrlFunc = CTRLFUNC_SHOW_BRIDGE_VERSION;
		}

#if defined(_DEBUG)
		DlgCheck.Init(TAB_1, make_pair(6, 0));
		ASSERT(DlgCheckSet.insert(DlgCheck).second);
		pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
		{
			pCtrlDetail->CtrlName = make_pair(_T("Die Version"), _T(""));
			pCtrlDetail->CtrlType = TEXT_GROUP;
			pCtrlDetail->CtrlFunc = CTRLFUNC_SHOW_DIEVERSION;
		}
#endif
	}
};
