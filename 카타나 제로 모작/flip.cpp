#include "stdafx.h"
#include "playerManager.h"
#include "fall.h"
#include "flip.h"
#include "attack.h"
#include "grab.h"

stateManager * flip::inputHandle(playerManager * player)
{
	if (!player->getPlayer().isFlip)
	{
		return new fall;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !player->getPlayer().atkCount)
	{
		return new attack;
	}
	/*if (!player->getPlayer().isGrabL && player->getPlayer().isGrabR)
	{
		return new grab;
	}
	if (!player->getPlayer().isGrabR && player->getPlayer().isGrabL)
	{
		return new grab;
	}*/
	return nullptr;
}

void flip::update(playerManager * player)
{
	player->getPlayer().y -= player->getPlayer().jumpPower;
	player->getPlayer().jumpPower -= player->getPlayer().gravity;
	if (player->getPlayer().jumpPower <= 0)player->getPlayer().isFlip = false;
	switch (player->getPlayer().dir)
	{
	case LEFT:
		player->getPlayer().x += 10.0f;
		if (_count++ % 3 == 0)
		{
			player->getPlayer().img->setFrameX(player->getPlayer().img->getFrameX() - 1);
			if (player->getPlayer().img->getFrameX() <= 0)
			{
				player->getPlayer().isFlip = false;
			}
		}
		break;
	case RIGHT:
		player->getPlayer().x -= 10.0f;
		if (_count++ % 3 == 0)
		{
			player->getPlayer().img->setFrameX(player->getPlayer().img->getFrameX() + 1);
			if (player->getPlayer().img->getFrameX() >= player->getPlayer().img->getMaxFrameX())
			{
				player->getPlayer().isFlip = false;
			}
		}
		break;
	}
}

void flip::enter(playerManager * player)
{

	player->getPlayer().img = IMAGEMANAGER->findImage("flip");
	player->getPlayer().state = FLIP;
	player->getPlayer().jumpPower = 15.0f;
	player->getPlayer().gravity = 0.7f;

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

void flip::exit(playerManager * player)
{
}
