#include "Bank.h"
#include <iostream>
#include <sstream>

void Bank::createAccount(int accountNumber, int balance)
{
    std::lock_guard<std::mutex> lock(allAccountsMutex);
    if (m_accounts.count(accountNumber) != 0)
    {
        std::cout << "Error: account does not exist\n";
        return;
    }
    m_accounts.emplace(accountNumber, std::make_shared<BankAccount>(accountNumber, balance));
}

void Bank::deleteAccount(int accountNumber)
{
    if (m_accounts.count(accountNumber) == 0)
    {
        std::cout << "Error: account does not exist\n";
        return;
    }
    // aquire the account pointer
    auto account = getAccount(accountNumber);
    // lock the bank mutex
    std::lock_guard lock(allAccountsMutex);
    if (account->getBalance() != 0)
    {
        std::cout << "Error: account " << accountNumber << " is not empty\n";
        return;
    }
    // add user prompt? Delete account #accountNumber, Are you sure (Y/n)
    m_accounts.erase(accountNumber);
    std::cout << "Account " << accountNumber << " deleted\n";
}

bool Bank::accountExists(int accountNumber)
{
    return (m_accounts.count(accountNumber) != 0);
}

void Bank::printBalances() const
{
    std::cout << "Saldo" << std::endl;
    for (const auto &account : m_accounts)
    {
        std::cout << "kontonummer: " << account.first << " saldo: " << account.second->getBalance() << std::endl;
    }
}

std::shared_ptr<BankAccount> Bank::getAccount(int accountNumber)
{
    auto search = m_accounts.find(accountNumber);
    if (search != m_accounts.end())
    {
        return search->second;
    }
    return nullptr;
}

std::shared_ptr<BankAccount> Bank::getRandomAccount()
{
    std::ostringstream stream;
    std::shared_ptr<BankAccount> account_ref;
    {
        std::lock_guard<std::mutex> lock(allAccountsMutex);
        // populate vector with all valid accounts
        std::vector<int> existingAccounts{getAccountNumbers()};
        // get size of vector
        int numOfAccounts{static_cast<int>(existingAccounts.size())};
        // get random index
        int randomAccount{Random::get_random(0, numOfAccounts - 1)};
        int accountNumber = existingAccounts[randomAccount];

        account_ref = getAccount(accountNumber);
        if (account_ref == nullptr)
        {
            stream << "Account does not exist" << std::endl;
            std::cout << stream.str();
            return nullptr;
        }
    }
    return account_ref;
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