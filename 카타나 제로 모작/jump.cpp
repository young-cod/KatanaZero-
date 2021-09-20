#include "stdafx.h"
#include "playerManager.h"
#include "idle.h"
#include "jump.h"
#include "run.h"
#include "fall.h"
#include "flip.h"
#include "grab.h"
#include "attack.h"

stateManager * jump::inputHandle(playerManager * player)
{
	/*if (player->getPlayer().isGrab)
	{
		return new grab;
	}*/
	if (!player->getPlayer().isJump)
	{
		return new fall;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		player->getPlayer().x += 7.0f;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		player->getPlayer().x -= 7.0f;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !player->getPlayer().atkCount)
	{
		return new attack;
	}
	return nullptr;
}

void jump::update(playerManager * player)
{

	player->getPlayer().y -= player->getPlayer().jumpPower;
	player->getPlayer().jumpPower -= player->getPlayer().gravity;

	if (player->getPlayer().jumpPower <= 0)	player->getPlayer().isJump = false;
	
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

void jump::enter(playerManager * player)
{
	player->getPlayer().img = IMAGEMANAGER->findImage("jump");
	player->getPlayer().state = JUMP;
	player->getPlayer().jumpPower = 15.0f;
	player->getPlayer().gravity = 0.9f;

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

void jump::exit(playerManager * player)
{
}
