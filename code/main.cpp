#include <iostream>
#include <sstream>
#include <limits>
#include "accounts.h"
#include "fileOperations.h"
using namespace std;

int main() {
    map<int, Account*> accounts; // store pointers to the base class Account
    int accountIdCounter = 1;
    loadFromFile(accounts, accountIdCounter);

    string input;
    while (true) {
        cout << "Welcome to the Bank Account Management System!\n"
         << "Please select an option:\n"
         << "1: Create account\n"
         << "2: Deposit\n"
         << "3: Withdraw\n"
         << "4: Check balance\n"
         << "5: Apply interest (savings account only)\n"
         << "6: View Account Summary\n"
         << "0: Exit\n";

        int option;
        cin >> option;

        // Check for invalid input
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Remove bad input
            cout << "Invalid input. Please enter a number.\n";
            continue; // Skip the rest of the loop iteration
        }

        switch (option) {
        case 1: // Create account
            {
                string name, type;
                cout << "Enter the account holder's name: ";
                cin >> name;
                cout << "Enter account type (Checking/Savings): ";
                cin >> type;

                Account* newAccount = nullptr;

                if (type == "Checking") {
                    newAccount = new CheckingAccount(accountIdCounter++, name);
                } else if (type == "Savings") {
                    newAccount = new SavingsAccount(accountIdCounter++, name);
                } else {
                    cout << "Invalid account type. Try again." << endl;
                    continue;
                }

                accounts[newAccount->getAccountID()] = newAccount;

                cout << "Account successfully created for " << name
                          << " with account ID " << newAccount->getAccountID() << ".\n";
            }
            break;
        case 2: // Deposit
            {
                int id;
                double amount;
                cout << "Enter your account ID: ";
                cin >> id;
                cout << "Enter amount to deposit: ";
                cin >> amount;

                // Search for the account
                if (accounts.find(id) != accounts.end()) {
                    // Found the account, deposit the amount
                    accounts[id]->deposit(amount);
                    cout << "Deposit successful. New balance is " 
                              << accounts[id]->getBalance() << ".\n";
                } else {
                    cout << "Account not found.\n";
                }
            }
            break;
        case 3: // Withdraw
            {
                int id;
                double amount;
                cout << "Enter your account ID: ";
                cin >> id;
                cout << "Enter amount to withdraw: ";
                cin >> amount;

                // Search for the account
                if (accounts.find(id) != accounts.end()) {
                    // Found the account, attempt to withdraw the amount
                    if (accounts[id]->withdraw(amount)) {
                        cout << "Withdrawal successful. New balance is " 
                                  << accounts[id]->getBalance() << ".\n";
                    } else {
                        cout << "Not enough balance for withdrawal.\n";
                    }
                } else {
                    cout << "Account not found.\n";
                }
            }
            break;
        case 4: // Check balance
            {
                int id;
                cout << "Enter your account ID: ";
                cin >> id;

                // Search for the account
                if (accounts.find(id) != accounts.end()) {
                    // Found the account, print the balance
                    cout << "The balance in your account is " 
                              << accounts[id]->getBalance() << ".\n";
                } else {
                    cout << "Account not found.\n";
                }
            }
            break;
        case 5: // Apply interest
            {
                int id;
                cout << "Enter your Savings account ID: ";
                cin >> id;

                if (accounts.find(id) != accounts.end()) {
                    SavingsAccount* sa = dynamic_cast<SavingsAccount*>(accounts[id]);
                    if (sa != nullptr) {
                        sa->applyInterest();
                        cout << "Interest applied. New balance is "
                                  << sa->getBalance() << ".\n";
                    } else {
                        cout << "Not a Savings account.\n";
                    }
                } else {
                    cout << "Account not found.\n";
                }
            }
            break;
        case 6: // View account summary
            {
                int id;
                cout << "Enter your account ID: ";
                cin >> id;
                if (accounts.find(id) != accounts.end()) {
                    cout << fixed << setprecision(2) << accounts[id]->getAccountSummary() << endl;
                } else {
                    cout << "Account not found.\n";
                }
            }
            break;
        case 0: // Exit
            saveToFile(accounts); // Save any new accounts
            for (const auto& account : accounts) {
                delete account.second;
            }
            return 0;
        default:
            cout << "Invalid option.\n";
        }
    }
    return 0;
}