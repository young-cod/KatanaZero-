#include "stdafx.h"
#include "bossIdle.h"
#include "bossPreDash.h"
#include "enemyManager.h"

bossStateManager* bossIdle::inputHandle(enemyManager* boss)
{
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();
	if (_timer > 40)
	{
		_timer = 0;
		if (enemy.x > WINSIZEX/2)enemy.dir = ELEFT;
		else enemy.dir = ERIGHT;
		return new bossPreDash;
	}
    //키입력
    return nullptr;
}

void bossIdle::update(enemyManager* boss)
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

void bossIdle::enter(enemyManager* boss)
{
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();

	enemy.img = IMAGEMANAGER->findImage("bossIdle");
	enemy.state = EIDLE;
	
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

void bossIdle::exit(enemyManager* boss)
{
}
