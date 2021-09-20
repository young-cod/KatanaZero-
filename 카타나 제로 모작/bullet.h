#pragma once
#include "gameNode.h"
#include <vector>

class playerManager;

struct tagBullet
{
	image* img;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float angle;
	float speed;
	bool isFire;
	bool isbomb;
};

struct tagMine
{
	image* img;
	RECT rc;
	float x, y;
	int timer;
};

class bullet : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range; //�Ѿ��� ������ ���󰥰��ΰ�
	int _bulletMax; //�Ѿ� �ִ� ����
	bool stay = false;

	int _timer=0;
	int _count=0;

	tagMine mine;
public:
	bullet();
	~bullet();

	virtual HRESULT init(int bulletMax, float range);
	virtual void release();
	virtual void update(bool type = false);
	virtual void render();

	void fire(float fireX, float fireY, float angle, bool type= false, bool  atkType = false);
	void move(bool type = false);

	void bulletFrame();

	vector<tagBullet>& getVBullet() { return _vBullet; }
};

