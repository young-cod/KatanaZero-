#include "stdafx.h"
#include "bossNoHead.h"
#include "enemyManager.h"

bossStateManager* bossNoHead::inputHandle(enemyManager* boss)
{
	return nullptr;
}

void bossNoHead::update(enemyManager* boss)
{
	_timer++;
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();
	
	//ÇÁ·¹ÀÓ
	enemy.headY -= enemy.headJP;
	enemy.headJP -= enemy.headGT;

	enemy.headRC = RectMakeCenter(enemy.headX, enemy.headY, enemy.head->getFrameWidth(), enemy.head->getFrameHeight());
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
	if (_headCount++ % 5 == 0)
	{
		switch (enemy.dir)
		{
		case ELEFT:
			enemy.headX -=20.0f;
	
			if (_count++ % 2 == 0)
			{
				enemy.head->setFrameX(enemy.head->getFrameX() - 1);
				if (enemy.head->getFrameX() <= 0)
				{
					enemy.head->setFrameX(enemy.head->getMaxFrameX());
				}
			}
			break;
		case ERIGHT:
			enemy.headX += 20.0f;
			if (_headCount++ % 2 == 0)
			{
				enemy.head->setFrameX(enemy.head->getFrameX() + 1);
				if (enemy.head->getFrameX() >= enemy.head->getMaxFrameX())
				{
					enemy.head->setFrameX(0);
				}
			}
			break;
		}
	}
}

void bossNoHead::enter(enemyManager* boss)
{
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();

	enemy.img = IMAGEMANAGER->findImage("bossNoHead");
	enemy.state = EBOSSNOHEAD;

	enemy.head = IMAGEMANAGER->findImage("bossFHead");
	enemy.headX = enemy.x;
	enemy.headY = enemy.y-60;
	enemy.headJP = 11.0f;
	enemy.headGT = 2.3f;
	_headCount = 0;
	enemy.headRC = RectMakeCenter(enemy.headX, enemy.headY, enemy.head->getFrameWidth(), enemy.head->getFrameHeight());
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
}

void bossNoHead::exit(enemyManager* boss)
{
}
