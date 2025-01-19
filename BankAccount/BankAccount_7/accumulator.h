#ifndef __ACCUMULATOR_H__
#define __ACCUMULATOR_H__
#include "date.h"
class Accumulator {
public:
    Accumulator(const Date& date, double value)
        : lastDate(date), value(value), sum(0) {}
    double getSum(const Date& date) const {
        return sum + value * (date - lastDate);
    }
    // 在date将数值变更为value
    void change(const Date& date, double value) {
        sum = getSum(date);
        lastDate = date;
        this->value = value;
    }
    // 初始化，将日期变为date，数值变为value，累加器清零
    void reset(const Date& date, double value) {
        lastDate = date;
        this->value = value;
        sum = 0;
    }
private:
    Date lastDate;
    double value;
    double sum;
};
#endif // __ACCUMULATOR_H__