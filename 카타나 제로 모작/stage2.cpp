#include "stdafx.h"
#include "stage2.h"
#include "grab.h"
#include "fall.h"
#include "g_die.h"

stage2::stage2()
{
}

stage2::~stage2()
{
}

HRESULT stage2::init()
{
	IMAGEMANAGER->addImage("stage2", "image/stage2_bg_render.bmp", 4288, 1200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stage2C", "image/stage2_bg_collision.bmp", 4288, 1200, true, RGB(255, 0, 255));
	
	groundSet();

	_pm = new playerManager;
	_pm->init(39, 700);

	_pm->getPlayer().name = "stage2C";

	_em = new enemyManager;
	_em->init();
	_em->setBald(1220, 735);
	_em->setCop(1306, 348);
	_em->setGrunt(2373, 478);
	_em->setBald(3177, 735);
	_em->setCop(3450, 735);

	_collision = new collsion;
	_pm->_collision = _collision;
	_collision->setPlayer(_pm);
	_em->_collision = _collision;
	_collision->setEnemy(_em);

	for (int i = 0; i < _em->getVEnemy().size(); i++)
	{
		_em->getVEnemy()[i]->setPlayer(_pm);
	}

	for (int i = 0; i < STAGE2NEMOMAX; i++)
	{
		_collision->addRect(_nemo[i]);
	}

	CAMERAMANAGER->setCameraCenter(_pm->getPlayer().x, _pm->getPlayer().y);
	return S_OK;
}

void stage2::release()
{
}

void stage2::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_SHIFT))
	{
		_pm->getPlayer().slowImg = IMAGEMANAGER->findImage("stageSlow");
		_pm->getPlayer().isSlow = true;
		TIMEMANAGER->update(30);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_SHIFT))_pm->getPlayer().isSlow = false;
	mWhere.x = _ptMouse.x + CAMERAMANAGER->getCameraX();
	mWhere.y = _ptMouse.y + CAMERAMANAGER->getCameraY();

	//===================�� ����========================
	//���� �÷��̾� ���ݿ� �׾��� ��
	_collision->enemyCollision();
	//���� �ڱ� �Ѿ˿� �׾��� ��
	_collision->enemyBulletCollision();
	//==================================================

	//===================�÷��̾� ����===================
	//�÷��̾ �Ѿ�(BALD, COP)�� �׾��� ��
	if (!_pm->getPlayer().noCol)
	{
		if (_collision->playerBulletCollision() && _pm->getPlayer().state != ROLL)
		{
			_pm->setState(new g_die);
			_pm->getState()->enter(_pm);
		}
	}
	//�÷��̾ GRUNT�� �׾��� ��
	if (_collision->playerGruntCollision() && _pm->getPlayer().state != G_DIE)
	{
		cout << "?" << endl;
		_pm->setState(new g_die);
		_pm->getState()->enter(_pm);
	}
	//==================================================

	collision();
	_pm->update("stage2C");
	_em->update("stage2C");
	EFFECTMANAGER->update();
	RECT rc = _pm->getPlayer().rc;

	CAMERAMANAGER->updateCamera(_pm->getPlayer().x, _pm->getPlayer().y); //�÷��̾ �簢�� ���� ������ ������ ������

	if (_pm->getPlayer().x > 4200)
	{
		SAFE_DELETE(_pm);
		SAFE_DELETE(_em);
		SCENEMANAGER->changeScene("bossStage");
		IMAGEMANAGER->deleteImage("new");
		IMAGEMANAGER->deleteImage("re");
		IMAGEMANAGER->deleteImage("option");
		IMAGEMANAGER->deleteImage("language");
		IMAGEMANAGER->deleteImage("end");
	}

}

void stage2::render()
{
	IMAGEMANAGER->findImage("stage2")->render(getMemDC());

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		for (int i = 0; i < STAGE2NEMOMAX; i++)
		{
			Rectangle(getMemDC(), _nemo[i]);
		}
	}

	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		IMAGEMANAGER->findImage("stage2C")->render(getMemDC());
	}
	if (_pm->getPlayer().isSlow)
	{
		_pm->getPlayer().slowImg->render(getMemDC());
	}
	_pm->render();
	_em->render();

	EFFECTMANAGER->render();
}

void stage2::collision()
{
	for (int i = 0; i < STAGE2NEMOMAX; i++)
	{

		RECT temp;
		_chk = _pm->getPlayer().chk;										//�Ʒ��� ���� �߷��� �����ҽ� �߷��� 0�̵ǹǷ� �־���� ������ �Ʒ��� ������ ���� �� õ�� �浹 �Ұ���
		if (IntersectRect(&temp, &_pm->getPlayer().rc, &_nemo[i])) //&& _pm->getPlayer().state != JUMP)
		{
			int plusG = 0;

			float width = (temp.right - temp.left);
			float height = (temp.bottom - temp.top);

			//���� ����
			(width > height) ? _pt = false : _pt = true;

			if (_pt) // ���� 
			{
				//���ʿ� �ֳ�
				if (_pm->getPlayer().rc.left < _nemo[i].left)
				{
					pixelCollision(1);
					//�ȼ� �ݸ��� �� �׷� �����̸�
					if (_pm->getPlayer().state == GRAB)_pm->getPlayer().x -= width - 27;
					else _pm->getPlayer().x -= width;
				}
				//�����ʿ� �ֳ�
				if (_pm->getPlayer().rc.right > _nemo[i].right)
				{
					pixelCollision(0);
					//�ȼ� �ݸ��� �� �׷� �����̸�
					if (_pm->getPlayer().state == GRAB)_pm->getPlayer().x += width - 27;
					else _pm->getPlayer().x += width;
				}

			}
			else if (!_pt) //����
			{
				//�����Ҷ� �����̳� �����̳� ������ �����϶��� �浹 X 
				//�����Ҷ� �����̳� �����̳� ������ �����϶��� �浹 X
				//���� �ֳ�
				if (_pm->getPlayer().rc.top < _nemo[i].top)
				{

					if (_pm->getPlayer().state == JUMP || _pm->getPlayer().state == ATTACK)continue;
					if (_pm->getPlayer().state == FALL && _chk)
					{
						continue;
					}
					_pm->getPlayer().y -= height;

				}
				//�Ʒ��� �ֳ�
				if (_pm->getPlayer().rc.bottom > _nemo[i].bottom && _pm->getPlayer().state != FALL)
				{
					if (_pm->getPlayer().state == RUN)continue;
					_pm->getPlayer().y += height;
				}
			}
		}
	}
}

void stage2::pixelCollision(int direction)
{
	int probeR, probeL;
	probeL = probeR = 0;
	if (direction == 1)probeR = _pm->getPlayer().rc.right + 1;
	else probeL = _pm->getPlayer().rc.left - 1;

	int probeB = _pm->getPlayer().rc.bottom;

	COLORREF color = GetPixel(IMAGEMANAGER->findImage("stage2C")->getMemDC(),
		(direction == 1) ? probeR : probeL, _pm->getPlayer().y);

	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);

	//�� �߰�
	if ((r == 255 && g == 0 && b == 0))
	{
		if (_pm->getPlayer().state == JUMP || _pm->getPlayer().state == FALL)
		{
			_pm->setState(new grab);
			_pm->getState()->enter(_pm);
		}
	}
}

bool stage2::topPixel()
{
	_probeT = _pm->getPlayer().rc.top;

	COLORREF color = GetPixel(IMAGEMANAGER->findImage("stage2C")->getMemDC(),
		_pm->getPlayer().x, _probeT);

	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);

	//������ �� �ִ� ���� �߰�
	if ((r == 0 && g == 0 && b == 0))
	{
		return true;
	}
	return false;
}

void stage2::mousePixel()
{
	COLORREF color = GetPixel(IMAGEMANAGER->findImage("stage2C")->getMemDC(),
		mWhere.x, mWhere.y);

	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);

}

void stage2::groundSet()
{
	_nemo[0] = RectMake(0, 775, 4288, 200);
	_nemo[1] = RectMake(0, 390, 670, 255);
	_nemo[2] = RectMake(0, 260, 575, 130);
	_nemo[3] = RectMake(670, 390, 900, 10);
	_nemo[4] = RectMake(800, 390, 320, 255);
	_nemo[5] = RectMake(1120, 390, 320, 60);
	_nemo[6] = RectMake(575, 200, 995, 60);
	_nemo[7] = RectMake(1570, 200, 220, 445);
	_nemo[8] = RectMake(1790, 515, 95, 65);
	_nemo[9] = RectMake(1790, 515, 1955, 25);
	_nemo[10] = RectMake(1790, 300, 1955, 25);
	_nemo[11] = RectMake(2594, 325, 61, 63);
	_nemo[12] = RectMake(3329, 325, 61, 63);
	_nemo[13] = RectMake(3130, 525, 485, 55);
	_nemo[14] = RectMake(3328, 580, 62, 65);
	_nemo[15] = RectMake(3745, 300, 543, 345);
}


