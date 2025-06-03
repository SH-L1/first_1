#include "framework.h"
#include "Collider.h"

Collider::Collider(Type type)
	: _type(type)
{
}

Collider::~Collider()
{
}

void Collider::Update()
{
	_transform->Update();
	_colorBuffer->Update();
}

void Collider::Render()
{
	_transform->Update();

	_vs->IASetInputLayout();
	_vertexBuffer->IASet(0);

	_transform->SetVS(0);
	_colorBuffer->SetPS(0);

	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	_vs->VSSet();
	_ps->PSSet();

	DC->Draw(_vertices.size(), 0);
}

void Collider::CreateMaterial()
{
	_vs = make_shared<VertexShader>(L"Shaders/ColliderVertexShader.hlsl");
	_ps = make_shared<PixelShader>(L"Shaders/ColliderPixelShader.hlsl");

	_transform = make_shared<Transform>();

	_colorBuffer = make_shared<ColorBuffer>();
	SetColor(WHITE);
}

bool Collider::IsCollision(shared_ptr<Collider> other, bool isObb)
{
	switch (other->_type)
	{
	case Collider::Type::NONE:
		break;
	case Collider::Type::CIRCLE:
	{
		auto circle = dynamic_pointer_cast<CircleCollider>(other);
		return IsCollision(circle, isObb);
	}
	case Collider::Type::RECT:
	{
		auto rect = dynamic_pointer_cast<RectCollider>(other);
		return IsCollision(rect, isObb);
	}
	default:
		break;
	}

	return false;
}