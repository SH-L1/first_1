#include "framework.h"
#include "Random.h"

mt19937 Random::rng(random_device{}());

int Random::RandomInt(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);

	return dist(rng);
}

float Random::RandomFloat(float min, float max)
{
	uniform_real_distribution<float> dist(min, max);

	return dist(rng);
}

Vector Random::RandomCord(Vector halfSize)
{
	int direction = RandomInt(0, 3);
	int x = 0, y = 0;

	switch (direction)
	{
	case 0:
		x = -1.0f * halfSize.x;
		y = RandomInt(-1.0f * halfSize.y, WIN_HEIGHT + halfSize.y);
		break;
	case 1:
		x = WIN_WIDTH + halfSize.x;
		y = RandomInt(-1.0f * halfSize.y, WIN_HEIGHT + halfSize.y);
		break;
	case 2:
		x = RandomInt(-1.0f * halfSize.x, WIN_WIDTH + halfSize.x);
		y = WIN_HEIGHT + halfSize.y;
		break;
	case 3:
		x = RandomInt(-1.0f * halfSize.x, WIN_WIDTH + halfSize.x);
		y = -1.0f * halfSize.y;
		break;
	}

	return Vector(x, y);
}
