#include "stdafx.h"
#include "playerManager.h"
#include "flip.h"
#include "grab.h"
#include "attack.h"

stateManager * grab::inputHandle(playerManager * player)
{
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		player->getPlayer().isFlip = true;
		player->getPlayer().isGrab = false;

		return new flip;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !player->getPlayer().atkCount)
	{
		return new attack;
	}
	return nullptr;
}

void grab::update(playerManager * player)
{
	player->getPlayer().y -= player->getPlayer().jumpPower;
	player->getPlayer().jumpPower -= player->getPlayer().gravity;
	/*switch (player->getPlayer().dir)
	{
	case LEFT:
		if (_count++ % 10 == 0)
		{
			player->getPlayer().img->setFrameX(player->getPlayer().img->getFrameX() - 1);
			if (player->getPlayer().img->getFrameX() <= 0)
			{
				player->getPlayer().img->setFrameX(player->getPlayer().img->getMaxFrameX());
			}
		}
		break;
	case RIGHT:
		if (_count++ % 10 == 0)
		{
			player->getPlayer().img->setFrameX(player->getPlayer().img->getFrameX() + 1);
			if (player->getPlayer().img->getFrameX() >= player->getPlayer().img->getMaxFrameX())
			{
				player->getPlayer().img->setFrameX(0);
			}
		}
		break;
	}*/
}

void grab::enter(playerManager * player)
{
	player->getPlayer().img = IMAGEMANAGER->findImage("grab");
	player->getPlayer().state = GRAB;
	player->getPlayer().jumpPower = 7.0f;
	player->getPlayer().gravity = 0.18f;
	player->getPlayer().atkCount = false;

	switch (player->getPlayer().dir)
	{
	case LEFT:
		player->getPlayer().img->setFrameX(0);
		player->getPlayer().img->setFrameY(1);
		break;
	case RIGHT:
		player->getPlayer().img->setFrameX(0);
		player->getPlayer().img->setFrameY(0);

		break;
	}
}

void grab::exit(playerManager * player)
{
}
