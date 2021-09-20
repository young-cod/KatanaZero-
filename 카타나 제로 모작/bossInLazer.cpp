#include "stdafx.h"
#include "bossInLazer.h"
#include "bossOutLazer.h"
#include "enemyManager.h"

bossStateManager* bossInLazer::inputHandle(enemyManager* boss)
{
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();
	if (_timer > 25)
	{
		_timer = 0;
		if (enemy.x > WINSIZEX / 2)enemy.dir = ELEFT;
		else enemy.dir = ERIGHT;
		return new bossOutLazer;
	}
	//키입력
	return nullptr;
}

void bossInLazer::update(enemyManager* boss)
{
	_timer++;
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();
	//프레임
	if (_count++ % 4 == 0)
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
	if (_lazerCount++ % 3 == 0)
	{
		enemy.lazer->setFrameX(enemy.lazer->getFrameX() + 1);
		if (enemy.lazer->getFrameX() >= enemy.lazer->getMaxFrameX())enemy.lazer->setFrameX(0);
	}
}

void bossInLazer::enter(enemyManager* boss)
{
	tagEnemy& enemy = boss->getVEnemy()[0]->getEnemy();

	enemy.img = IMAGEMANAGER->findImage("bossInLazer");
	enemy.state = EBOSSINLAZER;
	enemy.beforeState = EBOSSINLAZER;
	_randX = RND->getInt(5);
	if (_randX == 0)enemy.x = 300;
	else if(_randX==1)enemy.x = 500;
	else if(_randX==2)enemy.x = 700;
	else if(_randX==3)enemy.x = 900;
	else enemy.x = 1100;

	cout << enemy.x << "랜덤값ㅅㅅㅅㅅㅅㅅㅅㅅㅅㅅㅅㅅ" << endl << endl << endl;
	enemy.y = 180;
	enemy.rc = RectMakeCenter(enemy.x, enemy.y, enemy.img->getFrameWidth(), enemy.img->getFrameHeight());

	enemy.lazer = IMAGEMANAGER->findImage("bossLazer");
	enemy.lazerX = enemy.rc.left;
	enemy.lazerY = enemy.rc.bottom;
	enemy.lazerRC = RectMake(enemy.lazerX, enemy.lazerY, enemy.lazer->getFrameWidth(), enemy.lazer->getFrameHeight());

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

void bossInLazer::exit(enemyManager* boss)
{
}
