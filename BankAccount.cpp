#include "BankAccount.h"

BankAccount::BankAccount(int accountnumber, int balance)
    : m_accountNumber(accountnumber), m_balance(balance) {}

int BankAccount::getBalance() const
{
    std::shared_lock<std::shared_mutex> lock(m_accountMutex);

    if (m_balance > 0)
    {

        int randomValue{Random::get_random(100, 1000)};
        std::this_thread::sleep_for(std::chrono::milliseconds(randomValue));
        return m_balance;
    }
    else
    {
        throw std::invalid_argument("Balance can't be less than 0");
    }
}

void BankAccount::deposit(int amount)
{
    std::lock_guard<std::shared_mutex> lock(m_accountMutex);

    if (amount > 0)
    {
        int randomValue{Random::get_random(100, 1000)};
        std::this_thread::sleep_for(std::chrono::milliseconds(randomValue));
        m_balance += amount;
    }
    else
    {
        throw std::invalid_argument("Amount to deposit can't be less than 0");
    }
}

int BankAccount::withdraw(int amount)
{
    std::lock_guard<std::shared_mutex> lock(m_accountMutex);

    if (amount > 0 && m_balance - amount >= 0)
    {
        int randomValue{Random::get_random(100, 1000)};
        std::this_thread::sleep_for(std::chrono::milliseconds(randomValue));
        m_balance -= amount;
        return amount;
    }
    else
        return -1;
}

int BankAccount::transfer(int amount, std::shared_ptr<BankAccount> otherAccount)
{
    if (amount <= 0)
        return -1;
    {
        // Attempt to withdraw from current account. Return if it fails
        if (withdraw(amount) == -1)
            return -1;
    }
    // Deposit to the other account
    otherAccount->deposit(amount);
    return amount;
}

int BankAccount::getAccountNumber()
{
    std::shared_lock<std::shared_mutex> lock(m_accountMutex);

    int randomValue{Random::get_random(100, 1000)};
    std::this_thread::sleep_for(std::chrono::milliseconds(randomValue));
    return m_accountNumber;
}
