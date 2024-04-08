#include "account.h"
#include <iostream>
#include <cmath>
#include <utility>
using namespace std;
using namespace std::rel_ops;

// AccountRecord类实现
AccountRecord::AccountRecord(const Date& date, const Account* account,
                             double amount, double balance, const string& desc)
    : date(date), account(account), amount(amount), balance(balance), desc(desc) {}
void AccountRecord::show() const {
    cout << date << "\t#" << account->getId() << "\t" << amount << "\t"
         << balance << "\t" << desc << endl;
}

// Account类实现
double Account::total = 0;
Account::Account(const Date& date, const string& id) : id(id), balance(0) {
    cout << date << "\t#" << id << " created" << endl;
}
void Account::record(const Date& date, double amount, const string& desc) {
    amount = floor(amount * 100 + 0.5) / 100;
    balance += amount;
    total += amount;
    date.show();
    cout << "\t#" << id << "\t" << amount << "\t" << balance << "\t"
         << desc << endl;
}
void Account::error(const string& msg) const {
    cout << "Error(#" << id << "): " << msg << endl;
}
void Account::show(ostream& out) const {
    cout << "# " << id << "\tBalance: " << balance << endl;
}

// SavingsAccount类实现
SavingsAccount::SavingsAccount(const Date& date, const string& id, double rate)
    : Account(date, id), rate(rate), acc(date, 0) {}
void SavingsAccount::deposit(const Date& date, double amount, const string& desc) {
    record(date, amount, desc);
    acc.change(date, getBalance());
}
void SavingsAccount::withdraw(const Date& date, double amount, const string& desc) {
    if (amount > getBalance())
        error("not enough money");
    else
        record(date, -amount, desc);
    acc.change(date, getBalance());
}
void SavingsAccount::settle(const Date& date) {
    double interest = acc.getSum(date) * rate
                      / (date - Date(date.getYear() - 1, 1, 1));
    if (interest != 0)
        record(date, interest, "interest");
    acc.reset(date, getBalance());
}

// CreditAccount类实现
CreditAccount::CreditAccount(const Date& date, const string& id, double credit,
                             double rate, double fee)
    : Account(date, id), credit(credit), rate(rate), fee(fee), acc(date, 0) {}
void CreditAccount::deposit(const Date& date, double amount, const string& desc) {
    record(date, amount, desc);
    acc.change(date, getDebt());
}
void CreditAccount::withdraw(const Date& date, double amount, const string& desc) {
    if (amount - getBalance() > credit) {
        error("not enough money");
    } else {
        record(date, -amount, desc);
        acc.change(date, getDebt());
    }
}
void CreditAccount::settle(const Date& date) {
    double interest = acc.getSum(date) * rate;
    if (interest != 0) {
        record(date, interest, "interest");
    }
    if (date.getMonth() == 1) {
        record(date, -fee, "annual fee");
    }
    acc.reset(date, getDebt());
}
void CreditAccount::show(ostream& out) const {
    Account::show(out);
    cout << "\tAvailable credit: " << getAvailableCredit() << endl;
}