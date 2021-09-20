#include "stdafx.h"
#include "attack.h"
#include "playerManager.h"
#include "fall.h"

stateManager* attack::inputHandle(playerManager* player)
{
	if (!player->getPlayer().isAtk)
	{
		player->getPlayer().acc = 1.7f;
		
		return new fall;
	}
	if (player->getPlayer().isSlow)
	{
		player->getPlayer().noCol = true;
	}
    return nullptr;
}

void attack::update(playerManager* player)
{
	player->getPlayer().y -= player->getPlayer().jumpPower-1;
	player->getPlayer().jumpPower -= player->getPlayer().gravity;

	player->getPlayer().acc += 0.7f;
	if (player->getPlayer().speed > 6.0f)player->getPlayer().speed = 15.0f;

	player->getPlayer().x += cosf(player->getPlayer().angle)*player->getPlayer().acc;
	player->getPlayer().y += -sinf(player->getPlayer().angle)*player->getPlayer().acc;

	if (player->getPlayer().dir == LEFT)
	{
		player->getPlayer().eRC = RectMake(player->getPlayer().rc.left - 90,
			player->getPlayer().rc.top,
			player->getPlayer().eImg->getFrameWidth(),
			player->getPlayer().img->getFrameHeight());
	}
	else
	{
		player->getPlayer().eRC = RectMake(player->getPlayer().rc.left,
			player->getPlayer().rc.top,
			player->getPlayer().eImg->getFrameWidth(),
			player->getPlayer().img->getFrameHeight());
	}

	switch (player->getPlayer().dir)
	{
	case LEFT:
		if (_count++ % 3 == 0)
		{
			player->getPlayer().img->setFrameX(player->getPlayer().img->getFrameX() - 1);
			if (player->getPlayer().img->getFrameX() < player->getPlayer().img->getMaxFrameX())
			{
				player->getPlayer().eImg->setFrameX(player->getPlayer().eImg->getFrameX() - 1);
			}
			if (player->getPlayer().img->getFrameX() <= 0)
			{
				player->getPlayer().eRC = RectMakeCenter(0, 0, 0, 0);
				player->getPlayer().isAtk = false;
			}
		}
		break;
	case RIGHT:
		if (_count++ % 3 == 0)
		{
			player->getPlayer().img->setFrameX(player->getPlayer().img->getFrameX() + 1);
			if (player->getPlayer().img->getFrameX() > 0)
			{
				player->getPlayer().eImg->setFrameX(player->getPlayer().eImg->getFrameX() + 1);
			}
			if (player->getPlayer().img->getFrameX() >= player->getPlayer().img->getMaxFrameX())
			{
				player->getPlayer().eRC = RectMakeCenter(0, 0, 0, 0);
				player->getPlayer().isAtk = false;
			}
		}
		break;
	}
}

void attack::enter(playerManager* player)
{
	player->getPlayer().img = IMAGEMANAGER->findImage("attack");
	player->getPlayer().state = ATTACK;
	player->getPlayer().isAtk = true;
	player->getPlayer().atkCount = true;
	player->getPlayer().eImg = IMAGEMANAGER->findImage("attack_effect");

	

	float mX = _ptMouse.x + CAMERAMANAGER->getCameraX();
	float mY = _ptMouse.y + CAMERAMANAGER->getCameraY();

	//상단 좌
	if (player->getPlayer().x > mX && player->getPlayer().y > mY)player->getPlayer().dir = LEFT;
	//상단 우
	if (player->getPlayer().x < mX && player->getPlayer().y > mY)player->getPlayer().dir = RIGHT;
	//하단 좌
	if (player->getPlayer().x > mX && player->getPlayer().y < mY)player->getPlayer().dir = LEFT;
	//하단 우
	if (player->getPlayer().x < mX && player->getPlayer().y < mY)player->getPlayer().dir = RIGHT;

	cout << endl;
	cout << mX << "X<마우스 위치>Y" << mY << endl;
	cout << endl;
	player->getPlayer().angle = getAngle(player->getPlayer().x, player->getPlayer().y,
		mX, mY);
	player->getPlayer().jumpPower = 3.0f;
	player->getPlayer().gravity = 0.12f;

	switch (player->getPlayer().dir)
	{
	case LEFT:
		player->getPlayer().img->setFrameX(player->getPlayer().img->getMaxFrameX());
		player->getPlayer().img->setFrameY(1);
		player->getPlayer().eImg->setFrameX(player->getPlayer().eImg->getMaxFrameX());
		player->getPlayer().eImg->setFrameY(1);
		break;
	case RIGHT:
		player->getPlayer().img->setFrameX(0);
		player->getPlayer().img->setFrameY(0);
		player->getPlayer().eImg->setFrameX(0);
		player->getPlayer().eImg->setFrameY(0);
		break;
	}
}

void attack::exit(playerManager* player)
{
}
