#include "stdafx.h"
#include "playerManager.h"
#include "idle.h"
#include "run.h"
#include "jump.h"
#include "roll.h"
#include "attack.h"

stateManager * roll::inputHandle(playerManager * player)
{
	if (!player->getPlayer().isRoll)
	{
		return new idle;
	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		player->getPlayer().isJump = true;
		return new jump;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !player->getPlayer().atkCount)
	{
		return new attack;
	}
	return nullptr;
}

void roll::update(playerManager * player)
{
	switch (player->getPlayer().dir)
	{
	case LEFT:
		player->getPlayer().x -= 20.0f;
		if (_count++ % 2 == 0)
		{
			player->getPlayer().img->setFrameX(player->getPlayer().img->getFrameX() - 1);
			if (player->getPlayer().img->getFrameX() <= 0)
			{
				player->getPlayer().isRoll = false;
			}
		}
		break;
	case RIGHT:
		player->getPlayer().x += 20.0f;
		if (_count++ % 2 == 0)
		{
			player->getPlayer().img->setFrameX(player->getPlayer().img->getFrameX() + 1);
			if (player->getPlayer().img->getFrameX() >= player->getPlayer().img->getMaxFrameX())
			{
				player->getPlayer().isRoll = false;
			}
		}
		break;
	}
}


void roll::enter(playerManager * player)
{
	player->getPlayer().img = IMAGEMANAGER->findImage("roll");
	player->getPlayer().state = ROLL;

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

void roll::exit(playerManager * player)
{
}
