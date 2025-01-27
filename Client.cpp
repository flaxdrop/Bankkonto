#include "Client.h"
#include <sstream>

Client::Client(const std::string &name, Bank &bank_ref, std::vector<std::string>& reports, std::mutex& report_mutex, 
                std::condition_variable& cv) : name(name), bank(bank_ref)
{
}
void Client::client(Bank &bank_ref, const std::string &name, std::vector<std::string>& reports, std::mutex& report_mutex, 
                    std::condition_variable& cv)
{
    using clock = std::chrono::system_clock;
    Client client(name, bank_ref, reports, report_mutex, cv);
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

            stream << " Account does not exist. Transaction attempt " << getCurrentTime() << "\n";
            {
                std::lock_guard<std::mutex> report_lock(report_mutex);
                reports.emplace_back(stream.str());
            }
            cv.notify_one();
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
                   << ", " << getCurrentTime() << "\n";
            {
                std::lock_guard<std::mutex> report_lock(report_mutex);
                reports.emplace_back(stream.str());
            }
            cv.notify_one();
        }
        else if (randomValue == 1)
        {
            int randomAmount{Random::get_random(1, 100)};
            if (account_ref->getBalance() >= randomAmount)
            {
                account_ref->withdraw(randomAmount);
                stream << client.name << "withdrew " << randomAmount << " kr from account " << account_ref->getAccountNumber() 
                       << ", " << getCurrentTime() << "\n";
                {
                    std::lock_guard<std::mutex> report_lock(report_mutex);
                    reports.emplace_back(stream.str());
                }
                cv.notify_one();
            }
            else
            {
                stream << "Insufficient funds. Transaction attempt " << getCurrentTime() << "\n";
                {
                    std::lock_guard<std::mutex> report_lock(report_mutex);
                    reports.emplace_back(stream.str());
                }
                cv.notify_one();               
            }
        }
        else
        {
            stream << client.name << "checked balance in account: " << account_ref->getAccountNumber() << ". Balance: " << account_ref->getBalance() 
                   << ", " << getCurrentTime() << "\n";
            {
                std::lock_guard<std::mutex> report_lock(report_mutex);
                reports.emplace_back(stream.str());
            }
            cv.notify_one();
        }
    }

    return;
}


std::string Client::getCurrentTimeAndNewline(){
    using clock = std::chrono::system_clock;
    time_t now = clock::to_time_t(clock::now());
    char buffer[50];
    // OBS! ctime_r lägger till en newline. GRR!
    // Jag vet hur man fixar med std::strftime men osäker på om den är trådsäker
    ctime_r(&now, buffer);      
    return buffer;
}

std::string getCurrentTime(){
    std::lock_guard<std::mutex> time_mtx(ctime_mutex);
    std::time_t t = std::time(nullptr);
    char time_string[100]; 
    if (std::strftime(time_string, sizeof(time_string), "%c", std::localtime(&t))){
        return time_string;
    }
    else return "date_error";
}