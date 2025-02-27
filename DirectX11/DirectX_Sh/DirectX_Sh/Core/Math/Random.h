#pragma once

class Random
{
public:
	static int RandomInt(int min, int max);
	static float RandomFloat(float min, float max);
	static Vector RandomCord(Vector halfSize);

private:
	static mt19937 rng;
};