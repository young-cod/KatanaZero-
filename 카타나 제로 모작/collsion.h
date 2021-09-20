#pragma once
#include <vector>

class playerManager;
class enemyManager;

class collsion
{
private:
	vector<RECT> _vRect;
	playerManager* _player;
	enemyManager* _enemy;
public:
	void addRect(RECT rc);

	bool playerCollision();
	bool playerBulletCollision();

	bool playerBossCollision();
	bool playerLazerCollision();
	bool playerMineCollision();

	bool playerGruntCollision();
	bool enemyCollision();
	bool enemyBulletCollision();

	void setPlayer(playerManager* player) { _player = player; }
	void setEnemy(enemyManager* enemy) { _enemy = enemy; }
};