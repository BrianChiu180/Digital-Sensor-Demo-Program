#pragma once
#include "afxwin.h"


// About ��ܤ��

class CAbout : public CDialogEx
{
	DECLARE_DYNAMIC(CAbout)

public:
	CAbout(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CAbout();

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

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
