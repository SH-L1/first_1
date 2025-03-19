#pragma once

class Mario
{
public:
	Mario();
	~Mario();

	void PreUpdate();
	void Update();
	void Render();
	void PostRender();

private:
	shared_ptr<Quad> _mario;
	shared_ptr<RectCollider> _collider;

private:
};