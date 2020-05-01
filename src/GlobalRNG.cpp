#include <random>
#include <functional>

namespace globalRNG
{
	std::random_device rd{};

	// Use Mersenne twister engine to generate pseudo-random numbers.
	std::mt19937 engine{ rd() };

	// "Filter" MT engine's output to generate pseudo-random float values,
	// **uniformly distributed** on the closed interval [0, 1].
	// (Note that the range is [inclusive, inclusive].)
#ifdef _MSC_VER
	auto rng = std::bind(std::uniform_real_distribution<float>{ 0.0F, 1.0F }, engine);
#elif defined(_WIN32) || defined(WIN32)
	auto rng = std::bind(std::uniform_real_distribution<float>{ 0.0F, 1.0F }, std::cref(engine));
#endif
}