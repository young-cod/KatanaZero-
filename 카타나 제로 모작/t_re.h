#pragma once
#include "gameNode.h"
class t_re :  public gameNode
{
private:

public:
	t_re();
	~t_re();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

