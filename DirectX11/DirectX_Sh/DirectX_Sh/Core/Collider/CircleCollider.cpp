#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(float radius)
	: _radius(radius), Collider(Type::CIRCLE)
{
	CreateMesh();
	Collider::CreateMaterial();
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Update()
{
	Collider::Update();
}

void CircleCollider::Render()
{
	Collider::Render();
}

void CircleCollider::CreateMesh()
{
	Vertex _tempVertices;

	float theta = PI * (1.0f / 18.0f);

	for (int i = 0; i < 37; i++)
	{
		_tempVertices.pos = XMFLOAT3(_radius * cos(i * theta), _radius * sin(i * theta), 0.0f);
		_vertices.push_back(_tempVertices);
	}
}

bool CircleCollider::IsCollision(const Vector& pos)
{
	float distance = (_transform->GetWorldPos() - pos).Length();

	if (distance > GetWorldRadius())
		return false;
	
	return true;
}

bool CircleCollider::IsCollision(shared_ptr<CircleCollider> other)
{
	Vector _centre = _transform->GetWorldPos();
	Vector _otherCentre = other->GetTransform()->GetWorldPos();

	float distance = (_centre - _otherCentre).Length();

	float _rad = this->GetWorldRadius();
	float _otherRad = other->GetWorldRadius();

	if (distance > _rad + _otherRad)
		return false;

	return true;
}

bool CircleCollider::IsCollision(shared_ptr<RectCollider> other)
{
	return other->IsCollision(shared_from_this());
}