#include "accounts.h"

// Implementations for Account
string Account::getAccountSummary() const {
    string filename = "Account_" + to_string(getAccountID()) + "_Log.txt";
    ifstream inFile(filename);

    stringstream summary; // Use stringstream for easier formatting
    summary << fixed << setprecision(2); // Set precision for floating point numbers
    summary << "Account Summary for " << getAccountHolder() << "\n";
    summary << "Account ID: " << getAccountID() << "\n";
    summary << "Account Type: " << getAccountType() << "\n";
    summary << "Balance: $" << getBalance() << "\n"; // Format balance correctly
    summary << "Transaction Log: \n";

    string line;
    while (getline(inFile, line)) {
        summary << "  - " << line << "\n";
    }
    inFile.close();
    
    return summary.str(); // Convert the stringstream to a string and return it
}

void Account::writeToLog(const string& logEntry) {
    string filename = "Account_" + to_string(getAccountID()) + "_Log.txt";
    ofstream outFile(filename, ios::app); // Open in append mode
    if (outFile.is_open()) {
        outFile << fixed << setprecision(2) << logEntry << endl;
        outFile.close();
    }
}

// Implementations for CheckingAccount
CheckingAccount::CheckingAccount(int accountId, string accountHolderName, double initialBalance) {
    accountID = accountId;
    accountHolder = accountHolderName;
    balance = initialBalance;
}

int CheckingAccount::getAccountID() const {
      return accountID;
  }

string CheckingAccount::getAccountHolder() const {
      return accountHolder;
  }

double CheckingAccount::getBalance() const {
      return balance;
  }

void CheckingAccount::deposit(double amount) {
      balance += amount;
      ostringstream logStream;
      logStream << fixed << setprecision(2) << "Deposited " << amount << ", New balance: " << getBalance();
      writeToLog(logStream.str());
  }

bool CheckingAccount::withdraw(double amount) {
      ostringstream logStream;
      if (amount <= balance) {
          balance -= amount;
          logStream << fixed << setprecision(2) << "Withdrew " << amount << ", New balance: " << getBalance();
          writeToLog(logStream.str());
          return true;
      } else {
          logStream << fixed << setprecision(2) << "Failed to withdraw " << amount << ", Insufficient balance";
          writeToLog(logStream.str());
          return false;
      }
  }

string CheckingAccount::getAccountType() const {
    return "Checking";
  }

// Implementations for SavingsAccount
SavingsAccount::SavingsAccount(int accountId, string accountHolderName, double initialBalance, double rate) {
    accountID = accountId;
    accountHolder = accountHolderName;
    balance = initialBalance;
    interestRate = rate;
}

int SavingsAccount::getAccountID() const {
      return accountID;
  }

string SavingsAccount::getAccountHolder() const {
      return accountHolder;
  }

double SavingsAccount::getBalance() const {
      return balance;
  }

void SavingsAccount::deposit(double amount) {
      balance += amount;
      ostringstream logStream; 
      logStream << fixed << setprecision(2) << "Deposited " << amount << ", New balance: " << getBalance();
      writeToLog(logStream.str());
  }

bool SavingsAccount::withdraw(double amount) {
      ostringstream logStream;
      if (amount <= balance) {
          balance -= amount;
          logStream << fixed << setprecision(2) << "Withdrew " << amount << ", New balance: " << getBalance();
          writeToLog(logStream.str());
          return true;
      } else {
          logStream << fixed << setprecision(2) << "Failed to withdraw " << amount << ", Insufficient balance";
          writeToLog(logStream.str());
          return false;
      }
  }

void SavingsAccount::applyInterest() {
      ostringstream logStream;
      balance += balance * interestRate;
      logStream << fixed << setprecision(2) << "Applied interest, New balance: " << getBalance();
      writeToLog(logStream.str());
  }

string SavingsAccount::getAccountType() const {
    return "Savings";
  }