#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include "enemyManager.h"
#include "collsion.h"

#define STAGE2NEMOMAX 16

class stage2 :  public gameNode
{
private:
	playerManager* _pm;
	enemyManager* _em;
	collsion* _collision;
	RECT _nemo[STAGE2NEMOMAX];


	POINT mWhere;

	int _probeT;

	bool _pt;
	bool _chk;

public:
	stage2();
	~stage2();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void collision();
	void pixelCollision(int direction);
	bool topPixel();
	void mousePixel(); //현재 마우스가 있는곳에 픽셀 값
	void groundSet();

	void enemyDie();
};

