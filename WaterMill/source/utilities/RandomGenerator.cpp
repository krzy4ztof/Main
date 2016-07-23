#include "RandomGenerator.h"
#include <random> // mt19937, uniform_int_distribution
//#include <boost/random/mersenne_twister.hpp> // mt19937
//#include <boost/random/uniform_int_distribution.hpp> // uniform_int_distribution
#include<iostream> // cout

using namespace std;

namespace watermill {

    RandomGenerator::RandomGenerator(int min, int max) {
        generator = mt19937();
        distribution = uniform_int_distribution<int>(min,max);
	}


	RandomGenerator::RandomGenerator(int min, int max, int seed) {
        generator = mt19937(0);
        distribution = uniform_int_distribution<int>(min,max);
	}


	RandomGenerator::~RandomGenerator() {
	}

	void RandomGenerator::setSeed(int seed) {
	    generator.seed(seed);
	}

    int RandomGenerator::random() {
	    return distribution(generator);
	}
}
