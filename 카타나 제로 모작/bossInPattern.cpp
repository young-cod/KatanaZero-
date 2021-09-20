#include "stdafx.h"
#include "bossInPattern.h"
#include "bossIdle.h"
#include "bossPreDash.h"
#include "bossTakeOutGun.h"
#include "bossInLazer.h"
#include "enemyManager.h"
#include "playerManager.h"

bossStateManager* bossInPattern::inputHandle(enemyManager* boss)
{
	//플레이어 불러오기
	//getPlayer()->getPlayer().x;
	int randState = RND->getInt(3);
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();
	if (_rand > 80)
	{
		if (enemy.beforeState == EBOSSPREDASH)
		{
			if (randState == 0)	return new bossTakeOutGun;
			else
			{
				enemy.LazerCount = 2;
				return new bossInLazer;
			}
		}
		else return new bossPreDash;
	}
	else if (_rand < 80 && _rand>50)
	{
		if (enemy.beforeState == EBOSSTAKEOUTGUN)
		{
			if (randState == 0)	return new bossPreDash;
			else
			{
				enemy.LazerCount = 2;
				return new bossInLazer;
			}
		}
		else return new bossTakeOutGun;
	}
	else if (_rand < 50 && _rand>10)
	{
		if (enemy.beforeState == EBOSSINLAZER)
		{
			if (randState == 0)	return new bossPreDash;
			else return new bossTakeOutGun;
		}
		else
		{
			enemy.LazerCount = 2;
			return new bossInLazer;
		}
	}
	else
	{
		return new bossIdle;
	}
	//키입력
	return nullptr;
}

void bossInPattern::update(enemyManager* boss)
{
	_timer++;
	if (_timer++)
	{
		_timer = 0;
		_rand = RND->getInt(100);
	}
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

void bossInPattern::enter(enemyManager* boss)
{
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();

	enemy.img = IMAGEMANAGER->findImage("bossInPattern");
	int rand = RND->getInt(3);
	if (rand == 0)
	{
		enemy.x = 1080;
		enemy.dir = ELEFT;
	}
	else
	{
		enemy.x = 250;
		enemy.dir = ERIGHT;
	}
	enemy.y = 532;
	enemy.state = EBOSSINPATTERN;
	enemy.rc = RectMakeCenter(enemy.x, enemy.y, enemy.img->getFrameWidth(), enemy.img->getFrameHeight());

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

void bossInPattern::exit(enemyManager* boss)
{
}
