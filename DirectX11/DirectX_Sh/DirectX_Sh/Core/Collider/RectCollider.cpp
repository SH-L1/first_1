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

	_temp.top = _transform->GetWorldPos().y + _transform->GetWorldScale().y * _halfSize.y;
	_temp.bottom = _transform->GetWorldPos().y - _transform->GetWorldScale().y * _halfSize.y;
	_temp.left = _transform->GetWorldPos().x - _transform->GetWorldScale().x * _halfSize.x;
	_temp.right = _transform->GetWorldPos().x + _transform->GetWorldScale().x * _halfSize.x;

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
	OBB_DESC _temp = GetOBBDesc();

	Vector distance = _temp.pos - pos;
	Vector _axisX = _temp.direction[0];
	Vector _axisY = _temp.direction[1];
	float lengthX = abs(_axisX.DotProduct(distance));
	float lengthY = abs(_axisY.DotProduct(distance));

	if (lengthX > _temp.halfSize.x || lengthY > _temp.halfSize.y)
		return false;
	
	return true;
}

bool RectCollider::IsCollision(shared_ptr<RectCollider> other, bool isObb)
{
	if (isObb)
		return IsCollision_OBB(other);

	return IsCollision_AABB(other);
}

bool RectCollider::Block(shared_ptr<RectCollider> other)
{
	if (!IsCollision(other)) return false;

	Vector dir = other->GetTransform()->GetWorldPos() - GetWorldPos();
	Vector sum = other->GetWorldScale() * 0.5f + GetWorldScale() * 0.5f;
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

bool RectCollider::Block(shared_ptr<CircleCollider> other)
{
	if (!IsCollision(other)) return false;

	Vector otherHalfSize = Vector(other->GetWorldRadius(), other->GetWorldRadius());
	Vector dir = GetWorldPos() - other->GetWorldPos();
	Vector sum = GetWorldScale() * 0.5f + otherHalfSize;
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

bool RectCollider::IsCollision(shared_ptr<CircleCollider> other, bool isObb)
{
	if (isObb)
		return IsCollision_OBB(other);

	return IsCollision_AABB(other);
}

bool RectCollider::IsCollision_AABB(shared_ptr<RectCollider> other)
{
	Vector _centre = GetWorldPos();
	Vector _otherCentre = other->GetWorldPos();
	Vector distance = (GetWorldScale() + other->GetWorldScale()) * 0.5f;

	if (distance.x < abs(_centre.x - _otherCentre.x) ||
		distance.y < abs(_centre.y - _otherCentre.y))
		return false;

	return true;
}

bool RectCollider::IsCollision_AABB(shared_ptr<CircleCollider> other)
{
	AABB_DESC _temp = GetAABBDesc();
	
	Vector _circlePos = other->GetWorldPos();
	float _radius = other->GetWorldRadius();

	float closestX = max(_temp.left, min(_temp.right, _circlePos.x));
	float closestY = max(_temp.bottom, min(_temp.top, _circlePos.y));
	Vector closePoint = Vector(closestX, closestY);

	float distance = (_circlePos - closePoint).Length();

	if (distance > _radius)
		return false;

	return true;
}

bool RectCollider::IsCollision_OBB(shared_ptr<RectCollider> other)
{
	OBB_DESC _temp = GetOBBDesc();
	OBB_DESC _tempRect = other->GetOBBDesc();

	Vector _dis = _temp.pos - _tempRect.pos;

	Vector _axisX1 = _temp.direction[0];
	Vector _axisY1 = _temp.direction[1];
	Vector _lineX1 = _axisX1 * _temp.halfSize.x;
	Vector _lineY1 = _axisY1 * _temp.halfSize.y;

	Vector _axisX2 = _tempRect.direction[0];
	Vector _axisY2 = _tempRect.direction[1];
	Vector _lineX2 = _axisX2 * _tempRect.halfSize.x;
	Vector _lineY2 = _axisY2 * _tempRect.halfSize.y;

	float length = abs(_axisX1.DotProduct(_dis));
	float lengthA = _lineX1.Length();
	float lengthB = abs(_axisX1.DotProduct(_lineX2)) + abs(_axisX1.DotProduct(_lineY2));

	if (length > lengthA + lengthB)
		return false;

	length = abs(_axisY1.DotProduct(_dis));
	lengthA = _lineY1.Length();
	lengthB = abs(_axisY1.DotProduct(_lineY2)) + abs(_axisY1.DotProduct(_lineX2));

	if (length > lengthA + lengthB)
		return false;

	length = abs(_axisX2.DotProduct(_dis));
	lengthA = _lineX2.Length();
	lengthB = abs(_axisX2.DotProduct(_lineX1)) + abs(_axisX2.DotProduct(_lineY1));

	if (length > lengthA + lengthB)
		return false;

	length = abs(_axisY2.DotProduct(_dis));
	lengthA = _lineY2.Length();
	lengthB = abs(_axisY2.DotProduct(_lineY1)) + abs(_axisY2.DotProduct(_lineX1));

	if (length > lengthA + lengthB)
		return false;

	return true;
}

bool RectCollider::IsCollision_OBB(shared_ptr<CircleCollider> other)
{
	OBB_DESC _temp = GetOBBDesc();

	Vector _dis = other->GetWorldPos() - _temp.pos;
	float _radius = other->GetWorldRadius();

	float longest = _temp.halfSize.Length();
	if (_dis.Length() > longest + _radius)
		return false;

	Vector _axisX = _temp.direction[0];
	float lengthA = abs(_axisX.DotProduct(_dis));
	if (lengthA > _temp.halfSize.x + _radius)
		return false;

	Vector _axisY = _temp.direction[1];
	float lengthB = abs(_axisY.DotProduct(_dis));
	if (lengthB > _temp.halfSize.y + _radius)
		return false;

	return true;
}