#include "framework.h"
#include "ArrowScene.h"

ArrowScene::ArrowScene()
{
	_player = make_shared<Player>(L"Resource/Player.png");
	_bow = make_shared<Bow>(L"Resource/Bow.png");

	for (int i = 0;i < 30;i++)
	{
		shared_ptr<Bullet> _bullet = make_shared<Bullet>(L"Resource/Bullet.png");
		_bullets.push_back(_bullet);
	}

	_muzzle = make_shared<Transform>();
	
	_player->GetTransform()->SetPos(CENTRE);
	_player->GetTransform()->SetScale(Vector(0.2f, 0.2f));

	_bow->GetTransform()->SetParent(_player->GetTransform());
	_bow->GetTransform()->SetPos(Vector(100, -50));
	_bow->GetTransform()->SetScale(Vector(2.0f, 2.0f));
	
	_muzzle->SetParent(_bow->GetTransform());
	_muzzle->SetPos(Vector(100, 0));

	_rectCollider = make_shared<RectCollider>(CENTRE, Vector(100, 100));
}

ArrowScene::~ArrowScene()
{
}

void ArrowScene::Update()
{
	_rectCollider->Update();

	_player->Update();
	_bow->Update();
	_muzzle->Update();

	for (int i = 0; i < 30; i++)
	{
		_bullets[i]->Update();
	}

	Vector _dir = mousePos - _bow->GetTransform()->GetWorldPos();
	_bow->GetTransform()->SetAngle(_dir.Angle());

	Input();
}

void ArrowScene::Render()
{
	_player->Render();
	_bow->Render();

	for (int i = 0; i < 30; i++)
	{
		_bullets[i]->Render();
	}

	_rectCollider->Render(); // 가려지면 안되기 떄문에
}

void ArrowScene::Input()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		Vector dir = mousePos - _bow->GetTransform()->GetWorldPos();

		auto noneActiveBullet = find_if(_bullets.begin(), _bullets.end(), [](shared_ptr<Bullet> b)-> bool
			{
				return !(b->GetActive());
			});

		if (noneActiveBullet == _bullets.end())
			return;

		shared_ptr<Bullet> _bullet = *noneActiveBullet;
		_bullet->SetActive(true);
		_bullet->SetPos(_muzzle->GetWorldPos());
		_bullet->SetDir(dir);
		_bullet->SetAngle(dir.Angle());
	}
}
