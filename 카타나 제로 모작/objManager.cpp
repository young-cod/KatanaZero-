#include "stdafx.h"
#include "objManager.h"

objManager::objManager()
{
}

objManager::~objManager()
{
}

HRESULT objManager::init()
{
    _ground.x = 0;
    _ground.y = 520;
    _ground.rc = RectMake(_ground.x, _ground.y, 1200, 280);

    return S_OK;
}

void objManager::release()
{
}

void objManager::update()
{
}

void objManager::render()
{
}
