#include "stdafx.h"
#include "playGround.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

playGround::playGround()
{
}


playGround::~playGround()
{
}
 
//초기화는 여기다 하세요 제발
HRESULT playGround::init()
{
	gameNode::init(true);
	sceneSet();

	_ground = new objManager;
	_ground->init();



	//ShowCursor(false);


	return S_OK;
}

//메모리 해제는 여기다 하세요 제발
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

	//CAMERAMANAGER->updateCamera(_player.x, _player.y); //플레이어의 중점을 중심으로 움직이는 카메라
	//CAMERAMANAGER->updateCamera(_player.rc, 0.7, 0.3); //플레이어가 일정 중심이상 나가면 움직임
	//CAMERAMANAGER->updateCamera(playerRC, 0.3, 0.7, 0.3, 0.7); //플레이어가 사각형 범위 밖으로 나가면 움직임
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	// 위에 건들지마라
	//================제발 이 사이에 좀 그립시다==========================

	SCENEMANAGER->render();

	_ground->render();


	TIMEMANAGER->render(getMemDC());

	//==================================================
	//여기도 건들지마라
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
