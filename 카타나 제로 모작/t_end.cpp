#include "stdafx.h"
#include "t_end.h"

t_end::t_end()
{
}

t_end::~t_end()
{
}

HRESULT t_end::init()
{
	IMAGEMANAGER->addImage("end", "image/title/end.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	return S_OK;
}

void t_end::release()
{
}

void t_end::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP))SCENEMANAGER->changeScene("language");
}

void t_end::render()
{
	IMAGEMANAGER->findImage("end")->render(getMemDC());
}
