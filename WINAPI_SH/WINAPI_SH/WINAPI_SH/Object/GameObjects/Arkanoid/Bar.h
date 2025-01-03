#pragma once

class Bar
{
public:
	Bar();
	~Bar();

	void Update();
	void Render(HDC hdc);

	void AddPos(Vector2D vec) { _bar->centre += vec; }
	void UpdateBar(Vector2D barcentre) { _bar->centre = barcentre; }
	Vector2D GetSize() { return _halfsize; }
	Vector2D GetCollisionPoint(shared_ptr<CircleCollider> energy);
	
	shared_ptr<Collider> GetCollider() { return _bar; }

private:
	shared_ptr<RectCollider> _bar;
	
private:
	Vector2D _halfsize = Vector2D(80.0f, 10.0f);
};