// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once

#ifndef STRICT
#define STRICT
#endif

// 如果您必须使用下列所指定的平台之前的平台，则修改下面的定义。
// 有关不同平台的相应值的最新信息，请参考 MSDN。
#ifndef WINVER				// 允许使用特定于 Windows 95 和 Windows NT 4 或更高版本的功能。
//#define WINVER 0x0400		// 将此更改为针对于 Windows 98 和 Windows 2000 或更高版本的合适的值。
#define WINVER 0x0501		// 将此更改为针对于 Windows 98 和 Windows 2000 或更高版本的合适的值。
#endif

#ifndef _WIN32_WINNT		// 允许使用特定于 Windows NT 4 或更高版本的功能。
//#define _WIN32_WINNT 0x0400	// 将此更改为针对于 Windows 2000 或更高版本的合适的值。
#define _WIN32_WINNT 0x0501	// 将此更改为针对于 Windows 2000 或更高版本的合适的值。
#endif						

#ifndef _WIN32_WINDOWS		// 允许使用特定于 Windows 98 或更高版本的功能。
//#define _WIN32_WINDOWS 0x0410 // 将此更改为针对于 Windows Me 或更高版本的合适的值。
#define _WIN32_WINDOWS 0x0501 // 将此更改为针对于 Windows Me 或更高版本的合适的值。
#endif

#ifndef _WIN32_IE			// 允许使用特定于 IE 4.0 或更高版本的功能。
//#define _WIN32_IE 0x0400	// 将此更改为针对于 IE 5.0 或更高版本的合适的值。
#define _WIN32_IE 0x0500	// 将此更改为针对于 IE 5.0 或更高版本的合适的值。
#endif

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// 某些 CString 构造函数将为显式的

// 关闭 ATL 对某些常被安全忽略的常见警告消息的隐藏
#define _ATL_ALL_WARNINGS

#pragma warning (disable:4996)

#include <afxwin.h>
#include <afxdisp.h>
#include <afxdlgs.h>
#include <afxext.h>
#include <afxpriv.h>
#include <afxinet.h>

#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <io.h>

using namespace ATL;

#include <list>
#include <vector>
#include <map>
using namespace std;


#include <gdiplus.h>
using namespace Gdiplus;

#include <hmgskincontrol.h>
#include "publicdef.h"
#include "resgdiobj.h"

#include "..\hmgcrtlib.h"
#include "spacedata.h"

#ifdef _DEBUG
#import "..\..\binDebug\UserInfo.dll" named_guids no_namespace
#else
#import "..\..\binRelease\UserInfo.dll" named_guids no_namespace
#endif

//#import "..\WebConfig\Debug\WebConfig.tlb" named_guids no_namespace
#import "..\WebConfig\Debug\WebConfig.tlb" named_guids no_namespace

#ifdef _DEBUG
#import "..\..\binDebug\MyArticles.dll" named_guids no_namespace
#else
#import "..\..\binRelease\MyArticles.dll" named_guids no_namespace
#endif

#include <WebBusiness.h>

extern IUserInfoX *   g_pUserInfo;
extern IWebConfigXPtr g_pWebConfig;
extern IMyArticlesX * g_pMyArticles;
extern CSpaceData     g_spaceData;


void ShowMessage(LPCSTR lpszMsg,UINT nType=MB_OK);
INT CALLBACK EnumFontNameProc(LOGFONT *plf, TEXTMETRIC* /*ptm*/, INT /*nFontType*/, LPARAM lParam);

#define WM_INITWRITEBLOGDLG  WM_USER+0x201
#define WM_CLOSEWRITEBLOGDLG WM_USER+0x202