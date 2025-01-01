#pragma once

class Bar
{
public:
	Bar(Vector2D halfsize);
	~Bar();

	void Update();
	void Render(HDC hdc);

private:
	shared_ptr<RectCollider> _bar;
};

