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

bool CircleCollider::Block(shared_ptr<RectCollider> other)
{
	if(!IsCollision(other)) return false;

	Vector thisHalfSize = Vector(GetWorldRadius(), GetWorldRadius());
	Vector dir = GetWorldPos() - other->GetWorldPos();
	Vector sum = thisHalfSize + other->GetWorldScale() * 0.5f;
	Vector overlap = Vector(sum.x - abs(dir.x), sum.y - abs(dir.y));
	Vector curPos = other->GetWorldPos();

	dir.NormalVector();

	if (overlap.x > overlap.y)
	{
		if (dir.y < 0.0f)
			dir.y = -1.0f;
		else if (dir.y > 0.0f)
			dir.y = 1.0f;

		curPos.y += dir.y * overlap.y;
	}
	else
	{
		if (dir.x < 0.0f)
			dir.x = -1.0f;
		else if (dir.x > 0.0f)
			dir.x = 1.0f;

		curPos.x += dir.x * overlap.x;
	}

	other->GetTransform()->SetPos(curPos);

	return true;
}

bool CircleCollider::Block(shared_ptr<CircleCollider> other)
{
	if (!IsCollision(other)) return false;

	Vector dir = GetWorldPos() - other->GetWorldPos();
	float scalar = abs(GetWorldRadius() + other->GetWorldRadius() - dir.Length());

	dir.NormalVector();

	other->GetTransform()->AddPos(dir * scalar * DELTA_TIME);

	return true;
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