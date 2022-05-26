#pragma once
#include "Define.h"


// CModelless_List dialog

class CModelless_List : public CDialogEx {
	DECLARE_DYNAMIC(CModelless_List)

public:
	CModelless_List(CWnd* pParent = NULL);   // standard constructor
	virtual ~CModelless_List();
	virtual BOOL OnInitDialog();
	void CtrlInit(DlgSel_ i, CDieDetail* pDieDetail) {
		csName = pDieDetail->DlgName[i];
		pCtrlInfo = &pDieDetail->CtrlInfo[i];
		pRegTable = &pDieDetail->RegisterTable;
		pBitDetailMap = &pDieDetail->RegisterTable.BitDetail;
	}

	virtual BOOL DestroyWindow();

	// Dialog Data
	enum { IDD = IDD_MODELLESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl mList;

	map<uint8_t, int> RegMappingList;
	map<uint8_t, uint8_t> RegLastVal;

	CString csName;
	CRegisterTable* pRegTable;
	CCtrlInfo* pCtrlInfo;

	CCtrlDetail* pCtrlDetail;
	map<CString, CBitDetail>* pBitDetailMap;

protected:
	afx_msg LRESULT OnMessageUpdateui(WPARAM wParam, LPARAM lParam);
};
