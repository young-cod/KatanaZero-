#include "stdafx.h"
#include "title.h"

title::title()
{
}

title::~title()
{
}

HRESULT title::init()
{
	IMAGEMANAGER->addImage("new", "image/title/new.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	

	return S_OK;
}

void title::release()
{
}

void title::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))SCENEMANAGER->changeScene("re");
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))SCENEMANAGER->changeScene("bossStage");
}

void title::render()
{
	IMAGEMANAGER->findImage("new")->render(getMemDC());
}
