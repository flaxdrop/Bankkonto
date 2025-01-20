#ifndef CHAS_BOILER1_BANKSYSTEM_BANKACCOUNT
#define CHAS_BOILER1_BANKSYSTEM_BANKACCOUNT

#include <iostream>
#include <shared_mutex>
#include <thread>
#include <chrono>
#include "Random.h"

class BankAccount
{
private:
    int m_balance;
    int m_accountNumber;
    mutable std::shared_mutex m_accountMutex;
public:
    BankAccount(int accountnumber, int balance = 0);
    int getBalance() const;
    void deposit(int amount);
    void withdraw(int amount);
    int getAccountNumber();
};

#endif
