#include <iostream>
#include <climits>
using namespace std;

int main() {
    int fareRupees = 30;
    long long balancePaise = 10000;
    double fareDouble = 0.1;
    bool peak = true;
    char zone = 'A';
    unsigned int hour = 8;
    long long journeys = 3000000;

    cout << "Fare: Rs " << fareRupees << '\n';
    cout << "Balance: " << balancePaise << " paise\n";
    cout << "Double value: " << fareDouble << '\n';
    cout << "Peak hour: " << peak << '\n';
    cout << "Zone: " << zone << '\n';
    cout << "Hour: " << hour << '\n';
    cout << "Journeys: " << journeys << '\n';

    cout << "\nData type sizes:\n";
    cout << "sizeof(int): " << sizeof(int) << " bytes\n";
    cout << "sizeof(long long): " << sizeof(long long) << " bytes\n";
    cout << "sizeof(double): " << sizeof(double) << " bytes\n";
    cout << "sizeof(bool): " << sizeof(bool) << " bytes\n";
    cout << "sizeof(char): " << sizeof(char) << " byte\n";

    cout << "\nINT_MAX: " << INT_MAX << '\n';
    cout << "INT_MIN: " << INT_MIN << '\n';

    long long totalPaise =
        static_cast<long long>(journeys) * 3000LL;

    cout << "Total collection for 3000000 journeys: Rs "
         << totalPaise / 100 << '\n';

    double totalDouble = 0.1 * 1000000;
    cout << "Double calculation (0.1 * 1000000): "
         << totalDouble << '\n';

    return 0;
}