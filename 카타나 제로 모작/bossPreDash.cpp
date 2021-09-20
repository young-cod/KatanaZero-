#include "stdafx.h"
#include "bossIdle.h"
#include "bossDash.h"
#include "bossPreDash.h"
#include "enemyManager.h"

bossStateManager* bossPreDash::inputHandle(enemyManager* boss)
{
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();
	if (_timer > 40)
	{
		_timer = 0;
		return new bossDash;
	}
	//키입력
	return nullptr;
}

void bossPreDash::update(enemyManager* boss)
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
				enemy.img->setFrameX(0);
			}
			break;
		case ERIGHT:
			enemy.img->setFrameX(enemy.img->getFrameX() + 1);
			if (enemy.img->getFrameX() >= enemy.img->getMaxFrameX())
			{
				enemy.img->setFrameX(enemy.img->getMaxFrameX());
			}
			break;
		}
	}
}

void bossPreDash::enter(enemyManager* boss)
{
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();

	enemy.img = IMAGEMANAGER->findImage("bossPreDash");
	enemy.state = EBOSSPREDASH;
	enemy.beforeState = EBOSSPREDASH;

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

void bossPreDash::exit(enemyManager* boss)
{
}
