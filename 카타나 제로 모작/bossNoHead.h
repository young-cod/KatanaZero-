#pragma once
#include "bossStateManager.h"

class enemyManager;

class bossNoHead : public bossStateManager
{
private:
	int _count;
	int _timer = 0;
	int _headCount;
public:
	virtual bossStateManager* inputHandle(enemyManager* boss);
	virtual void update(enemyManager* boss);
	virtual void enter(enemyManager* boss);
	virtual void exit(enemyManager* boss);

};

