#include <iostream>
using namespace std;

class Time {
    int h, m;

public:
    Time(int hh, int mm) : h(hh), m(mm) {}

    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
};

int minutesBetween(const Time& a, const Time& b)
{
    // TODO 1: Calculate absolute difference in minutes
    int ta = a.h * 60 + a.m;
    int tb = b.h * 60 + b.m;

    return ta > tb ? ta - tb : tb - ta;
}

bool earlier(const Time& a, const Time& b)
{
    // TODO 2: Check whether a is earlier than b
    return a.h * 60 + a.m < b.h * 60 + b.m;
}

int main()
{
    Time departure(9, 45), arrival(13, 10);

    cout << minutesBetween(departure, arrival) << ' '
         << boolalpha << earlier(arrival, departure) << '\n';

    return 0;
}
