#include "stdafx.h"
#include "playerManager.h"
#include "fall.h"
#include "jump.h"
#include "idle.h"
#include "grab.h"
#include "attack.h"
#include "collsion.h"

stateManager * fall::inputHandle(playerManager * player)
{
	//땅이 아니면 떨어져라  땅이니까 아이들
	if (_isGround)
	{
		player->getPlayer().noCol = false;
		return new idle;
	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		player->getPlayer().dir = RIGHT;
		player->getPlayer().img->setFrameY(0);
		player->getPlayer().x += 8.0f;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		player->getPlayer().dir = LEFT;
		player->getPlayer().img->setFrameY(1);
		player->getPlayer().x -= 8.0f;
	}
	if (player->getPlayer().isGrab)
	{
		return new grab;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !player->getPlayer().atkCount)
	{
		return new attack;
	}
	if (KEYMANAGER->isOnceKeyUp('S'))
	{
		player->getPlayer().chk = false;
	}

	return nullptr;
}

void fall::update(playerManager * player)
{
	if (player->_collision->playerCollision())
	{
		//여기 안들어오는데요?
		_isGround = true;
	}

	player->getPlayer().jumpPower -= player->getPlayer().gravity;
	player->getPlayer().y -= player->getPlayer().jumpPower;
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


void fall::enter(playerManager * player)
{
	player->getPlayer().img = IMAGEMANAGER->findImage("fall");
	player->getPlayer().state = FALL;
	player->getPlayer().jumpPower = 0;
	player->getPlayer().gravity = 1.2f;
	_isGround = false; 
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

void fall::exit(playerManager * player)
{
}