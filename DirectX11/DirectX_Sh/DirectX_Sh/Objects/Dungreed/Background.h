#pragma once

class Background
{
public:
	Background();
	~Background();

	void Update();
	void Render();

	shared_ptr<Quad> GetQuad() { return _background; }

private:
	shared_ptr<Quad> _background;
};