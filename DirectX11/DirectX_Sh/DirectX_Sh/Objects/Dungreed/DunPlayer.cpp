#include "framework.h"
#include "DunPlayer.h"	

#include "DunBow.h"
#include "Items/Bible.h"

DunPlayer::DunPlayer()
{
	_player = make_shared<Quad>(L"Resource/Player.png");
	_collider = make_shared<RectCollider>(_player->GetImageSize());

	_muzzle = make_shared<Transform>();
	_playerBow = make_shared<Transform>();
	_playerBible = make_shared<Transform>();

	_collider->SetPos(CENTRE);

	_player->GetTransform()->SetParent(_collider->GetTransform());
	_playerBow->SetParent(_collider->GetTransform());
	_playerBible->SetParent(_collider->GetTransform());

	_collider->GetTransform()->SetScale(Vector(0.08f, 0.08f));
	_player->GetTransform()->AddScale(Vector(0.1f, 0.1f));
	_player->GetTransform()->AddPos(Vector(0, 25));

	CreateBow();
	CreateBible();
}

DunPlayer::~DunPlayer()
{
}

void DunPlayer::PreUpdate()
{
	if (_isDead == true) return;

	_collider->Update();

	for (auto bible : _bibles)
		bible->PreUpdate();
}

void DunPlayer::Update()
{
	if (_isDead == true) return;

	Move();
	UpdateBible();
	SetAim();

	_player->Update();
	_playerBow->Update();
	_bow->Update();
	_muzzle->Update();

	if (_bibleTime > 10.0f)
	{
		ActivateBible();
		_bibleTime = 0.0f;
	}

	for (auto bible : _bibles)
		bible->Update();
	
	_bibleTime += DELTA_TIME;
}

void DunPlayer::Render()
{
	if (_isDead == true) return;

	_player->Render();
	_bow->Render();

	for (auto bible : _bibles)
		bible->Render();
}

void DunPlayer::PostRender()
{
	if (_isDead == true) return;

	_collider->Render();

	for (auto bible : _bibles)
		bible->PostRender();
}

void DunPlayer::SetAim()
{
	_bowDir = mousePos - _bow->GetTransform()->GetWorldPos();
	_bow->GetTransform()->SetAngle(_bowDir.Angle());
}

void DunPlayer::TakeDamage(int damage)
{
	_hp -= damage;

	if (_hp == 0)
		_isDead = true;
}

void DunPlayer::Move()
{
	Vector moveDir = Vector(0, 0);
	
	if (KEY_PRESS('W'))
		moveDir.y += 1.0f;
	if (KEY_PRESS('S'))
		moveDir.y -= 1.0f;
	if (KEY_PRESS('A'))
	{
		moveDir.x -= 1.0f;
		_player->SetLeftRight(1);
		// _playerScene->
	}
	if (KEY_PRESS('D'))
	{
		moveDir.x += 1.0f;
		_player->SetLeftRight(0);
	}

	if (moveDir.Length() > 0.0f)
	{
		moveDir.Normalize();
		_collider->GetTransform()->AddPos(moveDir * _playerSpeed * DELTA_TIME);
	}
}

void DunPlayer::CreateBow()
{
	_bow = make_shared<DunBow>();
	_bow->GetTransform()->SetParent(_playerBow);
	_bow->GetTransform()->AddScale(Vector(5, 5));
	_bow->GetTransform()->AddPos(Vector(150, -50));

	_muzzle->SetParent(_bow->GetTransform());
	_muzzle->SetPos(Vector(50, 3));
}

void DunPlayer::CreateBible()
{
	for (int i = 0; i < _bibleNum; i++)
	{
		shared_ptr<Bible> _bible = make_shared<Bible>();
		_bible->GetCollider()->SetParent(_playerBible);
		_bible->GetCollider()->SetPos(Vector(_bibleRadius, 0));
		_bible->GetCollider()->GetTransform()->SetScale(Vector(1.5f, 1.5f));
		_bibles.push_back(_bible);
	}
}

void DunPlayer::ActivateBible()
{
	if (_bibleCount >= _bibleNum) return;

	auto notActiveBible = find_if(_bibles.begin(), _bibles.end(), [](shared_ptr<Bible> b)->bool
		{
			return !(b->GetActive());
		});

	if (notActiveBible == _bibles.end())
		return;

	(*notActiveBible)->SetActive(true);
	_bibleCount++;

	float angle = 2 * PI / (float)_bibleCount;

	for (int i = 0; i < _bibleCount; i++)
	{
		Vector pos = Vector(cos(angle * i), sin(angle * i));
		_bibles[i]->GetCollider()->SetPos(pos * _bibleRadius);
	}
}

void DunPlayer::UpdateBible()
{
	_playerBible->AddAngle(PI * DELTA_TIME);
	_playerBible->Update();
}