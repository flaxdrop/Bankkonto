#include "Bank.h"
#include "Client.h"
#include "Globals.h"
#include "BankAccount.h"
#include "Random.h"

int main()
{
    Bank bank;

    for (int i = 1; i <= 5; ++i)
    {
        bank.createAccount(i * 1000, 1000);
    }

    // for (int i = 0; 0 < 10; i++)
    // {
    //     Client(bank);
    // }

    
    std::thread user1(Client::Client, std::ref(bank));
    std::thread user2(Client::Client, std::ref(bank));
    std::thread user3(Client::Client, std::ref(bank));
    std::thread user4(Client::Client, std::ref(bank));
    std::thread user5(Client::Client, std::ref(bank));
    std::thread user6(Client::Client, std::ref(bank));
    std::thread user7(Client::Client, std::ref(bank));
    std::thread user8(Client::Client, std::ref(bank));
    std::thread user9(Client::Client, std::ref(bank));
    std::thread user10(Client::Client, std::ref(bank));

    user1.join();
    user2.join();
    user3.join();
    user4.join();
    user5.join();
    user6.join();
    user7.join();
    user8.join();
    user9.join();
    user10.join();


    return 0;
}