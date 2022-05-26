#pragma once

#include "Define.h"

#include "AP306E.h"
#include "AP3172.h"
#include "CS5072.h"
#include "CP507C.h"
#include "CP5076.h"
#include "AL306L.h"
#include "AL3070.h"
#include "AP3276.h"
#include "AP3272.h"
#include "AP3076.h"
#include "AP317E.h"
#include "AP337E.h"
#include "AP307E.h"
#include "AP3176.h"
#include "AP3426.h"
#include "AP314AQ.h"
#include "AL3320.h"
#include "CS5032.h"
#include "AL3010.h"
#include "AL3472.h"
#include "AL3042.h"
#include "DA3110.h"
#include "DA3111.h"
#include "AL3001.h"

#if defined(_AP3220) || defined(_DEBUG)
	#include "AP3220.h"
#endif

#include "PX318J.h"
#include "PX338N.h"
#include "PX328J.h"
#include "PX688R.h"
#include "NPX_Demo.h"
#include "VCNL_Demo.h"
#include "AL3092.h"
#include "PX3028.h"
#include "PX31BF.h"


#include "PXANALOG.h"

#include "AP309M.h"
#include "AP35AM.h"
#include "CS5092.h"
//Eminent
#include "MN26005U.h"
#include "MN58406D.h"
//Ritchtek
#include "DI3135.h"

class CDI_Sensor
{
public:
	CDI_Sensor();
	~CDI_Sensor();
	void Init(CString name, uint16_t version);
	int32_t GetConversionTime(CString name);
	double GetPowerConsumption(CString name);
	void AutoDac(CString name);
	uint8_t GetIntFlag(CString name);
	bool SLSuppression(CString name, uint8_t* SunLight_Status);
	map<CString, CSensorInfo*> SensorMap;   /*< ModelName , @ref CSensorInfo @code ModelName = _T("AP3220");*/

private:
	CAP306E Sensor_AP306E;
	CAP3172 Sensor_AP3172;
	CCS5072 Sensor_CS5072;
	CCP507C Sensor_CP507C;
	CCP5076 Sensor_CP5076;
	CAL306L Sensor_AL306L;
	CAL3070 Sensor_AL3070;
	CAP3276 Sensor_AP3276;
	CAP3272 Sensor_AP3272;
	CAP3076 Sensor_AP3076;
	CAP317E Sensor_AP317E;
	CAP337E Sensor_AP337E;
	CAP307E Sensor_AP307E;
	CAP3176 Sensor_AP3176;
	CAP3426 Sensor_AP3426;
	CAP314AQ Sensor_AP314AQ;
	CAL3320 Sensor_AL3320;
	CCS5032 Sensor_CS5032;
	CAL3010 Sensor_AL3010;
	CAL3472 Sensor_AL3472;
	CAL3042 Sensor_AL3042;
	CDA3110	Sensor_DA3110;
	CDA3111 Sensor_DA3111;

#if defined(_AP3220) || defined(_DEBUG)
	CAP3220 Sensor_AP3220;
#endif

	CPX318J Sensor_PX318J;
	CPX328J Sensor_PX328J;
	CPX338N Sensor_PX338N;
	CPX688R Sensor_PX688R;
	CNPX_DEMO Sensor_NPX_DEMO;
	CVCNL_DEMO Sensor_VCNL_DEMO;
	CMN26005U Sensor_MN26005U;
	CMN58406D Sensor_MN58406D;
	CDI3135	Sensor_DI3135;
	CAL3092 Sensor_AL3092;
	CPX3028 Sensor_PX3028;

	CAP309M Sensor_AP309M;
	CCS5092 Sensor_CS5092;
	CAP35AM Sensor_AP35AM;
	CPXANALOG Sensor_PXANALOG;

	CPX31BF Sensor_PX31BF;
	CAL3001 Sensor_AL3001;
};
