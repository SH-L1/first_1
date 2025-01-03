#pragma once

class LineCollider : public Line, public enable_shared_from_this<LineCollider>
{
public:
	LineCollider(Vector2D start, Vector2D end);

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual HitResult IsCollision(shared_ptr<Line> other) override;

public:
	LPPOINT lpPoint = nullptr;
	Vector2D _start;
	Vector2D _end;
};