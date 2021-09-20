#include "stdafx.h"
#include "effectManager.h"

HRESULT effectManager::init()
{
	return E_NOTIMPL;
}

void effectManager::release()
{
}

void effectManager::update()
{
	for (_effectMapIter = _effectMap.begin(); _effectMapIter != _effectMap.end(); _effectMapIter++) {
		string effectName = _effectMapIter->first;
		image* curEffect = _effectMapIter->second;
		_effectInfoMapIter = _effectInfoMap.find(effectName);
		for (int i = 0; i < _effectInfoMapIter->second.size(); i++) {
			if (_effectInfoMapIter->second[i].isActive == false) continue;
			_effectInfoMapIter->second[i].count++;
			if (_effectInfoMapIter->second[i].count == _effectInfoMapIter->second[i].term) {
				if (_effectInfoMapIter->second[i].currentFrameY == 0) {
					_effectInfoMapIter->second[i].currentFrameX++;
					if (_effectInfoMapIter->second[i].currentFrameX == curEffect->getMaxFrameX()) {
						_effectInfoMapIter->second[i].isActive = false;
					}
				}
				else {
					_effectInfoMapIter->second[i].currentFrameX--;
					if (_effectInfoMapIter->second[i].currentFrameX == -1) {
						_effectInfoMapIter->second[i].isActive = false;
					}
				}
				_effectInfoMapIter->second[i].count = 0;
			}
		}
	}
}

void effectManager::render()
{
	for (_effectMapIter = _effectMap.begin(); _effectMapIter != _effectMap.end(); _effectMapIter++) {
		string effectName = _effectMapIter->first;
		image* curEffect = _effectMapIter->second;
		_effectInfoMapIter = _effectInfoMap.find(effectName);
		for (int i = 0; i < _effectInfoMapIter->second.size(); i++) {
			if (_effectInfoMapIter->second[i].isActive == false) continue;
			curEffect->frameRender(_backBuffer->getMemDC(),
				_effectInfoMapIter->second[i].x, _effectInfoMapIter->second[i].y,
				_effectInfoMapIter->second[i].currentFrameX, _effectInfoMapIter->second[i].currentFrameY);
		}
	}
}

void effectManager::AddEffect(string effectName, image* newEffect, int term)
{
	_effectMap.insert(pair<string, image*>(effectName, newEffect));
	vector<EFFECTINFO> newEffectInfo;
	for (int i = 0; i < EFFECT_MAX; i++) {
		newEffectInfo.push_back(EFFECTINFO());
		newEffectInfo[i].maxFrameX = newEffect->getMaxFrameX();
		newEffectInfo[i].term = term;
		newEffectInfo[i].x = 0;
		newEffectInfo[i].y = 0;
		newEffectInfo[i].currentFrameX = 0;
		newEffectInfo[i].currentFrameY = 0;
		newEffectInfo[i].isActive = false;
		newEffectInfo[i].count = 0;
	}
	_effectInfoMap.insert(pair<string, vector<EFFECTINFO>>(effectName, newEffectInfo));
}

void effectManager::playEffect(string effectName, int x, int y, bool dir)
{
	_effectMapIter = _effectMap.find(effectName);

	if (_effectMapIter != _effectMap.end()) {
		_effectInfoMapIter = _effectInfoMap.find(effectName);
		image* curEffect = _effectMapIter->second;
		for (int i = 0; i < _effectInfoMapIter->second.size(); i++) {
			if (_effectInfoMapIter->second[i].isActive == true) continue;
			_effectInfoMapIter->second[i].x = x - curEffect->getFrameWidth() / 2;
			_effectInfoMapIter->second[i].y = y - curEffect->getFrameHeight() / 2;
			_effectInfoMapIter->second[i].isActive = true;
			if (dir == false) {
				_effectInfoMapIter->second[i].currentFrameY = 0;
				_effectInfoMapIter->second[i].currentFrameX = 0;
			}
			else {
				_effectInfoMapIter->second[i].currentFrameY = 1;
				_effectInfoMapIter->second[i].currentFrameX = _effectMapIter->second->getMaxFrameX();
			}
			_effectInfoMapIter->second[i].count = 0;
			break;
		}
	}
}
