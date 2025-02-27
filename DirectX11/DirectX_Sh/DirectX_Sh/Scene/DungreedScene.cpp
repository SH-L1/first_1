#include "framework.h"
#include "DungreedScene.h"

#include "Objects/Dungreed/DunPlayer.h"
#include "Objects/Dungreed/DunMonster.h"
#include "Objects/Dungreed/DunSkeleton.h"
#include "Objects/Dungreed/Background.h"

DungreedScene::DungreedScene()
{
	_background = make_shared<Background>();
	_player = make_shared<DunPlayer>();

	_monster = make_shared<DunMonster>();

	for (int i = 0; i < _skeletonNum; i++)
	{
		shared_ptr<DunSkeleton> skeleton = make_shared<DunSkeleton>();
		_skeletons.push_back(skeleton);
	}

	_monster->SetActive(true);
}

DungreedScene::~DungreedScene()
{
}

void DungreedScene::PreUpdate()
{
	_player->PreUpdate();
	_monster->PreUpdate();

	for (auto skeleton : _skeletons)
		skeleton->PreUpdate();
}

void DungreedScene::Update()
{
	CollisionCheck();

	_player->Update();

	_monster->Move(_player->GetCollider());
	_monster->Update();

	if (_skeletonSpawnTime > 5.0f)
	{
		ActivateSkeleton();
		_skeletonSpawnTime = 0.0f;
	}

	for (auto skeleton : _skeletons)
	{
		skeleton->Move(_player->GetCollider());
		skeleton->Update();
	}

	_skeletonSpawnTime += DELTA_TIME;
}

void DungreedScene::Render()
{
	_background->Render();
	_player->Render();
	_monster->Render();

	for (auto skeleton : _skeletons)
		skeleton->Render();
}

void DungreedScene::PostRender()
{
	_player->PostRender();
	_monster->PostRender();

	for (auto skeleton : _skeletons)
		skeleton->PostRender();
}

void DungreedScene::CollisionCheck()
{
	PlayerCollision();
	MonsterCollision();
	SkeletonCollision();
}

void DungreedScene::PlayerCollision()
{
	if(_monster->GetActive() == true)
		_monster->GetCollider()->Block(_player->GetCollider());
	
	for (auto skeleton : _skeletons)
	{
		if (skeleton->GetActive() == false)
			return;

		skeleton->GetCollider()->Block(_player->GetCollider());
	}

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

	for (auto skeleton : _skeletons)
	{
		if (skeleton->GetActive() == false)
			return;

		if (skeleton->IsCollision_Skeleton(_player->GetCollider()))
		{
			_player->TakeDamage(skeleton->GetDamage());

			Vector _dir = (_player->GetCollider()->GetWorldPos() -
				skeleton->GetCollider()->GetWorldPos()).NormalVector();
			float pushDis = 50.0f;

			_player->GetCollider()->GetTransform()->AddPos(_dir * pushDis);

			_damageTime = 1.0f;
		}
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

void DungreedScene::SkeletonCollision()
{
	for (auto skeleton : _skeletons)
	{
		if (skeleton->GetActive() == false)
			continue;

		if (_player->IsCollision_Bullet(skeleton->GetCollider()))
		{
			skeleton->TakeDamage(_player->GetDamage());
		}

		if (_player->IsCollision_Bible(skeleton->GetCollider()))
		{
			skeleton->TakeDamage(_player->GetDamage());
		}

		break;
	}
}

void DungreedScene::ActivateSkeleton()
{
	auto notActiveSkeleton = find_if(_skeletons.begin(), _skeletons.end(), [](shared_ptr<DunSkeleton> s)-> bool
		{
			return !(s->GetActive());
		});

	if (notActiveSkeleton == _skeletons.end())
		return;

	(*notActiveSkeleton)->SetActive(true);
}

// TODO(추가)
// 2. player 반전 시, bow와 bible도 반전