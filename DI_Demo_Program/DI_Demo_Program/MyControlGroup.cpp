#include "stdafx.h"
#include "MyControlGroup.h"
#include "AtmelHIDLIB.h"

IMPLEMENT_DYNAMIC(CMyControlGroup, CDialogEx)

CMyControlGroup::CMyControlGroup(UINT nIDTemplate, CWnd* pParent/* = NULL */)
	: CDialogEx(nIDTemplate, pParent), AvgNum(0), 
	CtrlColor(make_pair(CLR_DEFAULT, CLR_DEFAULT)), DefaultVal(0),CtrlScale(1.0), DevID(0),
	mToolTip(NULL), pBitDetail(NULL), pBitDetail0(NULL), pBitDetailMap(NULL), pBitMapping(NULL), pCCTCalculate(NULL),
	pCtrlDetail(NULL), pDieDetail(NULL), pListName(NULL), pListName2(NULL), 
	pLuxCalculate(NULL), pRegInfo(NULL), pRegInfoMap(NULL), pRegTable(NULL)
{

}


CMyControlGroup::~CMyControlGroup()
{
}

void CMyControlGroup::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyControlGroup, CDialogEx)
	ON_MESSAGE(WM_MESSAGE_CHANGE_AVG_NUM, &CMyControlGroup::OnMessageChangeAvgNum)
END_MESSAGE_MAP()


void CMyControlGroup::CtrlInit(CCtrlDetail* pCtrl, CToolTipCtrl* pToolTip)
{
	mToolTip = pToolTip;
	pCtrlDetail = pCtrl;
}

void CMyControlGroup::CtrlInit(CDieDetail* pDie, CCtrlDetail* pCtrl, CToolTipCtrl* pToolTip)
{
	mToolTip = pToolTip;
	pDieDetail = pDie;
	pCtrlDetail = pCtrl;
	pLuxCalculate = &pDieDetail->LuxCalculate;
	pCCTCalculate = &pDieDetail->CCTCalculate;
	pRegTable = &pDieDetail->RegisterTable;
	DevID = pRegTable->DeviceID;
	pBitDetailMap = &pRegTable->BitDetail;
	pRegInfoMap = &pRegTable->RegInfo;
	pListName = &pCtrlDetail->NameMapping;
	pListName2 = &pCtrlDetail->NameMapping2;
	pBitMapping = &pCtrlDetail->BitMapping;
	pBitDetail0 = NULL;
	pRegCurVal.clear();
	

	CtrlColor = pCtrlDetail->CtrlColor;

	DefaultVal = 0;
	CtrlRange = make_pair(0, 0);	

	if (pCtrlDetail->BitMapping.size() > 0)
	{
		TRACE(_T("BitMapping.at(0) %s\n"), pCtrlDetail->BitMapping.at(0));
		TRACE(_T("BitMapping.size %d\n"), pCtrlDetail->BitMapping.size());

		pBitDetail0 = &pRegTable->BitDetail.at(pCtrlDetail->BitMapping.at(0));
		pRegCurVal.push_back(&pRegTable->RegInfo.at(pBitDetail0->RegAddr).RegCurVal.at(0));

		TRACE(_T("RegAddr 0x%02x\n"), pBitDetail0->RegAddr);
		TRACE(_T("RegCurVal 0x%02x\n"), pRegTable->RegInfo.at(pBitDetail0->RegAddr).RegCurVal.at(0));

		auto iter = pCtrlDetail->BitMapping.begin();
		while (iter != pCtrlDetail->BitMapping.end())
		{
			for (size_t i = 0; i < pBitDetailMap->at(iter->second).DefaultVal.size(); i++)
			{
				DefaultVal += LSHIFT(pBitDetailMap->at(iter->second).DefaultVal.at(i) , pBitDetailMap->at(iter->second).BitShift.at(i));
				CtrlRange.first += LSHIFT(pBitDetailMap->at(iter->second).BitRange.at(i).first , pBitDetailMap->at(iter->second).BitShift.at(i));
				CtrlRange.second += LSHIFT(pBitDetailMap->at(iter->second).BitRange.at(i).second , pBitDetailMap->at(iter->second).BitShift.at(i));
			}

			if (pBitDetail0->bSign)
			{
				CtrlRange.second = CtrlRange.second >> 1;
				CtrlRange.first = ~CtrlRange.second;
			}
			++iter;
		}
	}
	else if (pCtrlDetail->RegMapping.size() > 0) {		
		for (uint8_t i = 0; i < pRegTable->RegInfo.at(pCtrlDetail->RegMapping.at(0)).RegBits; i++)
			pRegCurVal.push_back(&pRegTable->RegInfo.at(pCtrlDetail->RegMapping.at(0)).RegCurVal.at(i));
	}

}

uint8_t CMyControlGroup::CtrlWrite()
{
	uint8_t result;
	vector<uint8_t> u8Temp;
	if (pCtrlDetail->CtrlFunc == CTRLFUNC_SWRST)
	{
		if (pCtrlDetail->bActive)
			u8Temp.push_back(pBitDetail0->BitMask.at(0));
		else
			u8Temp.push_back(~pBitDetail0->BitMask.at(0));
	}
	else
		u8Temp.push_back((*pRegCurVal.at(0) & ~pBitDetail0->BitMask.at(0)) | LSHIFT(pBitDetail0->DefaultVal.at(0), pBitDetail0->BitShift.at(0)));

	result = I2CWrite(0, DevID, pBitDetail0->RegAddr, u8Temp.data(), 1);
	if (result == STATUS_OK)
	{
		Sleep(pCtrlDetail->I2CWriteDelayMs);
		result = I2CRead(0, DevID, pBitDetail0->RegAddr, pRegCurVal.at(0), 1, 0, 0, 1000);
	}

	return result;
}


uint8_t CMyControlGroup::CtrlWrite(uint8_t value, bool bUsedRegMap /*= false*/)
{
	uint8_t result;
	vector<uint8_t> u8Temp;
	uint8_t addr = 0x00;


	if (bUsedRegMap) {
		addr = pCtrlDetail->RegMapping.at(0);
		u8Temp.push_back(value);
	}
	else {
		addr = pBitDetail0->RegAddr;
		u8Temp.push_back((*pRegCurVal.at(0) & ~pBitDetail0->BitMask.at(0)) | LSHIFT(value, pBitDetail0->BitShift.at(0)));
	}

	result = I2CWrite(0, DevID, addr, u8Temp.data(), 1);
	if (result == STATUS_OK)
	{
		Sleep(pCtrlDetail->I2CWriteDelayMs);
		result = I2CRead(0, DevID, addr, pRegCurVal.at(0), 1, 0, 0, 1000);
	}

	return result;
}

uint8_t CMyControlGroup::CtrlWrite(uint32_t value)
{
	uint8_t result;
	uint8_t u8temp;
	vector<uint8_t> temp;

	pRegInfo = &pRegInfoMap->at(pBitDetail0->RegAddr);
	if (pRegInfo->RegBits > 1)
	{
		for (int i = 0; i < pRegInfo->RegBits; i++)
		{
			u8temp = RSHIFT(value, pBitDetail0->BitShift.at(i)) & pBitDetail0->BitMask.at(i);
			temp.push_back(u8temp);
		}
	}
	else
		return CtrlWrite((uint8_t)value);

	result = I2CWrite(0, DevID, pBitDetail0->RegAddr, temp.data(), (uint8_t)temp.size());
	if (result == STATUS_OK)
	{
		Sleep(pCtrlDetail->I2CWriteDelayMs);
		result = I2CRead(0, DevID, pBitDetail0->RegAddr, temp.data(), (uint16_t)temp.size(), 0, 0, 1000);
	}

	for (uint8_t i = 0; i < temp.size(); i++)
	{
		pRegInfo->RegCurVal.at(i) = temp[i];
	}

	return result;
}

void CMyControlGroup::SetName(CString name)
{
	if (mGroup.GetSafeHwnd() != NULL)
		mGroup.SetWindowTextW(name);
}


void CMyControlGroup::OnOK()
{
}


void CMyControlGroup::OnCancel()
{
}


BOOL CMyControlGroup::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam) {
		case VK_ESCAPE:
		case VK_RETURN:
			return false;
		}
	}

	if (mToolTip != NULL)
		mToolTip->RelayEvent(pMsg);

	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CMyControlGroup::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if(!pCtrlDetail->CtrlName.first.IsEmpty())
		mToolTip->AddTool(this, pCtrlDetail->CtrlName.first);
	else if(!pCtrlDetail->CtrlName.second.IsEmpty())
		mToolTip->AddTool(this, pCtrlDetail->CtrlName.second);
	else if (pBitDetail0 != NULL)
	{
		if (pBitDetail0->csDetailInfo.IsEmpty())
			mToolTip->AddTool(this, pBitDetail0->csDesc);
		else
			mToolTip->AddTool(this, pBitDetail0->csDetailInfo);
	}

	return TRUE;
}


void CMyControlGroup::SetEditText(uint32_t value)
{
	CString csTemp;

	csTemp.Format(_T("%d"), value);
	mEdit.SetWindowTextW(csTemp);
	switch (pRegInfoMap->at(pBitDetail0->RegAddr).RegBits)
	{
		case 1:	csTemp.Format(_T("0x%02X"), value); break;
		case 2:	csTemp.Format(_T("0x%04X"), value); break;
		case 4: csTemp.Format(_T("0x%08X"), value); break;
		default: csTemp.Format(_T("0x%X"), value); break;
	}
	mValueHex.SetWindowTextW(csTemp);
}


void CMyControlGroup::SetStaticDecHexText(uint32_t value)
{
	CString csTemp;

	csTemp.Format(_T("%d"), value);
	mValueDec.SetWindowTextW(csTemp);
	csTemp.Format(_T("0x%04X"), value);
	mValueHex.SetWindowTextW(csTemp);
}


BOOL CMyControlGroup::DestroyWindow()
{
	return CDialogEx::DestroyWindow();
}


afx_msg LRESULT CMyControlGroup::OnMessageChangeAvgNum(WPARAM wParam, LPARAM lParam)
{
	AvgNum = wParam;
	return 0;
}

uint8_t CMyControlGroup::GetBitValue()
{
	uint8_t value = 0;

	//TRACE(_T("pBitDetail0->RegAddr 0x%02x\n"), pBitDetail0->RegAddr);

	pRegInfo = &pRegInfoMap->at(pBitDetail0->RegAddr);

	value = RSHIFT((pRegInfo->RegCurVal.at(0) & pBitDetail0->BitMask.at(0)), pBitDetail0->BitShift.at(0));

	return value;
}

uint8_t CMyControlGroup::GetBitValue(CString BitName)
{
	uint8_t value = 0;

	pBitDetail = &pBitDetailMap->at(BitName);
	pRegInfo = &pRegInfoMap->at(pBitDetail->RegAddr);

	value = RSHIFT((pRegInfo->RegCurVal.at(0) & pBitDetail->BitMask.at(0)), pBitDetail->BitShift.at(0));

	return value;
}


int32_t CMyControlGroup::GetRegValue(uint8_t RegAddr, CString BitName)
{
	int32_t value = 0;
	int32_t mask = 0xFFFFFFFF;
	pRegInfo = &pRegInfoMap->at(RegAddr);

	if (BitName.IsEmpty())
		BitName = pRegInfoMap->at(RegAddr).BitName.at(0);

	pBitDetail = &pBitDetailMap->at(BitName);
	for (int i = 0; i < pRegInfo->RegBits; i++)
	{
		value += LSHIFT((pRegInfo->RegCurVal.at(i) & pBitDetail->BitMask.at(i)), pBitDetail->BitShift.at(i));
		mask &= ~ LSHIFT(pBitDetail->BitMask.at(i), pBitDetail->BitShift.at(i));
	}

	if (pBitDetail->bSign)
	{
		if (value > CtrlRange.second)
			value |= mask;
	}

	if (pRegInfo->RegScale != 1.0)
	{
		value = (int32_t)((double)value * pRegInfo->RegScale);
		if (value > CtrlRange.second)
			value = CtrlRange.second;
	}

	return value;
}

int32_t CMyControlGroup::GetRegValue(CString BitName)
{
	return GetRegValue(pBitDetailMap->at(BitName).RegAddr, BitName);
}

int32_t CMyControlGroup::GetRegValue()
{
	return GetRegValue(pBitDetail0->RegAddr, pCtrlDetail->BitMapping.at(0));
}

int32_t CMyControlGroup::GetLux()
{
	int32_t value = 0;
	map<uint8_t, uint32_t> count;
	map<uint8_t, double> dCount;
	double ratio = 0.0;

	if (pLuxCalculate->DataRegMapping.size() == 0)
		return 0;

	auto iter_DataRegMap = pLuxCalculate->DataRegMapping.begin();
	while (iter_DataRegMap != pLuxCalculate->DataRegMapping.end())
	{
		count[iter_DataRegMap->first] = GetRegValue(iter_DataRegMap->second);
		++iter_DataRegMap;
	}

	value = 0;

	auto iter_Count2Lux = pLuxCalculate->Count2LuxMapping.end();

	switch (pLuxCalculate->LuxFunc) {
	case OneCH:
		dCount[0] = count.at(0);
		value = (int32_t)(dCount.at(0) * pLuxCalculate->Count2LuxMapping.begin()->second.first);

		break;

	case TwoCH:
		dCount[0] = count.at(0);
		dCount[1] = count.at(1);

		count.at(0) = CtrlRange.second;
		ratio = dCount.at(1) / dCount.at(0);
		while (iter_Count2Lux != pLuxCalculate->Count2LuxMapping.begin())
		{
			--iter_Count2Lux;

			if (ratio >= iter_Count2Lux->first)
			{
				value = (int32_t)(dCount.at(0) * iter_Count2Lux->second.first + dCount.at(1) * iter_Count2Lux->second.second);
				break;
			}
		}
		break;
	case TwoCH_New:
		dCount[0] = count.at(0);
		dCount[1] = count.at(1);

		if (pLuxCalculate->DataRatioBitMapping.size() != 0)
		{
			auto iter_DataRatioBitMap = pLuxCalculate->DataRatioBitMapping.begin();
			while (iter_DataRatioBitMap != pLuxCalculate->DataRatioBitMapping.end())
			{
				auto iter_DataRatioBitMap2 = iter_DataRatioBitMap->second.begin();
				while (iter_DataRatioBitMap2 != iter_DataRatioBitMap->second.end())
				{
					dCount.at(iter_DataRatioBitMap->first) = dCount.at(iter_DataRatioBitMap->first)
						* pLuxCalculate->DataCountRatioMapping.at(iter_DataRatioBitMap->first).at(make_pair(iter_DataRatioBitMap2->first,GetBitValue(iter_DataRatioBitMap2->second)));
					++iter_DataRatioBitMap2;
				}
				++iter_DataRatioBitMap;
			}
		}

		count.at(0) = CtrlRange.second;
		if (dCount.at(1) != 0)
			ratio = dCount.at(1) / dCount.at(0);
		else
			ratio = 0;

		value = (int32_t)((ratio * pLuxCalculate->Lux_Coef_a + pLuxCalculate->Lux_Coef_b) * (dCount.at(0) + dCount.at(1) * pLuxCalculate->Lux_Coef_c));
		if (value < 0)
			value = 0;

		//pDieDetail->LuxValue = value;

		//return value;
		break;
	case FourCH_Color:
		dCount[0] = count.at(0);
		dCount[1] = count.at(1);
		dCount[2] = count.at(2);
		dCount[3] = count.at(3);

		ratio = dCount.at(3) / dCount.at(1);
		//! Y (Lux) = (α×𝐑𝐞𝐝)+(β×𝐆𝐫𝐞𝐞𝐧)+(γ×𝐁𝐥𝐮𝐞)+(δ×𝐂𝐥𝐞𝐚𝐫)+ε
		auto iter = pCCTCalculate->RegressCoefMapping.begin();
		while (iter != pCCTCalculate->RegressCoefMapping.end())
		{
			if (ratio >= iter->first)
			{
				auto iter2 = iter->second.at(1).begin();	//Take Y
				while (iter2 != iter->second.at(1).end())
				{
					if (iter2->first == 4)
						value += (int32_t)iter2->second;
					else
						value += (int32_t)(dCount.at(iter2->first) * iter2->second);
					++iter2;
				}
				break;
			}
			++iter;
		}
		break;
	}

	//! 將數值還原為1倍。
	dCount[0] = value;
	auto iter_RatioBitMap = pLuxCalculate->RatioBitMapping.begin();
	while (iter_RatioBitMap != pLuxCalculate->RatioBitMapping.end())
	{
		dCount.at(0) = dCount.at(0) * pLuxCalculate->CountRatioMapping.at(iter_RatioBitMap->first).at(GetBitValue(iter_RatioBitMap->second));
		++iter_RatioBitMap;
	}

	value = (int32_t)dCount.at(0);

	if (value < 0)
		value = 0;
		
	pDieDetail->LuxValue = value;

	return value;
}


int32_t CMyControlGroup::GetCCT()
{
	int32_t value = 0;

	map<uint8_t, double> dCount;
//	map<uint8_t, uint8_t> SelRadio;
	map<uint8_t, double> CCT_XYZ, CCT_xyn;
	double ratio = 0.0;

	if (pCCTCalculate->DataRegMapping.size() == 0)
		return 0;

	auto iter_DataRegMap = pCCTCalculate->DataRegMapping.begin();
	while (iter_DataRegMap != pCCTCalculate->DataRegMapping.end())
	{
		dCount[iter_DataRegMap->first] = GetRegValue(iter_DataRegMap->second);
		++iter_DataRegMap;
	}

	/**
	 * 𝐗,𝐘,𝐙=𝛂×𝐑+𝛃×𝐆+𝛄×𝐁+𝛅×𝐂+ ε
	 */
	auto iter = pCCTCalculate->RegressCoefMapping.begin();
	while (iter != pCCTCalculate->RegressCoefMapping.end())
	{
		if (ratio >= iter->first)
		{
			auto iter2 = iter->second.begin();
			while (iter2 != iter->second.end())
			{
				CCT_XYZ[iter2->first] = 0;
				auto iter3 = iter2->second.begin();
				while (iter3 != iter2->second.end())
				{
					if (iter3->first == 4)
						CCT_XYZ.at(iter2->first) += iter3->second;
					else
						CCT_XYZ.at(iter2->first) += dCount.at(iter3->first) * iter3->second;
					++iter3;
				}
				++iter2;
			}
			break;
		}
		++iter;
	}
	
	const double McCamy[6] = { -449.0, 3525.0, -6823.3, 5520.33, 0.3320, 0.1858 };	//a, b, c, d, xe, ye

	dCount.at(0) = CCT_XYZ.at(0) + CCT_XYZ.at(1) + CCT_XYZ.at(2);	//< X + Y + Z
	if (dCount.at(0) != 0)
	{
		CCT_xyn[0] = CCT_XYZ.at(0) / dCount.at(0);								//< x = X / (X + Y + Z)
		CCT_xyn[1] = CCT_XYZ.at(1) / dCount.at(0);								//< y = Y / (X + Y + Z)
		CCT_xyn[2] = (CCT_xyn.at(0) - McCamy[4]) / (CCT_xyn.at(1) - McCamy[5]);	//< (x-xe)/(y-ye)

		//! CCT = an3+bn2+cn+d
		dCount.at(0)  = McCamy[0] * pow(CCT_xyn.at(2), 3);	//an3
		dCount.at(0) += McCamy[1] * pow(CCT_xyn.at(2), 2);	//bn2
		dCount.at(0) += McCamy[2] * CCT_xyn.at(2);			//cn
		dCount.at(0) += McCamy[3];							//d
	}

	value = (int32_t)dCount.at(0);

	if (value < 0)
		value = 0;

	pDieDetail->CCTValue = value;

	return value;
}

double CMyControlGroup::GetAxis()
{
	int32_t iValue = 0;
	double dValue = 0;

	iValue = GetRegValue();

	dValue = (double)iValue * CtrlScale;

	return dValue;
}
