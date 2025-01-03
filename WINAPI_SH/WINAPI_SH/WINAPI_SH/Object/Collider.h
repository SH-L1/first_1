#pragma once

class Collider
{
public:
	enum Color
	{
		C_GREEN = 0,
		C_RED = 1
	};

	enum Type
	{
		NONE,
		CIRCLE,
		RECT
	};

	Collider();
	virtual ~Collider();

	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

	void SetRed() { _curColor = Color::C_RED; }
	void SetGreen() { _curColor = Color::C_GREEN; }

	bool IsCollision(shared_ptr<Collider> other);

	virtual bool IsCollision(const Vector2D& pos) = 0;
	virtual bool IsCollision(shared_ptr<class CircleCollider> other) = 0;
	virtual bool IsCollision(shared_ptr<class RectCollider> other) = 0;

	Vector2D centre;

protected:
	Type _type = NONE;

	Color _curColor = Color::C_GREEN;
	vector<HPEN> _pens;
};