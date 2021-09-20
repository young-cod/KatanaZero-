#pragma once
#include "gameNode.h"
#include "bald.h"
#include "cop.h"
#include "grunt.h"
#include "boss.h"
#include "collsion.h"
#include "bossStateManager.h"
#include <vector>

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;

private:
	vEnemy _vNormal;
	viEnemy _viNormal;

	bossStateManager* _state;
public:
	enemyManager();
	~enemyManager();

	collsion* _collision;

	virtual HRESULT init();
	virtual void release();
	virtual void update(string strkey);
	virtual void render();

	void setBald(int x, int y);
	void setCop(int x, int y);
	void setGrunt(int x, int y);
	void setBoss(int x, int y);

	void imgSet();

	vEnemy& getVEnemy() { return _vNormal; }
	viEnemy& getViEnemy() { return _viNormal; }

	void inputHandle();

	bossStateManager* getBSM() { return _state; }
	void setState(bossStateManager* state) { _state = state; }
};