#include <iostream>
#include <cmath>
using namespace std;

class SavingsAccount {
public:
    SavingsAccount(int date, int id, double rate);
    int getId() { return id; }
    double getRate() { return rate; }
    double getBalance() { return balance; }
    void deposit(int date, double amount);  // 存入现金
    void withdraw(int date, double amount); // 取出现金
    void settle(int date);                  // 结算利息，每年1月1日调用一次
    void show();

private:
    int id;
    int lastDate;
    double balance;
    double rate;
    double accumulation; // 余额按日累加之和
    void record(int date, double amount);
    double accumulate(int date) const { // 获得指定日期为止的存款按日累计值
        return accumulation + balance * (date - lastDate);
    }
};
SavingsAccount::SavingsAccount(int date, int id, double rate)
    : id(id), balance(0), rate(rate), lastDate(date), accumulation(0) {
    cout << date << "\t#" << id << " is created" << endl;
}
void SavingsAccount::record(int date, double amount) {
    accumulation = accumulate(date);
    lastDate = date;
    amount = floor(amount * 100 + 0.5) / 100;
    balance += amount;
    cout << date << "\t#" << id << "\t" << amount << "\t" << balance << endl;
}
void SavingsAccount::deposit(int date, double amount) {
    record(date, amount);
}
void SavingsAccount::withdraw(int date, double amount) {
    if (amount > getBalance()) {
        cout << "Error: not enough money!" << endl;
    } else {
        record(date, -amount);
    }
}
void SavingsAccount::settle(int date) {
    double interest = accumulate(date) * rate / 365; // 年息
    if (interest != 0) {
        record(date, interest);
    }
    accumulation = 0;
}
void SavingsAccount::show() {
    cout << "#" << id << "\tBalance: " << balance << endl;
}

int main() {
    SavingsAccount sa0(1, 21325302, 0.015);
    SavingsAccount sa1(1, 58320212, 0.015);
    sa0.deposit(5, 5000);
    sa1.deposit(25, 10000);
    sa0.deposit(45, 5500);
    sa1.withdraw(60, 4000);
    sa0.settle(90);
    sa1.settle(90);
    sa0.show();
    sa1.show();
    return 0;
}