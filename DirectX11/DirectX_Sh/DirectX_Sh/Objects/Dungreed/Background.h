#pragma once

class Background
{
public:
	Background();
	~Background();

	void Render();

private:
	shared_ptr<Quad> _background;
};