#include "Client.h"
#include <sstream>

//!
//! @brief Worker function for threaded work
//! Randomly selects one of four modes simulating an client action
//! deposit, withdraw, transfer and check balance
//! Each action catches potential error
//! All actions are logged to a report
void Client::simulated_client(Bank &bank_ref, const std::string &client_name, 
                              std::vector<std::string> &reports, 
                              std::mutex &report_mutex,
                              std::condition_variable &report_available)
{
    using clock = std::chrono::system_clock;

    std::ostringstream stream;
    std::shared_ptr<BankAccount> account_ref = bank_ref.getRandomAccount();

    if (account_ref == nullptr)
    {

        stream << " Account does not exist. Transaction attempt " << get_current_time() << "\n";
        {
            std::lock_guard<std::mutex> report_lock(report_mutex);
            reports.emplace_back(stream.str());
        }
        report_available.notify_one();
        return;
    }
    else
    {
        // Generate a random value to simulate different client actions
        switch (Random::get_random(0, 3))
        {
        case 0:
        {
            int random_amount{Random::get_random(1, 100)};
            try
            {
                account_ref->deposit(random_amount);
            }
            catch (const std::invalid_argument& e)
            {
                stream <<"Failed to Deposit. Error: "<< e.what() << "\n";
                {
                    std::lock_guard<std::mutex> report_lock(report_mutex);
                    reports.emplace_back(stream.str());
                }
                report_available.notify_one();
                break;
            }

            stream << client_name << "deposited " << random_amount << " kr into account " 
                << account_ref->getAccountNumber() << ", " << get_current_time() << "\n";
            {
                std::lock_guard<std::mutex> report_lock(report_mutex);
                reports.emplace_back(stream.str());
            }
            report_available.notify_one();
            break;
        }
        case 1:
        {
            int random_amount{Random::get_random(1, 100)};
            try
            {
                account_ref->withdraw(random_amount);
            }
            catch (std::exception e)
            {
                stream <<"Failed to withdraw. Error: "<< e.what() << "\n";
                {
                    std::lock_guard<std::mutex> report_lock(report_mutex);
                    reports.emplace_back(stream.str());
                }
                report_available.notify_one();
            }
            stream << client_name << "withdrew " << random_amount << " kr from account " << account_ref->getAccountNumber()
                       << ", " << get_current_time() << "\n";
                {
                    std::lock_guard<std::mutex> report_lock(report_mutex);
                    reports.emplace_back(stream.str());
                }
                report_available.notify_one();
            break;
        }
        case 2:
        {
            stream << client_name << "checked balance in account: " << account_ref->getAccountNumber() << ". Balance: " << account_ref->getBalance()
                   << ", " << get_current_time() << "\n";
            {
                std::lock_guard<std::mutex> report_lock(report_mutex);
                reports.emplace_back(stream.str());
            }
            report_available.notify_one();
            break;
        }
        case 3:
        {
            std::shared_ptr<BankAccount> other_account = bank_ref.getRandomAccount();
            int random_amount{Random::get_random(1, 100)};

            try
            {
                account_ref->transfer(random_amount, other_account);
            }
            catch (std::exception e)
            {
                stream << client_name << ": transfer failed: Error: "<< e.what() << "\n";
                std::lock_guard<std::mutex> report_lock(report_mutex);
                reports.emplace_back(stream.str());
            }
            stream << client_name << "transfered " << random_amount << " kr from account " << account_ref->getAccountNumber()
                       << " to account " << other_account->getAccountNumber() << ", " << get_current_time() << ".\n";
                std::lock_guard<std::mutex> report_lock(report_mutex);
                reports.emplace_back(stream.str());
            break;
        }
        default:
            break;
        }
    }
}

std::string get_current_time()
{
    std::lock_guard<std::mutex> time_mtx(ctime_mutex);
    std::time_t t = std::time(nullptr);
    char time_string[100];
    if (std::strftime(time_string, sizeof(time_string), "%c", std::localtime(&t)))
    {
        return time_string;
    }
    else
        throw std::runtime_error("Invalid date");
}