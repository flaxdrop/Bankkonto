#ifndef CHAS_BOILER1_BANKSYSTEM_CLIENT
#define CHAS_BOILER1_BANKSYSTEM_CLIENT

#include "Random.h"
#include "Bank.h"
#include <thread>
#include <mutex>
#include <random>
#include <chrono>
#include <atomic>
#include <ctime>
#include <cstring>

inline std::mutex ctime_mutex;
std::string getCurrentTime();

namespace Client {
    
    static void client(Bank& bank_ref, const std::string& name, std::vector<std::string>& reports, std::mutex& report_mutex, 
                std::condition_variable& cv);
};


#endif