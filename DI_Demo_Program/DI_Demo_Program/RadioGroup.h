#pragma once
#include "MyControlGroup.h"
#include "afxwin.h"

// CRadioGroup dialog

class CRadioGroup : public CMyControlGroup {
	DECLARE_DYNAMIC(CRadioGroup)

public:
	CRadioGroup(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRadioGroup();

	// Dialog Data
	enum { IDD = IDD_RADIO_GROUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedRadio(UINT nID);

private:
	map<uint8_t, CButton> mmRadio;
	uint8_t LastVal;
public:
	void SetValue(uint8_t value);

protected:
	afx_msg LRESULT OnMessageUpdateui(WPARAM wParam, LPARAM lParam);
};
