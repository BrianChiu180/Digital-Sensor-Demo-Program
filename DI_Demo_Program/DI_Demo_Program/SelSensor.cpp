// SelSensor.cpp : implementation file
//

#include "stdafx.h"
#include "SelSensor.h"
#include "DI_Sensor.h"
#include "afxdialogex.h"


// CSelSensor dialog

IMPLEMENT_DYNAMIC(CSelSensor, CDialogEx)

CSelSensor::CSelSensor(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSelSensor::IDD, pParent), pDISensor(NULL), SensorAddress(0), Version(0) {

}

CSelSensor::~CSelSensor() {
}

void CSelSensor::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, mComboSensor);
	DDX_Control(pDX, IDC_COMBO2, mComboVersion);
	DDX_Control(pDX, IDC_COMBO3, mComboAddress);
	DDX_Control(pDX, IDC_GROUP3, mGroupAddress);
}


BEGIN_MESSAGE_MAP(CSelSensor, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSelSensor::OnSelchangeSensor)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CSelSensor::OnSelchangeVersion)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CSelSensor::OnSelchangeAddress)	
END_MESSAGE_MAP()


// CSelSensor message handlers


BOOL CSelSensor::OnInitDialog() {
	CDialogEx::OnInitDialog();

	map<CString, CSensorInfo*>::iterator
		iter = pDISensor->SensorMap.begin();

	while (iter != pDISensor->SensorMap.end())
	{
		mComboSensor.AddString(iter->first);
		++iter;
	}

	SensorName = _T("");
	Version = 0;
	SensorAddress = 0;

	mGroupAddress.ShowWindow(SW_HIDE);
	mComboAddress.ShowWindow(SW_HIDE);

	return TRUE;
}


void CSelSensor::OnSelchangeSensor() {
	CString csTemp;

	mComboSensor.GetLBText(mComboSensor.GetCurSel(), SensorName);

	set<uint16_t>::iterator iter;
	iter = pDISensor->SensorMap.at(SensorName)->ModelVersion.begin();

	mComboVersion.ResetContent();
	while (iter != pDISensor->SensorMap.at(SensorName)->ModelVersion.end())
	{
		csTemp.Format(_T("%d.%02d"), *iter / 10000, ((*iter % 10000) / 100));
		mComboVersion.AddString(csTemp);
		Version = *iter;
		++iter;
	}

	mComboVersion.SetCurSel(mComboVersion.GetCount() - 1);
	OnSelchangeVersion();

	if (!pDISensor->SensorMap.at(SensorName)->ModelSelAddress.empty())
	{
		mGroupAddress.ShowWindow(SW_SHOW);
		mComboAddress.ShowWindow(SW_SHOW);

		set<uint8_t>::iterator iter2;
		int nSelect = 0;
		iter2 = pDISensor->SensorMap.at(SensorName)->ModelSelAddress.begin();
		mComboAddress.ResetContent();
		while (iter2 != pDISensor->SensorMap.at(SensorName)->ModelSelAddress.end())
		{
			csTemp.Format(_T("0x%02X"), *iter2);
			mComboAddress.AddString(csTemp);
			++iter2;
		}

		for(int i = 0; i < mComboAddress.GetCount(); i++)
		{
			mComboAddress.SetCurSel(i);
			mComboAddress.GetLBText(mComboAddress.GetCurSel(), csTemp);
			SensorAddress = (uint8_t)_tcstol(csTemp, NULL, 16);
			if (SensorAddress == pDISensor->SensorMap.at(SensorName)->ModelDefaultAddress)
				break;
		}
	}
	else
	{
		mGroupAddress.ShowWindow(SW_HIDE);
		mComboAddress.ShowWindow(SW_HIDE);
		SensorAddress = 0x00;
	}
}


void CSelSensor::OnSelchangeVersion() {
	CString csTemp;

	mComboVersion.GetLBText(mComboVersion.GetCurSel(), csTemp);

	Version = (uint16_t)(_ttof(csTemp) * 10000);
}

void CSelSensor::OnSelchangeAddress() {
	CString csTemp;

	mComboAddress.GetLBText(mComboAddress.GetCurSel(), csTemp);

	SensorAddress = (uint8_t)_tcstol(csTemp, NULL, 16);
}

void CSelSensor::OnOK() {
	if (SensorName.IsEmpty())
		MessageBoxW(_T("You need to select a Sensor before you click \"OK\"!"), _T("Warning"), MB_OK);
	else
		CDialogEx::OnOK();
}

