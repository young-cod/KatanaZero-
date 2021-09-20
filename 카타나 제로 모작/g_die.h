#pragma once
#include "stateManager.h"

class playerManager;

class g_die :public stateManager
{
private:
	int _count;
	int _power = 0;

	int _probeB;
	bool _isFall;
public:
	virtual stateManager* inputHandle(playerManager* player);
	virtual void update(playerManager* player);
	virtual void enter(playerManager* player);
	virtual void exit(playerManager* player);

	bool pixelCollision(playerManager* player);
};

