#pragma once

class RectCollider : public Collider
{
private:
	struct AABB_DESC
	{
		float top = 0.0f;
		float bottom = 0.0f;
		float left = 0.0f;
		float right = 0.0f;
	};

	struct OBB_DESC
	{
		Vector pos;
		Vector halfSize;
		Vector direction[2];
	};

public:
	RectCollider(Vector size);
	~RectCollider();

	virtual void Update() override;
	virtual void Render() override;

	virtual void CreateMesh() override;

	Vector GetWorldScale();

	AABB_DESC GetAABBDesc();
	OBB_DESC GetOBBDesc();

	virtual bool IsCollision(const Vector& pos) override;
	virtual bool IsCollision(shared_ptr<class CircleCollider> other, bool isObb = false) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other, bool isObb = false) override;

private:
	virtual bool IsCollision_AABB(shared_ptr<RectCollider> other) override;
	virtual bool IsCollision_AABB(shared_ptr<class CircleCollider> other) override;

	virtual bool IsCollision_OBB(shared_ptr<class CircleCollider> other) override;
	virtual bool IsCollision_OBB(shared_ptr<RectCollider> other) override;

private:
	Vector _halfSize;
};