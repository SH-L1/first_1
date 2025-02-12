#pragma once

class ColliderScene : public Scene
{
public:
	ColliderScene();
	~ColliderScene();

	void Update() override;
	void Render() override;

private:
	shared_ptr<class RectCollider> _rect1;
	shared_ptr<class RectCollider> _rect2;
	shared_ptr<class CircleCollider> _circle1;
	shared_ptr<class CircleCollider> _circle2;
};