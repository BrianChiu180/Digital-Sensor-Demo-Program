// ProgressBar.cpp : implementation file
//

#include "stdafx.h"
#include "ProgressBar.h"
#include "afxdialogex.h"


// CProgressBar dialog

IMPLEMENT_DYNAMIC(CProgressBar, CMyControlGroup)

CProgressBar::CProgressBar(CWnd* pParent /*=NULL*/)
	: CMyControlGroup(CProgressBar::IDD, pParent), AvgSum(0), LastVal(0), bChangeRange(FALSE) {

}

CProgressBar::~CProgressBar() {
}

void CProgressBar::DoDataExchange(CDataExchange* pDX) {
	CMyControlGroup::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, mValue);
	DDX_Control(pDX, IDC_PROGRESS1, mProgress);
	DDX_Control(pDX, IDC_STATIC2, mName);
}


BEGIN_MESSAGE_MAP(CProgressBar, CMyControlGroup)
	ON_MESSAGE(WM_MESSAGE_UPDATEUI, &CProgressBar::OnMessageUpdateui)
	ON_MESSAGE(WM_MESSAGE_CHANGE_RANGE, &CProgressBar::OnMessageChangeRange)
END_MESSAGE_MAP()


// CProgressBar message handlers


BOOL CProgressBar::OnInitDialog() {
	CMyControlGroup::OnInitDialog();

	LOGFONT lFont;

	GetFont()->GetLogFont(&lFont);
	//memset(&lFont, 0, sizeof(LOGFONT));
	lstrcpy(lFont.lfFaceName, _T("Calibri"));
	lFont.lfHeight -= 2;
	//lFont.lfItalic = 0;
	lFont.lfWeight += 200;
	mFontLabel.CreateFontIndirect(&lFont);
	mName.SetFont(&mFontLabel);
	mValue.SetFont(&mFontLabel);

	if (pCtrlDetail->CtrlName.first == _T(""))
		SetName(pCtrlDetail->BitMapping.at(0));
	else
		SetName(pCtrlDetail->CtrlName.first);

	mProgress.SetRange32(CtrlRange.first, CtrlRange.second);
	mProgress.SetBarColor(CtrlColor.first);

	AvgSum = 0;
	AvgNum = 1;
	SetValue(0);

	bChangeRange = false;

	return TRUE;
}


void CProgressBar::SetValue(int value) {
	CString cTemp;
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
			SetRange(CtrlRange.first, CtrlRange.second);
			bChangeRange = false;
		}

		mProgress.SetPos(iValue);
		if (iValue < 0)
			mProgress.SetBarColor(CtrlColor.second);
		else
			mProgress.SetBarColor(CtrlColor.first);

		cTemp.Format(_T("%d"), iValue);
		mValue.SetWindowTextW(cTemp);

		Invalidate();
		UpdateData(0);

		LastVal = iValue;
	}
}


void CProgressBar::SetName(CString name) {
	mName.SetWindowTextW(name);
}

void CProgressBar::SetRange(int min, int max) {
	mProgress.SetRange32(min, max);
}

afx_msg LRESULT CProgressBar::OnMessageUpdateui(WPARAM wParam, LPARAM lParam) {
	int32_t value = 0;

	switch (pCtrlDetail->CtrlFunc)
	{
	case CTRLFUNC_NORMAL:
		value = GetRegValue();
		break;
	case CTRLFUNC_LUX:
		value = GetLux();
		break;
	case CTRLFUNC_CCT:
		value = GetCCT();
		break;
	}

	SetValue(value);

	return 0;
}


afx_msg LRESULT CProgressBar::OnMessageChangeRange(WPARAM wParam, LPARAM lParam) {
	CCtrlDetail* CtrlDetail2 = (CCtrlDetail*)lParam;

	if (pCtrlDetail->CtrlFunc == CTRLFUNC_LUX)
		return 0;

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


BOOL CProgressBar::DestroyWindow()
{
	mFontLabel.DeleteObject();

	return CMyControlGroup::DestroyWindow();
}
