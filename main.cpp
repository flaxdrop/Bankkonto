#include "Bank.h"
#include "Client.h"
#include "BankAccount.h"
#include "Random.h"
#include "Report.h"
#include <vector>
#include <string>
#include <thread>
#include <sstream>

int main()
{
    Bank bank;

    for (int i = 1; i <= 5; ++i)
    {
        bank.createAccount(i * 1000, 1000);
    }
    
    std::vector<std::thread> threads;
    std::vector<std::string> clientNames = {"Alice ", "Bob ", "Charlie ", "David ", "Eve ", "Frank ", "Grace ", "Heidi ", "Ivan ", "Judy ", "John "};
    std::string reportsFileName { generate_filename() };

    std::vector<std::string> reports;
    std::mutex reportMutex;
    std::condition_variable reportAvailable;
    std::atomic_bool reportsLeftToDo { true };

    // Create threads
    std::thread reportthread(Report::report, std::ref(reports), std::ref(reportMutex), std::ref(reportAvailable), 
                             std::ref(reportsLeftToDo), std::ref(reportsFileName));
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    for (const auto& name : clientNames)
    {
        threads.emplace_back(std::thread(Client::client, std::ref(bank), name, 
                             std::ref(reports), std::ref(reportMutex), std::ref(reportAvailable)));
    }


    for (auto& thread : threads)
    {
        thread.join();
    }

    std::vector<int> accountNumbers = bank.getAccountNumbers();
    std::ostringstream balanceStream;
    balanceStream << "\nAccount balances: \n";
    for(int i = 0; i < accountNumbers.size(); i++)
    {
        balanceStream << "Account " << accountNumbers.at(i) << " : " 
        << bank.getAccount(accountNumbers.at(i))->getBalance() << " kr. \n";
    }
    {
        std::lock_guard<std::mutex> rep(reportMutex);
        reports.emplace_back(balanceStream.str());
    }
    reportAvailable.notify_one();

    reportsLeftToDo = false;
    reportthread.join();

    return 0;
}
