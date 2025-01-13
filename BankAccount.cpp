#include "BankAccount.h"


BankAccount::BankAccount(int accountnumber)
    : m_accountNumber ( accountnumber ), m_balance ( 0 ) {}

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
    //Vi kanske ska göra denna balancecheck innan withdraw körs?

    std::lock_guard<std::mutex> lock(m_accountMutex);
    if(m_balance >= amount)
    {
        m_balance -= amount;
        std::cout << amount << "withdrawn from account: " << m_accountNumber << std::endl; 
    }
    else
    {
        std::cout << "Insufficient funds" << std::endl;
    }
}
int BankAccount::getAccountNumber()
{
    return m_accountNumber;
}