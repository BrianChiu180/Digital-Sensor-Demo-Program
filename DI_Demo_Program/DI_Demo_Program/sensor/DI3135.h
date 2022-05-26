#pragma once
#include "Define.h"
#include "DI3135_D.h"

class CDI3135 : public CSensorInfo {
public:
	CDI3135()
	{
		ModelName = _T("DI3135");
		pDieInfo = new CDI3135_D;
#if defined(_DI3135_10000) || defined(_DEBUG) || defined(_DI3135)
		ModelVersion.insert(10000);//1.0
#endif

#if defined(_DEBUG) || defined(_DI3135)
		ModelSelAddress.insert(0x18);
		ModelSelAddress.insert(0x19);
		ModelDefaultAddress = 0x18;
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
			pDieDetail->DlgName[TAB_1] = _T("Main");
			pCtrlInfo[TAB_1] = &pDieDetail->CtrlInfo[TAB_1];

			pDieDetail->DlgStyle[TAB_2] = PAGE_STYLE1;
			pDieDetail->DlgName[TAB_2] = _T("INT&&TAP");
			pCtrlInfo[TAB_2] = &pDieDetail->CtrlInfo[TAB_2];

			pDieDetail->DlgStyle[TAB_3] = PAGE_STYLE1;
			pDieDetail->DlgName[TAB_3] = _T("FIFO");
			pCtrlInfo[TAB_3] = &pDieDetail->CtrlInfo[TAB_3];

			pDieDetail->DlgStyle[MODEL_1] = MODELLESS1;
			pDieDetail->DlgName[MODEL_1] = _T("Data Progress Bar");
			pCtrlInfo[MODEL_1] = &pDieDetail->CtrlInfo[MODEL_1];

			pDieDetail->DieFunc |= DF_AXIS;
			pDieDetail->DlgStyle[MODEL_2] = MODELLESS1;
			pDieDetail->DlgName[MODEL_2] = _T("Axis");
			pCtrlInfo[MODEL_2] = &pDieDetail->CtrlInfo[MODEL_2];

			pDieDetail->DlgStyle[MODEL_3] = MODELLESS_LIST;
			pDieDetail->DlgName[MODEL_3] = _T("Register Table");
			pRegTable = &pDieDetail->RegisterTable;
			{
				pRegTable->RegInfo.at(0x00).bEngMode = FALSE;
				pRegTable->RegInfo.at(0x01).bEngMode = FALSE;
				{
					DlgCheck.Init(MAIN_DIALOG, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("SRDY"), _T("Status of Data ready"));
						pCtrlDetail->BitMapping[0] = _T("STS_DRDY");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(1, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("SWTM"), _T("Status of FIFO water mark"));
						pCtrlDetail->BitMapping[0] = _T("STS_WTM");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("SOVN"), _T("Status of FIFO overrun"));
						pCtrlDetail->BitMapping[0] = _T("STS_OVN");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(3, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("SAOI"), _T("Status of AOI (Shock/Freefall/Profile/Gesture)"));
						pCtrlDetail->BitMapping[0] = _T("STS_AOI");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("STAP"), _T("Status of Tap Sensing"));
						pCtrlDetail->BitMapping[0] = _T("STS_TAP");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(5, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("SACT"), _T("Status of activity"));
						pCtrlDetail->BitMapping[0] = _T("STS_ACT");
					}
				}
				pRegTable->RegInfo.at(0x02).bEngMode = FALSE;
				{
					DlgCheck.Init(MAIN_DIALOG, make_pair(6, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("STBY"), _T("Power down mode status"));
						pCtrlDetail->BitMapping[0] = _T("STS_STBY");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(7, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("SWAK"), _T("Wakeup mode status"));
						pCtrlDetail->BitMapping[0] = _T("STS_WAK");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(8, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("SMEAS"), _T("Measurement mode statusg"));
						pCtrlDetail->BitMapping[0] = _T("STS_MEAS");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(9, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("PDRDY"), _T("Status of Data ready"));
						pCtrlDetail->BitMapping[0] = _T("PO_DRDY");
					}
				}

				pRegTable->RegInfo.at(0x07).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(6, 11));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("SELF_TEST");
					}
				}

				pRegTable->RegInfo.at(0x08).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(0, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = RADIO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlName = make_pair(_T("Operation Mode"), _T(""));
						pCtrlDetail->BitMapping[0] = _T("MEASURE");
						pCtrlDetail->NameMapping[0] = _T("[0x0] Power Down Mode");
						pCtrlDetail->NameMapping[1] = _T("[0x1] Wakeup Mode");
						pCtrlDetail->NameMapping[2] = _T("[0x2] Normal Measurement Mode");
						pCtrlDetail->I2CWriteDelayMs = 60;

					}

					DlgCheck.Init(TAB_1, make_pair(6, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = BUTTON_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_SWRST;
						pCtrlDetail->CtrlName = make_pair(_T("Software Reset"), _T(""));
						pCtrlDetail->BitMapping[0] = _T("SW_RST");
						pCtrlDetail->I2CWriteDelayMs = 60;
					}
				}
				pRegTable->RegInfo.at(0x09).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(4, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("XEN");
					}

					DlgCheck.Init(TAB_1, make_pair(4, 3));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("YEN");
					}

					DlgCheck.Init(TAB_1, make_pair(4, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ZEN");
					}

					DlgCheck.Init(TAB_1, make_pair(4, 5));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("HR");
					}

					DlgCheck.Init(TAB_1, make_pair(0, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_CONVERSION_TIME;
						pCtrlDetail->CtrlName = make_pair(_T("ODR"), _T(""));
						pCtrlDetail->BitMapping[0] = _T("ODR");
						pCtrlDetail->NameMapping[0] = _T("[0x0] 6.25 Hz");
						pCtrlDetail->NameMapping[1] = _T("[0x1] 12.5 Hz");
						pCtrlDetail->NameMapping[2] = _T("[0x2] 25 Hz");
						pCtrlDetail->NameMapping[3] = _T("[0x3] 50 Hz");
						pCtrlDetail->NameMapping[4] = _T("[0x4] 100 Hz");
						pCtrlDetail->NameMapping[5] = _T("[0x5] 200 Hz");
						pCtrlDetail->NameMapping[6] = _T("[0x6] 400 Hz");
					}
				}

				pRegTable->RegInfo.at(0x0A).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(2, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->CtrlName = make_pair(_T("Full Scale Range"), _T(""));
						pCtrlDetail->BitMapping[0] = _T("FSCALE");
						pCtrlDetail->NameMapping[0] = _T("[0x0] +-2G");
						pCtrlDetail->NameMapping[1] = _T("[0x1] +-4G");
						pCtrlDetail->NameMapping[2] = _T("[0x2] +-8G");
						pCtrlDetail->NameMapping[3] = _T("[0x3] +-16G");
						pCtrlDetail->CtrlFunc = CTRLFUNC_CHANGE_SCALE;
						pCtrlDetail->ValueScaleMapping[0] = 4.0 / 4096.0;
						pCtrlDetail->ValueScaleMapping[1] = 8.0 / 4096.0;
						pCtrlDetail->ValueScaleMapping[2] = 16.0 / 4096.0;
						pCtrlDetail->ValueScaleMapping[3] = 32.0 / 4096.0;
					}

					DlgCheck.Init(TAB_2, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IRQ1_POL");
						pCtrlDetail->NameMapping[0] = _T("Interrupt flag is Low active");
						pCtrlDetail->NameMapping[1] = _T("Interrupt flag is High active");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("IRQ2_POL");
						pCtrlDetail->NameMapping[0] = _T("Interrupt flag is Low active");
						pCtrlDetail->NameMapping[1] = _T("Interrupt flag is High active");
					}

					DlgCheck.Init(TAB_2, make_pair(0, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("I1_SLP");

					}

					DlgCheck.Init(TAB_2, make_pair(4, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("I2_SLP");

					}

					DlgCheck.Init(TAB_2, make_pair(0, 3));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("I1_ACT");

					}

					DlgCheck.Init(TAB_2, make_pair(4, 3));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("I2_ACT");

					}
				}

				pRegTable->RegInfo.at(0x0B).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("LATCH1_SEL");
						pCtrlDetail->NameMapping[0] = _T("Non-Latched");
						pCtrlDetail->NameMapping[1] = _T("Latched");
						pCtrlDetail->NameMapping[2] = _T("2.5 msec");
						pCtrlDetail->NameMapping[3] = _T("5 msec");
						pCtrlDetail->NameMapping[4] = _T("10 msec");
						pCtrlDetail->NameMapping[5] = _T("20 msec");
						pCtrlDetail->NameMapping[6] = _T("40 msec");
						pCtrlDetail->NameMapping[7] = _T("80 msec");
						pCtrlDetail->NameMapping[8] = _T("160 msec");
						pCtrlDetail->NameMapping[9] = _T("320 msec");
						pCtrlDetail->NameMapping[10] = _T("640 msec");
						pCtrlDetail->NameMapping[11] = _T("1.3 sec");
						pCtrlDetail->NameMapping[12] = _T("2.5 sec");
						pCtrlDetail->NameMapping[13] = _T("5.1 sec");
						pCtrlDetail->NameMapping[14] = _T("10.25 sec");
						pCtrlDetail->NameMapping[15] = _T("20.5 sec");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("LATCH2_SEL");
						pCtrlDetail->NameMapping[0] = _T("Non-Latched");
						pCtrlDetail->NameMapping[1] = _T("Latched");
						pCtrlDetail->NameMapping[2] = _T("2.5 msec");
						pCtrlDetail->NameMapping[3] = _T("5 msec");
						pCtrlDetail->NameMapping[4] = _T("10 msec");
						pCtrlDetail->NameMapping[5] = _T("20 msec");
						pCtrlDetail->NameMapping[6] = _T("40 msec");
						pCtrlDetail->NameMapping[7] = _T("80 msec");
						pCtrlDetail->NameMapping[8] = _T("160 msec");
						pCtrlDetail->NameMapping[9] = _T("320 msec");
						pCtrlDetail->NameMapping[10] = _T("640 msec");
						pCtrlDetail->NameMapping[11] = _T("1.3 sec");
						pCtrlDetail->NameMapping[12] = _T("2.5 sec");
						pCtrlDetail->NameMapping[13] = _T("5.1 sec");
						pCtrlDetail->NameMapping[14] = _T("10.25 sec");
						pCtrlDetail->NameMapping[15] = _T("20.5 sec");
					}
				}

				pRegTable->RegInfo.at(0x10).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor = make_pair(AXIS_POS_BAR, AXIS_NEG_BAR);
						pCtrlDetail->CtrlName = make_pair(_T("X"), _T("X"));
						pCtrlDetail->BitMapping[0] = _T("XDATA");
					}

					DlgCheck.Init(MODEL_2, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Xg"), _T(""));
						pCtrlDetail->CtrlType = TEXT_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_AXIS;
						pCtrlDetail->BitMapping[0] = _T("XDATA");
					}
				}
				pRegTable->RegInfo.at(0x12).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(1, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor = make_pair(AXIS_POS_BAR, AXIS_NEG_BAR);
						pCtrlDetail->CtrlName = make_pair(_T("Y"), _T("Y"));
						pCtrlDetail->BitMapping[0] = _T("YDATA");
					}

					DlgCheck.Init(MODEL_2, make_pair(0, 1));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Yg"), _T(""));
						pCtrlDetail->CtrlType = TEXT_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_AXIS;
						pCtrlDetail->BitMapping[0] = _T("YDATA");
					}
				}
				pRegTable->RegInfo.at(0x14).bEngMode = FALSE;
				{
					DlgCheck.Init(MODEL_1, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = PROGRESSBAR;
						pCtrlDetail->CtrlColor = make_pair(AXIS_POS_BAR, AXIS_NEG_BAR);
						pCtrlDetail->CtrlName = make_pair(_T("Z"), _T("Z"));
						pCtrlDetail->BitMapping[0] = _T("ZDATA");
					}

					DlgCheck.Init(MODEL_2, make_pair(0, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Zg"), _T(""));
						pCtrlDetail->CtrlType = TEXT_GROUP;
						pCtrlDetail->CtrlFunc = CTRLFUNC_AXIS;
						pCtrlDetail->BitMapping[0] = _T("ZDATA");
					}
				}
				pRegTable->RegInfo.at(0x16).bEngMode = FALSE;
				pRegTable->RegInfo.at(0x17).bEngMode = FALSE;
				{
					DlgCheck.Init(MAIN_DIALOG, make_pair(10, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("EMPTY"), _T("EMPTY"));
						pCtrlDetail->BitMapping[0] = _T("EMPTY");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(11, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("WTM"), _T("WTM"));
						pCtrlDetail->BitMapping[0] = _T("WTM");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(12, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("OVN"), _T("OVN"));
						pCtrlDetail->BitMapping[0] = _T("OVN");
					}
				}

				pRegTable->RegInfo.at(0x18).bEngMode = FALSE;
				{
					DlgCheck.Init(MAIN_DIALOG, make_pair(13, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("XL"), _T("XL"));
						pCtrlDetail->BitMapping[0] = _T("XL");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(14, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("XH"), _T("XH"));
						pCtrlDetail->BitMapping[0] = _T("XH");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(15, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("YL"), _T("YL"));
						pCtrlDetail->BitMapping[0] = _T("YL");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(16, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("YH"), _T("YH"));
						pCtrlDetail->BitMapping[0] = _T("YH");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(17, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("ZL"), _T("ZL"));
						pCtrlDetail->BitMapping[0] = _T("ZL");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(18, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("ZH"), _T("ZH"));
						pCtrlDetail->BitMapping[0] = _T("ZH");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(19, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("PO_AOI"), _T("PO_AOI"));
						pCtrlDetail->BitMapping[0] = _T("PO_AOI");
					}
				}

				pRegTable->RegInfo.at(0x19).bEngMode = FALSE;
				{
					DlgCheck.Init(MAIN_DIALOG, make_pair(20, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("SIGNX"), _T("SIGNX"));
						pCtrlDetail->BitMapping[0] = _T("SIGN_X");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(21, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("SIGNY"), _T("SIGNY"));
						pCtrlDetail->BitMapping[0] = _T("SIGN_Y");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(22, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("SIGNZ"), _T("SIGNZ"));
						pCtrlDetail->BitMapping[0] = _T("SIGN_Z");
					}
				}

				pRegTable->RegInfo.at(0x1A).bEngMode = FALSE;
				{
					DlgCheck.Init(MAIN_DIALOG, make_pair(23, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("XTAP"), _T("XTAP"));
						pCtrlDetail->BitMapping[0] = _T("XTAP");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(24, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("YTAP"), _T("YTAP"));
						pCtrlDetail->BitMapping[0] = _T("YTAP");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(25, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("ZTAP"), _T("ZTAP"));
						pCtrlDetail->BitMapping[0] = _T("ZTAP");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(26, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("SIGN"), _T("SIGN"));
						pCtrlDetail->BitMapping[0] = _T("SIGN");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(27, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("STAP"), _T("STAP"));
						pCtrlDetail->BitMapping[0] = _T("STAP");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(28, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("DTAP"), _T("DTAP"));
						pCtrlDetail->BitMapping[0] = _T("DTAP");
					}

					DlgCheck.Init(MAIN_DIALOG, make_pair(29, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = LED;
						pCtrlDetail->CtrlName = make_pair(_T("PTAP"), _T("PTAP"));
						pCtrlDetail->BitMapping[0] = _T("PO_TAP");
					}
				}

				pRegTable->RegInfo.at(0x20).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("I1_DRDY");

					}

					DlgCheck.Init(TAB_2, make_pair(2, 1));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("I1_WTM");

					}

					DlgCheck.Init(TAB_2, make_pair(2, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("I1_OVN");

					}

					DlgCheck.Init(TAB_2, make_pair(2, 3));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("I1_AOI");

					}

					DlgCheck.Init(TAB_2, make_pair(2, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("I1_TIA");

					}
				}

				pRegTable->RegInfo.at(0x21).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(6, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("I2_DRDY");

					}

					DlgCheck.Init(TAB_2, make_pair(6, 1));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("I2_WTM");

					}

					DlgCheck.Init(TAB_2, make_pair(6, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("I2_OVN");

					}

					DlgCheck.Init(TAB_2, make_pair(6, 3));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("I2_AOI");

					}

					DlgCheck.Init(TAB_2, make_pair(6, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("I2_TIA");

					}
				}
				
				pRegTable->RegInfo.at(0x22).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(2, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("TRIG_SRC");
						pCtrlDetail->NameMapping[0] = _T("Trigger source is AOI detection");
						pCtrlDetail->NameMapping[1] = _T("Trigger source is tapping sensing");
						pCtrlDetail->NameMapping[2] = _T("Trigger source is significant motion");
					}

					DlgCheck.Init(TAB_3, make_pair(2, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("FIFO_SKIP");
						pCtrlDetail->NameMapping[0] = _T("Disable skip function");
						pCtrlDetail->NameMapping[1] = _T("Only record one sample per 2 samples, the others are dropped.");
						pCtrlDetail->NameMapping[2] = _T("Only record one sample per 4 samples, the others are dropped");
						pCtrlDetail->NameMapping[3] = _T("Only record one sample per 8 samples, the others are dropped");
					}

					DlgCheck.Init(TAB_3, make_pair(0, 2));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("FIFO_MODE");
						pCtrlDetail->NameMapping[0] = _T("Bypass mode");
						pCtrlDetail->NameMapping[1] = _T("FIFO mode");
						pCtrlDetail->NameMapping[2] = _T("Stream mode");
						pCtrlDetail->NameMapping[3] = _T("Trigger mode (Stream-to-FIFO mode)");
					}

					DlgCheck.Init(TAB_3, make_pair(0, 4));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("FIFO_HR");
						pCtrlDetail->NameMapping[0] = _T("12bits data content is recorded in FIFO");
						pCtrlDetail->NameMapping[1] = _T("MSB 8bits data content is recorded in FIFO");
					}

					DlgCheck.Init(TAB_3, make_pair(0, 0));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("FIFO_EN");

					}
				}

				pRegTable->RegInfo.at(0x23).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_3, make_pair(0, 6));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("FIFO_THRES");
					}
				}

				pRegTable->RegInfo.at(0x24).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_1, make_pair(4, 7));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("HP_DATA");

					}

					DlgCheck.Init(TAB_1, make_pair(4, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("HP_AOI");

					}

					DlgCheck.Init(TAB_1, make_pair(4, 9));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("UNSIGN");

					}
				}

				pRegTable->RegInfo.at(0x30).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("COMP_X");
						pCtrlDetail->NameMapping[0] = _T("Higher than. Axis is higher than THSX. Ignore signed bit");
						pCtrlDetail->NameMapping[1] = _T("Lower than. Axis is lower than THSX. Ignore signed bit");
						pCtrlDetail->NameMapping[2] = _T("Relative match. Axis is located in specific range (THSX กำ HYSX). Should compare the signed bit");
						pCtrlDetail->NameMapping[3] = _T("Absolute match. Axis is located in any positive or negative range (THSX กำ HYSX). Ignore signed bit");
					}

					DlgCheck.Init(TAB_2, make_pair(2, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("COMP_Y");
						pCtrlDetail->NameMapping[0] = _T("Higher than. Axis is higher than THSX. Ignore signed bit");
						pCtrlDetail->NameMapping[1] = _T("Lower than. Axis is lower than THSX. Ignore signed bit");
						pCtrlDetail->NameMapping[2] = _T("Relative match. Axis is located in specific range (THSX กำ HYSX). Should compare the signed bit");
						pCtrlDetail->NameMapping[3] = _T("Absolute match. Axis is located in any positive or negative range (THSX กำ HYSX). Ignore signed bit");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("COMP_Z");
						pCtrlDetail->NameMapping[0] = _T("Higher than. Axis is higher than THSX. Ignore signed bit");
						pCtrlDetail->NameMapping[1] = _T("Lower than. Axis is lower than THSX. Ignore signed bit");
						pCtrlDetail->NameMapping[2] = _T("Relative match. Axis is located in specific range (THSX กำ HYSX). Should compare the signed bit");
						pCtrlDetail->NameMapping[3] = _T("Absolute match. Axis is located in any positive or negative range (THSX กำ HYSX). Ignore signed bit");
					}

					DlgCheck.Init(TAB_2, make_pair(6, 8));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AOI");
						pCtrlDetail->NameMapping[0] = _T("OR all three axis conditions");
						pCtrlDetail->NameMapping[1] = _T("AND all three axis conditions");
					}
				}

				pRegTable->RegInfo.at(0x31).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(6, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AOI_ACTIVE_TIME");
					}
				}
				
				pRegTable->RegInfo.at(0x32).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AOI_ACTIVE_THRESH_X");
					}
				}

				pRegTable->RegInfo.at(0x33).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AOI_ACTIVE_THRESH_Y");
					}
				}

				pRegTable->RegInfo.at(0x34).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 10));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AOI_ACTIVE_THRESH_Z");
					}
				}

				pRegTable->RegInfo.at(0x35).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 7));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("XCMP");
					}

					DlgCheck.Init(TAB_2, make_pair(2, 7));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("YCMP");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 7));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ZCMP");
					}


					DlgCheck.Init(TAB_2, make_pair(0, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AOI_HYS_X");
						for (uint8_t i = 0; i < 8; i++)
						{
							csTemp.Format(_T("%d mg"), (uint16_t)i * 16);
							pCtrlDetail->NameMapping[i] = csTemp;
						}					
						for (uint8_t i = 8; i < 16; i++)
						{
							csTemp.Format(_T("%d mg"), (uint16_t)(i-7) * 128);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x36).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AOI_HYS_Y");
						for (uint8_t i = 0; i < 8; i++)
						{
							csTemp.Format(_T("%d mg"), (uint16_t)i * 16);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
						for (uint8_t i = 8; i < 16; i++)
						{
							csTemp.Format(_T("%d mg"), (uint16_t)(i - 7) * 128);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}

					DlgCheck.Init(TAB_2, make_pair(4, 12));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("AOI_HYS_Z");
						for (uint8_t i = 0; i < 8; i++)
						{
							csTemp.Format(_T("%d mg"), (uint16_t)i * 16);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
						for (uint8_t i = 8; i < 16; i++)
						{
							csTemp.Format(_T("%d mg"), (uint16_t)(i - 7) * 128);
							pCtrlDetail->NameMapping[i] = csTemp;
						}
					}

				}

				pRegTable->RegInfo.at(0x37).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("XSEN");
					}

					DlgCheck.Init(TAB_2, make_pair(2, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("YSEN");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ZSEN");
					}

					DlgCheck.Init(TAB_2, make_pair(0, 15));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("XDEN");
					}

					DlgCheck.Init(TAB_2, make_pair(2, 15));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("YDEN");
					}

					DlgCheck.Init(TAB_2, make_pair(4, 15));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlType = CHECK_GROUP;
						pCtrlDetail->BitMapping[0] = _T("ZDEN");
					}
				}

				pRegTable->RegInfo.at(0x38).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(0, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Tapping detected threshold"), _T("Tapping detected threshold"));
						pCtrlDetail->CtrlType = EDIT_GROUP;
						pCtrlDetail->BitMapping[0] = _T("TAP_THRESH");
					}
				}

				pRegTable->RegInfo.at(0x39).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(2, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Tapping pulse window"), _T("Tapping pulse window"));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("TAP_LIMIT");
						for (uint16_t i = 0; i < 256; i++)
						{
							csTemp.Format(_T("%d msec"), i * 10);
							pCtrlDetail->NameMapping[(uint8_t)i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x3A).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(4, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Tapping quiet window"), _T("Tapping quiet window"));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("TAP_LATENCY");
						for (uint16_t i = 0; i < 256; i++)
						{
							csTemp.Format(_T("%d msec"), i * 10);
							pCtrlDetail->NameMapping[(uint8_t)i] = csTemp;
						}
					}
				}

				pRegTable->RegInfo.at(0x3B).bEngMode = FALSE;
				{
					DlgCheck.Init(TAB_2, make_pair(6, 16));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("Tapping interval window"), _T("Tapping interval window"));
						pCtrlDetail->CtrlType = COMBO_GROUP;
						pCtrlDetail->BitMapping[0] = _T("TAP_WINDOW");
						for (uint16_t i = 0; i < 256; i++)
						{
							csTemp.Format(_T("%d msec"), i * 10);
							pCtrlDetail->NameMapping[(uint8_t)i] = csTemp;
						}
					}
				}

			}// pRegTable = &pDieDetail->RegisterTable;

			pRegTable->BitDetail.at(_T("MEASURE")).DefaultVal.at(0) = 0x02;

			pReadTable = &pDieDetail->RegisterTable.ReadTable;
			pReadTable->insert(CReadTable(0x01, 2));
			pReadTable->insert(CReadTable(0x10, 6, LogDec));
			pReadTable->insert(CReadTable(0x16, 5));

			break;
		}// case 10000:

		}// switch (version)
		CSensorInfo::Init();
	}// void Init(uint16_t version)
};
