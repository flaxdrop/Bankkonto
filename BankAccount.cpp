#include "BankAccount.h"

BankAccount::BankAccount(int accountnumber, int balance)
    : m_accountNumber ( accountnumber ), m_balance ( balance ) {}

int BankAccount::getBalance() const
{
    std::shared_lock<std::shared_mutex> lock(m_accountMutex);

    int randomValue{Random::get_random(1, 3)};
    std::this_thread::sleep_for(std::chrono::seconds(randomValue));
    return m_balance;
}

void BankAccount::deposit(int amount)
{
    std::lock_guard<std::shared_mutex> lock(m_accountMutex);
    
    int randomValue{Random::get_random(1, 3)};
    std::this_thread::sleep_for(std::chrono::seconds(randomValue));
    m_balance += amount;
}

void BankAccount::withdraw(int amount)
{
    std::lock_guard<std::shared_mutex> lock(m_accountMutex);
    
    int randomValue{Random::get_random(1, 3)};
    std::this_thread::sleep_for(std::chrono::seconds(randomValue));
    m_balance -= amount;
}
int BankAccount::getAccountNumber()
{
    std::shared_lock<std::shared_mutex> lock(m_accountMutex);
    
    int randomValue{Random::get_random(1, 3)};
    std::this_thread::sleep_for(std::chrono::seconds(randomValue));
    return m_accountNumber;
}
