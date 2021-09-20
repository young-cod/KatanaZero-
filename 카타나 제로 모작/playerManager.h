#pragma once
#include "gameNode.h"
#include "stateManager.h"
#include "idle.h"
#include "collsion.h"

enum DIRECTION
{
	LEFT,
	RIGHT
};

enum PLAYERSTATE
{
	IDLE,
	RUN,
	JUMP,
	FALL,
	ROLL,
	ATTACK,
	GRAB,
	G_DIE,
	J_DIE,
	FLIP
};

struct tagPlayer
{
	image* img;							//플레이어 이미지
	image* eImg;						//공격 이미지
	image* slowImg;						//슬로우 이미지
	image* shadow[4];
	RECT rc;							//렉트
	RECT pRCL, pRCR, pRCT, pRCB;		//탐사 렉트
	RECT eRC;							//공격 렉트
	float proL,proR,proT,proB;			//탐사 범위
	int alpha;							//알파
	bool atkCount;						//공격 할 수 있는 횟수
	float x, y;							//좌표
	float speed;						//스피드
	float jumpPower;					//점프력
	float gravity;						//중력
	float angle;						//각도
	float acc;							//가속도
	bool chk;							//발판 체크
	bool isRoll;						//굴렀나
	bool isJump;						//점프했나
	bool isGrab;						//벽잡았나
	bool isFlip;						//공중에서 턴 했나
	bool isAtk;							//공격했나
	bool bJump;							//아래 점프하면 트루 //아니면 폴스 아하
	bool isSlow;
	bool noCol;
	PLAYERSTATE state;
	DIRECTION dir;
	string name;
	string stage;
};


class playerManager : public gameNode
{
private:
	tagPlayer _player;

	int _count, _index;
	float _y;

	image* _mouse;
	float mX, mY;

	int _rectMax;

	stateManager* _state;
public:
	playerManager();
	~playerManager();

	collsion* _collision;

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update(string strKey);
	virtual void render();

	void imgSet();
	void playerSet(float x,float y);
	void pixelCollision(string strKey);
	void gravity();

	void inputHandle();

	PLAYERSTATE& getPlayerState() { return _player.state; }
	tagPlayer& getPlayer() { return _player; }
	stateManager* getState() { return _state; }
	void setState(stateManager* state) {_state = state;}
};	