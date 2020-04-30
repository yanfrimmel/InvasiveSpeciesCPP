#pragma once

#include <chrono>
#include <functional>
#include <random>

namespace globalRNG {
#ifdef __unix__
    extern std::_Bind<std::uniform_real_distribution<float>(std::mt19937 &)> rng;
#elif defined(_WIN32) || defined(WIN32)
    extern std::_Binder<std::_Unforced, std::uniform_real_distribution<float>, std::mt19937 &> rng;
#endif
}
