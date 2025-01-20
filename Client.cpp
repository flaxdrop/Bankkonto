#include "Client.h"
#include <sstream>

Client::Client(const std::string& name, Bank& bank_ref) : name(name), bank(bank_ref)
{
}
void Client::client(Bank& bank_ref, const std::string& name)
{
Client client(name, bank_ref);
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
    std::ostringstream stream;
    std::shared_ptr<BankAccount> account_ref;
    {
        std::lock_guard<std::mutex> lock(bank_ref.allAccountsMutex);
        // populate vector with all valid accounts
        std::vector<int> existingAccounts{bank_ref.getAccountNumbers()};
        // get size of vector
        int numOfAccounts{ static_cast<int>(existingAccounts.size())};
        // get random index
        int randomAccount{Random::get_random(0, numOfAccounts - 1)};
        int accountNumber = existingAccounts[randomAccount];

        // test printing
        //std::cout << "Random account: " << existingAccounts.at(randomAccount) << "\n\n";
        
        account_ref = bank_ref.getAccount(accountNumber);
        if (account_ref == nullptr)
        {
            stream << "Account does not exist" << std::endl;
            std::cout << stream.str();
            return;
        }
    }
    {
        int randomValue{Random::get_random(0, 1)};
        if(randomValue == 1)
        {
            int randomAmount{Random::get_random(1, 100)};
            account_ref->deposit(randomAmount);
            stream << client.name << "deposited " << randomAmount << " kr into account " << account_ref->getAccountNumber() << "." << std::endl;
        }
        else 
        {
            int randomAmount{Random::get_random(1, 100)};
            if(account_ref->getBalance() >= randomAmount)
            {
                account_ref->withdraw(randomAmount);
                stream << client.name << "withdrew " << randomAmount << " kr from account " << account_ref->getAccountNumber() << "." << std::endl;
            }
            else
            {
                stream << "Insufficient funds" << std::endl;
            }
        }
    }
    std::cout << stream.str();
    return;
}