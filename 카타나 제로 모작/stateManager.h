#pragma once

class playerManager;

class stateManager
{
private:
public:
	virtual stateManager* inputHandle(playerManager* player)=0;
	virtual void update(playerManager* player) = 0;
	virtual void enter(playerManager* player) = 0;
	virtual void exit(playerManager* player) = 0;
};

