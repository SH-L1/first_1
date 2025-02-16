#pragma once

class ColliderScene : public Scene
{
public:
	ColliderScene();
	~ColliderScene();

	virtual void PreUpdate() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void Input();

private:
	shared_ptr<RectCollider> _rect;
	shared_ptr<RectCollider> _rotatedRect;
	shared_ptr <RectCollider> _movingRect;

	shared_ptr<CircleCollider> _circle;
	shared_ptr<CircleCollider> _movingCircle;
};