#pragma once

class Wall
{
public:
	Wall();
	~Wall();

	void PreUpdate();
	void Update();
	void Render();
	void PostRender();

	shared_ptr<Transform> GetTransform() { return _wall->GetTransform(); }
	shared_ptr<RectCollider> GetCollider() { return _collider; }
	shared_ptr<Quad> GetQuad() { return _wall; }

	void SetPos(Vector pos) { _collider->SetPos(pos); }
	Vector GetFinalSize() { return Vector(_wall->GetImageSize().x * _colliderScale.x * _textureScale.x, _wall->GetImageSize().y * _colliderScale.y * _textureScale.y); }

private:
	shared_ptr<Quad> _wall;
	shared_ptr<RectCollider> _collider;

private:
	Vector _textureScale = Vector(8.0f, 8.0f);
	Vector _colliderScale = Vector(25.0f, 5.0f);
};