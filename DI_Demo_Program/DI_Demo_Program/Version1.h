#pragma once
#define TOSTRING2(arg) #arg
#define TOSTRING(arg) TOSTRING2(arg)

//#define RELEASE_VER 1 // 0: beta version; 1: release version
//#define RELEASE_DATE "May 09 2013" // Mmm dd yyyy; only used for RELEASE_VER=1

#define VER_MAIN  1 // version number (binary)
#define VER_MAIN2 8
#define VER_SUB   0
#define VER_SUB2  1

#ifdef _ICON_CUSTOM_1
#define VER_COMPANYNAME_STR			"JingWei Electronic Technology CO., LTD"
#define VER_FILEDESCRIPTION_STR		"For demo sensor product."

// version number (string)
#define VER_FILEVERSION_STR			TOSTRING(VER_MAIN) "." TOSTRING(VER_MAIN2) "." TOSTRING(VER_SUB) "." TOSTRING(VER_SUB2)

#define VER_INTERNALNAME_STR		"JW_Demo_Program.exe"
#define VER_LEGALCOPYRIGHT_STR		"Copyright (C) 2019"
#define VER_ORIGINALFILENAME_STR	"JW_Demo_Program.exe"
#define VER_PRODUCTNAME_STR			"JW Demo Program"
#define VER_PRODUCTVERSION_STR		TOSTRING(VER_MAIN) "." TOSTRING(VER_MAIN2) "." TOSTRING(VER_SUB) "." TOSTRING(VER_SUB2)
#else
#define VER_COMPANYNAME_STR			"Dyna-Image Corporation"
#define VER_FILEDESCRIPTION_STR		"For demo dyna-image sensor product."

// version number (string)
#define VER_FILEVERSION_STR			 TOSTRING(VER_MAIN) "." TOSTRING(VER_MAIN2) "." TOSTRING(VER_SUB) "." TOSTRING(VER_SUB2)

#define VER_INTERNALNAME_STR		"DI_Demo_Program.exe"
#define VER_LEGALCOPYRIGHT_STR		"Copyright (C) 2019"
#define VER_ORIGINALFILENAME_STR	"DI_Demo_Program.exe"
#define VER_PRODUCTNAME_STR			"DI Demo Program"
#define VER_PRODUCTVERSION_STR		TOSTRING(VER_MAIN) "." TOSTRING(VER_MAIN2)"." TOSTRING(VER_SUB) "." TOSTRING(VER_SUB2)
#endif
