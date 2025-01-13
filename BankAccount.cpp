#include "BankAccount.h"

BankAccount::BankAccount(int accountnumber)
    : m_accountNumber(accountnumber), m_balance(200) {}

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
    // Vi kanske ska göra denna balancecheck innan withdraw körs?

    std::lock_guard<std::mutex> lock(m_accountMutex);

    m_balance -= amount;
}
int BankAccount::getAccountNumber()
{
    return m_accountNumber;
}