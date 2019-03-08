#pragma once

#include <random>

//utility for number randomization
class Random
{
	//class initializing the random numbers engine
	class RandomImpl {
	public:
		std::random_device rd;
		std::uniform_real_distribution<float> distf;
		std::mt19937 engine;
		RandomImpl();
	};

	//the instance of random numbers generator data
	static RandomImpl impl;

public:
	static int nextInt();
	static int nextInt(int bound);
	static int nextInt(int min, int max);
	static bool nextBool();
};

