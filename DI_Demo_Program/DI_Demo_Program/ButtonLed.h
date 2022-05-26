#pragma once
#include "afxbutton.h"
#include "afxwin.h"
#include "MyControlGroup.h"

// BTN_LED dialog

class CButtonLED : public CMyControlGroup {
	DECLARE_DYNAMIC(CButtonLED)

public:
	CButtonLED(CWnd* pParent = NULL);   // standard constructor
	virtual ~CButtonLED();

	enum 
	{
		IDD = IDD_LED, 
		IDD2 = IDD_MINILED
	};

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	/* LED_inactive_active*/
	enum LED_Style {
		LED_Gray_R,
		LED_Gray_G,
		LED_R_G,
		LED_G_R
	};

	virtual BOOL OnInitDialog();
	void SetStyle(enum LED_Style style = LED_Gray_R);
	void SetText(CString csText = _T(""));
	void SetLEDStatus(BOOL bStatus = false);

private:
	CMFCButton mLED;
	CStatic mText;
	BOOL bOldStatus;
	CFont mFontLabel;

	HICON icon_g, icon_r, icon_gary;
	int size;

public:
	virtual BOOL DestroyWindow();
protected:
	afx_msg LRESULT OnMessageUpdateui(WPARAM wParam, LPARAM lParam);
};
