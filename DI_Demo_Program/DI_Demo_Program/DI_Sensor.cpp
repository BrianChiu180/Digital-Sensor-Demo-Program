#include "stdafx.h"
#include "DI_Sensor.h"

CDI_Sensor::CDI_Sensor() {
	SensorMap.clear();
#if defined(_AP306E) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_AP306E.ModelName, &Sensor_AP306E));
#endif

#if defined(_AP3172) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_AP3172.ModelName, &Sensor_AP3172));
#endif

#if defined(_AP3176) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_AP3176.ModelName, &Sensor_AP3176));
#endif

#if defined(_CS5072) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_CS5072.ModelName, &Sensor_CS5072));
#endif

#if defined(_CP507C) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_CP507C.ModelName, &Sensor_CP507C));
#endif

#if defined(_CP5076) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_CP5076.ModelName, &Sensor_CP5076));
#endif

#if defined(_AP3276) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_AP3276.ModelName, &Sensor_AP3276));
#endif

#if defined(_AP3272) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_AP3272.ModelName, &Sensor_AP3272));
#endif

#if defined(_AP3076) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_AP3076.ModelName, &Sensor_AP3076));
#endif

#if defined(_AP317E) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_AP317E.ModelName, &Sensor_AP317E));
#endif

#if defined(_AP337E) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_AP337E.ModelName, &Sensor_AP337E));
#endif

#if defined(_AP307E) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_AP307E.ModelName, &Sensor_AP307E));
#endif

#if defined(_AL306L) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_AL306L.ModelName, &Sensor_AL306L));
#endif

#if defined(_AL3070) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_AL3070.ModelName, &Sensor_AL3070));
#endif

#if defined(_AP3426) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_AP3426.ModelName, &Sensor_AP3426));
#endif

#if defined(_AP314AQ) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_AP314AQ.ModelName, &Sensor_AP314AQ));
#endif

#if defined(_AL3320) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_AL3320.ModelName, &Sensor_AL3320));
#endif

#if defined(_CS5032) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_CS5032.ModelName, &Sensor_CS5032));
#endif

#if defined(_AL3010) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_AL3010.ModelName, &Sensor_AL3010));
#endif

#if defined(_AL3472) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_AL3472.ModelName, &Sensor_AL3472));
#endif

#if defined(_AL3042) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_AL3042.ModelName, &Sensor_AL3042));
#endif

#if defined(_DA3110) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_DA3110.ModelName, &Sensor_DA3110));
#endif

#if defined(_DA3111) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_DA3111.ModelName, &Sensor_DA3111));
#endif

#if defined(_AP3220) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_AP3220.ModelName, &Sensor_AP3220));
#endif

#if defined(_MN26005U) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_MN26005U.ModelName, &Sensor_MN26005U));
#endif

#if defined(_MN58406D) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_MN58406D.ModelName, &Sensor_MN58406D));
#endif

#if defined(_PX318J) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_PX318J.ModelName, &Sensor_PX318J));
#endif

#if defined(_PX328J) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_PX328J.ModelName, &Sensor_PX328J));
#endif

#if defined(_PX338N) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_PX338N.ModelName, &Sensor_PX338N));
#endif

#if defined(_PX688R) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_PX688R.ModelName, &Sensor_PX688R));
#endif

#if defined(_PX3028) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_PX3028.ModelName, &Sensor_PX3028));
#endif

#if defined(_DI3135) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_DI3135.ModelName, &Sensor_DI3135));
#endif

#if defined(_NPX_DEMO) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_NPX_DEMO.ModelName, &Sensor_NPX_DEMO));
#endif

#if defined(_VCNL_DEMO) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_VCNL_DEMO.ModelName, &Sensor_VCNL_DEMO));
#endif

#if defined(_AL3092) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_AL3092.ModelName, &Sensor_AL3092));
#endif

#if defined(_AP309M) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_AP309M.ModelName, &Sensor_AP309M));
#endif

#if defined(_CS5092) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_CS5092.ModelName, &Sensor_CS5092));
#endif

#if defined(_AP35AM) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_AP35AM.ModelName, &Sensor_AP35AM));
#endif

#if defined(_PXANALOG) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_PXANALOG.ModelName, &Sensor_PXANALOG));
#endif

#if defined(_PX31BF) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_PX31BF.ModelName, &Sensor_PX31BF));
#endif

#if defined(_AL3001) || defined(_DEBUG)
	SensorMap.insert(make_pair(Sensor_AL3001.ModelName, &Sensor_AL3001));
#endif

}

CDI_Sensor::~CDI_Sensor() {
	SensorMap.clear();
}

void CDI_Sensor::Init(CString name, uint16_t version) {
	CSensorInfo *Selected_SensorMap_SensorInfo = NULL;
	CDieInfo *Selected_SensorMap_DieInfo = NULL;

	map<CString, CSensorInfo*>::iterator
		iter = SensorMap.begin();

	while (iter != SensorMap.end())
	{
		if (name.Find(iter->first) == 0)
		{
			Selected_SensorMap_SensorInfo = iter->second; // Mapping to SensorMap's SensorInfo(such as Sensor_AP306E, Sensor_AP3220...)
			Selected_SensorMap_DieInfo = iter->second->pDieInfo; 
			break;
		}
		++iter;
	}

	if (Selected_SensorMap_SensorInfo != NULL)
		Selected_SensorMap_SensorInfo->Init(version); // Go to SensorMap's selected sensor(such as Sensor_AP306E, Sensor_AP3220...) to do Init
}

uint8_t CDI_Sensor::GetIntFlag(CString name)
{
	CSensorInfo* SensorInfo = NULL;
	CDieInfo* DieInfo = NULL;

	map<CString, CSensorInfo*>::iterator
		iter = SensorMap.begin();

	while (iter != SensorMap.end())
	{
		if (name.Find(iter->first) == 0)
		{
			SensorInfo = iter->second;
			DieInfo = iter->second->pDieInfo;
			break;
		}
		++iter;
	}

	if (SensorInfo == NULL)
		return 0;

	return DieInfo->GetIntFlag(SensorInfo->DieVersion, &SensorInfo->pDieInfo->DieDetail.at(SensorInfo->DieVersion).RegisterTable);
}

int32_t CDI_Sensor::GetConversionTime(CString name) {
	CSensorInfo *SensorInfo = NULL;
	CDieInfo *DieInfo = NULL;

	map<CString, CSensorInfo*>::iterator
		iter = SensorMap.begin();

	while (iter != SensorMap.end())
	{
		if (name.Find(iter->first) == 0)
		{
			SensorInfo = iter->second; 
			DieInfo = iter->second->pDieInfo;
			break;
		}
		++iter;
	}

	if (SensorInfo == NULL)
		return 0;

	return DieInfo->GetConversionTime(SensorInfo->DieVersion, &SensorInfo->pDieInfo->DieDetail.at(SensorInfo->DieVersion).RegisterTable);
}

double CDI_Sensor::GetPowerConsumption(CString name) {
	CSensorInfo *SensorInfo = NULL;
	CDieInfo *DieInfo = NULL;

	map<CString, CSensorInfo*>::iterator
		iter = SensorMap.begin();

	while (iter != SensorMap.end())
	{
		if (name.Find(iter->first) == 0)
		{
			SensorInfo = iter->second;
			DieInfo = iter->second->pDieInfo;
			break;
		}
		++iter;
	}

	if (SensorInfo == NULL)
		return 0;

	return DieInfo->GetPowerConsumption(SensorInfo->DieVersion, &SensorInfo->pDieInfo->DieDetail.at(SensorInfo->DieVersion).RegisterTable);	
}

void CDI_Sensor::AutoDac(CString name) {
	CSensorInfo* SensorInfo = NULL;
	CDieInfo* DieInfo = NULL;

	map<CString, CSensorInfo*>::iterator
		iter = SensorMap.begin();

	while (iter != SensorMap.end())
	{
		if (name.Find(iter->first) == 0)
		{
			SensorInfo = iter->second;
			DieInfo = iter->second->pDieInfo;
			break;
		}
		++iter;
	}

	if (SensorInfo == NULL)
		return;

	DieInfo->AutoDac(SensorInfo->DieVersion, &SensorInfo->pDieInfo->DieDetail.at(SensorInfo->DieVersion).RegisterTable);
}

bool CDI_Sensor::SLSuppression(CString name, uint8_t* SunLight_Status) {
	CSensorInfo* SensorInfo = NULL;
	CDieInfo* DieInfo = NULL;

	map<CString, CSensorInfo*>::iterator
		iter = SensorMap.begin();

	while (iter != SensorMap.end())
	{
		if (name.Find(iter->first) == 0)
		{
			SensorInfo = iter->second;
			DieInfo = iter->second->pDieInfo;
			break;
		}
		++iter;
	}

	if (SensorInfo == NULL)
		return false;

	return DieInfo->SLSuppression(&SensorInfo->pDieInfo->DieDetail.at(SensorInfo->DieVersion).RegisterTable, SunLight_Status);
}