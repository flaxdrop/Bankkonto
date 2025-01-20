#include "Bank.h"
#include "Client.h"
#include "Globals.h"
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
    for (const auto& name : clientNames)
    {
        threads.emplace_back(std::thread(Client::client, std::ref(bank), name));
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    return 0;
}