// Modelless_List.cpp : implementation file
//

#include "stdafx.h"
#include "Modelless_List.h"
#include "afxdialogex.h"


// CModelless_List dialog

IMPLEMENT_DYNAMIC(CModelless_List, CDialogEx)

CModelless_List::CModelless_List(CWnd* pParent /*=NULL*/)
	: CDialogEx(CModelless_List::IDD, pParent), pBitDetailMap(NULL), pCtrlDetail(NULL), pCtrlInfo(NULL), pRegTable(NULL) {

}

CModelless_List::~CModelless_List() {
}

void CModelless_List::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModelless_List, CDialogEx)
	ON_MESSAGE(WM_MESSAGE_UPDATEUI, &CModelless_List::OnMessageUpdateui)
END_MESSAGE_MAP()

BOOL CModelless_List::OnInitDialog() {
	CDialogEx::OnInitDialog();

	CRect rc, rc2;
	int value;
	CString csAddr = _T(""), csValue = _T(""), csDesc = _T("");
	CString csAddrMax = _T(""), csValueMax = _T(""), csDescMax = _T("");

	GetClientRect(&rc);
	GetWindowRect(&rc2);

	mList.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_NOSCROLL,
		CRect(0, 0, rc.Width(), rc.Height()), this, IDC_LISTCTRL1);

	mList.InsertColumn(0, _T("Addr"), LVCFMT_CENTER, 80, 0);
	mList.InsertColumn(1, _T("Value"), LVCFMT_CENTER, 80, 1);
	mList.InsertColumn(2, _T("Name"), LVCFMT_LEFT, 140, 2);
	map<uint8_t, CRegInfo>::iterator iter;
	iter = pRegTable->RegInfo.begin();

	int i = 0;
	int j = 0;
	uint8_t bits = 0;
	while (iter != pRegTable->RegInfo.end())
	{
		if (!iter->second.bEngMode)
		{
			RegMappingList[iter->first] = j;

			csAddr.Format(_T("0x%02X"), iter->first);
			if (iter->second.RegBits > 1)
			{
				for (i = 1; i < iter->second.RegBits; i++)
				{
					if(pRegTable->RegInfo.count(iter->first + i) == 0)
						csAddr.Format(_T("%s, 0x%02X"), csAddr.GetString(), iter->first + i);
				}
			}

			value = 0;
			for (i = 0; i < iter->second.RegBits; i++)
				value += iter->second.RegCurVal.at(i) << (i * 8);

			switch (iter->second.RegBits)
			{
			case 1: csValue.Format(_T("0x%02X"), value); break;
			case 2: csValue.Format(_T("0x%04X"), value); break;
			case 4: csValue.Format(_T("0x%08X"), value); break;
			default: csValue.Format(_T("0x%X"), value); break;
			}

			mList.InsertItem(j, csAddr);
			mList.SetItemText(j, 1, csValue);
			mList.SetItemText(j, 2, iter->second.RegDesc);

			if (csAddr.GetLength() > csAddrMax.GetLength())
				csAddrMax = csAddr;

			if (csValue.GetLength() > csValueMax.GetLength())
				csValueMax = csValue;

			if (iter->second.RegDesc.GetLength() > csDescMax.GetLength())
				csDescMax = iter->second.RegDesc;

			j++;
		}
		++iter;
	}

	CClientDC dc(&mList);
	CFont* font = mList.GetFont();

	dc.SelectObject(font);
	csAddrMax += _T("    ");
	CSize sz = dc.GetTextExtent(csAddrMax);
	mList.SetColumnWidth(0, sz.cx + 4);

	csValueMax += _T("    ");
	sz = dc.GetTextExtent(csValueMax);
	mList.SetColumnWidth(1, sz.cx + 4);

	csDescMax += _T("    ");
	sz = dc.GetTextExtent(csDescMax);
	mList.SetColumnWidth(2, sz.cx + 4);

	CRect rc_list;

	mList.GetItemRect(0, &rc_list, LVIR_BOUNDS);

	this->SetWindowPos(NULL, 0, 0,
		rc2.Width() - rc.Width() + rc_list.Width(),
		rc2.Height() - rc.Height() + (rc_list.Height() * (mList.GetItemCount() + 1)) + 5,
		SWP_NOMOVE | SWP_SHOWWINDOW);

	GetClientRect(&rc);
	mList.SetWindowPos(NULL, 0, 0, rc.Width(), rc.Height(), SWP_NOMOVE | SWP_SHOWWINDOW);

	DWORD dwStyle = mList.GetExtendedStyle();
	dwStyle |= LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_INFOTIP | LVS_EX_DOUBLEBUFFER;
	mList.SetExtendedStyle(dwStyle);

	this->SetWindowTextW(csName);

	return TRUE;
}


BOOL CModelless_List::DestroyWindow() {
	mList.DestroyWindow();

	return CDialogEx::DestroyWindow();
}


afx_msg LRESULT CModelless_List::OnMessageUpdateui(WPARAM wParam, LPARAM lParam) {
	CString csTemp;
	int value = 0;
	unsigned int i = 0;
	uint8_t first_reg = 0;
	uint8_t bits = 0;
	int8_t shift = 0;

	mList.SetRedraw(FALSE);
	map<uint8_t, CRegInfo>::iterator iter;
	map<uint8_t, CString>::iterator iter2;

	iter = pRegTable->RegInfo.begin();
	while (iter != pRegTable->RegInfo.end())
	{
		if (!iter->second.bEngMode)
		{
			value = 0;
			for (i = 0; i < iter->second.RegBits; i++)
			{
				if (pBitDetailMap->at(iter->second.BitName.at(0)).BitShift.size() >= (uint8_t)(i + 1))
				{
					iter2 = iter->second.BitName.begin();

					while (iter2 != iter->second.BitName.end())
					{
						if (pBitDetailMap->at(iter2->second).BitMask.size() <= i)
							break;

						if (iter->second.RegBits > 1)
						{
							shift = pBitDetailMap->at(iter2->second).BitShift.at(i);
						}
						else
							shift = 0;
					
						value += LSHIFT((iter->second.RegCurVal.at(i) & pBitDetailMap->at(iter2->second).BitMask.at(i)), shift);

						iter2++;

					}
				}
			}

			switch (iter->second.RegBits)
			{
			case 1: csTemp.Format(_T("0x%02X"), value); break;
			case 2: csTemp.Format(_T("0x%04X"), value); break;
			case 4: csTemp.Format(_T("0x%08X"), value); break;
			default: csTemp.Format(_T("0x%X"), value); break;
			}

			mList.SetItemText(RegMappingList[iter->first], 1, csTemp);
		}
		iter++;
	}

	mList.SetRedraw(TRUE);

	Invalidate();
	UpdateData(0);

	return 0;
}
