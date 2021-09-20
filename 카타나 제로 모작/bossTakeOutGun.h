#pragma once
#include "bossStateManager.h"

class enemyManager;

class bossTakeOutGun : public bossStateManager
{
private:
	int _count;
	int _timer = 0;
	int _rand;
public:
	virtual bossStateManager* inputHandle(enemyManager* boss);
	virtual void update(enemyManager* boss);
	virtual void enter(enemyManager* boss);
	virtual void exit(enemyManager* boss);
};

