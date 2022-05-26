// About.cpp : ¹ê§@ÀÉ
//

#include "stdafx.h"
#include "About.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CAbout, CDialogEx)

CAbout::CAbout(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ABOUT, pParent)
{
}

CAbout::~CAbout()
{
}

void CAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_Version, mVersion);
	DDX_Control(pDX, IDC_STATIC_COPY, mCopy);
	DDX_Control(pDX, IDC_LOGO_ICON, mLogo);

	DDX_Control(pDX, IDC_MFCLINK_AUTHOR, mAuthor);
	DDX_Control(pDX, IDC_MFCLINK_SALES, mSales);
	DDX_Control(pDX, IDC_MFCLINK_WEBSITE, mWebsite);
}


BEGIN_MESSAGE_MAP(CAbout, CDialogEx)
END_MESSAGE_MAP()


BOOL CAbout::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	HINSTANCE hInst = AfxGetResourceHandle();

#ifdef _ICON_CUSTOM_1
	HICON icon_logo = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_CUSTOM1), IMAGE_ICON, 64, 64, 0);
	HICON icon_logo2 = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_CUSTOM1), IMAGE_ICON, 128, 128, 0);
	mAuthor.ShowWindow(HIDE_WINDOW);
	mSales.ShowWindow(HIDE_WINDOW);
	mWebsite.ShowWindow(HIDE_WINDOW);
#else
	HICON icon_logo = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_LOGO), IMAGE_ICON, 64, 64, 0);
	HICON icon_logo2 = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_LOGO), IMAGE_ICON, 128, 128, 0);
#endif // _ICON_CUSTOM_1


	this->SetIcon(icon_logo, TRUE);
	mLogo.SetIcon(icon_logo2);

	DWORD  verHandle = 0;
	UINT   size = 0;
	LPBYTE lpBuffer = NULL;
	CString szVersionFile;
	GetModuleFileName(NULL, szVersionFile.GetBufferSetLength(512), 512);
	szVersionFile.ReleaseBuffer();
	DWORD  verSize = GetFileVersionInfoSize(szVersionFile, &verHandle);
	CString csVer;

	if (verSize != NULL)
	{
		LPSTR verData = new char[verSize];

		if (GetFileVersionInfo(szVersionFile, 0, verSize, verData))
		{
			if (VerQueryValueA(verData, "\\", (VOID FAR* FAR*)&lpBuffer, &size))
			{
				if (size)
				{
					VS_FIXEDFILEINFO *verInfo = (VS_FIXEDFILEINFO *)lpBuffer;
					if (verInfo->dwSignature == 0xfeef04bd)
					{
#ifdef _ICON_CUSTOM_1
						csVer.Format(_T("JingWei Demo Program Version : %d.%d.%d.%d"),
#else
						csVer.Format(_T("Dyna-Image Demo Program Version : %d.%d.%d.%d"),
#endif
							HIWORD(verInfo->dwFileVersionMS),
							LOWORD(verInfo->dwFileVersionMS),
							HIWORD(verInfo->dwFileVersionLS),
							LOWORD(verInfo->dwFileVersionLS)
						);

						mVersion.SetWindowTextW(csVer);
					}
				}
			}
		}
		delete[] verData;
	}

#ifdef _ICON_CUSTOM_1
	mCopy.SetWindowTextW(_T("Copyright (C) 2017 JingWei Electronic Technology CO., LTD. All rights reserved."));
#else
	mCopy.SetWindowTextW(_T("Copyright (C) 2017 Dyna-Image Corp. All rights reserved."));
#endif
	return TRUE;
}


BOOL CAbout::DestroyWindow()
{
	return CDialogEx::DestroyWindow();
}
