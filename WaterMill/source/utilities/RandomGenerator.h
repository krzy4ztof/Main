#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H
#include <random> // mt19937, uniform_int_distribution

namespace base_game {
	class RandomGenerator {
		public:
			RandomGenerator(int min, int max, int seed);
			RandomGenerator(int min, int max);
			virtual ~RandomGenerator();
			void setSeed(int n);

			int random();

		protected:

		private:
			std::mt19937 generator;
			std::uniform_int_distribution<int> distribution;
	};
}
#endif // RANDOMGENERATOR_H
