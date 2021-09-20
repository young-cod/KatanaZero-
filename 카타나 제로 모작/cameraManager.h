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
	void cameraRange(); //ī�޶� ��� ������ ������ �ʰ� ����� �Լ�
	void cameraRange(float a, float b); //ī�޶� ��� ������ ������ �ʰ� ����� �Լ�

	tagMouse _mouse;
public:
	HRESULT init();
	void release();

	void render(image* backBuffer, HDC frontDC);

	//ī�޶� ������ǥ�� ����
	void setCameraCenter(float x, float y)
	{
		_cameraBuffer->setCenter(x, y);
	}

	//ī�޶� left, top ��ǥ�� ����
	void setCamera(float x, float y)
	{
		_cameraBuffer->setX(x);
		_cameraBuffer->setY(y);
	}

	//ī�޶� ���Ͱ����� ������(�÷��̾ �߽����� �����̰� ������ ���)
	void updateCamera(float x, float y);

	// RECT�� X��, y������ ������� ������ �Ѿ�� ī�޶� ������( 0 < ratio < 1.0f)
	// 0�� ������ �� �� ��� ����
	void updateCamera(RECT& player, float ratioX, float ratioY);

	/*
	RECT�� ratio1 �� ratio2 ���̿��� ����� ī�޶� ������(0<ratio1<0.5f, 0.5f<ratio2<1.0f)
	ratio1�� x��->RECT.left, y��->RECT.top ����, ratio2�� x��->RECT.right, y�� ->RECT.bottom �������� ����, ��, ������, �Ʒ��� ������
	���� ������� ���� �ִٸ� 0�� ������ �� (x��, y�� �ϳ����̸� float �ΰ��� �ִ� updateCamera ��õ)
	*/
	void updateCamera(RECT& player, float ratioX1, float ratioX2, float ratioY1, float ratioY2);
	//����� �̵� ������ ����
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

