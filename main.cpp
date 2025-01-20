#include "Bank.h"
#include "Client.h"
#include "BankAccount.h"
#include "Random.h"

int main()
{
    Bank bank;

    for (int i = 1; i <= 5; ++i)
    {
        bank.createAccount(i * 1000, 1000);
    }
    
    std::thread user1(Client::client, std::ref(bank));
    std::thread user2(Client::client, std::ref(bank));
    std::thread user3(Client::client, std::ref(bank));
    std::thread user4(Client::client, std::ref(bank));
    std::thread user5(Client::client, std::ref(bank));
    std::thread user6(Client::client, std::ref(bank));
    std::thread user7(Client::client, std::ref(bank));
    std::thread user8(Client::client, std::ref(bank));
    std::thread user9(Client::client, std::ref(bank));
    std::thread user10(Client::client, std::ref(bank));

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