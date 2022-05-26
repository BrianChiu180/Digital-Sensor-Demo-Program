#pragma once
#include "Define.h"
#include "ProgressBar.h"
#include "TextGroup.h"

class CModelless1 : public CDialogEx {
	DECLARE_DYNAMIC(CModelless1)

public:
	CModelless1(CWnd* pParent = NULL);   // standard constructor
	CModelless1(UINT nIDTemplate, CWnd* pParent = NULL) :
		CDialogEx(nIDTemplate, pParent), mToolTip(NULL), pBitDetail(NULL), pCtrlDetail(NULL), 
		pCtrlInfo(NULL), pDieDetail(NULL), pRegTable(NULL)
	{};

	// Dialog Data
	enum { IDD = IDD_MODELLESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void CtrlInit(DlgSel_ i, CDieDetail* pDie, CToolTipCtrl* pToolTip) {
		pDieDetail = pDie;
		mToolTip = pToolTip;
		csName = pDieDetail->DlgName[i];
		pCtrlInfo = &pDieDetail->CtrlInfo[i];
		pRegTable = &pDieDetail->RegisterTable;
	}

	virtual BOOL DestroyWindow();
	CToolTipCtrl* mToolTip;

private:
	map<pairINT, CProgressBar> mBar;
	map<pairINT, CTextGroup> mText;
	CString csName;
	CDieDetail* pDieDetail;
	CRegisterTable* pRegTable;
	CCtrlInfo* pCtrlInfo;

	CCtrlDetail* pCtrlDetail;
	CBitDetail* pBitDetail;

protected:
	afx_msg LRESULT OnMessageUpdateui(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageChangeAvgNum(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageChangeRange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageChangeScale(WPARAM wParam, LPARAM lParam);
};
