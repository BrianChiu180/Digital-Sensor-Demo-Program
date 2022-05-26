#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "MyControlGroup.h"

// CProgressGroup dialog

class CProgressGroup : public CMyControlGroup {
	DECLARE_DYNAMIC(CProgressGroup)

public:
	CProgressGroup(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProgressGroup();

	// Dialog Data
	enum { IDD = IDD_PROGRESS_GROUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl mProgress;

	void CtrlInit(CDieDetail* pDie, CCtrlDetail* pCtrl, CToolTipCtrl* pToolTip) {
		CMyControlGroup::CtrlInit(pDie, pCtrl, pToolTip);
		LastVal = -1;
		dequeVal.clear();
	}

	virtual BOOL OnInitDialog();
	void SetValue(int value);

private:
	int LastVal;
	double AvgSum;
	deque<int> dequeVal;
	uint8_t SelData;
	BOOL bChangeRange;

protected:
	afx_msg LRESULT OnMessageUpdateui(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageChangeSelData(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageChangeRange(WPARAM wParam, LPARAM lParam);
};
