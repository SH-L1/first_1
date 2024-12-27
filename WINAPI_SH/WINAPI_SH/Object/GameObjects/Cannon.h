#pragma once

class Ball;

// 상속 기반 클래스 : 디자인패턴
class Cannon// : public shared_ptr<RectCollider>
{
public:
	Cannon();
	Cannon(int hp, int atk);
	~Cannon();

	void Update();
	void Render(HDC hdc);

	void Move();
	void RotateBarrel();
	void Shooting(bool& turn);

	shared_ptr<Ball> FindActiveBall();

	void SetPos(Vector2D pos) { _body->centre = pos; }
	void AddPos(Vector2D vec) { _body->centre += vec; }

	vector<shared_ptr<Ball>> GetBalls() { return _balls; }

	bool IsCollision_Ball(shared_ptr<Ball> ball);
	void TakeDamage(int amount);

	bool isActive = true;

private:
	shared_ptr<RectCollider> _body; // 컴포넌트 패턴 ... 유니티

	float _barrelspeed = 2.0f;
	float _angle = 0.0f;
	float _ballspeed = 0.07f;

	float _timer = 3.0f;
	float _delay = 3.0f;
	float _holdTime = 0.0f;

private:
	shared_ptr<class Barrel> _barrel;

	int _ballCount = 30;
	vector<shared_ptr<class Ball>> _balls;

private:
	int _hp;
	int _atk;
};