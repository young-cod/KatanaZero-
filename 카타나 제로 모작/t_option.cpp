#include "stdafx.h"
#include "t_option.h"

t_option::t_option()
{
}

t_option::~t_option()
{
}

HRESULT t_option::init()
{
    IMAGEMANAGER->addImage("option", "image/title/option.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

    return S_OK;
}

void t_option::release()
{
}

void t_option::update()
{
    if (KEYMANAGER->isOnceKeyDown(VK_UP))SCENEMANAGER->changeScene("re");
    if (KEYMANAGER->isOnceKeyDown(VK_DOWN))SCENEMANAGER->changeScene("language");
}

void t_option::render()
{
    IMAGEMANAGER->findImage("option")->render(getMemDC());
}
