#include "Bank.h"
#include "Client.h"
#include "BankAccount.h"
#include "Random.h"
#include "Report.h"
#include <vector>
#include <string>
#include <thread>

int main()
{
    Bank bank;

    for (int i = 1; i <= 5; ++i)
    {
        bank.createAccount(i * 1000, 1000);
    }
    
    std::vector<std::thread> threads;
    std::vector<std::string> clientNames = {"Alice ", "Bob ", "Charlie ", "David ", "Eve ", "Frank ", "Grace ", "Heidi ", "Ivan ", "Judy ", "John "};
    std::string filename { generate_filename() };

    std::vector<std::string> reports;
    std::mutex report_mutex;
    std::condition_variable cv;
    std::atomic_bool reports_left_to_do { true };

    // Create threads
    std::thread reportthread(Report::report, std::ref(reports), std::ref(report_mutex), std::ref(cv), 
                             std::ref(reports_left_to_do), std::ref(filename));
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    for (const auto& name : clientNames)
    {
        threads.emplace_back(std::thread(Client::client, std::ref(bank), name, 
                             std::ref(reports), std::ref(report_mutex), std::ref(cv)));
    }


    for (auto& thread : threads)
    {
        thread.join();
    }

    // Possible data race now that Report is running?
    std::vector<int> accountNumbers = bank.getAccountNumbers();
    std::ostringstream balance_stream;
    balance_stream << "\nAccount balances: \n";
    for(int i = 0; i < accountNumbers.size(); i++)
    {
        balance_stream << "Account " << accountNumbers.at(i) << " : "<< bank.getAccount(accountNumbers.at(i))->getBalance() << " kr. \n";
    }
    {
        std::lock_guard<std::mutex> rep(report_mutex);
        reports.emplace_back(balance_stream.str());
    }
    cv.notify_one();

    reports_left_to_do = false;
    reportthread.join();

    return 0;
}