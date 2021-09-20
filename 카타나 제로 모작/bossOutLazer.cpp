#include "stdafx.h"
#include "bossOutLazer.h"
#include "bossInLazer.h"
#include "bossInPattern.h"
#include "enemyManager.h"

bossStateManager* bossOutLazer::inputHandle(enemyManager* boss)
{
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();

	if (_timer > 5)
	{
		_timer = 0;
		if (enemy.x > WINSIZEX / 2)enemy.dir = ELEFT;
		else enemy.dir = ERIGHT;
		
		if (enemy.LazerCount-- > 0)return new bossInLazer;
		else return new bossInPattern;
	}
	//키입력
	return nullptr;
}

void bossOutLazer::update(enemyManager* boss)
{
	_timer++;

	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();
	//프레임
	if (_count++ % 5 == 0)
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

void bossOutLazer::enter(enemyManager* boss)
{
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();

	enemy.img = IMAGEMANAGER->findImage("bossOutLazer");
	enemy.state = EBOSSOUTLAZER;
	enemy.lazerRC = RectMake(0, 0, 0, 0);

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

void bossOutLazer::exit(enemyManager* boss)
{
}
