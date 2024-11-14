#include "framework.h"
#include "Player.h"

Player::Player()
: Creature()
{

}

Player::Player(int hp, int attack, string name)
: Creature(hp, attack, name)
{
}

Player::~Player()
{
}

void Player::RangeAttack(shared_ptr<Creature> arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == nullptr) continue;
		if (arr[i]->IsDead()) continue;

		this->Attack(arr[i]);
	}
}

