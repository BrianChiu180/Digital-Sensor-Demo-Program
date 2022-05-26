#pragma once
#include "TextGroup.h"
#include "ButtonGroup.h"
#include "CheckGroup.h"
#include "ComboGroup.h"
#include "EditGroup.h"
#include "SliderGroup.h"
#include "ProgressGroup.h"
#include "RadioGroup.h"
#include <map>

class CPageST1 : public CDialogEx {
	DECLARE_DYNAMIC(CPageST1)

public:
	CPageST1(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPageST1();

	// Dialog Data
	enum { IDD = IDD_PAGE_STYLE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void CtrlInit(CDieDetail* pDie, CCtrlInfo* pCtrl, CToolTipCtrl* pToolTip) {
		pDieDetail = pDie;
		pCtrlInfo = pCtrl;
		mToolTip = pToolTip;
	}

	void Set();
private:
	CDieDetail* pDieDetail;
	CRegisterTable* pRegTable;
	CCtrlInfo* pCtrlInfo;
	CCtrlDetail* pCtrlDetail;
	CBitDetail* pBitDetail;

	map<pairINT, CTextGroup>		mmTextGroup;
	map<pairINT, CComboGroup>		mmComboGroup;
	map<pairINT, CEditGroup>		mmEditGroup;
	map<pairINT, CSliderGroup>		mmSliderGroup;
	map<pairINT, CProgressGroup>	mmProgressGroup;
	map<pairINT, CCheckGroup>		mmCheckGroup;
	map<pairINT, CButtonGroup>		mmButtonGroup;
	map<pairINT, CRadioGroup>		mmRadioGroup;

	template <typename T>
	inline void DlgInit(T &obj, pairINT nID, int* incre) {
		obj[nID].CtrlInit(pDieDetail, pCtrlDetail, mToolTip);
		obj[nID].Create(obj[nID].IDD, this);
		obj[nID].SetWindowPos(NULL, 7 + nID.first * incre[0], 7 + nID.second * incre[1], 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW);
	}
public:
	virtual BOOL DestroyWindow();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CToolTipCtrl* mToolTip;
protected:
	afx_msg LRESULT OnMessageUpdateui(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageChangeAvgNum(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageChangeSelData(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageChangeRange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageCalibration(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageUpdateInfo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageChangeNameMapping(WPARAM wParam, LPARAM lParam);
};
