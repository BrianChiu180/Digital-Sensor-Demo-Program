// PageST1.cpp : implementation file
//

#include "stdafx.h"
#include "Define.h"
#include "PageST1.h"
#include "afxdialogex.h"


// PageST1 dialog

IMPLEMENT_DYNAMIC(CPageST1, CDialogEx)

CPageST1::CPageST1(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPageST1::IDD, pParent), 
	mToolTip(NULL), pBitDetail(NULL), pCtrlDetail(NULL), pCtrlInfo(NULL), pDieDetail(NULL), pRegTable(NULL) 
{

}

CPageST1::~CPageST1() {
}

void CPageST1::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageST1, CDialogEx)
	ON_MESSAGE(WM_MESSAGE_UPDATEUI, &CPageST1::OnMessageUpdateui)
	ON_MESSAGE(WM_MESSAGE_CHANGE_AVG_NUM, &CPageST1::OnMessageChangeAvgNum)
	ON_MESSAGE(WM_MESSAGE_CHANGE_SEL_DATA, &CPageST1::OnMessageChangeSelData)
	ON_MESSAGE(WM_MESSAGE_CHANGE_RANGE, &CPageST1::OnMessageChangeRange)
	ON_MESSAGE(WM_MESSAGE_CALIBRATION, &CPageST1::OnMessageCalibration)
	ON_MESSAGE(WM_MESSAGE_UPDATE_INFO, &CPageST1::OnMessageUpdateInfo)
	ON_MESSAGE(WM_MESSAGE_CHANGE_NAMEMAPPING, &CPageST1::OnMessageChangeNameMapping)
END_MESSAGE_MAP()

BOOL CPageST1::OnInitDialog() {
	CDialogEx::OnInitDialog();

	return TRUE;
}

void CPageST1::Set() {
	pairINT nID;
	int iDefault = 0;
	pairINT range = make_pair(0, 0);
	CRect rc;
	int incre[2] = { 0 };
	this->GetClientRect(rc);
	incre[0] = (rc.right - 6) / 8;
	incre[1] = (rc.bottom - 6) / 18;
	map<pair<uint8_t/* X */, uint8_t/* Y */>, CCtrlDetail>::iterator
		iter = pCtrlInfo->CtrlDetail.begin();

	while (iter != pCtrlInfo->CtrlDetail.end())
	{
		pCtrlDetail = &iter->second;
		nID = iter->first;

		switch (pCtrlDetail->CtrlType)
		{
		case TEXT_GROUP:
			DlgInit(mmTextGroup, nID, incre);
			break;
		case COMBO_GROUP:
			DlgInit(mmComboGroup, nID, incre);
			break;
		case EDIT_GROUP:
			DlgInit(mmEditGroup, nID, incre);
			break;
		case BUTTON_GROUP:
			TRACE(_T("BUTTON_GROUP\n"));
			TRACE(_T("X %d, Y%d\n"), iter->first.first, iter->first.second);
			DlgInit(mmButtonGroup, nID, incre);
			break;
		case CHECK_GROUP:
			DlgInit(mmCheckGroup, nID, incre);
			break;
		case RADIO_GROUP:
			DlgInit(mmRadioGroup, nID, incre);
			break;
		case PROGRESS_GROUP:
			DlgInit(mmProgressGroup, nID, incre);
			break;
		case SLIDER_GROUP:
			DlgInit(mmSliderGroup, nID, incre);
			break;
		default: break;
		}
		++iter;
	}
}

BOOL CPageST1::DestroyWindow() {
	CustomDestroy(mmButtonGroup);
	CustomDestroy(mmCheckGroup);
	CustomDestroy(mmComboGroup);
	CustomDestroy(mmEditGroup);
	CustomDestroy(mmProgressGroup);
	CustomDestroy(mmRadioGroup);
	CustomDestroy(mmSliderGroup);
	CustomDestroy(mmTextGroup);

	return CDialogEx::DestroyWindow();
}


void CPageST1::OnOK() {
}


void CPageST1::OnCancel() {
}


BOOL CPageST1::PreTranslateMessage(MSG* pMsg) {
	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam) {
		case VK_ESCAPE:
		case VK_RETURN:
			return false;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


afx_msg LRESULT CPageST1::OnMessageUpdateui(WPARAM wParam, LPARAM lParam) {
	CustomMessage(mmProgressGroup, WM_MESSAGE_UPDATEUI, wParam, lParam, wParam > 0);

	if (wParam == 0)
		return 0;

	CustomMessage(mmComboGroup, WM_MESSAGE_UPDATEUI, wParam, lParam, wParam > 0);
	CustomMessage(mmCheckGroup, WM_MESSAGE_UPDATEUI, wParam, lParam, wParam > 0);
	CustomMessage(mmEditGroup, WM_MESSAGE_UPDATEUI, wParam, lParam, wParam > 0);
	CustomMessage(mmRadioGroup, WM_MESSAGE_UPDATEUI, wParam, lParam, wParam > 0);
	CustomMessage(mmSliderGroup, WM_MESSAGE_UPDATEUI, wParam, lParam, wParam > 0);

	return 0;
}


afx_msg LRESULT CPageST1::OnMessageChangeAvgNum(WPARAM wParam, LPARAM lParam) {
	CustomMessage(mmProgressGroup, WM_MESSAGE_CHANGE_AVG_NUM, wParam, lParam);
	return 0;
}


afx_msg LRESULT CPageST1::OnMessageChangeSelData(WPARAM wParam, LPARAM lParam) {
	CustomMessage(mmProgressGroup, WM_MESSAGE_CHANGE_SEL_DATA, wParam, lParam);
	return 0;
}


afx_msg LRESULT CPageST1::OnMessageChangeRange(WPARAM wParam, LPARAM lParam) {
	CustomMessage(mmProgressGroup, WM_MESSAGE_CHANGE_RANGE, wParam, lParam);
	CustomMessage(mmSliderGroup, WM_MESSAGE_CHANGE_RANGE, wParam, lParam);
	return 0;
}


afx_msg LRESULT CPageST1::OnMessageCalibration(WPARAM wParam, LPARAM lParam)
{
	CustomMessage(mmEditGroup, WM_MESSAGE_CALIBRATION, wParam, lParam);
	return 0;
}


afx_msg LRESULT CPageST1::OnMessageUpdateInfo(WPARAM wParam, LPARAM lParam)
{
	CustomMessage(mmTextGroup, WM_MESSAGE_UPDATE_INFO, wParam, lParam);
	return 0;
}

afx_msg LRESULT CPageST1::OnMessageChangeNameMapping(WPARAM wParam, LPARAM lParam) {
	CustomMessage(mmComboGroup, WM_MESSAGE_CHANGE_NAMEMAPPING, wParam, lParam);
	return 0;
}
