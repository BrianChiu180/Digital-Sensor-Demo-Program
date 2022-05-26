#pragma once
#include "Define.h"
#include "DI_Sensor.h"
#include "afxwin.h"

// CSelSensor dialog

class CSelSensor : public CDialogEx {
	DECLARE_DYNAMIC(CSelSensor)

public:
	CSelSensor(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelSensor();

	// Dialog Data
	enum { IDD = IDD_SELSENSOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	void SetSensorInfo(CDI_Sensor* DISensor) {
		this->pDISensor = DISensor;
	}
private:
	CDI_Sensor* pDISensor;
	CComboBox mComboSensor;
	CComboBox mComboVersion;
	CComboBox mComboAddress;
	CStatic mGroupAddress;
public:
	CString SensorName;
	uint16_t Version;
	uint8_t  SensorAddress;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeSensor();
	afx_msg void OnSelchangeVersion();
	afx_msg void OnSelchangeAddress();
	virtual void OnOK();	
};
