#include "BankAccount.h"


BankAccount::BankAccount()
{

}

int BankAccount::getBalance()
{
    return balance;
}

void BankAccount::deposit(int amount)
{
    balance += amount;
}

void BankAccount::withdraw(int amount)
{
    //Vi kanske ska göra denna balancecheck innan withdraw körs?

    std::lock_guard<std::mutex> lock(account_mutex);
    if(balance >= amount)
    {
        balance -= amount;
        std::cout << amount << "withdrawn from account: " << accountNumber << std::endl; 
    }
    else
    {
        std::cout << "Insufficient funds" << std::endl;
    }
}
int BankAccount::getAccountNumber()
{
    return accountNumber;
}