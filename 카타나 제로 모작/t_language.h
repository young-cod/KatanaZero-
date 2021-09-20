#pragma once
#include "gameNode.h"
class t_language :  public gameNode
{
private:
public:
	t_language();
	~t_language();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

