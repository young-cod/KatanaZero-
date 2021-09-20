#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "utils.h"
#include "imageManager.h"
#include "txtData.h"
#include "timeManager.h"
#include "effectManager.h"
#include "cameraManager.h"
#include "sceneManager.h"

using namespace std;
using namespace SUNFL_UTIL;

//==================================
// ## 매크로 처리 ## 21.04.23 ##
//==================================

#define WINNAME (LPTSTR)(TEXT("28기 API"))
#define WINSTARTX 50	//윈도우 창 시작좌표 (left)
#define WINSTARTY 50	//윈도우 창 시작좌표 (top)
#define WINSIZEX 1260	//윈도우 가로크기
#define WINSIZEY 720	//윈도우 세로크기
#define BACKGROUNDX 4288
#define BACKGROUNDY 3500
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define CAMERAMANAGER cameraManager::getSingleton()
#define TXTDATA txtData::getSingleton()


#define SAFE_DELETE(p) {if(p) {delete(p); (p) = nullptr;}}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p) = NULL;}}

static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", BACKGROUNDX, BACKGROUNDY);

//==================================
// ## extern ## 21.04.28 ##
//==================================
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;