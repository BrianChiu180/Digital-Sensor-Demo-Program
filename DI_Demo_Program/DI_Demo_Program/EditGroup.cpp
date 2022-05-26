// EditGroup.cpp : implementation file
//

#include "stdafx.h"
#include "EditGroup.h"
#include "afxdialogex.h"


// CEditGroup dialog

IMPLEMENT_DYNAMIC(CEditGroup, CMyControlGroup)

CEditGroup::CEditGroup(CWnd* pParent /*=NULL*/)
	: CMyControlGroup(CEditGroup::IDD, pParent), LastVal(0)
{

}

CEditGroup::~CEditGroup()
{
}

void CEditGroup::DoDataExchange(CDataExchange* pDX)
{
	CMyControlGroup::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUP1, mGroup);
	DDX_Control(pDX, IDC_EDIT1, mEdit);
	DDX_Control(pDX, IDC_STATIC1, mValueHex);
}


BEGIN_MESSAGE_MAP(CEditGroup, CMyControlGroup)
	ON_MESSAGE(WM_MESSAGE_UPDATEUI, &CEditGroup::OnMessageUpdateui)
	ON_MESSAGE(WM_MESSAGE_CALIBRATION, &CEditGroup::OnMessageCalibration)
END_MESSAGE_MAP()

BOOL CEditGroup::OnInitDialog()
{
	CMyControlGroup::OnInitDialog();

	if (pCtrlDetail->CtrlName.first.IsEmpty())
	{
		if (pBitDetail0->csDesc.IsEmpty())
			SetName(pCtrlDetail->BitMapping.at(0));
		else
			SetName(pBitDetail0->csDesc);
	}
	else
		SetName(pCtrlDetail->CtrlName.first);

	SetEditText(DefaultVal);
	LastVal = DefaultVal;

	if (pCtrlDetail->CtrlFunc & CTRLFUNC_CHANGE_RANGE)
		AfxGetMainWnd()->PostMessage(WM_MESSAGE_CHANGE_RANGE, DefaultVal, (WPARAM)pCtrlDetail);

	return TRUE;
}


void CEditGroup::SetValue(uint32_t value)
{
	SetEditText(value);
	CtrlWrite(value);
	LastVal = value;

	Invalidate();
	UpdateData(0);

	if (pCtrlDetail->CtrlFunc & CTRLFUNC_CHANGE_RANGE)
		AfxGetMainWnd()->PostMessage(WM_MESSAGE_CHANGE_RANGE, value, (WPARAM)pCtrlDetail);

	if (pCtrlDetail->CtrlFunc & CTRLFUNC_CHANGE_CONVERSION_TIME)
		AfxGetMainWnd()->PostMessage(WM_MESSAGE_CHANGE_CONVERSION_TIME, value, (WPARAM)pCtrlDetail);

	if (pCtrlDetail->CtrlFunc & CTRLFUNC_CALCULATE_POWER)
		AfxGetMainWnd()->PostMessage(WM_MESSAGE_CALCULATE_POWER, value, (WPARAM)pCtrlDetail);

}

BOOL CEditGroup::PreTranslateMessage(MSG* pMsg)
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
			value = wcstol(csTemp, NULL, 10);
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
	else if(pMsg->message == WM_MOUSEWHEEL)
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


void CEditGroup::OnOK()
{
	CMyControlGroup::OnOK();
}


void CEditGroup::OnCancel()
{
	CMyControlGroup::OnCancel();
}

afx_msg LRESULT CEditGroup::OnMessageUpdateui(WPARAM wParam, LPARAM lParam)
{
	int32_t value = 0;

	if (pRegInfoMap->at(pBitDetail0->RegAddr).RegBits > 1)
		value = GetRegValue();
	else
		value = GetBitValue();

	if (value != LastVal)
	{
		SetEditText(value);
		LastVal = value;
	}

	return 0;
}


afx_msg LRESULT CEditGroup::OnMessageCalibration(WPARAM wParam, LPARAM lParam)
{
	CString csTemp;
	uint32_t value = wParam;
	CCtrlDetail* pCtrlDetail2 = (CCtrlDetail*)lParam;

	if (pCtrlDetail2->BitMapping.at(0).Find(pCtrlDetail->BitMapping.at(0)) == 0)
	{
		if (value > (uint32_t)CtrlRange.second)
		{
			value = CtrlRange.second;
			csTemp.Format(_T("The data is over calibration maximum value.\nSet calibration value to maximum = %d ."),
				value);
		}
		else
		{
			csTemp.Format(_T("Calibration Done.\nSet calibration value = %d ."), value);
		}
		SetValue(value);


		MessageBoxW(csTemp, _T("Calibration Function"), MB_OK);
	}

	return 0;
}
