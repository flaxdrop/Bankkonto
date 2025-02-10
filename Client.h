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
#include <condition_variable>

inline std::mutex ctime_mutex;
std::string get_current_time();

namespace Client
{
    void simulated_client(Bank &bank_ref, 
                          const std::string &client_name, 
                          std::vector<std::string> &reports, 
                          std::mutex &report_mutex,
                          std::condition_variable &report_available);
};

#endif