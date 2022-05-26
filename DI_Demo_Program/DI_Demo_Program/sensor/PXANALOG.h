#pragma once
#include "Define.h"
#include "DA3380.h"

class CPXANALOG : public CSensorInfo {
public:
	CPXANALOG()
	{
		ModelName = _T("PXANALOG");
		pDieInfo = new CDA3380;
#if defined(_PXANALOG_10000) || defined(_DEBUG) || defined(_PXANALOG)
		ModelVersion.insert(10000);
#endif


#if defined(_DEBUG) || defined(_PXANALOG)
		ModelSelAddress.insert(0x1C);
		ModelDefaultAddress = 0x1C;
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

			pDieDetail->DlgStyle[MODEL_1] = MODELLESS1;
			pDieDetail->DlgName[MODEL_1] = _T("Data Progress Bar");
			pCtrlInfo[MODEL_1] = &pDieDetail->CtrlInfo[MODEL_1];

			pDieDetail->DlgStyle[MODEL_3] = MODELLESS_LIST;
			pDieDetail->DlgName[MODEL_3] = _T("Register Table");

			pRegTable = &pDieDetail->RegisterTable;
			{
				pRegTable->DeviceID = 0x1C;

#if 0
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
				}
#endif

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

					DlgCheck.Init(TAB_1, make_pair(0, 14));
					ASSERT(DlgCheckSet.insert(DlgCheck).second);
					pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
					{
						pCtrlDetail->CtrlName = make_pair(_T("PS Data"), _T("PS Data"));
						pCtrlDetail->CtrlType = PROGRESS_GROUP;
						pCtrlDetail->BitMapping[0] = _T("PsData");
					}
				}
			}

			//pRegTable->BitDetail.at(_T("PsEn")).DefaultVal.at(0) = 0x01;
			//pRegTable->BitDetail.at(_T("PsDrv")).DefaultVal.at(0) = 11;	// 12 mA
			//pRegTable->BitDetail.at(_T("PsBits")).DefaultVal.at(0) = 1;	// 10 bit
			//pRegTable->BitDetail.at(_T("PsPuw")).DefaultVal.at(0) = 32;	// 32W

			pReadTable = &pDieDetail->RegisterTable.ReadTable;

			pReadTable->insert(CReadTable(0x00, 2, LogDec));
			
			break;
		}		
		}
		CSensorInfo::Init();
	}
};
