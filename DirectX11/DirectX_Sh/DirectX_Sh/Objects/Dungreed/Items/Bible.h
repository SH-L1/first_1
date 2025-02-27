#pragma once

class Bible
{
public:
	Bible();
	~Bible();

 	void PreUpdate();
	void Update();
	void Render();
	void PostRender();

	void SetActive(bool active) { _isActive = active; }

	bool GetActive() { return _isActive; }
	shared_ptr<RectCollider> GetCollider() { return _collider; }

private:
	shared_ptr<Quad> _bible;
	shared_ptr<RectCollider> _collider;

private:	
	bool _isActive = false;
};