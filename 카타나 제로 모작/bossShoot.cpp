#include "stdafx.h"
#include "bossShoot.h"
#include "bossOutPattern.h"
#include "enemyManager.h"
#include "playerManager.h"

bossStateManager* bossShoot::inputHandle(enemyManager* boss)
{
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();
	if (_timer > 40)
	{
		_timer = 0;
		return new bossOutPattern;
	}
	//키입력
	return nullptr;
}

void bossShoot::update(enemyManager* boss)
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

void bossShoot::enter(enemyManager* boss)
{
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();

	enemy.img = IMAGEMANAGER->findImage("bossShoot");
	enemy.state = EBOSSSHOOT;
	enemy.bulletCount = 1;

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

void bossShoot::exit(enemyManager* boss)
{
}
