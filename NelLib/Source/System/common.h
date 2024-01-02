#pragma once
// ====== インクルード部 ======
// #include "targetver.h"
#define WIN32_LEAN_AND_MEAN	// Windows ヘッダーから使用されていない部分を除外する
// Windows ヘッダー ファイル
#include <Windows.h>

// C ランタイム ヘッダー ファイル
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// C++ STL
#include <string>
#include <vector>
#include <list>

#ifdef _DEBUG
#define WARNING(flag,msg1,msg2)\
{if(flag){\
	char buf[512];\
	wsprintfA(buf , "%s\n%s\n\n%s : %d",msg1,msg2, __FILE__,__LINE__);\
	MessageBoxA(NULL,buf,"WARNING",MB_OK | MB_ICONERROR);\
	exit(1);\
	}\
}
#else
#define WARNING(flag,msg1,msg2){}
#endif // _DEBUG

#define SAFE_RELEASE(p) {if(p){(p)->Release();(p)=NULL;}}
#define SAFE_DELETE(p) {if(p){delete(p);(p)=NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p){delete[](p);(p)=NULL;}}
#define SAFE_FREE(p) {if(p){free(p);(p)=NULL;}}
