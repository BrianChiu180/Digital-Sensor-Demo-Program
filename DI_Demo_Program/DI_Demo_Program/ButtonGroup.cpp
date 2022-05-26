// ButtonGroup.cpp : implementation file
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "ButtonGroup.h"


// CButtonGroup dialog

IMPLEMENT_DYNAMIC(CButtonGroup, CMyControlGroup)

CButtonGroup::CButtonGroup(CWnd* pParent /*=NULL*/)
	: CMyControlGroup(CButtonGroup::IDD, pParent)
{

}

CButtonGroup::~CButtonGroup()
{
}

void CButtonGroup::DoDataExchange(CDataExchange* pDX)
{
	CMyControlGroup::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, mButton);
}


BEGIN_MESSAGE_MAP(CButtonGroup, CMyControlGroup)
	ON_BN_CLICKED(IDC_BUTTON1, &CButtonGroup::OnClickedButton1)
END_MESSAGE_MAP()


void CButtonGroup::SetName(CString name)
{
	mButton.SetWindowTextW(name);
}


void CButtonGroup::OnClickedButton1()
{
	if(pCtrlDetail->CtrlFunc & CTRLFUNC_NORMAL)
		CtrlWrite();

	if (pCtrlDetail->CtrlFunc & CTRLFUNC_CLEAR_INT)
	{
		CtrlWrite(0x00, true);
		AfxGetMainWnd()->PostMessage(WM_MESSAGE_UPDATEUI, 1); // Leo added for UI updata while sensor disable.
	}

	if (pCtrlDetail->CtrlFunc & CTRLFUNC_SWRST)
	{		
		CtrlWrite();
		AfxGetMainWnd()->SendMessage(WM_MESSAGE_RELOAD_REG);
		AfxGetMainWnd()->PostMessage(WM_MESSAGE_UPDATEUI, 1);
		TRACE(_T("CTRLFUNC_SWRST\n"));		
	}

	if (pCtrlDetail->CtrlFunc & CTRLFUNC_CALIBRATION)
	{
		CtrlWrite((uint32_t)0);
		AfxGetMainWnd()->SendMessage(WM_MESSAGE_UPDATEUI, 1);
		AfxGetMainWnd()->PostMessage(WM_MESSAGE_CALIBRATION, 0, (WPARAM)pCtrlDetail);
		TRACE(_T("CTRLFUNC_CALIBRATION\n"));
	}

	if (pCtrlDetail->CtrlFunc & CTRLFUNC_CALCULATE_POWER)
	{
		AfxGetMainWnd()->PostMessage(WM_MESSAGE_CALCULATE_POWER, 0, 0);
		TRACE(_T("CTRLFUNC_CALCULATE_POWER\n"));		
	}

	if (pCtrlDetail->CtrlFunc & CTRLFUNC_AUTO_DAC)
	{
		CtrlWrite((uint32_t)0);
		AfxGetMainWnd()->SendMessage(WM_MESSAGE_AUTO_DAC, 0, (WPARAM)pCtrlDetail);
	}

	if (pCtrlDetail->CtrlFunc & CTRLFUNC_SL_SUPPRESSION)
	{
		AfxGetMainWnd()->SendMessage(WM_MESSAGE_SL_SUPPRESSION, 0, (WPARAM)pCtrlDetail);
	}
}


BOOL CButtonGroup::OnInitDialog()
{
	CMyControlGroup::OnInitDialog();

	if (pCtrlDetail->CtrlName.first.IsEmpty()) {
		if (pBitDetail0->csDesc.IsEmpty())
			SetName(pCtrlDetail->BitMapping.at(0));
		else
			SetName(pBitDetail0->csDesc);
	}
	else
		SetName(pCtrlDetail->CtrlName.first);

	return TRUE;
}
