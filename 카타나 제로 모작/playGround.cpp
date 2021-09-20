#include "stdafx.h"
#include "playGround.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

playGround::playGround()
{
}


playGround::~playGround()
{
}
 
//�ʱ�ȭ�� ����� �ϼ��� ����
HRESULT playGround::init()
{
	gameNode::init(true);
	sceneSet();

	_ground = new objManager;
	_ground->init();



	//ShowCursor(false);


	return S_OK;
}

//�޸� ������ ����� �ϼ��� ����
void playGround::release()
{
	gameNode::release();

}


void playGround::update()
{
	gameNode::update();

	SCENEMANAGER->update();
	
	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		if (!CAMERAMANAGER->getSeeLine())
		{
			CAMERAMANAGER->setSeeLine(true);
		}
		else
		{
			CAMERAMANAGER->setSeeLine(false);
		}
	}

	//CAMERAMANAGER->updateCamera(_player.x, _player.y); //�÷��̾��� ������ �߽����� �����̴� ī�޶�
	//CAMERAMANAGER->updateCamera(_player.rc, 0.7, 0.3); //�÷��̾ ���� �߽��̻� ������ ������
	//CAMERAMANAGER->updateCamera(playerRC, 0.3, 0.7, 0.3, 0.7); //�÷��̾ �簢�� ���� ������ ������ ������
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	// ���� �ǵ�������
	//================���� �� ���̿� �� �׸��ô�==========================

	SCENEMANAGER->render();

	_ground->render();


	TIMEMANAGER->render(getMemDC());

	//==================================================
	//���⵵ �ǵ�������
	//this->getBackBuffer()->render(getHDC(), 0, 0);
	CAMERAMANAGER->render(this->getBackBuffer(), getHDC());
}

void playGround::sceneSet()
{
	IMAGEMANAGER->addImage("bossSlow", "image/stage5_bg_render_slow.bmp", 1344, 784, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stageSlow", "image/stage2_bg_render_slow.bmp", 4288, 1200, true, RGB(255, 0, 255));

	SCENEMANAGER->addScene("new", new title);
	SCENEMANAGER->addScene("re", new t_re);
	SCENEMANAGER->addScene("option", new t_option);
	SCENEMANAGER->addScene("language", new t_language);
	SCENEMANAGER->addScene("end", new t_end);
	SCENEMANAGER->addScene("stage2", new stage2);
	SCENEMANAGER->addScene("bossStage", new bossStage);

	SCENEMANAGER->changeScene("new");
}
