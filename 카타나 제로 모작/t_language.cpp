#include "stdafx.h"
#include "t_language.h"

t_language::t_language()
{
}

t_language::~t_language()
{
}

HRESULT t_language::init()
{
    IMAGEMANAGER->addImage("language", "image/title/language.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));


    return S_OK;
}

void t_language::release()
{
}

void t_language::update()
{
    if (KEYMANAGER->isOnceKeyDown(VK_UP))SCENEMANAGER->changeScene("option");
    if (KEYMANAGER->isOnceKeyDown(VK_DOWN))SCENEMANAGER->changeScene("end");
}

void t_language::render()
{
    IMAGEMANAGER->findImage("language")->render(getMemDC());
}
