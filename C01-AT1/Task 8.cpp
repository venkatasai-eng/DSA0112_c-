#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

int main() {
    int zone;
    int hour;
    long long balance = 10000;
    long long fare = 0;

    cout << "Enter zone (1-Inner, 2-Middle, 3-Outer): ";

    while (!(cin >> zone) || zone < 1 || zone > 3) {
        cout << "Invalid zone. Enter 1, 2, or 3: ";

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    cout << "Enter hour (0-23): ";

    while (!(cin >> hour) || hour < 0 || hour > 23) {
        cout << "Invalid hour. Enter 0-23: ";

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    switch (zone) {
        case 1:
            fare = 1000;
            break;
        case 2:
            fare = 2000;
            break;
        case 3:
            fare = 3000;
            break;
    }

    bool peak = (hour >= 8 && hour < 10) ||
                (hour >= 17 && hour < 20);

    if (peak) {
        fare += fare * 20 / 100;
    }

    cout << "\n----- METRO JOURNEY REPORT -----\n";
    cout << "Zone: " << zone << '\n';
    cout << "Hour: " << hour << '\n';
    cout << "Peak hour: " << (peak ? "Yes" : "No") << '\n';

    cout << fixed << setprecision(2);
    cout << "Fare: Rs " << static_cast<double>(fare) / 100.0 << '\n';

    if (balance - fare >= 5000) {
        balance -= fare;
        cout << "Journey status: Approved\n";
    } else {
        cout << "Journey status: Denied\n";
    }

    cout << "Remaining balance: Rs "
         << static_cast<double>(balance) / 100.0 << '\n';

    return 0;
}