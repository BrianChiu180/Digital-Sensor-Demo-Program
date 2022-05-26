#pragma once
#include "afxcmn.h"
#include "afxbutton.h"
#include "afxdialogex.h"
#include "DI_Sensor.h"
#include "MyControlGroup.h"
#include "PageST1.h"
#include "ButtonLed.h"
#include "Modelless1.h"
#include "Modelless_List.h"
#include "SelSensor.h"
#include "I2CDlg.h"
#include "About.h"
#include "afxwin.h"


// CDIDemoProgramDlg dialog

class CDIDemoProgramDlg : public CDialogEx {
	DECLARE_DYNAMIC(CDIDemoProgramDlg)

public:
	CDIDemoProgramDlg(CWnd* pParent = NULL); // standard constructor
	~CDIDemoProgramDlg() {};
	// Dialog Data
	enum { IDD = IDD_DIDemoProgramDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD_PTR dwData);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangingTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedOpen();
	afx_msg void OnClickedButtonLOG();
	afx_msg void OnClickedRun();
	afx_msg void OnClickedReload();
	afx_msg void OnClickedSave();
	afx_msg void OnClickedI2CTool();
private:
	HDEVNOTIFY m_HDevNotify;
	CString SensorName;
	uint16_t SensorVersion;
	uint8_t SensorAddress;

	CFile	mLogFile;
	CString csLOGFileName;
	CString csINIFileName;

	CDieDetail* pDieDetail;
	map<CString/* Bit Name */, CBitDetail>* pBitDetailMap;
	map<uint8_t, CRegInfo>*		pRegInfoMap;
	CBitDetail*	pBitDetail;
	CRegisterTable* pRegTable;
	CRegInfo*		pRegInfo;

	CButton mBtnLOG;
	CButton mBtn_I2C;
	CMFCButton mLogo;
	CMFCButton mBtnOpen;
	CMFCButton mBtnSave;
	CMFCButton mBtnRun;
	CMFCButton mBtnReload;
	CStatusBar mStatusBar;
	CEdit mAvgNum;

	CDI_Sensor DI_Sensor;
	CSensorInfo* pSensorInfo;
	CTabCtrl mTab;
	map<int, CPageST1> mmTabPage;
	map<int, CButtonLED> mmButtonLED;
	map<int, CModelless1> mmModelLess;
	map<int, CModelless_List> mmModelLess_List;

	CStatic mGroup;
	CString hidName;
	uint8_t hidNum;
	uint32_t LastAvgNum;
	BOOL bLoopRead;
	BOOL bLogEnable;
	BOOL bDetectSensor;
	uint32_t ConversionTime;
	double PowerConsumption;

	CCtrlDetail* pCtrlDetail_Cali;
	BOOL bCalibration;
	BOOL bSLActive;										//!< LEO added for checking whether Sun Light suppression active
	deque<int> dequeCali;
	double CaliSum;

	double LogTimer;

	void SensorInitial();
	void Log2File();
	void SetLoopRead();
	void CloseLoopRead();
	void LoadINIFile();
	void SaveINIFile();
	void DestroyCtrl();

	enum {
		GetDataTime,
		CheckSensorTime
	};

public:
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CToolTipCtrl* mToolTip;

protected:
	afx_msg LRESULT OnMessageUpdateui(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageChangeSelData(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageChangeRange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageReloadReg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageChangeConversionTime(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageCalibration(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClickedAbout();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	virtual BOOL DestroyWindow();
	afx_msg LRESULT OnMessageUpdateInfo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageCalculatePower(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageChangeScale(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageChangeNameMapping(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageAutoDac(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMessageSLSuppression(WPARAM wParam, LPARAM lParam);
};
