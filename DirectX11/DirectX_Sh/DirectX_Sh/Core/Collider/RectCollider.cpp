#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector size)
	: _halfSize(size * 0.5f), Collider(Type::RECT)
{
	CreateMesh();
	Collider::CreateMaterial();
}
RectCollider::~RectCollider()
{
}
void RectCollider::Update()
{
	Collider::Update();
}
void RectCollider::Render()
{
	Collider::Render();
}
void RectCollider::CreateMesh()
{
	_vertices =
	{
		{ XMFLOAT3(-_halfSize.x, _halfSize.y, 0.0f) },
		{ XMFLOAT3(_halfSize.x, _halfSize.y, 0.0f)},
		{ XMFLOAT3(_halfSize.x, -_halfSize.y, 0.0f) },
		{ XMFLOAT3(-_halfSize.x, -_halfSize.y, 0.0f)},
		{ XMFLOAT3(-_halfSize.x, _halfSize.y, 0.0f) }
	};

	_vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), _vertices.size(), 0);
}
Vector RectCollider::GetWorldScale()
{
	Vector _temp;

	_temp.x = (_halfSize.x * 2.0f) * _transform->GetWorldScale().x;
	_temp.y = (_halfSize.y * 2.0f) * _transform->GetWorldScale().y;

	return _temp;
}
RectCollider::AABB_DESC RectCollider::GetAABBDesc()
{
	AABB_DESC _temp;

	_temp.top = _transform->GetWorldPos().y + _transform->GetWorldScale().y * 0.5f;
	_temp.bottom = _transform->GetWorldPos().y - _transform->GetWorldScale().y * 0.5f;
	_temp.left = _transform->GetWorldPos().x - _transform->GetWorldScale().x * 0.5f;
	_temp.right = _transform->GetWorldPos().x + _transform->GetWorldScale().x * 0.5f;

	return _temp;
}

RectCollider::OBB_DESC RectCollider::GetOBBDesc()
{
	OBB_DESC _temp;

	_temp.pos = _transform->GetWorldPos();
	
	Vector _tempSize;
	_tempSize.x = GetWorldScale().x * 0.5f;
	_tempSize.y = GetWorldScale().y * 0.5f;

	_temp.halfSize = _tempSize;

	XMMATRIX _tempMatrix = _transform->GetMatrix();
	_temp.direction[0] = { _tempMatrix.r[0].m128_f32[0], _tempMatrix.r[0].m128_f32[1] };
	_temp.direction[1] = { _tempMatrix.r[1].m128_f32[0], _tempMatrix.r[1].m128_f32[1] };
	_temp.direction[0].Normalize();
	_temp.direction[1].Normalize();

	return _temp;
}

bool RectCollider::IsCollision(const Vector& pos)
{
	AABB_DESC _temp = GetAABBDesc();

	if (pos.x >= _temp.left && pos.x <= _temp.right &&
		pos.y >= _temp.bottom && pos.y <= _temp.top)
		return true;
	
	return false;
}

bool RectCollider::IsCollision(shared_ptr<RectCollider> other)
{
	Vector _centre = _transform->GetWorldPos();
	Vector _otherCentre = other->GetTransform()->GetWorldPos();
	Vector distance = (this->GetWorldScale() + other->GetWorldScale()) * 0.5f;

	if (distance.x < abs(_centre.x - _otherCentre.x)) return false;
	else if (distance.y < abs(_centre.y - _otherCentre.y)) return false;

	return true;
}

bool RectCollider::IsCollision(shared_ptr<CircleCollider> other)
{
	AABB_DESC rect = GetAABBDesc();
	Vector circlePos = other->GetTransform()->GetWorldPos();
	float radius = other->GetWorldRadius();

	Vector closestPoint;
	closestPoint.x = max(rect.left, min(circlePos.x, rect.right));
	closestPoint.y = max(rect.bottom, min(circlePos.y, rect.top));

	float distance = (circlePos - closestPoint).Length();

	if (distance > radius)
		return false;

	return true;
}

bool RectCollider::IsCollision_OBB(shared_ptr<RectCollider> other)
{
	OBB_DESC _temp = GetOBBDesc();
	OBB_DESC _tempRect = other->GetOBBDesc();

	Vector _dis = _temp.pos - _tempRect.pos;

	Vector _axisX = _temp.direction[0];
	Vector _axisY = _temp.direction[1];
	Vector _edgea1 = _temp.direction[0] * _temp.halfSize.x;
	Vector _edgea2 = _temp.direction[1] * _temp.halfSize.y;

	Vector _edgeb1 = _tempRect.direction[0] * _tempRect.halfSize.x;
	Vector _edgeb2 = _tempRect.direction[1] * _tempRect.halfSize.y;

	float _standX = abs(_axisX.DotProduct(_dis));
	float _standY = abs(_axisY.DotProduct(_dis));
	float lengthX = abs(_axisX.DotProduct(_edgea1)) + abs(_axisX.DotProduct(_edgeb1));
	float lengthY = abs(_axisY.DotProduct(_edgea2)) + abs(_axisY.DotProduct(_edgeb2));

	if (_standX > lengthX) return false;
	if (_standY > lengthY) return false;

	return true;
}

bool RectCollider::IsCollision_OBB(shared_ptr<CircleCollider> other)
{
	OBB_DESC _temp = GetOBBDesc();

	Vector _dis = _temp.pos - other->GetWorldPos();

	Vector _axisX = _temp.direction[0];
	Vector _axisY = _temp.direction[1];
	Vector _edgea1 = _temp.direction[0] * _temp.halfSize.x;
	Vector _edgea2 = _temp.direction[1] * _temp.halfSize.y;

	float _standX = abs(_axisX.DotProduct(_dis));
	float _standY = abs(_axisY.DotProduct(_dis));
	float lengthX = abs(_axisX.DotProduct(_edgea1)) + other->GetWorldRadius();
	float lengthY = abs(_axisY.DotProduct(_edgea2)) + other->GetWorldRadius();

	if (_standX > lengthX) return false;
	if (_standY > lengthY) return false;

	return true;
}