#pragma once
#include "afxwin.h"


// About 對話方塊

class CAbout : public CDialogEx
{
	DECLARE_DYNAMIC(CAbout)

public:
	CAbout(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CAbout();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CStatic mVersion;
	CStatic mCopy;
	CStatic mLogo;
	virtual BOOL DestroyWindow();
	CMFCLinkCtrl mAuthor;
	CMFCLinkCtrl mSales;
	CMFCLinkCtrl mWebsite;
};
