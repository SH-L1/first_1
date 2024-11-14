#pragma once
class Creature : public enable_shared_from_this<Creature>
{
public:
	Creature();
	Creature(int hp, int attack, string name);
	virtual ~Creature();

	void PrintInfo();
	void SetInfo(int hp, int attack, string name);

	// 가상함수...
	virtual void Attack(shared_ptr<Creature> other);

	virtual void TakeDamage(shared_ptr<Creature> attacker, int amount);
	bool IsDead() { return GetHp() <= 0; }

	const int& GetHp() { return _hp; }
	void SetHp(int hp);
	const string& GetName() { return _name; }

protected:
	int _hp;
	int _attack;
	string _name;
};

