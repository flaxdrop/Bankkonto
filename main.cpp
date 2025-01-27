#include "Bank.h"
#include "Client.h"
#include "BankAccount.h"
#include "Random.h"
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
    std::vector<std::string> clientNames = {"Alice ", "Bob ", "Charlie ", "David ", "Eve ", "Frank ", "Grace ", "Heidi ", "Ivan ", "Judy ", "john "};

    std::mutex report_mutex;
    std::vector<std::string> reports;
    std::condition_variable cv;
    // std::mutex cv_mutex;
    bool data_to_report { false };

    for (const auto& name : clientNames)
    {
        threads.emplace_back(std::thread(Client::client, std::ref(bank), name, 
                             std::ref(reports), std::ref(report_mutex), std::ref(cv), std::ref(data_to_report)));
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    std::vector<int> accountNumbers = bank.getAccountNumbers();
    std::cout << "Account balances: \n";
    for(int i = 0; i < accountNumbers.size(); i++)
    {
        std::cout << "Account " << accountNumbers.at(i) << " : "<< bank.getAccount(accountNumbers.at(i))->getBalance() << " kr. \n";
    }
    return 0;
}