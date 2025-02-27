#include "framework.h"
#include "DungreedScene.h"

#include "Objects/Dungreed/DunPlayer.h"
#include "Objects/Dungreed/DunMonster.h"
#include "Objects/Dungreed/Background.h"

DungreedScene::DungreedScene()
{
	_background = make_shared<Background>();
	_player = make_shared<DunPlayer>();

	_monster = make_shared<DunMonster>();

	_monster->SetActive(true);
}

DungreedScene::~DungreedScene()
{
}

void DungreedScene::PreUpdate()
{
	_player->PreUpdate();
	_monster->PreUpdate();
}

void DungreedScene::Update()
{
	CollisionCheck();

	_player->Update();
	_monster->Move(_player->GetCollider()->GetWorldPos());
	_monster->Update();
}

void DungreedScene::Render()
{
	_background->Render();
	_player->Render();
	_monster->Render();
}

void DungreedScene::PostRender()
{
	_player->PostRender();
	_monster->PostRender();
}

void DungreedScene::CollisionCheck()
{
	PlayerCollision();
	MonsterCollision();
}

void DungreedScene::PlayerCollision()
{
	_monster->GetCollider()->Block(_player->GetCollider());

	if (_damageTime > 0)
	{
		_damageTime -= DELTA_TIME;
		return;
	}

	if (_monster->IsCollision_Monster(_player->GetCollider()))
	{
		_player->TakeDamage(_monster->GetDamage());

		Vector _dir = (_player->GetCollider()->GetWorldPos() -
			_monster->GetCollider()->GetWorldPos()).NormalVector();
		float pushDis = 50.0f;

		_player->GetCollider()->GetTransform()->AddPos(_dir * pushDis);

		_damageTime = 1.0f;
	}
}

void DungreedScene::MonsterCollision()
{
	if (_player->IsCollision_Bullet(_monster->GetCollider()))
	{
		_monster->TakeDamage(_player->GetDamage());
	}

	if (_player->IsCollision_Bible(_monster->GetCollider()))
	{
		_monster->TakeDamage(_player->GetDamage());
	}
}

// TODO(����)
// 3. monster ��� �Ŀ��� player�� �浹 ��� ������

// TODO(�߰�)
// 2. player ���� ��, bow�� bible�� ����