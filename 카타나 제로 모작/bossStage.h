#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include "enemyManager.h"
#include "collsion.h"
#include "bossStateManager.h"

#define BOSSNEMOMAX 3

class bossStage : public gameNode
{
private:
	playerManager* _pm;
	enemyManager* _em;
	collsion* _collision;
	RECT _nemo[BOSSNEMOMAX];

	bool _pt;			//수직 수평 확인
	bool _chk;			//아래 키 눌렀을 때 확인 시켜주는 용도
	bossStateManager* _bSM;
public:
	bossStage();
	~bossStage();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void collision();
	void pixelCollision(int direction);
	void groundSet();

};

