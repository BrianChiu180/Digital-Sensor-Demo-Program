// CheckGroup.cpp : implementation file
//

#include "stdafx.h"
#include "CheckGroup.h"
#include "afxdialogex.h"


// CCheckGroup dialog

IMPLEMENT_DYNAMIC(CCheckGroup, CMyControlGroup)

CCheckGroup::CCheckGroup(CWnd* pParent /*=NULL*/)
	: CMyControlGroup(CCheckGroup::IDD, pParent) {
	LastVal = 0;
}

CCheckGroup::~CCheckGroup() {
}

void CCheckGroup::DoDataExchange(CDataExchange* pDX) {
	CMyControlGroup::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, mCheck);
}


BEGIN_MESSAGE_MAP(CCheckGroup, CMyControlGroup)
	ON_MESSAGE(WM_MESSAGE_UPDATEUI, &CCheckGroup::OnMessageUpdateui)
	ON_BN_CLICKED(IDC_CHECK1, &CCheckGroup::OnClickedCheck)
END_MESSAGE_MAP()

BOOL CCheckGroup::OnInitDialog() {
	CMyControlGroup::OnInitDialog();
	uint8_t value;	

	if (pCtrlDetail->CtrlName.first.IsEmpty())
	{
		if (pBitDetail0->csDesc.IsEmpty())
			SetName(pCtrlDetail->BitMapping.at(0));
		else
			SetName(pBitDetail0->csDesc);
	}
	else
		SetName(pCtrlDetail->CtrlName.first);

	value = DefaultVal;

	if (!pCtrlDetail->bActive)
		value = (uint8_t)(value != 1);

	LastVal = value;
	mCheck.SetCheck(value);

	return TRUE;
}


void CCheckGroup::SetName(CString name) {
	mCheck.SetWindowTextW(name);
}

void CCheckGroup::SetValue(uint8_t value) {
	LastVal = value;
	mCheck.SetCheck(value);

	//LEO for sun light suppression
	if (pCtrlDetail->CtrlFunc == CTRLFUNC_SL_SUPPRESSION)
	{
		AfxGetMainWnd()->PostMessage(WM_MESSAGE_SL_SUPPRESSION, value, 0);
		return;
	}
	//LEO

	if (!pCtrlDetail->bActive)
		value = (uint8_t)(value != 1);
	CtrlWrite(value);

	if (pCtrlDetail->CtrlFunc & CTRLFUNC_CHANGE_CONVERSION_TIME)
		AfxGetMainWnd()->PostMessage(WM_MESSAGE_CHANGE_CONVERSION_TIME, value, (WPARAM)pCtrlDetail);

	if (pCtrlDetail->CtrlFunc & CTRLFUNC_CALCULATE_POWER)
		AfxGetMainWnd()->PostMessage(WM_MESSAGE_CALCULATE_POWER, 0, 0);

}

void CCheckGroup::CtrlInit(CDieDetail* pDie, CCtrlDetail* pCtrl, CToolTipCtrl* pToolTip) {
	//leo
	if (pCtrl->CtrlFunc == CTRLFUNC_SL_SUPPRESSION)
	{
		CMyControlGroup::CtrlInit(pCtrl, pToolTip);
		DefaultVal = 0;
	}
	else // leo
	{ 		
		CMyControlGroup::CtrlInit(pDie, pCtrl, pToolTip);

		DefaultVal = LSHIFT(DefaultVal, pBitDetail0->BitShift.at(0));
	}
}


afx_msg LRESULT CCheckGroup::OnMessageUpdateui(WPARAM wParam, LPARAM lParam) {
	uint8_t value;
	
	//leo
	if (pCtrlDetail->CtrlFunc == CTRLFUNC_SL_SUPPRESSION)
	{
		value = mCheck.GetCheck();
	}
	else // leo
	{
		value = GetBitValue();
	}

	if (!pCtrlDetail->bActive)
		value = (uint8_t)(value != 1);

	if (value != LastVal)
	{
		mCheck.SetCheck(value);
		LastVal = value;
	}

	return 0;
}


void CCheckGroup::OnClickedCheck()
{
	uint8_t value = mCheck.GetCheck();

	if (value != LastVal)
		SetValue(value);
}
