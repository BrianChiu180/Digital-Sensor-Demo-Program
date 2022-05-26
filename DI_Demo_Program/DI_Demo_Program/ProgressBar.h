#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "MyControlGroup.h"

// CProgressBar dialog

class CProgressBar : public CMyControlGroup {
	DECLARE_DYNAMIC(CProgressBar)

public:
	CProgressBar(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProgressBar();

	enum { IDD = IDD_PROGRESSBAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void CtrlInit(CDieDetail* pDie, CCtrlDetail* pCtrl, CToolTipCtrl* pToolTip) {
		CMyControlGroup::CtrlInit(pDie, pCtrl, pToolTip);
		LastVal = -1;
	}

	virtual BOOL OnInitDialog();
	CStatic mName;
	CStatic mValue;
	CProgressCtrl mProgress;
	CFont mFontLabel;

	void SetValue(int value);
	void SetName(CString name);
	void SetRange(int min, int max);

private:
	int LastVal;
	double AvgSum;
	deque<int> dequeVal;
	BOOL bChangeRange;

protected:
	afx_msg LRESULT OnMessageUpdateui(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageChangeRange(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL DestroyWindow();
};
