#pragma once
#include "gameNode.h"
#include "objManager.h"
#include "title.h"
#include "t_re.h"
#include "t_option.h"
#include "t_language.h"
#include "t_end.h"
#include "stage2.h"
#include "bossStage.h"


class playGround : public gameNode
{
private:

	image* _background;

	objManager* _ground;

	float dudu;


public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void sceneSet();
};

