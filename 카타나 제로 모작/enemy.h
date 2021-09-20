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
	TYPEENEMY type;					//�� ����
	image* img;						//�̹���
	RECT rc;						//��Ʈ
	float x, y;						//��ǥ

	image* eImg;					//�߻� �̹���
	
	image* lazer;					//������ �̹���
	RECT lazerRC;					//������ ����
	float lazerX, lazerY;			//������ ��ǥ
	
	image* head;					//�Ӹ�
	RECT headRC;
	float headX, headY;
	float headJP;					//�Ӹ� ������?
	float headGT;					//�Ӹ� �߷�
	float headBT;					//�Ӹ� �Ʒ�

	RECT detectRC;					//���� ��Ʈ
	float speed;					//���ǵ�
	float gravity;
	float probeB, probeL, probeR;	//Ž�����
	float distance;
	bool isAtk;						//�����ұ�
	bool findP;						//�÷��̾� �߰�
	bool isDead;
	bool stop;
	bool cut;
	int currentFrameX;				//������ ��ȣ
	int currentFrameY;
	int timer;						//Ÿ�̸�
	int atkTimer;					//�����ֱ�(����)
	int moveRand;					//���� ����
	int dirRand;					//���� ����
	int bulletCount;
	int beforeState;
	int LazerCount;
	int bossHitCount;
	EDIRECTION dir;					//����
	ESTATE state;					//����
};

class enemy : public gameNode
{
protected:
	tagEnemy _enemy;

	int _count;			//�����ӷ��� ����
	int _fireCount;		//�Ѿ� �߻� ī��Ʈ
	int _index;			//������ ��ȣ

	RECT dRC;
	RECT drcChk;

	playerManager* _player;

	bullet* _bullet;

	bool _patternGo; //���� ó�� ���� �����ϰ� ���ش�


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

