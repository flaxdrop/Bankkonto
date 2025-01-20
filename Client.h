#ifndef CHAS_BOILER1_BANKSYSTEM_CLIENT
#define CHAS_BOILER1_BANKSYSTEM_CLIENT

#include "Random.h"
#include "Bank.h"
#include <thread>
#include <mutex>
#include <random>

class Client {
    public:
    Client(const std::string& name, Bank& bank_ref);
 static void client(Bank& bank_ref, const std::string& name);
 private:
 std::string name;
 Bank& bank;
};


#endif