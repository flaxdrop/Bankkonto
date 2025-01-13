#include "Client.h"

void Client::client(Bank& bank_ref)
{

    // lock the bank account map
    // get random account number
    // get account reference
    // free map

    // Lock the account
    // get random amount (within a certain limits)
    // get random transaction type
    // Check if transcation possible
    // perform transaction
    // free account

    std::shared_ptr<BankAccount> account_ref;
    {
        std::lock_guard<std::mutex> lock(bank_ref.allAccountsMutex);
        
        std::vector<int> existingAccounts{bank_ref.getAccountNumbers()};
        size_t numOfAccounts{existingAccounts.size()};
        int randomAccount{Random::get_random(0, numOfAccounts - 1)};
        int accountNumber = existingAccounts[randomAccount];

        std::cout << randomAccount << "\n";

        account_ref = bank_ref.getAccount(accountNumber);
        if (account_ref == nullptr)
        {
            std::cout << "Account does not exist" << std::endl;
            return;
        }
    }
    {
        int randomValue{Random::get_random(0, 1)};
        if(randomValue == 1)
        {
            int randomAmount{Random::get_random(0, 100)};
            account_ref->deposit(randomAmount);
            std::cout << "Client deposited " << randomAmount << "sek into account " << account_ref->getAccountNumber() << "." << std::endl;
        }
        else 
        {
            int randomAmount{Random::get_random(0, 100)};
            if(account_ref->getBalance() >= randomAmount)
            {
                account_ref->withdraw(randomAmount);
                std::cout << "Client withdrew " << randomAmount << "sek from account " << account_ref->getAccountNumber() << "." << std::endl;
            }
            else
            {
                std::cout << "Insufficient funds" << std::endl;
            }
        }
    }
    return;
}