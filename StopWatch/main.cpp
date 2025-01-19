#include "StopWatch.h"
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    StopWatch sw;
    int count = 1;
    cout << "请输入循环次数：" << endl;
    cin >> count;
    sw.start();
    for (int i = 0; i < count; ++i) {}
    sw.stop();
    cout << fixed << setprecision(10);
    cout << "经过了" << sw.elapsedSecond() << "秒" << endl;
    system("PAUSE");
    return 0;
}