#ifndef CHAS_BOILER1_BANKSYSTEM_RANDOM
#define CHAS_BOILER1_BANKSYSTEM_RANDOM

#include <random>
#include <mutex>

namespace Random {
    std::mutex random_mutex;
    inline std::mt19937 random_generator { std::random_device{}() };
    inline int get_random(size_t min, size_t max) {
        std::lock_guard lock_random (random_mutex);
        return std::uniform_int_distribution{min, max}(random_generator);
    }
};


#endif