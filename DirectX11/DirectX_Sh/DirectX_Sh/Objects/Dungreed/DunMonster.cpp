#include "framework.h"
#include "DunMonster.h"

DunMonster::DunMonster()
{
    _monster = make_shared<Quad>(L"Resource/monster.png");
    _collider = make_shared<RectCollider>(_monster->GetImageSize());

    _collider->SetPos(Vector(CENTRE.x, WIN_HEIGHT));
    _monster->GetTransform()->SetParent(_collider->GetTransform());
    _collider->GetTransform()->SetScale(Vector(0.2f, 0.2f));

    _collider->Update();
}

DunMonster::~DunMonster()
{
}

void DunMonster::PreUpdate()
{
    if (_isActive == false) return;

	_collider->Update();
}

void DunMonster::Update()
{
    if (_isActive == false) return;

	_monster->Update();
}

void DunMonster::Render()
{
    if (_isActive == false) return;

	_monster->Render();
}

void DunMonster::PostRender()
{
    if (_isActive == false) return;

	_collider->Render();
}

void DunMonster::TakeDamage(int damage)
{
    _hp -= damage;

    if (_hp == 0)
        _isActive = false;
}

void DunMonster::Move(shared_ptr<Collider> other)
{
    Vector _monsterPos = _collider->GetTransform()->GetWorldPos();

    Vector _dir = (other->GetWorldPos() - _monsterPos).NormalVector();

    if (abs(other->GetWorldPos().x - _monsterPos.x) <= 0.1f &&
        abs(other->GetWorldPos().y - _monsterPos.y) <= 0.1f)
        return;

    _collider->GetTransform()->AddPos(_dir * _speed * DELTA_TIME);
}

bool DunMonster::IsCollision_Monster(shared_ptr<Collider> other)
{
    if (_isActive == false) return false;

    if (other->IsCollision(_collider))
        return true;

    return false;
}