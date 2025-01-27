#include "Client.h"
#include <sstream>

Client::Client(const std::string &name, Bank &bank_ref, std::vector<std::string>& reports, std::mutex& report_mutex) : name(name), bank(bank_ref)
{
}
void Client::client(Bank &bank_ref, const std::string &name, std::vector<std::string>& reports, std::mutex& report_mutex)
{
    Client client(name, bank_ref, reports, report_mutex);
    std::ostringstream stream;
    std::shared_ptr<BankAccount> account_ref;
    {
        std::lock_guard<std::mutex> lock(bank_ref.allAccountsMutex);
        // populate vector with all valid accounts
        std::vector<int> existingAccounts{bank_ref.getAccountNumbers()};
        // get size of vector
        int numOfAccounts{static_cast<int>(existingAccounts.size())};
        // get random index
        int randomAccount{Random::get_random(0, numOfAccounts - 1)};
        int accountNumber = existingAccounts[randomAccount];

        account_ref = bank_ref.getAccount(accountNumber);
        if (account_ref == nullptr)
        {
            stream << "Transaction attempt " << std::chrono::system_clock::now() << " Account does not exist" << std::endl;
            std::lock_guard<std::mutex> report_lock(report_mutex);
            reports.emplace_back(stream.str());
            return;
        }
    }
    {
        // get random value for client action
        int randomValue{Random::get_random(0, 2)};
        if (randomValue == 0)
        {
            int randomAmount{Random::get_random(1, 100)};
            account_ref->deposit(randomAmount);
            stream << client.name << "deposited " << randomAmount << " kr into account " << account_ref->getAccountNumber() 
                   << ", " << std::chrono::system_clock::now() << std::endl;
            std::lock_guard<std::mutex> report_lock(report_mutex);
            reports.emplace_back(stream.str());
            // Printing is now handled by Report thread
        }
        else if (randomValue == 1)
        {
            int randomAmount{Random::get_random(1, 100)};
            if (account_ref->getBalance() >= randomAmount)
            {
                account_ref->withdraw(randomAmount);
                stream << client.name << "withdrew " << randomAmount << " kr from account " << account_ref->getAccountNumber() 
                       << ", " << std::chrono::system_clock::now() << std::endl;
                std::lock_guard<std::mutex> report_lock(report_mutex);
                reports.emplace_back(stream.str());
            }
            else
            {
                stream << "Transaction attempt " << std::chrono::system_clock::now() << "Insufficient funds" << std::endl;
                std::lock_guard<std::mutex> report_lock(report_mutex);
                reports.emplace_back(stream.str());
            }
        }
        else
        {
            stream << client.name << "checked balance in account: " << account_ref->getAccountNumber() << ". Balance: " << account_ref->getBalance() 
                   << std::chrono::system_clock::now() << std::endl;
            std::lock_guard<std::mutex> report_lock(report_mutex);
            reports.emplace_back(stream.str());
        }
    }

    return;
}