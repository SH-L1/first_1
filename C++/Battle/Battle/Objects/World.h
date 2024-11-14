#pragma once

#define MAX_GOBLINS 10

class World
{
public:
	World();
	~World();

	void Init();
	void Update(); 

	bool End();

	bool IsPlayersAllDead();

private:
	shared_ptr<Creature> _boss;
	vector<shared_ptr<Creature>> _players;
};

