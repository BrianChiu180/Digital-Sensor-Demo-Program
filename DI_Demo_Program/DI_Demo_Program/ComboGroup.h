#pragma once
#include "afxwin.h"
#include "MyControlGroup.h"

// CComboText dialog

class CComboGroup : public CMyControlGroup {
	DECLARE_DYNAMIC(CComboGroup)

public:
	CComboGroup(CWnd* pParent = NULL);   // standard constructor
	virtual ~CComboGroup();

	// Dialog Data
	enum { IDD = IDD_COMBO_GROUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CFont mFontLabel;

	void CtrlInit(CDieDetail* pDie, CCtrlDetail* pCtrl, CToolTipCtrl* pToolTip);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();

	void SetName(CString name);
private:
	CComboBox mCombo;
	CStatic mValue;

	map<CString, uint8_t> rmap_Item;
	map<uint8_t, int> mapComboItem;
	uint8_t LastVal;

	void CComboGroup::AddString(void);
	void CComboGroup::ReMapping(void);
public:
	void SetValue(int value);
	uint8_t SetTextBySel();
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg LRESULT OnMessageUpdateui(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageChangeNameMapping(WPARAM wParam, LPARAM lParam);
};
