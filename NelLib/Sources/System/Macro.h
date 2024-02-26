#pragma once

// ====== インクルード部 ======
#include <system_error>

#ifdef _DEBUG
#define WARNING(flag,msg1,msg2)\
{if(flag){\
	char buf[512];\
	wsprintfA(buf , "%s\n%s\n\n%s : %d",msg1,msg2, __FILE__,__LINE__);\
	MessageBoxA(NULL,buf,"WARNING",MB_OK | MB_ICONERROR);\
	exit(1);\
	}\
}
#define WARNINGHR(hr,msg1)\
{if(FAILED(hr)){\
	char buf[512];\
	const char* error = std::system_category().message(hr).c_str();\
	wsprintfA(buf , "%s\n%s\n\n%s : %d",msg1,error, __FILE__,__LINE__);\
	MessageBoxA(NULL,buf,"WARNING",MB_OK | MB_ICONERROR);\
	exit(1);\
	}\
}

// メモリリーク検出
#define NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)	// メモリリーク検出用のNEW

#else
#define NEW new
#define WARNING(flag,msg1,msg2){}
#define WARNINGHR(hr,msg1){}
#endif // _DEBUG

#define SAFE_RELEASE(p) {if(p){(p)->Release();(p)=NULL;}}
#define SAFE_DELETE(p) {if(p){delete(p);(p)=NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p){delete[](p);(p)=NULL;}}
#define SAFE_FREE(p) {if(p){free(p);(p)=NULL;}}
#define SAFE_CLOSE(h) {if(h){CloseHandle(h);(h)=NULL;}}

// ラジアン変換
#define DEG2RAD(deg) ((deg) * (3.1415926f / 180.0f))
#define RAD2DEG(rad) ((rad) * (180.0f / 3.1415926f))