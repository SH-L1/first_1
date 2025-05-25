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

	void SetPos(Vector pos) {
		_collider->SetPos(pos);
	}

private:
	shared_ptr<Quad> _wall;
	shared_ptr<RectCollider> _collider;
};