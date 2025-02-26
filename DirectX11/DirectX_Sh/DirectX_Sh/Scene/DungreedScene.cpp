#include "framework.h"
#include "DungreedScene.h"

#include "Objects/Dungreed/DunPlayer.h"
#include "Objects/Dungreed/DunMonster.h"
#include "Objects/Dungreed/DunBullet.h"
#include "Objects/Dungreed/Background.h"

DungreedScene::DungreedScene()
{
	_background = make_shared<Background>();
	_player = make_shared<DunPlayer>();

	for (int i = 0; i < _bulletNum; i++)
	{
		shared_ptr<DunBullet> _bullet = make_shared<DunBullet>();
		_bullets.push_back(_bullet);
	}

	_monster = make_shared<DunMonster>();

	_monster->SetActive(true);
}

DungreedScene::~DungreedScene()
{
}

void DungreedScene::PreUpdate()
{
	_player->PreUpdate();

	for (int i = 0; i < _bulletNum; i++)
		_bullets[i]->PreUpdate();

	_monster->PreUpdate();
}

void DungreedScene::Update()
{
	Input();
	CollisionManager();

	_player->Update();

	for (int i = 0; i < _bulletNum; i++)
		_bullets[i]->Update();

	_monster->Move(_player->GetCollider()->GetWorldPos());
	_monster->Update();
}

void DungreedScene::Render()
{
	_background->Render();
	_player->Render();

	for (int i = 0; i < _bulletNum; i++)
		_bullets[i]->Render();

	_monster->Render();
}

void DungreedScene::PostRender()
{
	_player->PostRender();

	for (int i = 0; i < _bulletNum; i++)
		_bullets[i]->PostRender();

	_monster->PostRender();
}

void DungreedScene::Input()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		auto notActiveBullet = find_if(_bullets.begin(), _bullets.end(), [](shared_ptr<DunBullet> nab)->bool {
			return !(nab->GetActive());
			});

		if (notActiveBullet == _bullets.end())
			return;

		Fire(*notActiveBullet);
	}
}

void DungreedScene::CollisionManager()
{
	PlayerCollision();
	MonsterCollision();
}

void DungreedScene::Fire(shared_ptr<DunBullet> bullet)
{
	bullet->SetActive(true);
	bullet->SetPos(_player->GetMuzzle()->GetWorldPos());
	bullet->SetDir(_player->GetAim());
	bullet->SetAngle(_player->GetAim().Angle());
}

void DungreedScene::PlayerCollision()
{
	_monster->GetCollider()->Block(_player->GetCollider());

	if (_damageTime > 0)
	{
		_damageTime -= DELTA_TIME;
		return;
	}

	if (_player->GetCollider()->IsCollision(_monster->GetCollider()))
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
	auto collideBullet = find_if(_bullets.begin(), _bullets.end(), [this](shared_ptr<DunBullet> ab)->bool
		{
			return ab->GetCollider()->IsCollision(_monster->GetCollider());
		});

	if (collideBullet == _bullets.end()) return;
	
	(*collideBullet)->SetActive(false);
	_monster->TakeDamage((*collideBullet)->GetDamage());
}

// TODO(����)
// 1. ȭ�� �浹 ��, ������ �浹��
// 2. ȭ�� �浹 ��, ���� ȭ�� ������ ����
// 3. monster ��� �Ŀ��� player�� �浹 ��� ������
// 4. bullet�� bible ���� ��, ���� ����

// TODO(�߰�)
// 1. monster�� bible �浹 ����
// 2. player ���� ��, bow�� bible�� ����