#pragma once
#include "afxwin.h"
#include "MyControlGroup.h"

// CCheckGroup dialog

class CCheckGroup : public CMyControlGroup {
	DECLARE_DYNAMIC(CCheckGroup)

public:
	CCheckGroup(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCheckGroup();

	enum { IDD = IDD_CHECK_GROUP };
	void SetValue(uint8_t value);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	void SetName(CString name);
	virtual BOOL OnInitDialog();
	void CtrlInit(CDieDetail* pDie, CCtrlDetail* pCtrl, CToolTipCtrl* pToolTip);
	afx_msg void OnClickedCheck();

private:
	CButton mCheck;
	uint8_t LastVal;

protected:
	afx_msg LRESULT OnMessageUpdateui(WPARAM wParam, LPARAM lParam);

};
