#pragma once

class CircleCollider : public Collider, public enable_shared_from_this<CircleCollider>
{
public:
	CircleCollider(float radius);
	virtual ~CircleCollider();

	virtual void Update() override;
	virtual void Render() override;

	virtual void CreateMesh() override;

	float GetRadius() { return _radius; }
	float GetWorldRadius() { return _radius * _transform->GetWorldScale().x; }

	virtual bool IsCollision(const Vector& pos) override;
	virtual bool IsCollision(shared_ptr<CircleCollider> other, bool isObb = false) override;
	virtual bool IsCollision(shared_ptr<class RectCollider> other, bool isObb = false) override;

private:
	virtual bool IsCollision_AABB(shared_ptr<CircleCollider> other) override;
	virtual bool IsCollision_AABB(shared_ptr<class RectCollider> other) override;

	virtual bool IsCollision_OBB(shared_ptr<class RectCollider> other) override;
	virtual bool IsCollision_OBB(shared_ptr<CircleCollider> other) override;

private:
	float _radius;
};