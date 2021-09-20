#include "stdafx.h"
#include "bullet.h"

bullet::bullet()
{
}

bullet::~bullet()
{
}

HRESULT bullet::init(int bulletMax, float range)
{
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void bullet::release()
{
}

void bullet::update(bool type)
{
	move(type);

	if (stay)
	{
		bulletFrame();
		_timer++;
		if (_timer > 80)
		{
			_timer = 0;
			mine.timer = 0;
			stay = false;
			mine.rc = RectMakeCenter(0,0,0,0);
		}
		if (_timer > 50)
		{
			mine.timer++;
			mine.rc = RectMakeCenter(mine.x, mine.y, 220, 220);
		}
	}

}

void bullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		//보스스테이지는 프레임렌더 일반은 그냥 렌더
		_viBullet->img->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
	if (stay)
	{
		if (_timer > 50)mine.img->frameRender(getMemDC(), mine.x-10, mine.y-10);
		else mine.img->frameRender(getMemDC(), mine.rc.left, mine.rc.top);
		IMAGEMANAGER->findImage("mineCircle")->render(getMemDC(),
			mine.x - (IMAGEMANAGER->findImage("mineCircle")->getWidth() / 2),
			mine.y - (IMAGEMANAGER->findImage("mineCircle")->getHeight() / 2));
	}
		Rectangle(getMemDC(), mine.rc);
}

void bullet::fire(float fireX, float fireY, float angle, bool enemyType, bool atkType)
{
	if (!enemyType)
	{
		if (_bulletMax < _vBullet.size())return;

		tagBullet newbullet;
		ZeroMemory(&newbullet, sizeof(tagBullet));
		newbullet.img = new image;
		newbullet.img->init("image/enemy/enemy_bullet.bmp", 5, 5, true, RGB(255, 0, 255));
		newbullet.x = newbullet.fireX = fireX;
		newbullet.y = newbullet.fireY = fireY;
		newbullet.rc = RectMakeCenter(fireX, fireY, 0, 0);
		newbullet.isFire = true;
		newbullet.speed = 10.0f;
		newbullet.angle = angle;
		_vBullet.push_back(newbullet);
	}
	else
	{
		if (_bulletMax < _vBullet.size())return;

		tagBullet newbullet;
		ZeroMemory(&newbullet, sizeof(tagBullet));
		newbullet.img = new image;
		if (!atkType)newbullet.img->init("image/enemy/enemy_bullet.bmp", 5, 5, true, RGB(255, 0, 255));
		else newbullet.img->init("image/boss/boss_mine.bmp", 20, 20, true, RGB(255, 0, 255));
		newbullet.x = newbullet.fireX = fireX;
		newbullet.y = newbullet.fireY = fireY;
		newbullet.rc = RectMakeCenter(fireX, fireY, 0, 0);
		newbullet.isFire = true;
		newbullet.speed = 10.0f;
		newbullet.angle = angle;
		newbullet.isbomb = false;
		_vBullet.push_back(newbullet);
		cout << _vBullet.size() << endl;
	}
}

void bullet::move(bool type)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{

		if (_timer > 50)
		{
			stay = false;
		}
		if (!stay)
		{
			_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
			_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;
		}
		if (_viBullet->x > 50)_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, 5, 5);
		else _viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, 0, 0);
		//사거리 넘게 날아가면 소멸
		if (!type)
		{
			if (_range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
			{
				SAFE_RELEASE(_viBullet->img);
				SAFE_DELETE(_viBullet->img);

				_viBullet = _vBullet.erase(_viBullet);
			}
			else ++_viBullet;
		}
		else
		{
			if (_range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY) && !stay)
			{
				stay = true;

				mine.img = new image;
				mine.img->init("image/boss/boss_mine_2x1.bmp", 40, 20, 2, 1, true, RGB(255, 0, 255));
				mine.x = _viBullet->x;
				mine.y = _viBullet->y;
				mine.rc = RectMakeCenter(mine.x, mine.y, 20, 20);

				SAFE_RELEASE(_viBullet->img);
				SAFE_DELETE(_viBullet->img);

				_viBullet = _vBullet.erase(_viBullet);
			}
			else ++_viBullet;
		}
		//플레이어가 맞으면 소멸
		//플레이어 공격모션에 맞으면 소멸
	}
}

void bullet::bulletFrame()
{
	if (_count++ % 5 == 0)
	{
		if (mine.img->getFrameX() >= mine.img->getMaxFrameX())mine.img->setFrameX(-1);
		mine.img->setFrameX(mine.img->getFrameX() + 1);
	}

}
