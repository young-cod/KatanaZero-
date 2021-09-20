#pragma once
#include "gameNode.h"

struct tagObject
{
	image* img;
	RECT rc;
	float x, y;
};

class objManager : public gameNode
{
private:
	tagObject _ground;

public:
	objManager();
	~objManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	tagObject getGround() { return _ground; }

};

