#pragma once
#include "gameNode.h"
#include "bullet.h"

class playerManager;

enum TYPEENEMY
{
	BALD,
	COP,
	GRUNT,
	TALLBOSS
};

enum EDIRECTION
{
	ELEFT,
	ERIGHT
};

enum ESTATE
{
	EIDLE,
	EWALK,
	ERUN,
	EATTACK,
	EBOSSPREDASH,
	EBOSSDASH,
	EBOSSENDDASH,
	EBOSSINPATTERN,
	EBOSSOUTPATTERN,
	EBOSSSHOOT,
	EBOSSTAKEOUTGUN,
	EBOSSINLAZER,
	EBOSSOUTLAZER,
	EBOSSHIT,
	EBOSSCREEP,
	EBOSSNOHEAD,
	EDIE
};



struct tagEnemy
{
	TYPEENEMY type;					//적 종류
	image* img;						//이미지
	RECT rc;						//렉트
	float x, y;						//좌표

	image* eImg;					//발사 이미지
	
	image* lazer;					//레이저 이미지
	RECT lazerRC;					//레이저 렉ㅌ
	float lazerX, lazerY;			//레이저 좌표
	
	image* head;					//머리
	RECT headRC;
	float headX, headY;
	float headJP;					//머리 점프력?
	float headGT;					//머리 중력
	float headBT;					//머리 아래

	RECT detectRC;					//감지 렉트
	float speed;					//스피드
	float gravity;
	float probeB, probeL, probeR;	//탐사범위
	float distance;
	bool isAtk;						//공격할까
	bool findP;						//플레이어 발견
	bool isDead;
	bool stop;
	bool cut;
	int currentFrameX;				//프레임 번호
	int currentFrameY;
	int timer;						//타이머
	int atkTimer;					//공격주기(랜덤)
	int moveRand;					//상태 랜덤
	int dirRand;					//방향 랜덤
	int bulletCount;
	int beforeState;
	int LazerCount;
	int bossHitCount;
	EDIRECTION dir;					//방향
	ESTATE state;					//상태
};

class enemy : public gameNode
{
protected:
	tagEnemy _enemy;

	int _count;			//프레임렌더 변수
	int _fireCount;		//총알 발사 카운트
	int _index;			//프레임 번호

	RECT dRC;
	RECT drcChk;

	playerManager* _player;

	bullet* _bullet;

	bool _patternGo; //제일 처음 패턴 시작하게 해준다


public:
	enemy();
	~enemy();


	virtual HRESULT init();
	virtual HRESULT init(bool enemyType, const char* imageName, POINT position, TYPEENEMY type, float distance =350.0f);
	virtual void release();
	virtual	void update(string strkey);
	virtual	void render();

	void move();
	void draw();

	//============Normal AI ==================
	void direction(int rand);
	void walk(int rand);
	void idle(int rand);
	void run();
	void attack();

	bool detectPlayer();

	void frame();
	void state(EDIRECTION dir, ESTATE state, int y);
	//========================================

	//============Boss AI ==================
	void effectFrame();
	
	void bossDirection(int rand);
	void bossWalk(int rand);
	void bossIdle(int rand);
	void bossRun();
	void bossAttack();

	void bossFire();

	bool bossDetectPlayer();

	void bossFrame();
	void bossState(EDIRECTION dir, ESTATE bossState, int y);
	//========================================


	inline RECT getRect() { return _enemy.rc; }

	tagEnemy& getEnemy() { return _enemy; }
	bullet* getBullet() { return _bullet; }

	void pixelCollision(string strkey);

	void setPlayer(playerManager* player) { _player = player; }


};

