#pragma once

#include <chrono>
#include <functional>
#include <random>

namespace globalRNG {
#ifdef _MSC_VER
	extern std::_Binder<std::_Unforced, std::uniform_real_distribution<float>, std::mt19937 &> rng;
#else
	extern std::_Bind<std::uniform_real_distribution<float>(std::mt19937 &)> rng;
#endif
}
