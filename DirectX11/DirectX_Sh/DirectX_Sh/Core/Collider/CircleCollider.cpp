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
	int _vertexCount = 36;
	Vertex _tempVertices;

	float theta = 2 * PI / _vertexCount;

	for (int i = 0; i < _vertexCount + 1; i++)
	{
		_tempVertices.pos = XMFLOAT3(_radius * cosf(i * theta), _radius * sinf(i * theta), 0.0f);
		_vertices.push_back(_tempVertices);
	}

	_vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), _vertices.size(), 0);
}

bool CircleCollider::IsCollision(const Vector& pos)
{
	float distance = (_transform->GetWorldPos() - pos).Length();

	if (distance > GetWorldRadius())
		return false;
	
	return true;
}

bool CircleCollider::IsCollision(shared_ptr<RectCollider> other, bool isObb)
{
	if (isObb)
		return IsCollision_OBB(other);

	return IsCollision_AABB(other);
}

bool CircleCollider::IsCollision(shared_ptr<CircleCollider> other, bool isObb)
{
	if (isObb)
		return IsCollision_OBB(other);

	return IsCollision_AABB(other);
}

bool CircleCollider::IsCollision_AABB(shared_ptr<RectCollider> other)
{
	return other->IsCollision(shared_from_this());
}

bool CircleCollider::IsCollision_AABB(shared_ptr<CircleCollider> other)
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

bool CircleCollider::IsCollision_OBB(shared_ptr<RectCollider> other)
{
	return other->IsCollision(shared_from_this(), true);
}

bool CircleCollider::IsCollision_OBB(shared_ptr<CircleCollider> other)
{
	return IsCollision(other);
}