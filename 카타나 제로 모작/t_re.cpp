#include "stdafx.h"
#include "t_re.h"

t_re::t_re()
{
}

t_re::~t_re()
{
}

HRESULT t_re::init()
{
	IMAGEMANAGER->addImage("re", "image/title/re.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	return S_OK;
}

void t_re::release()
{
}

void t_re::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP))SCENEMANAGER->changeScene("new");
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))SCENEMANAGER->changeScene("option");
}

void t_re::render()
{
	IMAGEMANAGER->findImage("re")->render(getMemDC());
}
