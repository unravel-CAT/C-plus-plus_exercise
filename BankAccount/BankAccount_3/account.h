#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
#include "date.h"
#include <string>

class SavingsAccount {
public:
    SavingsAccount(const Date& date, const std::string& id, double rate);
    const std::string& getId() const { return id; }
    double getBalance() const { return balance; }
    double getRate() const { return rate; }
    static double getTotal() { return total; }
    // 存入现金
    void deposit(const Date& date, double amount, const std::string& desc);
    // 取出现金
    void withdraw(const Date& date, double amount, const std::string& desc);
    // 结算利息，每个月结算一次
    void settle(const Date& date);
    // 显示账户信息
    void show() const;
private:
    std::string id;
    double balance;
    double rate;
    Date lastDate;
    double accumulation;
    static double total; // 所有账户的总金额
    // 记录一笔账，date为日期，amount为金额，desc为说明
    void record(const Date& date, double amount, const std::string& desc);
    // 报告错误信息
    void error(const std::string& msg) const;
    // 获得到指定日期为止的存款金额按日累计值
    double accumulate(const Date& date) const {
        return accumulation + balance * date.distance(lastDate);
    }
};
#endif // __ACCOUNT_H__