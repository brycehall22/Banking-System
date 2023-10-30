#include "fileOperations.h"
#include "accounts.h"

void saveToFile(const map<int, Account*>& accounts) {
    ofstream outFile("accounts.txt");
    if (!outFile.is_open()) {
        cerr << "Error: Could not open accounts.txt for writing.\n";
        return;
    }

    for (const auto& [id, account] : accounts) {
        if (account == nullptr) {
            cerr << "Warning: Null account pointer encountered. Skipping..." << endl;
            continue;
        }
        outFile << account->getAccountID() << " "
                << account->getAccountType() << " "
                << account->getAccountHolder() << " "
                << account->getBalance() << "\n";
    }
    outFile.close();
}

void loadFromFile(map<int, Account*>& accounts, int& accountIdCounter) {
    ifstream inFile("accounts.txt");
    if (!inFile.is_open()) {
        cerr << "Warning: Could not open accounts.txt. Starting with an empty account list.\n";
        return;
    }
    int id;
    string type, holder;
    double balance;
    int highestId = 0; // To keep track of the highest ID loaded
    while (inFile >> id >> type >> holder >> balance) {
        Account* account = nullptr;
        if (type == "Checking") {
            account = new CheckingAccount(id, holder, balance);
        } else if (type == "Savings") {
            account = new SavingsAccount(id, holder, balance, 0.05); // 0.05 is a default interest rate
        }
        if (account != nullptr) {
            accounts[id] = account;
            if (id > highestId) {
                highestId = id;
            }
        } else {
            cerr << "Warning: Unrecognized account type '" << type << "'. Skipping..." << endl;
        }
    }
    inFile.close();
    accountIdCounter = highestId + 1; // Set the account ID counter to be one more than the highest ID loaded
}