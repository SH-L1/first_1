#include "framework.h"
#include "World.h"

World::World()
{
	Init();
}

World::~World()
{
}

void World::Init()
{
	_boss =  make_shared<Boss>(1000, 15);

	for (int i = 0; i < 10; i++)
	{
		auto k = make_shared<Knight>(rand() % 5 + 70, 10 + rand() %10, "knight" + to_string(i + 1));
		_players.push_back(k);
	}
}

void World::Update()
{
	for (int i = 0; i < _players.size(); i++)
	{
		_players[i]->Attack(_boss);
	}

	auto boss = dynamic_pointer_cast<Boss>(_boss);
	if (boss != nullptr)
		boss->BossRangeAttack();
}

bool World::End()
{
	if(_boss->IsDead() || IsPlayersAllDead())
		return true;
	return false;
}

bool World::IsPlayersAllDead()
{
	return std::all_of(_players.begin(), _players.end(), [](shared_ptr<Creature> creature) -> bool
		{
			if (creature->IsDead() == false)
				return false;
			return true;
		});
}

