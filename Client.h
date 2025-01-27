#ifndef CHAS_BOILER1_BANKSYSTEM_CLIENT
#define CHAS_BOILER1_BANKSYSTEM_CLIENT

#include "Random.h"
#include "Bank.h"
#include <thread>
#include <mutex>
#include <random>
#include <chrono>

class Client {
    public:
    Client(const std::string& name, Bank& bank_ref, std::vector<std::string>& reports, std::mutex& report_mutex, 
    std::condition_variable& cv, std::atomic_bool& data_to_report);
 static void client(Bank& bank_ref, const std::string& name, std::vector<std::string>& reports, std::mutex& report_mutex, 
                    std::condition_variable& cv, std::atomic_bool& data_to_report);
 private:
 std::string name;
 Bank& bank;
};


#endif