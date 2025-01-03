#pragma once

class LineScene : public Scene
{
public:
	LineScene();
	~LineScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	shared_ptr<LineCollider> _line1;
	shared_ptr<LineCollider> _line2;
	shared_ptr<LineCollider> _floor;

	shared_ptr<CircleCollider> _circle;
};

