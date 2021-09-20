#include "stdafx.h"
#include "playerManager.h"
#include "idle.h"

playerManager::playerManager()
{
}

playerManager::~playerManager()
{
}

HRESULT playerManager::init(float x, float y)
{

	imgSet();
	playerSet(x, y);
	for (int i = 0; i < 4; i++) {
		_player.shadow[i] = new image();
		_player.shadow[i]->init(_player.img->getFrameWidth(), _player.img->getFrameHeight(), true);
	}
	return S_OK;
}

void playerManager::release()
{
}

void playerManager::update(string strKey)
{
	inputHandle();
	
	_player.rc = RectMakeCenter(_player.x, _player.y,
		_player.img->getFrameWidth(), _player.img->getFrameHeight());
	
	pixelCollision(strKey);
	
	_state->update(this);
	if (_player.rc.top < 0)_player.rc = RectMakeCenterX(_player.x, 0, _player.img->getFrameWidth(), _player.img->getFrameHeight());


	_player.pRCL = RectMakeCenter(_player.rc.left, _player.y, 5, 5);

	_player.pRCR = RectMakeCenter(_player.rc.right, _player.y, 5, 5);


	_player.pRCT = RectMakeCenter(_player.x, _player.rc.top, 5, 5);
	_player.pRCB = RectMakeCenter(_player.x, _player.rc.bottom, 5, 5);
	_player.proB = _player.rc.bottom;

	// 마우스 절대 좌표를 상대 좌표롤 바꿔준다
	mX = _ptMouse.x + CAMERAMANAGER->getCameraX();  //camera leftw
	mY = _ptMouse.y + CAMERAMANAGER->getCameraY();	//camer right

}

void playerManager::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _player.rc);
		Rectangle(getMemDC(), _player.eRC);
	}

	if(_player.isAtk && _player.dir == RIGHT)_player.eImg->frameRender(getMemDC(),
		_player.rc.left, _player.rc.top);
	if(_player.isAtk && _player.dir == LEFT)_player.eImg->frameRender(getMemDC(),
		_player.rc.left - 90, _player.rc.top);
	
	_player.img->frameRender(getMemDC(), _player.rc.left, _player.rc.top);

	Rectangle(getMemDC(), _player.pRCL);
	Rectangle(getMemDC(), _player.pRCR);
	Rectangle(getMemDC(), _player.pRCT);
	Rectangle(getMemDC(), _player.pRCB);

	//IMAGEMANAGER->findImage("stage1C")->render(getMemDC());

}

//이미지 셋
void playerManager::imgSet()
{
	IMAGEMANAGER->addFrameImage("idle", "image/player/player_idle_11x2.bmp", 0, 0, 770, 140, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("run", "image/player/player_run_10x2.bmp", 880, 128, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("jump", "image/player/player_jump_4x2.bmp", 240, 168, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("fall", "image/player/player_fall_4x2.bmp", 328, 192, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("roll", "image/player/player_roll_7x2.bmp", 658, 128, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("flip", "image/player/player_flip_11x2.bmp", 1056, 176, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("attack", "image/player/player_attack_7x2.bmp", 840, 164, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("grab", "image/player/player_grab_wall_1x2.bmp", 76, 152, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("g_die", "image/player/player_hurtground_6x2.bmp", 684, 92, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("j_die", "image/player/player_hurtfly_4x2.bmp", 400, 132, 4, 2, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addFrameImage("attack_effect", "image/player/player_slash_basic_6x2.bmp", 1260, 120, 6, 2, true, RGB(255, 0, 255));
}
//플레이어 셋
void playerManager::playerSet(float x, float y)
{

	_player.dir = RIGHT;
	_state = new idle();
	_state->enter(this);
	_player.x = x;
	_player.y = y;

	_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
	_player.proL = _player.rc.left;
	_player.proR = _player.rc.right;
	_player.proT = _player.rc.top;
	_player.proB = _player.rc.bottom;
	_player.jumpPower = 100.0f;
	_player.speed = 5.0f;

	_player.alpha = 255;
}

//계단 충돌
void playerManager::pixelCollision(string strKey)
{
	//아래
	for (int i = _player.proB - 20; i < _player.proB + 10; ++i)
	{

		COLORREF color = GetPixel(IMAGEMANAGER->findImage(strKey)->getMemDC(), _player.x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		
		if ((r == 50 && g == 56 && b == 71))
		{
			//if (_player.state == JUMP)continue;
			_player.y = i - _player.img->getFrameHeight() / 2;
			break;
		}
	}
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.img->getFrameWidth(), _player.img->getFrameHeight());
}


void playerManager::gravity()
{
	_player.y -= _player.gravity;
	_player.gravity -= TIMEMANAGER->getElapsedTime() * 15;
}

void playerManager::inputHandle()
{
	stateManager* newState = _state->inputHandle(this);

	if (newState != nullptr)
	{
		SAFE_DELETE(_state);
		_state = newState;
		_state->enter(this);
	}
}