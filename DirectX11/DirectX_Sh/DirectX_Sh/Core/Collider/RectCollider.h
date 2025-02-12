#pragma once

class RectCollider : public Collider
{
private:
	struct AABBRect
	{
		float top = 0.0f;
		float bottom = 0.0f;
		float left = 0.0f;
		float right = 0.0f;
	};

	/*struct OBBRect
	{

	};*/

public:
	RectCollider(Vector size);
	~RectCollider();

	virtual void Update() override;
	virtual void Render() override;

	virtual void CreateMesh() override;

	Vector GetScale();

	AABBRect GetAABBRect();
	// OBBRect GetOBBRect();

	virtual bool IsCollision(const Vector& pos) override;
	virtual bool IsCollision(shared_ptr<class RectCollider> other) override;
	virtual bool IsCollision(shared_ptr<class CircleCollider> other) override;

private:
	Vector _halfSize;
};