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
	image* img;							//�÷��̾� �̹���
	image* eImg;						//���� �̹���
	image* slowImg;						//���ο� �̹���
	image* shadow[4];
	RECT rc;							//��Ʈ
	RECT pRCL, pRCR, pRCT, pRCB;		//Ž�� ��Ʈ
	RECT eRC;							//���� ��Ʈ
	float proL,proR,proT,proB;			//Ž�� ����
	int alpha;							//����
	bool atkCount;						//���� �� �� �ִ� Ƚ��
	float x, y;							//��ǥ
	float speed;						//���ǵ�
	float jumpPower;					//������
	float gravity;						//�߷�
	float angle;						//����
	float acc;							//���ӵ�
	bool chk;							//���� üũ
	bool isRoll;						//������
	bool isJump;						//�����߳�
	bool isGrab;						//����ҳ�
	bool isFlip;						//���߿��� �� �߳�
	bool isAtk;							//�����߳�
	bool bJump;							//�Ʒ� �����ϸ� Ʈ�� //�ƴϸ� ���� ����
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