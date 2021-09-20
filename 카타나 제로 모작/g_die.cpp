#include "stdafx.h"
#include "g_die.h"
#include "playerManager.h"
#include "run.h"

stateManager* g_die::inputHandle(playerManager* player)
{
	/*if (KEYMANAGER->isStayKeyDown('D'))
	{
		player->getPlayer().dir = RIGHT;
		return new run;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		player->getPlayer().dir = LEFT;
		return new run;
	}*/
    return nullptr;
}

void g_die::update(playerManager* player)
{
	if (player->_collision->playerCollision())player->getPlayer().gravity = 0;
	else player->gravity();
	if (_count++ % 7 == 0)
	{
		switch (player->getPlayer().dir)
		{
		case LEFT:
			player->getPlayer().img->setFrameX(player->getPlayer().img->getFrameX() - 1);
			if (player->getPlayer().img->getFrameX() <= 0)
			{
				player->getPlayer().img->setFrameX(0);
			}

			break;
		case RIGHT:
			player->getPlayer().img->setFrameX(player->getPlayer().img->getFrameX() + 1);
			if (player->getPlayer().img->getFrameX() >= player->getPlayer().img->getMaxFrameX())
			{
				player->getPlayer().img->setFrameX(player->getPlayer().img->getMaxFrameX());
			}

			break;
		}
	}
}

void g_die::enter(playerManager* player)
{
	player->getPlayer().img = IMAGEMANAGER->findImage("g_die");
	player->getPlayer().state = G_DIE;
	player->getPlayer().isAtk = false;

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

void g_die::exit(playerManager* player)
{
}

bool g_die::pixelCollision(playerManager* player)
{
    return false;
}
