#ifndef CHAS_BOILER1_BANKSYSTEM_RANDOM
#define CHAS_BOILER1_BANKSYSTEM_RANDOM

#include <random>
#include <mutex>

namespace Random {
    static std::mutex random_mutex;
    inline std::mt19937 random_generator { std::random_device{}() };
    inline int get_random(int min, int max) {
        std::lock_guard lock_random (random_mutex);
        return std::uniform_int_distribution{min, max}(random_generator);
    }
};


#endif