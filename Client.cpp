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

    BankAccount *account_ref;
    {
        std::lock_guard<std::mutex> lock(bank_ref.allAccountsMutex);
        // populate vector with all valid accounts
        std::vector<int> existingAccounts{bank_ref.getAccountNumbers()};
        // get size of vector
        int numOfAccounts{ static_cast<int>(existingAccounts.size())};
        // get random index
        int randomAccount{Random::get_random(0, numOfAccounts - 1)};

        // test printing
        std::cout << "Random account: " << existingAccounts.at(randomAccount) << "\n\n";

        // account_ref = bank_ref.getAccount(randomAccount);
        // if (account_ref == nullptr)
        //     return;
    }

    {
        std::cout << "Client doing transaction!" << std::endl;
    }
    return;
}