#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
class SavingsAccount {
public:
    SavingsAccount(int date, int id, double rate);
    int getId() const { return id; }
    double getRate() const { return rate; }
    double getBalance() const { return balance; }
    static double getTotal() { return total; }
    void deposit(int date, double amount);  // 存入现金
    void withdraw(int date, double amount); // 取出现金
    void settle(int date);                  // 结算利息，每年1月1日调用一次
    void show() const;
private:
    int id;
    int lastDate;
    double balance;
    double rate;
    double accumulation; // 余额按日累加之和
    static double total;
    void record(int date, double amount);
    double accumulate(int date) const { // 获得指定日期为止的存款按日累计值
        return accumulation + balance * (date - lastDate);
    }
};
#endif // __ACCOUNT_H__