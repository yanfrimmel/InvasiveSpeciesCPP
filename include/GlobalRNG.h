#pragma once

#include <random>
#include <chrono>
#include <functional>

namespace globalRNG
{
	extern std::_Binder<std::_Unforced, std::uniform_real_distribution <float>, std::mt19937&> rng;
}