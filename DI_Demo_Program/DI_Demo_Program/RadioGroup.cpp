// RadioGroup.cpp : implementation file
//

#include "stdafx.h"
#include "RadioGroup.h"
#include "afxdialogex.h"


// CRadioGroup dialog

IMPLEMENT_DYNAMIC(CRadioGroup, CMyControlGroup)

CRadioGroup::CRadioGroup(CWnd* pParent /*=NULL*/)
	: CMyControlGroup(CRadioGroup::IDD, pParent), LastVal(0)
{

}

CRadioGroup::~CRadioGroup()
{
}

void CRadioGroup::DoDataExchange(CDataExchange* pDX)
{
	CMyControlGroup::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUP1, mGroup);
}


BEGIN_MESSAGE_MAP(CRadioGroup, CMyControlGroup)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO1, IDC_RADIO8, &CRadioGroup::OnClickedRadio)
	ON_MESSAGE(WM_MESSAGE_UPDATEUI, &CRadioGroup::OnMessageUpdateui)
END_MESSAGE_MAP()

BOOL CRadioGroup::OnInitDialog()
{
	CMyControlGroup::OnInitDialog();

	CRect rc;
	this->GetClientRect(rc);

	size_t sz_item = pListName->size() - 1;
	this->SetWindowPos(NULL, 0, 0, rc.right, rc.bottom + sz_item * 23, SWP_NOMOVE | SWP_SHOWWINDOW);
	mGroup.SetWindowPos(NULL, 0, 0, rc.right, rc.bottom + sz_item * 23, SWP_NOMOVE | SWP_SHOWWINDOW);

	map<uint8_t, CString>::iterator iter = pListName->begin();
	int y = 17;
	while (iter != pListName->end())
	{
		mmRadio[iter->first].Create(iter->second, (iter == pListName->begin()?WS_GROUP:NULL) | WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			CRect(5, y, rc.right-5, y+20), this, IDC_RADIO1 + iter->first);
		y += 23;
		++iter;
	}

	if (pCtrlDetail->CtrlName.first == _T(""))
		SetName(pCtrlDetail->BitMapping.at(0));
	else
		SetName(pCtrlDetail->CtrlName.first);

	LastVal = DefaultVal;

	SetValue(DefaultVal);

	return TRUE;
}


void CRadioGroup::SetValue(uint8_t value)
{
	mmRadio[value].SetCheck(1);
	CtrlWrite(value);
	LastVal = value;

	if (pCtrlDetail->CtrlFunc & CTRLFUNC_CHANGE_CONVERSION_TIME)
		AfxGetMainWnd()->PostMessage(WM_MESSAGE_CHANGE_CONVERSION_TIME, value, (WPARAM)pCtrlDetail);

	if (pCtrlDetail->CtrlFunc & CTRLFUNC_CALCULATE_POWER)
		AfxGetMainWnd()->PostMessage(WM_MESSAGE_CALCULATE_POWER, 0, 0);

	if (pCtrlDetail->CtrlFunc & CTRLFUNC_CHANGE_SCALE)
		AfxGetMainWnd()->PostMessage(WM_MESSAGE_CHANGE_SCALE, value, (WPARAM)pCtrlDetail);

}

void CRadioGroup::OnClickedRadio(UINT nID)
{
	SetValue(nID - IDC_RADIO1);
}

afx_msg LRESULT CRadioGroup::OnMessageUpdateui(WPARAM wParam, LPARAM lParam)
{
	uint8_t value = 0;

	value = GetBitValue();

	if (value != LastVal && value < mmRadio.size())
	{
		mmRadio[LastVal].SetCheck(0);
		mmRadio[value].SetCheck(1);

		LastVal = value;
	}

	return 0;
}
