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
		Vertex _tempVertices;
		
		_tempVertices.pos = XMFLOAT3(-_halfSize.x, _halfSize.y, 0.0f);
		_vertices.push_back(_tempVertices);

		_tempVertices.pos = XMFLOAT3(_halfSize.x, _halfSize.y, 0.0f);
		_vertices.push_back(_tempVertices);

		_tempVertices.pos = XMFLOAT3(_halfSize.x, -_halfSize.y, 0.0f);
		_vertices.push_back(_tempVertices);

		_tempVertices.pos = XMFLOAT3(-_halfSize.x, -_halfSize.y, 0.0f);
		_vertices.push_back(_tempVertices);

		_tempVertices.pos = XMFLOAT3(-_halfSize.x, _halfSize.y, 0.0f);
		_vertices.push_back(_tempVertices);
	}

	Vector RectCollider::GetScale()
	{
		Vector _temp;

		_temp.x = (_halfSize.x * 2.0f) * _transform->GetScale().x;
		_temp.y = (_halfSize.y * 2.0f) * _transform->GetScale().y;

		return _temp;
	}

	RectCollider::AABBRect RectCollider::GetAABBRect()
	{
		AABBRect _temp;

		_temp.top = _transform->GetWorldPos().y + _transform->GetScale().y * 0.5f;
		_temp.bottom = _transform->GetWorldPos().y - _transform->GetScale().y * 0.5f;
		_temp.left = _transform->GetWorldPos().x - _transform->GetScale().x * 0.5f;
		_temp.right = _transform->GetWorldPos().x + _transform->GetScale().x * 0.5f;

		return _temp;
	}

	/*RectCollider::OBBRect RectCollider::GetOBBRect()
	{
	}*/

	bool RectCollider::IsCollision(const Vector& pos)
	{
		AABBRect _temp = GetAABBRect();

		if (pos.x >= _temp.left && pos.x <= _temp.right &&
			pos.y >= _temp.bottom && pos.y <= _temp.top)
			return true;
		
		return false;
	}

	bool RectCollider::IsCollision(shared_ptr<RectCollider> other)
	{
		Vector _centre = _transform->GetWorldPos();
		Vector _otherCentre = other->GetTransform()->GetWorldPos();
		Vector distance = (this->GetScale() + other->GetScale()) * 0.5f;

		if (distance.x < abs(_centre.x - _otherCentre.x)) return false;
		else if (distance.y < abs(_centre.y - _otherCentre.y)) return false;

		return true;
	}

	bool RectCollider::IsCollision(shared_ptr<CircleCollider> other)
	{
		AABBRect rect = GetAABBRect();
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