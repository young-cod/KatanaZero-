#include "stdafx.h"
#include "bossDash.h"
#include "bossEndDash.h"
#include "enemyManager.h"

bossStateManager* bossDash::inputHandle(enemyManager* boss)
{
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();
	if (_timer > 20)
	{
		_timer = 0;
		return new bossEndDash;
	}
	//키입력
	return nullptr;
}

void bossDash::update(enemyManager* boss)
{
	_timer++;
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();
	//프레임

	switch (enemy.dir)
	{
	case ELEFT:
		enemy.x -= 40.0f;
		if (_count++ % 7 == 0)
		{
			enemy.img->setFrameX(enemy.img->getFrameX() - 1);
			if (enemy.img->getFrameX() <= 0)
			{
				enemy.img->setFrameX(enemy.img->getMaxFrameX());
			}
		}
		break;
	case ERIGHT:
		enemy.x += 40.0f;
		if (_count++ % 7 == 0)
		{
			enemy.img->setFrameX(enemy.img->getFrameX() + 1);
			if (enemy.img->getFrameX() >= enemy.img->getMaxFrameX())
			{
				enemy.img->setFrameX(0);
			}
		}
		break;
	}
}

void bossDash::enter(enemyManager* boss)
{
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();

	enemy.img = IMAGEMANAGER->findImage("bossDash");
	enemy.state = EBOSSDASH;

	switch (enemy.dir)
	{
	case ELEFT:
		enemy.img->setFrameX(enemy.img->getMaxFrameX());
		enemy.img->setFrameY(1);
		break;
	case ERIGHT:
		enemy.img->setFrameX(0);
		enemy.img->setFrameY(0);
		break;
	}
	//이미지
}

void bossDash::exit(enemyManager* boss)
{
}
