#include "stdafx.h"
#include "enemyManager.h"
#include "bossIdle.h"

enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	imgSet();

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update(string strkey)
{
	if (strkey == "bossStageC")
	{
		inputHandle();
		_state->update(this);
	}
	for (_viNormal = _vNormal.begin(); _viNormal != _vNormal.end(); ++_viNormal)
	{
		(*_viNormal)->update(strkey);
	}
}

void enemyManager::render()
{
	for (_viNormal = _vNormal.begin(); _viNormal != _vNormal.end(); ++_viNormal)
	{
		(*_viNormal)->render();
	}
}

void enemyManager::setBald(int x, int y)
{
	enemy* normal;
	normal = new bald;
	normal->init(0, "baldIdle", PointMake(x, y), BALD);

	_vNormal.push_back(normal);
}

void enemyManager::setCop(int x, int y)
{
	enemy* normal;
	normal = new cop;
	normal->init(0, "copIdle", PointMake(x, y), COP);

	_vNormal.push_back(normal);
}

void enemyManager::setGrunt(int x, int y)
{
	enemy* normal;
	normal = new grunt;
	normal->init(0, "gruntIdle", PointMake(x, y), GRUNT, 55);

	_vNormal.push_back(normal);
}

void enemyManager::setBoss(int x, int y)
{
	enemy* tallBoss;
	tallBoss = new boss;
	tallBoss->init(1, "bossIdle", PointMake(x, y), TALLBOSS, 0);

	_vNormal.push_back(tallBoss);

	_state = new bossIdle;
	_state->enter(this);
}

void enemyManager::imgSet()
{
	//effect
	IMAGEMANAGER->addImage("findPlayer", "image/enemy/enemy_follow.bmp", 16, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bloodSwordL", "image/effect/effect_blood_remain1_L.bmp", 118, 113, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bloodSwordR", "image/effect/effect_blood_remain1_R.bmp", 118, 113, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bloodGunL", "image/effect/effect_blood_remain2_R.bmp", 120, 116, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bloodGunR", "image/effect/effect_blood_remain2_L.bmp", 120, 116, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("enemyBlood", "image/effect/effect_blood_10x2.bmp", 800, 158, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("gunSpark", "image/effect/effect_gunspark_4x2.bmp", 392, 156, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("reflect", "image/effect/effect_reflect_6x2.bmp", 883, 280, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hitEnemy", "image/effect/effect_slashhit3_6x2.bmp", 650, 217, 6, 2, true, RGB(255, 0, 255));

	//TALLBOSS
	IMAGEMANAGER->addFrameImage("bossIdle", "image/boss/boss_headhunter_idle_12x2.bmp", 528, 176, 12, 2, true, RGB(255, 0, 255));
	//boss dash
	IMAGEMANAGER->addFrameImage("bossPreDash", "image/boss/boss_predash_8x2.bmp", 912, 172, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossDash", "image/boss/boss_dash_1x2.bmp", 102, 100, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossEndDash", "image/boss/boss_dash_end_10x2.bmp", 1000, 184, 10, 2, true, RGB(255, 0, 255));
	//boss pattern in/out
	IMAGEMANAGER->addFrameImage("bossInPattern", "image/boss/boss_in_pattern_4x2.bmp", 288, 124, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossOutPattern", "image/boss/boss_out_pattern_4x2.bmp", 288, 124, 4, 2, true, RGB(255, 0, 255));
	//boss mine
	IMAGEMANAGER->addFrameImage("bossTakeOutGun", "image/boss/boss_takeoutgun_7x2.bmp", 658, 172, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossShoot", "image/boss/boss_shoot_8x2.bmp", 1088, 184, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossMine", "image/boss/boss_mine_1x2.bmp", 40, 20, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mineCircle", "image/boss/boss_circle.bmp", 274, 274, true, RGB(255, 0, 255));
	//boss lazer
	IMAGEMANAGER->addFrameImage("bossInLazer", "image/boss/boss_teleport_in_4x2.bmp", 224, 180, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossOutLazer", "image/boss/boss_teleport_out_4x2.bmp", 224, 180, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossLazer", "image/boss/boss_lazer_top_10x1.bmp", 360, 1500, 10, 1, true, RGB(255, 0, 255));
	//boss die
	IMAGEMANAGER->addFrameImage("bossHit", "image/boss/boss_headhunter_hurt_recover_10x2.bmp", 1400, 212, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossDie", "image/boss/boss_dieground_8x2.bmp", 928, 164, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossCreep", "image/boss/boss_dead_19x2.bmp", 2128, 84, 19, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossNoHead", "image/boss/boss_nohead_6x2.bmp", 720, 88, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossFHead", "image/boss/boss_headfly_8x2.bmp", 320, 84, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossGHead", "image/boss/boss_headground_8x2.bmp", 720, 56, 8, 2, true, RGB(255, 0, 255));

	//bald
	IMAGEMANAGER->addFrameImage("baldIdle", "image/enemy/enemy_bold_Idle_8x2.bmp", 576, 140, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("baldWalk", "image/enemy/enemy_bold_Walk_8x2.bmp", 544, 152, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("baldRun", "image/enemy/enemy_bold_run_10x2.bmp", 900, 156, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("baldDie", "image/enemy/enemy_bold_hurt_14x2.bmp", 1036, 128, 14, 2, true, RGB(255, 0, 255));

	//bald attack zip
	//¸öÅë
	IMAGEMANAGER->addImage("baldBodyL", "image/enemy/enemy_bold_aim_L.bmp", 42, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("baldBodyR", "image/enemy/enemy_bold_aim_R.bmp", 42, 70, true, RGB(255, 0, 255));
	//ÃÑ
	IMAGEMANAGER->addImage("baldGunL", "image/enemy/enemy_bold_gun_L.bmp", 54, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("baldGunR", "image/enemy/enemy_bold_gun_R.bmp", 54, 12, true, RGB(255, 0, 255));
	//¿ŞÂÊ ¹Ù¶óº¼ ¶§ ÆÈ
	IMAGEMANAGER->addImage("baldArmLL", "image/enemy/enemy_bold_leftarm_L.bmp", 28, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("baldArmRL", "image/enemy/enemy_bold_rightarm_L.bmp", 30, 18, true, RGB(255, 0, 255));
	//¿À¸¥ÂÊ ¹Ù¶óº¼ ¶§ ÆÈ
	IMAGEMANAGER->addImage("baldArmLR", "image/enemy/enemy_bold_leftarm_R.bmp", 28, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("baldArmRR", "image/enemy/enemy_bold_rightarm_R.bmp", 30, 18, true, RGB(255, 0, 255));
	//==============================================================================================================================
	//cop
	IMAGEMANAGER->addFrameImage("copIdle", "image/enemy/enemy_cop_idle_8x2.bmp", 576, 148, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("copWalk", "image/enemy/enemy_cop_walk_8x2.bmp", 432, 152, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("copRun", "image/enemy/enemy_cop_run_10x2.bmp", 900, 160, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("copDie", "image/enemy/enemy_cop_hurt_14x2.bmp", 1148, 136, 14, 2, true, RGB(255, 0, 255));

	//cop attack zip
	//¸öÅë
	IMAGEMANAGER->addImage("copBodyL", "image/enemy/enemy_cop_aim_L.bmp", 46, 72, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("copBodyR", "image/enemy/enemy_cop_aim_R.bmp", 46, 72, true, RGB(255, 0, 255));
	//ÃÑ
	IMAGEMANAGER->addImage("copGunL", "image/enemy/enemy_cop_gun_L.bmp", 54, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("copGunR", "image/enemy/enemy_cop_gun_R.bmp", 54, 12, true, RGB(255, 0, 255));
	//¿ŞÂÊ ¹Ù¶óº¼ ¶§ ÆÈ
	IMAGEMANAGER->addImage("copArmLL", "image/enemy/enemy_cop_leftarm_L.bmp", 28, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("copArmRL", "image/enemy/enemy_cop_rightarm_L.bmp", 30, 18, true, RGB(255, 0, 255));
	//¿À¸¥ÂÊ ¹Ù¶óº¼ ¶§ ÆÈ
	IMAGEMANAGER->addImage("copArmLR", "image/enemy/enemy_cop_leftarm_R.bmp", 28, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("copArmRR", "image/enemy/enemy_cop_rightarm_R.bmp", 30, 18, true, RGB(255, 0, 255));
	//==============================================================================================================================
	//grunt
	IMAGEMANAGER->addFrameImage("gruntIdle", "image/enemy/enemy_grunt_idle_8x2.bmp", 480, 144, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("gruntWalk", "image/enemy/enemy_grunt_walk_10x2.bmp", 640, 160, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("gruntRun", "image/enemy/enemy_grunt_run_10x2.bmp", 720, 156, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("gruntAttack", "image/enemy/enemy_grunt_attack_7x2.bmp", 616, 168, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("gruntDie", "image/enemy/enemy_grunt_hurt_15x2.bmp", 1680, 164, 15, 2, true, RGB(255, 0, 255));

	EFFECTMANAGER->AddEffect("blood", IMAGEMANAGER->findImage("enemyBlood"), 1);
	EFFECTMANAGER->AddEffect("hurt", IMAGEMANAGER->findImage("hitEnemy"),3);
	EFFECTMANAGER->AddEffect("reflect", IMAGEMANAGER->findImage("reflect"), 3);
	EFFECTMANAGER->AddEffect("gunSpark", IMAGEMANAGER->findImage("gunSpark"), 4);
}

void enemyManager::inputHandle()
{
	bossStateManager* newState = _state->inputHandle(this);

	if (newState != nullptr)
	{
		SAFE_DELETE(_state);
		_state = newState;
		_state->enter(this);
	}
}

