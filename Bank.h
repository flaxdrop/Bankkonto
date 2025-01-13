#ifndef CHAS_BOILER1_BANKSYSTEM_BANK
#define CHAS_BOILER1_BANKSYSTEM_BANK

#include "BankAccount.h"
#include <iostream>
#include <mutex>
#include <map>
#include <vector>
#include <memory>


class Bank{
    private:
        std::map<int, std::shared_ptr<BankAccount>> m_accounts;
    public:
        Bank(){};
        std::mutex allAccountsMutex;
        void createAccount(int accountNumber, int balance);
        bool accountExists(int accountNumber);
        void printBalance()const;
        std::shared_ptr<BankAccount> getAccount(int accountNumber);
        // int getBalance(int accountNumber) const;
        std::vector<int> getAccountNumbers();
};

#endif