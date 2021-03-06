#pragma once
#include "singletonBase.h"
#include "image.h"

struct tagMouse
{
	image* img;
	RECT rc;
	float x, y;
};

class cameraManager : public singletonBase<cameraManager>
{
private:
	image* _cameraBuffer;
	bool _seeLine;
	float x[2];
	float y[2];
	void cameraRange(); //카메라가 배경 밖으로 나가지 않게 만드는 함수
	void cameraRange(float a, float b); //카메라가 배경 밖으로 나가지 않게 만드는 함수

	tagMouse _mouse;
public:
	HRESULT init();
	void release();

	void render(image* backBuffer, HDC frontDC);

	//카메라를 중점좌표로 설정
	void setCameraCenter(float x, float y)
	{
		_cameraBuffer->setCenter(x, y);
	}

	//카메라를 left, top 좌표로 설정
	void setCamera(float x, float y)
	{
		_cameraBuffer->setX(x);
		_cameraBuffer->setY(y);
	}

	//카메라 센터값으로 움직임(플레이어를 중심으로 움직이고 싶으면 사용)
	void updateCamera(float x, float y);

	// RECT가 X축, y축으로 어느정도 비율을 넘어가면 카메라가 움직임( 0 < ratio < 1.0f)
	// 0을 넣으면 그 축 사용 안함
	void updateCamera(RECT& player, float ratioX, float ratioY);

	/*
	RECT가 ratio1 과 ratio2 사이에서 벗어나면 카메라를 움직임(0<ratio1<0.5f, 0.5f<ratio2<1.0f)
	ratio1은 x축->RECT.left, y축->RECT.top 기준, ratio2는 x축->RECT.right, y축 ->RECT.bottom 기준으로 왼쪽, 위, 오른쪽, 아래로 움직임
	만약 빼고싶은 것이 있다면 0을 넣으면 됨 (x축, y축 하나씩이면 float 두개만 넣는 updateCamera 추천)
	*/
	void updateCamera(RECT& player, float ratioX1, float ratioX2, float ratioY1, float ratioY2);
	//백버퍼 이동 사이즈 조정
	void updateCamera(RECT& player, float ratioX1, float ratioX2, float ratioY1, float ratioY2,float sizeX, float sizeY);

	void setSeeLine(bool b) { _seeLine = b; }
	bool getSeeLine() { return _seeLine; }

	/*
	void setCameraX(float x) { _cameraBuffer->setX(x); }
	void setCameraY(float y) { _cameraBuffer->setY(y); }
	*/

	float getCameraX() { return _cameraBuffer->getX(); }
	float getCameraY() { return _cameraBuffer->getY(); }

	float getCameraCenterX() { return _cameraBuffer->getCenterX(); }
	float getCameraCenterY() { return _cameraBuffer->getCenterY(); }
	
};

