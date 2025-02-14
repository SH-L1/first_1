#pragma once

class ColliderScene : public Scene
{
public:
	ColliderScene();
	~ColliderScene();

	void Update() override;
	void Render() override;

private:
	shared_ptr<RectCollider> _rect1;
	shared_ptr<RectCollider> _rect2;
	shared_ptr<CircleCollider> _circle1;
	shared_ptr<CircleCollider> _circle2;
};