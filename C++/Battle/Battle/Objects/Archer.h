#pragma once

class Archer : public Player
{
public:
	Archer(int hp, int atk);
	~Archer();

	virtual void Attack(shared_ptr<Creature> a) override;

private:

};

