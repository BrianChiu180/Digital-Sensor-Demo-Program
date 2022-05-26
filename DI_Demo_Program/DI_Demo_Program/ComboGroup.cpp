// ComboText.cpp : implementation file
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "ComboGroup.h"


// CComboText dialog

IMPLEMENT_DYNAMIC(CComboGroup, CMyControlGroup)

CComboGroup::CComboGroup(CWnd* pParent /*=NULL*/)
	: CMyControlGroup(CComboGroup::IDD, pParent) {
	LastVal = 0;
}

CComboGroup::~CComboGroup() {
}

void CComboGroup::DoDataExchange(CDataExchange* pDX) {
	CMyControlGroup::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUP1, mGroup);
	DDX_Control(pDX, IDC_COMBO1, mCombo);
	DDX_Control(pDX, IDC_STATIC1, mValue);
}


BEGIN_MESSAGE_MAP(CComboGroup, CMyControlGroup)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CComboGroup::OnSelchangeCombo1)
	ON_MESSAGE(WM_MESSAGE_UPDATEUI, &CComboGroup::OnMessageUpdateui)
	ON_MESSAGE(WM_MESSAGE_CHANGE_NAMEMAPPING, &CComboGroup::OnMessageChangeNameMapping)
END_MESSAGE_MAP()


// CComboText message handlers


void CComboGroup::SetName(CString name) {
	CMyControlGroup::SetName(name);

	CRect rect1;
	CClientDC dc(&mGroup);

	dc.SelectObject(GetFont());
	CSize sz = dc.GetTextExtent(name);
	mGroup.GetClientRect(&rect1);

	if (rect1.Width() < sz.cx)
	{
		LOGFONT lFont;
		GetFont()->GetLogFont(&lFont);
		lFont.lfHeight = (lFont.lfHeight * rect1.Width() / sz.cx) + 1;
		mFontLabel.CreateFontIndirect(&lFont);
		mGroup.SetFont(&mFontLabel);
	}
}

void CComboGroup::CtrlInit(CDieDetail* pDie, CCtrlDetail* pCtrl, CToolTipCtrl* pToolTip) {
	CMyControlGroup::CtrlInit(pDie, pCtrl, pToolTip);

	ReMapping();
	DefaultVal = LSHIFT(DefaultVal, pBitDetail0->BitShift.at(0));
}

BOOL CComboGroup::OnInitDialog() {
	CMyControlGroup::OnInitDialog();
	CString csTemp;

	AddString();

	if (pCtrlDetail->CtrlName.first.IsEmpty())
	{
		if (pBitDetail0->csDesc.IsEmpty())
			SetName(pCtrlDetail->BitMapping.at(0));
		else
			SetName(pBitDetail0->csDesc);
	}
	else
		SetName(pCtrlDetail->CtrlName.first);

	mCombo.SetCurSel(mapComboItem[DefaultVal]);
	LastVal = DefaultVal;
	csTemp.Format(_T("0x%02X"), DefaultVal);
	mValue.SetWindowTextW(csTemp);

	if(pCtrlDetail->CtrlFunc & CTRLFUNC_SELDATA)
		AfxGetMainWnd()->PostMessage(WM_MESSAGE_CHANGE_SEL_DATA, pCtrlDetail->RegMapping.at(DefaultVal));
	
	if (pCtrlDetail->CtrlFunc & CTRLFUNC_CHANGE_RANGE)
		AfxGetMainWnd()->PostMessage(WM_MESSAGE_CHANGE_RANGE, DefaultVal, (WPARAM)pCtrlDetail);

	if (pCtrlDetail->CtrlFunc & CTRLFUNC_CHANGE_SCALE)
		AfxGetMainWnd()->PostMessage(WM_MESSAGE_CHANGE_SCALE, DefaultVal, (WPARAM)pCtrlDetail);

	if (pCtrlDetail->CtrlFunc & CTRLFUNC_CHANGE_NAMEMAPPING)
		AfxGetMainWnd()->PostMessage(WM_MESSAGE_CHANGE_NAMEMAPPING, DefaultVal, (WPARAM)pCtrlDetail);

	return TRUE;
}

void CComboGroup::AddString(void) {
	CDC* pDC = mCombo.GetDC();
	CSize TSize;
	LONG TMax = 0;

	int i = 0;

	mCombo.ResetContent();
	mapComboItem.clear();

	if (pListName->size() > 0)
	{
		map<uint8_t, CString>::iterator iter = pListName->begin();

		while (iter != pListName->end())
		{
			mCombo.AddString(iter->second);
			mapComboItem[iter->first] = i;
			TSize = pDC->GetTextExtent(iter->second);
			TMax = TSize.cx > TMax ? TSize.cx : TMax;
			i++;
			++iter;
		}
	}
	else if (pListName2->size() > 0)
	{
		uint8_t Bit2Value = GetBitValue(pCtrlDetail->BitMapping[1]);
		map<pair<uint8_t, uint8_t>, CString>::iterator iter = pListName2->begin();
		while (iter != pListName2->end())
		{
			if (Bit2Value == iter->first.second)
			{
				mCombo.AddString(iter->second);
				mapComboItem[iter->first.first] = i;
				TSize = pDC->GetTextExtent(iter->second);
				TMax = TSize.cx > TMax ? TSize.cx : TMax;
				i++;
			}
			++iter;
		}
	}

	mCombo.ReleaseDC(pDC);

	if (mCombo.GetDroppedWidth() < TMax)
		mCombo.SetDroppedWidth(TMax);
}

void CComboGroup::ReMapping(void) {

	rmap_Item.clear();

	if (pListName->size() > 0)
	{
		map<uint8_t, CString>::iterator iter = pListName->begin();
		while (iter != pListName->end())
		{
			rmap_Item[iter->second] = iter->first;
			++iter;
		}
	}
	else if (pListName2->size() > 0)
	{
		uint8_t Bit2Value = GetBitValue(pCtrlDetail->BitMapping[1]);
		map<pair<uint8_t, uint8_t>, CString>::iterator iter = pListName2->begin();
		while (iter != pListName2->end())
		{
			if (Bit2Value == iter->first.second)
				rmap_Item[iter->second] = iter->first.first;
			++iter;
		}
	}
}


void CComboGroup::SetValue(int value) {
	mCombo.SetCurSel(mapComboItem[value]);
	OnSelchangeCombo1();
}

uint8_t CComboGroup::SetTextBySel() {
	uint8_t value;
	CString csTemp;

	mCombo.GetLBText(mCombo.GetCurSel(), csTemp);
	value = rmap_Item.find(csTemp)->second;

	if (LastVal != value)
	{
		csTemp.Format(_T("0x%02X"), value);
		mValue.SetWindowTextW(csTemp);
		if (pCtrlDetail->CtrlFunc & CTRLFUNC_SELDATA)
			AfxGetMainWnd()->PostMessage(WM_MESSAGE_CHANGE_SEL_DATA, pCtrlDetail->RegMapping.at(value));
		
		if (pCtrlDetail->CtrlFunc & CTRLFUNC_CHANGE_RANGE)
			AfxGetMainWnd()->PostMessage(WM_MESSAGE_CHANGE_RANGE, value, (WPARAM)pCtrlDetail);

		if (pCtrlDetail->CtrlFunc & CTRLFUNC_CHANGE_CONVERSION_TIME)
			AfxGetMainWnd()->PostMessage(WM_MESSAGE_CHANGE_CONVERSION_TIME, value, (WPARAM)pCtrlDetail);

		if (pCtrlDetail->CtrlFunc & CTRLFUNC_CALCULATE_POWER)
			AfxGetMainWnd()->PostMessage(WM_MESSAGE_CALCULATE_POWER, 0, 0);

		if (pCtrlDetail->CtrlFunc & CTRLFUNC_CHANGE_SCALE)
			AfxGetMainWnd()->PostMessage(WM_MESSAGE_CHANGE_SCALE, value, (WPARAM)pCtrlDetail);

		if (pCtrlDetail->CtrlFunc & CTRLFUNC_CHANGE_NAMEMAPPING)
			AfxGetMainWnd()->PostMessage(WM_MESSAGE_CHANGE_NAMEMAPPING, value, (WPARAM)pCtrlDetail);

		LastVal = value;
	}

	return value;
}

void CComboGroup::OnSelchangeCombo1() {
	CtrlWrite(SetTextBySel());
}

BOOL CComboGroup::DestroyWindow() {
	mFontLabel.DeleteObject();
	return CMyControlGroup::DestroyWindow();
}


BOOL CComboGroup::PreTranslateMessage(MSG* pMsg) {
	return CMyControlGroup::PreTranslateMessage(pMsg);
}



afx_msg LRESULT CComboGroup::OnMessageUpdateui(WPARAM wParam, LPARAM lParam) {
	uint8_t value;

	value = GetBitValue();

	if (value != LastVal)
	{
		mCombo.SetCurSel(mapComboItem[value]);
		SetTextBySel();

		LastVal = value;
	}

	return 0;
}

afx_msg LRESULT CComboGroup::OnMessageChangeNameMapping(WPARAM wParam, LPARAM lParam) 
{
	AddString();
	ReMapping();
	mCombo.SetCurSel(mapComboItem[GetBitValue()]);
	SetTextBySel();

	return 0;
}
