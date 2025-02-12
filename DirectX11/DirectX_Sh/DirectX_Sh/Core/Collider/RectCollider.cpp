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

		_vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), _vertices.size(), 0);
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
		{
			return true;
		}
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
		AABBRect _temp = GetAABBRect();

		Vector leftTop = Vector(_temp.left, _temp.top);
		Vector leftBottom = Vector(_temp.left, _temp.bottom);
		Vector rightTop = Vector(_temp.right, _temp.top);
		Vector rightBottom = Vector(_temp.right, _temp.bottom);

		if (other->IsCollision(leftTop) || other->IsCollision(leftBottom) ||
			other->IsCollision(rightTop) || other->IsCollision(rightBottom))
			return true;

		if (_temp.right > other->GetTransform()->GetWorldPos().x && _temp.left < other->GetTransform()->GetWorldPos().x)
		{
			if (_temp.top + other->GetWorldRadius() > other->GetTransform()->GetWorldPos().y
				&& _temp.bottom - other->GetWorldRadius() < other->GetTransform()->GetWorldPos().y)
				return true;
		}
		if (_temp.bottom < other->GetTransform()->GetWorldPos().y && _temp.top > other->GetTransform()->GetWorldPos().y)
		{
			if (_temp.left - other->GetWorldRadius() < other->GetTransform()->GetWorldPos().x
				&& _temp.right + other->GetWorldRadius() > other->GetTransform()->GetWorldPos().x)
				return true;
		}

		return false;
	}