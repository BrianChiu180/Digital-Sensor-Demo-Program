// SliderGroup.cpp : implementation file
//

#include "stdafx.h"
#include "SliderGroup.h"
#include "afxdialogex.h"


// CSliderGroup dialog

IMPLEMENT_DYNAMIC(CSliderGroup, CMyControlGroup)

CSliderGroup::CSliderGroup(CWnd* pParent /*=NULL*/)
	: CMyControlGroup(CSliderGroup::IDD, pParent), LastVal(0)
{

}

CSliderGroup::~CSliderGroup()
{
}

void CSliderGroup::DoDataExchange(CDataExchange* pDX)
{
	CMyControlGroup::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUP1, mGroup);
	DDX_Control(pDX, IDC_SLIDER1, mSlider);
	DDX_Control(pDX, IDC_EDIT1, mEdit);
	DDX_Control(pDX, IDC_STATIC1, mValueHex);
}


BEGIN_MESSAGE_MAP(CSliderGroup, CMyControlGroup)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CSliderGroup::OnCustomdrawSlider1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, &CSliderGroup::OnReleasedcaptureSlider1)
	ON_MESSAGE(WM_MESSAGE_UPDATEUI, &CSliderGroup::OnMessageUpdateui)
	ON_MESSAGE(WM_MESSAGE_CHANGE_RANGE, &CSliderGroup::OnMessageChangeRange)
END_MESSAGE_MAP()

void CSliderGroup::OnCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	int iPOS = mSlider.GetPos();
	static int iPOS_last = 0;

	if (iPOS_last != iPOS)
	{
		SetEditText(iPOS);
		iPOS_last = iPOS;
	}

	*pResult = 0;
}

void CSliderGroup::SetValue(int value)
{
	SetEditText(value);
	mSlider.SetPos(value);

	Invalidate();
	UpdateData(0);

	CtrlWrite((uint32_t)value);
	LastVal = value;
}

BOOL CSliderGroup::OnInitDialog()
{
	CMyControlGroup::OnInitDialog();

	mEdit.SetWindowTextW(_T("0"));

	if (pCtrlDetail->CtrlName.first == _T(""))
		SetName(pCtrlDetail->BitMapping.at(0));
	else
		SetName(pCtrlDetail->CtrlName.first);

	mSlider.SetRange(CtrlRange.first, CtrlRange.second, true);
	mSlider.SetLineSize(CtrlRange.second / 20);
	mSlider.SetPageSize(CtrlRange.second / 20);
	SetEditText(DefaultVal);
	mSlider.SetPos(DefaultVal);

	LastVal = DefaultVal;
	return TRUE;
}


BOOL CSliderGroup::PreTranslateMessage(MSG* pMsg)
{
	int value;
	CString csTemp;

	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam) {
		case VK_ESCAPE:
			SetEditText(LastVal);
			break;
		case VK_RETURN:
			mEdit.GetWindowTextW(csTemp);
			value = wcstoul(csTemp, NULL, 10);
			if (value < CtrlRange.first || value > CtrlRange.second)
			{
				csTemp.Format(_T("Range is %d ~ %d."), CtrlRange.first, CtrlRange.second);
				MessageBoxW(csTemp, _T("Out of range!"), MB_OK);
				SetEditText(LastVal);
				break;
			}

			SetValue(value);
			break;
		case VK_UP:
			if (pMsg->hwnd == mEdit.m_hWnd)
			{
				mEdit.GetWindowTextW(csTemp);
				value = wcstol(csTemp, NULL, 10);

				if (value < CtrlRange.second)
					value++;

				SetValue(value);
			}
			break;
		case VK_DOWN:
			if (pMsg->hwnd == mEdit.m_hWnd)
			{
				mEdit.GetWindowTextW(csTemp);
				value = wcstol(csTemp, NULL, 10);

				if (value > CtrlRange.first)
					value--;

				SetValue(value);
			}
			break;
		}
	}
	else if (pMsg->message == WM_MOUSEWHEEL)
	{
		if (pMsg->hwnd == mEdit.m_hWnd)
		{
			short zDelta = GET_WHEEL_DELTA_WPARAM(pMsg->wParam);

			mEdit.GetWindowTextW(csTemp);
			value = wcstol(csTemp, NULL, 10);

			if (zDelta > 0)
			{
				if (value < CtrlRange.second)
					value++;
			}
			else
			{
				if (value > CtrlRange.first)
					value--;
			}

			SetValue(value);
		}
	}

	return CMyControlGroup::PreTranslateMessage(pMsg);
}


void CSliderGroup::OnReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	int iPOS = mSlider.GetPos();

	if (iPOS != LastVal)
		SetValue(iPOS);

	*pResult = 0;
}


afx_msg LRESULT CSliderGroup::OnMessageUpdateui(WPARAM wParam, LPARAM lParam)
{
	int32_t value = 0;

	value = GetRegValue();

	if (value != LastVal)
	{
		SetEditText(value);
		mSlider.SetPos(value);
		LastVal = value;
	}

	return 0;
}


afx_msg LRESULT CSliderGroup::OnMessageChangeRange(WPARAM wParam, LPARAM lParam)
{
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
				int value = mSlider.GetPos();

				if (value > 0)
				{
					if (value == CtrlRange.second)
						value = newRange.second;
					else
					{
						value = (int)(value * ((float)(newRange.second + 1) / (CtrlRange.second + 1)));
					}

					if (value > newRange.second)
						value = newRange.second;
				}

				mSlider.SetRange(newRange.first, newRange.second);
				CtrlRange = newRange;
				mSlider.SetLineSize(CtrlRange.second / 20);
				mSlider.SetPageSize(CtrlRange.second / 20);
				SetValue(value);
			}
		}
		++iter;
	}
	return 0;
}
