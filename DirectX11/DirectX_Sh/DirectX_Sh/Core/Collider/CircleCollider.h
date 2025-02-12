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
	float GetWorldRadius() { return _radius * _transform->GetScale().x; }

	virtual bool IsCollision(const Vector& pos) override;
	virtual bool IsCollision(shared_ptr<CircleCollider> other) override;
	virtual bool IsCollision(shared_ptr<class RectCollider> other) override;

private:
	float _radius;
};