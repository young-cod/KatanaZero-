#include "stdafx.h"
#include "playerManager.h"
#include "idle.h"
#include "run.h"
#include "jump.h"
#include "roll.h"
#include "attack.h"

stateManager * run::inputHandle(playerManager * player)
{
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		return new idle;
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		return new idle;
	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		player->getPlayer().isJump = true;
		return new jump;
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		player->getPlayer().isRoll = true;
		return new roll;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !player->getPlayer().atkCount)
	{
		return new attack;
	}
	return nullptr;
}

void run::update(playerManager * player)
{
	switch (player->getPlayer().dir)
	{
	case LEFT:
		//°¡¼Óµµ
		player->getPlayer().x -= player->getPlayer().speed;
		player->getPlayer().speed += 0.2f;
		if (player->getPlayer().speed > 2.0f)player->getPlayer().speed = 10.0f;

		if (_count++ % 5 == 0)
		{
			player->getPlayer().img->setFrameX(player->getPlayer().img->getFrameX() - 1);
			if (player->getPlayer().img->getFrameX() <= 0)
			{
				player->getPlayer().img->setFrameX(player->getPlayer().img->getMaxFrameX());
			}
		}
		break;
	case RIGHT:
		player->getPlayer().x += player->getPlayer().speed;
		player->getPlayer().speed += 0.2f;
		if (player->getPlayer().speed > 2.5f)player->getPlayer().speed = 10.0f;
		if (_count++ % 5 == 0)
		{
			player->getPlayer().img->setFrameX(player->getPlayer().img->getFrameX() + 1);
			if (player->getPlayer().img->getFrameX() >= player->getPlayer().img->getMaxFrameX())
			{
				player->getPlayer().img->setFrameX(0);
			}
		}
		break;
	}
}

void run::enter(playerManager * player)
{

	player->getPlayer().img = IMAGEMANAGER->findImage("run");
	player->getPlayer().state = RUN;
	player->getPlayer().speed = 1.0f;

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

void run::exit(playerManager * player)
{
}
