#pragma once

class PaintScene : public Scene
{
public:
	PaintScene();
	~PaintScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	shared_ptr<Collider> circle = make_shared<CircleCollider>(Vector2D(500, 500), 50);
	shared_ptr<Collider> rect = make_shared<RectCollider>(Vector2D(500, 500), Vector2D(30, 30));
	shared_ptr<Line> line = make_shared<LineCollider>(Vector2D(500, 500), Vector2D(30, 111));
};