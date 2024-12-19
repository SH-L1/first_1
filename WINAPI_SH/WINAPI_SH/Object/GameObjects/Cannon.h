#pragma once

// ��� ��� Ŭ���� : ����������
class Cannon// : public shared_ptr<RectCollider>
{
public:
	Cannon();
	~Cannon();

	void Update();
	void Render(HDC hdc);

	void Move();
	void RotateBarrel();
	void Shooting();

	void SetPos(Vector2D  pos) { _body->centre = pos; }
	void AddPos(Vector2D  vec) { _body->centre += vec; }

private:
	shared_ptr<RectCollider> _body; // ������Ʈ ���� ... ����Ƽ

	float _speed = 2.0f;
	float _angle = 0.0f;
	float _ballspeed = 50.0f;

private:
	shared_ptr<class Barrel> _barrel;
	shared_ptr<class Ball> _ball;
};

// �� Render�ϸ� Cannon�� Rectó�� Rend��?