// I2CDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "I2CDlg.h"
#include "afxdialogex.h"
#include <regex>

// CI2CDlg 對話方塊

IMPLEMENT_DYNAMIC(CI2CDlg, CDialogEx)

CI2CDlg::CI2CDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_I2C, pParent)
{

}

CI2CDlg::~CI2CDlg()
{
}

void CI2CDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mShowArea);
	DDX_Control(pDX, IDC_EDIT2, mCmdArea);
	DDX_Control(pDX, IDC_BUTTON1, mBtnClr);
}


BEGIN_MESSAGE_MAP(CI2CDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CI2CDlg::OnClickedClear)
END_MESSAGE_MAP()

BOOL CI2CDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	LOGFONT lFont;
	GetFont()->GetLogFont(&lFont);
	lstrcpy(lFont.lfFaceName, _T("Calibri"));
	lFont.lfHeight -= 6;
	mFontLabel.CreateFontIndirect(&lFont);
	mCmdArea.SetFont(&mFontLabel);
	lFont.lfWeight += 200;
	mShowArea.SetFont(&mFontLabel);

	ShowHelpMessage();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX 屬性頁應傳回 FALSE
}


BOOL CI2CDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam) {
		case VK_ESCAPE:
			return false;
		case VK_RETURN:
			if (pMsg->hwnd == mCmdArea.m_hWnd)
			{
				CmdFormatCheck();
			}
			return false;
		case VK_UP:
			if (cmdHistory.size() > 0)
			{
				if (iter_history != cmdHistory.begin())
				{
					iter_history--;
					mCmdArea.SetWindowTextW(*iter_history);
					mCmdArea.SetFocus();
					mCmdArea.SetSel(-1);
				}
			}
			return false;
		case VK_DOWN:
			if (cmdHistory.size() > 0)
			{
				if (iter_history != (cmdHistory.end()-1))
				{
					iter_history++;
					mCmdArea.SetWindowTextW(*iter_history);
					mCmdArea.SetFocus();
					mCmdArea.SetSel(-1);
				}
			}
			return false;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CI2CDlg::CmdFormatCheck()
{
	uint8_t result = STATUS_OK;
	CString csCmd;
	CString csShow;
	CString csTemp;
	string sTemp;
	uint8_t SlaveID, Address;
	uint16_t DataNum;
	vector<CString> csData;
	vector<uint8_t> u8Temp(2000);
	regex reg("[0-9xa-fA-F]*");
	smatch m;
	ssub_match sm;

	mCmdArea.GetWindowTextW(csCmd);

	if (csCmd.IsEmpty())
		return;

	if (cmdHistory.size() > 0)
	{
		if (csCmd != *cmdHistory.rbegin())
			cmdHistory.push_back(csCmd);
	}
	else
		cmdHistory.push_back(csCmd);

	iter_history = cmdHistory.end();
//	csCmd.MakeUpper();
	
	if (csCmd.FindOneOf(_T("rRwWiIsS//")) == 0)
	{
		csTemp = csCmd.GetAt(0);
		csCmd = csCmd.Mid(2);
		sTemp = CT2A(csCmd);
		if (csTemp.FindOneOf(_T("rR")) == 0)
		{
			while (regex_search(sTemp, m, reg))
			{
				for (auto &match : m) {
					sm = match;
					csTemp = sm.str().c_str();
					csData.push_back(csTemp);
				}
				sTemp = m.suffix().str();
				if (sTemp.size() > 0)
					sTemp.erase(0, 1);
				else
					break;
			}

			if (csData.size() == 3)
			{
				SlaveID = (uint8_t)wcstol(csData[0], NULL, 0);
				Address = (uint8_t)wcstol(csData[1], NULL, 0);
				DataNum = (uint16_t)wcstol(csData[2], NULL, 0);
				result = I2CRead(0, SlaveID, Address, u8Temp.data(), DataNum, 0, 0, 1000);
				mCmdArea.GetWindowTextW(csTemp);
				if (result != STATUS_OK)
					csTemp = _T("\r\nNo Ack\r\n");
				else
				{
					csTemp += _T("\r\nData:\t");
					for (int i = 0; i < DataNum; i++)
					{
						csTemp.Format(_T("%s 0x%02X"), csTemp.GetString(), u8Temp[i]);
						if ((i + 1) % 16 == 0)
						{
							csTemp += _T("\r\n\t");
						}
					}
				}
				ShowAreaAddString(csTemp);
			}
			else
			{
				ShowAreaAddString(_T("Please check your format\r\nThe I2C Read Format is: R SlaveID Address Numbers"));
			}
		}
		else if (csTemp.FindOneOf(_T("wW")) == 0)
		{
			while (regex_search(sTemp, m, reg))
			{
				for (auto &match : m) {
					sm = match;
					csTemp = sm.str().c_str();
					csData.push_back(csTemp);
				}
				sTemp = m.suffix().str();
				if (sTemp.size() > 0)
					sTemp.erase(0, 1);
				else
					break;
			}

			if (csData.size() > 2)
			{
				SlaveID = (uint8_t)wcstol(csData[0], NULL, 0);
				Address = (uint8_t)wcstol(csData[1], NULL, 0);
				u8Temp.clear();
				for (size_t i = 2; i < csData.size(); i++)
				{
					u8Temp.push_back((uint8_t)wcstol(csData[i], NULL, 0));
				}

				result = I2CWrite(0, SlaveID, Address, u8Temp.data(), (uint8_t)u8Temp.size());

				mCmdArea.GetWindowTextW(csTemp);
				ShowAreaAddString(csTemp);
			}
			else
			{
				ShowAreaAddString(_T("Please check your format\r\nThe I2C Write Format is: W SlaveID Address Data0 Data1 ... DataN"));
			}
		}
		else if (csTemp.FindOneOf(_T("iI")) == 0)
		{
			int i = 0;
			mCmdArea.GetWindowTextW(csTemp);
			Address = 0x00;
			DataNum = 1;
			for (SlaveID = 0; SlaveID <= 0x7F; SlaveID++)
			{
				result = I2CRead(0, SlaveID, Address, u8Temp.data(), DataNum, 0, 0, 1000);
				if (result == STATUS_OK)
				{
					if(i == 0)
						csTemp = _T("\r\nDevice ID:\t");

					csTemp.Format(_T("%s 0x%02X"), csTemp.GetString(), SlaveID);
					i++;
					if (i % 16 == 0)
					{
						csTemp += _T("\r\n\t");
					}
				}
			}
			if(i == 0)
				csTemp = _T("\r\nNo Device on Bus\r\n");
			ShowAreaAddString(csTemp);
		}
		else if (csTemp.FindOneOf(_T("sS")) == 0)
		{
			while (regex_search(sTemp, m, reg))
			{
				for (auto &match : m) {
					sm = match;
					csTemp = sm.str().c_str();
					csData.push_back(csTemp);
				}
				sTemp = m.suffix().str();
				if (sTemp.size() > 0)
					sTemp.erase(0, 1);
				else
					break;
			}

			if (csData.size() > 0)
			{
				mCmdArea.GetWindowTextW(csTemp);
				for (size_t i = 0; i < csData.size(); i++)
				{
					SlaveID = (uint8_t)wcstol(csData[i], NULL, 0);
					result = I2CReadScan(0, SlaveID, 0x00, u8Temp.data(), 256, 0, 0, 2000);
					if (result != STATUS_OK)
					{
						csTemp.Format(_T("\r\nDevice ID 0x%02X No Ack!\r\n"), SlaveID);
					}
					else
					{
						csTemp.Format(_T("\r\nDevice ID: 0x%02X\r\n"), SlaveID);
						for (uint8_t j = 0; j < 16; j++)
						{
							csTemp.Format(_T("%s0x%XX => "),csTemp.GetString(), j);
							for (uint8_t k = 0; k < 16; k++)
							{
								csTemp.Format(_T("%s 0x%02X"), csTemp.GetString(), u8Temp[k+j*16]);
							}
							csTemp += _T("\r\n");
						}
						csTemp += _T("\r\n");
					}
				}

				ShowAreaAddString(csTemp);
			}
			else
			{
				ShowAreaAddString(_T("Please check your format\r\nThe I2C Scan Format is: S SlaveID1 SlaveID2 ... SlaveIDN\r\n"));
			}

		}
		else if (csTemp.FindOneOf(_T("//")) == 0)
		{

		}
	}
	mCmdArea.SetWindowTextW(_T(""));
}


void CI2CDlg::ShowAreaAddString(CString csTemp)
{
	int lineCount = 0;
	CString csShow;

	mShowArea.GetWindowTextW(csShow);
	csShow += _T("\r\n");
	csShow += csTemp;
	csShow += _T("\r\n");
	mShowArea.SetWindowTextW(csShow);

	lineCount = mShowArea.GetLineCount();
	mShowArea.LineScroll(lineCount);
}


void CI2CDlg::OnClickedClear()
{
	mShowArea.SetWindowTextW(_T(""));
}


void CI2CDlg::ShowHelpMessage()
{
	CString csTemp;

	csTemp =	_T("Command List\r\n");
	csTemp +=	_T("========================================\r\n");
	csTemp +=	_T(" I2C Read:\r\n");
	csTemp +=	_T(" R SlaveID Address Num\r\n");
	csTemp +=	_T("\r\n");
	csTemp +=	_T(" I2C Write:\r\n");
	csTemp +=	_T(" W SlaveID Address Data0 Data1 ... DataN\r\n");
	csTemp +=	_T(" \r\n");
	csTemp +=	_T(" Scan I2C Bus:\r\n");
	csTemp +=	_T(" I\r\n");
	csTemp +=	_T(" \r\n");
	csTemp +=	_T(" Scan I2C Device Reg Table:\r\n");
	csTemp +=	_T(" S SlaveID1 SlaveID2 ... SlaveIDN\r\n");
	csTemp +=	_T("========================================\r\n");

	mShowArea.SetWindowTextW(csTemp);
}


BOOL CI2CDlg::DestroyWindow()
{
	mFontLabel.DeleteObject();

	return CDialogEx::DestroyWindow();
}
