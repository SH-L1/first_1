#pragma once

class Torch
{
public:
	Torch();
	~Torch();

	void PreUpdate();
	void Update();
	void Render();
	void PostRender();

	void Falling();

	void SetActive(bool active) { _isActive = active; }

	shared_ptr<Transform> GetTransform() { return _torch->GetTransform(); }
	shared_ptr<RectCollider> GetCollider() { return _collider; }
	bool GetActive() { return _isActive; }

private:
	shared_ptr<Quad> _torch;
	shared_ptr<RectCollider> _collider;

	weak_ptr<RectCollider> _ground;

private:
	bool _isActive = false;

	Vector _velocity = Vector(0, 0);

	float _gravity = 8.0f;
};