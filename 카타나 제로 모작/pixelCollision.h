#pragma once
#include "gameNode.h"

class pixelCollision : public gameNode
{
private:
	image* _mountain;
	image* _ball;

	RECT _rc;
	float _x, _y;
	int _probeY; //probe == Å½»ç

public:
	pixelCollision();
	~pixelCollision();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

