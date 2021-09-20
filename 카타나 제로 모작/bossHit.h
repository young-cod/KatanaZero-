#pragma once
#include "bossStateManager.h"

class enemyManager;

class bossHit : public bossStateManager
{
private:
	int _count;
	int _timer = 0;
public:
	virtual bossStateManager* inputHandle(enemyManager* boss);
	virtual void update(enemyManager* boss);
	virtual void enter(enemyManager* boss);
	virtual void exit(enemyManager* boss);
};

