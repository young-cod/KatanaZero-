#pragma once
#include "gameNode.h"
class t_option : public gameNode
{
private:

public:
	t_option();
	~t_option();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

