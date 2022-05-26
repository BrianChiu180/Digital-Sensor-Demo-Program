#pragma once
#include "afxwin.h"
#include "MyControlGroup.h"

// CEditGroup dialog

class CEditGroup : public CMyControlGroup {
	DECLARE_DYNAMIC(CEditGroup)

public:
	CEditGroup(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditGroup();

	// Dialog Data
	enum { IDD = IDD_EDIT_GROUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void SetValue(uint32_t value);
	virtual void OnOK();
	virtual void OnCancel();

private:
	uint32_t LastVal;

protected:
	afx_msg LRESULT OnMessageUpdateui(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageCalibration(WPARAM wParam, LPARAM lParam);
};
