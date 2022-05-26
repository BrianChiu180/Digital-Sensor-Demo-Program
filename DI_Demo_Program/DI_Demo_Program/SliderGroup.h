#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "MyControlGroup.h"

// CSliderGroup dialog

class CSliderGroup : public CMyControlGroup {
	DECLARE_DYNAMIC(CSliderGroup)

public:
	CSliderGroup(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSliderGroup();

	// Dialog Data
	enum { IDD = IDD_SLIDER_GROUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void OnOK() {}

	void SetValue(int value);
private:
	CSliderCtrl mSlider;

	int LastVal;
public:
	afx_msg void OnReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult);

protected:
	afx_msg LRESULT OnMessageUpdateui(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageChangeRange(WPARAM wParam, LPARAM lParam);
};
