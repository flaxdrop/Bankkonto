#include "BankAccount.h"

BankAccount::BankAccount(int accountnumber, int balance)
    : m_accountNumber ( accountnumber ), m_balance ( balance ) {}

int BankAccount::getBalance() const
{
    std::lock_guard<std::mutex> lock(m_accountMutex);
    return m_balance;
}

void BankAccount::deposit(int amount)
{
    std::lock_guard<std::mutex> lock(m_accountMutex);
    m_balance += amount;
}

void BankAccount::withdraw(int amount)
{
    std::lock_guard<std::mutex> lock(m_accountMutex);

    m_balance -= amount;
}
int BankAccount::getAccountNumber()
{
    return m_accountNumber;
}