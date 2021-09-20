#include "stdafx.h"
#include "bossStage.h"
#include "fall.h"
#include "grab.h"
#include "g_die.h"
#include "bossHit.h"

bossStage::bossStage()
{
}

bossStage::~bossStage()
{
}

HRESULT bossStage::init()
{
	IMAGEMANAGER->addImage("bossStage", "image/stage5_bg_render.bmp", 1344, 784, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossStageC", "image/stage5_bg_collision.bmp", 1344, 784, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gameOver", "image/effect/effect_fail.bmp", 1280, 720, true, RGB(255, 0, 255));

	_pm = new playerManager;
	_pm->init(300, WINSIZEY / 2);

	_pm->getPlayer().name = "bossStageC";

	_em = new enemyManager;
	_em->init();
	_em->setBoss(1080, 532);

	_em->getBSM()->setPlayer(_pm);
	groundSet();

	_collision = new collsion;
	_pm->_collision = _collision;
	_collision->setPlayer(_pm);
	_em->_collision = _collision;
	_collision->setEnemy(_em);

	for (int i = 0; i < _em->getVEnemy().size(); i++)
	{
		_em->getVEnemy()[i]->setPlayer(_pm);
	}

	for (int i = 0; i < BOSSNEMOMAX; i++)
	{
		_collision->addRect(_nemo[i]);
	}

	CAMERAMANAGER->setCameraCenter(WINSIZEX / 2, WINSIZEY / 2);
	return S_OK;
}

void bossStage::release()
{
}

void bossStage::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_SHIFT))
	{
		_pm->getPlayer().slowImg = IMAGEMANAGER->findImage("bossSlow");
		_pm->getPlayer().isSlow = true;
		TIMEMANAGER->update(30);
	}
	if (KEYMANAGER->isOnceKeyUp(VK_SHIFT))_pm->getPlayer().isSlow = false;

	//�ٽ� ����
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && _pm->getPlayer().state == G_DIE)this->init();
	collision();
	_pm->update("bossStageC");
	_em->update("bossStageC");

	//===================�� ����========================
	//���� �÷��̾� ���ݿ� �¾��� ��
	if (_collision->enemyCollision())
	{
		_em->setState(new bossHit);
		_em->getBSM()->enter(_em);
	}
	//==================================================

	////===================�÷��̾� ����===================
	//if (_pm->getPlayer().state != ROLL && _pm->getPlayer().state != G_DIE)
	//{
	//	//�뽬 ���ݿ� �״� ��
	//	if (_collision->playerBossCollision())
	//	{
	//		_pm->setState(new g_die);
	//		_pm->getState()->enter(_pm);
	//	}
	//	//������ ���ݿ� �״°�
	//	if (_collision->playerLazerCollision())
	//	{
	//		_pm->setState(new g_die);
	//		_pm->getState()->enter(_pm);
	//	}
	//	//���� ���ݿ� �״°�
	//	if (_collision->playerMineCollision())
	//	{
	//		_pm->setState(new g_die);
	//		_pm->getState()->enter(_pm);
	//	}
	//}


	RECT rc = _pm->getPlayer().rc;
	CAMERAMANAGER->updateCamera(rc, 0.3, 0.7, 0.3, 0.7, 1260, 720);
}

void bossStage::render()
{
	IMAGEMANAGER->findImage("bossStage")->render(getMemDC());
	if (_pm->getPlayer().isSlow)
	{
		_pm->getPlayer().slowImg->render(getMemDC());
	}
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < BOSSNEMOMAX; i++)
		{
			Rectangle(getMemDC(), _nemo[i]);
		}
	}

	if (_pm->getPlayer().state == G_DIE)
	{
		IMAGEMANAGER->findImage("bossSlow")->render(getMemDC());
	}

	_pm->render();
	_em->render();

	if (_pm->getPlayer().state == G_DIE)
	{
		IMAGEMANAGER->findImage("gameOver")->render(getMemDC());
	}
}

void bossStage::collision()
{
	for (int i = 0; i < BOSSNEMOMAX; i++)
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

void bossStage::pixelCollision(int direction)
{
	int probeR, probeL;
	probeL = probeR = 0;
	if (direction == 1)probeR = _pm->getPlayer().rc.right + 1;
	else probeL = _pm->getPlayer().rc.left - 1;

	int probeB = _pm->getPlayer().rc.bottom;

	COLORREF color = GetPixel(IMAGEMANAGER->findImage("bossStageC")->getMemDC(),
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

void bossStage::groundSet()
{
	_nemo[0] = RectMake(0, 33, 160, 575);
	_nemo[1] = RectMake(1185, 33, 160, 575);
	_nemo[2] = RectMake(0, 575, 1400, 800);
}
