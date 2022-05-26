#pragma once
#include "afxwin.h"
#include "MyControlGroup.h"

// CTextGroup dialog

class CTextGroup : public CMyControlGroup {
	DECLARE_DYNAMIC(CTextGroup)

public:
	CTextGroup(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTextGroup();

	// Dialog Data
	enum { IDD = IDD_TEXT_GROUP };
	CFont mFontLabel;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void SetName(CString group, CString text);
	void SetValue(int value);
	void SetValue(double value);

protected:
	afx_msg LRESULT OnMessageUpdateui(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageChangeScale(WPARAM wParam, LPARAM lParam);
private:
	CStatic mText;

	int LastVal;
	double AvgSum, dLastVal;
	deque<int> idequeVal;
	deque<double> ddequeVal;

public:
	virtual BOOL DestroyWindow();
protected:
	afx_msg LRESULT OnMessageUpdateInfo(WPARAM wParam, LPARAM lParam);
};
