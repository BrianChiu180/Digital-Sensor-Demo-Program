// BTN_LED.cpp : implementation file
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "ButtonLed.h"


// BTN_LED dialog

IMPLEMENT_DYNAMIC(CButtonLED, CMyControlGroup)

CButtonLED::CButtonLED(CWnd* pParent /*=NULL*/)
	: CMyControlGroup(CButtonLED::IDD, pParent),size(0), bOldStatus(FALSE), icon_g(NULL), icon_r(NULL), icon_gary(NULL){

}

CButtonLED::~CButtonLED() {
}

void CButtonLED::DoDataExchange(CDataExchange* pDX) {
	CMyControlGroup::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCBUTTON1, mLED);
	DDX_Control(pDX, IDC_STATIC1, mText);
}


BEGIN_MESSAGE_MAP(CButtonLED, CMyControlGroup)
	ON_MESSAGE(WM_MESSAGE_UPDATEUI, &CButtonLED::OnMessageUpdateui)
END_MESSAGE_MAP()


// BTN_LED message handlers


BOOL CButtonLED::OnInitDialog() {
	CMyControlGroup::OnInitDialog();

	CRect rect;

	mLED.GetClientRect(&rect);

	TRACE(_T("rect.Width() %d\n"), rect.Width());

	if (rect.Width() >= 128)		size = 128;
	else if (rect.Width() >= 96)	size = 96;
	else if (rect.Width() >= 80)	size = 80;
	else if (rect.Width() >= 72)	size = 72;
	else if (rect.Width() >= 64)	size = 64;
	else if (rect.Width() >= 48)	size = 48;
	else if (rect.Width() >= 32)	size = 32;
	else if (rect.Width() >= 24)	size = 24;
	else 						size = 16;

	HINSTANCE hInst = AfxGetResourceHandle();
	icon_g = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_LED_G), IMAGE_ICON, size, size, 0);
	icon_r = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_LED_R), IMAGE_ICON, size, size, 0);
	icon_gary = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_LED_Gray), IMAGE_ICON, size, size, 0);

	mLED.SetImage(icon_gary);
	mLED.SetCheckedImage(icon_r);

	bOldStatus = FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CButtonLED::SetStyle(enum LED_Style style) {
	switch (style)
	{
	case LED_Gray_R:
		mLED.SetImage(icon_gary);
		mLED.SetCheckedImage(icon_r);
		break;
	case LED_Gray_G:
		mLED.SetImage(icon_gary);
		mLED.SetCheckedImage(icon_g);
		break;
	case LED_R_G:
		mLED.SetImage(icon_r);
		mLED.SetCheckedImage(icon_g);
		break;
	case LED_G_R:
		mLED.SetImage(icon_g);
		mLED.SetCheckedImage(icon_r);
		break;
	}
}

void CButtonLED::SetText(CString csText) {
	mLED.m_bGrayDisabled = false;
	mLED.m_bHighlightChecked = false;
	mLED.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;

	LOGFONT lFont;
	memset(&lFont, 0, sizeof(LOGFONT));
	lstrcpy(lFont.lfFaceName, _T("Calibri"));
	if (size < 48)
		lFont.lfHeight = 17;
	else
		lFont.lfHeight = 22;

	if (size < 48 && csText.GetLength() > 4)
		lFont.lfHeight -= (int)((csText.GetLength() - 4) * 2.5);
	else if(csText.GetLength() > 5)
		lFont.lfHeight -= ((csText.GetLength() - 5) * 2);		

	lFont.lfItalic = 1;

	mFontLabel.CreateFontIndirect(&lFont);
	mText.SetFont(&mFontLabel);

	mText.SetWindowTextW(csText);	
}

void CButtonLED::SetLEDStatus(BOOL bStatus) {
	if (bOldStatus != bStatus)
	{
		bOldStatus = bStatus;
		mLED.SetCheck(bStatus);
	}
}

BOOL CButtonLED::DestroyWindow() {
	mFontLabel.DeleteObject();
	DestroyIcon(icon_g);
	DestroyIcon(icon_r);
	DestroyIcon(icon_gary);

	return CMyControlGroup::DestroyWindow();
}

afx_msg LRESULT CButtonLED::OnMessageUpdateui(WPARAM wParam, LPARAM lParam) {
	uint8_t value;

	value = GetBitValue();

	SetLEDStatus(value > 0);

	return 0;
}
