// DIDemoProgramDlg.cpp : implementation file
//

#include "stdafx.h"
#include <dbt.h>
#include <hidsdi.h>
#include "DIDemoProgramDlg.h"
#include "AtmelHIDLIB.h"

static UINT indicators[] = {
	ID_INDICATOR_STATUS,
	ID_INDICATOR_SENSOR,
	ID_INDICATOR_CONV_TIME,
	ID_INDICATOR_POWER_CONSUMPTION,
	//ID_INDICATOR_SL_SUPPRESSION
};

IMPLEMENT_DYNAMIC(CDIDemoProgramDlg, CDialogEx)

CDIDemoProgramDlg::CDIDemoProgramDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDIDemoProgramDlg::IDD, pParent), CaliSum(0), ConversionTime(0), LastAvgNum(0), LogTimer(0), PowerConsumption(0),
	SensorAddress(0), SensorVersion(0), bCalibration(FALSE), bDetectSensor(FALSE), bLogEnable(FALSE), bLoopRead(FALSE),
	hidNum(0), mToolTip(NULL), m_HDevNotify(NULL),
	pBitDetail(NULL), pBitDetailMap(NULL), pCtrlDetail_Cali(NULL), pDieDetail(NULL),
	pRegInfo(NULL), pRegInfoMap(NULL), pRegTable(NULL), pSensorInfo(NULL) 
{

}

void CDIDemoProgramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, mTab);
	DDX_Control(pDX, IDC_MFCBUTTON1, mLogo);
	DDX_Control(pDX, IDC_MFCBUTTON2, mBtnOpen);
	DDX_Control(pDX, IDC_MFCBUTTON3, mBtnSave);
	DDX_Control(pDX, IDC_MFCBUTTON4, mBtnRun);
	DDX_Control(pDX, IDC_MFCBUTTON5, mBtnReload);
	DDX_Control(pDX, IDC_GROUP1, mGroup);
	DDX_Control(pDX, IDC_EDIT1, mAvgNum);
	DDX_Control(pDX, IDC_BUTTON1, mBtnLOG);
	DDX_Control(pDX, IDC_BUTTON2, mBtn_I2C);
}

BEGIN_MESSAGE_MAP(CDIDemoProgramDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_TIMER()
	ON_WM_DEVICECHANGE()
	ON_WM_CTLCOLOR()
	ON_MESSAGE(WM_MESSAGE_UPDATEUI, &CDIDemoProgramDlg::OnMessageUpdateui)
	ON_MESSAGE(WM_MESSAGE_CHANGE_SEL_DATA, &CDIDemoProgramDlg::OnMessageChangeSelData)
	ON_MESSAGE(WM_MESSAGE_CHANGE_RANGE, &CDIDemoProgramDlg::OnMessageChangeRange)
	ON_MESSAGE(WM_MESSAGE_RELOAD_REG, &CDIDemoProgramDlg::OnMessageReloadReg)
	ON_MESSAGE(WM_MESSAGE_CHANGE_CONVERSION_TIME, &CDIDemoProgramDlg::OnMessageChangeConversionTime)
	ON_MESSAGE(WM_MESSAGE_CALIBRATION, &CDIDemoProgramDlg::OnMessageCalibration)
	ON_MESSAGE(WM_MESSAGE_CALCULATE_POWER, &CDIDemoProgramDlg::OnMessageCalculatePower)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CDIDemoProgramDlg::OnSelchangeTab)
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB, &CDIDemoProgramDlg::OnSelchangingTab)
	ON_BN_CLICKED(IDC_MFCBUTTON2, &CDIDemoProgramDlg::OnClickedOpen)
	ON_BN_CLICKED(IDC_BUTTON1, &CDIDemoProgramDlg::OnClickedButtonLOG)
	ON_BN_CLICKED(IDC_MFCBUTTON4, &CDIDemoProgramDlg::OnClickedRun)
	ON_BN_CLICKED(IDC_MFCBUTTON5, &CDIDemoProgramDlg::OnClickedReload)
	ON_BN_CLICKED(IDC_MFCBUTTON3, &CDIDemoProgramDlg::OnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON2, &CDIDemoProgramDlg::OnClickedI2CTool)
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CDIDemoProgramDlg::OnClickedAbout)
	ON_MESSAGE(WM_MESSAGE_UPDATE_INFO, &CDIDemoProgramDlg::OnMessageUpdateInfo)
	ON_MESSAGE(WM_MESSAGE_CHANGE_SCALE, &CDIDemoProgramDlg::OnMessageChangeScale)
	ON_MESSAGE(WM_MESSAGE_CHANGE_NAMEMAPPING, &CDIDemoProgramDlg::OnMessageChangeNameMapping)
	ON_MESSAGE(WM_MESSAGE_AUTO_DAC, &CDIDemoProgramDlg::OnMessageAutoDac)
	ON_MESSAGE(WM_MESSAGE_SL_SUPPRESSION, &CDIDemoProgramDlg::OnMessageSLSuppression)
END_MESSAGE_MAP()

BOOL CDIDemoProgramDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		pSysMenu->AppendMenuW(MF_SEPARATOR);	//< 分割線
		pSysMenu->AppendMenuW(MF_STRING, IDM_ABOUTBOX, _T("About"));
	}

	HINSTANCE hInst = AfxGetResourceHandle();
#ifdef _ICON_CUSTOM_1
	HICON icon_logo = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_CUSTOM1), IMAGE_ICON, 64, 64, 0);
#else
	HICON icon_logo = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_LOGO), IMAGE_ICON, 64, 64, 0);
#endif
	this->SetIcon(icon_logo, TRUE);	

	CRect rect;

	mToolTip = new CToolTipCtrl();
	mToolTip->Create(this);

	GetClientRect(&rect);

	mLogo.m_bHighlightChecked = FALSE;
	mLogo.m_bDrawFocus = FALSE;

	mBtnOpen.m_bHighlightChecked = FALSE;
	mBtnOpen.m_bDrawFocus = FALSE;

	mBtnSave.m_bHighlightChecked = FALSE;
	mBtnSave.m_bDrawFocus = FALSE;

	mBtnReload.m_bHighlightChecked = FALSE;
	mBtnReload.m_bDrawFocus = FALSE;

	mBtnRun.m_bHighlightChecked = FALSE;
	mBtnRun.m_bDrawFocus = FALSE;
	mBtnRun.m_nFlatStyle = mBtnRun.BUTTONSTYLE_NOBORDERS;
	mBtnRun.SetMouseCursor(LoadCursor(NULL, IDC_HAND));

	CRect rect_ctrl;

	mBtnRun.GetClientRect(&rect_ctrl);

	int size;

	if (rect_ctrl.Width() >= 128)		size = 128;
	else if (rect_ctrl.Width() >= 96)	size = 96;
	else if (rect_ctrl.Width() >= 80)	size = 80;
	else if (rect_ctrl.Width() >= 72)	size = 72;
	else if (rect_ctrl.Width() >= 64)	size = 64;
	else if (rect_ctrl.Width() >= 48)	size = 48;
	else if (rect_ctrl.Width() >= 32)	size = 32;
	else if (rect_ctrl.Width() >= 24)	size = 24;
	else 								size = 16;

	HICON icon_open = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_OPEN), IMAGE_ICON, size, size, 0);
	HICON icon_save = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_SAVE), IMAGE_ICON, size, size, 0);
	HICON icon_run = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_RUN), IMAGE_ICON, size, size, 0);
	HICON icon_stop = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_STOP), IMAGE_ICON, size, size, 0);
	HICON icon_reload = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_RELOAD), IMAGE_ICON, size, size, 0);
	HICON icon_disable = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_LED_Gray), IMAGE_ICON, size, size, 0);
	HICON icon_disable2 = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_LED_Gray), IMAGE_ICON, size, size, 0);
	HICON icon_disable3 = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_LED_Gray), IMAGE_ICON, size, size, 0);
	HICON icon_disable4 = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_LED_Gray), IMAGE_ICON, size, size, 0);

	mBtnOpen.SetImage(icon_open);
	mToolTip->AddTool(&mBtnOpen, _T("Select Sensor"));

	mBtnSave.SetImage(icon_save, 1, NULL, icon_disable, 0);
	mToolTip->AddTool(&mBtnSave, _T("Save to INI"));

	mBtnReload.SetImage(icon_reload, 1, NULL, icon_disable4, 0);
	mToolTip->AddTool(&mBtnReload, _T("Reload setting"));

	mBtnRun.SetImage(icon_run, 1, icon_run, icon_disable2, 0);	
	mBtnRun.SetCheckedImage(icon_stop, 1, icon_stop, icon_disable3, 0);
	mToolTip->AddTool(&mBtnRun, _T("Run/Stop"));


	mLogo.GetClientRect(&rect_ctrl);
	if (rect_ctrl.Width() >= 256)		size = 256;
	else if (rect_ctrl.Width() >= 128)	size = 128;
	else if (rect_ctrl.Width() >= 96)	size = 96;
	else if (rect_ctrl.Width() >= 64)	size = 64;
	else if (rect_ctrl.Width() >= 48)	size = 48;
	else if (rect_ctrl.Width() >= 32)	size = 32;
	else if (rect_ctrl.Width() >= 24)	size = 24;
	else 								size = 16;

#ifdef _ICON_CUSTOM_1
	HICON icon_logo2 = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_CUSTOM1), IMAGE_ICON, size, size, 0);
	SetWindowText(_T("JW Demo Program"));
#else
	HICON icon_logo2 = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_LOGO), IMAGE_ICON, size, size, 0);
	SetWindowText(_T("DI Demo Program"));
#endif
	mLogo.SetImage(icon_logo2, 1, icon_logo2, icon_logo2, 0);
	mLogo.m_bGrayDisabled = false;
	mLogo.m_bDrawFocus = false;

	mStatusBar.Create(this);
	mStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));
	mStatusBar.SetPaneText(0, _T("Status: "));
	mStatusBar.SetPaneText(1, _T("Conv Time:"));
	mStatusBar.SetPaneText(2, _T("PWR Consumption:"));
	mStatusBar.SetPaneText(3, _T("No Select Sensor"));
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, ID_INDICATOR_STATUS);

	mStatusBar.SetPaneInfo(0, ID_INDICATOR_STATUS, SBPS_NORMAL, (int)(rect.Width() * 0.25));
	mStatusBar.SetPaneInfo(1, ID_INDICATOR_CONV_TIME, SBPS_NORMAL, (int)(rect.Width() * 0.25));
	mStatusBar.SetPaneInfo(2, ID_INDICATOR_POWER_CONSUMPTION, SBPS_NORMAL, (int)(rect.Width() * 0.25));
	mStatusBar.SetPaneInfo(3, ID_INDICATOR_SENSOR, SBPS_STRETCH, 0);
	

	GUID HidGuid;
	DEV_BROADCAST_DEVICEINTERFACE DevBroadcastDeviceInterface;
	HidD_GetHidGuid(&HidGuid);
	DevBroadcastDeviceInterface.dbcc_size = sizeof(DevBroadcastDeviceInterface);
	DevBroadcastDeviceInterface.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	DevBroadcastDeviceInterface.dbcc_classguid = HidGuid;

	m_HDevNotify = RegisterDeviceNotification(m_hWnd,
		&DevBroadcastDeviceInterface,
		DEVICE_NOTIFY_WINDOW_HANDLE);

	hidName = _T("");
	hidNum = HID_Open();

	if (hidNum > 0)
	{
		mStatusBar.SetPaneText(0, _T("Status: Control board is found."));
		SetTimer(CheckSensorTime, 1000, NULL);
	}
	else
		mStatusBar.SetPaneText(0, _T("Status: Control board is not found."));

	SensorName = _T("");
	SensorVersion = 0;
	csLOGFileName = _T("");
	pRegInfoMap = NULL;

	mAvgNum.SetWindowTextW(_T("1"));
	LastAvgNum = 1;

	mToolTip->SetDelayTime(350);
	mToolTip->Activate(TRUE);

	bDetectSensor = false;
	bCalibration = false;
	bLoopRead = false;
	bLogEnable = false;
	bSLActive = false; // LEO added

	return TRUE;
}


/* 顯示改變後的頁面 */
afx_msg void CDIDemoProgramDlg::OnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nTab = mTab.GetCurSel() + TAB_1;
	mmTabPage.at(nTab).ShowWindow(SW_SHOW);
	*pResult = 0;
}

/* 隱藏改變前的頁面 */
afx_msg void CDIDemoProgramDlg::OnSelchangingTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nTab = mTab.GetCurSel() + TAB_1;
	mmTabPage.at(nTab).ShowWindow(SW_HIDE);
	*pResult = 0;
}


void CDIDemoProgramDlg::OnClickedOpen()
{
	CRect rect_mainsize, rect_dlg, rect_location, rect_ctrl;
	LONG x = 0;
	LONG y = 0;
	int i, j;
	BOOL bLoopRead_Old = bLoopRead;
	int resolution_x;
	HMONITOR hMonitor;
	MONITORINFO mi;

	if (bLogEnable)
	{
		mBtnLOG.SetCheck(0);
		OnClickedButtonLOG();
	}

	KillTimer(CheckSensorTime);
	CloseLoopRead();
	CSelSensor* m_pSelSensor = new CSelSensor();
	m_pSelSensor->SetSensorInfo(&DI_Sensor);
	INT_PTR ptr = m_pSelSensor->DoModal();
	switch (ptr)
	{
	case IDOK:
		DestroyCtrl();
		mBtnRun.SetCheck(1);

		if(!SensorName.IsEmpty())
			DI_Sensor.SensorMap.at(SensorName)->Clear();

		SensorName = m_pSelSensor->SensorName;
		TRACE("Name %s\n", SensorName.GetString());
		SensorVersion = m_pSelSensor->Version;

		GetClientRect(&rect_mainsize);
		GetWindowRect(&rect_location);

		resolution_x = GetSystemMetrics(SM_CXSCREEN);
		hMonitor = MonitorFromRect(rect_location, MONITOR_DEFAULTTONEAREST);
		mi.cbSize = sizeof(mi);
		GetMonitorInfo(hMonitor, &mi);

		DI_Sensor.Init(SensorName, SensorVersion);

		pSensorInfo = DI_Sensor.SensorMap.at(SensorName);

		pDieDetail = &pSensorInfo->pDieInfo->DieDetail.at(pSensorInfo->DieVersion);
		pBitDetailMap = &pDieDetail->RegisterTable.BitDetail;
		pRegTable = &pDieDetail->RegisterTable;
		pRegInfoMap = &pRegTable->RegInfo;

		if (m_pSelSensor->SensorAddress != 0x00)
			pRegTable->DeviceID = m_pSelSensor->SensorAddress;

		uint8_t buff[2];

		buff[0] = 0;
		GPIOswitch(0, GPIO_PA22, buff); /* VLED_EN */
		GPIOswitch(0, GPIO_PA23, buff); /* IVDD_EN */
		GPIOswitch(0, GPIO_PA27, buff); /* SVDD_EN */
		Sleep(5000);


		I2CConfig_ I2CConfig;

		I2CConfig.enable = 1;
		I2CConfig.baudrate = pDieDetail->I2CFreqKHz;
		I2CsetConfig(0, (uint8_t*)&I2CConfig, 1000);

		buff[0] = 1;
		GPIOswitch(0, GPIO_PA22, buff); /* VLED_EN */
		GPIOswitch(0, GPIO_PA27, buff); /* SVDD_EN */
		Sleep(3);
		GPIOswitch(0, GPIO_PA23, buff); /* IVDD_EN */
        Sleep(10);

		LoadINIFile();

		/* Tab Page Show */
		mTab.DeleteAllItems();
		mTab.GetItemRect(0, &rect_ctrl);
		mTab.GetClientRect(&rect_dlg);
		for (i = TAB_1, j = 0; i <= TAB_6; i++)
		{
			if (pDieDetail->DlgName.count((DlgSel_)i))
			{
				mTab.InsertItem(j, pDieDetail->DlgName[(DlgSel_)i]);

				mmTabPage[i].CtrlInit(pDieDetail, &pDieDetail->CtrlInfo[(DlgSel_)i], mToolTip);
				mmTabPage[i].Create(mmTabPage[i].IDD, &mTab);
				mmTabPage[i].SetWindowPos(NULL, 0,
					rect_ctrl.Height(), rect_dlg.Width(),
					rect_dlg.Height() - rect_ctrl.Height(),
					SWP_HIDEWINDOW);
				mmTabPage[i].Set();
				j++;
			}
		}

		mTab.SetCurSel(0);
		mmTabPage.begin()->second.ShowWindow(SW_SHOW);

		/* INT LED SHOW */
		if (pDieDetail->CtrlInfo[MAIN_DIALOG].CtrlDetail.size() > 0)
		{
			auto iter2 = pDieDetail->CtrlInfo[MAIN_DIALOG].CtrlDetail.begin();
			i = 1;
			while (iter2 != pDieDetail->CtrlInfo[MAIN_DIALOG].CtrlDetail.end())
			{
				TRACE(_T("BitMapping %s\n"), iter2->second.BitMapping[0]);
				mmButtonLED[iter2->first.first].CtrlInit(pDieDetail, &iter2->second, mToolTip);
				TRACE(_T("CtrlDetail.size() %d\n"), pDieDetail->CtrlInfo[MAIN_DIALOG].CtrlDetail.size());
				if(pDieDetail->CtrlInfo[MAIN_DIALOG].CtrlDetail.size() > 8)
					mmButtonLED[iter2->first.first].Create(mmButtonLED[iter2->first.first].IDD2, this);
				else
					mmButtonLED[iter2->first.first].Create(mmButtonLED[iter2->first.first].IDD, this);

				mmButtonLED[iter2->first.first].GetClientRect(&rect_dlg);
				if (pDieDetail->CtrlInfo[MAIN_DIALOG].CtrlDetail.size() > 14)
				{
					x = rect_mainsize.right - (LONG)((LONG)ceil(i / 2.0) * (rect_dlg.right + 5L)) - 10;
					y = rect_mainsize.bottom - rect_dlg.bottom - ((i % 2) == 1? 68 : 19);
				}
				else if (pDieDetail->CtrlInfo[MAIN_DIALOG].CtrlDetail.size() > 8)
				{					
					x = rect_mainsize.right - i * (rect_dlg.right + 5) - 10;
					y = rect_mainsize.bottom - rect_dlg.bottom - 50;
				}
				else
				{
					x = rect_mainsize.right - i * (rect_dlg.right + 5) - 15;
					y = rect_mainsize.bottom - rect_dlg.bottom - 30;
				}

				mmButtonLED[iter2->first.first].SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW);
				mmButtonLED[iter2->first.first].SetText(iter2->second.CtrlName.first);
				i++;
				iter2++;
			}
			CClientDC dc(&mGroup);
			CString csTemp;

			mGroup.GetWindowTextW(csTemp);
			dc.SelectObject(GetFont());
			CSize sz = dc.GetTextExtent(csTemp);

			if (pDieDetail->CtrlInfo[MAIN_DIALOG].CtrlDetail.size() > 14)
			{
				y = rect_mainsize.bottom - rect_dlg.bottom - 58;
				mGroup.SetWindowPos(NULL, x - 7, y - sz.cy - 10, rect_mainsize.right - x, rect_mainsize.bottom - y + 6, SWP_SHOWWINDOW);
			}
			else if (pDieDetail->CtrlInfo[MAIN_DIALOG].CtrlDetail.size() > 8)
				mGroup.SetWindowPos(NULL, x - 7, y - sz.cy - 10, rect_mainsize.right - x, rect_mainsize.bottom - y - 10, SWP_SHOWWINDOW);
			else
				mGroup.SetWindowPos(NULL, x - 7, y - sz.cy, rect_mainsize.right - x, rect_mainsize.bottom - y - 10, SWP_SHOWWINDOW);

		}
		else
			mGroup.ShowWindow(SW_HIDE);

		/* Modelless Show */
		for (i = MODEL_1; i <= MODEL_5; i++)
		{
			if (pDieDetail->DlgName.count((DlgSel_)i))
			{
				switch (pDieDetail->DlgStyle[(DlgSel_)i])
				{
				case MODELLESS1:
					if (mmModelLess.size() > 0)
					{
						mmModelLess.rbegin()->second.GetWindowRect(&rect_location);
					}
					else
						GetWindowRect(&rect_location);


					mmModelLess[i].CtrlInit((DlgSel_)i, pDieDetail, mToolTip);
					mmModelLess[i].Create(mmModelLess[i].IDD);
					mmModelLess[i].GetWindowRect(&rect_dlg);
					x = rect_location.left - rect_dlg.Width();
					y = rect_location.top;
					if (x < mi.rcWork.left)
					{
						x = rect_location.left;
						if((y + rect_dlg.Height()) < mi.rcMonitor.bottom )
							y = rect_location.bottom;
					}

					mmModelLess[i].SetWindowPos(NULL, x, y,
						0, 0, SWP_NOSIZE | SWP_SHOWWINDOW);
					break;
				case MODELLESS_LIST:
					if (mmModelLess_List.size() > 0)
					{
						mmModelLess_List.rbegin()->second.GetWindowRect(&rect_location);
					}
					else
						GetWindowRect(&rect_location);

					mmModelLess_List[i].CtrlInit((DlgSel_)i, pDieDetail);
					mmModelLess_List[i].Create(mmModelLess_List[i].IDD);
					mmModelLess_List[i].SetWindowPos(NULL,
						mmModelLess_List.size() > 1 ? rect_location.left : rect_location.right,
						mmModelLess_List.size() > 1 ? rect_location.bottom : rect_location.top,
						0, 0, SWP_NOSIZE | SWP_SHOWWINDOW);
					break;
				}
			}
		}

		mStatusBar.SetPaneText(3, SensorName);

		bDetectSensor = false;

		PostMessage(WM_MESSAGE_UPDATE_INFO, (WPARAM)(pSensorInfo->DieVersion << 16 | SensorVersion), 0);

		break;
	case IDCANCEL:
		if (bLoopRead_Old)
			SetLoopRead();		
		break;
	}
	m_pSelSensor = NULL;
	SetTimer(CheckSensorTime, 1000, NULL);
}

BOOL CDIDemoProgramDlg::OnDeviceChange(UINT nEventType, DWORD_PTR dwData)
{
	DEV_BROADCAST_DEVICEINTERFACE* DevBroadcastDeviceInterface = (DEV_BROADCAST_DEVICEINTERFACE*)dwData;
	CString csTemp;
	uint8_t dev_num = 0;

	switch (nEventType)
	{
	case DBT_DEVICEARRIVAL:
		if (hidName.IsEmpty())
		{
			csTemp = DevBroadcastDeviceInterface->dbcc_name;
			if ((csTemp.Find(_T("VID_0F43") > 0) && (csTemp.Find(_T("PID_2000") > 0))))
			{
				hidName = csTemp;
				hidNum = HID_Open();
				mStatusBar.SetPaneText(0, _T("Status: Control board is found."));

				if (!SensorName.IsEmpty())
				{
					SensorInitial();
				}

				SetTimer(CheckSensorTime, 1000, NULL);
			}
		}

		break;
	case DBT_DEVICEREMOVECOMPLETE:
		if (!hidName.IsEmpty())
		{
			csTemp = DevBroadcastDeviceInterface->dbcc_name;
			if (csTemp != hidName) break;
			else
			{
				KillTimer(CheckSensorTime);
				hidName = _T("");
				HID_Close();
				hidNum = 0;
				mStatusBar.SetPaneText(0, _T("Status: Control board is no found."));

				if (!SensorName.IsEmpty())
				{
					mBtnSave.EnableWindow(0);
					mBtnRun.EnableWindow(0);
					mBtnReload.EnableWindow(0);
					mBtnLOG.EnableWindow(0);
				}

				bDetectSensor = false;
			}
		}
		else
			break;


		break;
	}
	PostMessage(WM_MESSAGE_UPDATE_INFO, 0, 0);

	return CDialogEx::OnDeviceChange(nEventType, dwData);
}


HBRUSH CDIDemoProgramDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	return hbr;
}


void CDIDemoProgramDlg::OnTimer(UINT_PTR nIDEvent)
{
	uint8_t result;
	vector<uint8_t> u8_temp(2000, 0);
	uint16_t num;

	int i;
	CString csTemp;
	uint8_t SunLight_Status = 3;
	bool SunLight_ACT = false;
	uint8_t data = 0;

	switch (nIDEvent)
	{
	case GetDataTime:

		//SendMessage(WM_MESSAGE_SL_SUPPRESSION);
		/*SunLight_ACT = DI_Sensor.SLSuppression(SensorName, &SunLight_Status);

		if (SunLight_Status == SUNLIGHT_OK)
			csTemp.Format(_T("SUNLIGHT_OK"));
		else if (SunLight_Status == SUNLIGHT_INC)
			csTemp.Format(_T("SUNLIGHT_INC"));
		else if (SunLight_Status == SUNLIGHT_DEC)
			csTemp.Format(_T("SUNLIGHT_DEC"));
		else
			csTemp.Format(_T("SUNLIGHT_TOO_STRONG"));

		mStatusBar.SetPaneText(4, csTemp);

		if (SunLight_ACT)
		{
			for (i = 0; i < 3; i++) // skip two data
			{
				uint8_t IntFlag_VAL = 0;
				I2CWrite(0, pDieDetail->RegisterTable.DeviceID, reg_IntFlag, &IntFlag_VAL, 1);				
				while (!(DI_Sensor.GetIntFlag(SensorName) & 0x10))				
				{		
					Sleep(DI_Sensor.GetConversionTime(SensorName)/1000);
					//Sleep(60);
				}
			}
		}*/

		result = I2CLoopRead(0, &u8_temp[0], &num, 1, 1000);

		if (result == STATUS_OK)
		{
			if (num > 0)
			{
				u8_temp.resize(num);
				auto iter_u8 = u8_temp.begin();
				while (iter_u8 != u8_temp.end())
				{					
					auto iter = pDieDetail->RegisterTable.ReadTable.begin();
					while (iter != pDieDetail->RegisterTable.ReadTable.end())
					{
						for (i = 0; i < iter->ReadNum;)
						{
							if (pDieDetail->RegisterTable.RegInfo.count(iter->RegAddr) > 0) // Check whether there is RegAddr
							{								
								memcpy(pDieDetail->RegisterTable.RegInfo.at(iter->RegAddr + i).RegCurVal.data(),
									iter_u8._Ptr,
									pDieDetail->RegisterTable.RegInfo.at(iter->RegAddr + i).RegBits);

								if (bCalibration && ((iter->RegAddr + i) == pCtrlDetail_Cali->RegMapping.at(0)))
								{
									TRACE(_T("bCalibration %d\n"), bCalibration);

									//Start Storing PS data from tail of dequeCali
									dequeCali.push_back(pDieDetail->RegisterTable.GetRegValue(iter->RegAddr + i));

									TRACE(_T("dequeCali.size() %d\n"), dequeCali.size());

									if (dequeCali.size() >= 23)
									{
										bCalibration = false;
										CaliSum = 0;

										//ORG
										//dequeCali.pop_front();
										//dequeCali.pop_front();
										//dequeCali.pop_front();
										//Leo Modify for del the last three in the dequeCali sequence
										dequeCali.pop_back();
										dequeCali.pop_back();
										dequeCali.pop_back();
										//

										auto iter = dequeCali.begin();
										while (iter != dequeCali.end())
										{
											CaliSum += *iter;
											++iter;
										}

										dequeCali.clear();

										if (CaliSum > 0)
											CaliSum /= 20;
										else if (CaliSum < 1)
											CaliSum = -1;

										PostMessage(WM_MESSAGE_CALIBRATION, (WPARAM)CaliSum, (LPARAM)pCtrlDetail_Cali);
									}
								}

								if (iter_u8 == u8_temp.end())
									break;

								iter_u8 = iter_u8 + pDieDetail->RegisterTable.RegInfo.at(iter->RegAddr + i).RegBits;

								i += pDieDetail->RegisterTable.RegInfo.at(iter->RegAddr + i).RegBits;
							}
							else
								i++;

							if (iter_u8 == u8_temp.end())
								break;
						}
						++iter;
					}

					if (bLogEnable)
						Log2File();

					if (iter_u8 == u8_temp.end())
						break;
				}
				//leo, SunLight suppression behavior is that if PsDrvErr is error, force on PsData to zero and Obj to far.
				if (bSLActive)
				{
					uint8_t value[2] = {0};					

					if (*pDieDetail->RegisterTable.RegInfo.at(0xff).RegCurVal.data() & 0x10)
					{
						memcpy(pDieDetail->RegisterTable.RegInfo.at(0x00).RegCurVal.data(),
							value,
							pDieDetail->RegisterTable.RegInfo.at(0x00).RegBits);

						value[0] = *pDieDetail->RegisterTable.RegInfo.at(0xff).RegCurVal.data() | 0x80;
						memcpy(pDieDetail->RegisterTable.RegInfo.at(0xff).RegCurVal.data(),
							value,
							pDieDetail->RegisterTable.RegInfo.at(0xff).RegBits);
					}
				}
				//leo
				PostMessageW(WM_MESSAGE_UPDATEUI);
			}
		}
		else
		{
			bDetectSensor = false;
			CloseLoopRead();
		}

		break;
	case CheckSensorTime:
		if (!SensorName.IsEmpty())
		{
			result = I2CRead(0, pDieDetail->RegisterTable.DeviceID, 0x00, &u8_temp[0], 1, 0, 0, 1000);

			if (result == STATUS_OK)
			{
				if (!bDetectSensor)
				{
					bDetectSensor = true;


					SendMessage(WM_MESSAGE_RELOAD_REG);
					SensorInitial();
					PostMessage(WM_MESSAGE_UPDATEUI, 1);

					if (mBtnRun.GetCheck() == 1)
					{
						SendMessage(WM_MESSAGE_CHANGE_CONVERSION_TIME);
						SendMessage(WM_MESSAGE_CALCULATE_POWER);
					}
					mBtnSave.EnableWindow();
					mBtnRun.EnableWindow();
					mBtnReload.EnableWindow();
					mBtnLOG.EnableWindow();

					mStatusBar.SetPaneText(0, _T("Status: Sensor is found."));
					SendMessage(WM_MESSAGE_UPDATE_INFO, (WPARAM)(pSensorInfo->DieVersion << 16 | SensorVersion), 0);
				}
			}
			else if(bDetectSensor)
			{
				mBtnSave.EnableWindow(false);
				mBtnRun.EnableWindow(false);
				mBtnReload.EnableWindow(false);
				mBtnLOG.EnableWindow(false);

				bDetectSensor = false;
				CloseLoopRead();
				mStatusBar.SetPaneText(0, _T("Status: Sensor is no found."));
				SendMessage(WM_MESSAGE_UPDATE_INFO, 0, 0);
			}
		}
		else
		{
			mStatusBar.SetPaneText(0, _T("Status: Sensor is no select."));
			SendMessage(WM_MESSAGE_UPDATE_INFO, 0, 0);
		}		
	
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CDIDemoProgramDlg::OnOK()
{
}


void CDIDemoProgramDlg::OnCancel()
{
	KillTimer(CheckSensorTime);

	if (bLoopRead)
		CloseLoopRead();

	CDialogEx::OnCancel();
}


BOOL CDIDemoProgramDlg::PreTranslateMessage(MSG* pMsg)
{
	uint32_t value;
	CString csTemp;

	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam) {
		case VK_ESCAPE:
			if (pMsg->hwnd = mAvgNum.GetSafeHwnd())
				mAvgNum.SetWindowTextW(csTemp);
			break;
		case VK_RETURN:
			if (pMsg->hwnd = mAvgNum.GetSafeHwnd())
			{
				mAvgNum.GetWindowTextW(csTemp);
				value = wcstoul(csTemp, NULL, 10);
				if (value < 1)
				{
					csTemp.Format(_T("Average number minimun is 1."));
					MessageBoxW(csTemp, _T("Out of range!"), MB_OK);
					csTemp.Format(_T("%d"), LastAvgNum);
					mAvgNum.SetWindowTextW(csTemp);
					break;
				}

				CustomMessage(mmTabPage, WM_MESSAGE_CHANGE_AVG_NUM, value, 0);
				CustomMessage(mmModelLess, WM_MESSAGE_CHANGE_AVG_NUM, value, 0);

				LastAvgNum = value;
			}

			break;

			return false;
		}
	}

	if (mToolTip != NULL)
		mToolTip->RelayEvent(pMsg);

	return CDialogEx::PreTranslateMessage(pMsg);
}


afx_msg LRESULT CDIDemoProgramDlg::OnMessageUpdateui(WPARAM wParam, LPARAM lParam)
{
	CustomMessage(mmTabPage, WM_MESSAGE_UPDATEUI, wParam, lParam, wParam > 0);
	CustomMessage(mmButtonLED, WM_MESSAGE_UPDATEUI, wParam, lParam, wParam > 0);
	CustomMessage(mmModelLess, WM_MESSAGE_UPDATEUI, wParam, lParam, wParam > 0);
	CustomMessage(mmModelLess_List, WM_MESSAGE_UPDATEUI, wParam, lParam, wParam > 0);
	return 0;
}

void CDIDemoProgramDlg::OnClickedRun()
{
	if (mBtnRun.GetCheck())
	{
		SendMessage(WM_MESSAGE_CHANGE_CONVERSION_TIME);
		SendMessage(WM_MESSAGE_CALCULATE_POWER);
	}
	else 
		CloseLoopRead();
}

void CDIDemoProgramDlg::OnClickedButtonLOG()
{
	int iCheck = mBtnLOG.GetCheck();

	if (iCheck > 0)
	{
		mBtnLOG.SetWindowTextW(_T("Disable Log"));
		CTime ctCurrentTime = CTime::GetCurrentTime();
		CString csTime = ctCurrentTime.Format("%Y%m%d_%H%M%S");

		csLOGFileName.Format(_T("%s_v%1.2f_%s.csv"), SensorName.GetString(), (float)SensorVersion / 10000, csTime.GetString());

		mBtnRun.EnableWindow(0);
		mBtnReload.EnableWindow(0);
		mBtn_I2C.EnableWindow(0);
		bLogEnable = true;
	}
	else
	{
		mBtnLOG.SetWindowTextW(_T("Enable Log"));

		mBtnRun.EnableWindow(1);
		mBtnReload.EnableWindow(1);
		mBtn_I2C.EnableWindow(1);
		bLogEnable = false;
	}
}

void CDIDemoProgramDlg::OnClickedReload()
{
	if (MessageBox(_T("Reload Setting to Default value?"), _T("Reload Setting"), MB_OKCANCEL) == IDOK)
	{
		if (!SensorName.IsEmpty() && SensorVersion != 0)
		{
			SensorInitial();

			MessageBox(_T("Reload Done!"), _T("Reload Setting"), MB_OK);
		}
		else
			MessageBox(_T("Sensor is no selected!"), _T("Reload Setting"), MB_OK | MB_ICONEXCLAMATION);
	}
}

void CDIDemoProgramDlg::OnClickedSave()
{
	if (MessageBoxW(_T("Save Current Setting to .ini File?"), _T("Save to INI"), MB_OKCANCEL) == IDOK)
		SaveINIFile();
}

void CDIDemoProgramDlg::Log2File()
{
	CString csTemp;

	if (!mLogFile.Open(csLOGFileName, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate, NULL))
		return;

	if (mLogFile.GetLength() == 0)
	{
		csTemp.Format(_T("Register Table Setting\n"));
		mLogFile.Write(csTemp, 2 * csTemp.GetLength());

		csTemp = _T("Addr");
		auto iter2 = pDieDetail->RegisterTable.RegInfo.begin();
		while (iter2 != pDieDetail->RegisterTable.RegInfo.end())
		{
			if (!iter2->second.bEngMode)
			{
				csTemp.Format(_T("%s,0x%02X"), csTemp.GetString(), iter2->first);
				for (int i = 1; i < iter2->second.RegBits; i++)
					csTemp.Format(_T("%s,0x%02X"), csTemp.GetString(), iter2->first + i);
			}
			++iter2;
		}

		csTemp += _T("\n");
		mLogFile.SeekToEnd();
		mLogFile.Write(csTemp, 2 * csTemp.GetLength());

		csTemp = _T("Value");
		iter2 = pDieDetail->RegisterTable.RegInfo.begin();
		while (iter2 != pDieDetail->RegisterTable.RegInfo.end())
		{
			if (!iter2->second.bEngMode)
			{
				csTemp.Format(_T("%s,0x%02X"), csTemp.GetString(), iter2->second.RegCurVal.at(0));
				for (int i = 1; i < iter2->second.RegBits; i++)
					csTemp.Format(_T("%s,0x%02X"), csTemp.GetString(), iter2->second.RegCurVal.at(i));
			}
			++iter2;
		}
		csTemp += _T("\n\n");
		mLogFile.SeekToEnd();
		mLogFile.Write(csTemp, 2 * csTemp.GetLength());

		csTemp.Format(_T("Time"));

		auto iter = pRegTable->ReadTable.begin();
		while (iter != pDieDetail->RegisterTable.ReadTable.end())
		{
			for (int i = 0; i < iter->ReadNum; i++)
			{
				auto iter2 = pRegTable->RegInfo.at(iter->RegAddr + i).BitName.begin();
				while (iter2 != pRegTable->RegInfo.at(iter->RegAddr + i).BitName.end())
				{
					csTemp.Format(_T("%s,%s"), csTemp.GetString(), iter2->second.GetString());
					++iter2;
				}
				i += pRegTable->RegInfo.at(iter->RegAddr + i).RegBits - 1;
			}
			++iter;
		}

		if (pDieDetail->DieFunc & DF_LUX)
		{
			csTemp += _T(", Lux");
		}

		if (pDieDetail->DieFunc & DF_CCT)
		{
			csTemp += _T(", CCT");
		}

		csTemp += _T("\n");
		mLogFile.SeekToEnd();
		mLogFile.Write(csTemp, 2 * csTemp.GetLength());

		LogTimer = 0;
	}

	csTemp.Format(_T("%lf"), LogTimer);

	int32_t value;
	int32_t range;

	auto iter = pDieDetail->RegisterTable.ReadTable.begin();
	while (iter != pDieDetail->RegisterTable.ReadTable.end())
	{
		for (int i = 0; i < iter->ReadNum; i++)
		{
			int32_t mask = 0xFFFFFFFF;

			if (pRegTable->RegInfo.count(iter->RegAddr + i) > 0)
			{
				pRegInfo = &pRegTable->RegInfo.at(iter->RegAddr + i);
				auto iter2 = pRegTable->RegInfo.at(iter->RegAddr + i).BitName.begin();
				while (iter2 != pRegTable->RegInfo.at(iter->RegAddr + i).BitName.end())
				{
					pBitDetail = &pBitDetailMap->at(iter2->second);
					value = 0;
					range = 0;
					mask = 0xFFFFFFFF;
					if(pRegInfo->RegBits > 1)
					{ 
						for (unsigned int j = 0; j < pRegInfo->RegBits; j++)
						{
							if (pBitDetail->BitMask.size() <= j)
								break;

							value += LSHIFT((pRegInfo->RegCurVal.at(j) & pBitDetail->BitMask.at(j)), pBitDetail->BitShift.at(j));
							range += LSHIFT(pBitDetail->BitRange.at(j).second, pBitDetail->BitShift.at(j));
							mask &= ~LSHIFT(pBitDetail->BitMask.at(j), pBitDetail->BitShift.at(j));
						}
					}
					else
					{
						value += RSHIFT((pRegInfo->RegCurVal.at(0) & pBitDetail->BitMask.at(0)), pBitDetail->BitShift.at(0));
						range = pBitDetail->BitRange.at(0).second;
						mask &= ~RSHIFT(pBitDetail->BitMask.at(0), pBitDetail->BitShift.at(0));
					}

					switch (iter->LogFormat)
					{
					case LogHex:
						switch (pRegTable->RegInfo.at(iter->RegAddr + i).RegBits)
						{
						case 1: csTemp.Format(_T("%s,0x%02X"), csTemp.GetString(), value);	break;
						case 2: csTemp.Format(_T("%s,0x%04X"), csTemp.GetString(), value);	break;
						case 4: csTemp.Format(_T("%s,0x%08X"), csTemp.GetString(), value);	break;
						default: csTemp.Format(_T("%s,0x%X"), csTemp.GetString(), value);	break;
						}
						break;
					case LogDec:
						if (pBitDetail->bSign)
						{
							if (value > (range >> 1))
								value |= mask;
						}
						csTemp.Format(_T("%s,%d"), csTemp.GetString(), value);
						break;
					}
					++iter2;
				}
				i += pRegTable->RegInfo.at(iter->RegAddr + i).RegBits - 1;
			}
		}
		++iter;
	}

	if (pDieDetail->DieFunc & DF_LUX)
	{
		csTemp.Format(_T("%s,%d"), csTemp.GetString(), pDieDetail->LuxValue);
	}

	if (pDieDetail->DieFunc & DF_CCT)
	{
		csTemp.Format(_T("%s,%d"), csTemp.GetString(), pDieDetail->CCTValue);
	}

	csTemp += _T("\n");
	LogTimer += (double)ConversionTime / 1000000.0;
	mLogFile.SeekToEnd();
	mLogFile.Write(csTemp, 2 * csTemp.GetLength());
	mLogFile.Close();
}


afx_msg LRESULT CDIDemoProgramDlg::OnMessageChangeSelData(WPARAM wParam, LPARAM lParam)
{
	CustomMessage(mmTabPage, WM_MESSAGE_CHANGE_SEL_DATA, wParam, lParam);
	return 0;
}


afx_msg LRESULT CDIDemoProgramDlg::OnMessageChangeRange(WPARAM wParam, LPARAM lParam)
{
	CustomMessage(mmTabPage, WM_MESSAGE_CHANGE_RANGE, wParam, lParam);
	CustomMessage(mmModelLess, WM_MESSAGE_CHANGE_RANGE, wParam, lParam);
	return 0;
}


void CDIDemoProgramDlg::DestroyCtrl()
{
	CustomDestroy(mmTabPage);
	CustomDestroy(mmButtonLED);
	CustomDestroy(mmModelLess);
	CustomDestroy(mmModelLess_List);
}



void CDIDemoProgramDlg::SetLoopRead()
{
	uint8_t result;
	UINT time = 250;
	struct devInfo_ {
		uint8_t devid;
		uint8_t addr;
		uint8_t num;
	}devInfo;

	vector<devInfo_> LoopReadSet;	

	if (ConversionTime > 0)
	{
		auto iter = pDieDetail->RegisterTable.ReadTable.begin();
		while (iter != pDieDetail->RegisterTable.ReadTable.end())
		{			
			if (iter->bSignalRead)
			{
				devInfo.devid = pRegTable->DeviceID;
				for (int i = 0; i < iter->ReadNum; i++)
				{
					devInfo.addr = iter->RegAddr + i;
					devInfo.num = 1;
					LoopReadSet.push_back(devInfo);
				}
			}
			else
			{
				devInfo.devid = pRegTable->DeviceID;
				devInfo.addr = iter->RegAddr;
				devInfo.num = iter->ReadNum;
				LoopReadSet.push_back(devInfo);
			}
			++iter;
		}		

		if (LoopReadSet.size() > 0 && LoopReadSet.size() < 19)
		{
			result = I2CLoopReadSet(0, (uint8_t)LoopReadSet.size(), (uint8_t*)&LoopReadSet[0], ConversionTime);
		}

		if ((ConversionTime / 2000) > 250)
			time = (ConversionTime / 2000);
		else
			time = 250;

		bLoopRead = true;

		SetTimer(GetDataTime, time, NULL);
	}
	else
	{
		SendMessage(WM_MESSAGE_UPDATEUI, 1);
	}
}


void CDIDemoProgramDlg::CloseLoopRead()
{
	vector<uint8_t> u8_temp(2000);
	uint16_t u16_temp;

	I2CLoopRead(0, u8_temp.data(), &u16_temp, 0, 1000);

	if(bLoopRead)
		KillTimer(GetDataTime);

	bLoopRead = false;
}


void CDIDemoProgramDlg::LoadINIFile()
{
	int32_t value;
	CFile mIniFile;
	CString csTemp = _T("");
	CString csAddr = _T("");
	CString csValue = _T("");
	set<uint8_t> RegSet;

	CString csCurrentDir;
	WIN32_FIND_DATA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	GetCurrentDirectory(1024, csCurrentDir.GetBuffer(1024));
	csCurrentDir.ReleaseBuffer();
	csINIFileName.Format(_T("%s\\%s_v%1.2f*.ini"), csCurrentDir.GetString(), SensorName.GetString(), (float)SensorVersion / 10000);
	
	hFind = FindFirstFile(csINIFileName, &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		csINIFileName.Format(_T("%s\\%s_v%1.2f.ini"), csCurrentDir.GetString(), SensorName.GetString(), (float)SensorVersion / 10000);

		if (!mIniFile.Open(csINIFileName, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate, NULL))
			return;

		auto iter_RegInfo = pRegTable->RegInfo.begin();
		while (iter_RegInfo != pRegTable->RegInfo.end())
		{
			if (iter_RegInfo->second.bEngMode)
			{
				++iter_RegInfo;
				continue;
			}
			if (iter_RegInfo->second.BitName.count(0))
				if (!iter_RegInfo->second.BitName.at(0).IsEmpty())
					if(pBitDetailMap->at(iter_RegInfo->second.BitName.at(0)).BitRW == ONLY_R)
					{
						++iter_RegInfo;
						continue;
					}
			
			value = 0;
			csAddr.Format(_T("0x%02X"), iter_RegInfo->first);
			if (iter_RegInfo->second.RegBits > 1)
			{
				pBitDetail = &pBitDetailMap->at(iter_RegInfo->second.BitName.at(0));
				for (uint8_t i = 0; i < iter_RegInfo->second.RegBits; i++)
				{
					if ((i + 1) <= (uint8_t)pBitDetail->BitMask.size())
					{
						if (pRegTable->RegInfo.count(iter_RegInfo->first + i) == 0)
							csAddr.Format(_T("%s, 0x%02X"), csAddr.GetString(), iter_RegInfo->first + i);

						value += LSHIFT(pBitDetail->DefaultVal.at(i) , pBitDetail->BitShift.at(i));
					}
				}
			}
			else
			{
				auto iter_BitName = iter_RegInfo->second.BitName.begin();
				while (iter_BitName != iter_RegInfo->second.BitName.end())
				{
					pBitDetail = &pBitDetailMap->at(iter_BitName->second);
					value += LSHIFT(pBitDetail->DefaultVal.at(0) , pBitDetail->BitShift.at(0));
					++iter_BitName;
				}
			}

			switch (iter_RegInfo->second.RegBits)
			{
			case 1:
				csTemp.Format(_T("[%s]\r\n;Address = %s\r\nDefault = 0x%02X\r\n\r\n"), 
					iter_RegInfo->second.RegDesc.GetString(), csAddr.GetString(), value);
				break;
			case 2:
				csTemp.Format(_T("[%s]\r\n;Address = %s\r\nDefault = 0x%04X\r\n\r\n"), 
					iter_RegInfo->second.RegDesc.GetString(), csAddr.GetString(), value);
				break;
			case 4:
				csTemp.Format(_T("[%s]\r\n;Address = %s\r\nDefault = 0x%08X\r\n\r\n"), 
					iter_RegInfo->second.RegDesc.GetString(), csAddr.GetString(), value);
				break;
			}

			mIniFile.Write(csTemp, 2 * csTemp.GetLength());

			++iter_RegInfo;
		}

		if (pDieDetail->LuxCalculate.Count2LuxMapping.size() != 0)
		{
			uint8_t i = 0;
			csTemp.Format(_T("[LuxCalculate]\r\n"));
			auto iter = pDieDetail->LuxCalculate.Count2LuxMapping.begin();
			while (iter != pDieDetail->LuxCalculate.Count2LuxMapping.end())
			{
				csTemp.Format(_T("%sRatio%d = %lf\r\n"),
					csTemp.GetString(), i, iter->first);
				csTemp.Format(_T("%sCoef%d = %.16lf, %.16lf\r\n\r\n"),
					csTemp.GetString(), i, iter->second.first, iter->second.second);
				mIniFile.Write(csTemp, 2 * csTemp.GetLength());
				i++;
				iter++;
			}
		}

		if (pDieDetail->CCTCalculate.RegressCoefMapping.size() != 0)
		{
			uint8_t i = 0;
			CString XYZ[3] = { _T("X"), _T("Y"), _T("Z") };
			csTemp.Format(_T("[CCTCalculate]\r\n"));
			auto iter = pDieDetail->CCTCalculate.RegressCoefMapping.begin();
			while (iter != pDieDetail->CCTCalculate.RegressCoefMapping.end())
			{
				csTemp.Format(_T("%sRatio%d = %lf\r\n"),
					csTemp.GetString(), i, iter->first);
				auto iter2 = iter->second.begin();
				while (iter2 != iter->second.end())
				{
					csTemp.Format(_T("%s%s%d_Coef = %.16lf,%.16lf,%.16lf,%.16lf,%.16lf\r\n"),
						csTemp.GetString(), XYZ[iter2->first].GetString(), i
						, iter2->second.at(0), iter2->second.at(1), iter2->second.at(2), iter2->second.at(3), iter2->second.at(4));
					iter2++;
				}
				csTemp.Format(_T("%s\r\n"), csTemp.GetString());
				mIniFile.Write(csTemp, 2 * csTemp.GetLength());
				i++;
				iter++;
			}
		}
		mIniFile.Close();
		MessageBox(_T("INI file is no found!\nCreate new INI file at current directory."), _T("Load INI"), MB_OK);
	}
	else
	{
		csINIFileName = csCurrentDir + _T("\\");
		csINIFileName +=ffd.cFileName;
		if (FindNextFile(hFind, &ffd) != 0)
		{
			CFileDialog fOpenDlg(TRUE,
				TEXT("ini"),
				TEXT("*.ini"),
				OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
				TEXT("DI Sensor Initail Setting Files (*.ini)|*.ini||"),
				this);

			fOpenDlg.m_ofn.lpstrInitialDir = csCurrentDir;

			if (IDOK == fOpenDlg.DoModal())
				csINIFileName = fOpenDlg.GetPathName();
			else
				return;
		}
		FindClose(hFind);

		RegSet.clear();
		auto iter_RegInfo = pRegTable->RegInfo.begin();
		while (iter_RegInfo != pRegTable->RegInfo.end())
		{
			if (GetPrivateProfileString(iter_RegInfo->second.RegDesc,
				_T("Default"), _T(""),
				csTemp.GetBuffer(256), 256,
				csINIFileName))
			{
				csTemp.ReleaseBuffer();
				value = wcstol(csTemp, NULL, 0);

				if (iter_RegInfo->second.RegBits > 1)
				{
					pBitDetail = &pBitDetailMap->at(iter_RegInfo->second.BitName.at(0));
					for (uint8_t i = 0; i < iter_RegInfo->second.RegBits; i++)
					{
						if (i + 1 <= (uint8_t)pBitDetail->BitMask.size())
							iter_RegInfo->second.RegInit.at(i) = RSHIFT(value, pBitDetail->BitShift.at(i)) & pBitDetail->BitMask.at(i);
					}
				}
				else
					iter_RegInfo->second.RegInit.at(0) = value & 0xFF;

				RegSet.insert(iter_RegInfo->first);
			}

			++iter_RegInfo;
		}

		auto iter_RegSet = RegSet.begin();
		while (iter_RegSet != RegSet.end())
		{
			pRegInfo = &pRegTable->RegInfo.at(*iter_RegSet);
			if (pRegInfo->RegBits > 1)
			{
				for (uint8_t i = 0; i < pRegInfo->RegBits; i++)
				{
					if(pBitDetailMap->at(pRegInfo->BitName.at(0)).DefaultVal.size() >= (uint8_t)(i + 1))
						pBitDetailMap->at(pRegInfo->BitName.at(0)).DefaultVal.at(i) = pRegInfo->RegInit.at(i);
				}
			}
			else
			{
				auto iter_BitName = pRegInfo->BitName.begin();
				while (iter_BitName != pRegInfo->BitName.end())
				{
					pBitDetail = &pBitDetailMap->at(iter_BitName->second);
					pBitDetail->DefaultVal.at(0) = RSHIFT((pRegInfo->RegInit.at(0) & pBitDetail->BitMask.at(0)), pBitDetail->BitShift.at(0));
					++iter_BitName;
				}
			}

			if (pRegInfo->bEngMode)
			{
				I2CWrite(0, pRegTable->DeviceID, *iter_RegSet, &pRegInfo->RegInit.at(0), pRegInfo->RegBits);
			}
			++iter_RegSet;
		}

		if (GetPrivateProfileString(_T("LuxCalculate"),
			_T("Ratio0"), _T(""),
			csTemp.GetBuffer(2048), 2048,
			csINIFileName))
		{
			csTemp.ReleaseBuffer();

		}

		uint8_t i = 0;
		CString csKeyName;
		while (1)
		{
			csKeyName.Format(_T("Ratio%d"), i);
			if (GetPrivateProfileString(_T("CCTCalculate"),
				csKeyName, NULL,
				csTemp.GetBuffer(256), 256,
				csINIFileName))
			{
				if(i == 0)
					pDieDetail->CCTCalculate.RegressCoefMapping.clear();

				csTemp.ReleaseBuffer();
				double ratio = wcstod(csTemp, NULL);
				CString XYZ[3] = { _T("X"), _T("Y"), _T("Z") };

				for (uint8_t j = 0; j < 3; j++)
				{
					csKeyName.Format(_T("%s%d_Coef"),XYZ[j].GetString(), i);
					GetPrivateProfileString(_T("CCTCalculate"),
						csKeyName, NULL,
						csTemp.GetBuffer(256), 256,
						csINIFileName);

					csTemp.ReleaseBuffer();
					for (uint8_t k = 0; k < 5; k++)
					{
						pDieDetail->CCTCalculate.RegressCoefMapping[ratio][j][k] = wcstod(csTemp.Left(csTemp.Find(_T(","))), NULL);
						csTemp = csTemp.Mid(csTemp.Find(_T(",")) + 1);
					}
				}

				i++;
			}
			else
				break;
		}
	}
}

void CDIDemoProgramDlg::SaveINIFile()
{
	int32_t value;
	CString csTemp = _T("");
	CString csValue = _T("");

	if (PathFileExists(csINIFileName))
	{
		auto iter_RegInfo = pRegTable->RegInfo.begin();
		while (iter_RegInfo != pRegTable->RegInfo.end())
		{
			if (iter_RegInfo->second.bEngMode)
			{
				++iter_RegInfo;
				continue;
			}
			if (iter_RegInfo->second.BitName.count(0))
				if (!iter_RegInfo->second.BitName.at(0).IsEmpty())
					if (pBitDetailMap->at(iter_RegInfo->second.BitName.at(0)).BitRW == ONLY_R)
					{
						++iter_RegInfo;
						continue;
					}

			value = 0;
			if (iter_RegInfo->second.RegBits > 1)
			{
				for (uint8_t i = 0; i < iter_RegInfo->second.RegBits; i++)
				{
					if ((i + 1) <= (uint8_t)pBitDetail->BitMask.size())
						value += LSHIFT(iter_RegInfo->second.RegCurVal.at(i), pBitDetailMap->at(iter_RegInfo->second.BitName.at(0)).BitShift.at(i));
				}
			}
			else
			{
				value = iter_RegInfo->second.RegCurVal.at(0);
			}

			switch (iter_RegInfo->second.RegBits)
			{
			case 1:	csTemp.Format(_T("0x%02X"), value);	break;
			case 2:	csTemp.Format(_T("0x%04X"), value);	break;
			case 4:	csTemp.Format(_T("0x%08X"), value);	break;
			}

			WritePrivateProfileString(iter_RegInfo->second.RegDesc, _T("Default"), csTemp, csINIFileName);
			++iter_RegInfo;
		}

		MessageBox(_T("Save Done!"), _T("Save INI"), MB_OK);
	}
	else
		MessageBox(_T("File is no exist!"), _T("Save INI"), MB_OK | MB_ICONEXCLAMATION);
}


void CDIDemoProgramDlg::OnClickedI2CTool()
{
	CI2CDlg* m_pI2CDlg = new CI2CDlg();
	KillTimer(CheckSensorTime);

	if(bDetectSensor)
		CloseLoopRead();

	this->ShowWindow(SW_HIDE);
	CustomShowWindows(mmModelLess, SW_HIDE);
	CustomShowWindows(mmModelLess_List, SW_HIDE);

	m_pI2CDlg->DoModal();
	m_pI2CDlg = NULL;

	this->ShowWindow(SW_SHOW);
	CustomShowWindows(mmModelLess, SW_SHOW);
	CustomShowWindows(mmModelLess_List, SW_SHOW);


	SendMessage(WM_MESSAGE_RELOAD_REG);
	PostMessage(WM_MESSAGE_UPDATEUI, 1);

	if (bDetectSensor)
	{
		SendMessage(WM_MESSAGE_CHANGE_CONVERSION_TIME);
		SendMessage(WM_MESSAGE_CALCULATE_POWER);
	}

	SetTimer(CheckSensorTime, 1000, NULL);
}


afx_msg LRESULT CDIDemoProgramDlg::OnMessageReloadReg(WPARAM wParam, LPARAM lParam)
{
	uint8_t result = STATUS_OK;

	if (pRegInfoMap == NULL)
		return 0;

	auto iter = pRegInfoMap->begin();
	while (iter != pRegInfoMap->end())
	{
		int retry = 3;
		do {
			result = I2CRead(0, pRegTable->DeviceID, iter->first, &iter->second.RegCurVal.at(0), iter->second.RegBits, 0, 0, 1000);
		} while (result != STATUS_OK && retry > 0);
		++iter;
	}

	return 0;
}


void CDIDemoProgramDlg::SensorInitial()
{
	set<uint8_t> Reg;
	map<uint8_t, map<uint8_t, uint8_t> > RegWrite;
	uint8_t result = STATUS_OK;

	auto iter_RegInfo = pRegInfoMap->begin();
	while (iter_RegInfo != pRegInfoMap->end())
	{
		auto iter_BitName = iter_RegInfo->second.BitName.begin();
		while (iter_BitName != iter_RegInfo->second.BitName.end())
		{
			pBitDetail = &pBitDetailMap->at(iter_BitName->second);
			if (pBitDetail->BitRW != ONLY_R)
			{
				for (int i = 0; i < iter_RegInfo->second.RegBits; i++)
				{
					if ((i + 1) <= (uint8_t)pBitDetail->BitMask.size())
					{	
						if (LSHIFT(pBitDetail->DefaultVal.at(i), (pBitDetail->BitShift.at(i) % 8))
							!= (iter_RegInfo->second.RegCurVal.at(i) & pBitDetail->BitMask.at(i)))
						{
							Reg.insert(iter_RegInfo->first);
							break;
						}
					}
				}
			}
			++iter_BitName;
		}
		++iter_RegInfo;
	}

	auto iter_reg = Reg.begin();
	while (iter_reg != Reg.end())
	{
		pRegInfo = &pRegInfoMap->at(*iter_reg);
		for(int i = 0; i < pRegInfo->RegBits; i++)
			RegWrite[*iter_reg][i] = 0;

		auto iter_BitName = pRegInfo->BitName.begin();
		while (iter_BitName != pRegInfo->BitName.end())
		{
			pBitDetail = &pBitDetailMap->at(iter_BitName->second);
			for (int i = 0; i < pRegInfo->RegBits; i++)
			{
				if(pBitDetail->BitShift.size() >= (uint8_t)(i + 1))
					RegWrite.at(*iter_reg).at(i) += LSHIFT(pBitDetail->DefaultVal.at(i), (pBitDetail->BitShift.at(i) % 8));
			}
			++iter_BitName;
		}
		++iter_reg;
	}

	auto iter_RegWrite = RegWrite.begin();
	while(iter_RegWrite != RegWrite.end())
	{
		vector<uint8_t> u8_temp;

		auto iter = iter_RegWrite->second.begin();
		while (iter != iter_RegWrite->second.end())
		{
			u8_temp.push_back(iter->second);
			++iter;
		}		

		int retry = 3;
		do {			
			result = I2CWrite(0, pRegTable->DeviceID, iter_RegWrite->first, u8_temp.data(), (uint8_t)u8_temp.size());
			Sleep(30);
		} while (result != STATUS_OK && retry-- > 0);
		
		if(result == STATUS_OK)
		{
			I2CRead(0, pRegTable->DeviceID, iter_RegWrite->first, u8_temp.data(), (uint16_t)u8_temp.size(), 0, 0, 1000);
			for (size_t i = 0; i < u8_temp.size(); i++)
			{
				pRegInfoMap->at(iter_RegWrite->first).RegCurVal.at(i) = u8_temp[i];
			}
		}
		++iter_RegWrite;
	}

	if (RegWrite.size() > 0)
		SendMessage(WM_MESSAGE_UPDATEUI, 1);
}


afx_msg LRESULT CDIDemoProgramDlg::OnMessageChangeConversionTime(WPARAM wParam, LPARAM lParam)
{
	CString csTemp;

	ConversionTime = DI_Sensor.GetConversionTime(SensorName);
	if(ConversionTime == 0)
		csTemp = _T("Conv Time: 0 ms");
	else
		csTemp.Format(_T("Conv Time: %.2f ms"), (double)ConversionTime / 1000.0);
	mStatusBar.SetPaneText(1, csTemp);

	if (bDetectSensor && mBtnRun.GetCheck())
	{		
		CloseLoopRead();
		SetLoopRead();
	}

	return 0;
}


afx_msg LRESULT CDIDemoProgramDlg::OnMessageCalibration(WPARAM wParam, LPARAM lParam)
{
	int value = (int)wParam;

	TRACE(_T("value %d\n"), value);

	if (value == 0)
	{
		bCalibration = true;
		pCtrlDetail_Cali = (CCtrlDetail*)lParam;
	}
	else if(value > 0)
	{
		CustomMessage(mmTabPage, WM_MESSAGE_CALIBRATION, wParam, lParam);
	}

	return 0;
}


BOOL CDIDemoProgramDlg::DestroyWindow()
{
	DestroyCtrl();
	mStatusBar.DestroyWindow();
	mToolTip->DestroyToolTipCtrl();
	UnregisterDeviceNotification(m_HDevNotify);

	pSensorInfo = NULL;
	pDieDetail = NULL;
	pBitDetailMap = NULL;
	pRegInfoMap = NULL;
	pBitDetail = NULL;
	pRegTable = NULL;
	pRegInfo = NULL;
	pCtrlDetail_Cali = NULL;
	mToolTip = NULL;
	m_HDevNotify = NULL;

	return CDialogEx::DestroyWindow();
}


void CDIDemoProgramDlg::OnClickedAbout()
{
	CAbout* m_pAbout = new CAbout();
	m_pAbout->DoModal();
}


void CDIDemoProgramDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == IDM_ABOUTBOX)
	{
		CAbout* m_pAbout = new CAbout();
		m_pAbout->DoModal();
	}

	CDialogEx::OnSysCommand(nID, lParam);
}


afx_msg LRESULT CDIDemoProgramDlg::OnMessageUpdateInfo(WPARAM wParam, LPARAM lParam)
{
	CustomMessage(mmTabPage, WM_MESSAGE_UPDATE_INFO, wParam, lParam);
	return 0;
}

afx_msg LRESULT CDIDemoProgramDlg::OnMessageChangeScale(WPARAM wParam, LPARAM lParam)
{
	CustomMessage(mmModelLess, WM_MESSAGE_CHANGE_SCALE, wParam, lParam);
	return 0;
}

afx_msg LRESULT CDIDemoProgramDlg::OnMessageChangeNameMapping(WPARAM wParam, LPARAM lParam)
{
	CustomMessage(mmTabPage, WM_MESSAGE_CHANGE_NAMEMAPPING, wParam, lParam);
	return 0;
}

afx_msg LRESULT CDIDemoProgramDlg::OnMessageCalculatePower(WPARAM wParam, LPARAM lParam)
{
	CString csTemp;

	PowerConsumption = DI_Sensor.GetPowerConsumption(SensorName);
	if (PowerConsumption <= 0.0)
		csTemp = _T("PWR Consumption: No Define");
	else
	{
		if(PowerConsumption > 1000)
			csTemp.Format(_T("PWR Consumption: %.3f mA"), PowerConsumption / 1000.0);
		else
			csTemp.Format(_T("PWR Consumption: %.2f uA"), PowerConsumption);
	}
	mStatusBar.SetPaneText(2, csTemp);

	if (bDetectSensor && mBtnRun.GetCheck())
	{
		CloseLoopRead();
		SetLoopRead();
	}
	return 0;
}

afx_msg LRESULT CDIDemoProgramDlg::OnMessageAutoDac(WPARAM wParam, LPARAM lParam)
{
	int run = mBtnRun.GetCheck();

	mBtnRun.SetCheck(0);
	OnClickedRun();

	DI_Sensor.AutoDac(SensorName);

	mBtnRun.SetCheck(run);
	OnClickedRun();

	SendMessage(WM_MESSAGE_UPDATEUI, 1);
//	PostMessage(WM_MESSAGE_CALIBRATION, 0, (LPARAM)lParam);
	return 0;
}

afx_msg LRESULT CDIDemoProgramDlg::OnMessageSLSuppression(WPARAM wParam, LPARAM lParam)
{
	bSLActive = (BOOL)wParam;	

	return 0;
}
