#pragma once

class enemyManager;
class playerManager;

class bossStateManager
{
private:
protected:
	playerManager* _player;
public:
	virtual bossStateManager* inputHandle(enemyManager* boss) = 0;
	virtual void update(enemyManager* boss) = 0;
	virtual void enter(enemyManager* boss) = 0;
	virtual void exit(enemyManager* boss) = 0;

	void setPlayer(playerManager* player) { _player = player; }
	playerManager* getPlayer() { return _player; }
};

