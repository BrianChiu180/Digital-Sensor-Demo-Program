#pragma once
#include "afxwin.h"
#include "Define.h"


// CI2CDlg 對話方塊

class CI2CDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CI2CDlg)

public:
	CI2CDlg(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CI2CDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_I2C };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	CEdit mShowArea;
	CEdit mCmdArea;
	CButton mBtnClr;
	CFont mFontLabel;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();

	afx_msg void OnClickedClear();

private:
	void ShowAreaAddString(CString csTemp);
	void ShowHelpMessage();
	void CmdFormatCheck();

	vector<CString> cmdHistory;
	vector<CString>::iterator iter_history;
public:
	virtual BOOL DestroyWindow();
};
