#pragma once

class Bar;
class Block;
class Map;

class ArkanoidScene : public Scene
{
public:
	ArkanoidScene();
	~ArkanoidScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	shared_ptr<Map> _arkanoidMap;
};

