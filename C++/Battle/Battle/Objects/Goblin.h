#pragma once
class Goblin : public Monster
{
public:
	Goblin(int hp, int attack, string name);
	~Goblin();

	virtual void Attack(shared_ptr<Creature> other) override;
};

