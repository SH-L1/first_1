#include "framework.h"
#include "DungreedScene.h"

#include "Objects/Dungreed/DunPlayer.h"
#include "Objects/Dungreed/DunMonster.h"
#include "Objects/Dungreed/DunBow.h"
#include "Objects/Dungreed/DunBullet.h"

DungreedScene::DungreedScene()
{
	_player = make_shared<DunPlayer>(L"Resource/Player.png");
	_monster = make_shared<DunMonster>(L"Resource/monster.png");
	_bow = make_shared<DunBow>(L"Resource/Bow.png");

	for (int i = 0;i < _bulletNum;i++)
	{
		shared_ptr<DunBullet> _bullet = make_shared<DunBullet>(L"Resource/Bullet.png");
		_bullet->GetTransform()->SetScale(Vector(0.1f, 0.1f));
		_bullets.push_back(_bullet);
	}

	_muzzle = make_shared<Transform>();

	_player->GetTransform()->SetPos(CENTRE);
	_player->GetTransform()->SetScale(Vector(0.1f, 0.1f));

	_monster->SetActive(true);
	_monster->GetTransform()->SetPos(Vector(CENTRE.x, WIN_HEIGHT));
	_monster->GetTransform()->SetScale(Vector(0.2f, 0.2f));

	_bow->GetTransform()->SetParent(_player->GetTransform());
	_bow->GetTransform()->SetPos(Vector(100, -50));
	_bow->GetTransform()->SetScale(Vector(5.0f, 5.0f));

	_muzzle->SetParent(_bow->GetTransform());
	_muzzle->SetPos(Vector(100, 0));
}

DungreedScene::~DungreedScene()
{
}

void DungreedScene::PreUpdate()
{
	if (_player->IsDead() || _monster->IsDead()) return;

	_player->PreUpdate();
	
	for (int i = 0; i < _bulletNum; i++)
	{
		_bullets[i]->PreUpdate();
	}

	_monster->PreUpdate();
}

void DungreedScene::Update()
{
	if (_player->IsDead() || _monster->IsDead()) return;

	_player->Update();
	_bow->Update();
	_muzzle->Update();

	for (int i = 0; i < _bulletNum; i++)
	{
		_bullets[i]->Update();
	}

	_monster->Update();
	
	Input();
	CollisionManage();

	_monster->Move(_player);

	Vector _dir = mousePos - _bow->GetTransform()->GetWorldPos();
	_bow->GetTransform()->SetAngle(_dir.Angle());
}

void DungreedScene::Render()
{
	if (_player->IsDead() || _monster->IsDead()) return;

	_player->Render();
	_bow->Render();

	for (int i = 0; i < _bulletNum; i++)
	{
		_bullets[i]->Render();
	}

	_monster->Render();
}

void DungreedScene::PostRender()
{
	if (_player->IsDead() || _monster->IsDead()) return;

	_player->PostRender();

	for (int i = 0; i < _bulletNum; i++)
	{
		_bullets[i]->PostRender();
	}

	_monster->PostRender();
}

void DungreedScene::Input()
{
	AutoReload();

	if (KEY_DOWN(VK_LBUTTON))
	{
		if (_curMag == _fullMag)
			return;

		auto noneActiveBullet = find_if(_bullets.begin(), _bullets.end(), [](shared_ptr<DunBullet> b)-> bool
			{
				return !(b->GetActive());
			});

		if (noneActiveBullet == _bullets.end())
			return;

		Fire(*noneActiveBullet);
	}

	if (KEY_PRESS('R'))
	{
		Reload();
	}
}

void DungreedScene::CollisionManage()
{
	PlayerCollision();
	MonsterCollision();
}

void DungreedScene::Fire(shared_ptr<DunBullet> _bullet)
{
	Vector dir = mousePos - _bow->GetTransform()->GetWorldPos();
	_bullet->SetActive(true);
	_bullet->SetPos(_muzzle->GetWorldPos());
	_bullet->SetDir(dir);
	_bullet->SetAngle(dir.Angle());

	if (_curMag < _fullMag)
		_curMag++;
}

void DungreedScene::Reload()
{
	if (_curMag == 0)
		return;

	_curMag = 0;
}

void DungreedScene::AutoReload()
{
	if (_curMag == _fullMag)
	{
		if (_time >= _autoTime)
		{
			_curMag = 0;
			_time = 0.0f;
		}

		_time += DELTA_TIME;
	}
}

void DungreedScene::PlayerCollision()
{
	if (_player->GetCollider()->IsCollision(_monster->GetCollider()))
	{
		_player->GetCollider()->SetRed();
		_monster->GetCollider()->SetRed();
		//_player->TakeDamage(_monster->GetDamage());

		Vector _dir = (_player->GetTransform()->GetWorldPos() -
			_monster->GetTransform()->GetWorldPos()).NormalVector();

		float pushDis = 100.0f * DELTA_TIME;
		_player->GetTransform()->AddPos(_dir * pushDis);
		_monster->GetTransform()->AddPos((_dir * -pushDis));
	}
	else
	{
		_player->GetCollider()->SetGreen();
		_monster->GetCollider()->SetGreen();
	}
}

void DungreedScene::MonsterCollision()
{
	auto activeBullet = find_if(_bullets.begin(), _bullets.end(), [](shared_ptr<DunBullet> b)->bool
		{
			return b->GetActive();
		});

	if (activeBullet == _bullets.end())
		return;

	shared_ptr<DunBullet> cb = *activeBullet;

	if (_monster->GetCollider()->IsCollision(cb->GetCollider()))
	{
		cb->GetCollider()->SetRed();
		_monster->GetCollider()->SetRed();
		_monster->TakeDamage(cb->GetDamage());
	}
	else
	{
		cb->GetCollider()->SetGreen();
		_monster->GetCollider()->SetGreen();
	}
}