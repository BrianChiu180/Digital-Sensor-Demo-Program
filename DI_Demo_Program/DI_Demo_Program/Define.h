/**
 * @file Define.h
 *
 * @author Rocky Hsiao <rocky.hsiao@dyna-image.com>
 * @date 2017/06/27
 * @copyright Copyright(C) 2017 Dyna-Image Corporation All rights reserved.
 */
#pragma once
#include "stdafx.h"
#include <atlstr.h>
#include <set>
#include <map>
#include <vector>
#include <deque>
#include <tuple>
#include "AtmelHIDLIB.h"

#define WM_MESSAGE_UPDATEUI					(WM_USER + 0)
#define WM_MESSAGE_CHANGE_AVG_NUM			(WM_USER + 1)
#define WM_MESSAGE_CHANGE_RANGE				(WM_USER + 2)
#define WM_MESSAGE_CHANGE_SEL_DATA			(WM_USER + 3)
#define WM_MESSAGE_RELOAD_REG				(WM_USER + 4)
#define WM_MESSAGE_CHANGE_CONVERSION_TIME	(WM_USER + 5)
#define WM_MESSAGE_CALIBRATION				(WM_USER + 6)
#define WM_MESSAGE_UPDATE_INFO				(WM_USER + 7)
#define WM_MESSAGE_CALCULATE_POWER			(WM_USER + 8)
#define WM_MESSAGE_CHANGE_SCALE				(WM_USER + 9)
#define WM_MESSAGE_CHANGE_NAMEMAPPING		(WM_USER + 10)
#define WM_MESSAGE_AUTO_DAC					(WM_USER + 11)
#define WM_MESSAGE_SL_SUPPRESSION			(WM_USER + 12)

#define BIT(n) 0x01 << n

#define LSHIFT(val, shift) ((shift) > 0 ? ((val) << (shift)) : ((val) >> -(shift)))
#define RSHIFT(val, shift) ((shift) > 0 ? ((val) >> (shift)) : ((val) << -(shift)))

using namespace std;

typedef pair<CString, CString> pairCS;
typedef pair<int, int> pairINT;

//! @namespace SensorInfo
namespace SensorInfo {
	/**
	* @enum DlgSel_
	* @brief 頁面位置選擇。
	*/
	enum DlgSel_ {
		MAIN_DIALOG,	/*< 主頁面 */
		TAB_1,			/*< TAB1，主要用於SysConfig */
		TAB_2,			/*< TAB2 */
		TAB_3,			/*< TAB3 */
		TAB_4,			/*< TAB4 */
		TAB_5,			/*< TAB5 */
		TAB_6,			/*< TAB6 */
		MODEL_1,		/*< MODEL1 */
		MODEL_2,		/*< MODEL2 */
		MODEL_3,		/*< MODEL3 */
		MODEL_4,		/*< MODEL4 */
		MODEL_5			/*< MODEL5 */
	};

	/**
	* @enum StyleSel_
	* @brief 頁面風格選擇。
	*/
	enum StyleSel_ {
		NOSTYLE,		/*< 僅用於<b>MAIN_DIALOG</b> */
		PAGE_STYLE1,	/*< 用於TAB1~6 */
		MODELLESS1,		/*< 放置直向進度條使用 */
		MODELLESS_LIST	/*< 放置List使用，主要呈現Register Table資訊。 */
	};

	/**
	* @enum CtrlType_
	* @brief 控制項類別
	*/
	enum CtrlType_ {
		CTRL_TYPE_NONE,
		/**
		*	@brief 靜態文字框控制項
		*
		*	根據CCtrlDetial::CtrlFunc的值作不同功能的區分。
		*	1. CTRLFUNC_SHOWTEXT\n
		*	預設值。
		*	1. CTRLFUNC_NORMAL\n
		*	顯示十進位數字。
		*	2. CTRLFUNC_LUX\n
		*	顯示計算後的LUX值。@ref CTRLFUNC_LUX
		*	3. CTRLFUNC_CCT\n
		*	顯示計算後的CCT值。@ref CTRLFUNC_CCT
		*/
		TEXT_GROUP,
		/**
		*	@brief 下拉式選單
		*
		*	必須在CCtrlDetial::NameMapping裡寫出所有選項資料。
		*	根據CCtrlDetial::CtrlFunc的值作不同功能的區分。
		*	1. CTRLFUNC_NORMAL\n
		*	預設值。
		*	2. CTRLFUNC_SELDATA\n
		*	動態改變Progress bar內所顯示的資料，必須在RegMapping列出會使用的資料的第一個Address。
		*	3. CTRLFUNC_CHANGE_RANGE\n
		*	動態改變指定的BitName裡的Range，必須在RegMapping列出會使用的資料的第一個Address。
		*	另外必須在RangeMapping裡標出會用到的Range，後面重覆的不用標出。
		*	4. CTRLFUNC_CHANGE_CONVERSION_TIME
		*	此控制項會變動到Conversion_Time，可以用OR的方式同時放多個CTRLFUNC。
		*/
		COMBO_GROUP,
		/**
		*	@brief 文字輸入控制項
		*
		*	根據CCtrlDetial::CtrlFunc的值作不同功能的區分。
		*	1. CTRLFUNC_NORMAL\n
		*	預設值。
		*	2. CTRLFUNC_CHANGE_RANGE\n
		*	動態改變指定的BitName裡的Range，必須在RegMapping列出會使用的資料的第一個Address。\n
		*	另外必須在RangeMapping裡標出會用到的Range，後面重覆的不用標出。
		*	3. CTRLFUNC_CHANGE_CONVERSION_TIME
		*	此控制項會變動到Conversion_Time，可以用OR的方式同時放多個CTRLFUNC。
		*/
		EDIT_GROUP,
		/**
		*	@brief 按鍵控制項
		*
		*	按鍵按下去的值為BitDetail內設的Default Value。
		*	根據CCtrlDetial::CtrlFunc的值作不同功能的區分。
		*	1. CTRLFUNC_NORMAL\n
		*	預設值。
		*	2. CTRLFUNC_SWRSTS\n
		*	按下這個按鍵後會重新讀取所有在Register Table裡的Register Value。
		*/
		BUTTON_GROUP,
		CHECK_GROUP,	/*< 勾選控制項 */
		RADIO_GROUP,	/*< 多選一控制項，可加CRLFUNC_CHANGE_CONVERSION_TIME。*/
		/**
		*	@brief 進度條控制項
		*
		*	可以增加CTRLFUNC_SELDATA來動態選擇輸出資料。
		*	根據CCtrlDetial::CtrlFunc的值作不同功能的區分。
		*	1. CTRLFUNC_NORMAL\n
		*	預設值。
		*	2. CTRLFUNC_SELDATA\n
		*	必須要在regMappgin列出會使用的資料的第一個Address，regMappging的Key必須配合Combobox內的輸出值。
		*	3. CTRLFUNC_LUX\n
		*	數值使用Lux計算公式。
		*/
		PROGRESS_GROUP,
		SLIDER_GROUP,	/*<	滑捍控制項 */
		LED,			/*<	LED顯示控制項，僅用於MAIN_DIALOG顯示Interrupt Flag使用。 */
		PROGRESSBAR		/*<	進度條控制項（直），僅用於Modelless視窗。 */
	};

	/**
	* @enum BitRW_
	* @brief Bit讀寫屬性。
	*/
	enum BitRW_ {
		BOTH_RW,	/*< 同時具有讀與寫 */
		ONLY_R,		/*< 僅有讀取 */
		ONLY_W		/*< 僅有寫入 */
	};

	/**
	* @enum CtrlFunc_
	* @brief 控制項功能選擇。
	*/
	enum CtrlFunc_ {
		CTRLFUNC_NORMAL = BIT(0),	/*< 預設動作。 */
		CTRLFUNC_SWRST = BIT(1),	/*< 用於Softwave Reset使用，會對該Bit寫入Mask值。 */
		CTRLFUNC_CLEAR_INT = BIT(2),	/*< 用於Clear interrupt使用，會對該RegMapping[0]的Addr寫入0x00 */
		CTRLFUNC_CALIBRATION = BIT(3),	/*< 用於Calibration 使用，會對RegMapping[0]的Data平均後寫入BitMapping[0] */
		/**
		 * @brief 使用於TEXT_GROUP控制項，用來顯示LUX值。
		 *
		 * 計算過程需要設定<b>LuxCalculate</b>的參數。
		 * LuxFunc 指定計算使用的公式。
		 * DataRegMapping 列舉需要的資料的Register Address。
		 * RatioBitMapping 列舉影響資料比例的Bit Name。
		 * CountRatioMapping 二維陣列，前項連結RatioBitMapping的Key值，後項為該Bit的Value。	\n
		 *					 等式裡面放的是Ratio值。
		 * Count2LuxMapping 將Count轉成Lux的參數。									\n
		 *					根據不同的<b>LuxFunc</b>會有不同的意義。
		 * @example Count2LuxMapping[A] = make_pair(B, C)							\n
		 * 1. OneCH，A與C為0，B為與資料相乘的Ratio。									\n
		 * 2. TwoCH，A為CH1/CH0比例判斷值，由小到大排列。B與C分別為CH0以及CH1乘的Ratio。	\n
		 * 3. FourCH_Color，A為0，1，2，3連結<b>DataRegMapping</b>的順序。				\n
		 *	  B為與資料相乘的Ratio。 C為0。
		 */
		CTRLFUNC_LUX = BIT(4),
		/**
		* @brief 使用於TEXT_GROUP控制項，用來顯示CCT值。
		*
		* 計算過程需要設定<b>CCTCalculate</b>的參數。
		* DataRegMapping 列舉需要的資料的Register Address。
		* RatioBitMapping 列舉影響資料比例的Bit Name。
		* CountRatioMapping 二維陣列，前項連結RatioBitMapping的Key值，後項為該Bit的Value。	\n
		*					等式裡面放的是Ratio值。
		* RegressCoefMapping 二維陣列前項為0,1,2代表X，Y，Z，								\n
		*	後項Key為0,1,2,3,4依序放置𝛂(alpha), 𝛃(beta), 𝛄(gamma), 𝛅(delta)以及ε(epsilon) 參數值。
		* McCamyCCTParaMapping Key為0,1,2,3,4,5依序放置a, b, c, d, Xe, Ye 參數值。
		*/
		CTRLFUNC_CCT = BIT(5),
		CTRLFUNC_SELDATA = BIT(6),				/*< 該控制項可以改變或擁有多個資料來源。 */
		CTRLFUNC_CHANGE_RANGE = BIT(7),	/*< 該控制項可以改變某些資料的範圍大小。 */
		CTRLFUNC_CHANGE_CONVERSION_TIME = BIT(8),	/*< 該控制項會改變Conversion time。 */
		CTRLFUNC_CALCULATE_POWER = BIT(9),

		CTRLFUNC_SHOW_BRIDGE_VERSION = BIT(10),	/*< 顯示Control board的版本 */
		CTRLFUNC_SHOWTEXT = BIT(11),			/*< 該控制項用來顯示靜態文字。 */
		CTRLFUNC_SHOW_DATASHEET = BIT(12),
		CTRLFUNC_SHOW_DIEVERSION = BIT(13),
		CTRLFUNC_AXIS = BIT(14),
		CTRLFUNC_CHANGE_SCALE = BIT(15),
		CTRLFUNC_CHANGE_NAMEMAPPING = BIT(16),
		CTRLFUNC_AUTO_DAC = BIT(17),
		CTRLFUNC_SL_SUPPRESSION = BIT(18)
	};

	enum BarColor_ {
		R_BAR	= RGB(240,40,40),	//Red
		G_BAR	= RGB(40,240,80),	//Green, ALS, CH0
		B_BAR	= RGB(35,65,240),	//Blue
		C_BAR	= RGB(230,250,30),	//Comp , CH1, L
		PS_BAR	= RGB(180,32,32),	//PS
		IR_BAR	= RGB(150,150,150),	//IR
		AXIS_POS_BAR = RGB(20, 20, 220),
		AXIS_NEG_BAR = RGB(128, 128, 220)
	};

	//! @enum LuxFunc_ 列舉Lux計算公式。
	enum LuxFunc_ {
		NON_LUX,		/*< Default Value */
		OneCH,			/*< 只有一個Channel */
		TwoCH,			/*< 有兩個Channel */
		TwoCH_New,		/*< (CH0/CH1 * a + b) * (CH0 - CH1 * c) */
		FourCH_Color,	/*< 有四個Channel，For Color */
	};

	//! @enum LogFormat_ 資料LOG的格式。
	enum LogFormat_ {
		LogHex = BIT(0),
		LogDec = BIT(1),
		LogAxis = BIT(2)
	};

	//! @enum DieFunc_ Die含有的功能，使用"|"運算元組合。
	enum DieFunc_ {
		DF_NONE,
		DF_LUX = BIT(0),
		DF_CCT = BIT(1),
		DF_AXIS = BIT(2)
	};

	enum SL_SUPPRESSION_STATUS {
		SUNLIGHT_OK,
		SUNLIGHT_INC,
		SUNLIGHT_DEC,
		SUNLIGHT_TOO_STRONG
	};

	/**
	* @class CCtrlDetail
	* @brief 儲存控制項的資訊。
	*/
	class CCtrlDetail {
	public:
		enum CtrlType_ CtrlType;								//!< 控制項類別。@ref CtrlType_
		pairCS CtrlName;										//!< 控制件名稱，fist為簡易名稱，second為詳細敘述。
		pair<COLORREF, COLORREF> CtrlColor;						//!< 控制件顏色，主要用於Bar類別。
		map<uint8_t, CString> BitMapping;						//!< 連接控制件對應的BIT NAME，以0為基底，從低位元開始放置。
		map<uint8_t, CString> NameMapping;						//!< 控制件項目名稱，主要用於COMBO_GROUP。
		map<pair<uint8_t, uint8_t>, CString> NameMapping2;		//!< 控制件項目名稱，主要用於COMBO_GROUP。對應兩組Bit Setting
		map<uint8_t, pair<int, int> > RangeMapping;				//!< 用於CtrlFunc = CTRLFUNC_CHANGERNAGE，條列出所有範圍。
		map<uint8_t, uint8_t> RegMapping;						//!< 連接控制件影響的Reg
		uint32_t CtrlFunc;										//!< 控制項功能
		uint32_t I2CWriteDelayMs;								//!< 在寫入設定後Delay多久
		BOOL bActive;											//!< 觸發時是否為1。		
		map<uint8_t, double> ValueScaleMapping;					//!< 資料縮放值，主要用在計算加速度的G值。

		//! 創建<b>CCtrlDetail</b>並填入預設值。
		CCtrlDetail() : 
			CtrlType(CTRL_TYPE_NONE),
			CtrlName(make_pair(_T(""), _T(""))), 
			CtrlColor(make_pair(CLR_DEFAULT, CLR_DEFAULT)),
			CtrlFunc(CTRLFUNC_NORMAL), 
			I2CWriteDelayMs(0),
			bActive(TRUE)
			{}

		//! 創建<b>CCtrlDetail</b>並初始化。
		CCtrlDetail(enum CtrlType_ type, BOOL active = TRUE, uint32_t delayMs = 0) : 
			CtrlType(type), 
			CtrlName(make_pair(_T(""), _T(""))),
			CtrlColor(make_pair(CLR_DEFAULT, CLR_DEFAULT)),
			CtrlFunc(CTRLFUNC_NORMAL),
			bActive(active),
			I2CWriteDelayMs(delayMs)
			{}
	};

	/**
	* @class CCtrlInfo
	* @brief 儲存在頁面中所有控制項的資訊。
	*/
	class CCtrlInfo {
	public:
		map<pair<uint8_t, uint8_t>, CCtrlDetail> CtrlDetail;	/*< 控制項的座標對照表 */
	};

	/**
	* @class CBitDetail
	* @brief 儲存Bit內應有的資訊。
	*/
	class CBitDetail {
	public:
		CString csDesc;					//!< 使用Datasheet內的簡短描述。
		CString csDetailInfo;			//!< 使用Datasheet內的詳細描述。
		uint8_t RegAddr;				//!< 對應的Address。
		vector<uint8_t> BitMask;		//!< 使用的Mask(未Shift前)。
		vector<int8_t> BitShift;		//!< 位移量。
		vector<pair<uint8_t, uint8_t> >BitRange;	//!< 以pair呈現的Bit範圍設定，設定方式為make_pair()。 @code BitRange = make_pair(min, max)@endcode
		vector<uint8_t> DefaultVal;		//!< 程式內預設值。
		enum BitRW_ BitRW;				//!< @ref BitRW_ Bit讀寫屬性。
		BOOL bSign;						//!< 是否有正負號。

		//! 創建<b>CBitDetail</b>。
		CBitDetail() : 
			csDesc(_T("")), 
			csDetailInfo(_T("")), 
			RegAddr(0x00), 
			BitMask({ 0x00 }), 
			BitShift({ 0x00 }), 
			BitRange({ make_pair(0x00,0x00) }), 
			DefaultVal({ 0x00 }),
			BitRW(BOTH_RW), 
			bSign(FALSE) 
			{};

		//! 創建<b>CBitDetail</b>，並做初始化。
		CBitDetail(uint8_t RegAddr, int8_t BitShift = 0 , CString desc = _T(""), uint8_t DefaultVal = 0x00, enum BitRW_ BitRW = BOTH_RW, CString descDetail = _T(""))
			: csDesc(desc), csDetailInfo(descDetail), RegAddr(RegAddr), BitShift({ BitShift }), BitRW(BitRW), BitRange({ make_pair(0, 1) }), DefaultVal({ DefaultVal }), bSign(FALSE)
		{
			BitMask.push_back(BIT(BitShift));
		}

		//! 創建<b>CBitDetail</b>，並做初始化，針對 1 Bit。
		CBitDetail(CString desc, CString detailInfo, uint8_t RegAddr, uint8_t BitMask, int8_t BitShift, enum BitRW_ BitRW = BOTH_RW, uint8_t DefaultVal = 0x00, BOOL sign = FALSE)
			: csDesc(desc), csDetailInfo(detailInfo), RegAddr(RegAddr), BitMask({ BitMask }), BitShift({ BitShift }), BitRW(BitRW), BitRange({ make_pair(0, 1) }), DefaultVal({ DefaultVal }), bSign(sign)	{ }

		//! 創建<b>CBitDetail</b>，並做初始化。
		CBitDetail(CString desc, CString detailInfo, uint8_t RegAddr, vector<uint8_t> BitMask, vector<int8_t> BitShift, enum BitRW_ BitRW, vector<pair<uint8_t, uint8_t> >range, vector<uint8_t> DefaultVal, BOOL sign = FALSE)
			: csDesc(desc), csDetailInfo(detailInfo), RegAddr(RegAddr), BitMask(BitMask), BitShift(BitShift), BitRW(BitRW), BitRange(range), DefaultVal(DefaultVal), bSign(sign) { }

		//! 創建<b>CBitDetail</b>，並做初始化。
		CBitDetail(CString desc, CString detailInfo, uint8_t RegAddr, uint8_t BitMask, int8_t BitShift, enum BitRW_ BitRW, pair<uint8_t, uint8_t>range, uint8_t DefaultVal = 0x00, BOOL sign = FALSE)
			: csDesc(desc), csDetailInfo(detailInfo), RegAddr(RegAddr), BitMask({ BitMask }), BitShift({ BitShift }), BitRW(BitRW), BitRange({ range }), DefaultVal({ DefaultVal }), bSign(sign) { }
	};	

	/**
	* @class CRegInfo
	* @brief Register Information.
	*/
	class CRegInfo {
	public:
		uint8_t RegBits;				//!< Reg所佔的Bit數。
		CString RegDesc;				//!< 填入Datasheet內的簡短敘述。
		vector<uint8_t> RegInit;		//!< 填入Datasheet內的預設值。
		vector<uint8_t> RegCurVal;		//!< 儲存Reg當下的值。
		map<uint8_t, CString> BitName;	//!< 填入Datasheet內的Reg對應的Bit名稱。
		BOOL bEngMode;					//!< 是否為工程模式，工程模式在Release版不顯示。
		double RegScale;				//!< 資料組合後，跟此值做相乘的動作。

		//! 創建<b>CRegInfo</b>並初始化。
		CRegInfo(vector<uint8_t> initVal = {0}, CString regDesc = _T(""), uint8_t bits = 1, double scale = 1.0, BOOL bEng = TRUE)
			: RegBits(bits), RegInit(initVal), RegDesc(regDesc), RegCurVal(initVal), RegScale(scale), bEngMode(bEng) {};
	};	

	/**
	* @class CReadTable
	* @brief 列出在程式中需要重覆讀取的Register及數量。
	*/
	class CReadTable {
	public:
		uint8_t RegAddr;			//!< 要讀取的第一個Register Address。
		uint8_t ReadNum;			//!< 要讀取的數量。
		enum LogFormat_ LogFormat;	//!< Log時要使用的格式。
		BOOL	bSignalRead;		//!< 是否要使用單筆讀取的方式。

		//! 創建<b>CReadTable</b>並初始化。
		CReadTable(uint8_t addr = 0x00, uint8_t num = 1,enum LogFormat_ log = LogHex, BOOL bsignal = false)
			: RegAddr(addr), ReadNum(num), LogFormat(log), bSignalRead(bsignal) {
		}

		//! 用於排序使用。
		bool operator < (const CReadTable &a) const {
			return RegAddr < a.RegAddr;
		}
	};

	/**
	 * @class CRegisterTable
	 * @brief 儲存Sensor相關資料。
	 */
	class CRegisterTable {
	private:
		uint8_t addr;
	public:
		uint8_t DeviceID;						/*< Device Slave Address */
		map<uint8_t, CRegInfo> RegInfo;			/*< Address, CRegInfo */		
		map<CString, CBitDetail> BitDetail;		/*< BitName, CBitDetail */
		set<CReadTable> ReadTable;				/*< 會重覆讀取的Register列表。 */
		uint8_t OnReadAddrAddVal;				/*< 在Read時Address加的數值。 */

		CRegisterTable() : 
			addr(0x00),
			DeviceID(0x00),
			OnReadAddrAddVal(0x00) {}

		void SetRegAddr(uint8_t addr) { this->addr = addr; }

		//Set RegInfo
		void SetRegInfo(vector<uint8_t> InitVal = { 0 }, CString csDesc = _T(""), uint8_t bits = 1, double scale = 1.0, BOOL bEng = TRUE)
		{
			RegInfo[addr] = CRegInfo(InitVal, csDesc, bits, scale, bEng);
		}		

		//One Bit
		void SetBitDetail(CString BitName, uint8_t bit = 1, CString csDesc = _T("")
			, uint8_t defaultVal = 0x00, enum BitRW_ BitRW = BOTH_RW)
		{
			BitDetail[BitName] = CBitDetail(addr, bit, csDesc, defaultVal, BitRW);
		}

		void SetBitDetailOne(CString BitName, uint8_t bit = 1, CString csDesc = _T(""), CString csDescDetail = _T("")
			, uint8_t defaultVal = 0x00, enum BitRW_ BitRW = BOTH_RW)
		{
			BitDetail[BitName] = CBitDetail(addr, bit, csDesc, defaultVal, BitRW, csDescDetail);
		}

		//Mutil bit
		void SetBitDetail(CString BitName, CString csDesc , uint8_t bitMask = 0xFF
			, uint8_t bitShift = 0, enum BitRW_ BitRW = BOTH_RW
			, pair<uint8_t, uint8_t> range = { 0, 255 }, uint8_t defaultVal = 0x00)
		{
			BitDetail[BitName] = CBitDetail(csDesc, _T(""), addr, bitMask, bitShift, BitRW, range, defaultVal);
		}		

		void SetBitDetail(CString BitName, CString csDesc, CString csDescDetail
			, uint8_t bitMask = 0xFF, int8_t bitShift = 0, enum BitRW_ BitRW = BOTH_RW
			, pair<uint8_t, uint8_t> range = { 0, 255 }, uint8_t defaultVal = 0x00)
		{
			BitDetail[BitName] = CBitDetail(csDesc, csDescDetail, addr, bitMask, bitShift, BitRW, range, defaultVal);
		}

		//Mutil byte
		void SetBitDetail2(CString BitName, vector<uint8_t> defaultVal = { 0x00, 0x00 }, CString csDesc = _T(""), CString csDescDetail = _T("")
			, vector<uint8_t> bitMask = { 0xFF, 0xFF }, vector<int8_t> bitShift = { 0, 8 }
			, enum BitRW_ BitRW = BOTH_RW, vector< pair<uint8_t, uint8_t> > range = { make_pair(0, 255), make_pair(0, 255) }, BOOL bSign = FALSE
			)
		{
			BitDetail[BitName] = CBitDetail(csDesc, csDescDetail, addr, bitMask, bitShift, BitRW, range, defaultVal, bSign);
		}

		void SetBitDetail2(CString BitName, CString csDesc, CString csDescDetail = _T("")
			, vector<uint8_t> bitMask = { 0xFF, 0xFF }, vector<int8_t> bitShift = { 0, 8 }
			, enum BitRW_ BitRW = ONLY_R, vector< pair<uint8_t, uint8_t> > range = { make_pair(0, 255), make_pair(0, 255) }
			, vector<uint8_t> defaultVal = { 0x00, 0x00 }, BOOL bSign = FALSE)
		{
			BitDetail[BitName] = CBitDetail(csDesc, csDescDetail, addr, bitMask, bitShift, BitRW, range, defaultVal, bSign);
		}

		uint8_t GetBitValue(CString BitName)
		{
			return RSHIFT((RegInfo.at(BitDetail.at(BitName).RegAddr).RegCurVal.at(0) 
				& BitDetail.at(BitName).BitMask.at(0)), BitDetail.at(BitName).BitShift.at(0));
		}

		int32_t GetRegValue(uint8_t RegAddr)
		{
			int32_t value = 0;
			int32_t maxValue = 0;
			CRegInfo* pRegInfo;
			CBitDetail* pBitDetail;
			CString BitName;

			pRegInfo = &RegInfo.at(RegAddr);
			BitName = RegInfo.at(RegAddr).BitName.at(0);

			pBitDetail = &BitDetail.at(BitName);

			for (int i = 0; i < pRegInfo->RegBits; i++)
			{
				value += LSHIFT((pRegInfo->RegCurVal.at(i) & pBitDetail->BitMask.at(i)), pBitDetail->BitShift.at(i));
				maxValue += LSHIFT(pBitDetail->BitRange.at(i).second, pBitDetail->BitShift.at(i));
			}

			if (value > maxValue)
				value = maxValue;

			return value;
		}
	};

	/**
	* @class CLuxCalculate
	* @brief Lux計算相關參數。
	*/
	class CLuxCalculate {
	public:
		enum LuxFunc_ LuxFunc;									//!< Lux所使用的計算公式。
		map<uint8_t, uint8_t> DataRegMapping;					//!< 連結公式所使用的資料所連結的的Register Addr。
		map<uint8_t, CString> RatioBitMapping;					//!< 列舉出影響CountRatioMapping的Bit名稱，最大數量2個。
		map<uint8_t, map<uint8_t, double> >CountRatioMapping;	//!< 根據RatioBitMapping來列舉出所有的Count Ratio。
		map<double, pair<double, double> >Count2LuxMapping;		//!< 根據Data的比例來決定Lux的比例公式。
		double constVal;
		map<uint8_t, map<uint8_t, CString> > DataRatioBitMapping;//!<
		map<uint8_t, map<pair<uint8_t, uint8_t>, double> > DataCountRatioMapping;//!<

		double Lux_Coef_a, Lux_Coef_b, Lux_Coef_c;	//!<(CH0/CH1 * a + b)(CH0 - CH1 * c)

		CLuxCalculate() :
			LuxFunc(OneCH),
			constVal(0.0) 
			{}
	};

	/**
	* @class CCCTCaculate
	* @brief CCT計算相關參數。
	*/
	class CCCTCaculate : public CLuxCalculate{
	public:
		map<double, map<uint8_t, map<uint8_t, double> > >RegressCoefMapping;	/*< 𝛂, 𝛃, 𝛄, 𝛅, ε */

		/**
		 * @brief 重載運算子"="
		 * 將<b>CLuxCalculate</b>的部份設定放入<b>CCCTCaculate<b>
		 */
		CCCTCaculate& operator= (const CLuxCalculate& luxCal)
		{
			DataRegMapping = luxCal.DataRegMapping;
			RatioBitMapping = luxCal.RatioBitMapping;
			CountRatioMapping = luxCal.CountRatioMapping;
			return *this;
		}
	};

	/**
	 * @class CDieDetail
	 * @brief 儲存Die相關資料，包含程式呈現的樣式、頁面位置、控制項資訊以及Register資料。
	 */
	class CDieDetail {
	public:
		uint16_t I2CFreqKHz;

		map<enum DlgSel_, enum StyleSel_> DlgStyle;	/*< 頁面使用的樣式對照表 */
		map<enum DlgSel_, CString> DlgName;			/*< 頁面名稱對照表 */
		map<enum DlgSel_, CCtrlInfo> CtrlInfo;		/*< 頁面與控制項的對應表 */

		CRegisterTable RegisterTable;				/*< Slave Address, Register Table, @see CRegisterTable */

		int32_t DieFunc;
		int32_t LuxValue;
		int32_t CCTValue;
		CLuxCalculate LuxCalculate;					//!< Lux計算相關參數。
		CCCTCaculate CCTCalculate;

		CDieDetail() :
			I2CFreqKHz(400),
			DieFunc(0),
			LuxValue(0),
			CCTValue(0)
			{}								//!< 創建<b>CDieDetail</b>。
	};

	/**
	* @class CModelDetail
	* @brief 儲存Model相關資料。
	*/
	class CDieInfo {
	public:
		CDieInfo() :
			ConversionTime(0),
			PowerConsumption(0),
			pDieDetail(NULL),
			pRegTable(NULL)
			{}
		CString DieName;						/*< Die 名稱 */
		map<uint16_t, CDieDetail> DieDetail;	/*< Die 版本 , @ref CDieDetail */

		virtual void Init(uint16_t version) { ; }
		virtual uint32_t GetConversionTime(uint16_t version, CRegisterTable* pRegTable) { return 0; }
		virtual double GetPowerConsumption(uint16_t version, CRegisterTable* pRegTable) { return 0.0; }
		virtual void AutoDac(uint16_t version, CRegisterTable* pRegTable) { ; }
		virtual uint8_t GetIntFlag(uint16_t version, CRegisterTable* pRegTable) { return 0; }
		virtual bool SLSuppression(CRegisterTable* pRegTable, uint8_t* SunLight_Status) { return false; }

	protected:
		double ConversionTime;
		double PowerConsumption;

		CDieDetail* pDieDetail;
		CRegisterTable* pRegTable;
		map<enum DlgSel_, CCtrlInfo*> pCtrlInfo;

		void MappingBitName2Reg(BOOL bClearBitName = false)
		{
			uint8_t i = 0;
			CRegInfo* pRegInfo;

			if (bClearBitName)
			{
				map<uint8_t, CRegInfo>::iterator iter_reg;
				iter_reg = pRegTable->RegInfo.begin();
				while (iter_reg != pRegTable->RegInfo.end())
				{
					iter_reg->second.BitName.clear();
					++iter_reg;
				}
			}
			
			map<CString, CBitDetail>::iterator iter;
			iter = pRegTable->BitDetail.begin();
			while (iter != pRegTable->BitDetail.end())
			{
				pRegInfo = &pRegTable->RegInfo.at(iter->second.RegAddr);

				i = (uint8_t)pRegInfo->BitName.size();
				pRegInfo->BitName[i] = iter->first;

				++iter;
			}
		}
	};

	class CSensorInfo {
	public:
		CSensorInfo():
			ModelName(_T("")),
			ModelDefaultAddress(0x00),
			DieVersion(0),
			pDieInfo(NULL),
			pRegTable(NULL),
			pBitDetail(NULL),
			pReadTable(NULL),
			pDieDetail(NULL),
			pCtrlDetail(NULL),
			pLuxCalculate(NULL),
			pCCTCalculate(NULL),
			csTemp(_T("")),
			BarNumCount(0),
			DlgCheck({ TAB_1, make_pair(0,0) })
			{}

		CString ModelName;							/*< Model Name */
		set<uint16_t> ModelVersion;					/*< Model Datasheet version(10000 = 1.00.00) */
		set<uint8_t> ModelSelAddress;
		uint8_t ModelDefaultAddress;
		uint16_t DieVersion;
		CDieInfo *pDieInfo;

		virtual void Init(uint16_t version) { ; }

		void Clear()
		{
			DlgCheckSet.clear();
			if (pDieInfo->DieDetail.count(DieVersion))
			{
				pDieInfo->DieDetail.at(DieVersion).CtrlInfo.clear();
				pDieInfo->DieDetail.at(DieVersion).CtrlInfo.clear();
				pDieInfo->DieDetail.at(DieVersion).DlgName.clear();
				pDieInfo->DieDetail.at(DieVersion).DlgStyle.clear();
				pDieInfo->DieDetail.at(DieVersion).RegisterTable.RegInfo.clear();
				pDieInfo->DieDetail.at(DieVersion).RegisterTable.BitDetail.clear();
				pDieInfo->DieDetail.at(DieVersion).RegisterTable.ReadTable.clear();
				pDieInfo->DieDetail.at(DieVersion).RegisterTable.DeviceID = 0x00;
			}
			DieVersion = 0;
		}

	protected:
		CRegisterTable* pRegTable;					/*< Point of <b>CRegisterTable</b> */
		CBitDetail* pBitDetail;						/*< Point of <b>CBitDetail</b> */
		set<CReadTable>* pReadTable;				/*< Point of <b>CReadTable</b> set */
		CDieDetail* pDieDetail;						/*< Point of <b>CDieDetail</b> */
		map<enum DlgSel_, CCtrlInfo*> pCtrlInfo;	/*< Point of <b>CCtrlInfo</b> */
		CCtrlDetail* pCtrlDetail;					/*< Point of <b>CCtrlDetail</b> */
		CLuxCalculate* pLuxCalculate;				/*< Point of <b>CLuxCalculate</b> */
		CCCTCaculate* pCCTCalculate;				/*< Point of <b>CCCTCaculate</b> */

		CString csTemp;								/*< CString template */
		int BarNumCount;

		/**
		* @struct CheckDlg_
		* @brief 用於檢查控制項是否重疊使用。
		*/
		struct CheckDlg_ {
			enum DlgSel_ DlgSel;	/* 指定頁面 */
			pairINT CtrlXY;			/* 在指定頁面上的座標 */


			//! 初始化<b>CheckDlg_</b>
			void Init(enum DlgSel_ dlg, pairINT location) {
				DlgSel = dlg;
				CtrlXY = location;
			}

			//! 用於排序使用。
			bool operator < (const CheckDlg_ &a) const {
				if (DlgSel < a.DlgSel)
					return true;
				else if (DlgSel == a.DlgSel)
				{
					if (CtrlXY.first < a.CtrlXY.first)
						return true;
					else if (CtrlXY.first == a.CtrlXY.first)
						return CtrlXY.second < a.CtrlXY.second;
				}

				return false;
			}
		}DlgCheck;
		set<CheckDlg_>	DlgCheckSet;	//!< 使用在檢查控制項有沒有重疊。

		void Init()
		{
			DlgCheck.Init(TAB_1, make_pair(0, 0));
			ASSERT(DlgCheckSet.insert(DlgCheck).second);
			pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
			{
				pCtrlDetail->CtrlName = make_pair(_T("Sensor Name"), ModelName);
				pCtrlDetail->CtrlType = TEXT_GROUP;
				pCtrlDetail->CtrlFunc = CTRLFUNC_SHOWTEXT;
			}

			DlgCheck.Init(TAB_1, make_pair(2, 0));
			ASSERT(DlgCheckSet.insert(DlgCheck).second);
			pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
			{
				pCtrlDetail->CtrlName = make_pair(_T("Data Sheet Version"), _T(""));
				pCtrlDetail->CtrlType = TEXT_GROUP;
				pCtrlDetail->CtrlFunc = CTRLFUNC_SHOW_DATASHEET;
			}

			DlgCheck.Init(TAB_1, make_pair(4, 0));
			ASSERT(DlgCheckSet.insert(DlgCheck).second);
			pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
			{
				pCtrlDetail->CtrlName = make_pair(_T("Control Board Version"), _T(""));
				pCtrlDetail->CtrlType = TEXT_GROUP;
				pCtrlDetail->CtrlFunc = CTRLFUNC_SHOW_BRIDGE_VERSION;
			}

#ifdef _DEBUG
			DlgCheck.Init(TAB_1, make_pair(6, 0));
			ASSERT(DlgCheckSet.insert(DlgCheck).second);
			pCtrlDetail = &pCtrlInfo[DlgCheck.DlgSel]->CtrlDetail[DlgCheck.CtrlXY];
			{
				pCtrlDetail->CtrlName = make_pair(_T("Die Version"), _T(""));
				pCtrlDetail->CtrlType = TEXT_GROUP;
				pCtrlDetail->CtrlFunc = CTRLFUNC_SHOW_DIEVERSION;
			}
#endif
		}
	};
};

using namespace SensorInfo;

template <typename T>
inline void CustomMessage(T &obj, UINT message, WPARAM wParam, LPARAM lParam, BOOL bSend = false)
{
	if (obj.size() > 0) {
		auto iter = obj.begin();
		while (iter != obj.end()) {
			if (iter->second.GetSafeHwnd() != NULL)
			{
				if (bSend)
					iter->second.SendMessageW(message, wParam, lParam);
				else
					iter->second.PostMessageW(message, wParam, lParam);
			}
			iter++;
		}
	}
}

template <typename T>
inline void CustomDestroy(T &obj) {
	if (obj.size() > 0) {
		auto iter = obj.begin();
		while (iter != obj.end()) {
			if (iter->second.GetSafeHwnd() != NULL)
				iter->second.DestroyWindow();
			iter++;
		}
		obj.clear();
	}
}

template <typename T>
inline void CustomShowWindows(T &obj, int cCmdShow) {
	if (obj.size() > 0)
	{
		auto iter = obj.begin();
		while (iter != obj.end())
		{
			if (iter->second.GetSafeHwnd() != NULL)
				iter->second.ShowWindow(cCmdShow);
			iter++;
		}
	}
}