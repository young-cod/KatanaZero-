#pragma once
#include "stateManager.h"

class playerManager;

class run : public stateManager
{
private:
	int _count;
public:
	virtual stateManager* inputHandle(playerManager* player);
	virtual void update(playerManager* player);
	virtual void enter(playerManager* player);
	virtual void exit(playerManager* player);
};

