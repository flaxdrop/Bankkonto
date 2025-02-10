#include "BankAccount.h"

//! @brief List constructor for bank accounts
BankAccount::BankAccount(int accountnumber, int balance)
    : m_accountNumber ( accountnumber ), m_balance ( balance ) {}


const int BankAccount::getBalance() const
{
    std::shared_lock<std::shared_mutex> lock(m_accountMutex);

    int randomValue{Random::get_random(100, 1000)};
    std::this_thread::sleep_for(std::chrono::milliseconds(randomValue));
    return m_balance;
}


//! Throws invalid_argument if amount is 0 or less.
//!
void BankAccount::deposit( int amount )
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


//! Throws invalid_argument if amount is 0 or less,
//! and runtime_error if the account doesn't have enough money. 
//!
void BankAccount::withdraw(int amount)
{
    std::lock_guard<std::shared_mutex> lock(m_accountMutex);
    
    if (amount > 0 && m_balance - amount >= 0) {      
        int randomValue{Random::get_random(100, 1000)};
        std::this_thread::sleep_for(std::chrono::milliseconds(randomValue));
        m_balance -= amount;
    }
    else
    {
        if ( amount <= 0 )
        {
            throw std::invalid_argument(
                "Amount to withdraw must be greater than 0"
            );
        } 
        else if ( m_balance - amount < 0 ) 
        {
            throw std::runtime_error(
                "Not enough money on account"
            );
        }
    }
}


//! Throws invalid_argument if amount is 0 or less,
//! runtime_error if the pointer can't be dereferenced,
//! and runtime_error if the account doesn't have enough money. 
//!
void BankAccount::transfer(int amount, std::shared_ptr<BankAccount> otherAccount)
{
    if( amount <= 0 ) 
    {
        throw std::invalid_argument("Amount to transfer must be 1 or more.");
    };
    if( !otherAccount ) 
    {
        throw std::runtime_error("Failed to dereference pointer to other account.");
    };
    //Attempt to withdraw from current account. Return if it fails
    try
    {
        withdraw(amount);
    }
    catch (std::invalid_argument e)
    {
        throw e;
    }
    //Deposit to the other account
    try
    {
        otherAccount->deposit(amount);
    }
    catch ( std::invalid_argument e )
    {
        throw e;
    }
}


const int BankAccount::getAccountNumber() const
{
    std::shared_lock<std::shared_mutex> lock(m_accountMutex);
    
    int randomValue{Random::get_random(100, 1000)};
    std::this_thread::sleep_for(std::chrono::milliseconds(randomValue));
    return m_accountNumber;
}

