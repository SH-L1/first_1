	#include "framework.h"
	#include "RectCollider.h"

	RectCollider::RectCollider(Vector centre, Vector size)
		: _centre(centre), _halfSize(size * 0.5f)
	{
		CreateMesh();
		CreateMaterial();

		_transform = make_shared<Transform>();
		_transform->SetPos(centre);
		
		// TODO _colorBuffer = make_shared<ColorBuffer>();
	}

	RectCollider::~RectCollider()
	{
	}

	void RectCollider::Update()
	{
		_transform->Update();
	}

	void RectCollider::Render()
	{
		_transform->SetVS(0);
		
		_vertexBuffer->IASet(0);

		DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

		_vs->VSSet();
		_ps->PSSet();

		DC->Draw(_vertices.size(), 0);
	}

	bool RectCollider::IsCollision(const Vector& pos)
	{
		if (pos.x > Right()) return false;
		if (pos.x < Left()) return false;
		if (pos.y > Bottom()) return false;
		if (pos.y < Top()) return false;

		return true;
	}

	bool RectCollider::IsCollision(shared_ptr<RectCollider> other)
	{
		if (Right() < other->Left()) return false;
		if (Left() > other->Right()) return false;
		if (Bottom() < other->Top()) return false;
		if (Top() > other->Bottom()) return false;

		return true;
	}

	// AABB 충돌
	bool RectCollider::IsCollision(shared_ptr<CircleCollider> other)
	{
		Vector circleCentre = other->centre;
		float radius = other->GetRadius();
		float length = (circleCentre - centre).Length();

		// 위 아래 충돌체크
		if (circleCentre.x < Right() && circleCentre.x > Left())
		{
			float result = 0.0f;
			if (circleCentre.y > centre.y) // circle이 아래쪽에있다.
				result = circleCentre.y - centre.y;
			else
				result = centre.y - circleCentre.y;

			return result < radius + _halfSize.y;
		}

		// 좌우 충돌체크
		if (circleCentre.y < Bottom() && circleCentre.y > Top())
		{
			float result = 0.0f;
			if (circleCentre.x > centre.x) // circle이 오른쪽에 있다.
				result = circleCentre.x - centre.x;
			else
				result = centre.x - circleCentre.x;

			return result < radius + _halfSize.x;
		}

		// 각 꼭지점 체크
		Vector leftTop = Vector(Left(), Top());
		Vector rightTop = Vector(Right(), Top());
		Vector leftBottom = Vector(Left(), Bottom());
		Vector rightBottom = Vector(Right(), Bottom());

		bool check1 = other->IsCollision(leftTop);
		bool check2 = other->IsCollision(rightTop);
		bool check3 = other->IsCollision(leftBottom);
		bool check4 = other->IsCollision(rightBottom);

		return check1 || check2 || check3 || check4;
	}

	Vector RectCollider::GetClosestPoint(const Vector& point)
	{
		float closestX = max(Left(), min(point.x, Right()));
		float closestY = max(Top(), min(point.y, Bottom()));

		return Vector(closestX, closestY);
	}

	void RectCollider::CreateMesh()
	{
		_vertices =
		{
			{ XMFLOAT3(-_halfSize.x, _halfSize.y, 0.0f) },
			{ XMFLOAT3(_halfSize.x, _halfSize.y, 0.0f) },
			{ XMFLOAT3(_halfSize.x, -_halfSize.y, 0.0f) },
			{ XMFLOAT3(-_halfSize.x, -_halfSize.y, 0.0f) },
			{ XMFLOAT3(-_halfSize.x, _halfSize.y, 0.0f) }
		};
		
		_vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), _vertices.size(), 0);
	}

	void RectCollider::CreateMaterial()
	{
		_vs = make_shared<VertexShader>(L"Shaders/ColliderVertexShader.hlsl");
		_ps = make_shared<PixelShader>(L"Shaders/ColliderPixelShader.hlsl");
	}