#ifndef CHAS_BOILER1_BANKSYSTEM_BANKACCOUNT
#define CHAS_BOILER1_BANKSYSTEM_BANKACCOUNT

#include <iostream>
#include <mutex>
#include <map>

class BankAccount {
private:
    int balance;
    int accountNumber;
    std::mutex account_mutex;
public:
BankAccount();

    int getBalance();
    void deposit(int amount);
    void withdraw(int amount);
    int getAccountNumber();

};

#endif
