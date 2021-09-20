#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	SetTimer(_hWnd, 1, 10, NULL);
	KEYMANAGER->init();
	IMAGEMANAGER->init();

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		EFFECTMANAGER->init();
		SCENEMANAGER->init();
		CAMERAMANAGER->init();
		TXTDATA->init();

	}

	return S_OK;
}

void gameNode::release()
{
	if (_managerInit)
	{
		KillTimer(_hWnd, 1);
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();

		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();

		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();

		TXTDATA->release();
		TXTDATA->releaseSingleton();
	}


	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update()
{

}

void gameNode::render()
{
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC         hdc; //얘 찐 중요합니...


	switch (iMessage)
	{

		//마우스 움직이면 여기서 메세지 발생
	case WM_MOUSEMOVE:
		_ptMouse.x = static_cast<float>(LOWORD(lParam));
		_ptMouse.y = static_cast<float>(HIWORD(lParam));

		break;
		//마우스 왼쪽 클릭(눌려지고 있을때 여기)

	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;


		//윈도우 창 부쉬는(?) 
	case WM_DESTROY:
		//윈도우 종료함수
		PostQuitMessage(0);
		return 0;
	}


	return (DefWindowProc(hWnd, iMessage, wParam, lParam));

}
