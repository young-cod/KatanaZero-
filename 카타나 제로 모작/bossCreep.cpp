#include "stdafx.h"
#include "bossCreep.h"
#include "bossNoHead.h"
#include "enemyManager.h"

bossStateManager* bossCreep::inputHandle(enemyManager* boss)
{
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();
	if (enemy.cut)return new bossNoHead;
	return nullptr;
}

void bossCreep::update(enemyManager* boss)
{
	_timer++;
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();
	//프레임

	switch (enemy.dir)
	{
	case ELEFT:
		if(enemy.x > 300 && !enemy.stop)enemy.x -= 0.5f;
		if (_count++ % 7 == 0)
		{
			enemy.img->setFrameX(enemy.img->getFrameX() - 1);
			if (enemy.img->getFrameX() <= 0)
			{
				enemy.stop = true;
				enemy.img->setFrameX(0);
			}
		}
		break;
	case ERIGHT:
		if (enemy.x < 1100 && !enemy.stop)enemy.x += 0.5f;
		if (_count++ % 7 == 0)
		{
			enemy.img->setFrameX(enemy.img->getFrameX() + 1);
			if (enemy.img->getFrameX() >= enemy.img->getMaxFrameX())
			{
				enemy.stop = true;
				enemy.img->setFrameX(enemy.img->getMaxFrameX());
			}
		}
		break;
	}
}

void bossCreep::enter(enemyManager* boss)
{
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();

	enemy.img = IMAGEMANAGER->findImage("bossCreep");
	enemy.state = EBOSSCREEP;
	enemy.stop = false;

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

void bossCreep::exit(enemyManager* boss)
{
}
