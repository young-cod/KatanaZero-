#pragma once
#include "singletonBase.h"
#define EFFECT_MAX 5
class effectManager : public singletonBase<effectManager>
{
private:
	typedef enum enumEffect {
		BLOOD,
		HURT,
		DUST,
		REFLECT,
		GUNSPARK
	};
	typedef struct tagEffectInfo {
		int x, y;
		int currentFrameX;
		int currentFrameY;
		int isActive;
		int count;
		int term;
		int maxFrameX;
		enumEffect type;
	}EFFECTINFO;
private:
	map<string, image*> _effectMap;
	map<string, image*>::iterator _effectMapIter;

	map<string, vector<EFFECTINFO>> _effectInfoMap;
	map<string, vector<EFFECTINFO>>::iterator _effectInfoMapIter;
public:
	effectManager() {};
	~effectManager() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void AddEffect(string effectName, image* newEffect, int term);
	void playEffect(string effectName, int x, int y, bool dir);
};