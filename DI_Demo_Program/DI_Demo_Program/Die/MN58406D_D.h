#pragma once
#include "Define.h"

class CMN58406D_D : public CDieInfo {
public:
	CMN58406D_D() {}
	void Init(uint16_t version)
	{
		DieName = _T("MN58406D_D");
		switch (version)
		{
		case 4000:
			DieDetail.insert(make_pair(4000, CDieDetail()));
			{
				pDieDetail = &DieDetail.at(4000);
				pRegTable = &pDieDetail->RegisterTable;

				pRegTable->DeviceID = 0x41;

				pRegTable->SetRegAddr(0x00);
				pRegTable->SetRegInfo({ 0x00 }, _T("Reg0x00"));
				{
					pRegTable->SetBitDetail(_T("WTIME"), _T("Wait Time"), 0xF0, 4, BOTH_RW, { 0, 0x0F });
					pRegTable->SetBitDetail(_T("MODE"), _T("Mode"), 0x03, 0, BOTH_RW, { 0, 3 });
				}

				pRegTable->SetRegAddr(0x01);
				pRegTable->SetRegInfo({ 0x1F }, _T("Reg0x01"));
				{
					pRegTable->SetBitDetail(_T("ALS_INTEG"), _T("ALS Integration Time"), 0x3C, 2, BOTH_RW, { 0, 0x0F }, 0x07);
					pRegTable->SetBitDetail(_T("ALS_GAINS"), _T("ALS Gain Setting"), 0x03, 0, BOTH_RW, { 0, 3 }, 0x03);
				}

				pRegTable->SetRegAddr(0x02);
				pRegTable->SetRegInfo({ 0x15 }, _T("Reg0x02"));
				{
					pRegTable->SetBitDetail(_T("ALS_FILTER"), _T("Filter Order Setting"), 0x07, 0, BOTH_RW, { 0, 7 }, 0x05);
				}

				pRegTable->SetRegAddr(0x03);
				pRegTable->SetRegInfo({ 0x1F }, _T("Reg0x03"));
				{
					pRegTable->SetBitDetail(_T("PS_INTEG"), _T("PS Integration Time"), 0x3C, 2, BOTH_RW, { 0, 0x0F }, 0x07);
					pRegTable->SetBitDetail(_T("PS_GAINS"), _T("PS Gain Setting"), 0x03, 0, BOTH_RW, { 0, 3 }, 0x03);
				}

				pRegTable->SetRegAddr(0x04);
				pRegTable->SetRegInfo({ 0x13 }, _T("Reg0x04"));
				{
					pRegTable->SetBitDetail(_T("PS_FILTER"), _T("Filter Order Setting"), 0x07, 0, BOTH_RW, { 0, 7 }, 0x03);
				}

				pRegTable->SetRegAddr(0x05);
				pRegTable->SetRegInfo({ 0x23 }, _T("Reg0x05"));
				{
					pRegTable->SetBitDetail(_T("PS_IR_MODE"), 4, _T("Comparator High Bit"), 0);
					pRegTable->SetBitDetail(_T("PS_IR_DRIVE"), _T("Filter Order Setting"), 0x03, 0, BOTH_RW, { 0, 3 }, 0x03);
				}

				pRegTable->SetRegAddr(0x06);
				pRegTable->SetRegInfo({ 0x20 }, _T("Reg0x06"));
				{
					pRegTable->SetBitDetail(_T("INT_CTRL"), _T("Interrupt Control"), 0x30, 4, BOTH_RW, { 0, 3 }, 0x02);
					pRegTable->SetBitDetail(_T("PS_PERSIST"), _T("Interrupt Persistence"), 0x0C, 2, BOTH_RW, { 0, 3 }, 0x00);
					pRegTable->SetBitDetail(_T("PS_INTTY"), _T("Interrupt Mode Selection"), 0x03, 0, BOTH_RW, { 0, 3 }, 0x00);
				}

				pRegTable->SetRegAddr(0x07);
				pRegTable->SetRegInfo({ 0x00 }, _T("Reg0x07"));
				{
					pRegTable->SetBitDetail(_T("ALS_PERSIST"), _T("Interrupt Persistence"), 0x0C, 2, BOTH_RW, { 0, 3 }, 0x00);
					pRegTable->SetBitDetail(_T("ALS_INTTY"), _T("Interrupt Mode Selection"), 0x03, 0, BOTH_RW, { 0, 3 }, 0x00);
				}

				pRegTable->SetRegAddr(0x08);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("ALS_INT_L"), 2);
				{
					pRegTable->SetBitDetail2(_T("ALS_INT_L"), { 0x00, 0x00 });
				}

				pRegTable->SetRegAddr(0x0A);
				pRegTable->SetRegInfo({ 0xFF, 0xFF }, _T("ALS_INT_H"), 2);
				{
					pRegTable->SetBitDetail2(_T("ALS_INT_H"), { 0xFF, 0xFF });
				}

				pRegTable->SetRegAddr(0x0C);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("PS_INT_L"), 2);
				{
					pRegTable->SetBitDetail2(_T("PS_INT_L"), { 0x00, 0x00 });
				}

				pRegTable->SetRegAddr(0x0E);
				pRegTable->SetRegInfo({ 0xFF, 0xFF }, _T("PS_INT_H"), 2);
				{
					pRegTable->SetBitDetail2(_T("PS_INT_H"), { 0xFF, 0xFF });
				}

				pRegTable->SetRegAddr(0x11);
				pRegTable->SetRegInfo({ 0x03 }, _T("Reg0x11"));
				{
					pRegTable->SetBitDetail(_T("RESETN"), 1, _T("Chip Reset Control"), 0x01);
					pRegTable->SetBitDetail(_T("SLEEP"), 0, _T("Chip Sleep Mode Setting"), 0x01);
				}

				pRegTable->SetRegAddr(0x12);
				pRegTable->SetRegInfo({ 0x02 }, _T("Reg0x12"));
				{
					pRegTable->SetBitDetail(_T("ALS_CMP_H"), 4, _T("Comparator High Bit"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("ALS_CMP_L"), 3, _T("Comparator Low Bit"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("ALS_INT_FLAG"), 2, _T("Interrupt Flag"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("ALS_CMP_RSTN"), 1, _T("Comparator Reset Control"), 1);
					pRegTable->SetBitDetail(_T("ALS_LOCK"), 0, _T("ALS Data Lock Setting"));
				}

				pRegTable->SetRegAddr(0x13);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("CH0_DATA"), 2);
				{
					pRegTable->SetBitDetail2(_T("CH0_DATA"), _T("CH0_DATA"));
				}

				pRegTable->SetRegAddr(0x15);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("CH1_DATA"), 2);
				{
					pRegTable->SetBitDetail2(_T("CH1_DATA"), _T("CH1_DATA"));
				}

				pRegTable->SetRegAddr(0x1B);
				pRegTable->SetRegInfo({ 0x02 }, _T("Reg0x1B"));
				{
					pRegTable->SetBitDetail(_T("PS_CMP_H"), 4, _T("Comparator High Bit"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("PS_CMP_L"), 3, _T("Comparator Low Bit"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("PS_INT_FLAG"), 2, _T("Interrupt Flag"), 0, ONLY_R);
					pRegTable->SetBitDetail(_T("PS_CMP_RSTN"), 1, _T("Comparator Reset Control"), 1);
					pRegTable->SetBitDetail(_T("PS_LOCK"), 0, _T("PS Data Lock Setting"));
				}

				pRegTable->SetRegAddr(0x1C);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("PALS_DATA"), 2);
				{
					pRegTable->SetBitDetail2(_T("PALS_DATA"), _T("PALS_DATA"));
				}

				pRegTable->SetRegAddr(0x1E);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("PS_DATA"), 2);
				{
					pRegTable->SetBitDetail2(_T("PS_DATA"), _T("PS_DATA"));
				}

				pRegTable->SetRegAddr(0x20);
				pRegTable->SetRegInfo({ 0x88 }, _T("Reg0x20"));
				{
					pRegTable->SetBitDetail(_T("REVNO"), _T("Revision Number"), 0xFF, 0, ONLY_R);
				}

				pRegTable->SetRegAddr(0x22);
				pRegTable->SetRegInfo({ 0x00, 0x00 }, _T("PS_OFFSET"), 2);
				{
					pRegTable->SetBitDetail2(_T("PS_OFFSET"), _T("PS_OFFSET"));
				}
			}
			break;

		default: return;
		}

		MappingBitName2Reg();
	}

	uint32_t GetConversionTime(uint16_t version, CRegisterTable* pRegTable)
	{
		uint8_t Reg0x00;
		map<CString, CBitDetail>* pBitDetailMap;
		Reg0x00 = pRegTable->RegInfo.at(0x00).RegCurVal.at(0);
		pBitDetailMap = &pRegTable->BitDetail;

		ConversionTime = 100;

		return (uint32_t)(ConversionTime * 1000);
	}
};