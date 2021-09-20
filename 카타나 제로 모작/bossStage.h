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

	bool _pt;			//���� ���� Ȯ��
	bool _chk;			//�Ʒ� Ű ������ �� Ȯ�� �����ִ� �뵵
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

