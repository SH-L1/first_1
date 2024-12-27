#pragma once

class Cannon;

class CannonScene : public Scene
{
public:
	CannonScene();
	~CannonScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	shared_ptr<Cannon> _cannon;
	shared_ptr<Cannon> _rivalcannon;

	bool _turn = true;
}; 