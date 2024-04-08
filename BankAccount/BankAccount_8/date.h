#ifndef __DATE_H__
#define __DATE_H__
#include <iostream>

class Date {
public:
    Date(int year = 1, int month = 1, int day = 1); // 构造函数
    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }
    // 获得当月有多少天
    int getMaxDay() const;
    // 判断是否是闰年
    bool isLeapYear() const {
        return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    }
    void show() const;
    // 计算两个日期相差多少天
    int operator-(const Date& date) const {
        return totalDays - date.totalDays;
    }
    // 判断两个日期的先后顺序
    bool operator<(const Date& date) const {
        return totalDays - date.totalDays;
    }
private:
    int year;
    int month;
    int day;
    int totalDays; // 相对日期
};
std::istream& operator>>(std::istream& in, Date& date);
std::ostream& operator<<(std::ostream& out, const Date& date);
#endif // __DATE_H__