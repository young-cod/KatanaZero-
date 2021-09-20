#include "stdafx.h"
#include "enemy.h"
#include "playerManager.h"
#include "bossIdle.h"

enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init()
{

	return S_OK;
}

HRESULT enemy::init(bool enemyType, const char* imageName, POINT position, TYPEENEMY type, float distance)
{
	if (!enemyType)
	{
		_index = 0;
		_count = _fireCount = 0;
		_enemy.x = position.x;
		_enemy.y = position.y;
		_enemy.distance = distance;
		_enemy.timer = 0;
		_enemy.atkTimer = 0;
		_enemy.img = IMAGEMANAGER->findImage(imageName);
		_enemy.type = type;
		_enemy.rc = RectMakeCenter(_enemy.x, _enemy.y,
			_enemy.img->getFrameWidth(),
			_enemy.img->getFrameHeight());

		_enemy.detectRC = RectMakeCenterY(_enemy.x, _enemy.y - 150, 800, _enemy.rc.bottom);


		int rand = RND->getInt(2);
		rand == 0 ? state(ERIGHT, EIDLE, 0) : state(ELEFT, EIDLE, 1);


		_enemy.state = EIDLE;

		if (type != GRUNT)
		{
			_bullet = new bullet;
			_bullet->init(1, 900);
		}

	}
	else
	{
		_index = 0;
		_count = _fireCount = 0;
		_enemy.x = position.x;
		_enemy.y = position.y;
		_enemy.distance = distance;
		_enemy.timer = 0;
		_enemy.atkTimer = 0;
		_enemy.img = IMAGEMANAGER->findImage(imageName);
		_enemy.type = type;
		_enemy.bossHitCount = 2;
		_enemy.rc = RectMakeCenter(_enemy.x, _enemy.y,
			_enemy.img->getFrameWidth(),
			_enemy.img->getFrameHeight());

		_enemy.detectRC = RectMakeCenterY(_enemy.x, _enemy.y - 150, 800, _enemy.rc.bottom);

		_enemy.dir = ELEFT;
		_enemy.state = EIDLE;

		_bullet = new bullet;
		_bullet->init(1, 400);

		_enemy.bulletCount = 1;

	}
	return S_OK;
}

void enemy::release()
{
	SAFE_DELETE(_bullet);
}

void enemy::update(string strkey)
{
	//일반 적 업데이트
	if (_enemy.type == TALLBOSS)
	{
		if (_enemy.state == EBOSSSHOOT)bossFire();
		_bullet->update(1);

		pixelCollision(strkey);

		_enemy.rc = RectMakeCenter(_enemy.x, _enemy.y,
			_enemy.img->getFrameWidth(),
			_enemy.img->getFrameHeight());
		_enemy.detectRC = RectMakeCenterY(_enemy.x, _enemy.y - 150, 800, _enemy.rc.bottom);
	}
	else
	{
		if (!_enemy.isDead)move();
		if (_enemy.type != GRUNT)_bullet->update();
		frame();

		pixelCollision(strkey);

		_enemy.rc = RectMakeCenter(_enemy.x, _enemy.y,
			_enemy.img->getFrameWidth(),
			_enemy.img->getFrameHeight());
		_enemy.detectRC = RectMakeCenterY(_enemy.x, _enemy.y - 150, 800, _enemy.rc.bottom);
	}
}

void enemy::render()
{
	draw();
	if (KEYMANAGER->isToggleKey(VK_F3))
	{
		Rectangle(getMemDC(), _enemy.rc);
		Rectangle(getMemDC(), _enemy.lazerRC);
	}
	//if (_enemy.isDead)IMAGEMANAGER->findImage("bloodSwordL")->render(getMemDC(), _enemy.rc.left, _enemy.rc.right);
	if (_enemy.state == EBOSSINLAZER)_enemy.lazer->frameRender(getMemDC(), _enemy.rc.left, _enemy.rc.bottom);
	if (_enemy.state == EBOSSNOHEAD)_enemy.head->frameRender(getMemDC(), _enemy.headRC.left, _enemy.headRC.top);
}

void enemy::move()
{
	//랜덤으로 주기 줘서 바꾸기
	_enemy.timer++;
	if (_enemy.timer % 40 == 0)
	{
		_enemy.moveRand = RND->getInt(100);
		_enemy.dirRand = RND->getInt(30);
		_enemy.timer = 0;
	}

	//탐지
	if (detectPlayer())
	{
		int dis = _enemy.x - _player->getPlayer().x;
		if (dis <= 0)
			_enemy.dir = ERIGHT;
		else 
			_enemy.dir = ELEFT;
		int dist = getDistance(_player->getPlayer().x, _player->getPlayer().y, _enemy.x, _enemy.y);
		if (dist < _enemy.distance)attack();
		else run();
	}
	else
	{
		_enemy.findP = false;
		direction(_enemy.dirRand);
		idle(_enemy.moveRand);
		walk(_enemy.moveRand);
	}
}

void enemy::frame()
{
	switch (_enemy.type)
	{
	case BALD:
		_count++;
		switch (_enemy.state)
		{
		case EIDLE:
			if (_enemy.dir == ELEFT)
			{
				if (_count % 11 == 0)
				{
					_enemy.img->setFrameX(_index--);
					if (_index <= 0) _index = _enemy.img->getMaxFrameX();
				}
			}
			else
			{
				if (_count % 11 == 0)
				{
					_enemy.img->setFrameX(_index++);
					if (_index >= _enemy.img->getMaxFrameX()) _index = 0;
				}
			}

			break;
		case EWALK:
			if (_enemy.dir == ELEFT)
			{
				_enemy.x -= 4.0f;
				if (_count % 5 == 0)
				{
					_enemy.img->setFrameX(_index--);
					if (_index <= 0) _index = _enemy.img->getMaxFrameX();
				}
			}
			else
			{
				_enemy.x += 4.0f;
				if (_count % 5 == 0)
				{
					_enemy.img->setFrameX(_index++);
					if (_index >= _enemy.img->getMaxFrameX()) _index = 0;
				}
			}
			break;
		case ERUN:
			if (_enemy.dir == ELEFT)
			{
				if (_count % 4 == 0)
				{
					_enemy.img->setFrameX(_index--);
					if (_index <= 0) _index = _enemy.img->getMaxFrameX();
				}
			}
			else
			{

				if (_count % 4 == 0)
				{
					_enemy.img->setFrameX(_index++);
					if (_index >= _enemy.img->getMaxFrameX()) _index = 0;
				}
			}
			break;
		case EATTACK:
			if (_count % 10 == 0)
			{
				if (_enemy.dir == ELEFT)
				{
					_enemy.img->setFrameX(_index--);
					if (_index <= 0) _index = _enemy.img->getMaxFrameX();
				}
				else
				{
					_enemy.img->setFrameX(_index++);
					if (_index >= _enemy.img->getMaxFrameX()) _index = 0;
				}
			}
			break;
		case EDIE:
			if (_count % 15 == 0)
			{
				if (_enemy.dir == ELEFT)
				{
					_enemy.img->setFrameX(_enemy.img->getFrameX() - 1);
					if (_enemy.img->getFrameX() <= 0) _enemy.img->setFrameX(0);
				}
				else
				{
					_enemy.img->setFrameX(_enemy.img->getFrameX() + 1);
					if (_enemy.img->getFrameX() >= _enemy.img->getMaxFrameX()) _enemy.img->setFrameX(_enemy.img->getMaxFrameX());
				}
			}
			break;
			_count = 0;
		}
		break;
	case COP:
		_count++;
		switch (_enemy.state)
		{
		case EIDLE:
			if (_enemy.dir == ELEFT)
			{
				if (_count % 11 == 0)
				{
					_enemy.img->setFrameX(_index--);
					if (_index <= 0) _index = _enemy.img->getMaxFrameX();
				}
			}
			else
			{
				if (_count % 11 == 0)
				{
					_enemy.img->setFrameX(_index++);
					if (_index >= _enemy.img->getMaxFrameX()) _index = 0;
				}
			}

			break;
		case EWALK:
			if (_enemy.dir == ELEFT)
			{
				_enemy.x -= 4.0f;
				if (_count % 5 == 0)
				{
					_enemy.img->setFrameX(_index--);
					if (_index <= 0) _index = _enemy.img->getMaxFrameX();
				}
			}
			else
			{
				_enemy.x += 4.0f;
				if (_count % 5 == 0)
				{
					_enemy.img->setFrameX(_index++);
					if (_index >= _enemy.img->getMaxFrameX()) _index = 0;
				}
			}
			break;
		case ERUN:
			if (_enemy.dir == ELEFT)
			{
				if (_count % 4 == 0)
				{
					_enemy.img->setFrameX(_index--);
					if (_index <= 0) _index = _enemy.img->getMaxFrameX();
				}
			}
			else
			{
				if (_count % 4 == 0)
				{
					_enemy.img->setFrameX(_index++);
					if (_index >= _enemy.img->getMaxFrameX()) _index = 0;
				}
			}
			break;
		case EATTACK:
			if (_count % 10 == 0)
			{
				if (_enemy.dir == ELEFT)
				{
					_enemy.img->setFrameX(_index--);
					if (_index <= 0) _index = _enemy.img->getMaxFrameX();
				}
				else
				{
					_enemy.img->setFrameX(_index++);
					if (_index >= _enemy.img->getMaxFrameX()) _index = 0;
				}
			}
			break;
		case EDIE:
			if (_count % 15 == 0)
			{
				if (_enemy.dir == ELEFT)
				{
					_enemy.img->setFrameX(_enemy.img->getFrameX() - 1);
					if (_enemy.img->getFrameX() <= 0) _enemy.img->setFrameX(0);
				}
				else
				{
					_enemy.img->setFrameX(_enemy.img->getFrameX() + 1);
					if (_enemy.img->getFrameX() >= _enemy.img->getMaxFrameX()) _enemy.img->setFrameX(_enemy.img->getMaxFrameX());
				}
			}
			break;
			_count = 0;
		}
		break;
	case GRUNT:
		_count++;
		switch (_enemy.state)
		{
		case EIDLE:
			if (_enemy.dir == ELEFT)
			{
				if (_count % 11 == 0)
				{
					_enemy.img->setFrameX(_index--);
					if (_index <= 0) _index = _enemy.img->getMaxFrameX();
				}
			}
			else
			{
				if (_count % 11 == 0)
				{
					_enemy.img->setFrameX(_index++);
					if (_index >= _enemy.img->getMaxFrameX()) _index = 0;
				}
			}

			break;
		case EWALK:
			if (_enemy.dir == ELEFT)
			{
				_enemy.x -= 4.0f;
				if (_count % 5 == 0)
				{
					_enemy.img->setFrameX(_index--);
					if (_index <= 0) _index = _enemy.img->getMaxFrameX();
				}
			}
			else
			{
				_enemy.x += 4.0f;
				if (_count % 5 == 0)
				{
					_enemy.img->setFrameX(_index++);
					if (_index >= _enemy.img->getMaxFrameX()) _index = 0;
				}
			}
			break;
		case ERUN:
			if (_enemy.dir == ELEFT)
			{
				if (_count % 4 == 0)
				{
					_enemy.img->setFrameX(_index--);
					if (_index <= 0) _index = _enemy.img->getMaxFrameX();
				}
			}
			else
			{
				if (_count % 4 == 0)
				{
					_enemy.img->setFrameX(_index++);
					if (_index >= _enemy.img->getMaxFrameX()) _index = 0;
				}
			}
			break;
		case EATTACK:
			if (_count % 9 == 0)
			{
				if (_enemy.dir == ELEFT)
				{
					_enemy.img->setFrameX(_index--);
					if (_enemy.img->getFrameX() < 3)_enemy.isAtk = true;
					if (_index <= 0)
					{
						_index = _enemy.img->getMaxFrameX();
						_enemy.isAtk = false;
					}
				}
				else
				{
					_enemy.img->setFrameX(_index++);
					if (_enemy.img->getFrameX() > 3)_enemy.isAtk = true;
					if (_index >= _enemy.img->getMaxFrameX())
					{

						_index = 0;
						_enemy.isAtk = false;
					}
				}
			}
			break;
		case EDIE:
			if (_count % 15 == 0)
			{
				if (_enemy.dir == ELEFT)
				{
					_enemy.img->setFrameX(_enemy.img->getFrameX()-1);
					if (_enemy.img->getFrameX() <= 0) _enemy.img->setFrameX(0);
				}
				else
				{
					_enemy.img->setFrameX(_enemy.img->getFrameX()+1);
					if (_enemy.img->getFrameX() >= _enemy.img->getMaxFrameX()) _enemy.img->setFrameX(_enemy.img->getMaxFrameX());
				}
			}
			break;
			_count = 0;
		}
		break;
	}
}

void enemy::state(EDIRECTION dir, ESTATE state, int y)
{
	_enemy.state = state;
	_enemy.dir = dir;

	switch (_enemy.type)
	{
	case BALD:
		switch (state)
		{
		case EIDLE:
			_enemy.img = IMAGEMANAGER->findImage("baldIdle");
			_enemy.img->setFrameY(y);
			_index = (dir == ERIGHT) ? 0 : _enemy.img->getMaxFrameX();
			break;
		case EWALK:
			_enemy.img = IMAGEMANAGER->findImage("baldWalk");
			_enemy.img->setFrameY(y);
			_index = (dir == ERIGHT) ? 0 : _enemy.img->getMaxFrameX();
			break;
		case ERUN:
			_enemy.img = IMAGEMANAGER->findImage("baldRun");
			_enemy.img->setFrameY(y);
			_index = (dir == ERIGHT) ? 0 : _enemy.img->getMaxFrameX();
			break;
		case EATTACK:
			_enemy.img = IMAGEMANAGER->findImage("baldIdle");
			_enemy.img->setFrameY(y);
			_index = (dir == ERIGHT) ? 0 : _enemy.img->getMaxFrameX();
			break;
		case EDIE:
			_enemy.img = IMAGEMANAGER->findImage("baldDie");
			_enemy.img->setFrameY(y);
			_index = (dir == ERIGHT) ? 0 : _enemy.img->getMaxFrameX();
			break;
		}
		break;
	case COP:
		switch (state)
		{
		case EIDLE:
			_enemy.img = IMAGEMANAGER->findImage("copIdle");
			_enemy.img->setFrameY(y);
			_index = (dir == ERIGHT) ? 0 : _enemy.img->getMaxFrameX();
			break;
		case EWALK:
			_enemy.img = IMAGEMANAGER->findImage("copWalk");
			_enemy.img->setFrameY(y);
			_index = (dir == ERIGHT) ? 0 : _enemy.img->getMaxFrameX();
			break;
		case ERUN:
			_enemy.img = IMAGEMANAGER->findImage("copRun");
			_enemy.img->setFrameY(y);
			_index = (dir == ERIGHT) ? 0 : _enemy.img->getMaxFrameX();
			break;
		case EATTACK:
			_enemy.img = IMAGEMANAGER->findImage("copIdle");
			_enemy.img->setFrameY(y);
			_index = (dir == ERIGHT) ? 0 : _enemy.img->getMaxFrameX();
			break;
		case EDIE:
			_enemy.img = IMAGEMANAGER->findImage("copDie");
			_enemy.img->setFrameY(y);
			_index = (dir == ERIGHT) ? 0 : _enemy.img->getMaxFrameX();
			break;
		}
		break;
	case GRUNT:
		switch (state)
		{
		case EIDLE:
			_enemy.img = IMAGEMANAGER->findImage("gruntIdle");
			_enemy.img->setFrameY(y);
			_index = (dir == ERIGHT) ? 0 : _enemy.img->getMaxFrameX();
			break;
		case EWALK:
			_enemy.img = IMAGEMANAGER->findImage("gruntWalk");
			_enemy.img->setFrameY(y);
			_index = (dir == ERIGHT) ? 0 : _enemy.img->getMaxFrameX();
			break;
		case ERUN:
			_enemy.img = IMAGEMANAGER->findImage("gruntRun");
			_enemy.img->setFrameY(y);
			_index = (dir == ERIGHT) ? 0 : _enemy.img->getMaxFrameX();
			break;
		case EATTACK:
			_enemy.img = IMAGEMANAGER->findImage("gruntAttack");
			_enemy.img->setFrameY(y);
			_index = (dir == ERIGHT) ? 0 : _enemy.img->getMaxFrameX();
			break;
		case EDIE:
			_enemy.img = IMAGEMANAGER->findImage("gruntDie");
			_enemy.img->setFrameY(y);
			_index = (dir == ERIGHT) ? 0 : _enemy.img->getMaxFrameX();
			break;
		}
		break;
	}

}

void enemy::pixelCollision(string strkey)
{
	_enemy.probeB = _enemy.rc.bottom;
	_enemy.probeL = _enemy.rc.left;
	_enemy.probeR = _enemy.rc.right;

	drcChk = RectMakeCenter(_enemy.x, _enemy.probeB, 5, 5);


	//아래
	for (int i = _enemy.probeB - 20; i < _enemy.probeB + 20; ++i)
	{

		COLORREF color = GetPixel(IMAGEMANAGER->findImage(strkey)->getMemDC(), _enemy.x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//계단 만 받을지 생각해보자 탐지 범위도 생각해보자
		if (!(r == 255 && g == 0 && b == 255))
		{
			_enemy.y = i - _enemy.img->getFrameHeight() / 2;
			break;
		}
	}
	//왼쪽
	for (int i = _enemy.probeL - 20; i < _enemy.probeL + 20; ++i)
	{

		COLORREF color = GetPixel(IMAGEMANAGER->findImage(strkey)->getMemDC(), i, _enemy.y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0) && !(r == 255 && g == 0 && b == 0))
		{
			_enemy.x = i - _enemy.img->getFrameWidth() / 2;
			_enemy.state = EIDLE;
			break;
		}
	}
	//오른쪽
	for (int i = _enemy.probeR - 20; i < _enemy.probeR + 20; ++i)
	{

		COLORREF color = GetPixel(IMAGEMANAGER->findImage(strkey)->getMemDC(), i, _enemy.y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0) && !(r == 255 && g == 0 && b == 0))
		{
			_enemy.x = i + _enemy.img->getFrameWidth() / 2;
			_enemy.state = EIDLE;
			break;
		}
	}

	dRC = RectMakeCenter(_enemy.x, _enemy.rc.bottom, 5, 5);
	//_enemy.rc = RectMakeCenter(_enemy.x, _enemy.probeB, _enemy.img->getFrameWidth(), _enemy.img->getFrameHeight());
}


bool enemy::detectPlayer()
{
	RECT temp;
	if (IntersectRect(&temp, &_player->getPlayer().rc, &_enemy.detectRC))
	{
		return true;
	}
	return false; 
}

void enemy::draw()
{
	_enemy.img->frameRender(getMemDC(), _enemy.rc.left, _enemy.rc.top);
	if (_enemy.type != GRUNT)_bullet->render();
	if (_enemy.findP && !_enemy.isDead)IMAGEMANAGER->findImage("findPlayer")->render(getMemDC(),
		_enemy.x, _enemy.rc.top - 20);

}

void enemy::direction(int rand)
{
	if (rand < 4)_enemy.dir = ERIGHT;
	else _enemy.dir = ELEFT;
}

void enemy::walk(int rand)
{
	//walk
	if (rand < 2)
	{
		_enemy.state = EWALK;
		switch (_enemy.type)
		{
		case BALD:
			_enemy.img = IMAGEMANAGER->findImage("baldWalk");
			(_enemy.dir == ERIGHT) ? _enemy.img->setFrameY(0) : _enemy.img->setFrameY(1);
			break;
		case COP:
			_enemy.img = IMAGEMANAGER->findImage("copWalk");
			(_enemy.dir == ERIGHT) ? _enemy.img->setFrameY(0) : _enemy.img->setFrameY(1);
			break;
		case GRUNT:
			_enemy.img = IMAGEMANAGER->findImage("gruntWalk");
			(_enemy.dir == ERIGHT) ? _enemy.img->setFrameY(0) : _enemy.img->setFrameY(1);
			break;
		}
	}
}

void enemy::idle(int rand)
{
	if (rand > 1)
	{
		_enemy.state = EIDLE;
		switch (_enemy.type)
		{
		case BALD:
			_enemy.img = IMAGEMANAGER->findImage("baldIdle");
			(_enemy.dir == ERIGHT) ? _enemy.img->setFrameY(0) : _enemy.img->setFrameY(1);
			break;
		case COP:
			_enemy.img = IMAGEMANAGER->findImage("copIdle");
			(_enemy.dir == ERIGHT) ? _enemy.img->setFrameY(0) : _enemy.img->setFrameY(1);
			break;
		case GRUNT:
			_enemy.img = IMAGEMANAGER->findImage("gruntIdle");
			(_enemy.dir == ERIGHT) ? _enemy.img->setFrameY(0) : _enemy.img->setFrameY(1);
			break;
		}
	}
}

void enemy::run()
{
	_enemy.findP = true;
	_enemy.state = ERUN;
	switch (_enemy.type)
	{
	case BALD:
		_enemy.img = IMAGEMANAGER->findImage("baldRun");
		if (_enemy.x >= _player->getPlayer().x)
		{
			_enemy.dir = ELEFT;
			_enemy.img->setFrameY(1);
			_enemy.x -= 6.0f;
		}
		else
		{
			_enemy.dir = ERIGHT;
			_enemy.img->setFrameY(0);
			_enemy.x += 6.0f;
		}
		break;
	case COP:
		_enemy.img = IMAGEMANAGER->findImage("copRun");
		if (_enemy.x >= _player->getPlayer().x)
		{
			_enemy.dir = ELEFT;
			_enemy.img->setFrameY(1);
			_enemy.x -= 6.0f;
		}
		else
		{
			_enemy.dir = ERIGHT;
			_enemy.img->setFrameY(0);
			_enemy.x += 6.0f;
		}
		break;
	case GRUNT:
		_enemy.img = IMAGEMANAGER->findImage("gruntRun");
		if (_enemy.x >= _player->getPlayer().x)
		{
			_enemy.dir = ELEFT;
			_enemy.img->setFrameY(1);
			_enemy.x -= 6.0f;
		}
		else
		{
			_enemy.dir = ERIGHT;
			_enemy.img->setFrameY(0);
			_enemy.x += 6.0f;
		}
		break;
	}
}

void enemy::attack()
{
	_enemy.atkTimer++;
	int rand = RND->getFromIntTo(30, 50);
	if (_enemy.atkTimer % rand == 0 && _enemy.type != GRUNT)
	{
		if (!_enemy.isDead)
		{
			_bullet->fire((_enemy.dir == ELEFT) ? _enemy.rc.left : _enemy.rc.right,
				_enemy.y - 5, getAngle(_enemy.x, _enemy.y,
					_player->getPlayer().x,
					_player->getPlayer().y
				));
			EFFECTMANAGER->playEffect("gunSpark", (_enemy.dir == ELEFT) ?_enemy.x-70 :_enemy.rc.right+40, _enemy.y-5, (_enemy.dir == ELEFT) ? ERIGHT : ELEFT);
		}
		_enemy.atkTimer = 0;
	}

	_enemy.findP = false;
	_enemy.state = EATTACK;

	switch (_enemy.type)
	{
	case BALD:
		_enemy.img = IMAGEMANAGER->findImage("baldIdle");
		(_enemy.dir == ELEFT) ? _enemy.img->setFrameY(1) : _enemy.img->setFrameY(0);
		break;
	case COP:
		_enemy.img = IMAGEMANAGER->findImage("copIdle");
		(_enemy.dir == ELEFT) ? _enemy.img->setFrameY(1) : _enemy.img->setFrameY(0);
		break;
	case GRUNT:
		_enemy.img = IMAGEMANAGER->findImage("gruntAttack");
		(_enemy.dir == ELEFT) ? _enemy.img->setFrameY(1) : _enemy.img->setFrameY(0);
		break;
	}

}

void enemy::bossFire()
{
	float randAngle;

	if (_enemy.dir == ELEFT)	randAngle = RND->getFromFloatTo(2.07f, 2.64f);
	else randAngle = RND->getFromFloatTo(0.5f, 1.07f);

	if (_enemy.bulletCount > 0)
	{
		_bullet->fire(_enemy.x, _enemy.y, randAngle, 1, 1);
		_enemy.bulletCount--;
	}

}
