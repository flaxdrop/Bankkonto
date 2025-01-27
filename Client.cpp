#include "Client.h"
#include <sstream>

Client::Client(const std::string &name, Bank &bank_ref, std::vector<std::string> &reports, std::mutex &report_mutex,
               std::condition_variable &cv) : name(name), bank(bank_ref)
{
}
void Client::client(Bank &bank_ref, const std::string &name, std::vector<std::string> &reports, std::mutex &report_mutex,
                    std::condition_variable &cv)
{
    using clock = std::chrono::system_clock;
    Client client(name, bank_ref, reports, report_mutex, cv);
    std::ostringstream stream;
    std::shared_ptr<BankAccount> account_ref = bank_ref.getRandomAccount();

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
    {
        // get random value for client action
        int randomValue{Random::get_random(0, 3)};
        switch (randomValue)
        {
        case 0:
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
            break;
        }
        case 1:
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
            break;
        }
        case 2:
        {
            stream << client.name << "checked balance in account: " << account_ref->getAccountNumber() << ". Balance: " << account_ref->getBalance()
                   << ", " << getCurrentTime() << "\n";
            {
                std::lock_guard<std::mutex> report_lock(report_mutex);
                reports.emplace_back(stream.str());
            }
            cv.notify_one();
            break;
        }
        case 3:
        {
            std::shared_ptr<BankAccount> otherAccount = bank_ref.getRandomAccount();
            int randomAmount{Random::get_random(1, 100)};

            if (account_ref->transfer(randomAmount, otherAccount) != -1)
            {
                stream << client.name << "transfered " << randomAmount << " kr from account " << account_ref->getAccountNumber()
                       << " to account " << otherAccount->getAccountNumber() << ", " << getCurrentTime() << ".\n";
                std::lock_guard<std::mutex> report_lock(report_mutex);
                reports.emplace_back(stream.str());
            }
            else
            {
                stream << client.name << ": transfer failed.\n";
                std::lock_guard<std::mutex> report_lock(report_mutex);
                reports.emplace_back(stream.str());
            }
            break;
        }
        default:
            break;
        }

        return;
    }
}

std::string getCurrentTime()
{
    std::lock_guard<std::mutex> time_mtx(ctime_mutex);
    std::time_t t = std::time(nullptr);
    char time_string[100];
    if (std::strftime(time_string, sizeof(time_string), "%c", std::localtime(&t)))
    {
        return time_string;
    }
    else
        return "date_error";
}