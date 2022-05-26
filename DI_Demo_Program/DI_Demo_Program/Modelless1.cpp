// Modelless1.cpp : implementation file
//

#include "stdafx.h"
#include "Modelless1.h"
#include "afxdialogex.h"

// CModelless1 dialog

IMPLEMENT_DYNAMIC(CModelless1, CDialogEx)

CModelless1::CModelless1(CWnd* pParent /*=NULL*/)
	: CDialogEx(CModelless1::IDD, pParent), 
	mToolTip(NULL), pBitDetail(NULL), pCtrlDetail(NULL), pCtrlInfo(NULL), pDieDetail(NULL), pRegTable(NULL)
{

}

void CModelless1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModelless1, CDialogEx)
	ON_MESSAGE(WM_MESSAGE_UPDATEUI, &CModelless1::OnMessageUpdateui)
	ON_MESSAGE(WM_MESSAGE_CHANGE_AVG_NUM, &CModelless1::OnMessageChangeAvgNum)
	ON_MESSAGE(WM_MESSAGE_CHANGE_RANGE, &CModelless1::OnMessageChangeRange)
	ON_MESSAGE(WM_MESSAGE_CHANGE_SCALE, &CModelless1::OnMessageChangeScale)
END_MESSAGE_MAP()


// CModelless1 message handlers


BOOL CModelless1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	pairINT nID;
	int x, y;
	int incre[2] = { 0 };
	CRect rc, rc2;

	auto iter = pCtrlInfo->CtrlDetail.begin();

	size_t CtrlSize = pCtrlInfo->CtrlDetail.size();

	while (iter != pCtrlInfo->CtrlDetail.end())
	{
		pCtrlDetail = &iter->second;
		nID = iter->first;
		x = nID.first;
		y = nID.second;

		switch (pCtrlDetail->CtrlType)
		{
		case PROGRESSBAR:
			mBar[nID].CtrlInit(pDieDetail, pCtrlDetail, mToolTip);
			mBar[nID].Create(mBar[nID].IDD, this);
			mBar[nID].GetClientRect(rc);
			mBar[nID].SetWindowPos(NULL, 7 + x * incre[0], 7, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW);

			if (pCtrlDetail->CtrlName.first == _T(""))
				mBar[nID].SetName(pCtrlDetail->BitMapping.at(0));
			else
				mBar[nID].SetName(pCtrlDetail->CtrlName.first);

			break;
		case TEXT_GROUP:
			mText[nID].CtrlInit(pDieDetail, pCtrlDetail, mToolTip);
			mText[nID].Create(mText[nID].IDD, this);
			mText[nID].GetClientRect(rc);
			mText[nID].SetWindowPos(NULL, 7, 7 + y * incre[1], 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW);
			break;
		}

		if (iter == pCtrlInfo->CtrlDetail.begin())
		{
			int width = 0;
			int height = 0;

			switch (pCtrlDetail->CtrlType)
			{
			case PROGRESSBAR:
				mBar.at(nID).GetWindowRect(&rc);
				width = CtrlSize * (rc.Width() + (CtrlSize > 1 ? 10 : 7)) + 7;
				height = rc.Height() + 10;
				break;
			case TEXT_GROUP:
				mText.at(nID).GetWindowRect(&rc);
				width = rc.Width() + 10;
				height = CtrlSize * (rc.Height() + (CtrlSize > 1 ? 10 : 7)) + 7;
				break;
			}

			this->GetWindowRect(&rc);
			this->GetClientRect(&rc2);

			width += (rc.Width() - rc2.Width());
			height += (rc.Height() - rc2.Height());
			this->SetWindowPos(NULL, 0, 0, width, height, SWP_NOMOVE);

			this->GetClientRect(&rc);
			incre[0] = rc.Width() / CtrlSize;
			incre[1] = rc.Height() / CtrlSize;
		}
		++iter;
	}

	this->SetWindowTextW(csName);

	return TRUE;
}

BOOL CModelless1::DestroyWindow()
{
	CustomDestroy(mBar);
	CustomDestroy(mText);

	return CDialogEx::DestroyWindow();
}


afx_msg LRESULT CModelless1::OnMessageUpdateui(WPARAM wParam, LPARAM lParam)
{
	CustomMessage(mBar, WM_MESSAGE_UPDATEUI, wParam, lParam, wParam > 0);
	CustomMessage(mText, WM_MESSAGE_UPDATEUI, wParam, lParam, wParam > 0);

	return 0;
}


afx_msg LRESULT CModelless1::OnMessageChangeAvgNum(WPARAM wParam, LPARAM lParam)
{
	CustomMessage(mBar, WM_MESSAGE_CHANGE_AVG_NUM, wParam, lParam);
	CustomMessage(mText, WM_MESSAGE_CHANGE_AVG_NUM, wParam, lParam);

	return 0;
}


afx_msg LRESULT CModelless1::OnMessageChangeRange(WPARAM wParam, LPARAM lParam)
{
	CustomMessage(mBar, WM_MESSAGE_CHANGE_RANGE, wParam, lParam);

	return 0;
}

afx_msg LRESULT CModelless1::OnMessageChangeScale(WPARAM wParam, LPARAM lParam)
{
	CustomMessage(mText, WM_MESSAGE_CHANGE_SCALE, wParam, lParam);
	return 0;
}
