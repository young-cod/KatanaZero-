#pragma once
#include "gameNode.h"

class title : public gameNode
{
private:
	RECT rc;

public:
	title();
	~title();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

