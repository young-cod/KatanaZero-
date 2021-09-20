#include "stdafx.h"
#include "collsion.h"
#include "playerManager.h" 
#include "enemyManager.h"

void collsion::addRect(RECT rc)
{
	_vRect.push_back(rc);
}


bool collsion::playerCollision()
{
	if (_player->getPlayer().chk)return false;
	for (int i = 0; i < _vRect.size(); i++)
	{
		RECT temp;//플레이어에 bJump true 면 바로 리턴 폴스
		if (IntersectRect(&temp, &_player->getPlayer().pRCB, &_vRect[i]))
		{
			float width = (temp.right - temp.left);
			float height = (temp.bottom - temp.top);

			if (width >= height)return true;

		}
	}
	return false;
}

bool collsion::enemyCollision()
{
	RECT temp;
	for (int i = 0; i < _enemy->getVEnemy().size(); i++)
	{
		tagEnemy& enemy = _enemy->getVEnemy()[i]->getEnemy();
		if (IntersectRect(&temp, &_player->getPlayer().eRC, &enemy.rc))
		{
			if (enemy.state == EBOSSDASH ||
				enemy.state == EBOSSINLAZER ||
				enemy.state == EBOSSOUTLAZER ||
				enemy.state == EBOSSOUTPATTERN ||
				enemy.state == EBOSSHIT)return false;

			if (enemy.state == EBOSSCREEP && enemy.img->getFrameX() >= enemy.img->getMaxFrameX())
			{
				enemy.cut = true;
			}
			if (enemy.state == EBOSSCREEP && enemy.img->getFrameX() != enemy.img->getMaxFrameX())
			{
				return false;
			}

			if (enemy.cut)return false;
			if (enemy.type == TALLBOSS)
			{
				if (enemy.state != EBOSSHIT)
				{
					if (enemy.x >= _player->getPlayer().x)enemy.dir = ELEFT;
					else enemy.dir = ERIGHT;
					enemy.bossHitCount--;
					return true;
				}
			}

			cout << "으악!" << endl;
			enemy.isDead = true;
			enemy.state = EDIE;
			/*EFFECTMANAGER->play("enemyBlood", _enemy->getVEnemy()[i]->getEnemy().x,
				_enemy->getVEnemy()[i]->getEnemy().y);
			EFFECTMANAGER->play("hitEnemy", _enemy->getVEnemy()[i]->getEnemy().x,
				_enemy->getVEnemy()[i]->getEnemy().y);*/
			switch (enemy.type)
			{
			case BALD:
				enemy.img = IMAGEMANAGER->findImage("baldDie");
				if (enemy.dir == ERIGHT)
				{
					enemy.img->setFrameY(0);
				}
				else enemy.img->setFrameY(1);
				break;
			case COP:
				enemy.img = IMAGEMANAGER->findImage("copDie");
				if (enemy.dir == ERIGHT)
				{
					enemy.img->setFrameY(0);
				}
				else enemy.img->setFrameY(1);
				break;
			case GRUNT:
				enemy.img = IMAGEMANAGER->findImage("gruntDie");
				if (enemy.dir == ERIGHT)
				{
					enemy.img->setFrameY(0);
				}
				else enemy.img->setFrameY(1);
				break;
			}
			EFFECTMANAGER->playEffect("blood", (enemy.dir == ELEFT) ? enemy.x + 30 : enemy.x - 30, enemy.y - 30, enemy.dir);
			EFFECTMANAGER->playEffect("hurt", (enemy.dir == ELEFT) ? enemy.x : enemy.x, enemy.y, enemy.dir);
			return true;
		}
	}
	return false;
}

bool collsion::enemyBulletCollision()
{
	for (int i = 0; i < _enemy->getVEnemy().size(); i++)
	{
		tagEnemy& enemy = _enemy->getVEnemy()[i]->getEnemy();
		if (enemy.type == GRUNT)continue;
		vector<tagBullet>& bullet = _enemy->getVEnemy()[i]->getBullet()->getVBullet();

		RECT temp;
		for (int j = 0; j < bullet.size(); j++)
		{
			if (IntersectRect(&temp, &enemy.rc, &bullet[j].rc))
			{
				enemy.isDead = true;
				enemy.state = EDIE;
				switch (enemy.type)
				{
				case BALD:
					enemy.img = IMAGEMANAGER->findImage("baldDie");
					if (enemy.dir == ERIGHT)
					{
						enemy.img->setFrameX(0);
						enemy.img->setFrameY(0);
					}
					else
					{
						enemy.img->setFrameX(enemy.img->getMaxFrameX());
						enemy.img->setFrameY(1);
					}
					break;
				case COP:
					enemy.img = IMAGEMANAGER->findImage("copDie");
					if (enemy.dir == ERIGHT)
					{
						enemy.img->setFrameX(0);
						enemy.img->setFrameY(0);
					}
					else
					{
						enemy.img->setFrameX(enemy.img->getMaxFrameX());
						enemy.img->setFrameY(1);
					}
					break;
				}
				EFFECTMANAGER->playEffect("blood", (enemy.dir == ELEFT) ? enemy.x + 30 : enemy.x - 30, enemy.y - 30, enemy.dir);
				EFFECTMANAGER->playEffect("hurt", (enemy.dir == ELEFT) ? enemy.x : enemy.x, enemy.y, enemy.dir);
				return true;
			}
		}
	}
	return false;
}

bool collsion::playerBulletCollision()
{
	for (int i = 0; i < _enemy->getVEnemy().size(); i++)
	{
		if (_enemy->getVEnemy()[i]->getEnemy().type == GRUNT)continue;
		vector<tagBullet>& bullet = _enemy->getVEnemy()[i]->getBullet()->getVBullet();

		RECT temp;
		for (int j = 0; j < bullet.size(); j++)
		{
			if (_player->getPlayer().state == ATTACK)
			{
				if (IntersectRect(&temp, &_player->getPlayer().eRC,
					&bullet[j].rc))
				{
					EFFECTMANAGER->playEffect("reflect", temp.right, temp.top, _player->getPlayer().dir);
					//bullet[j].angle = getAngle(_player->getPlayer().x, _player->getPlayer().y,
					//	bullet[j].x, bullet[j].y);
					bullet[j].angle = bullet[j].angle + PI;
					_player->getPlayer().eRC = RectMakeCenter(0, 0, 0, 0);
					return false;
				}
			}
			else
			{
				if (IntersectRect(&temp, &_player->getPlayer().rc, &bullet[j].rc))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool collsion::playerBossCollision()
{
	RECT temp;
	for (int i = 0; i < _enemy->getVEnemy().size(); i++)
	{
		tagEnemy& boss = _enemy->getVEnemy()[i]->getEnemy();
		RECT temp;//플레이어에 bJump true 면 바로 리턴 폴스
		if (boss.state == EBOSSDASH || boss.state == EBOSSENDDASH)
		{
			if (IntersectRect(&temp, &_player->getPlayer().rc, &boss.rc))
			{
				return true;
			}
		}
	}
	return false;
}

bool collsion::playerLazerCollision()
{
	RECT temp;
	for (int i = 0; i < _enemy->getVEnemy().size(); i++)
	{
		tagEnemy& boss = _enemy->getVEnemy()[i]->getEnemy();
		RECT temp;//플레이어에 bJump true 면 바로 리턴 폴스
		if (boss.state == EBOSSINLAZER)
		{
			if (IntersectRect(&temp, &_player->getPlayer().rc, &boss.lazerRC))
			{
				return true;
			}
		}
	}
	return false;
}

bool collsion::playerMineCollision()
{
	for (int i = 0; i < _enemy->getVEnemy().size(); i++)
	{
		vector<tagBullet>& bullet = _enemy->getVEnemy()[i]->getBullet()->getVBullet();

		RECT temp;
		for (int j = 0; j < bullet.size(); j++)
		{
			if (IntersectRect(&temp, &_player->getPlayer().rc, &bullet[j].rc))
			{
				return true;
			}
		}
	}
	return false;
}

bool collsion::playerGruntCollision()
{

	RECT temp;
	for (int i = 0; i < _enemy->getVEnemy().size(); i++)
	{
		if (_enemy->getVEnemy()[i]->getEnemy().type != GRUNT)continue;

		if (IntersectRect(&temp, &_player->getPlayer().rc,
			&_enemy->getVEnemy()[i]->getEnemy().rc)
			&& _enemy->getVEnemy()[i]->getEnemy().isAtk)
		{
			cout << "dfa" << endl;
			return true;
		}
	}
	return false;
}