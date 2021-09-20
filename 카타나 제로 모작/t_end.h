#pragma once
#include "gameNode.h"
class t_end :  public gameNode
{
private:
public:
	t_end();
	~t_end();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

