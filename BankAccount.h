#ifndef CHAS_BOILER1_BANKSYSTEM_BANKACCOUNT
#define CHAS_BOILER1_BANKSYSTEM_BANKACCOUNT

#include <iostream>
#include <mutex>
#include <map>

class BankAccount
{
private:
    int m_balance;
    int m_accountNumber;
    mutable std::mutex m_accountMutex;
public:
    BankAccount(int accountnumber, int balance = 0);
    int getBalance() const;
    void deposit(int amount);
    void withdraw(int amount);
    int getAccountNumber();
};

#endif
