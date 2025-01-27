#include "Client.h"
#include <sstream>

Client::Client(const std::string &name, Bank &bank_ref) : name(name), bank(bank_ref)
{
}
void Client::client(Bank &bank_ref, const std::string &name)
{
    Client client(name, bank_ref);
    std::ostringstream stream;
    std::shared_ptr<BankAccount> account_ref = bank_ref.getRandomAccount();
    {
        // get random value for client action
        int randomValue{Random::get_random(0, 3)};
        switch (randomValue)
        {
        case 0:
        {
            int randomAmount{Random::get_random(1, 100)};
            account_ref->deposit(randomAmount);
            stream << client.name << "deposited " << randomAmount << " kr into account " << account_ref->getAccountNumber() << "." << std::endl;
            std::cout << stream.str();
            break;
        }
        case 1:
        {
            int randomAmount{Random::get_random(1, 100)};
            if (account_ref->getBalance() >= randomAmount)
            {
                account_ref->withdraw(randomAmount);
                stream << client.name << "withdrew " << randomAmount << " kr from account " << account_ref->getAccountNumber() << "." << std::endl;
                std::cout << stream.str();
            }
            else
            {
                stream << "Insufficient funds" << std::endl;
                std::cout << stream.str();
            }
            break;
        }
        case 2:
        {
            stream << client.name << "checked balance in account: " << account_ref->getAccountNumber() << ". Balance: " << account_ref->getBalance() << ".\n";
            std::cout << stream.str();
            break;
        }
        case 3:
        {
            std::shared_ptr<BankAccount> otherAccount = bank_ref.getRandomAccount();
            int randomAmount{Random::get_random(1, 100)};

            if (account_ref->transfer(randomAmount, otherAccount) != -1)
            {
                stream << client.name << "transfered " << randomAmount << " kr from account " << account_ref->getAccountNumber() << " to account " << otherAccount->getAccountNumber() << ".\n";
                std::cout << stream.str();
            }
            else
            {
                stream << client.name << ": transfer failed.\n";
                std::cout << stream.str();
            }
            break;
        }
        default:
            break;
        }
    }

    return;
}