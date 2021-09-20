#include "stdafx.h"
#include "bossShoot.h"
#include "bossTakeOutGun.h"
#include "enemyManager.h"
#include "playerManager.h"

bossStateManager* bossTakeOutGun::inputHandle(enemyManager* boss)
{

	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();
	if (_timer > 40)
	{
		_timer = 0;
		return new bossShoot;
	}
	//키입력
	return nullptr;
}

void bossTakeOutGun::update(enemyManager* boss)
{
	_timer++;

	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();
	//프레임
	if (_count++ % 7 == 0)
	{
		switch (enemy.dir)
		{
		case ELEFT:
			enemy.img->setFrameX(enemy.img->getFrameX() - 1);
			if (enemy.img->getFrameX() <= 0)
			{
				enemy.img->setFrameX(enemy.img->getMaxFrameX());
			}
			break;
		case ERIGHT:
			enemy.img->setFrameX(enemy.img->getFrameX() + 1);
			if (enemy.img->getFrameX() >= enemy.img->getMaxFrameX())
			{
				enemy.img->setFrameX(0);
			}
			break;
		}
	}
}

void bossTakeOutGun::enter(enemyManager* boss)
{
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();

	enemy.img = IMAGEMANAGER->findImage("bossTakeOutGun");
	enemy.state = EBOSSTAKEOUTGUN;
	enemy.beforeState = EBOSSTAKEOUTGUN;
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

void bossTakeOutGun::exit(enemyManager* boss)
{
}
