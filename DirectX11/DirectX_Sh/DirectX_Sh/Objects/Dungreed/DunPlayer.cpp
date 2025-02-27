#include "framework.h"
#include "DunPlayer.h"	

#include "Items/DunBow.h"
#include "Items/DunBullet.h"
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
	CreateBullet();
	CreateBible();
}

DunPlayer::~DunPlayer()
{
}

void DunPlayer::PreUpdate()
{
	if (_isActive == false) return;

	_collider->Update();

	for (auto bullet : _bullets)
		bullet->PreUpdate();

	for (auto bible : _bibles)
		bible->PreUpdate();
}

void DunPlayer::Update()
{
	if (_isActive == false) return;

	Move();
	Fire();
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

	for (auto bullet : _bullets)
		bullet->Update();

	for (auto bible : _bibles)
		bible->Update();
	
	_bibleTime += DELTA_TIME;
}

void DunPlayer::Render()
{
	if (_isActive == false) return;

	_player->Render();
	_bow->Render();

	for (auto bullet : _bullets)
		bullet->Render();

	for (auto bible : _bibles)
		bible->Render();
}

void DunPlayer::PostRender()
{
	if (_isActive == false) return;

	_collider->Render();

	for (auto bullet : _bullets)
		bullet->PostRender();

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
		_isActive = false;
}

void DunPlayer::Move()
{
	Vector moveDir = Vector(0, 0);
	Vector curPos = _collider->GetWorldPos();
	Vector space = _collider->GetWorldScale() * 0.5f;
	
	if (KEY_PRESS('W'))
	{
		if(curPos.y < WIN_HEIGHT - space.y)
			moveDir.y += 1.0f;
	}
	if (KEY_PRESS('S'))
	{
		if(curPos.y > space.y)
			moveDir.y -= 1.0f;
	}
	if (KEY_PRESS('A'))
	{
		if(curPos.x > space.x)
			moveDir.x -= 1.0f;
		_player->SetLeftRight(1);
	}
	if (KEY_PRESS('D'))
	{
		if(curPos.x < WIN_WIDTH - space.x)
			moveDir.x += 1.0f;
		_player->SetLeftRight(0);
	}

	if (moveDir.Length() > 0.0f)
	{
		moveDir.Normalize();
		_collider->GetTransform()->AddPos(moveDir * _playerSpeed * DELTA_TIME);
	}
}

void DunPlayer::Fire()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		auto notActiveBullet = find_if(_bullets.begin(), _bullets.end(),
			[](shared_ptr<DunBullet> b)->bool {
				return !(b->GetActive());
			});
	
		if (notActiveBullet == _bullets.end())
			return;

		(*notActiveBullet)->SetActive(true);
		(*notActiveBullet)->SetPos(_muzzle->GetWorldPos());
		(*notActiveBullet)->SetDir(_bowDir);
		(*notActiveBullet)->SetAngle(_bowDir.Angle());
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

void DunPlayer::CreateBullet()
{
	for (int i = 0; i < _bulletNum; i++)
	{
		shared_ptr<DunBullet> _bullet = make_shared<DunBullet>();
		_bullets.push_back(_bullet);
	}
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
	_playerBible->AddAngle(0.5f * PI * DELTA_TIME);
	_playerBible->Update();
}

bool DunPlayer::IsCollision_Bullet(shared_ptr<Collider> other)
{
	if (_isActive == false) return false;

	for (auto bullet : _bullets)
	{
		if (bullet->GetActive() == false)
			continue;

		if (other->IsCollision(bullet->GetCollider()))
		{
			bullet->SetActive(false);
			return true;
		}
	}

	return false;
}

bool DunPlayer::IsCollision_Bible(shared_ptr<Collider> other)
{
	if (_isActive == false) return false;

	for (auto bible : _bibles)
	{
		if (bible->GetActive() == false)
			continue;

		if (other->IsCollision(bible->GetCollider()))
			return true;
	}

	return false;
}