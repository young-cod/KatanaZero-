#pragma once
#include "singletonBase.h"
#include "image.h"
#include <map>

class imageManager : public singletonBase<imageManager>
{
private:
	//first - string
	//second - image*
	typedef map<string, image*>				mapImageList;
	typedef map<string, image*>::iterator	mapImageIter;

private:
	mapImageList _mImageList;

public:
	imageManager();
	~imageManager();

	HRESULT init();
	void release();

	image* addImage(string strKey, int width, int height, bool isAlpha = FALSE);
	image* addImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor, bool isAlpha = FALSE);

	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor, bool isAlpha = FALSE);
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor, bool isAlpha = FALSE);

	image* findImage(string strKey);

	BOOL deleteImage(string strKey);

	BOOL deleteAll();

	//void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

};