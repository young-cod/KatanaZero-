#include "stdafx.h"
#include "bossDie.h"
#include "enemyManager.h"

bossStateManager* bossDie::inputHandle(enemyManager* boss)
{
	return nullptr;
}

void bossDie::update(enemyManager* boss)
{
	_timer++;
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();
	//프레임

	switch (enemy.dir)
	{
	case ELEFT:
		if (_count++ % 7 == 0)
		{
			enemy.img->setFrameX(enemy.img->getFrameX() - 1);
			if (enemy.img->getFrameX() <= 0)
			{
				enemy.img->setFrameX(0);
			}
		}
		break;
	case ERIGHT:
		if (_count++ % 7 == 0)
		{
			enemy.img->setFrameX(enemy.img->getFrameX() + 1);
			if (enemy.img->getFrameX() >= enemy.img->getMaxFrameX())
			{
				enemy.img->setFrameX(enemy.img->getMaxFrameX());
			}
		}
		break;
	}
}

void bossDie::enter(enemyManager* boss)
{
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();

	enemy.img = IMAGEMANAGER->findImage("bossDie");
	enemy.state = EDIE;

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

void bossDie::exit(enemyManager* boss)
{
}
