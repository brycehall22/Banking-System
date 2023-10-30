#pragma once
#include <string>
#include <vector> 
#include <fstream>
#include <iomanip>
using namespace std;

// Abstract base class for all accounts
class Account {
public:
  virtual ~Account() = default;
  virtual void deposit(double amount) = 0;
  virtual bool withdraw(double amount) = 0;
  virtual double getBalance() const = 0;
  virtual int getAccountID() const = 0;
  virtual string getAccountType() const = 0;
  virtual string getAccountHolder() const = 0;
  virtual void writeToLog(const string& logEntry);
  virtual string getAccountSummary() const;

protected:
  vector<string> transactionLog;
};

// Derived class for checking accounts
class CheckingAccount : public Account {
private: 
  int accountID;
  string accountHolder;
  double balance;
public:
  CheckingAccount(int accountId, string accountHolderName, double initialBalance = 0.0);
  int getAccountID() const override;
  string getAccountHolder() const override;
  double getBalance() const override;
  void deposit(double amount) override;
  bool withdraw(double amount) override;
  string getAccountType() const override;
};

// Derived class for savings accounts
class SavingsAccount : public Account {
private: 
  int accountID;
  string accountHolder;
  double balance;
  double interestRate;
public:
  SavingsAccount(int accountId, string accountHolderName, double initialBalance = 0.0, double rate = 0.0);
  int getAccountID() const override;
  string getAccountHolder() const override;
  double getBalance() const override;
  void deposit(double amount) override;
  bool withdraw(double amount) override;
  void applyInterest();
  string getAccountType() const override;
};