#include "StopWatch.h"
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    StopWatch sw;
    int count = 1;
    cout << "������ѭ��������" << endl;
    cin >> count;
    sw.start();
    for (int i = 0; i < count; ++i) {}
    sw.stop();
    cout << fixed << setprecision(10);
    cout << "������" << sw.elapsedSecond() << "��" << endl;
    system("PAUSE");
    return 0;
}