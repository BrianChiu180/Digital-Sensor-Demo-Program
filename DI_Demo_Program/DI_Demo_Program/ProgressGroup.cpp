// ProgressGroup.cpp : implementation file
//

#include "stdafx.h"
#include "ProgressGroup.h"
#include "afxdialogex.h"


// CProgressGroup dialog

IMPLEMENT_DYNAMIC(CProgressGroup, CMyControlGroup)

CProgressGroup::CProgressGroup(CWnd* pParent /*=NULL*/)
	: CMyControlGroup(CProgressGroup::IDD, pParent), AvgSum(0), LastVal(0), SelData(0), bChangeRange(FALSE) {

}

CProgressGroup::~CProgressGroup() {
}

void CProgressGroup::DoDataExchange(CDataExchange* pDX) {
	CMyControlGroup::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUP1, mGroup);
	DDX_Control(pDX, IDC_PROGRESS1, mProgress);
	DDX_Control(pDX, IDC_STATIC1, mValueDec);
	DDX_Control(pDX, IDC_STATIC2, mValueHex);
}


BEGIN_MESSAGE_MAP(CProgressGroup, CMyControlGroup)
	ON_MESSAGE(WM_MESSAGE_UPDATEUI, &CProgressGroup::OnMessageUpdateui)
	ON_MESSAGE(WM_MESSAGE_CHANGE_SEL_DATA, &CProgressGroup::OnMessageChangeSelData)
	ON_MESSAGE(WM_MESSAGE_CHANGE_RANGE, &CProgressGroup::OnMessageChangeRange)
END_MESSAGE_MAP()

void CProgressGroup::SetValue(int value) {
	CString csTemp;
	int iValue;

	dequeVal.push_back(value);
	while (dequeVal.size() > AvgNum)
	{
		AvgSum -= dequeVal.front();
		dequeVal.pop_front();
	}

	AvgSum += dequeVal.back();

	if (AvgSum == 0)
		iValue = 0;
	else
		iValue = (int)(AvgSum / dequeVal.size());

	if (LastVal != iValue)
	{
		if (bChangeRange)
		{
			mProgress.SetRange32(CtrlRange.first, CtrlRange.second);
			bChangeRange = false;
		}
		mProgress.SetPos(iValue);

		if (iValue < 0)
			mProgress.SetBarColor(CtrlColor.second);
		else
			mProgress.SetBarColor(CtrlColor.first);

		SetStaticDecHexText(iValue);

		Invalidate();
		UpdateData(0);

		LastVal = iValue;
	}
}

BOOL CProgressGroup::OnInitDialog() {
	CMyControlGroup::OnInitDialog();

	if (pCtrlDetail->CtrlName.first.IsEmpty())
		SetName(pCtrlDetail->BitMapping.at(0));
	else
		SetName(pCtrlDetail->CtrlName.first);

	mProgress.SetBarColor(CtrlColor.first);
	mProgress.SetRange32(CtrlRange.first, CtrlRange.second);
	AvgSum = 0;
	AvgNum = 1;
	SetValue(0);
	bChangeRange = false;

	return TRUE;
}

afx_msg LRESULT CProgressGroup::OnMessageUpdateui(WPARAM wParam, LPARAM lParam) {
	int32_t value = 0;

	value = GetRegValue();

	if (value > CtrlRange.second)
		value = CtrlRange.second;

	SetValue(value);

	return 0;
}


afx_msg LRESULT CProgressGroup::OnMessageChangeSelData(WPARAM wParam, LPARAM lParam) {
	if (pCtrlDetail->CtrlFunc == CTRLFUNC_SELDATA)
	{
		map<uint8_t, uint8_t>::iterator iter;
		iter = pCtrlDetail->RegMapping.begin();
		while (iter != pCtrlDetail->RegMapping.end())
		{
			if (iter->second == wParam)
			{
				SetName(pBitDetailMap->at(pRegInfoMap->at(wParam).BitName.at(0)).csDesc);
				pCtrlDetail->BitMapping.at(0) = pRegInfoMap->at(wParam).BitName.at(0);
				pBitDetail0 = &pBitDetailMap->at(pCtrlDetail->BitMapping.at(0));
				return 0;
			}
			++iter;
		}
	}
	return 0;
}


afx_msg LRESULT CProgressGroup::OnMessageChangeRange(WPARAM wParam, LPARAM lParam) {
	CCtrlDetail* CtrlDetail2 = (CCtrlDetail*)lParam;
	map<uint8_t, uint8_t>::iterator iter;
	iter = CtrlDetail2->RegMapping.begin();
	while (iter != CtrlDetail2->RegMapping.end())
	{
		if (pBitDetail0->RegAddr == iter->second)
		{
			pair<int, int> newRange;
			if (CtrlDetail2->RangeMapping.count(wParam) == 0)
			{
				newRange = CtrlDetail2->RangeMapping.rbegin()->second;
			}
			else
			{
				newRange = CtrlDetail2->RangeMapping.at(wParam);
			}

			if (CtrlRange != newRange)
			{
				CtrlRange = newRange;

				bChangeRange = true;
			}
			return 0;
		}
		++iter;
	}
	return 0;
}
