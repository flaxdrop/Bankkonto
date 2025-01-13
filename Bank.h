#ifndef CHAS_BOILER1_BANKSYSTEM_BANK
#define CHAS_BOILER1_BANKSYSTEM_BANK

#include "BankManager.h"
#include <iostream>
#include <mutex>
#include <map>


class Bank{
    private:
        std::map<int, BankAccount> accounts;
    public:
        std::mutex create_account_mutex;
        void createAccount(int accountNumber);
        void printBalance();
    

};

#endif