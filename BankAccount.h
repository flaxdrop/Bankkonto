#ifndef CHAS_BOILER1_BANKSYSTEM_BANKACCOUNT
#define CHAS_BOILER1_BANKSYSTEM_BANKACCOUNT

#include <iostream>
#include <shared_mutex>
#include <thread>
#include <chrono>
#include <stdexcept>
#include "Random.h"

//! @brief Class for bank accounts
//! 
class BankAccount
{
private:
    int m_balance = 0;
    int m_accountNumber;
    mutable std::shared_mutex m_accountMutex;
public:
    BankAccount(int accountnumber, int balance);
    const int getBalance() const;
    void deposit(int amount);
    void withdraw(int amount);
    void transfer(int amount,std::shared_ptr<BankAccount> otherAccount);
    const int getAccountNumber() const;
};

#endif
