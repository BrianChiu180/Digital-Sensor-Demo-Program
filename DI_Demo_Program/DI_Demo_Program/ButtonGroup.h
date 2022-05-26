#pragma once
#include "afxwin.h"
#include "MyControlGroup.h"

// CButtonGroup dialog

class CButtonGroup : public CMyControlGroup {
	DECLARE_DYNAMIC(CButtonGroup)

public:
	CButtonGroup(CWnd* pParent = NULL);   // standard constructor
	virtual ~CButtonGroup();

	enum { IDD = IDD_BUTTON_GROUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton mButton;
	void SetName(CString name);
	afx_msg void OnClickedButton1();
	virtual BOOL OnInitDialog();
};
