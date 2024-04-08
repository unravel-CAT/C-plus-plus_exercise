#ifndef __DATE_H__
#define __DATE_H__
class Date {
public:
    Date(int year, int month, int day); // 构造函数
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
    int distance(const Date& date) const {
        return totalDays - date.totalDays;
    }
private:
    int year;
    int month;
    int day;
    int totalDays; // 相对日期
};
#endif // __DATE_H__