#ifndef CHAS_BOILER1_BANKSYSTEM_CLIENT
#define CHAS_BOILER1_BANKSYSTEM_CLIENT

#include "Random.h"
#include "Bank.h"
#include <thread>
#include <mutex>
#include <random>

class Client {
    public:
 static void client(Bank& bank_ref);
};


#endif