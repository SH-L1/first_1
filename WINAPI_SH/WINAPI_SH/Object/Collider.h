#pragma once

class Collider
{
public:
	enum Color
	{
		C_GREEN = 0,
		C_RED = 1
	};

	Collider();
	virtual ~Collider();

	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;

	void SetRed() { _curColor = Color::C_RED; }
	void SetGreen() { _curColor = Color::C_GREEN; }

	bool IsCollision(shared_ptr<Collider> other);

	virtual bool IsCollision(const Vector2D& pos) abstract;
	virtual bool IsCollision(shared_ptr<CircleCollider> other) abstract;
	virtual bool IsCollision(shared_ptr<class RectCollider> other) abstract;

	Vector2D centre;

protected:
	Color _curColor = Color::C_GREEN;
	vector<HPEN> _pens;
};