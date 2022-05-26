// TextGroup.cpp : implementation file
//

#include "stdafx.h"
#include "TextGroup.h"
#include "afxdialogex.h"


// CTextGroup dialog

IMPLEMENT_DYNAMIC(CTextGroup, CMyControlGroup)

CTextGroup::CTextGroup(CWnd* pParent /*=NULL*/)
	: CMyControlGroup(CTextGroup::IDD, pParent), AvgSum(0), LastVal(0), dLastVal(0.0)
{

}

CTextGroup::~CTextGroup()
{
}

void CTextGroup::DoDataExchange(CDataExchange* pDX)
{
	CMyControlGroup::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUP1, mGroup);
	DDX_Control(pDX, IDC_STATIC1, mText);
}


BEGIN_MESSAGE_MAP(CTextGroup, CMyControlGroup)
	ON_MESSAGE(WM_MESSAGE_UPDATEUI, &CTextGroup::OnMessageUpdateui)
	ON_MESSAGE(WM_MESSAGE_UPDATE_INFO, &CTextGroup::OnMessageUpdateInfo)
	ON_MESSAGE(WM_MESSAGE_CHANGE_SCALE, &CTextGroup::OnMessageChangeScale)
END_MESSAGE_MAP()

void CTextGroup::SetName(CString group, CString text)
{
	mGroup.SetWindowTextW(group);
	mText.SetWindowTextW(text);
}


BOOL CTextGroup::OnInitDialog()
{
	CMyControlGroup::OnInitDialog();

	LOGFONT lFont;

	GetFont()->GetLogFont(&lFont);
	lstrcpy(lFont.lfFaceName, _T("Calibri"));

	AvgSum = 0;
	AvgNum = 1;
	LastVal = -1;

	switch (pCtrlDetail->CtrlFunc)
	{
	case CTRLFUNC_LUX:
	case CTRLFUNC_CCT:
		SetName(pCtrlDetail->CtrlName.first, _T("0"));
		SetValue(0);
		lFont.lfHeight -= 8;
		break;
	case CTRLFUNC_AXIS:
		SetName(pCtrlDetail->CtrlName.first, _T("0"));
		SetValue(0);
		lFont.lfHeight -= 8;
		break;
	default:
		SetName(pCtrlDetail->CtrlName.first, pCtrlDetail->CtrlName.second);
		lFont.lfHeight -= 5;
		break;
	}

	lFont.lfWeight += 200;
	mFontLabel.CreateFontIndirect(&lFont);
	mText.SetFont(&mFontLabel);

	return TRUE;
}

void CTextGroup::SetValue(int value)
{
	CString csTemp;
	int iValue;

	idequeVal.push_back(value);
	while (idequeVal.size() > AvgNum)
	{
		AvgSum -= idequeVal.front();
		idequeVal.pop_front();
	}

	AvgSum += idequeVal.back();

	if (AvgSum == 0)
		iValue = 0;
	else
		iValue = (int)(AvgSum / idequeVal.size());

	if (LastVal != iValue)
	{
		csTemp.Format(_T("%d"), iValue);
		mText.SetWindowTextW(csTemp);

		Invalidate();
		UpdateData(0);

		LastVal = iValue;
	}
}

void CTextGroup::SetValue(double value)
{
	CString csTemp;
	double dValue;

	ddequeVal.push_back(value);
	while (ddequeVal.size() > AvgNum)
	{
		AvgSum -= ddequeVal.front();
		ddequeVal.pop_front();
	}

	AvgSum += ddequeVal.back();

	if (AvgSum == 0)
		dValue = 0.0;
	else
		dValue = (double)(AvgSum / ddequeVal.size());

	if (dLastVal != dValue)
	{
		csTemp.Format(_T("%2.3f g"), dValue);
		mText.SetWindowTextW(csTemp);

		Invalidate();
		UpdateData(0);

		dLastVal = dValue;
	}
}

afx_msg LRESULT CTextGroup::OnMessageUpdateui(WPARAM wParam, LPARAM lParam)
{
	switch (pCtrlDetail->CtrlFunc)
	{
	case CTRLFUNC_NORMAL:
		SetValue(GetRegValue());
		break;
	case CTRLFUNC_LUX:
		SetValue(GetLux());
		break;
	case CTRLFUNC_CCT:
		SetValue(GetCCT());
		break;
	case CTRLFUNC_AXIS:
		SetValue(GetAxis());
	default: return 0;
	}

	return 0;

}

BOOL CTextGroup::DestroyWindow()
{
	mFontLabel.DeleteObject();

	return CMyControlGroup::DestroyWindow();
}


afx_msg LRESULT CTextGroup::OnMessageUpdateInfo(WPARAM wParam, LPARAM lParam)
{
	CString csTemp = _T("Not Detect");
	vector<char> chBuff(200, 0);
	uint16_t SensorVersion = (uint16_t)(wParam & 0xFFFF);
	uint16_t DieVersion = (uint16_t)((wParam & 0xFFFF0000) >> 16);

	switch (pCtrlDetail->CtrlFunc)
	{
	case CTRLFUNC_SHOW_BRIDGE_VERSION:
		if (INFOgetVersion(0, (uint8_t*)&chBuff[0]) == STATUS_OK)
		{
			csTemp = &chBuff[0];
			csTemp.Delete(0, 8);
			csTemp.Delete(csTemp.Find(_T(" ")), csTemp.GetLength() - csTemp.Find(_T(" ")));
		}
		break;
	case CTRLFUNC_SHOW_DATASHEET:
		if (SensorVersion > 0)
		{
			if (SensorVersion % 100 == 0)
				csTemp.Format(_T("V%01d.%02d"), SensorVersion / 10000, (SensorVersion % 10000) / 100);
			else
				csTemp.Format(_T("V%01d.%04d"), SensorVersion / 10000, (SensorVersion % 10000) / 100);
		}
		break;
	case CTRLFUNC_SHOW_DIEVERSION:
		if (DieVersion > 0)
		{
			if (DieVersion % 100 == 0)
				csTemp.Format(_T("V%01d.%02d"), DieVersion / 10000, (DieVersion % 10000) / 100);
			else
				csTemp.Format(_T("V%01d.%02d%X"), DieVersion / 10000, (DieVersion % 10000) / 100, (DieVersion % 100));
		}
		break;
	default: return 0;
	}

	SetName(pCtrlDetail->CtrlName.first, csTemp);
	return 0;
}

afx_msg LRESULT CTextGroup::OnMessageChangeScale(WPARAM wParam, LPARAM lParam)
{
	CCtrlDetail* pCtrlDetail2 = (CCtrlDetail*)lParam;

	CtrlScale = pCtrlDetail2->ValueScaleMapping[wParam];

	return 0;
}