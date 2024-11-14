#include "framework.h"
#include "Goblin.h"

Goblin::Goblin(int hp, int attack, string name)
: Monster()
{
	_hp = hp;
	_attack = attack;
	_name = name;
}

Goblin::~Goblin()
{
}

void Goblin::Attack(shared_ptr<Creature> other)
{
	Creature::Attack(other);
	cout << "°íºí¸° Attack!!" << endl;
}
