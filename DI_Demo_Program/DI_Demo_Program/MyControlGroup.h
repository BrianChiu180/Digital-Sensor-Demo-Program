#pragma once
#include "afxdialogex.h"
#include "Define.h"

class CMyControlGroup :
	public CDialogEx {
	DECLARE_DYNAMIC(CMyControlGroup)
public:
	CMyControlGroup(UINT nIDTemplate, CWnd* pParent = NULL);
	~CMyControlGroup();
	void CtrlInit(CDieDetail* pDie, CCtrlDetail* pCtrl, CToolTipCtrl* pToolTip);
	void CtrlInit(CCtrlDetail* pCtrl, CToolTipCtrl* pToolTip);
	uint8_t CtrlWrite();
	uint8_t CtrlWrite(uint8_t value, bool bUsedRegMap = false);
	uint8_t CtrlWrite(uint32_t value);
	void SetName(CString name);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	uint8_t				DevID;
	vector<uint8_t*>	pRegCurVal;
	CDieDetail*			pDieDetail;
	CCtrlDetail*		pCtrlDetail;
	CRegisterTable*		pRegTable;
	CRegInfo*			pRegInfo;
	CBitDetail*			pBitDetail;
	CBitDetail*			pBitDetail0;
	CLuxCalculate*		pLuxCalculate;
	CCCTCaculate*		pCCTCalculate;

	map<CString, CBitDetail>*	pBitDetailMap;
	map<uint8_t, CRegInfo>*		pRegInfoMap;
	map<uint8_t, CString>*		pBitMapping;
	map<uint8_t, CString>*		pListName;
	map<pair<uint8_t, uint8_t>, CString>* pListName2;

	pair<int, int> CtrlRange;
	uint32_t DefaultVal;
	pair<COLORREF, COLORREF> CtrlColor;	//postive, negtive

	CStatic mGroup;
	CEdit mEdit;
	CStatic mValueDec;
	CStatic mValueHex;
	CToolTipCtrl* mToolTip;
	uint32_t AvgNum;
	double CtrlScale;

	virtual void OnOK();
	virtual void OnCancel();

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	void SetEditText(uint32_t value);
	void SetStaticDecHexText(uint32_t value);
	virtual BOOL DestroyWindow();
	int32_t GetRegValue();
	int32_t GetRegValue(uint8_t RegAddr, CString BitName = _T(""));
	int32_t GetRegValue(CString BitName);
	uint8_t GetBitValue();
	uint8_t GetBitValue(CString BitName);
	int32_t GetLux();
	int32_t GetCCT();
	double	GetAxis();

protected:
	afx_msg LRESULT OnMessageChangeAvgNum(WPARAM wParam, LPARAM lParam);
};

