#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
#include "date.h"
#include "accumulator.h"
#include <string>
#include <map>
#include <istream>

class Account;
class AccountRecord {
public:
    AccountRecord(const Date& date, const Account* account, double amount,
                  double balance, const std::string& desc);
    void show() const;
private:
    Date date;
    const Account* account; // 账户
    double amount;
    double balance;
    std::string desc;
};

// 定义用来存储账目记录的多重映射类型
typedef std::multimap<Date, AccountRecord> RecordMap;
class Account { // 账户基类
public:
    const std::string& getId() const { return id; }
    double getBalance() const { return balance; }
    static double getTotal() { return total; }
    virtual void deposit(const Date& date, double amount, const std::string& desc) = 0;
    virtual void withdraw(const Date& date, double amount, const std::string& desc) = 0;
    virtual void settle(const Date& date) = 0;
    virtual void show(std::ostream& out) const;
    // 查询指定时间内的账目记录
    static void query(const Date& begin, const Date& end);
protected:
    // 供派生类调用的构造函数
    Account(const Date& date, const std::string& id);
    // 记录一笔账，date为日期，amount为金额，desc为说明
    void record(const Date& date, double amount, const std::string& desc);
    // 报告错误信息
    void error(const std::string& msg) const;
private:
    std::string id;
    double balance;
    static double total;
    static RecordMap recordMap; // 账目记录
};
inline std::ostream& operator<<(std::ostream& out, const Account& account) {
    account.show(out);
    return out;
}

class SavingsAccount : public Account { // 储蓄账户类
public:
    SavingsAccount(const Date& date, const std::string& id, double rate);
    double getRate() const { return rate; }
    // 存入现金
    void deposit(const Date& date, double amount, const std::string& desc);
    // 取出现金
    void withdraw(const Date& date, double amount, const std::string& desc);
    // 结算利息，每个月结算一次
    void settle(const Date& date);
private:
    Accumulator acc;
    double rate;
};

class CreditAccount : public Account { // 信用账户类
public:
    CreditAccount(const Date& date, const std::string& id, double credit,
                  double rate, double fee);
    double getCredit() const { return credit; }
    double getRate() const { return rate; }
    double gerFee() const { return fee; }
    double getAvailableCredit() const { // 获得可用信用额度
        if (getBalance() < 0)
            return credit + getBalance();
        else
            return credit;
    }
    // 存入现金
    void deposit(const Date& date, double amount, const std::string& desc);
    // 取出现金
    void withdraw(const Date& date, double amount, const std::string& desc);
    // 结算利息，每个月结算一次
    void settle(const Date& date);
    void show(std::ostream& out) const;
private:
    Accumulator acc;
    double credit;
    double rate;
    double fee;
    double getDebt() const {
        double balance = getBalance();
        return (balance < 0 ? balance : 0);
    }
};
#endif // __ACCOUNT_H__