#include "stdafx.h"
#include "playerManager.h"
#include "idle.h"
#include "run.h"
#include "jump.h"
#include "roll.h"
#include "attack.h"
#include "fall.h"
#include "collsion.h"
#include "g_die.h"

stateManager * idle::inputHandle(playerManager * player)
{
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		player->getPlayer().dir = RIGHT;
		return new run;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		player->getPlayer().dir = LEFT;
		return new run;
	}
	//원스로
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		player->getPlayer().isJump = true;
		return new jump;
	}
	//원스로
	if (KEYMANAGER->isStayKeyDown('S') && pixelCollision(player))
	{
		player->getPlayer().chk = true;
		return new fall;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !player->getPlayer().atkCount)
	{
		return new attack;
	}
	
	return nullptr;
}

void idle::update(playerManager * player)
{
	player->gravity();
	if (player->_collision->playerCollision())
	{
		player->getPlayer().gravity = 0;
	}
	_probeB = player->getPlayer().rc.bottom + 7;

	if (_count++ % 7 == 0)
	{
		switch (player->getPlayer().dir)
		{
		case LEFT:
			player->getPlayer().img->setFrameX(player->getPlayer().img->getFrameX() - 1);
			if (player->getPlayer().img->getFrameX() <= 0)
			{
				player->getPlayer().img->setFrameX(player->getPlayer().img->getMaxFrameX());
			}

			break;
		case RIGHT:
			player->getPlayer().img->setFrameX(player->getPlayer().img->getFrameX() + 1);
			if (player->getPlayer().img->getFrameX() >= player->getPlayer().img->getMaxFrameX())
			{
				player->getPlayer().img->setFrameX(0);
			}

			break;
		}
	}
}

void idle::enter(playerManager * player)
{
	float mX = _ptMouse.x + CAMERAMANAGER->getCameraX();
	float mY = _ptMouse.y + CAMERAMANAGER->getCameraY();

	player->getPlayer().img = IMAGEMANAGER->findImage("idle");
	player->getPlayer().state = IDLE;
	player->getPlayer().jumpPower = 0;
	player->getPlayer().gravity = 0;
	player->getPlayer().chk = false;
	player->getPlayer().atkCount = false;

	switch (player->getPlayer().dir)
	{
	case LEFT:
		player->getPlayer().img->setFrameX(player->getPlayer().img->getMaxFrameX());
		player->getPlayer().img->setFrameY(1);
		break;
	case RIGHT:
		player->getPlayer().img->setFrameX(0);
		player->getPlayer().img->setFrameY(0);

		break;
	}
}

void idle::exit(playerManager * player)
{
}

bool idle::pixelCollision(playerManager* player)
{
	COLORREF color = GetPixel(IMAGEMANAGER->findImage(player->getPlayer().name)->getMemDC(),
		player->getPlayer().x, _probeB);

	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);


	//내려갈 수 있는 발판 발견
	if ((r == 0 && g == 0 && b == 0))
	{
		return true;
	}
	return false;
}
