#pragma once

// 상속 기반 클래스 : 디자인패턴
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
	void SetBD() { _barrel->SetDir(Vector2D(-1, 0)); }

private:
	shared_ptr<RectCollider> _body; // 컴포넌트 패턴 ... 유니티

	float _barrelspeed = 2.0f;
	float _angle = 0.0f;
	float _ballspeed = 0.07f;

	float _timer = 3.0f;
	float _delay = 3.0f;

private:
	shared_ptr<class Barrel> _barrel;

	int _ballCount = 30;
	vector<shared_ptr<class Ball>> _balls;
};