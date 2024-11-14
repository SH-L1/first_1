#pragma once
class Knight : public Player
{
public:
	Knight(int hp, int atk, string name = "");
	~Knight();
	
	virtual void Attack(shared_ptr<Creature> other) override;

private:
	int _maxHp;
};

