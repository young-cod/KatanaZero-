#include "stdafx.h"
#include "bossHit.h"
#include "bossCreep.h"
#include "bossOutPattern.h"
#include "enemyManager.h"

bossStateManager* bossHit::inputHandle(enemyManager* boss)
{
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();
	if (enemy.bossHitCount < 1)return new bossCreep;
	if (_timer > 80)
	{
		if (enemy.bossHitCount > 0)return new bossOutPattern;
	}
	cout << enemy.bossHitCount << "보스체력" << endl;
	return nullptr;
}

void bossHit::update(enemyManager* boss)
{
	_timer++;
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();
	if (enemy.bossHitCount > 0)
	{
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
}

void bossHit::enter(enemyManager* boss)
{
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();

	enemy.img = IMAGEMANAGER->findImage("bossHit");
	enemy.state = EBOSSHIT;
	_timer = 0;
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

void bossHit::exit(enemyManager* boss)
{
}
