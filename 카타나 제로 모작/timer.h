#pragma once
class timer
{
private:
	float		_timeScale;				//시간 경과량
	float		_timeElapsed;			//틱 시간
	__int64		_curTime;				//현재 시간
	__int64		_lastTime;				//마지막 시간
	__int64		_periodFrequency;		//주기

	unsigned long _frameRate;			//프레임 량
	unsigned long _FPSframeCount;		//프레임 스키핑
	float _FPSTimeElapsed;				//한 프레임 당 경과량
	float _worldTime;					//작동 시간 총량

public:
	timer();
	~timer();

	HRESULT init();
	void tick(float lockFPS = 0.0f);
	unsigned long getFrameRate(char* str = NULL) const;
	inline float getElapsedTime() const { return _timeElapsed; }
	inline float getWorldTime() const { return _worldTime; }
};

