#include "Bank.h"
#include <iostream>


void Bank::createAccount(int accountNumber, int balance)
{
    std::lock_guard<std::mutex> lock(allAccountsMutex);
    if (m_accounts.count(accountNumber) != 0)
    {
        // error message: account already exists
        return;
    }
     //BankAccount* newAccount = new BankAccount(accountNumber);
    // m_accounts.insert({accountNumber,0});
    // lockguard allAccountsMutex
    // check if account already exists
}

bool Bank::accountExists(int accountNumber)
{
    return (m_accounts.count(accountNumber) != 0);
}

void Bank::printBalance() const
{
    std::cout << "Saldo" << std::endl;
    for (const auto &account : m_accounts)
    {
        std::cout << "kontonummer: " << account.first << " saldo: " << account.second.getBalance() << std::endl;
    }
}

BankAccount *Bank::getAccount(int accountNumber)
{
    if (auto search = m_accounts.find(accountNumber); search != m_accounts.end())
        return &search->second;
    else
    {
        std::cout << "Account does not exist" << std::endl;
        return nullptr;
    }
}

std::vector<int> Bank::getAccountNumbers()
{
    std::vector<int> allAccountNumbers;
    for (auto &account : m_accounts)
    {
        allAccountNumbers.push_back(account.first);
    }
    return allAccountNumbers;
}